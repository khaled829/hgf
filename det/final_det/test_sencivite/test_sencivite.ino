#include "detector.h"



DETECTOR det;

/////interupts////
void signal_open();
void signal_close();

void signal_open() {

  det.Alarm_off();
  det.is_open = true;
  Serial.println("open");
}

void signal_close() {
  det.is_open = false;
  Serial.println("close");
}

////interupts////


uint8_t counter = 0;

bool cont = 0;

void setup() {
  cont = digitalRead(contac);

  det.int_pins();
  det.int_sensor();

  Serial.println("calb");
  det.accelx_bias = det.calb(MPU1);
  det.accelx1_bias = det.calb(MPU2);
  Serial.println(det.accelx_bias);
  Serial.println(det.accelx1_bias);

  attachInterrupt(digitalPinToInterrupt(open_contac), signal_open, RISING);
  attachInterrupt(digitalPinToInterrupt(close_contac), signal_close, RISING);

  delay(1000);
  Serial.println("Start");
  delay(100);
}

float last_res = 0;
 
void loop() {

  det.GetMpuValue2();
   if(det.aceelX1<0){
     det.aceelX1=-det.aceelX1;
   }
   if (det.aceelX1 > last_res) {
     last_res=det.aceelX1;
     Serial.println(last_res);
   }
delay(4);
}
