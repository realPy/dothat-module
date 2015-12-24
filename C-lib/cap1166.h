/* C version of dothat-module sysfs functions

cap1166 interface

 (c) P Biggs 2015

*/

void cap1166_blink(unsigned int leds);
void cap1166_blink_rate(unsigned int rate);
void cap1166_graph_bar(unsigned int level);
void cap1166_graph_bar_reverse(unsigned int level);
void cap1166_leds(unsigned int leds);
void cap1166_polarity(unsigned int leds);
void cap1166_luminosity(unsigned int level);
