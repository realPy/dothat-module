/* C version of dothat-module sysfs functions

sn3218 interface

 (c) P Biggs 2015

*/


extern void st7036_clear(void) ;
extern void st7036_cursor_on(int enable) ;
extern void st7036_cursor_blink(int enable) ;
extern void st7036_contrast(int contrast) ;
extern void st7036_cursor_position(int col, int row) ;
extern int st7036_get_cursor_position(void) ;
extern void st7036_lcd_buffer(char *string) ;
extern char * st7036_get_lcd_buffer(char *string,int i) ;
