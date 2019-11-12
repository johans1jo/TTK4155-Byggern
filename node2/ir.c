#include "ir.h"
#include "adc.h"

void ir_init() {

}

int ir_read() {
	return adc_read();
}
