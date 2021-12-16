

#include <ros.h>
#include <std_msgs/UInt8.h>


const int ldrPin = A0;  //the number of the LDR pin

ros::NodeHandle nh;
std_msgs::UInt8 ldr_msg;

ros::Publisher Sensors("SENSORS",&ldr_msg);

void setup() {

  
  
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
   nh.initNode();
  nh.advertise(Sensors);
}

void loop() {

  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

 
  
  ldr_msg.data = ldrStatus;
  Sensors.publish( &ldr_msg );
  nh.spinOnce();
}
