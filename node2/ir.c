#include "ir.h"
#include "adc.h"

#define IR_TRESHOLD 300

void ir_init() {

}

int ir_get() {
	int read = adc_read(); // Les IR-verdi
	int ir = (read < IR_TRESHOLD);
	return ir;
}
