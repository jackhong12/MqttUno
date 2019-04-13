#include "mqtt.h"

MQTT mqtt("TY1025", "56941205", 3, 4, "35.233.174.129", 1883);

void setup() {
    Serial.begin(9600);
    mqtt.connectWifi();
    mqtt.setSubscribe("home/test2");
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
    delay(20);
}
