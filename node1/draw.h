/**
 * @file
 * @brief Et kult program som kan tegne figurer og sprell på oled'en
 */

#ifndef HEI
#define HEI

// Linje
typedef struct Point {
	int x;
	int y;
} point;

/**
 @brief Draws a pixel at position (x1, y1)

 @param[in] x1 The x-value of the position of the pixel
 @param[in] x1 The y-value of the position of the pixel
 */
void draw_set_bit(int x, int y);


/**
 @brief Clears a pixel at position (x1, y1)

 @param[in] x1 The x-value of the position of the pixel
 @param[in] x1 The y-value of the position of the pixel
 */
void draw_clear_bit(int x, int y);


/**
 @brief Draws something

 */
void draw_print();


/**
 @brief Calls draw_init, which clears all pixels of the oled

 */
void draw_init();

/**
 @brief Clears all pixels of the oled

 */
void draw_clear();


/**
 @brief Draws a point at position (x1, y1) with size size

 @param[in] x1 The x-value of the position
 @param[in] x1 The y-value of the position
 @param[in] x1 The size of the point
 */
void draw_point(int x1, int y1, int size);


/**
 @brief Draws a circle with center at (x1, y1) with radius size

 @param[in] x1 The x-value of the center of the circle
 @param[in] y1 The y-value of the center of the circle
 @param[in] size The radius of the circle

 */
void draw_circle(int x1, int y1, int width, int size);


/**
 @brief Draws a line from the point (x1, y1) to the point (x2, y2) with width size

 @param[in] x1 The x-value of point 1
 @param[in] y1 The y-value of point 1
 @param[in] x2 The x-value of point 2
 @param[in] y2 The x-value of point 2
 */
void draw_line(int x1, int y1, int x2, int y2, int size);


/**
 @brief Draws a several lines??

 @param[in] A pointer to the points we would like to draw
 @param[in] The length of the line??
 @param[in] The size of the line
 */
void draw_lines(point * points, int length, int size);

#endif
