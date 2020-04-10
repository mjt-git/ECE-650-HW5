ifeq ($(KERNELRELEASE),)

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: build clean

all: sneaky_process build

sneaky_process: sneaky_process.c
	gcc -O3 -o sneaky_process sneaky_process.c

build:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.order *.symvers *.ko *.mod.c sneaky_process
else

$(info Building with KERNELRELEASE = ${KERNELRELEASE})
obj-m :=    sneaky_mod.o

endif
