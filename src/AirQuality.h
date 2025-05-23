#ifndef _AIRQUALITY_H
#define _AIRQUALITY_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
// #include <WiFiClientSecureBearSSL.h>
#include <WiFiClientSecure.h>
#include <ArduinoUZlib.h>
#pragma once
// #define DEBUG // 调试用

class AirQuality
{
public:
  AirQuality();

  void config(String API_Host, String Token, String location, String lang);
  bool get();
  String getServerCode();
  String getLastUpdate();
  int getAqi();
  String getCategory();
  int getPm10();
  int getPm2p5();
  int getNo2();
  int getSo2();
  float getCo();
  int getO3();

private:
  String _reqToken;    // 私钥
  String _reqLocation; // 位置
  String _reqHost;
  String _reqLang; // 语言

  const char *_host = _reqHost.c_str(); // 服务器地址
  const int httpsPort = 443;

  void _parseNowJson(String payload); // 解析json信息

  String _response_code = "no_init";   // API状态码
  String _last_update_str = "no_init"; // 当前API最近更新时间
  int _now_aqi_int = 999;             // 实况温度
  String _now_category_str = "no_init";    // 实况空气质量类别
  int _now_pm10_int = 999;              // 实况pm10
  int _now_pm2p5_int = 999;            // 实况pm2.5
  int _now_no2_int = 999;              // 实况no2
  int _now_so2_int = 999;        // 实况so2
  float _now_co_float = 999;     // 实况co
  int _now_o3_int = 999;          // 实况o3
};

#endif
