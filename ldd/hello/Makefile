ifneq ($(KERNELRELEASE),)
        obj-m := hello.o
else
        #KERNELDIR ?= /usr/src/kernels/$(shell uname -r)/build
        KERNELDIR ?= /usr/src/kernels/3.10.0-514.26.2.el7.x86_64

        PWD := $(shell pwd)
default:
        $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
