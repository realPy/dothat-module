/*
 *  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		GPIO support
 */

#include "dothat-gpio.h"
#include <asm/io.h>
volatile unsigned *gpio;


int setupGPIO(void)
{

 if ((gpio = ioremap(DOTHATGPIO_BASE,0xB0)) == NULL) {
        pr_err("io remap failed\n");
        return -EBUSY;
    }

return 0;
}


void unsetupGPIO(void) 
{

 iounmap(gpio);

} 

