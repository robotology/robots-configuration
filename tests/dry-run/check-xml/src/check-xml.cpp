/******************************************************************************
 *                                                                            *
 * Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include <pugixml.hpp>
#include <yarp/os/ResourceFinder.h>


std::string ltrim(const std::string &s) {
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}
 
std::string rtrim(const std::string &s) {
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}
 
std::string trim(const std::string &s) {
    return ltrim(rtrim(s));
}

bool loadIni(const std::string& robot_dir, std::string& inifile) {
    inifile = robot_dir + inifile;
    std::ifstream in(inifile);
    std::vector<std::string> vecOfStrs;

    if(!in)
    {
        std::cerr << "Cannot open the yarprobotinterface.ini File !!! Exiting..." << std::endl;
        return false;
    }
    else std::cout << "yarprobotinterface.ini FOUND! PASSED" << std::endl;

     std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    in.close();

    str = vecOfStrs.at(0);
    str = std::regex_replace(str, std::regex("config ./"), ""); 
    inifile = trim(robot_dir + str);
    
    return true;
}

inline bool fileExists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

bool checkIncludedFiles(const std::string& robot_dir, std::vector<std::string>& vectorAllFiles,
                        const std::string& filename, pugi::xml_document& doc ){
    int tot,notfound,found;
    pugi::xml_node hrefs = doc.child("robot").child("devices");
    tot =0;
    notfound =0;
    found=0;

    for (auto fpath = hrefs.first_child(); fpath; fpath = fpath.next_sibling())
    {
        tot++;
        vectorAllFiles.push_back(robot_dir + fpath.first_attribute().value());
        if(fileExists(robot_dir + fpath.first_attribute().value())){
        std::cout << "found :" << robot_dir + fpath.first_attribute().value() << std::endl;
        found++;
    }
        else {
            std::cerr << "NOT found :" << robot_dir + fpath.first_attribute().value() << std::endl;
            notfound++;
        }
    }

    std::cout << std::endl << "***************************************" << std::endl;

    if(found == tot){
        std::cout << "PASS ! found " << found << " of " << tot << " file included." << std::endl << std::endl;
        return true;
    }
        
    else{
        std::cerr << "FAIL ! not found " << notfound << " of " << tot << " file included." << std::endl << std::endl;
        return false;
    }
       
}

bool loadXmlFile(const std::string& robot_dir, const std::string& filename, pugi::xml_document& doc){
    pugi::xml_parse_result result = doc.load_file(filename.c_str());
    
    if(result){
        return true;
    }
    else{
        std::cout << "Loading " + filename + " : " << result.description() << std::endl;
        return false;
    }
}

bool checkWrappersRemappers(const std::string& robot_dir, std::vector<std::string>& vectorAllFiles,
                            const std::string& part, const std::string& target, bool& pass){
    bool found = false;
    pugi::xml_document doc_wrapper, doc_remapper;
    std::string device;

    for (auto ele : vectorAllFiles)
    {
        if(ele.find(part) == std::string::npos) {
            continue;
        }

        auto base_filename = ele.substr(ele.find_last_of("/\\") + 1);
        auto part_ = std::regex_replace(base_filename, std::regex("_mc.*"), "");
        part_ = std::regex_replace(part_, std::regex("-mc.*"), "");
        part_ = trim(part_);
        if(part != part_) {
            continue;
        }

        if(ele.find("wrappers/motorControl") != std::string::npos){
            if(ele.find("wrapper.xml") != std::string::npos) {
                if(!loadXmlFile(robot_dir, ele, doc_wrapper)) return false;
                pugi::xpath_node action_startup = doc_wrapper.select_node("//action[@phase='startup']/param[@name='device']/text()");
                device = trim(action_startup.node().value());
                if(device == target) std::cout << part <<" - WRAPPER CHECK PASSED!" << std::endl;
                else {
                    std::cerr << part << " - WRAPPER CHECK FAILED!" << std::endl;
                    pass = false;
                }
                found = true;
            }
            else if (ele.find("remapper.xml")){
                if(!loadXmlFile(robot_dir, ele, doc_remapper)) return false;
                pugi::xpath_node device_name = doc_remapper.select_node("device");
                device = trim(device_name.node().attribute("name").value());
                if(device == target) std::cout << part << " - REMAPPER CHECK PASSED!" << std::endl;
                else {
                    std::cerr << part << " - REMAPPER CHECK FAILED!" << std::endl;
                    pass = false;
                }
                found = true;
            }
        }
    }

    return found;
}

bool checkCartesian(const std::string& robot_dir, std::vector<std::string>& vectorAllFiles,
                    const std::string& part, const std::string& target, bool& pass){
    bool found = false;
    pugi::xml_document doc_cartesian;
    std::string torso, arm;

    for (auto ele : vectorAllFiles)
    {
        if(ele.find("cartesian") != std::string::npos && ele.find(part) != std::string::npos) {
            if(!loadXmlFile(robot_dir, ele, doc_cartesian)) return false;
            pugi::xpath_node elem_torso = doc_cartesian.select_node("//action[@phase='startup']/paramlist[@name='networks']/elem[@name='torso']/text()");
            torso = trim(elem_torso.node().value());
            arm = "//action[@phase='startup']/paramlist[@name='networks']/elem[@name='" + part + "']/text()";
            pugi::xpath_node elem_arm = doc_cartesian.select_node(arm.c_str());
            arm = trim(elem_arm.node().value());
            if(torso == "torso-mc_remapper" && arm == target || torso == "torso_mc_remapper" && arm == target) std::cout << part <<" - CARTESIAN CHECK PASSED!" << std::endl;
            else {std::cerr << part << " - CARTESIAN CHECK FAILED! " << std::endl; pass = false;} 
            found = true;
        }
    }
    return true;
}

bool checkCalibratorsWrappersRemappers(const std::string& robot_dir, std::vector<std::string>& vectorAllFiles, bool& pass){
    for (auto ele : vectorAllFiles)
    {
        std::string part, target1, target2;

        if(ele.find("calibrators") != std::string::npos) {
            pugi::xml_document doc_calibrator;
            loadXmlFile(robot_dir, ele, doc_calibrator);
            pugi::xpath_node action_startup = doc_calibrator.select_node("//action[@phase='startup']/param[@name='target']/text()");
            pugi::xpath_node action_interrupt1 = doc_calibrator.select_node("//action[@phase='interrupt1']/param[@name='target']/text()");

            part = std::regex_replace(action_startup.node().value(), std::regex("_mc.*"), "");
            part = std::regex_replace(part, std::regex("-mc.*"), "");
            part = trim(part);

            target1 = trim(action_startup.node().value());
            target2 = trim(action_interrupt1.node().value());

            if(ele.find("hand") == std::string::npos){
                if(target1 == target2){
                    std::cout << part << " - CALIBRATOR CHECK PASSED!" << std::endl;
                }
                else{
                    std::cerr << part << " CALIBRATOR CHECK FAILED!" << std::endl;
                    pass = false;
                }

                checkWrappersRemappers(robot_dir, vectorAllFiles, part, target1, pass);
                if(ele.find("arm") != std::string::npos){
                    checkCartesian(robot_dir, vectorAllFiles, part, target1, pass);
                }
            }
            
            doc_calibrator.reset();
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    std::string filename = "yarprobotinterface.ini";
    pugi::xml_document doc;
    std::vector<std::string> vectorAllFiles;
    bool ALL_PASSED = true;
    bool XSD_PASSED = true;
    bool found = false;
    std::string robot_dir;

    yarp::os::ResourceFinder rf;
    rf.setDefaultContext("check-xml");
    rf.configure(argc, argv);

    robot_dir = rf.find("robot-dir").asString();
    robot_dir = robot_dir + "/";
    
    // loads the XML file contained in yarprobotinterface.ini
    std::cout << std::endl << "1 - test yarprobotinterface.ini presence **************" << std::endl << std::endl;
    if(!loadIni(robot_dir, filename)) return EXIT_FAILURE;

    // loads the above XML file, e.g. icub_all.xml
    if(!loadXmlFile(robot_dir, filename, doc)) return EXIT_FAILURE;

    // checks if all files included in the XML exist
    std::cout << std::endl << "2 - test included xml files presence **************" << std::endl << std::endl;

    if(!checkIncludedFiles(robot_dir, vectorAllFiles, filename, doc)) return EXIT_FAILURE;
   
    // checks calibrators/wrappers/remappers/cartesian xml files consistency
    std::cout << std::endl << "3 - test calibrators/wrappers/remappers/cartesian xml files consistency **************" << std::endl << std::endl;

    if(!checkCalibratorsWrappersRemappers(robot_dir, vectorAllFiles, ALL_PASSED)) return EXIT_FAILURE;

    // checks calibrators xml files w/ XSD schema
    std::cout << std::endl << "4 - test calibrators consistency with XSD schema **************" << std::endl << std::endl;
    for (auto ele : vectorAllFiles)
    {
        if(ele.find("calibrators") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            auto calibrators = rf.findFile("calibrators.xsd");
            auto xsd_cmd = "xmllint --schema " + calibrators + " " +  ele + " --noout";
            auto ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
        }
    }
    if(!found) std::cout << "Calibrators not found! Skipped!" << std::endl;
    else if(XSD_PASSED) std::cout << "Calibrators XSD check passed!" << std::endl;
    else std::cerr << "Calibrators XSD check failed!" << std::endl;

    // checks cartesian xml files w/ XSD schema
    XSD_PASSED = true;
    found = false;
    std::cout << std::endl << "5 - test cartesian consistency with XSD schema **************" << std::endl << std::endl;
    for (auto ele : vectorAllFiles)
    {
        if(ele.find("cartesian") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            std::string schema_suffix;
            if(ele.find("arm") != std::string::npos) {
                schema_suffix = "_arms";
            } else if(ele.find("leg") != std::string::npos) {
                schema_suffix = "_legs";
            } else {
                ALL_PASSED = false;
                XSD_PASSED = false;
                std::cerr << "Cartesian part unrecognized!" << std::endl;
            }

            if(!schema_suffix.empty()) {
                auto cartesian = rf.findFile("cartesian"+schema_suffix+".xsd");
                auto xsd_cmd = "xmllint --schema " + cartesian + " " +  ele + " --noout";
                auto ret = system(xsd_cmd.c_str());
                
                if (WEXITSTATUS(ret) != 0) {            
                    ALL_PASSED = false;
                    XSD_PASSED = false;
                }
            }
        }
    }
    if(!found) std::cout << "Cartesian not found! Skipped!" << std::endl;
    else if(XSD_PASSED) std::cout << "Cartesian XSD check passed!" << std::endl;
    else std::cerr << "Cartesian XSD check failed!" << std::endl;
    
    // checks wrappers xml files w/ XSD schema
    XSD_PASSED = true;
    found = false;
    std::cout << std::endl << "6 - test wrappers consistency with XSD schema **************" << std::endl << std::endl;
    for (auto ele : vectorAllFiles)
    {
        if(ele.find("wrappers/motorControl") != std::string::npos && ele.find("_wrapper") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            auto wrapper = rf.findFile("wrapper.xsd");
            auto xsd_cmd = "xmllint --schema " + wrapper + " " +  ele + " --noout";
            auto ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
        }
    }
    if(!found) std::cout << "Wrappers not found! Skipped!" << std::endl;
    else if(XSD_PASSED) std::cout << "Wrappers XSD check passed!" << std::endl;
    else std::cerr << "Wrappers XSD check failed!" << std::endl;

    // checks remappers xml files w/ XSD schema
    XSD_PASSED = true;
    found = false;
    std::cout << std::endl << "7 - test remappers consistency with XSD schema **************" << std::endl << std::endl;
    for (auto ele : vectorAllFiles)
    {
        if(ele.find("wrappers/motorControl") != std::string::npos && ele.find("_remapper") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            auto remapper = rf.findFile("remapper.xsd");
            auto xsd_cmd = "xmllint --schema " + remapper + " " +  ele + " --noout";
            auto ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
        }
    }
    if(!found) std::cout << "Remappers not found! Skipped!" << std::endl;
    else if(XSD_PASSED) std::cout << "Remappers XSD check passed!" << std::endl;
    else std::cerr << "Remappers XSD check failed!" << std::endl;

    std::cout << std::endl << "***************************************************" << std::endl;
    if(ALL_PASSED) std::cout << std::endl << "ALL TESTS PASSED!!" << std::endl;
    else std::cerr << std::endl << "SOME TESTS FAILED!!" << std::endl;

    return (ALL_PASSED ? EXIT_SUCCESS : EXIT_FAILURE);
}

