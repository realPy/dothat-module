#Kernel module for dothat (Display O Tron Hat)
This driver is still experimental. Use it at your own risk. He can not be load with kernel tree for the moment.

##Why a kernel module?
The first things when I bought one is try to play with. The installation install lots of thing and it's really a pain to test it.
Why just plug it and play it just on line in bash? The only language available is python. I love python but i don't want to be limited in one language. I'll really want to control it with C / bash / etc.. and share with several processus. The python lib by piromoni not work very well with touch. First i think it's a hardware problem but you can check that the touch work very well with this driver.

##The hardware:

The display o tron hat is not just on components but three components togother:
* A sn3218: used to backlight the LCD. Its a 6 segments BGR color.
* A cap1166: used to handle touch and control the 6 graph leds.
* A st7036: The LCD components to draw.

This 3 components not use the same protocol. The sn3218 and cap1166 use I2C and the st7036 use SPI. The st7036 is also controlled by a GPIO PIN to selected a dedicated register. 

##Requirements:
You need the source of your kernel and the spidev need to be disable. The spidev is not compile in module with all kernel provide by Hexxeh with rpi-update. Thanks to the Kernel-tree we are not need to recompiled the kernel. Just copy the nospidev.dtb in your /boot/overlays and add this line in /boot/config.txt:

	dtoverlay=nospidev


##How to compile:
You can update with the rpi-update

	sudo rpi-update
	
Install or update your source kernel by the method provide here:
https://github.com/notro/rpi-source/wiki

Then

	git clone https://github.com/realPy/dothat-module.git
	cd dothat-module
	make
	insmod dothat.ko
	
Compile the client:
Replace the "tun0" reference in the ioclient.c source by the interface of your choice (eth0 for example)
Compile with:

	gcc -o ioclient ioclient.c -lm

Run and push the button :)


##Control with sysfs:
The driver can be controlled by sysfs.
You just need to read or write to a virtual file in /sys/

###Backlight LCD

####/sys/class/dothat/sn3218/enable
Value: 0 for disable , 1 or enable

	echo 1 > /sys/class/dothat/sn3218/enable

####/sys/class/dothat/sn3218/lcd
Set the color of one segment or get all color of segment
 
Get the color status:	
	cat /sys/class/dothat/sn3218/lcd
    B: 0x00 0x00 0x00 0x00 0x00 0x00
    G: 0x00 0x00 0x00 0x00 0x00 0x00
    R: 0x00 0x00 0x00 0x00 0x00 0x00
	
Set the color blue to the segment 2
	echo "2 FF0000" > /sys/class/dothat/sn3218/lcd

####/sys/class/dothat/sn3218/monocolor
Set the same color for all segment or get all color of segment

	
Set the color red for all segments
	echo "0000FF" > /sys/class/dothat/sn3218/monocolor


####/sys/class/dothat/sn3218/lcd_raw

Set the colors of segments in one time. You need provide a the 6 colors of the segments [BGR][BGR][BGR][BGR][BGR][BGR]

	echo "0000FF00FFFF0000FF0000FF0000DF0000CC" > /sys/class/dothat/sn3218/lcd_raw

###TEXT LCD

####/sys/class/dothat/st7036/clear
Write to it clear the screen and set the cursor to the position 0,0

	echo 1 > /sys/class/dothat/st7036/clear

####/sys/class/dothat/st7036/contrast
Use to control the contrast of the lcd. By default the value is 40 decimal. 
	echo 40 > /sys/class/dothat/st7036/contrast
	
####/sys/class/dothat/st7036/cursor_on
Set the cursor "_" to on or disable it
	echo 1 > /sys/class/dothat/st7036/cursor_on

For disable:
	echo 1 > /sys/class/dothat/st7036/cursor_on
	
####/sys/class/dothat/st7036/cursor_blink
Blink the cursor
	echo 1 > /sys/class/dothat/st7036/cursor_blink
	
For disable:
	echo 0 > /sys/class/dothat/st7036/cursor_blink

####/sys/class/dothat/st7036/cursor_position
The LCD have a 3 lines of 16 character.
A "8 0" value mean  column 8, row 0
	echo "8 1" > /sys/class/dothat/st7036/cursor_position
You can also get the current position with:
	cat /sys/class/dothat/st7036/cursor_position

####/sys/class/dothat/st7036/lcd_buffer
Write on it write the text a the cursor position:
Example: 
	echo "2 0" > /sys/class/dothat/st7036/cursor_position
	echo "Hello World" > /sys/class/dothat/st7036/lcd_buffer
	
We set the cursor a the 2 0 and write "Hello world". The Hello world is centered at the first line.


####/sys/class/dothat/st7036/shift_display
Shift the display with the correspondant value:
* '>' character, shift the text to the right
	echo '>' > /sys/class/dothat/st7036/shift_display
	
* '<' character, shift the text to the left
	echo '<' > /sys/class/dothat/st7036/shift_display

###Graph leds

####/sys/class/dothat/cap1166/blink

Blink the led at the blink_rate value. The leds is coded in one byte. Each leds is coded with a bit value.
[LED 6 | LED 5 | LED 4 | LED 3 | LED 2 | LED 1  ]

To blink 5 / 3 / 1  its 010101 binary. In decimal the convert value is 21

	echo 21 > /sys/class/dothat/cap1166/blink
	
####/sys/class/dothat/cap1166/blink_rate

Set the blink rate in ms
	echo 500 > /sys/class/dothat/cap1166/blink_rate


####/sys/class/dothat/cap1166/graph_bar
Set the all 6 leds as a progress bar.
The light value go from the top to the bottom
0 value mean 0%
255 value mean 100%
	echo 127 > /sys/class/dothat/cap1166/graph_bar

	
####/sys/class/dothat/cap1166/graph_bar_reverse
Same as graph_bar except that the light value go from the bottom to the top
	
####/sys/class/dothat/cap1166/leds
Enable the leds. The leds is coded in one byte. Each leds is coded with a bit value.
[LED 6 | LED 5 | LED 4 | LED 3 | LED 2 | LED 1  ]

Enable leds light not mean that is light always on. If polarity is disable the led is light. If polarity is enable , enable the led light off the leds and disable light on.
 
####/sys/class/dothat/cap1166/luminosity
 Set the luminosity of the enable leds
 	echo 144 > /sys/class/dothat/cap1166/luminosity
	
####/sys/class/dothat/cap1166/polarity
Set the polrity of the leds. The leds is coded in one byte. Each leds is coded with a bit value.
[LED 6 | LED 5 | LED 4 | LED 3 | LED 2 | LED 1  ]
 The polarity inverse the logical state of the specified leds.
 Example
 *led1 polarity is OFF led 1 is enable: led 1 is light on
 *led1 polarity is OFF led 1 is disable: led 1 is light off
 *led1 polarity is ON led 1 is enable: led 1 is light off
 *led1 polarity is OFF led 1 is disable: led 1 is light on
 
 
###Touch sensors:
The touch sensors is recognized like a classic unix keyboard at /dev/input/by-path/platform-3f804000.i2c-event
See the C example ioclient.c to handle.
This example show the Bandwidth of a VPN tun interface in real time.

### FAQ
####Why the rainbox effect is in the client code and directly hardcoded in the driver?
To calculate a rainbow effect we use the HSV color transformation. This require floating point. Linus not recommanded to use floating point in kernel module and I'm agree.


