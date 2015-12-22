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

#ifndef DOTHATSN3218SYSFS_H
#define DOTHATSN3218SYSFS_H


#include <linux/kernel.h>
#include <linux/fs.h> 

void sn3218_init_sysfs(struct class *s_pDeviceClass,struct psn3218 *data);
void sn3218_exit_sysfs(struct psn3218 *data);

#endif