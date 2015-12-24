*** C interface for dothat kernel module

*backlight_rgb

Set the backlight to the RGB values

	void backlight_rgb(int R, int G, int B)

	0 <= R,G,B <=255

*backlight_led_rgb

Set individual backlight LED to RGB value

	void backlight_led_rgb(int LED, int R, int G, int B)

	0 <= LED <= 5 (0=left end, 5=right end)
	0 <= R,G,B <=255

*backlight_array

Set all the individual backlight LEDs to specific values in one go.

	void backlight_array(int LED[5][2])

Array LED[5][2] is structured as [0][0]= R0 [0][1]=G0 [0][2]=B0 [1][0]=R1 etc.




