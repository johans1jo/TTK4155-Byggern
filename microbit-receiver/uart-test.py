from microbit import *

#uart.init(baudrate=115200)
uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin0, rx=pin1)

display.scroll("X")
while True:
	uart.write("a")
	sleep(100)
