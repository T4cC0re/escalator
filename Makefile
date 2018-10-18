KERNEL?=$(shell uname -r)
MODULE_DIR?=/lib/modules/$(KERNEL)
BIN_DIR?=/usr/local/bin

obj-m+=escalator.o

all:
	make -C $(MODULE_DIR)/build/ M=$(PWD) modules
clean:
	make -C $(MODULE_DIR)/build/ M=$(PWD) clean
install:
	cp escalator.ko $(MODULE_DIR)/
	depmod -a
	cp escalator $(BIN_DIR)/
