
#include "mqtt.h"

MQTT mqtt("ME91307", "", 3, 4, "35.233.174.129", 1883);

void setup() {
    Serial.begin(9600);
    mqtt.connectWifi();
    mqtt.setSubscribe("home/test1");
    //mqtt.client->publish("home/test", "hello");
}

void loop() {
    if (mqtt.isNewMessage()) {
        Serial.print("x: ");
        Serial.println(mqtt.getX());
        Serial.print("y: ");
        Serial.println(mqtt.getY());
        Serial.print("mode: ");
        Serial.println(mqtt.getMode());
        Serial.print("theta: ");
        Serial.println(mqtt.getTheta());
    }
    delay(5);
}
