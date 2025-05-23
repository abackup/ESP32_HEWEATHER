# ESP32_Heweather

- [ESP32_Heweather](#esp32-heweather)
  * [基本介绍](#基本介绍)
  * [准备工作](#准备工作)
  * [使用说明](#使用说明)
    + [获取实时天气信息](#获取实时天气信息)
    + [获取实时空气质量信息](#获取实时空气质量信息)

## 基本介绍

**Arduino**开发平台使用**ESP32**获取**和风天气**的第三方库（原地址：[ye-zhang0720](https://github.com/ye-zhang0720/ESP32_HEWEATHER)），更新了和风 API v7.15。



此库用于**ESP32**物联网开发板通过**HTTPS协议**获取和风天气API所提供的免费天气信息。使用此库可以省去繁杂的HTTPS请求以及JSON解析部分，使用几行代码即可获取有效信息，大大简化了开发步骤。

> 注：
>
> - 由于信息的安全性要求不高，故HTTPS请求中设置了不进行身份校验；
> - 只涉及常人经常关注的信息如`温度`、`风力`、`空气质量`等。



## 准备工作

1. 注册和风天气并获得key，详见 https://console.qweather.com/project/492FYDNDMB?lang=zh  ；

2. 安装ESP32扩展程序

3. 安装**ArduinoJson**库，详见 https://docs.arduino.cc/libraries/arduinojson/  ；
   安装**ArduinoUZlib**库，详见 https://github.com/tignioj/ArduinoUZlib/  ;

	其他说明：

	- 私钥获取 https://console.qweather.com/project/492FYDNDMB?lang=zh  ；

	- 城市代码 https://github.com/heweather/LocationList

		excel表 `Location_ID`，亦可通过[城市搜索](https://dev.heweather.com/docs/api/geo)获取 ；

	- 和风天气开发者**官方文档**：https://dev.qweather.com/docs/start/  ；

## 使用说明

1. 安装本库

	1）下载压缩包或克隆；

	2）解压并复制到**项目文件夹**下的**libraries**目录下；

	3）重启Arduino IDE。

2. **example**目录中列出了使用的基本结构和所有函数示例，为主要参考文档；

### 获取实时天气信息

  ```c++
WeatherNow weatherNow;         // 建立weatherNow对象
weatherNow.config(API_Host, Token, Location, Unit, Lang); // 配置请求信息
weatherNow.getServerCode();    // 获取API状态码   
weatherNow.getLastUpdate();    // 获取服务器更新天气信息时间
weatherNow.getTemp();          // 获取实况温度
weatherNow.getFeelLike();      // 获取实况体感温度
weatherNow.getIcon();          // 获取当前天气图标代码
weatherNow.getWeatherText();   // 获取实况天气状况的文字描述
weatherNow.getWind360();
weatherNow.getWindDir();       // 获取实况风向
weatherNow.getWindScale();     // 获取实况风力等级
weatherNow.getHumidity();      // 获取实况相对湿度百分比数值
weatherNow.getPrecip();        // 获取实况降水量,毫米
weatherNow.getPressure();
weatherNow.getVis();
weatherNow.getCloud();
weatherNow.getDew();
  ```



### 获取实时空气质量信息

```c++
AirQuality airQuality;           // 建立airQuality对象
airQuality.config(API_Host, Token, Location, Lang); // 配置请求信息
airQualityir.getServerCode();      // 获取API状态码
airQualityir.getLastUpdate();      // 获取服务器更新天气信息时间
airQualityir.getAqi();             // 实时空气质量指数
airQualityir.getCategory();        // 实时空气质量指数级别
airQualityir.getPrimary();         // 实时空气质量的主要污染物，优时返回值为NA
airQualityir.getPm10();
airQualityir.getPm2p5();
airQualityir.getNo2();
airQualityir.getSo2();
airQualityir.getCo();
airQualityir.getO3();
```





















