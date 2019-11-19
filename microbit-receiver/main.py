from microbit import *
import radio

radio.on()
radio.config(queue=1)
#uart.init(baudrate=115200)
#uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin0, rx=pin1)
#sleep(1000)

display.scroll("MOTTA")
pin0.write_analog(200)
sleep(10000)
'''
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
	a = int(split[2])
	b = int(split[3])
	shake = int(split[3])

	servo_out = 0
	if a and b:
		servo_out = 0
	elif a:
		servo_out = 511
	elif b:
		servo_out = 1023

	shake_out = 0
	if shake:
		shake_out = 1023

	x_out = (x + 2000)*1023/4000

	pin0.write_analog(servo_out)
	pin1.write_analog(shake_out)
	pin2.write_analog(x_out)

	sleep(1000)
'''
