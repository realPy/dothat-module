/* C version of dothat-module sysfs functions

cap1166 interface

 (c) P Biggs 2015

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

const char *f_blink=   "/sys/class/dothat/cap1166/blink";
const char *f_blink_rate=      "/sys/class/dothat/cap1166/blink_rate";
const char *f_graph_bar="/sys/class/dothat/cap1166/graph_bar";
const char *f_graph_bar_reverse="/sys/class/dothat/cap1166/graph_bar_reverse";
const char *f_leds="/sys/class/dothat/cap1166/leds";
const char *f_luminosity=  "/sys/class/dothat/cap1166/luminosity";
const char *f_polarity=  "/sys/class/dothat/cap1166/polarity";

void cap1166_blink(unsigned int leds)
{
int fd;

fd=open(f_blink, O_WRONLY | O_APPEND); 

if (fd>0) {
		dprintf(fd,"%u",leds);
	close(fd);
	};
}

void cap1166_blink_rate(unsigned int rate)
{
int fd;

fd=open(f_blink_rate, O_WRONLY | O_APPEND); 

if (fd>0) {
		dprintf(fd,"%u",rate);
	close(fd);
	};
}

void cap1166_graph_bar(unsigned int level)
{
int fd;

fd=open(f_graph_bar, O_WRONLY | O_APPEND); 

if (fd>0) {
		dprintf(fd,"%u",level);
	close(fd);
	};
}

void cap1166_graph_bar_reverse(unsigned int level)
{
int fd;

fd=open(f_graph_bar_reverse, O_WRONLY | O_APPEND); 

if (fd>0) {
		dprintf(fd,"%u",level);
	close(fd);
	};
}

void cap1166_leds(unsigned int leds)
{
int fd;

fd=open(f_leds, O_WRONLY | O_APPEND); 

if (fd>0) {
		dprintf(fd,"%u",leds);
	close(fd);
	};
}

unsigned int cap1166_get_leds(void)
{
int fd;
unsigned int v;
char s[20];

v=0;

fd=open(f_leds, O_RDONLY); 

if (fd>0) {
		read(fd,s, sizeof s);
	close(fd);
	sscanf(s,"%i",&v);
	};

return v;
}

void cap1166_polarity(unsigned int leds)
{
int fd;

fd=open(f_polarity, O_WRONLY | O_APPEND); 

if (fd>0) {
	dprintf(fd,"%u",leds);
	close(fd);
	};
}

unsigned int cap1166_get_polarity(void)
{
int fd;
unsigned int v;
char s[20];
int n;

v=0;

fd=open(f_polarity, O_RDONLY); 

if (fd>0) {
	n=read(fd,s, sizeof s);
	close(fd);
	sscanf(s,"%i",&v);
	};

return v;
}

void cap1166_luminosity(unsigned int level)
{
int fd;

fd=open(f_luminosity, O_WRONLY | O_APPEND); 

if (fd>0) {
		dprintf(fd,"%u",level);
	close(fd);
	};
}
