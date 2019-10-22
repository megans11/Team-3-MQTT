from curses import wrapper
from time import sleep, time
from datetime import datetime
import paho.mqtt.client as mqtt
import json
import copy

class displayApp:

	def __init__(self):
		self.good = True
		pass

	def initApp(self, stdscr):
		self.title =  "|"+"TOPIC PUBLISHES".center(79) + "|"
		self.cap =      ".-------------------------------------------------------------------------------."
		self.bottom =   "'-------------------------------------------------------------------------------'"
		self.div =      "|-------------------------------------------------------------------------------|"
		self.header1  =  "|  Topic  |     Arm      |     Rover    |    Cannon    |    Sensor    |  Total  |"
		self.header2 = "|         | /sec | total | /sec | total | /sec | total | /sec | total |         |"
		self.row =    "|{:>8} |{:>5} |{:>6} |{:>5} |{:>6} |{:>5} |{:>6} |{:>5} |{:>6} |{:>8} |"
		self.board_header = "|  Board  | Pub Attempts |   Success  |   Failed   |  Rec  | Last Time  |  Good |"
		self.board_row = "|{:>8} |{:>13} |{:>11} |{:>11} |{:>6} |{:>11} |{:>6} |"
		self.topics = ["debug", "stats", "rover", "arm", "cannon", "sensor"]
		self.stdscr = stdscr

		self.counts = {}
		self.last_sec = {}
		self.per_sec = {"total":[0,0,0,0]}
		for topic in self.topics:
			self.counts[topic] =[0,0,0,0,0]
			self.last_sec[topic] =[0,0,0,0,0]
			self.per_sec[topic] =[0,0,0,0,0]

		self.boards = ["arm", "rover", "cannon", "sensor"]
		self.board_stats = {
			"arm":
			{
					"pub_attempts" : 0,
					"pub_success" : 0,
					"msg_received" : 0,
					"last_time": datetime.fromtimestamp(time()).strftime("%X")
			},
			"rover":
			{
					"pub_attempts" : 0,
					"pub_success" : 0,
					"msg_received" : 0,
					"last_time": datetime.fromtimestamp(time()).strftime("%X")
			},
			"cannon":
			{
					"pub_attempts" : 0,
					"pub_success" : 0,
					"msg_received" : 0,
					"last_time": datetime.fromtimestamp(time()).strftime("%X")
			},
			"sensor":
			{
					"pub_attempts" : 0,
					"pub_success" : 0,
					"msg_received" : 0,
					"last_time": datetime.fromtimestamp(time()).strftime("%X")
			}
		}

		self.last_time = time()

		self.stdscr.addstr(0, 0, self.cap)
		self.stdscr.addstr(1, 0, self.title)
		self.stdscr.addstr(2, 0, self.div)
		self.stdscr.addstr(3, 0, self.header1)
		self.stdscr.addstr(4, 0, self.header2)
		self.stdscr.addstr(5, 0, self.div)


		for i, topic in enumerate(self.topics):
			self.stdscr.addstr(i+6, 0, self.row.format(topic,
														self.per_sec[topic][0], self.counts[topic][0],
														self.per_sec[topic][1], self.counts[topic][1],
														self.per_sec[topic][2], self.counts[topic][2],
														self.per_sec[topic][3], self.counts[topic][3],
														self.counts[topic][4]))

		self.stdscr.addstr(len(self.topics)+6, 0, self.div)	
		self.stdscr.addstr(len(self.topics)+7, 0, self.board_header)
		self.stdscr.addstr(len(self.topics)+8, 0, self.div)	
		for i, board in enumerate(self.boards):
			self.stdscr.addstr(len(self.topics)+ 9 + i, 0, self.board_row.format(board,
																																						self.board_stats[board]["pub_attempts"],
																																						self.board_stats[board]["pub_success"],
																																						self.board_stats[board]["pub_attempts"] - self.board_stats[board]["pub_success"],
																																						self.board_stats[board]["msg_received"],
																																						self.board_stats[board]["last_time"],
																																						0,
																																						"No"))
		self.stdscr.addstr(len(self.topics)+13, 0, self.bottom)	
		self.stdscr.refresh()


	def update(self):
		# print("UPDATING DISP")
		diff = time() - self.last_time
		if (diff > 1):
			self.per_sec["total"] = [0,0,0,0]
			for topic in self.topics:
				self.per_sec["total"][0] += (self.counts[topic][0] - self.last_sec[topic][0])/diff
				self.per_sec["total"][1] += (self.counts[topic][1] - self.last_sec[topic][1])/diff
				self.per_sec["total"][2] += (self.counts[topic][2] - self.last_sec[topic][2])/diff
				self.per_sec["total"][3] += (self.counts[topic][3] - self.last_sec[topic][3])/diff
				self.per_sec[topic][0] = round((self.counts[topic][0] - self.last_sec[topic][0])/diff)
				self.per_sec[topic][1] = round((self.counts[topic][1] - self.last_sec[topic][1])/diff)
				self.per_sec[topic][2] = round((self.counts[topic][2] - self.last_sec[topic][2])/diff)
				self.per_sec[topic][3] = round((self.counts[topic][3] - self.last_sec[topic][3])/diff)
			self.last_sec = copy.deepcopy(self.counts)
			self.last_time = time()

		# print("UPDATING DISP 1")
		for i, topic in enumerate(self.topics):
			self.stdscr.addstr(i+6, 0, self.row.format(topic,
														self.per_sec[topic][0], self.counts[topic][0],
														self.per_sec[topic][1], self.counts[topic][1],
														self.per_sec[topic][2], self.counts[topic][2],
														self.per_sec[topic][3], self.counts[topic][3],
														self.counts[topic][4]))

		# print("UPDATING DISP 2")
		# print(self.board_stats)
		for i, board in enumerate(self.boards):
			if self.per_sec["total"][i] > 9.5:
				status = "Yes"
			else:
				status = "No"
			self.stdscr.addstr(len(self.topics)+ 9 + i, 0, self.board_row.format(board,
																																						self.board_stats[board]["pub_attempts"],
																																						self.board_stats[board]["pub_success"],
																																						self.board_stats[board]["pub_attempts"] - self.board_stats[board]["pub_success"],
																																						self.board_stats[board]["msg_received"],
																																						self.board_stats[board]["last_time"],
																																						status))
		# print("UPDATING DISP 3")
		self.stdscr.refresh()
		# print("UPDATING DISP 4")


