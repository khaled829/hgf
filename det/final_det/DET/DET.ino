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
int led_time=0;
void setup() {
  cont = digitalRead(contac);

  det.int_pins();
  delay(100);
  det.int_sensor();

  Serial.println("calb");
  det.accelx_bias = det.calb(MPU1);
  det.accelx1_bias = det.calb(MPU2);
  Serial.println(det.accelx_bias);
  Serial.println(det.accelx1_bias);

  attachInterrupt(digitalPinToInterrupt(open_contac), signal_open, RISING);
  attachInterrupt(digitalPinToInterrupt(close_contac), signal_close, RISING);
    digitalWrite(buz, HIGH);

  delay(1000);
  digitalWrite(buz, LOW);


  Serial.println("Start");
  delay(100);
}


void loop() {
if(millis()-led_time>1000){
  led_time=millis();
  digitalWrite(SMALL_LED, !digitalRead(SMALL_LED));
}

  cont = digitalRead(contac);
  delay(10);

  if (det.is_open == false and cont) {
    det.GetMpuValue1();
    det.GetMpuValue2();
Serial.print(det.accelX);
Serial.print( "\t");
Serial.println(det.aceelX1);
    if (det.accelX > threshold or det.accelX < -threshold) {
      det.alarm();
    }


    if (det.aceelX1 > threshold or det.aceelX1 < -threshold) { det.alarm(); }
  }


  if (!cont or det.is_open == true) {
    det.Alarm_off();
    delay(1000);
    Serial.println("off");
  }

  if(!cont){
    digitalWrite(RED_LED,LOW);
      
  }








}