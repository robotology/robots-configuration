#include "pugixml.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

 
std::string ltrim(const std::string &s) {
    return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}
 
std::string rtrim(const std::string &s) {
    return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}
 
std::string trim(const std::string &s) {
    return ltrim(rtrim(s));
}

bool loadIni(std::string robot_dir, std::string & inifile){

    inifile = robot_dir + inifile;

    std::ifstream in(inifile);
    std::vector<std::string> vecOfStrs;

    if(!in)
    {
        std::cout << "Cannot open the yarprobotinterface.ini File !!! Exiting..." << std::endl;
        return false;
    }
    else std::cout << "yarprobotinterface.ini FOUND! PASS" << std::endl;

     std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //  std::cout << vecOfStrs.at(0) << std::endl;
    //Close The File
    in.close();

    str = vecOfStrs.at(0);
    str = std::regex_replace(str, std::regex("config ./"), ""); 
    inifile = robot_dir + str;
    
    return true;
}

inline bool fileExists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

bool checkIncludedFiles(std::string robot_dir, std::vector<std::string>& vectorAllFiles, std::string& filename, pugi::xml_document& doc ){

    int tot,notfound,found;

    // pugi::xml_document doc;

    // pugi::xml_parse_result result = doc.load_file(filename.c_str());

    // std::cout << "Loading " + filename + " : " << result.description() << std::endl;

    pugi::xml_node hrefs = doc.child("robot").child("devices");
    tot =0;
    notfound =0;
    found=0;


    for (pugi::xml_node fpath = hrefs.first_child(); fpath; fpath = fpath.next_sibling())
        {
            tot++;
            vectorAllFiles.push_back(robot_dir + fpath.first_attribute().value());
            if(fileExists(robot_dir + fpath.first_attribute().value())){
            std::cout << "found :" << robot_dir + fpath.first_attribute().value() << std::endl;
            found++;
        }
            else{
                std::cout << "NOT found :" << robot_dir + fpath.first_attribute().value() << std::endl;
                notfound++;
            }
        }

    std::cout << std::endl << "***************************************" << std::endl;

    if(found == tot){
        std::cout << "PASS ! found " << found << " of " << tot << " file included." << std::endl << std::endl;
        return true;
    }
        
    else{
        std::cout << "FAIL ! not found " << notfound << " of " << tot << " file included." << std::endl << std::endl;
        return false;
    }
       
}

bool loadXmlFile(std::string robot_dir, std::string& filename, pugi::xml_document& doc){
    // std::string fn;
    // fn = robot_dir + filename;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    
    if(result){
        // std::cout << "Loading " + filename + " : " << result.description() << std::endl;
        return true;
    }
    else{
        std::cout << "Loading " + filename + " : " << result.description() << std::endl;
        return false;
    }
}


bool checkWrappersRemappers(std::string robot_dir, std::vector<std::string> & vectorAllFiles, std::string part, std::string target, bool & pass){
    bool found = false;
    pugi::xml_document doc_wrapper, doc_remapper;
    std::string device;


    for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
                   // std::cout << part << " " << ele << std::endl;

        if(ele.find("wrappers/motorControl") != std::string::npos && ele.find(part) != std::string::npos && ele.find("wrapper.xml") != std::string::npos) {
            //std::cout << part << " " << ele << std::endl;
            if(!loadXmlFile(robot_dir, ele, doc_wrapper)) return false;
            pugi::xpath_node action_startup = doc_wrapper.select_node("//action[@phase='startup']/param[@name='device']/text()");
            device = trim(action_startup.node().value());
            if(device == target) std::cout << part <<" - WRAPPER CHECK PASSED!" << std::endl;
            else {std::cout << part << " - WRAPPER CHECK FAILED!" << std::endl; pass = false;} 
            found = true;
        }
        else if (ele.find("wrappers/motorControl") != std::string::npos && ele.find(part) != std::string::npos && ele.find("remapper.xml")){
            //std::cout << part << " " << ele << std::endl;
            if(!loadXmlFile(robot_dir, ele, doc_remapper)) return false;
            pugi::xpath_node device_name = doc_remapper.select_node("device");
            device = trim(device_name.node().attribute("name").value());
            if(device == target) std::cout << part << " - REMAPPER CHECK PASSED!" << std::endl;
            else {std::cout << part << " - REMAPPER CHECK FAILED!" << std::endl; pass = false;} 

            found = true;
        }
        
    }
    if(found) return true;
    else return false;
}

