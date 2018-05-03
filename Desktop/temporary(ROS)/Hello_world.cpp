#include "dji_sdk/path.h"  //To include the msg created
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



void pictureCallback(const dji_sdk::path::ConstPtr& msg)
{

//We just enter when we get a message
   

 //First we just check if the writer works (not collected data) and then we check the rest
//We don't use any function or anything like this
    
    std::string xml="/home/nico/Desktop/test.xml";
    TiXmlDocument doc(xml.c_str()); //We open an existing document
    if (doc.LoadFile()) {
        TiXmlHandle docHandle(&doc);
        TiXmlElement* fileLog = docHandle.FirstChild("FileLog").ToElement();
        
        if (fileLog) { //If the element filelog exists, we add a new one
            TiXmlElement recording("recording");
            
            recording.SetAttribute("id", 4);
            
            fileLog->InsertEndChild(recording);
        }
    }
    
    else std::cout << "error loading file" << std::endl;
    
    if(doc.SaveFile(xml.c_str())){
        std::cout << "file saved succesfully.\n";
        
    }
    else std::cout << "error saving file" << std::endl;
    
    
    //if(loadXML() == FAILURE)
       // return 1; //It is a void we don't return anything
    
   
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listen");

  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe("path_defined", 1000, pictureCallback);
  ros::spin();

  return 0;
}


