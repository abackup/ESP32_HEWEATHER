#include "WeatherNow.h"
WeatherNow::WeatherNow()
{
}

// 配置请求信息，私钥、位置
void WeatherNow::config(String API_Host, String Token, String location, String unit, String lang)
{
    _reqToken = Token;
    _reqLocation = location;
    _reqHost = API_Host;
    _reqUnit = unit;
    _reqLang = lang;
}

// 尝试获取信息，成功返回true，失败返回false
bool WeatherNow::get()
{
    // https请求
    String url = "https://" + _reqHost + "/v7/weather/now?location=" + _reqLocation + "&key=" + _reqToken + "&unit=" + _reqUnit + "&lang=" + _reqLang;
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
void WeatherNow::_parseNowJson(String payload)
{
//    const size_t capacity = 2 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) +
//                            JSON_OBJECT_SIZE(15) + 350;
//    DynamicJsonDocument doc(capacity);
    JsonDocument doc;
    
    deserializeJson(doc, payload);

    JsonObject now = doc["now"];

    _response_code = doc["code"].as<String>();         // API状态码
    _last_update_str = doc["updateTime"].as<String>(); // 当前API最近更新时间
    _now_temp_int = now["temp"].as<int>();             // 实况温度
    _now_feelsLike_int = now["feelsLike"].as<int>();   // 实况体感温度
    _now_icon_int = now["icon"].as<int>();             // 当前天气状况和图标的代码
    _now_text_str = now["text"].as<String>();          // 实况天气状况的文字描述
    _now_windDir_str = now["windDir"].as<String>();    // 实况风向
    _now_windScale_int = now["windScale"].as<int>();   // 实况风力等级
    _now_humidity_float = now["humidity"].as<float>(); // 实况相对湿度百分比数值
    _now_precip_float = now["precip"].as<float>();     // 实况降水量,毫米
    _now_pressure_int = now["pressure"].as<int>();     // 实况气压,百帕
    _now_vis_int = now["vis"].as<int>();               // 实况能见度,公里
    _now_cloud_int = now["cloud"].as<int>();           // 实况云量,百分比数值
    _now_dew_int = now["dew"].as<int>();               // 实况露点温度
    _now_wind360_int = now["wind360"].as<int>();
    _now_windSpeed_int = now["windSpeed"].as<int>();
}

// API状态码
String WeatherNow::getServerCode()
{
    return _response_code;
}

// 当前API最近更新时间
String WeatherNow::getLastUpdate()
{
    return _last_update_str;
}

// 实况温度
int WeatherNow::getTemp()
{
    return _now_temp_int;
}

// 实况体感温度
int WeatherNow::getFeelLike()
{
    return _now_feelsLike_int;
}

// 当前天气状况和图标的代码
int WeatherNow::getIcon()
{
    return _now_icon_int;
}

// 实况天气状况的文字描述
String WeatherNow::getWeatherText()
{
    return _now_text_str;
}

// 实况风向
String WeatherNow::getWindDir()
{
    return _now_windDir_str;
}

// 实况风力等级
int WeatherNow::getWindScale()
{
    return _now_windScale_int;
}

// 实况相对湿度百分比数值
float WeatherNow::getHumidity()
{
    return _now_humidity_float;
}
// 实况降水量,毫米
float WeatherNow::getPrecip()
{
    return _now_precip_float;
}

int WeatherNow::getPressure()
{
    return _now_pressure_int;
}

int WeatherNow::getVis()
{
    return _now_vis_int;
}

int WeatherNow::getCloud()
{
    return _now_cloud_int;
}

int WeatherNow::getDew()
{
    return _now_dew_int;
}

int WeatherNow::getWind360()
{
    return _now_wind360_int;
}

int WeatherNow::getWindSpeed()
{
    return _now_windSpeed_int;
}