bool checkCartesian(std::string robot_dir, std::vector<std::string> & vectorAllFiles, std::string part, std::string target, bool & pass){
    bool found = false;
    pugi::xml_document doc_cartesian;
    std::string torso, arm;

    for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
        if(ele.find("cartesian") != std::string::npos && ele.find(part) != std::string::npos) {
            // std::cout << part << " " << ele << std::endl;
            if(!loadXmlFile(robot_dir, ele, doc_cartesian)) return false;
            pugi::xpath_node elem_torso = doc_cartesian.select_node("//action[@phase='startup']/paramlist[@name='networks']/elem[@name='torso']/text()");
            torso = trim(elem_torso.node().value());
            arm = "//action[@phase='startup']/paramlist[@name='networks']/elem[@name='" + part + "']/text()";
            pugi::xpath_node elem_arm = doc_cartesian.select_node(arm.c_str());
            arm = trim(elem_arm.node().value());
            //std::cout << part << " " << arm << " " << target << std::endl;
            if(torso == "torso-mc_remapper" && arm == target || torso == "torso_mc_remapper" && arm == target) std::cout << part <<" - CARTESIAN CHECK PASSED!" << std::endl;
            else {std::cout << part << " - CARTESIAN CHECK FAILED! " << std::endl; pass = false;} 
            found = true;
        }
    }
    return true;
}

bool checkCalibratorsWrappersRemappers(std::string robot_dir, std::vector<std::string> & vectorAllFiles, bool & pass){
    for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
        std::string part, target1, target2;

        if(ele.find("calibrators") != std::string::npos) {
            // std::cout << ele << std::endl;
            pugi::xml_document doc_calibrator;
            loadXmlFile(robot_dir, ele, doc_calibrator);
            pugi::xpath_node action_startup = doc_calibrator.select_node("//action[@phase='startup']/param[@name='target']/text()");
            pugi::xpath_node action_interrupt1 = doc_calibrator.select_node("//action[@phase='interrupt1']/param[@name='target']/text()");
            part = std::regex_replace(action_startup.node().value() , std::regex("_mc.*"), "");
            part = std::regex_replace(part , std::regex("-mc.*"), "");

            part = trim(part);
            //std::cout << part << std::endl;
            target1 = trim(action_startup.node().value());
            target2 = trim(action_interrupt1.node().value());
            if((target1 == target2) && target1.find("remapper") != std::string::npos && target2.find("remapper") != std::string::npos && !(ele.find("hand") != std::string::npos)){
                std::cout << part << " - CALIBRATOR CHECK PASSED!" << std::endl;
                // std::cout << target1 << " " << target2 << std::endl;
                // return true;
            }
            else if(!(ele.find("hand") != std::string::npos))  {std::cout << part << " CALIBRATOR CHECK FAILED!" << std::endl; pass = false;} 

            if(!(ele.find("hand") != std::string::npos)) {
                //std::cout << part << std::endl;
                checkWrappersRemappers(robot_dir, vectorAllFiles, part, target1, pass);
                if(ele.find("arm") != std::string::npos) checkCartesian(robot_dir, vectorAllFiles, part, target1, pass);
            }
      //      std::cout << part << std::endl;
            
            doc_calibrator.reset();
        }
        
    }
    return true;
}


