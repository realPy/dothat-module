/* C version of dothat-module sysfs functions

sn3218 interface

 (c) P Biggs 2015

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

const char *f_enable=   "/sys/class/dothat/sn3218/enable";
const char *f_lcd=      "/sys/class/dothat/sn3218/lcd";
const char *f_monocolor="/sys/class/dothat/sn3218/monocolor";
const char *f_lcd_raw=  "/sys/class/dothat/sn3218/lcd_raw";

void sn3218_enable(int enable)
{
int fd;

fd=open(f_enable, O_WRONLY | O_APPEND); 

if (fd>0) {
	if (enable==0)
		dprintf(fd,"0") ;
	else
		dprintf(fd,"1");
	};
	close(fd);
}

void sn3218_lcd_set(unsigned char segment,char *value)
{
int fd;
fd=open(f_lcd,  O_WRONLY | O_APPEND);
if (fd>0) {
	dprintf(fd,"%i %s",segment,value);
	close(fd);
	}
}

void sn3218_monocolor(char *value)
{
int fd;
fd=open(f_monocolor,  O_WRONLY | O_APPEND);
if (fd>0) {
        dprintf(fd,"%s",value);
        close(fd);
        }
}

void sn3218_lcd_raw(char *value)
{
int fd,i,j;
fd=open(f_lcd_raw,  O_WRONLY | O_APPEND);
if (fd>0) {
	dprintf(fd,"%s",value);
	close(fd);
	}
}
