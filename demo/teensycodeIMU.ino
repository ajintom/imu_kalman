#include "MPU9250.h"
#include "_wip_vector.h"
#include "_wip_quaternion.h"
#include "_wip_mahony.h"
#include <math.h>

const int LED = 0;
const int LED1= 13;
MPU9250 myIMU;
_wip_::Vector omega;
_wip_::Vector va;
_wip_::Vector vm;
_wip_::MahonyFilter f(1000);
int now, before;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);

  // boot up notification
  digitalWrite(LED1, HIGH); delay(1000); digitalWrite(LED1, LOW); delay(1000);

  Wire.begin();

  // if you ever want to recalibrate the bias offsets in the MPU EEPROM,
  // uncomment the next line, and run the sketch with the device sitting on a
  // table with the sensor integrated circuit level with the table and facing up

  // myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

  myIMU.initMPU9250();
  //
  myIMU.initAK8963(myIMU.magCalibration);

  myIMU.getGres();
  // myIMU.getAres();
  // myIMU.getMres();

  // get from manual calibration
  // myIMU.magbias[0] = +470.;
  // myIMU.magbias[1] = +120.;
  // myIMU.magbias[2] = +125.;

  f.setk_P(0.3);
  f.setk_I(0.0);
  f.setk_a(1.0);
  f.setk_m(0.1);

  Serial.begin(115200);
}

// wrapper functions for setting filter parameters with OSC
//void setk_Pwrapper(OSCMessage &msg)
//{
//  if (msg.isFloat(0)) f.setk_P(msg.getFloat(0));
//  else if (msg.isInt(0)) f.setk_P((float)msg.getInt(0)/127.0f);
//}
//
//void setk_Iwrapper(OSCMessage &msg)
//{
//  if (msg.isFloat(0)) f.setk_I(msg.getFloat(0));
//  else if (msg.isInt(0)) f.setk_I((float)msg.getInt(0)/127.0f);
//}
//
//void setk_awrapper(OSCMessage &msg)
//{
//  if (msg.isFloat(0)) f.setk_a(msg.getFloat(0));
//  else if (msg.isInt(0)) f.setk_a((float)msg.getInt(0)/127.0f);
//}
//
//void setk_mwrapper(OSCMessage &msg)
//{
//  if (msg.isFloat(0)) f.setk_m(msg.getFloat(0));
//  else if (msg.isInt(0)) f.setk_m((float)msg.getInt(0)/127.0f);
//}

void loop()
{

    if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    {
      // when there is new sensor data, read it
      digitalWrite(13, HIGH);
      myIMU.readGyroData(myIMU.gyroCount);
      // myIMU.getGres();
      omega.x = (float)myIMU.gyroCount[0] * myIMU.gRes * DEG_TO_RAD;
      omega.y = (float)myIMU.gyroCount[1] * myIMU.gRes * DEG_TO_RAD;
      omega.z = (float)myIMU.gyroCount[2] * myIMU.gRes * DEG_TO_RAD;
//      bndl.add("/g").add(omega.x).add(omega.y).add(omega.z);

      myIMU.readAccelData(myIMU.accelCount);
      // // myIMU.getAres();
      va.x = (float)myIMU.accelCount[0];
      va.y = (float)myIMU.accelCount[1];
      va.z = (float)myIMU.accelCount[2];
//      bndl.add("/a").add(va.x).add(va.y).add(va.z);

      myIMU.readMagData(myIMU.magCount);
      // myIMU.getMres();
      vm.x = (float)myIMU.magCount[0];
      vm.y = (float)myIMU.magCount[1];
      vm.z = (float)myIMU.magCount[2];
//      bndl.add("/m").add(vm.x).add(vm.y).add(vm.z);

      digitalWrite(13, LOW);
    }
    now = micros();
    float period = (float)(now - before) / 1000000.0f;
    const _wip_::Quaternion& q = f.filter(omega, va, vm, period);
    before = now;



//      Serial.print(va.x);
//      Serial.print("|");
//      Serial.print(va.y);
//      Serial.print("|");
//      Serial.print(va.z);
//      Serial.print("|");
//      
//      Serial.print(omega.x);
//      Serial.print("|");
//      Serial.print(omega.y);
//      Serial.print("|");
//      Serial.print(omega.z);
//      Serial.print("|");
//      
//      Serial.print(vm.x);
//      Serial.print("|");
//      Serial.print(vm.y);
//      Serial.print("|");
//      Serial.print(vm.z);
//      Serial.println("|");

float roll, pitch, yaw;

  roll  = atan2(2*q.v.y*q.w - 2*q.v.x*q.v.z, 1 - 2*q.v.y*q.v.y - 2*q.v.z*q.v.z);
  pitch = atan2(2*q.v.x*q.w - 2*q.v.y*q.v.z, 1 - 2*q.v.x*q.v.x - 2*q.v.z*q.v.z);
  yaw   = 2.0 * asin(2*q.v.x*q.v.y + 2*q.v.z*q.w);

    
    Serial.print(va.x);
    Serial.print("?");
    
    Serial.print(q.w);
    Serial.print("?");
    Serial.print(q.v.x);
    Serial.print("?");
    Serial.print(q.v.y);
    Serial.print("?");
    Serial.print(q.v.z);
    Serial.print("?");

    Serial.print(roll);
    Serial.print("?");
    Serial.print(pitch);
    Serial.print("?");
    Serial.print(yaw);
    Serial.println("?");

}
