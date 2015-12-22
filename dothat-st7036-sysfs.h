 /*  * Copyright 2015-2016
 *  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		SN3218 SYS FS support header
 */

#ifndef DOTHATST7036SYSFS_H
#define DOTHATST7036SYSFS_H


#include <linux/kernel.h>
#include <linux/fs.h> 

void st7036_init_sysfs(struct class *s_pDeviceClass,struct pst7036 *data);
void st7036_exit_sysfs(struct pst7036 *data);

#endif