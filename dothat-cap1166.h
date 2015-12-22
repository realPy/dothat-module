 /*  *
 *  * Author: Manuel BARRAUD <manuel.barraud@me.com>
 *  *
 *  * This file is subject to the terms and conditions of version 2 of
 *  * the GNU General Public License.  See the file COPYING in the main
 *  * directory of this archive for more details.
 *
 *		CAP1166 support header
 */

#ifndef DOTHATCAP1166_H
#define DOTHATCAP1166_H

#include <linux/workqueue.h>
#include <linux/i2c.h>
#include <linux/timer.h>
#include <linux/input.h>


#define NUM_LEDS	6
#define STEP_DUTY	16

#define CAP1166_R_MAIN_CONTROL 0x0
#define CAP1166_R_GENERAL_STATUS 	  0x02
#define CAP1166_R_INPUT_STATUS 	  0x03
#define CAP1166_R_NOISE_STATUS	0xA

#define CAP1166_R_INPUT_1_DELTA    0x10
#define CAP1166_R_INPUT_2_DELTA    0x11
#define CAP1166_R_INPUT_3_DELTA    0x12
#define CAP1166_R_INPUT_4_DELTA    0x13
#define CAP1166_R_INPUT_5_DELTA    0x14
#define CAP1166_R_INPUT_6_DELTA    0x15
#define CAP1166_R_INPUT_7_DELTA    0x16
#define CAP1166_R_INPUT_8_DELTA    0x17
#define CAP1166_R_SENSITIVITY      0x1F

#define CAP1166_R_GENERAL_CONFIG   0x20	
#define CAP1166_R_INPUT_ENABLE 0x21
#define CAP1166_R_SAMPLING_CONFIG  0x24
#define CAP1166_R_CALIBRATION 0x26
#define CAP1166_R_INTERRUPT_EN 0x27
#define CAP1166_R_REPEAT_ENABLE 0x28
#define CAP1166_R_RECALIBRATION_REGISTER 0x2F

#define CAP1166_R_INPUT_1_THRESH   0x30
#define CAP1166_R_INPUT_2_THRESH   0x31
#define CAP1166_R_INPUT_3_THRESH   0x32
#define CAP1166_R_INPUT_4_THRESH   0x33
#define CAP1166_R_INPUT_5_THRESH   0x34
#define CAP1166_R_INPUT_6_THRESH   0x35
#define CAP1166_R_INPUT_7_THRESH   0x36
#define CAP1166_R_INPUT_8_THRESH   0x37

#define CAP1166_R_CONFIGURATION2   0x44

#define CAP1166_R_LED_POLARITY	0x73
#define CAP1166_LED_OUTPUT_CON	0x74
#define CAP1166_LED_DIRECT_DUTY	0x93
#define CAP1166_LED_BEHAVIOR1	0x81
#define CAP1166_LED_BEHAVIOR2	0x82
#define CAP1166_LED_BREATH_PERIOD	0x86

#define CAP1166_PRODUCT_ID	0xFD



typedef enum  {
        CAP1166_STATE_NONE,
		CAP1166_STATE_PRESS,
		CAP1166_STATE_HOLD,
		CAP1166_STATE_RELEASE,
		CAP1166_STATE_PRESSED = 128
} CAP1166_STATE;


extern char *cap1166_state_str[];

int cap1166_graph_off(struct i2c_client *client);
u8 cap1166_get_ProductID(struct i2c_client *client);


struct pcap1166 {
    struct i2c_client      *client;
	struct device *sysfsdevice;
    char phys[32];
	struct mutex lock;
	unsigned char willUnload;
    struct work_struct      work;
	struct timer_list      timer;
	u8 needCheckRelease;
	CAP1166_STATE		buttonState[8];
	struct input_dev *idev;
	u8 graph_bar_value;
	u8 leds_blink;
};

void cap1166_touch_init(struct pcap1166 *data);
void cap1166_touch_detach(struct pcap1166 *data);
int cap1166_set_progress_bar(struct i2c_client *client,u8 value);
int cap1166_set_progress_bar_reverse(struct i2c_client *client,u8 value);

int cap1166_graph_set_leds(struct i2c_client *client,u8 leds);
u8 cap1166_graph_get_leds(struct i2c_client *client);

int cap1166_graph_set_polarity(struct i2c_client *client,u8 leds);
u8 cap1166_graph_get_polarity(struct i2c_client *client);

int cap1166_graph_set_leds_luminosity(struct i2c_client *client,u8 duty);
u8 cap1166_graph_get_leds_luminosity(struct i2c_client *client);

void cap1166_graph_set_leds_blink(struct i2c_client *client,u8 leds);
int cap1166_graph_set_breath_period(struct i2c_client *client,u8 period);
u8 cap1166_graph_get_breath_period(struct i2c_client *client);

#endif