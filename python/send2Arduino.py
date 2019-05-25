import paho.mqtt.publish as publish
import paho.mqtt.client as mqtt
import json
import time

# publish a message then disconnect.
host = "35.233.174.129"
topic = "home/test1"


def sendMessage(x, y, theta, mode):
    dic = {"x" : x, "y" : y, "theta" : theta, "mode" : mode}
    payload = json.dumps(dic)
    publish.single(topic, payload, qos=1, hostname=host)




