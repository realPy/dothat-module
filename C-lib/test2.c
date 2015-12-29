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

lcd_cursor(0,0);

lcd_cursor_pos(0,0);
lcd_text("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz");

sleep(1);
backlight_rgb(128,0,128);

lcd_clear();

lcd_text_line(1,"Some Text");
lcd_text_line(0,"012345678901234567890");

sleep(1);

backlight_rgb(0,128,128);

lcd_text_lines("First line", "  second", "Line the third");

sleep(1);

graph_bar(0,25);
sleep(1);
graph_bar(1,25);


}