int main(int argc, char *argv[])
{
    std::string filename = "yarprobotinterface.ini";
    pugi::xml_document doc;
    std::vector<std::string> vectorAllFiles;
    bool ALL_PASSED = true;
    bool XSD_PASSED = true;
    bool found = false;
    std::string robot_dir,xsd_cmd;
    int ret;
    

    robot_dir = argv[1];
    robot_dir = robot_dir + "/";
    
    // loads the XML file contained in yarprobotinterface.ini
    std::cout << std::endl << "1 - test yarprobotinterface.ini presence **************" << std::endl << std::endl;
    if(!loadIni(robot_dir, filename)) return 0;

    // loads the above XML file i.e. icub_all.xml
    if(!loadXmlFile(robot_dir, filename, doc)) return 0;

    // checks if all files included in the XML exist
    std::cout << std::endl << "2 - test included xml files presence **************" << std::endl << std::endl;

    if(!checkIncludedFiles(robot_dir, vectorAllFiles, filename, doc)) return 0;
   
    // checks calibrators/wrappers/remappers/cartesian xml files consistency
    std::cout << std::endl << "3 - test calibrators/wrappers/remappers/cartesian xml files consistency **************" << std::endl << std::endl;

    if(!checkCalibratorsWrappersRemappers(robot_dir, vectorAllFiles, ALL_PASSED)) return 0;


    // checks calibrators xml files w/ XSD schema
    std::cout << std::endl << "4 - test calibrators consistency with XSD schema **************" << std::endl << std::endl;
    for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
        if(ele.find("calibrators") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            xsd_cmd = "xmllint --schema ..\/calibrators.xsd " +  ele + " --noout";
            ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
            
        }
    }
    if(!found){
        ALL_PASSED = false;
        XSD_PASSED = false;
    }
    if(XSD_PASSED) std::cout << "Calibrators XSD check passed!" << std::endl;
    else std::cout << "Calibrators XSD check failed!" << std::endl;

    // checks cartesian xml files w/ XSD schema
    XSD_PASSED = true;
    found = false;
    std::cout << std::endl << "5 - test cartesian consistency with XSD schema **************" << std::endl << std::endl;
    for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
        if(ele.find("cartesian") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            xsd_cmd = "xmllint --schema ..\/cartesian.xsd " +  ele + " --noout";
            ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
            
        }
    }
    if(!found){
        ALL_PASSED = false;
        XSD_PASSED = false;
    }
    if(XSD_PASSED) std::cout << "Cartesian XSD check passed!" << std::endl;
    else std::cout << "Cartesian XSD check failed!" << std::endl;

    // checks wrappers xml files w/ XSD schema
    XSD_PASSED = true;
    found = false;
    std::cout << std::endl << "6 - test wrappers consistency with XSD schema **************" << std::endl << std::endl;
    for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
        if(ele.find("wrappers/motorControl") != std::string::npos && ele.find("_wrapper") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            xsd_cmd = "xmllint --schema ..\/wrapper.xsd " +  ele + " --noout";
            ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
            
        }
    }
    if(!found){
        ALL_PASSED = false;
        XSD_PASSED = false;
    }
    if(XSD_PASSED) std::cout << "Wrappers XSD check passed!" << std::endl;
    else std::cout << "Wrappers XSD check failed!" << std::endl;

    // checks remappers xml files w/ XSD schema
    XSD_PASSED = true;
    found = false;
    std::cout << std::endl << "7 - test remappers consistency with XSD schema **************" << std::endl << std::endl;
        for (std::vector<std::string>::iterator t=vectorAllFiles.begin(); t!=vectorAllFiles.end(); ++t) 
    {
        std::string ele = *t;
        if(ele.find("wrappers/motorControl") != std::string::npos && ele.find("_remapper") != std::string::npos) {
            found = true;
            std::cout << ele << std::endl;
            xsd_cmd = "xmllint --schema ..\/remapper.xsd " +  ele + " --noout";
            ret = system(xsd_cmd.c_str()); 
            if (WEXITSTATUS(ret) != 0) {            
                ALL_PASSED = false;
                XSD_PASSED = false;
            }
            
        }
    }
    if(!found){
        ALL_PASSED = false;
        XSD_PASSED = false;
    }
    if(XSD_PASSED) std::cout << "Remappers XSD check passed!" << std::endl;
    else std::cout << "Remappers XSD check failed!" << std::endl;

    std::cout << std::endl << "***************************************************" << std::endl;
    if(ALL_PASSED) std::cout << std::endl << "ALL TESTS PASSED!!" << std::endl;
    else std::cout << std::endl << "SOME TESTS FAILED!!" << std::endl;



}



