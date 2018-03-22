obj-m += chardriver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) testCharModeDriver.c -o test
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm test
