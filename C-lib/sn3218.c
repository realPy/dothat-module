/* C version of dothat-module sysfs functions

sn3218 interface

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
