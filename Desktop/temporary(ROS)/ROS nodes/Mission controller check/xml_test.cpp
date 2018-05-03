#include "dji_sdk/test.h"  //To include the msg created
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

void pictureCallback(const dji_sdk::test::ConstPtr& msg)
{

//We just enter when we get a message
   

 //First we just check if the writer works (not collected data) and then we check the rest
//We don't use any function or anything like this
   
    //A way to convert integers into strings
    char buf[256];
    snprintf(buf, sizeof(buf), "%d", i); //Later we can with i as an integer
    
    //Later we can also try this way. It is more elegant
   // std::string gps_position_x = boost::lexical_cast<std::string>(current_gps.longitude);
    
    std::string xml="/home/nico/Desktop/test.xml";
    TiXmlDocument doc(xml.c_str()); //We open an existing document
    if (doc.LoadFile()) {
        TiXmlHandle docHandle(&doc);
        TiXmlElement* fileLog = docHandle.FirstChild("FileLog").ToElement();
        
        if (fileLog) { //If the element filelog exists, we add a new one
            TiXmlElement recording("recording");
            
            recording.SetAttribute("id", i); //Check if there is a problem and we have to do it with other "instructions"
            
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

  
  ros::Subscriber sub = n.subscribe("test", 1000, pictureCallback);
  ros::spin();

  return 0;
}


