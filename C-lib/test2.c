/* test prog */

#include <stdlib.h>
#include <stdio.h>

#include "dothat.h"

int main()
{

int LED[6][3];
int i,j;
/*
backlight_rgb(255,0,0);
sleep(1);
backlight_rgb(0,255,0);
sleep(1);
backlight_rgb(0,0,255);
sleep(1);
backlight_rgb(128,128,128);
sleep(1);
backlight_rgb(0,0,0);
for (i=0 ; i<=5; i++)
{
sleep(1);
backlight_led_rgb(i,i*50, (i*20), (5-i)*50);
}

sleep(1);
*/
backlight_rgb(0,0,0);
sleep(1);

for (i=0 ; i<=5 ; i++)
 for (j=0 ; j<=2 ; j++)
  {
   LED[i][j]= (6-i)*(j+1)*25;
   printf("%i %i %i\n",i,j,LED[i][j]);

  }

backlight_array(LED);

sleep(1) ;

lcd_contrast(2);
sleep(1) ;
lcd_contrast(70);
sleep(1);
lcd_contrast(-1);

lcd_clear();

lcd_cursor(1,0);

lcd_cursor_pos(2,2);
lcd_text("Gunge gunge");


}
