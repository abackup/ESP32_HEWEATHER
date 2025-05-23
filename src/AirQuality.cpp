#include "AirQuality.h"
AirQuality::AirQuality()
{
}

// 配置请求信息，私钥、位置
void AirQuality::config(String API_Host, String Token, String location,  String lang)
{
    _reqToken = Token;
    _reqLocation = location;
    _reqHost = API_Host;
    _reqLang = lang;
}

// 尝试获取信息，成功返回true，失败返回false
bool AirQuality::get()
{
    // https请求
    String url = "https://" + _reqHost + "/v7/air/now?location=" + _reqLocation + "&key=" + _reqToken  + "&lang=" + _reqLang;
    HTTPClient http;
#ifdef DEBUG
    Serial.print("[HTTP] begin...\n");
#endif
    if (http.begin(url))
    {
#ifdef DEBUG
        Serial.println("HTTPclient setUp done!");
#endif
    }
#ifdef DEBUG
    Serial.print("[HTTP] GET...\n");
#endif
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
#ifdef DEBUG
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
#endif
        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            WiFiClient *stream = http.getStreamPtr();
            int size = http.getSize();
            uint8_t inbuff[size];
            stream->readBytes(inbuff, size);
            uint8_t *outbuf = NULL;
            uint32_t out_size = 0;
            int result = ArduinoUZlib::decompress(inbuff, size, outbuf, out_size);
            String payload = String(outbuf, out_size);
            _parseNowJson(payload);
#ifdef DEBUG
            Serial.println(payload);
#endif
        }
    }
    else
    {
#ifdef DEBUG
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
#endif
        return false;
    }

    http.end();
    return true;
}

// 解析Json信息
void AirQuality::_parseNowJson(String payload)
{
    const size_t capacity = 2 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) +
                            JSON_OBJECT_SIZE(15) + 350;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, payload);

    JsonObject now = doc["now"];

    _response_code = doc["code"].as<String>();         // API状态码
    _last_update_str = doc["updateTime"].as<String>(); // 当前API最近更新时间
    _now_aqi_int = now["aqi"].as<int>();             // 实况Aqi
    _now_category_str = now["category"].as<String>();  // 实况Category
    _now_pm10_int = now["pm10"].as<int>();             // 当前Pm10
    _now_pm2p5_int = now["pm2p5"].as<int>();   // 实况Pm2p5
    _now_no2_int = now["no2"].as<int>();     // 实况No2
    _now_so2_int = now["so2"].as<int>();               // 实况So2
    _now_co_float = now["co"].as<float>();     // 实况Co
    _now_o3_int = now["o3"].as<int>();           // 实况O3

}

// API状态码
String AirQuality::getServerCode()
{
    return _response_code;
}

// 当前API最近更新时间
String AirQuality::getLastUpdate()
{
    return _last_update_str;
}

String AirQuality::getCategory()
{
    return _now_category_str;
}

//
int AirQuality::getAqi()
{
    return _now_aqi_int;
}

//
int AirQuality::getPm10()
{
    return _now_pm10_int;
}

// 
int AirQuality::getPm2p5()
{
    return _now_pm2p5_int;
}

// 实况No2
int AirQuality::getNo2()
{
    return _now_no2_int;
}

int AirQuality::getSo2()
{
    return _now_so2_int;
}

// 实况Co
float AirQuality::getCo()
{
    return _now_co_float;
}


int AirQuality::getO3()
{
    return _now_o3_int;
}
