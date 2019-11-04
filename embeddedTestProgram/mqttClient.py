import paho.mqtt.client as mqtt
from time import sleep

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	if msg.topic == "debug":
		print(msg.topic+" "+str(msg.payload))
	elif msg.topic == "config":
		print(msg.topic+" "+str(msg.payload))
    

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("192.168.1.14", 1883, 60)

i = 0
while (1):
	i += 1
	client.publish("distance",'{"type" : "sensor", "action": "155"}') 

	sleep(.2)
	print("Pub {}".format(i))



