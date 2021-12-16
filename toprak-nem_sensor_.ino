
#include <ros.h>
#include <std_msgs/UInt8.h>

int sensor_pin = A0;
 
int cikis_degeri ;

ros::NodeHandle nh;
std_msgs::UInt8 topraknem_msg;

ros::Publisher Sensors("SENSORS",&topraknem_msg);
 
void setup() {
 
 nh.initNode();
 nh.advertise(Sensors);
 
}
 
void loop() {
 
cikis_degeri= analogRead(sensor_pin);

 

  topraknem_msg.data = map(cikis_degeri,550,0,0,100);
  Sensors.publish( &topraknem_msg );
  nh.spinOnce();
 
delay(1000);
 
}
