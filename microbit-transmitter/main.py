from microbit import *
import radio

radio.on()
display.scroll("SEND")

while True:
	x = accelerometer.get_x()
	#y = accelerometer.get_y()
	#z = accelerometer.get_z()
	a = button_a.is_pressed()
	b = button_b.is_pressed()
	gesture = accelerometer.current_gesture()
	msg = str(x) + "," + str(a) + "," + str(b) + "," + gesture
	radio.send(msg)
