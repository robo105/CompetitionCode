#include "subsystems/Camera.h"

Camera::Camera()
{
    
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    //lower[0]=0;
    m_lower=lower;
    m_upper=upper;

    for(int i=0;i<10;i++)
    {
        QRs[i]="";
    }

    //inputVideo.open(0);
    //VideoCapture cap(0);
    //cap.open(0);
    /*cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CAP_PROP_FRAME_WIDTH, 1920);*/
    //cap  img;
    

    global::SelectRed=0;
}

std::string lastData = "";
std::string lastColor = "";
std::string lastDirection = "";
int detectedColor = -1;
int lastNumber = -1;

bool Camera::colorDetected(Mat img)
{
  int cnt = 0;

  cnt = countNonZero(img);

  /*for(int i=0; i<640; i++)
  {
    for(int j=0; j<480; j++)
    {
        color = img.at<Vec3b>(Point(i,j));
        if(color[0] == (255))
        {
          cnt++;
         
          if(cnt >= 100)
          {
            return true;
          }
        }
    }
  }*/
  if(constant::Debug::CAMERA)
  {
    frc::SmartDashboard::PutNumber("Detected Pixel", cnt);
  }

  if(cnt>=300)
  {
      return true;
  }
  
  return false;
}

bool driveRight = false;
bool driveLeft = false;

bool Camera::drive_Right()
{
    return driveRight;
}

bool Camera::drive_Left()
{
    return driveLeft;
}

bool Camera::drive_direction_right()
{
    /*if(driveRight==true&&driveLeft==true)
    {
        return 3;
    }
    else if(driveRight==true&&driveLeft==false)
    {
        return 2;
    }
    else if(driveRight==false&&driveLeft==true)
    {
        return 1;
    }

    return 0;*/
    //frc::SmartDashboard::PutString("lastData2",lastData);
    int i =0;
    //std::string test = "";
    /*while(QRs[i]!="")
    {
        test=QRs[i];
        i++;
    }*/

    //frc::SmartDashboard::PutString("lastData2",lastData);
    if(lastData=="RIGHT")
    {
        return true;
    }

    return false;
}


void Camera::DetectLine(Mat img, int FrameWidth)
{
    unsigned int cnt_left = 0;
    unsigned int cnt_right = 0;
    unsigned int cnt = 0;

    driveLeft=false;
    driveRight=false;
    
    vector<Point> all_pixels;
    findNonZero(img, all_pixels);

    for (int i = 0; i < all_pixels.size(); i++)
    {
        Point pnt = all_pixels[i];
        if (pnt.x < (FrameWidth / 30))
        {
            cnt_left++;
            if (cnt_left > 50)
            {
                driveLeft = true;
            }
            else
            {
                driveLeft = false;
            }
        }
        else if (pnt.x > (29 * (FrameWidth / 30)))
        {
            cnt_right++;
            if (cnt_right > 50)
            {
                driveRight = true;
            }
            else
            {
                driveRight = false;
            }
        }
        else
        {
            cnt++;
        }
    }

    if(constant::Debug::CAMERA)
    {
        frc::SmartDashboard::PutBoolean("Drive Right",driveRight);
        frc::SmartDashboard::PutBoolean("Drive Left",driveLeft);
    }
}

bool Camera::IsSearchedColorRed()
{
    if(lastColor=="RED")
    {
        return true;
    }

    return false;
}

bool Camera::IsSearchedColorBlue()
{
    if(lastColor=="BLUE")
    {
        return true;
    }

    return false;
}

bool Camera::IsSearchedColorYellow()
{
    if(lastColor=="YELLOW")
    {
        return true;
    }

    return false;
}

