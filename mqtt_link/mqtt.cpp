#include "mqtt.h"
#define MQTT_DEBUG
#define ARDUINO_MEGA
int MQTT::buffer_length = 0;
char MQTT::buffer[] = {};
int MQTT::state = 0;
int MQTT::mode = 0;
int MQTT::x = 0;
int MQTT::y = 0;
int MQTT::theta = 0;


MQTT::MQTT (String wifiName, String password, int TX, int RX, String serverIp, int serverPort) {
    this->wifiName = wifiName;
    this->wifiPassword = password;
    this->TX = TX;
    this->RX = RX;
    this->serverIp = serverIp;
    this->serverPort = serverPort;
}

// 連線wifi最多嘗試maxTime次
bool MQTT::connectWifi (int maxTime = 10) {
    espClient = new WiFiEspClient();
    client = new PubSubClient(*espClient);

#ifndef ARDUINO_MEGA
    Serial.println("hi1");
    esp = new SoftwareSerial(this->TX, this->RX);
    esp->begin(EspBuad);  //設定esp8266胞率 
    WiFi.init(esp);
#else
    Serial.println("hi");

    Serial1.begin(115200);
    WiFi.init(&Serial1);
#endif

    const char* name = this->wifiName.c_str();
    const char* password = this->wifiPassword.c_str();

    while (WiFi.begin(name, password) != WL_CONNECTED) {
        --maxTime;
        if (maxTime <= 0) {
            Serial.println("中止連線\n");
            return false;
        }
        delay(100);
    }

    // set server ip and port
    const char* ip = this->serverIp.c_str();
    client->setServer(ip, this->serverPort);
    return true;
}

// 是否連上mqtt,沒有的話重連,最多嘗試maxtime次
bool MQTT::isConnectMQTT (int maxTime = 1, int delayTime = 20) {
    // 沒有連線重新連線
    while (!this->client->connected()) {
        if (this->client->connect("127.0.0.1")) {
            return true;
        }

        delay(delayTime);

        --maxTime;
        if (maxTime < 1) {
            return false;
        }
    }

    return true;
}

int MQTT::getX () {
    state = STATE_CONNECT_EMPTY;
    return x;
}

int MQTT::getY () {
    state = STATE_CONNECT_EMPTY;
    return y;
}

int MQTT::getMode () {
    state = STATE_CONNECT_EMPTY;
    return mode;
}

int MQTT:: getTheta () {
    state = STATE_CONNECT_EMPTY;
    return theta;
}

// 是否有新訊息,有的話擷取新訊息
bool MQTT::isNewMessage () {
    // 連線
    if (!client->loop()) {
        Serial.println("重新連線MQTT");
        if (!this->isConnectMQTT()) {
            Serial.println("連線失敗");
        }
        else {
            Serial.println("MQTT連線成功");
            this->subscribe();
        }
    }

    if (state == STATE_CONEECT_GET)
        return true;
    else 
        return false;
}

void MQTT::setSubscribe (String topic) {
    this->topicSubscribe = topic;
    isNewMessage();
}

// subscribe mqtt
void MQTT::subscribe () {
    char* topic = topicSubscribe.c_str();
    client->subscribe(topic);
    client->setCallback(mqttCallback);
}

// mqtt callback
static void MQTT::mqttCallback (char* topic, byte* payload, unsigned int length) {
    byte* p = (byte*)malloc(length);
    memcpy(p, payload, length);

    int i = 0;
    /*
    for (; i < length && i < 50; i++) 
        buffer[i] = (char)p[i];
    for (; i < 50; i++)
        buffer[i] = ' ';
    */
    char *newMessage = new char[length];
    newMessage = (char*) p;

    /*
    DynamicJsonDocument json(50); //buffer多大
    deserializeJson(json, buffer);
    */
    DynamicJsonDocument json(length); //buffer多大
    deserializeJson(json, newMessage);
    mode = json["mode"];
    theta = json["theta"];
    x = json["x"];
    y = json["y"];

    state = STATE_CONEECT_GET;  //change state, let user know there is a message
}

static void MQTT::printByte (byte* p, unsigned int length) {
    for (int i = 0; i < length; i++) {
        Serial.print((char)p[i]);
    }
}
