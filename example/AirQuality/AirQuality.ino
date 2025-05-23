#include <ESP32_Heweather.h>

const char *ssid = "SSID";     // WiFi名称
const char *passwd = "PASSWORD"; // WiFi密码

String Token = "********1f7c4e63a03dcb2ec0af98bc"; // api-key
String Location = "10119****";                     //
String API_Host = "********gg.re.qweatherapi.com";
String Lang = "en"; // 语言 英文-en/中文-zh
float ROUND = 1.5;  // 更新间隔<分钟>

AirQuality airQuality;

void setup()
{
  Serial.begin(115200);
  Serial.println("");

  ConnectWiFi();                                      // 连接WiFi
  airQuality.config(API_Host, Token, Location, Lang); // 配置请求信息
}

void loop()
{
  if (airQuality.get())
  { // 获取天气更新
    Serial.println(F("======Weahter Now Info======"));
    Serial.print("Server Response: ");
    Serial.println(airQuality.getServerCode()); // 获取API状态码
    Serial.print(F("Last Update: "));
    Serial.println(airQuality.getLastUpdate()); // 获取服务器更新天气信息时间
    Serial.print(F("Aqi: "));
    Serial.println(airQuality.getAqi()); // 获取实况Aqi
    Serial.print(F("Category: "));
    Serial.println(airQuality.getCategory()); // 获取实况Category
    Serial.print(F("Pm10: "));
    Serial.println(airQuality.getPm10()); // 获取实况Pm10
    Serial.print(F("Pm2.5: "));
    Serial.println(airQuality.getPm2p5()); // 获取实况Pm2p5
    Serial.print(F("No2: "));
    Serial.println(airQuality.getNo2()); // 获取实况No2
    Serial.print(F("So2: "));
    Serial.println(airQuality.getSo2()); // 获取实况So2
    Serial.print(F("Co: "));
    Serial.println(airQuality.getCo()); // 获取实况Co
    Serial.print(F("O3: "));
    Serial.println(airQuality.getO3()); // 获取实况O3

    Serial.println(F("========================"));
  }
  else
  { // 更新失败
    Serial.println("Update Failed...");
    Serial.print("Server Response: ");
    Serial.println(airQuality.getServerCode()); // 参考 https://dev.heweather.com/docs/start/status-code
  }
  delay(ROUND * 60000);
}

// 连接WiFi
void ConnectWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED && (i < 10))
  {
    delay(1000);
    Serial.print('.');
    i++;
  }
  if (i == 10)
  { // 10s失败
    Serial.println("WiFi Connection Failed");
  }
  else
  { // 成功
    Serial.println("");
    Serial.println("WiFi Connection Successful!");
    Serial.print("IP address:   ");
    Serial.println(WiFi.localIP());
  }
}
