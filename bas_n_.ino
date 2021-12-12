#include <ros.h>

#include <SFE_BMP180.h>
#include <Wire.h>
#include <std_msgs/UInt8.h>
ros::NodeHandle nh;
std_msgs::UInt8 basinc_msg;

ros::Publisher Sensors("SENSORS",&basinc_msg);


SFE_BMP180 bmp180;  // bmp180 adında bir sensör nesnesi oluştur
void setup() {
  Serial.begin(9600);
  
  // bmp 180 ile haberleşme sağlandı mı kontrol et
  bool basarili = bmp180.begin();
  if (basarili) {
    Serial.println("BMP180 başlatıldı.");
  }
  nh.initNode();
  nh.advertise(Sensors);
}
void loop() {
  char durum;  // Sensörden okunan durum
  double T, P;  // Sıcaklık ve basınç değişkenleri
  bool basarili = false;  // Sensör çalışıyor mu bilgisi değişkeni
  durum = bmp180.startTemperature();
  if (durum != 0) {
    delay(1000);
    durum = bmp180.getTemperature(T);
    if (durum != 0) {
      durum = bmp180.startPressure(3);
      if (durum != 0) {
        delay(durum);
        durum = bmp180.getPressure(P, T);
        if (durum != 0) {
          Serial.print("Basınç: ");
          Serial.print(P);
          Serial.println(" hPa");
          Serial.print("Sıcaklık: ");
          Serial.print(T);
          Serial.println(" C");

          
        }
      }
    }
  }
  basinc_msg.data = P;
  Sensors.publish( &basinc_msg );
  nh.spinOnce();
}
