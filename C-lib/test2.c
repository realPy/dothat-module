/* test prog */

#include <stdlib.h>
#include <stdio.h>

#include "dothat.h"

int main()
{

int LED[5][2];
int i,j;
backlight_rgb(128,128,128);

lcd_clear();

lcd_cursor(1,0);

lcd_cursor_pos(0,0);
lcd_text("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz");

sleep(1);

lcd_clear();

lcd_text_line(1,"Some Text");
lcd_text_line(0,"012345678901234567890");

}
