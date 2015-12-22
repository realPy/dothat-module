obj-m += dothat.o

dothat-objs := dothat-core.o dothat-st7036.o dothat-gpio.o dothat-sn3218.o dothat-sn3218-sysfs.o dothat-cap1166.o dothat-cap1166-sysfs.o dothat-st7036-sysfs.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make  -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
