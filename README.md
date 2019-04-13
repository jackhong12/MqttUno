Link MQTT and Arduino with Esp8266
===
透過Esp8266使Arduino可以和google platform連線

**使用環境**
- Ubuntu 18.04.2 LTS
- Arduino Uno
- Arduino package
    - PubSubClient (version 2.6.0)
    - WiFiEsp (version 2.2.2)
    - ArduinoJson (Version 6.10.0)

![demo](/assets/demo.png)

**未來可能遇到問題**
- 如果arduino延遲太久連線可能會中斷，導致無法接收太長的資料

### Issue
**1. [WiFiEsp] cannot initializing**
因為WiFiEsp package只提供9600 rate，Esp8266可能預設為115200 rate，所以要進入Esp8266 command line調整，下面為使用Arduino調整的方法

a. 照下面接法，Arduino reset pin可接可不接
```
Esp8266 | Arduino
-----------------
     RX | RX
     TX | TX
    GND | GND
    VCC | 5v
  CH_PD | 5v
 GPIO 0 | None
 GPIO 2 | None
=================

Arduino | Arduino
-----------------
  Reset | GND
=================
```

b. 打開Serial Monitor，設定`Both NL&CR`，並調成Esp8266 baud

c. 在Serial Monitor 輸入 `AT+UART_DEF=9600,8,1,0,0`
![change baud](/assets/change%20baud.png)


**2. usb permission denied**
![arduino_usb_deny](/assets/arduino_usb_deny.png)

    sudo chmod a+rw /dev/ttyACM0
