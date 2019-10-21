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

client.connect("127.0.0.1", 1883, 60)
i = 0
while (1):
	i += 1
	client.publish("debug",'{{"board" : "rover", "count": "{}", "msg": "TEST0"}}'.format(i)) 
	client.publish("debug",'{{"board" : "arm", "count": "{}", "msg": "TEST1"}}'.format(i)) 
	client.publish("debug",'{{"board" : "cannon", "count": "{}", "msg": "TEST2"}}'.format(i)) 
	client.publish("debug",'{{"board" : "sensor", "count": "{}", "msg": "TEST3"}}'.format(i)) 
	sleep(.04)
	i += 1
	client.publish("config",'{{"board" : "rover", "count": "{}", "msg": "TEST0"}}'.format(i)) 
	client.publish("config",'{{"board" : "arm", "count": "{}", "msg": "TEST1"}}'.format(i)) 
	client.publish("config",'{{"board" : "cannon", "count": "{}", "msg": "TEST2"}}'.format(i)) 
	client.publish("config",'{{"board" : "sensor", "count": "{}", "msg": "TEST3"}}'.format(i)) 
	sleep(.04)
	print("Pub {}".format(i))

