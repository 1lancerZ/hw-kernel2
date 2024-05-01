ifneq ($(KERNELRELEASE),)
	obj-m := module1.o module2.o module3.o module4.o
else
	KERNELDIR ?= /root/kernel
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY:clean
clean:
	-rm *.mod.c *.o *.order *.symvers *.ko
