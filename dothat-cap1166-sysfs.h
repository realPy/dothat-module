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

#ifndef DOTHATCAP1166SYSFS_H
#define DOTHATCAP1166SYSFS_H

#include <linux/kernel.h>
#include <linux/fs.h> 

void cap1166_init_sysfs(struct class *s_pDeviceClass,struct pcap1166 *data);
void cap1166_exit_sysfs(struct pcap1166 *data);

#endif
