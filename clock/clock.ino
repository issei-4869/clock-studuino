#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <MMA8653.h>
#include <MPU6050.h>
#include <IRremoteForStuduino.h>
#include <ColorSensor.h>
#include "Studuino.h"

Studuino board;

void leap_year_check(void);
int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int day[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

int year;
unsigned long time_1;
unsigned long time_2;
unsigned long s;
unsigned long m;
unsigned long m_2;
unsigned long h;
unsigned long h_2;
unsigned long h_3;
unsigned long d;
unsigned long d_2;
unsigned long d_3;
unsigned long mo;
unsigned long mo_2;
unsigned long mo_3;
unsigned long mo_4;
unsigned long mo_5;
unsigned long g_1;
unsigned long g_2;

unsigned long timee;
unsigned long s_c;
unsigned long m_c;
unsigned long h_c_1;
unsigned long h_c_2;
unsigned long h_c_3;
unsigned long d_c;
void setup() {
  board.InitSensorPort(PORT_A1, PIDLED);
  board.InitSensorPort(PORT_A2, PIDLED);
  Serial.begin(9600);
  year = 2020; //西暦
  mo = 2; //何月か
  mo_3 = month[mo];
  mo_5 = mo;
  leap_year_check();  //閏年か
  d_3 = day[29]; //何日か
  d_c = d_3 * 86400; // 日を秒に変換
  h_c_1 = 9 * 3600; //--------------|
  h_c_2 = 9 * 3600; //時間を秒に変換|
  h_c_3 = 5 * 3600; //--------------|
  m_c = 59 * 60; // 分を秒に変換
  s_c = 50; //秒を入れる
  timee = d_c + h_c_1 + h_c_2 + h_c_3 + m_c + s_c; //現在時刻の合計の秒
  timee = timee * 1000;
  mo_4 = mo_3 + 1;
  time_2 = 86400000 * mo_4;
}

void loop() {

  time_1 = millis();
  time_1 = time_1 + timee;
  if (mo == mo_5) {
    if (g_1 == 1) {
      mo = mo + 1;
      timee = timee + 86400000;
      month[mo];
      leap_year_check();
    }
  }
  if (mo == mo_5 + 1) {
    if (g_1 == 2) {
      mo = mo + 1;
      month[mo];
      leap_year_check();
    }
  }
  if (mo == 13) {
    mo = 1;
    year = year + 1;
    leap_year_check();
  }
  g_1 = time_1 / time_2;
  g_2 = time_1 % time_2;
  d = g_2 / 86400000;
  d_2 = g_2 % 86400000;
  h = d_2 / 3600000; //何時間経過しているか
  h_2 = d_2 % 3600000; //余り
  m = h_2 / 60000; //何分経過しているか
  m_2 = h_2 % 60000; //余り　＝　何秒経過しているか
  s = m_2 / 1000;
  Serial.print(mo);
  Serial.print("月");
  Serial.print(d);
  Serial.print("日");
  Serial.print(h);
  Serial.print("時");
  Serial.print(m);
  Serial.print("分");
  Serial.print(s);
  Serial.println("秒");
  delay(1000);
}

void leap_year_check() { //閏年チェックプログラム
  if (mo == 2) {
    if (year % 100 == 0) {
      mo_3 = 29;
    } else if (year % 4 == 0 && year % 100 != 0) {
      mo_3 = 29;
    }
  }
}
