# C interface for dothat kernel module

Run make to generate 'libdothat.a'.  Compile a program with 

	cc -o test test.c -L. -ldothat

Only the dothat.h header file is needed for the higher level C routines below.


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

## lcd_text_lines

Displays the three strings on the three  lines

	void lcd_text_lines(char *s1, char *s2, char *s3)

The display is cleared before writing the strings and each string us 
truncated at character 16.

## graph_bar

Uses the six LEDs as a bar graph

	void graph_bar(int d, int p)

Variable 'p' is the percentage of the bar illuminated, 'd' gives the 
direction: d=0 bar starts at the top and grows down, else bar starts
at bottom and grows up.

## led_intensity

Sets the intensity of the six LEDs

	void led_intensity(int l, int h)

This sets the low ('l') and high ('h') intensity of the LEDs. Only the
low 4 bits of each value is used and the percentage intensity is a 
non-linear scale from 0-77% for the low value and 7-100% for the high.
The actual brightness of the LEDs is determined by the 'polarity' and 
'enabled' stated of each LED. 

	LED	Polarity	Appearance

	0	0		on at min level
	1	0		on at max level
	0	1		on at 100-min level
	1	1		on at 100-max level

## led_state, led_polarity, led_get_state, led_get_polarity

These routines set and get the status of individual LEDs.

	void led_state(int i, int s)
	void led_polarity(int i, int s)
	int led_get_state(int i)
	int led_get_polarity(int i)

In all these 'i' is the LED (0 <= i <= 5) and 's' sets the state (s=0|1).
The get routines return 0 or 1 refelcting the state set for the particular
LED. See above for the interaction between the state and polarity values.

## led_states, led_polarities

Sets the status of all LEDs 

	void led_states(int s0, int s1, int s2, int s3, int s4, int s5)
	void led_polarities(int s0, int s1, int s2, int s3, int s4, int s5)

's0' to 's5' are the individual LEDs

## led_breathe

Set a specific LED to breathe (i.e. flash with ramp on / ramp off)

	void led_breathe(int i, int p)

'i' is the LED (0 <= i <= 5) and 'p' is the breathe rate in ms. A
breathe rate of '0' will stop the LED from flashing.

## led_breathe_rate

Sets the breathe rate for LEDs for next time an LED is set to blink (if
no other rate set as part of led_breathe routine).

	void led_breathe_rate(int p)

## led_breathes

Sets the breathe status of all leds

	void led_breathes(int s0, int s1, int s2, int s3, int s4, int s5)

's0' to 's5' are the individual LEDs, a '0' turns the LED off, anything
else will set the LED breathing at the rate determined by last call
to led_breathe_rate

## Note on LEDs

Setting LEDs on/off at a specific intensity and setting the LEDS breathing
are mutually exclusive across all the LEDs. i.e. You can't set a single 
LED on and have another one blinking - all LEDs are controlled by the
polarity/state routines OR by the breathe routines.

