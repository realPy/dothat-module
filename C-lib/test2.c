/* test prog */

#include <stdlib.h>
#include <stdio.h>

#include "dothat.h"

int main()
{

int LED[5][2];
int i,j,l,p;
backlight_rgb(128,128,128);

lcd_clear();

lcd_cursor(0,0);


cap1166_leds(0);

for (i=0 ; i<=5 ; i++)
{
led_state(i,1);
}

for (i=0 ; i<=5 ; i++)
{
led_state(i,0);
}

cap1166_polarity(3);
cap1166_leds(21);

led_intensity(0,1);

for (i=0 ; i<=5 ; i++)
{
l=led_get_state(i);
p=led_get_polarity(i);
printf("LED %i : State - %i ; Polarity = %i\n",i,l,p);
}


}
