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

i=st7036_get_cursor_position();
printf("ANS = %i\n",i);

st7036_cursor_position(4,1);

i=st7036_get_cursor_position();
printf("ANS = %i\n",i);


char bb[60];
st7036_get_lcd_buffer(bb, sizeof bb);
printf(":%s:\n",bb);

i=cap1166_get_leds();
printf("%i\n",i);
cap1166_leds(0);
i=cap1166_get_leds();
printf("%i\n",i);
cap1166_leds(21);
i=cap1166_get_leds();
printf("%i\n",i);


}
