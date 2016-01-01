/* C version of dothat-module sysfs functions

cap1166 interface

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

void cap1166_blink(unsigned int leds);
unsigned int cap1166_get_blink(void);
void cap1166_blink_rate(unsigned int rate);
unsigned int cap1166_get_blink_rate(void);
void cap1166_graph_bar(unsigned int level);
void cap1166_graph_bar_reverse(unsigned int level);
void cap1166_leds(unsigned int leds);
unsigned int cap1166_get_leds(void);
void cap1166_polarity(unsigned int leds);
unsigned int cap1166_get_polarity(void);
void cap1166_luminosity(unsigned int level);