myApp = displayApp()

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    for topic in myApp.topics:
    	client.subscribe(topic)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	board_pos_map = {"rover" : 1, "arm": 0, "cannon": 2, "sensor" : 3}

	# print(msg.topic+" "+str(msg.payload))
	# parse
	msg_dict = json.loads(msg.payload)

	if (msg.topic == "stats") :
		myApp.board_stats[msg_dict["board"]]["msg_received"] = msg_dict["received"]
	else:
		# update stats
		myApp.counts[msg.topic][board_pos_map[msg_dict["board"]]] += 1
		myApp.counts[msg.topic][4] += 1

		myApp.board_stats[msg_dict["board"]]["pub_attempts"] = int(msg_dict["count"])
		myApp.board_stats[msg_dict["board"]]["pub_success"] += 1
		myApp.board_stats[msg_dict["board"]]["last_time"] = datetime.fromtimestamp(time()).strftime("%X")

	if myApp.counts[msg.topic][4] % 25 == 0:
		myApp.update()



def main(stdscr):
	# Clear screen
	stdscr.clear()

	myApp.initApp(stdscr)

	client = mqtt.Client()
	client.on_connect = on_connect
	client.on_message = on_message
	client.connect("192.168.2.3", 1883, 60)
	# client.connect("127.0.0.1", 1883, 60)

	client.loop_forever()

wrapper(main)
