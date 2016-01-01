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

void backlight_array(int LED[5][2])
{
char v[60], vt[10];
int i,j;

v[0]='\0';

for (i=0; i<=5 ; i++)
{
	sprintf(vt,"%02X%02X%02X",LED[i][2],LED[i][1],LED[i][0]);
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

void lcd_text_line(int line, char *s)
{
char st[16];
int r;

strncpy(st,s,16);

r=line % 3;

st7036_cursor_position(0,r);
st7036_lcd_buffer(st);

}

void lcd_text_lines(char *s1, char *s2, char *s3)
{
char st[16];

st7036_clear();

strncpy(st,s1,16);
st7036_cursor_position(0,0);
st7036_lcd_buffer(st);

strncpy(st,s2,16);
st7036_cursor_position(0,1);
st7036_lcd_buffer(st);

strncpy(st,s3,16);
st7036_cursor_position(0,2);
st7036_lcd_buffer(st);

}

void graph_bar(int d, int p)
{

int v;

v=(255*p)/100 ;

if (d==0) 
	{
	cap1166_graph_bar(v);
	}
else
	{
	cap1166_graph_bar_reverse(v);
	}
}

void led_intensity(int l, int h)
{

unsigned int v;

v=((h & 0xff)<<4)+(l & 0xff);

cap1166_luminosity(v);

}

void led_state(int i, int s)
{
unsigned int l,j;

l=cap1166_get_leds();

if (s==0)
	{
	l &= ~(1<<(i));
	}
  else
	{
	l |= (1<<(i));
	};
cap1166_leds(l);
}

void led_states(int s0, int s1, int s2, int s3, int s4, int s5)
{
unsigned int l;


l= s0 & 0x01 ;
l |= (s1 & 0x01)<<1;
l |= (s2 & 0x01)<<2;
l |= (s3 & 0x01)<<3;
l |= (s4 & 0x01)<<4;
l |= (s5 & 0x01)<<5;

cap1166_leds(l);
}

void led_polarities(int s0, int s1, int s2, int s3, int s4, int s5)
{
unsigned int l;


l= s0 & 0x01 ;
l |= (s1 & 0x01)<<1;
l |= (s2 & 0x01)<<2;
l |= (s3 & 0x01)<<3;
l |= (s4 & 0x01)<<4;
l |= (s5 & 0x01)<<5;

cap1166_polarity(l);
}


void led_polarity(int i, int s)
{
unsigned int l,j;

l=cap1166_get_polarity();

if (s==0)
	{
	l &= ~(1<<(i));
	}
  else
	{
	l |= (1<<(i));
	};
cap1166_polarity(l);
}

int led_get_state(int i)
{
unsigned int l;

l=cap1166_get_leds();

l &= (1<<i);

if (l==0) { return 0 ; } else {return 1 ; };
}

int led_get_polarity(int i)
{
unsigned int l;

l=cap1166_get_polarity();

l &= (1<<i);

if (l==0) { return 0 ; } else {return 1 ; };
}

void led_breathe(int i, int p)
{
unsigned int l;

l=cap1166_get_blink();

if (p==0)
        {
        l &= ~(1<<(i));
        }
  else
        {
        l |= (1<<(i));
        };

cap1166_blink_rate(p);
cap1166_blink(l);
}

void led_breathe_rate(int p)
{
cap1166_blink_rate(p);
}

void led_breathes(int s0, int s1, int s2, int s3, int s4, int s5)
{
unsigned int l;


l= s0 & 0x01 ;
l |= (s1 & 0x01)<<1;
l |= (s2 & 0x01)<<2;
l |= (s3 & 0x01)<<3;
l |= (s4 & 0x01)<<4;
l |= (s5 & 0x01)<<5;

cap1166_blink(l);
}

