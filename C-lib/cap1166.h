/* C version of dothat-module sysfs functions

cap1166 interface

 (c) P Biggs 2015

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
