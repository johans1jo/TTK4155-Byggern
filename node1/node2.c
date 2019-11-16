#include "node2.h"
#include "can.h"

void node2_reset() {
	message_t reset_msg = {
		103,
		2,
		param_p,
		param_i
	};
	can_send(&controller_msg);
}
