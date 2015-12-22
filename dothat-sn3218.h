 /*  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		SN3218 support header
 */

#ifndef DOTHATSN3218_H
#define DOTHATSN3218_H

#include <linux/i2c.h>

struct psn3218 {
  //  struct mutex lock;
    struct i2c_client      *client;
	struct device *sysfsdevice;
    u8 state;
    u32 mask;
    unsigned char ledColor[18];

};

#define SN3218_CMD_ENABLE_OUTPUT 0x0
#define SN3218_CMD_ENABLE_LEDS 0x13
#define SN3218_CMD_UPDATE 0x16
#define SN3218_CMD_SET_PWM_VALUES 0x1
#define SN3218_CMD_RESET 0x17


int sn3218_enable(struct i2c_client *client,u8 state);
int sn3218_update(struct i2c_client *client);
int sn3218_enable_leds(struct i2c_client *client,u32 bits);
int sn3218_output(struct i2c_client *client,u8 *ledColor);
int sn3218_output_monocolor(struct psn3218 *pData,u8 *monoColor);

//extern u8 gamma_table[];	

#endif
