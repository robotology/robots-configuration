/******************************************************************************
 *                                                                            *
 * Copyright (C) 2021 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/PeriodicThread.h>
#include <yarp/os/Property.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Time.h>

#include <fstream>
#include <string>
#include <vector>
#include <signal.h>

 /******************************************************************************/
struct DataExperiment {
  double pwm;
  double pid_out;
  double enc;
  double ref;
  double err;
  double target;
  double taskspace_enc;
  double current;
};

constexpr int PITCH_JOINT_ID = 2;
constexpr int ROLL_JOINT_ID = 1;
constexpr int YAW_JOINT_ID = 0;


bool TERMINATED = false;

/******************************************************************************/
// The function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum) {
  // Terminate program
  TERMINATED = true;
}

class ReadThread : public yarp::os::PeriodicThread {
private:
  yarp::dev::PolyDriver driver;
  yarp::dev::IEncoders* iEnc{ nullptr };
  yarp::dev::IPidControl* iPidCtrl{ nullptr };
  yarp::dev::IPositionControl* iPosCtrl{ nullptr };
  yarp::dev::IAmplifierControl* iAmplifier{ nullptr };
  
  
  std::ofstream file_output;
  std::string remote;
  std::string fname;
  std::vector<DataExperiment> yaw_data;
  std::vector<DataExperiment> roll_data;
  std::vector<DataExperiment> pitch_data;
  std::vector<double> time_vector;
  double t0;

public:
  ReadThread(const yarp::conf::float64_t period, const std::string& remote_port, const std::string& filename)
    : PeriodicThread(period) {
    remote = remote_port;
    fname = filename;
  }

  bool threadInit() {
    yInfo() << "ReadThread starting";

    yarp::os::Property conf;
    conf.put("device", "remote_controlboard");
    conf.put("remote", remote);
    conf.put("local", "/logger");

    if (!driver.open(conf)) {
      yError() << "Failed to connect to" << remote;
      return false;
    }

    if (!(driver.view(iEnc))) {
      yError() << "Failed to open encoder interface";
      driver.close();
      return false;
    }

    if (!(driver.view(iAmplifier))) {
      yError() << "Failed to open amplifier interface";
      driver.close();
      return false;
    }
    
    if (!(driver.view(iPidCtrl))) {
      yError() << "Failed to open PID control interface";
      driver.close();
      return false;
    }

    if (!(driver.view(iPosCtrl))) {
      yError() << "Failed to open position control interface";
      driver.close();
      return false;
    }

    file_output.open(fname);

    if (!file_output.is_open()) {
      yError() << "Failed to open "
        << fname;
      driver.close();
      return false;
    }

    file_output << "Time"<< ","<< "Mot0_Pwm"<< ","<< "Mot1_Pwm"<< ","<< "Mot2_Pwm"<< ","
      << "Mot0_Ref"<< ","<< "Mot1_Ref"<< ","<< "Mot2_Ref"<< ","
      << "Mot0_Err"<< ","<< "Mot1_Err"<< ","<< "Mot2_Err" << "," 
      << "Roll"<< ","<< "Pitch"<< ","<< "Yaw" << ","<< "Curr2 " << ","<< " Curr0" << ","<< "Curr1" << ","<< "setRoll"<< ","<<"setPitch"<< ","<< "setYaw" << std::endl;
    t0 = yarp::os::Time::now();

    return true;
  }

