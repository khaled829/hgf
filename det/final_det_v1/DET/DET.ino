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
int led_time = 0;
void setup() {
  cont = digitalRead(contac);

  det.int_pins();
  delay(100);
  det.int_sensor();

  Serial.println("calb");

  det.accx_b = det.calb(MPU1, accx_add);
  det.accy_b = det.calb(MPU1, accy_add);
  det.accz_b = det.calb(MPU1, accz_add);

  det.accx1_b = det.calb(MPU2, accx_add);
  det.accy1_b = det.calb(MPU2, accy_add);
  det.accz1_b = det.calb(MPU2, accz_add);


  Serial.println(det.accx_b);
  Serial.println(det.accx1_b);

  Serial.println(det.accy_b);
  Serial.println(det.accy1_b);

  Serial.println(det.accz_b);
  Serial.println(det.accz1_b);


  attachInterrupt(digitalPinToInterrupt(open_contac), signal_open, RISING);
  attachInterrupt(digitalPinToInterrupt(close_contac), signal_close, RISING);
  digitalWrite(buz, HIGH);

  delay(1000);
  digitalWrite(buz, LOW);


  Serial.println("Start");
  delay(100);
}


void loop() {
  if (millis() - led_time > 1000) {
    led_time = millis();
    digitalWrite(SMALL_LED, !digitalRead(SMALL_LED));
  }

  cont = digitalRead(contac);
  delay(10);

  if (det.is_open == false and cont) {

    det.accx = det.get_acc(MPU1, accx_add) - det.accx_b;
    det.accx1 = det.get_acc(MPU2, accx_add) - det.accx1_b;

    det.accy = det.get_acc(MPU1, accy_add) - det.accy_b;
    det.accy1 = det.get_acc(MPU2, accy_add) - det.accy1_b;

    det.accz = det.get_acc(MPU1, accz_add) - det.accz_b;
    det.accz1 = det.get_acc(MPU2, accz_add) - det.accz1_b;


    Serial.print(det.accx);
    Serial.print("\t");
    Serial.println(det.accx1);
    if (det.accx > threshold or det.accx < -threshold) {
      det.alarm();
    }


    if (det.accx1 > threshold or det.accx1 < -threshold) {
      det.alarm();
    }
  }


  if (!cont or det.is_open == true) {
    det.Alarm_off();
    delay(1000);
    Serial.println("off");
  }

  if (!cont) {
    digitalWrite(RED_LED, LOW);
  }
}