/* C version of dothat-module sysfs functions

st7036 interface

Copyright (c) P. Biggs 2015-2016

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, US

*/


extern void st7036_clear(void) ;
extern void st7036_cursor_on(int enable) ;
extern void st7036_cursor_blink(int enable) ;
extern void st7036_contrast(int contrast) ;
extern void st7036_cursor_position(int col, int row) ;
extern int st7036_get_cursor_position(void) ;
extern void st7036_lcd_buffer(char *string) ;
extern char * st7036_get_lcd_buffer(char *string,int i) ;
