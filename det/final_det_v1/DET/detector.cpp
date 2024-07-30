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

float DETECTOR::get_acc(uint8_t device_address, uint8_t axis) {
  Wire.beginTransmission(device_address);
  Wire.write(axis);
  Wire.endTransmission();
  Wire.requestFrom(device_address, 2);
  float acc = 0;
  acc = Wire.read() << 8 | Wire.read();
  acc /= 1671.763;

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


float DETECTOR::calb(uint8_t device_address ,uint8_t axis) {
  float avg_acc = 0;
  float acc=0;
  for (uint8_t i = 0; i < sample; i++) {
    Wire.beginTransmission(device_address);
    Wire.write(axis);
    Wire.endTransmission();
    Wire.requestFrom(device_address, 2);
    acc = Wire.read() << 8 | Wire.read();
    acc /= acc_FC;
    avg_acc += acc;
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
