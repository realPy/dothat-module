/* test prog */

#include <stdlib.h>
#include <stdio.h>

#include "dothat.h"

int main()
{

int LED[5][2];
int i,j,l,p;
backlight_rgb(255,255,255);
sleep(1);
backlight_led_rgb(0,128,0,0);
sleep(1);
backlight_led_rgb(1,128,0,0);
sleep(1);
backlight_led_rgb(2,0,128,0);
sleep(1);
backlight_led_rgb(3,0,128,0);
sleep(1);
backlight_led_rgb(4,0,0,128);
sleep(1);
backlight_led_rgb(5,0,0,128);

sleep(1);
lcd_clear();

lcd_cursor(0,0);

lcd_text_lines("Hello World!","dothat C library","(c) P. Biggs");

cap1166_leds(0);

for (i=0 ; i<=5 ; i++)
{
led_state(i,1);
sleep(1);
}

for (i=0 ; i<=5 ; i++)
{
led_state(i,0);
sleep(1);
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

sleep(1);

led_polarities(0,0,0,0,0,0);
led_states(0,0,0,0,0,1);

led_breathe(1,500);
sleep(1);
led_breathe(2,1000);
sleep(1);
led_breathe(3,100);
sleep(2);
led_breathe(2,0);
sleep(1);
led_breathe_rate(4000);
led_breathes(1,0,1,0,1,0);


}
