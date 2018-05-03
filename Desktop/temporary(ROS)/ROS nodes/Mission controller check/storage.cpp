#include "dji_sdk/picture.h"  //To include the msg created
#include <std_msgs/Float32MultiArray.h> //Just in case we also add the multiarray part
#include <std_msgs/MultiArrayDimension.h>
#include "ros/ros.h"
//#include "dji_sdk_demo/storage3.h"
#include <time.h>
#include "std_msgs/String.h"
#include <stdlib.h>
#include <sstream>
#include <tinyxml.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

 int i = 0;

void pictureCallback(const dji_sdk::picture::ConstPtr& msg)
{

//We just enter when we get a message
    sensor_msgs::NavSatFix current_gps = msg->gps_position;
    sensor_msgs::Imu current_imu = msg->imu;
    geometry_msgs::Quaternion current_atti = msg->Attitude;
    geometry_msgs::Vector3Stamped current_velocity = msg->velocity;
    ros::Time Time_stamp = msg->gps_position.header.stamp;
    
    //That is one way to do it
    std::string gps_position_x = boost::lexical_cast<std::string>(current_gps.longitude);

 //First we just check if the writer works (not collected data) and then we check the rest
//We don't use any function or anything like this
   
    //A way to convert integers into strings
    char buf[256];
    snprintf(buf, sizeof(buf), "%d", i); //Later we can with i as an integer
    
    std::string xml="/home/nico/Desktop/test.xml";
    TiXmlDocument doc(xml.c_str()); //We open an existing document
    if (doc.LoadFile()) {
        TiXmlHandle docHandle(&doc);
        TiXmlElement* fileLog = docHandle.FirstChild("FileLog").ToElement();
        
        if (fileLog) { //If the element filelog exists, we add a new one
            TiXmlElement recording("picture_taken");
            
            recording.SetAttribute("gps_position", gps_position_x); //Check if there is a problem and we have to do it with other "instructions"
            
            fileLog->InsertEndChild(recording);
        }
    }
    
    else std::cout << "error loading file" << std::endl;
    
    if(doc.SaveFile(xml.c_str())){
        std::cout << "file saved succesfully.\n";
        
    }
    else std::cout << "error saving file" << std::endl;
    
    

    i++;
   
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listen");

  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe("picture_taken", 1000, pictureCallback);
  ros::spin();

  return 0;
}


