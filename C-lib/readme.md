# C interface for dothat kernel module

## backlight_rgb

Set the backlight to the RGB values

	void backlight_rgb(int R, int G, int B)

	0 <= R,G,B <=255

## backlight_led_rgb

Set individual backlight LED to RGB value

	void backlight_led_rgb(int LED, int R, int G, int B)

	0 <= LED <= 5 (0=left end, 5=right end)
	0 <= R,G,B <=255

## backlight_array

Set all the individual backlight LEDs to specific values in one go.

	void backlight_array(int LED[5][2])

Array LED[5][2] is structured as [0][0]= R0 [0][1]=G0 [0][2]=B0 [1][0]=R1 etc.

## lcd_clear

Clear the LCD display text

	void lcd_clear(void)

## lcd_contrast

Set the contrast of the LCD display

	void lcd_contrast(int c)

The default value of the contrast is 40. Sensible range is 0-80.  A value of -1 will set it to the default.

## lcd_cursor

Sets the properties of the cursor 

	void lcd_cursor(int cursor_on, int cursor_blink)

A non-zero first parameter will turn the cursor on as an underline, zero turns it off.

A non-zero second parameter will turn on the blinking block cursor, zero turns it off.

Both types of cursor can be present.

## lcd_cursor_pos

Sets the position of the cursor in the 16 column, 3 row display

	void lcd_cursor_pos(int col, int row)

	0<= col <=15
	0<= row <=2

## lcd_text

Displays a string at the cursor position

	void lcd_text(char *s)

Long text is wrapped on to next line and around the bottom of the display to the top line.

## lcd_text_line

Displays the string on the specified line starting at character 0.

	void lcd_text_line(int line, char *s)

The string is truncated at character 16 so that no wrapping occurs.


