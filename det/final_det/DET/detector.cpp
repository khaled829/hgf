#include "Arduino.h"
#include "detector.h"

void DETECTOR::int_pins() {
  Serial.begin(serial_baudrate);

  pinMode(buz, OUTPUT);
  pinMode(BIG_BUZZ, OUTPUT);
  pinMode(SMALL_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);


  pinMode(contac, INPUT);
  pinMode(open_contac, INPUT);
  pinMode(close_contac, INPUT);

  digitalWrite(buz, HIGH);


  Serial.println("start");
  delay(1000);
  digitalWrite(buz, LOW);
}


void DETECTOR::int_sensor() {

 
 
  Serial.println("1");
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();
Serial.println("2");

   Wire.beginTransmission(0x69);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x69);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x69);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();
  digitalWrite(buz, LOW);
Serial.println("3");
}

void DETECTOR::GetMpuValue1() {
  
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 2);

  accelX = Wire.read() << 8 | Wire.read();
  accelX /= 1671.763;
  accelX -= accelx_bias;
}

void DETECTOR::GetMpuValue2() {

  Wire.beginTransmission(0x69);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x69, 2);
  aceelX1 = Wire.read() << 8 | Wire.read();
  aceelX1 /= acc_FC;
  aceelX1 -= accelx1_bias;
}
void DETECTOR::alarm() {
  for (int i = 0; i < 6; i++) {
    if (contac == HIGH) {
      digitalWrite(buz, LOW);
      digitalWrite(BIG_BUZZ, LOW);

      break;
    }

    if (is_open == true) {
      digitalWrite(BIG_BUZZ, LOW);
      digitalWrite(buz, HIGH);
      digitalWrite(RED_LED, HIGH);

      break;
    }

    //Serial.println(i);
    digitalWrite(BIG_BUZZ, HIGH);
    digitalWrite(buz, HIGH);
    digitalWrite(RED_LED, HIGH);

    delay(1500);
    digitalWrite(BIG_BUZZ, LOW);
    digitalWrite(buz, HIGH);
    digitalWrite(RED_LED, LOW);
    delay(1000);
  }
  digitalWrite(buz, HIGH);
  digitalWrite(RED_LED, HIGH);
}

void DETECTOR::Alarm_off() {
  digitalWrite(buz, LOW);
  digitalWrite(BIG_BUZZ, LOW);
  // digitalWrite(RED_LED, LOW);


}


float DETECTOR::calb(uint8_t MPU) {
  float avg_acc = 0;
  for (uint8_t i = 0; i < sample; i++) {
    Wire.beginTransmission(MPU);
    Wire.write(acc_value_add);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 2);
    aceelX1 = Wire.read() << 8 | Wire.read();
    aceelX1 /= acc_FC;
    avg_acc += aceelX1;
    delay(15);
  }

  return avg_acc / sample;
}



void DETECTOR::print_value() {
  // Serial.print("mpu1 = ");
  // Serial.print(det.accelX);
  // Serial.print("  mpu2 = ");
  // Serial.println(det.aceelX1);
  // Serial.println();
  // Serial.println();
  // Serial.println();
  // if a first sensor value out the range start alarm
}
