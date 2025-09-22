/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>

#include "Constants.h"

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace cv;
using namespace std;
#define pix 10 // 25



class Camera : public frc2::SubsystemBase {
 public:
  Camera();
  void Periodic() override;
  void SetColorRange(double hmin, double hmax, double smin, double smax, double vmin, double vmax);
  bool colorDetected(Mat img);
  double getCountours(Mat mask, int FrameWidth);
  double GetDiferenceToCube();
  bool FarbeErkannt();
  void EnableCamera(bool enable);
  void DetectLine(Mat img, int FrameWidth);
  void TakePictureForQRCode();
  void TakeSinglePicture();
  void SearchforCube();
  double GetCubeHigh();

  bool drive_Right();
  bool drive_Left();
  bool drive_direction_right();

  int GetDetectedColor();
  int GetLastColorRead();
  int GetLastNumberRead();
  bool LastNumberEven();
  bool IsDetectedColorSearched();

  void SetColorDetection(int ColorID);

  bool IsSearchedColorRed();
  bool IsSearchedColorBlue();
  bool IsSearchedColorYellow();

 private:
  #define COUNT 1

  void ProcessPicture();
  bool ProcessSinglePicture();

  bool ColorDetected = false;
  double DiferenceToCube = 0;
  double DiferenceToCubeArray[COUNT] = {0};
  double DiferenceToCubeHelp=0;
  int DiferenceToCubeCount = 0;
  double CubeHigh = 0;
  bool CubeAvailable = false;

  bool CameraEnable=false;
  
  double hmin = 100, smin = 70, vmin = 10;
  double hmax = 179, smax = 150, vmax = 60;

  double hmin_red[2] = {104,95};
  double hmax_red[2] = {114,116};
  double smin_red[2] = {141,121};
  double smax_red[2] = {185,171};
  double vmin_red[2] = {55,46};
  double vmax_red[2] = {105,89};

  double hmin_yel[2] = {79,79};
  double hmax_yel[2] = {95,91};
  double smin_yel[2] = {135,151};
  double smax_yel[2] = {181,181};
  double vmin_yel[2] = {74,79};
  double vmax_yel[2] = {138,146};

  Mat img, picture_hsv, mask, mask_new, mask_new2, finish, mask_test;
  Mat qr;
  Mat bbox, rectifiedImage;

  QRCodeDetector qrDecoder;
  
  Vec3b color;
  
  Scalar m_lower, m_upper;

  VideoCapture inputVideo; //to open video flux
  VideoCapture cap;
  
  int FrameWidth = 0;

  cv::String date;
  
  std::string QRs[10] = { "0" };

  bool Color_detected = false;

  //fstream file;
  //int i = 0;
  

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  
};
