/* test prog */

#include <stdlib.h>
#include <stdio.h>

#include "sn3218.h"
#include "st7036.h"
#include "cap1166.h"

int main()
{

unsigned char red[6],green[6],blue[6];
int i,j;

sn3218_enable(1);
sn3218_monocolor("a0a0a0");

st7036_clear();

sleep(1);

st7036_cursor_on(1);
st7036_cursor_blink(1);

st7036_contrast(40);

st7036_cursor_position(4,1);
st7036_lcd_buffer("Hello World");

sleep(1);
st7036_cursor_position(0,0);
st7036_lcd_buffer("Top Left");

for (i=0 ; i<=255 ; i+=5)
	{
	cap1166_graph_bar(i);
	for (j=0; j<=1000000 ; j++) { };
	}
for (i=255 ; i>=0 ; i-=5)
	{
	cap1166_graph_bar_reverse(i);
	for (j=0; j<=1000000 ; j++) { };
	}


}
