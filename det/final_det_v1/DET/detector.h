#include "Arduino.h"
#include <Wire.h>
#include <EEPROM.h>
//sensor adrees
#define MPU1 0x68
#define MPU2 0x69
#define pow_mangment 0x6B
#define gyro_config 0x1B
#define acce_config 0x1C
#define accx_add 0x3B
#define accy_add 0x3D 
#define accz_add 0x3F

#define acc_FC 1671.763
// pins name
#define buz A1
#define contac 4
#define open_contac 2
#define close_contac 3
#define BIG_BUZZ A0
#define SMALL_LED 5
#define RED_LED 7

#define sample 100


#define threshold 0.8
#define edge_contac_value 500
#define bytes_req 2
#define serial_baudrate 9600

#define DEBUG 1

class DETECTOR {


public:

  bool is_open = false;

  float accx = 0, accx1 = 0;
  float accy = 0, accy1 = 0;
  float accz = 0, accz1 = 0;

  float accx_b = 0, accx1_b = 0;
  float accy_b = 0, accy1_b = 0;
  float accz_b = 0, accz1_b = 0;

  void int_pins();
  void int_sensor();

  void Alarm_off();
  void print_value();
  void alarm();

  float calb(uint8_t device_address, uint8_t axis);
  float get_acc(uint8_t device_address, uint8_t axis);
};
