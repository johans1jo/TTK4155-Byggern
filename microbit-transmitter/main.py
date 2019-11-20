from microbit import *
import radio

radio.on()
display.scroll("Send")

while True:
	x = accelerometer.get_x()
	#y = accelerometer.get_y()
	#z = accelerometer.get_z()
	a = int(button_a.is_pressed())
	b = int(button_b.is_pressed())
	gesture = accelerometer.current_gesture()
	shake = 0
	if gesture is 'shake':
		shake = 1
	msg = str(x) + "," + str(a) + "," + str(b) + "," + str(shake)
	radio.send(msg)
