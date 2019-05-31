import paho.mqtt.publish as publish
import paho.mqtt.client as mqtt
import json
import time
import threading

# publish a message then disconnect.
host = "35.233.174.129"
topic = "home/test1"


def sendMessage(x, y, theta, mode):
    dic = {"x" : x, "y" : y, "theta" : theta, "mode" : mode}
    payload = json.dumps(dic)
    publish.single(topic, payload, qos=1, hostname=host)


def testM(client, userdata, message):
    print(str(message.payload.decode("utf-8")))


class ListenMqtt():

    def __init__(self, trigger, host = "35.233.174.129", topic = "home/test1"):
        self.client = mqtt.Client(host)
        self.client.on_message = trigger 
        self.client.connect(host)
        self.client.loop_start()
        self.client.subscribe(topic)




