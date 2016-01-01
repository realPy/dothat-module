/*

dothat.h

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

void backlight_rgb(int, int, int);
void backlight_led_rgb(int, int, int, int);
void backlight_array(int [5][2]);
void lcd_clear(void);
void lcd_contrast(int);
void lcd_cursor(int, int);
void lcd_cursor_pos(int,int);
void lcd_text(char *);
void lcd_text_line(int , char *);
void lcd_text_lines(char *, char *, char *);
void graph_bar(int, int);
void led_intensity(int, int);
void led_state(int, int);
void led_polarity(int, int);
int led_get_state(int);
int led_get_polarity(int);
void led_states(int, int, int, int, int, int);
void led_polarities(int, int, int, int, int, int);
void led_breathe(int, int);
void led_breathes(int, int, int, int, int, int);
void led_breathe_rate(int);
