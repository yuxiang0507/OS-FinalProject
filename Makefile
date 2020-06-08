obj-m += linear.o
obj-m += dfs.o
# obj-m 指定最後要建立的 .ko 檔是以哪些 .o 檔構成的。

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	# -C 是指定 Makefile 的位置

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
