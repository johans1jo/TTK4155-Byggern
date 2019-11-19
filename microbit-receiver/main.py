from microbit import *
import radio

radio.on()
radio.config(queue=1)
#uart.init(baudrate=115200)
uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin0, rx=pin1)

uart.write("Motta\r\n")
display.scroll("MOTTA")

while True:
	radio.receive()
	msg = radio.receive()
	while msg is None:
		msg = radio.receive()
		pass
	uart.write(msg)
	uart.write('\r\n')
	sleep(1000)
