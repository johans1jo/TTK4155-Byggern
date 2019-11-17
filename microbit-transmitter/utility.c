#include <stdarg.h>
#include "utility.h"

static void utility_helper_print_int(
		void (*put_func)(char),
		int number
		){
	if(number == 0){
		put_func('0');
		return;
	}

	int digits = 0;
	int reverse = 0;
	int print_negative_sign = 0;

	if(number < 0){
		print_negative_sign = 1;
		number = -number;
	}

	while(number){
		reverse *= 10;
		reverse += (number % 10);
		number /= 10;
		digits++;
	}

	if(print_negative_sign)
		put_func('-');

	while(reverse){
		put_func((char)((reverse % 10) + '0'));
		reverse /= 10;
		digits--;
	}
	while(digits){
		put_func('0');
		digits--;
	}
}

static int utility_helper_min_width(char * let){
	int minimum_width = 0;
	while(*let != 'd'){
		minimum_width *= 10;
		minimum_width += (*let - '0');
		let++;
	}
	return minimum_width;
}

static int utility_helper_anticipate_width(int number){
	if(number == 0)
		return 1;
	int width = 0;
	if(number < 0)
		width++;
	while(number){
		width++;
		number /= 10;
	}
	return width;
}

void utility_print(
		void (*put_func)(char),
		char * format_string,
		...
		){
	va_list arg_ptr;
	va_start(arg_ptr, format_string);

	int number;
	int minimum_width;
	int required_width;
	char * let;
	for(let = format_string; *let; let++){
		if(*let != '%'){
			put_func(*let);
			continue;
		}
		number = va_arg(arg_ptr, int);

		let++;
		minimum_width = utility_helper_min_width(let);
		required_width = utility_helper_anticipate_width(number);

		while(*let != 'd')
			let++;

		while(required_width < minimum_width){
			put_func(' ');
			required_width++;
		}

		utility_helper_print_int(put_func, number);
	}
	va_end(arg_ptr);
}
