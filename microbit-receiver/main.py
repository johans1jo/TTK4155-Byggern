from microbit import *
import radio

radio.on()
radio.config(queue=1)
#uart.init(baudrate=115200)
uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin0, rx=pin1)
sleep(1000)

uart.write("Motta\r\n")
sleep(1000)
display.scroll("MOTTA")

while True:
	radio.receive()
	msg = radio.receive()
	while msg is None:
		msg = radio.receive()
		pass
	split = msg.split(",")
	#display.scroll(split[0]) // x
	#display.scroll(split[1]) // a button
	#display.scroll(split[2]) // b button
	#display.scroll(split[3]) // shake
	uart.write(split[0])
	uart.write('\r\n')
	sleep(1000)
