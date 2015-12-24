/* 
Higher level C routines to controla dothat via low level routines

(c) P. Biggs 2015

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sn3218.h"
#include "st7036.h"
#include "cap1166.h"

void backlight_rgb(int R, int G, int B)
{
char v[10];
int red, green, blue;

red=R % 256;
green=G % 256;
blue = B % 256;
sprintf(v,"%02X%02X%02X",blue, green, red);
sn3218_monocolor(v);
}

void backlight_led_rgb(int LED, int R, int G, int B)
{
char v[10];
int red, green, blue, led;

led = LED % 5;
red=R % 256;
green=G % 256;
blue = B % 256;
sprintf(v,"%02X%02X%02X",blue, green, red);
sn3218_lcd_set(led, v);
}

void backlight_array(int LED[6][3])
{
char v[60], vt[10];
int i,j;

v[0]='\0';

for (i=0; i<=5 ; i++)
{
	sprintf(vt,"%02X%02X%02X",LED[i][0],LED[i][1],LED[i][2]);
	strncat(v,vt,6);
}

sn3218_lcd_raw(v);

}

void lcd_clear(void)
{
st7036_clear();

}

void lcd_contrast(int c)
{
int con;

if (c<0 ) con=40 ; else con=c ;

st7036_contrast(con);

}

void lcd_cursor(int cursor_on, int cursor_blink)
{
if (cursor_on==0) st7036_cursor_on(0) ; else st7036_cursor_on(1);
if (cursor_blink==0) st7036_cursor_blink(0) ; else st7036_cursor_blink(1);

}

void lcd_cursor_pos(int col, int row)
{
int c,r;

c=col%16;
r=r%3;

st7036_cursor_position(c,r);

}

void lcd_text(char *s)
{
st7036_lcd_buffer(s);
}