bool Camera::ProcessSinglePicture()
{
    Color_detected=false;

    inRange(picture_hsv, m_lower, m_upper, mask); 

    // close
    cv::dilate(mask, mask_new, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    erode(mask_new, mask_new2, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    // remove
    erode(mask_new2, mask_new, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    cv::dilate(mask_new, mask_new2, getStructuringElement(MORPH_RECT, Size(pix, pix)));

    cv::Canny(mask_new2, finish, 25, 75);
    cv::imwrite("/home/pi/Desktop/Image/finish.jpg", finish);

    Color_detected = colorDetected(mask_new2);

    if(Color_detected==true)
    {
        DiferenceToCube = getCountours(finish, FrameWidth);
    }

    if(constant::Debug::CAMERA)
    {
        frc::SmartDashboard::PutNumber("Differenz Cube verarbeitet", DiferenceToCube);
        frc::SmartDashboard::PutNumber("Color detected SearchForCube", Color_detected);
    }

    return Color_detected;
}

void Camera::TakeSinglePicture()
{
    VideoCapture cap(0);
    
    //VideoCapture cap(0);

    FrameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    //SetColorRange(53,90,0,84,0,51); // schwarz
    //SetColorRange(100,179,70,150,10,60); // rot ohne Licht
    //SetColorRange(76,186,155,255,167,255); // rot mit Licht
    /*inputVideo.grab();
    inputVideo.retrieve(img);*/
    cap >> img;
    //cap.read(img);
    //img = cv::imread("/home/pi/Dekstop/libcam/frame1.jpg");
    cv::imwrite("/home/pi/Desktop/Image/testimg.jpg", img);
    cvtColor(img, picture_hsv, COLOR_BGR2HSV);

    DiferenceToCube = 1000;
}

void Camera::SearchforCube()
{
    detectedColor = -1;
    TakeSinglePicture();

    global::CountSearchColor++;

    fstream file;
    file.open("/home/pi/Desktop/QR_Codes.txt", ios_base::out | ios_base::app);

    /*frc::SmartDashboard::PutBoolean("Color Blue detected",false);
    frc::SmartDashboard::PutBoolean("Color Red detected",false);
    frc::SmartDashboard::PutBoolean("Color Yellow detected",false);*/

    for (int color = 0;color < 4; color++)
    {
        SetColorDetection(color);
        
        ProcessSinglePicture();

        switch(color)
        {
            case constant::Camera::BLUE:
                cv::imwrite("/home/pi/Desktop/Image/finishBlue.jpg", finish);
                break;
            
            case constant::Camera::RED:
                cv::imwrite("/home/pi/Desktop/Image/finishRed.jpg", finish);
                break;

            case constant::Camera::YELLOW:
                cv::imwrite("/home/pi/Desktop/Image/finishYellow.jpg", finish);
                break;
            
            case constant::Camera::GREEN:
                cv::imwrite("/home/pi/Desktop/Image/finishGreen.jpg", finish);
                break;
        }
        
        if(Color_detected==true)
        {
            switch (color)
            {
                case constant::Camera::BLUE:
                    file << "B\n";
                    frc::SmartDashboard::PutBoolean("Color Blue detected",Color_detected);
                    break;

                case constant::Camera::RED:

                    file << "R\n";
                    frc::SmartDashboard::PutBoolean("Color Red detected",Color_detected);
                    break;

                case constant::Camera::YELLOW:
                    
                    file << "Y\n";
                    frc::SmartDashboard::PutBoolean("Color Yellow detected",Color_detected);
                    break;

                case constant::Camera::GREEN:

                    file << "G\n";
                    frc::SmartDashboard::PutBoolean("Color Green detected",Color_detected);
                    break;
            }

            detectedColor = color;
            break;
        }
    }
    file.close();
}

void Camera::SetColorDetection(int colorID)
{
    switch (colorID)
        {
            case constant::Camera::BLUE: 
            {
                //Blau
                //hmin = 98, smin = 167, vmin = 25;
                //hmax = 121, smax = 244, vmax = 192;

                //SetColorRange(0,69,0,44,0,22); // Blau alt
                //SetColorRange(18,56,42,114,18,65);
                //SetColorRange(0,55,83,158,25,128);
                SetColorRange(30,69,47,95,23,47);
                // 0,55,83,158,25,128
                break;
            }
            case constant::Camera::RED:
            {
                //Rot
                //hmin = 100, smin = 70, vmin = 10;
                //hmax = 179, smax = 150, vmax = 60;
                //SetColorRange(100,130,67,118,0,57);
                //SetColorRange(86,120,102,174,39,101);
                //SetColorRange(86,128,79,123,0,59);
                //SetColorRange(93,137,90,153,37,75);
                //SetColorRange(93,118,111,208,199,255);
                SetColorRange(hmin_red[global::SelectRed],hmax_red[global::SelectRed],smin_red[global::SelectRed],smax_red[global::SelectRed],vmin_red[global::SelectRed],vmax_red[global::SelectRed]);
                // 93,137,90,153,37,75
                break;
            }
            case constant::Camera::YELLOW:
            {
                //Gelb
                //hmin = 0, smin = 0, vmin = 158;
                //hmax = 84, smax = 93, vmax = 241;

                //SetColorRange(67,128,102,149,28,81); // Gelb alt
                //SetColorRange(74,102,127,197,44,109);
                //SetColorRange(0,0,0,0,0,0);
                //SetColorRange(74,127,118,185,199,255);
                SetColorRange(hmin_yel[global::SelectRed],hmax_yel[global::SelectRed],smin_yel[global::SelectRed],smax_yel[global::SelectRed],vmin_yel[global::SelectRed],vmax_yel[global::SelectRed]);
                break;
            }
            case constant::Camera::GREEN:
            {
                SetColorRange(21,74,109,169,37,93);
                break;
            }

            // GREEN 21,74,109,169,37,93
        }
}

int Camera::GetDetectedColor()
{
    return detectedColor;
}

int Camera::GetLastNumberRead()
{
    return lastNumber;
}

bool Camera::LastNumberEven()
{
    if(lastNumber%2==0)
    {
        return true;
    }

    return false;
}

int Camera::GetLastColorRead()
{
    //lastColor = 0;
    if(lastColor=="RED")
    {
        return constant::Camera::RED;
    }
    else if(lastColor=="BLUE")
    {
        return constant::Camera::BLUE;
    }
    else if(lastColor=="YELLOW")
    {
        return constant::Camera::YELLOW;
    }
    else if(lastColor=="GREEN")
    {
        return constant::Camera::GREEN;
    }
    
    return -1;
}

bool Camera::IsDetectedColorSearched()
{
    //frc::SmartDashboard::PutString("lastColor",lastColor);
    //frc::SmartDashboard::PutNumber("detectedColor",detectedColor);

    if(lastColor=="BLUE"&&detectedColor==0)
    {
        return true;
    }
    else if(lastColor=="RED"&&detectedColor==1)
    {
        return true;
    }
    else if(lastColor=="YELLOW"&&detectedColor==2)
    {
        return true;
    }
    else if(lastColor=="GREEN"&&detectedColor==3)
    {
        return true;
    }
    else if(global::CountSearchColor>30)
    {
        global::CountSearchColor=0;
        return true;
    }

    return false;
}

void Camera::TakePictureForQRCode()
{
    //VideoCapture cap(0);
    lastNumber=-1;
    VideoCapture cap(0);

    FrameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    //SetColorRange(100,130,67,118,0,57); // Rot V2
    SetColorRange(53,90,0,84,0,51); // schwarz
    //SetColorRange(100,179,70,150,10,60); // rot ohne Licht
    //SetColorRange(76,186,155,255,167,255); // rot mit Licht
    /*inputVideo.grab();
    inputVideo.retrieve(img);*/
    cap >> img;
    //cap.read(img);
    cv::imwrite("/home/pi/Desktop/Image/testimg.jpg", img);
    cvtColor(img, picture_hsv, COLOR_BGR2HSV);

    inRange(picture_hsv, m_lower, m_upper, mask); 

    // close
    cv::dilate(mask, mask_new, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    erode(mask_new, mask_new2, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    // remove
    erode(mask_new2, mask_new, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    cv::dilate(mask_new, mask_new2, getStructuringElement(MORPH_RECT, Size(pix, pix)));

    cv::Canny(mask_new2, finish, 25, 75);
    cv::imwrite("/home/pi/Desktop/Image/finish.jpg", finish);

    fstream file;
    /*file.open("/home/pi/Desktop/QR_Codes.txt", ios_base::app | ios_base::in);*/
    file.open("/home/pi/Desktop/QR_Codes.txt", ios_base::out | ios_base::app);

    date = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);
    std::string daten = date.c_str();

    if (daten.length() > 0)
    {
        //frc::SmartDashboard::PutString("QR Code Aktuell", daten);
        /*if (datenOLD == "No Data")
        {*/
            
            rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
            file << daten + "\n";
            lastData=daten;

            if(daten=="RIGHT"||daten=="LEFT")
            {
                lastDirection=daten;
            }
            else if(daten=="31"||daten=="32"||daten=="33")
            {
                if(daten=="31")
                {
                    lastColor="RED";
                    lastNumber=31;
                }
                else if(daten=="32")
                {
                    lastColor="BLUE";
                    lastNumber=32;
                }
                else if(daten=="33")
                {
                    lastColor="YELLOW";
                    lastNumber=33;
                }
                //lastColor=daten;
            }
            else
            {
                //lastNumber = 0; // BUG: keine NUMMER vorhanden

                if(daten=="31"||daten=="32"||daten=="33"||daten=="36"||daten=="38")
                {
                    if(daten=="31")
                    {
                        lastNumber=31;
                    }
                    else if(daten=="32")
                    {
                        lastNumber=32;
                    }
                    else if(daten=="33")
                    {
                        lastNumber=33;
                    }
                    else if(daten=="36")
                    {
                        lastNumber=36;
                    }
                    else if(daten=="38")
                    {
                        lastNumber=38;
                    }
                }
            }
            
            
            if(constant::Debug::CAMERA)
            {
                
                frc::SmartDashboard::PutString("QR Code", daten);
            }
            
            //frc::SmartDashboard::PutString("lastData 1",lastData);
            /*datenOLD = "Data";
        }*/
    }
    else
    {
        if(constant::Debug::CAMERA)
        {
            frc::SmartDashboard::PutString("QR Code", "No Data");
        }
        //datenOLD = "No Data";
    }

    frc::SmartDashboard::PutNumber("lastNumber",lastNumber);

    file.close();

    file.open("/home/pi/Desktop/QR_Codes.txt", ios_base::in);

    int i=0;

    while (file)
    {
        if(i < 10)
        {
            getline(file, QRs[i]);
        }
        i++;    
    }

    file.close();

    if(constant::Debug::CAMERA)
    {
        //frc::SmartDashboard::PutStringArray("QR Saved Array",QRs);
        if (QRs[2] != "")
        {
            //frc::SmartDashboard::PutString("QR Saved", QRs[2]);
        }
        else
        {
            //frc::SmartDashboard::PutString("QR Saved", "No Data");
        }
    }
    
    cv::imwrite("/home/pi/Desktop/Image/mask_new2.jpg", mask_new2);
    //DetectLine(mask_new2,cap.get(CAP_PROP_FRAME_WIDTH));

    DetectLine(mask_new2,FrameWidth);

    if(constant::Debug::CAMERA)
    {
        frc::SmartDashboard::PutNumber("driveRight",driveRight);
        frc::SmartDashboard::PutNumber("driveLeft",driveLeft);
    }
}

bool Camera::FarbeErkannt()
{
    return ColorDetected;
}

/*double Camera::getCountours(Mat mask, int FrameWidth)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;

    findContours(mask, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(0, 255, 0), 5);

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());

        frc::SmartDashboard::PutNumber("Area Farberkennung", area);
       
        if (area > 750)
        {
            float peri = arcLength(contours[i], false);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, false);
            boundRect[i] = boundingRect(conPoly[i]);
            //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 255), 5);
            Point middle;
            middle.x = (boundRect[i].tl().x + (boundRect[i].width / 2));
            middle.y = (boundRect[i].tl().y + (boundRect[i].height / 2));
            //circle(img, middle, 4, Scalar(255, 255, 0), 2);
            double diffCube = (FrameWidth/2) - middle.x;
            return diffCube;
        }
    }

    return 1000;
}*/

double Camera::getCountours(Mat mask, int FrameWidth)
{
    vector<vector<Point>> contours2;
    vector<Vec4i> hierachy;

    findContours(mask, contours2, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(img, contours2, -1, Scalar(0, 255, 0), 5);
    vector<vector<Point>> contours(contours2.size());

    for (int i = 0; i < contours2.size(); i++)
    {
        convexHull(Mat(contours2[i]), contours[i]);
        int area = contourArea(contours[i]);
        
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());

        if(constant::Debug::CAMERA)
        {
            //frc::SmartDashboard::PutNumber("Area Farberkennung", area);
        }
        
        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            boundRect[i] = boundingRect(conPoly[i]);
            //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 0, 255), 5);
            Point middle;
            middle.x = (boundRect[i].tl().x + (boundRect[i].width / 2));
            middle.y = (boundRect[i].tl().y + (boundRect[i].height / 2));
            //circle(img, middle, 4, Scalar(255, 255, 0), 2);
            double diffCube = (FrameWidth/2) - middle.x;

            CubeHigh = boundRect[i].height;
            if(constant::Debug::CAMERA)
            {
                frc::SmartDashboard::PutNumber("Höhe Würfel", boundRect[i].height);
                frc::SmartDashboard::PutNumber("berechneter Weg",0.601915959*DiferenceToCube - 0.0458380785);
            }
            return diffCube;
        }
    }

    return 1000;
}

double Camera::GetDiferenceToCube()
{
    return DiferenceToCube;
}

double Camera::GetCubeHigh()
{
    return CubeHigh;
}

int CountCamera = 0;

void Camera::EnableCamera(bool enable)
{
    CameraEnable=enable;
}

void Camera::ProcessPicture()
{   
    CountCamera++;
    /*
    double hmin = 100, smin = 70, vmin = 10;
    double hmax = 179, smax = 150, vmax = 60;
    */

    VideoCapture cap(0);
    SetColorRange(93,118,111,208,199,255); // Rot V3
    //SetColorRange(86,120,102,174,39,101); // Rot V2
    //SetColorRange(100,179,70,150,10,60); // rot ohne Licht
    //SetColorRange(76,186,155,255,167,255); // rot mit Licht
    //SetColorRange(97,144,113,199,35,115);
    FrameWidth = cap.get(CAP_PROP_FRAME_WIDTH);

    if(constant::Debug::CAMERA)
    {
        frc::SmartDashboard::PutNumber("FrameWidth",FrameWidth);
        frc::SmartDashboard::PutNumber("CountCamera",CountCamera);
    }

    cap >> img;
    //cap.read(img);
    cv::imwrite("/home/pi/Desktop/Image/testimg.jpg", img);
    cvtColor(img, picture_hsv, COLOR_BGR2HSV);

    inRange(picture_hsv, m_lower, m_upper, mask); 

    // close
    cv::dilate(mask, mask_new, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    erode(mask_new, mask_new2, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    // remove
    erode(mask_new2, mask_new, getStructuringElement(MORPH_RECT, Size(pix, pix)));
    cv::dilate(mask_new, mask_new2, getStructuringElement(MORPH_RECT, Size(pix, pix)));

    cv::Canny(mask_new2, finish, 25, 75);
    cv::imwrite("/home/pi/Desktop/Image/finish.jpg", finish);

    /*fstream file;
    file.open("/home/pi/Desktop/QR_Codes.txt", ios_base::app | ios_base::in);*/

    if(DiferenceToCubeCount<COUNT)
    {
        DiferenceToCubeArray[DiferenceToCubeCount]=getCountours(finish, FrameWidth);
        DiferenceToCubeCount++;
        
        if(constant::Debug::CAMERA)
        {
            frc::SmartDashboard::PutNumber("Differenz Cube", DiferenceToCubeArray[DiferenceToCubeCount]);
        }
    }
    else
    {
        CubeAvailable = true;
        DiferenceToCubeCount=0;
        DiferenceToCubeHelp=0;
        int greatest = 0;
        int lowest = 0;

        /*for(int i=0;i<COUNT;i++)
        {
            if(DiferenceToCubeArray[i]<DiferenceToCubeArray[lowest])
            {
                DiferenceToCubeArray[lowest]=DiferenceToCubeArray[i];
            }

            if(DiferenceToCubeArray[i]>DiferenceToCubeArray[greatest])
            {
                DiferenceToCubeArray[greatest]=DiferenceToCubeArray[i];
            }
        }*/

        for(int i=0;i<COUNT;i++)
        {
            /*if(i!=greatest&&i!=lowest)
            {*/
                DiferenceToCubeHelp+=DiferenceToCubeArray[i];
                if(DiferenceToCubeArray[i]==1000)
                {
                    CubeAvailable=false;
                }
            //}
        }

        if(CubeAvailable)
        {
            //DiferenceToCube=DiferenceToCubeHelp/(COUNT-2);
            DiferenceToCube=DiferenceToCubeHelp/(COUNT);
        }
        else
        {
            DiferenceToCube=1000;
        }
        
    }

    ColorDetected = colorDetected(mask_new2);

    if(constant::Debug::CAMERA)
    {
        frc::SmartDashboard::PutNumber("Differenz Cube verarbeitet", DiferenceToCube);
        frc::SmartDashboard::PutNumber("Color detected", ColorDetected);
    }
}

void Camera::Periodic()
{
    if(CameraEnable==true)
    {
        ProcessPicture();
        global::CameraEnabled=true;
    }
    else
    {
        global::CameraEnabled=false;
    }

    if(constant::Debug::CAMERA)
    {
        frc::SmartDashboard::PutString("lastData 3",lastData);
    }
}

void Camera::SetColorRange(double hmin, double hmax, double smin, double smax, double vmin, double vmax)
{
    Scalar lower_a(hmin, smin, vmin);
    Scalar upper_a(hmax, smax, vmax);

    m_upper=upper_a;
    m_lower=lower_a;
}
