

#include <ros.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25
//define pin
int sensor_pin = A0;

//define variables
int cikis_degeri ;


Adafruit_BMP085 bmp;
ros::NodeHandle nh;
std_msgs::String basinc_msg;

ros::Publisher Sensors("SENSORS",&basinc_msg);
void setup() {
  bmp.begin(); 
  nh.initNode();
  nh.advertise(Sensors);
}
  
void loop() {

    String temperature =  String(bmp.readTemperature());
    String pressure =  String(bmp.readPressure());
    String altitude =  String(bmp.readAltitude());
    String nem = String(analogRead(sensor_pin));
    String karbon = String(analogRead(A3));
    String alldatas = temperature + "," + pressure + "," + altitude +","+ nem+","+ karbon;
     
  
    basinc_msg.data = alldatas.c_str();
    Sensors.publish( &basinc_msg );
    nh.spinOnce();
    
    delay(500);
}
