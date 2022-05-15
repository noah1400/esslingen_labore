# Makefile for module mod_kmalloc.c

obj-m =
obj-m += mod_kmalloc.o

KVERSION = $(shell uname -r)

modules all:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(shell pwd) clean