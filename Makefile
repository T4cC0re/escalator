obj-m+=escalator.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean

install:
	cp escalator.ko /lib/modules/$(shell uname -r)
	depmod -a
