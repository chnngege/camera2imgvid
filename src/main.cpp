#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time_camera.h>
#include <xml_para.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Mat Frame;
typedef struct {
  double frame_width;
  double frame_height;
  double fps;
}struct_vid_para;
struct_vid_para vid_para;

typedef struct{
  int img_time_interval;
  int vid_time_interval;
  int vid_duration;
  int video_i;
  int img_i;
  double fps;
  int fps_enable;
}struct_img_vid_xml;
struct_img_vid_xml img_vid_xml;

const int vid_time_interrupt = 5;  //5s time interrupt

bool video_open = 0;               //the flag to save video 

cv::VideoWriter video_writer;      //global val to write a video

int xml_para[2][5] = {60, 0, 0, 0, 0, 10, 0, 30, 0, 300};//default value 

/***************************************************************************************************
 * Input: none  
 * Return: none
 * Description: get parameters from .xml
****************************************************************************************************/
void read_xml_init()
{
  //could not load the xml file
  if(readXmlFile(xml_para) < 0)
  {
    writeXmlFile(xml_para);//default para
    readXmlFile(xml_para);//load xml file again
  }
   
  img_vid_xml.img_time_interval = xml_para[0][0];
  img_vid_xml.vid_time_interval = xml_para[1][0];
  img_vid_xml.video_i = xml_para[1][1] + 1;
  img_vid_xml.img_i = xml_para[0][1] + 1;
  img_vid_xml.vid_duration = xml_para[1][4];
  img_vid_xml.fps_enable = xml_para[1][3];
  img_vid_xml.fps = xml_para[1][2];
}

/***************************************************************************************************
 * Input: none  
 * Return: none
 * Description: save current number of image & video
****************************************************************************************************/
void write_xml_init()
{
  xml_para[1][1] = img_vid_xml.video_i - 1;
  xml_para[0][1] = img_vid_xml.img_i - 1;
}

/***************************************************************************************************
 * Input: none  
 * Return: none
 * Description: generate images from camera
****************************************************************************************************/
void Camera_to_img()
{
  char* image_name; 
  string defaultPath = "../../data/img-";
  
  cout << "Camera_to_images:  " << img_vid_xml.img_i << endl;
  
  //get syetem time
  tm* curenttime = Get_systemTime();//get system time
                
  //get the data of the folder
  char folder_time[20];
  sprintf(folder_time, "%2d-%02d-%02d", curenttime->tm_year, curenttime->tm_mon, curenttime->tm_mday);
  string folderPath = defaultPath + folder_time; 

  //generate folder using system command
  string command = "mkdir -p " + folderPath;  
  system(command.c_str());
  
  //generate path to save the ?.jpg
  image_name = (char*)folderPath.data();
  sprintf(image_name, "%s%s%d%s", image_name,"/img", img_vid_xml.img_i++, ".jpg");
  
  //write an image
  imwrite( image_name, Frame);
  
  //save parameters to .xml
  write_xml_init();
  writeXmlFile(xml_para);

  //retiming
  add_timer(img_vid_xml.img_time_interval, Camera_to_img);  
}

/***************************************************************************************************
 * Input: none  
 * Return: none
 * Description: timing
****************************************************************************************************/
void videocount()
{
  static unsigned int count_frame = 0;
  count_frame++;
                                                                                                                                                                                                                                                                                    
  if(count_frame <= img_vid_xml.vid_duration / vid_time_interrupt)
  {
    video_open = 1;
    add_timer(vid_time_interrupt, videocount);
  }
  else
  {
    video_open = 0;
    count_frame = 0;
    img_vid_xml.video_i++;
    write_xml_init();
    writeXmlFile(xml_para);
    add_timer(img_vid_xml.vid_time_interval, videocount);
    cout << "Camera_to_videos:  "  << img_vid_xml.video_i - 1 << "     finished" << endl;
  }
}

/***************************************************************************************************
 * Input: none  
 * Return: none
 * Description: "img_vid_xml.video_i == last_video_i"means that the video should continue to be saved
 *              "img_vid_xml.video_i == last_video_i"means that a new video should be saved
****************************************************************************************************/
void Camera_to_avi()
{
  char* avi_name;
  string defaultPath = "../../data/vid-";
  static int last_video_i = 0;
  
  if(img_vid_xml.video_i != last_video_i)
  {
    cout << "Camera_to_videos:  "  << img_vid_xml.video_i << "     start" << endl;
    
    last_video_i = img_vid_xml.video_i;   
    
    //get syetem time
    tm* curenttime = Get_systemTime();
  
    //get the data of the folder
    char folder_time[20];
    sprintf(folder_time, "%2d-%02d-%02d", curenttime->tm_year, curenttime->tm_mon, curenttime->tm_mday);
    string folderPath = defaultPath + folder_time; 
    
    //generate folder using system command
    string command = "mkdir -p " + folderPath;  
    system(command.c_str());
    
    //generate path to save the ?.avi
    avi_name = (char*)folderPath.data();
    sprintf(avi_name, "%s%s%d%s",avi_name, "/vid", img_vid_xml.video_i, ".avi");
    cv::Size frameSize(static_cast<int>(vid_para.frame_width),static_cast<int>(vid_para.frame_height));
    cv::VideoWriter writer(avi_name,CV_FOURCC('M','J','P','G'),vid_para.fps,frameSize,true); 
    
    //to global variables
    video_writer = writer;
  } 
  
  //write a video
  video_writer.write(Frame);
  
}

int main()
{
    //the signal of time interrupt
    signal(SIGALRM, tick);
    
    // 1s heart
    alarm(1); 
    
    //open camera & get paras from camera
    VideoCapture capture(0);
    vid_para.frame_width  = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    vid_para.frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    
    //get paras from xml file
    read_xml_init(); 
    
    //time interrupt
    add_timer(img_vid_xml.img_time_interval, Camera_to_img);
    add_timer(img_vid_xml.vid_time_interval, videocount);
    
    bool set_fps = true;
    double time_frame;
    
    while (true)
    {
      
	if(set_fps) time_frame = (double)cv::getTickCount();
	  
	if (capture.isOpened())
	{
	    capture >> Frame;
	    //set the value of fps 
	    if(set_fps)
	    {
		set_fps = false;
		if(img_vid_xml.fps_enable)
		{
		  time_frame = ((double)getTickCount() - time_frame) / getTickFrequency();
		  vid_para.fps = 1.0 / time_frame;
		  cout << "auto fps:  " << vid_para.fps << endl << endl;
		}
		else
		{
		  vid_para.fps = img_vid_xml.fps;
		  cout << "set fps:  " << vid_para.fps << endl << endl;
		}
	    }	    
	}
	else
	  return -1;
	
	//save video
	if(video_open)
	{
	  Camera_to_avi();
	}
    }
    
    return 0;
}