#include "Arduino.h"
#include "detector.h"

void DETECTOR::int_pins() {
  Serial.begin(serial_baudrate);

  pinMode(buz, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(contac, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  digitalWrite(buz, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  Serial.println("start");
  delay(1000);
  
}


void DETECTOR::int_sensor() {
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

  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0b00000000);
  Wire.endTransmission();


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
  for (int i = 0; i < 18; i++) {
    if (contac == HIGH) {
      digitalWrite(buz, LOW);
      break;
    }

    if (is_open == true) {
      digitalWrite(buz, LOW);
      break;
    }

    //Serial.println(i);
    digitalWrite(13, HIGH);
    digitalWrite(buz, HIGH);
    digitalWrite(8, HIGH);
    delay(3000);
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);
    digitalWrite(buz, HIGH);
    delay(500);
  }
}

void DETECTOR::Alarm_off() {
  digitalWrite(buz, LOW);
  //    digitalWrite(8,LOW);
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