  void run() {
    DataExperiment yaw_d;
    DataExperiment roll_d;
    DataExperiment pitch_d;
    time_vector.push_back(static_cast<double>(yarp::os::Time::now() - t0));

    iEnc->getEncoder(YAW_JOINT_ID, &yaw_d.taskspace_enc);
    iEnc->getEncoder(ROLL_JOINT_ID, &roll_d.taskspace_enc);
    iEnc->getEncoder(PITCH_JOINT_ID, &pitch_d.taskspace_enc);
    
    iAmplifier->getCurrent(YAW_JOINT_ID, &yaw_d.current); 
    iAmplifier->getCurrent(PITCH_JOINT_ID, &pitch_d.current);
    iAmplifier->getCurrent(ROLL_JOINT_ID, &roll_d.current);
    
    iPidCtrl->getPidReference(yarp::dev::VOCAB_PIDTYPE_POSITION, YAW_JOINT_ID,
      &yaw_d.ref);
    iPidCtrl->getPidReference(yarp::dev::VOCAB_PIDTYPE_POSITION, ROLL_JOINT_ID,
      &roll_d.ref);
    iPidCtrl->getPidReference(yarp::dev::VOCAB_PIDTYPE_POSITION, PITCH_JOINT_ID,
      &pitch_d.ref);

    if (!iPosCtrl->getTargetPosition(YAW_JOINT_ID, &yaw_d.target))
      yWarning() << "Cannot retrieve yaw tg";
    if (!iPosCtrl->getTargetPosition(ROLL_JOINT_ID, &roll_d.target))
      yWarning() << "Cannot retrieve roll tg";
    if (!iPosCtrl->getTargetPosition(PITCH_JOINT_ID, &pitch_d.target))
      yWarning() << "Cannot retrieve pitch tg";

    iPidCtrl->getPidError(yarp::dev::VOCAB_PIDTYPE_POSITION, YAW_JOINT_ID, &yaw_d.err);
    iPidCtrl->getPidError(yarp::dev::VOCAB_PIDTYPE_POSITION, ROLL_JOINT_ID, &roll_d.err);
    iPidCtrl->getPidError(yarp::dev::VOCAB_PIDTYPE_POSITION, PITCH_JOINT_ID, &pitch_d.err);

    iPidCtrl->getPidOutput(yarp::dev::VOCAB_PIDTYPE_POSITION, YAW_JOINT_ID, &yaw_d.pwm);
    iPidCtrl->getPidOutput(yarp::dev::VOCAB_PIDTYPE_POSITION, ROLL_JOINT_ID, &roll_d.pwm);
    iPidCtrl->getPidOutput(yarp::dev::VOCAB_PIDTYPE_POSITION, PITCH_JOINT_ID, &pitch_d.pwm);

    yaw_data.push_back(std::move(yaw_d));
    roll_data.push_back(std::move(roll_d));
    pitch_data.push_back(std::move(pitch_d));
  }

  void threadRelease() {
    for (uint32_t i = 0; i < roll_data.size(); ++i) {
      file_output << time_vector[i] << "," << yaw_data[i].pwm << ","
        << roll_data[i].pwm << "," << pitch_data[i].pwm << ","
        << yaw_data[i].ref << "," << roll_data[i].ref << ","
        << pitch_data[i].ref << "," << yaw_data[i].err << ","
        << roll_data[i].err << "," << pitch_data[i].err << ","
        << roll_data[i].taskspace_enc << "," << pitch_data[i].taskspace_enc << "," 
        << yaw_data[i].taskspace_enc << ","<< roll_data[i].current << "," << pitch_data[i].current << "," 
        << yaw_data[i].current << "," << roll_data[i].target << "," << pitch_data[i].target << "," 
        << yaw_data[i].target << "," << std::endl;
    }
    yInfo() << "Saved data";

    // Close I/O resources
    file_output.close();
    driver.close();

    yInfo() << "Done.";
  }
};

/****************************************************************q`**************/
int main(int argc, char* argv[]) {
  // Register signal and signal handler
  signal(SIGINT, signal_callback_handler);

  yarp::os::Network yarp;
  if (!yarp.checkNetwork()) {
    yError() << "Unable to find YARP server!";
    return EXIT_FAILURE;
  }

  yarp::os::ResourceFinder rf;
  rf.configure(argc, argv);

  auto remote = rf.check("remote", yarp::os::Value("/nfa/wrist_mc")).asString();
  auto filename = rf.check("file", yarp::os::Value("log.csv")).asString();
  auto period = rf.check("period", yarp::os::Value(0.01)).asFloat64();

  ReadThread read_thread(period, remote, filename);

  yInfo() << "Started recording...";
  read_thread.start();

  while (!TERMINATED) {
    yInfo() << "Recording data...";
    yarp::os::Time::delay(5);
  }

  if (TERMINATED) {
    yInfo() << "Catched SIGINT, saving data to file...";
    read_thread.stop();
  }

  return EXIT_SUCCESS;
}
