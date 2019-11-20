from microbit import *
import radio

radio.on()
radio.config(queue=1)

display.scroll("Receive")

while True:
	radio.receive()
	msg = radio.receive()
	while msg is None:
		msg = radio.receive()
		pass
	split = msg.split(",")
	# split[0] # x
	# split[1] # a button
	# split[2] # b button
	# split[3] # shake
	x = int(split[0])
	a = int(split[1])
	b = int(split[2])
	shake = int(split[3])

	# x_out: x
	# left_out: servo left/button left		1: servo venstre	begge: solenoide
	# right_out: servo right/button right	1: servo høyre		begge:

	x_out = (x + 2000)*1023/4000
	if x_out < 0:
		x_out = 0
	elif x_out > 1023:
		x_out = 1023

	left_out = 0
	right_out = 0
	if a and b:
		pass
	elif a:
		left_out = 1
	elif b:
		right_out = 1

	if shake:
		left_out = 1
		right_out = 1

	pin0.write_analog(x_out)
	pin1.write_digital(left_out)
	pin2.write_digital(right_out)
