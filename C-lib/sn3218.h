/* C version of dothat-module sysfs functions

sn3218 interface

 (c) P Biggs 2015

*/

extern void sn3218_enable(int) ;
extern void sn3218_lcd_set(unsigned char ,char *) ;
extern void sn3218_monocolor(char *) ;
extern void sn3218_lcd_raw(char *);
