#ifndef MQTT_H
#define MQTT_H

#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define EspBuad 9600


class MQTT {
public:
    MQTT(String wifiName, String password, int TX, int RX, String serverIp, int serverPort);
    bool connectWifi(int maxTime = 10); // 連網路,最多嘗試maxTime次
    bool isConnectMQTT(int maxTime = 1, int delayTime = 20);   // 是否連上mqtt,沒有重連
    bool isNewMessage();    // 是否有新訊息,有的話擷取新訊息
    int getX();
    int getY();
    int getTheta();
    int getMode();
    void setSubscribe(String topic);

private:
    String wifiName, wifiPassword, serverIp, subTopic, topicSubscribe;
    int TX, RX, serverPort;
    SoftwareSerial *esp;
    WiFiEspClient *espClient;

public:
    PubSubClient *client;

    // state
    static const int STATE_CONNECT_EMPTY = 0;
    static const int STATE_CONEECT_GET = 1;

    // buffer data
    static int buffer_length;
    static char buffer[250];
    static int state, mode, x, y, theta;

    static void mqttCallback(char* topic, byte* payload, unsigned int length); //get callback
    static void printByte(byte* payload, unsigned int length);
    void subscribe();
};


#endif
