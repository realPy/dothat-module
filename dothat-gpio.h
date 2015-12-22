/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		GPIO support header
 */

#ifndef DOTHATGPIO_H
#define DOTHATGPIO_H	




#define RPI2

#ifdef RPI2
#define PERI_BASE        0x3F000000
#else
#define PERI_BASE        0x20000000
#endif

#define DOTHATGPIO_BASE                (PERI_BASE + 0x200000) /* GPIO controller */

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define GPIO_READ(g)  *(gpio + 13) &= (1<<(g))

#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)
#define GPIO_CLR *(gpio+10)


extern volatile unsigned *gpio;
int setupGPIO(void);
void unsetupGPIO(void);

#endif