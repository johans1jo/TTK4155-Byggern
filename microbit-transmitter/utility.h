#ifndef UTILITY_H
#define UTILITY_H

/*
 * utility_print mimics a minimal implementation
 * of printf, but is much more lightweight. It
 * takes a function pointer to a function capable
 * of printing a single char (and returning void),
 * followed by a string where "%Nd" is used to
 * signal "replace with number". N is a positive
 * integer specifying the minimal print width.
 * Finally comes a list of integers to be
 * substituted in for "%Nd".
 *
 * To be light, it does no error checking, so the
 * number of "%Nd"s must match with the number of
 * integers given after the string. Lest you get
 * unpredictable behavior ;)
 *
 * utility_print can only substitute integers.
 *
 * EXAMPLE USAGE:
 * utility_print(&uart_send, "Num: %d\n\r", 42);
 * 	-> Num: 42
 *
 * utility_print(&uart_send, "Padding: %6d\n\r", 175);
 *	-> Padding: ___175
 *	(Underscores are not printed)
 */

void utility_print(
		void (*put_func)(char),
		char * format_string,
		...
		);

#endif
