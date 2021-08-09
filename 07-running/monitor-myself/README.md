
# Calculating checksum of my code and protect it


	$ make
	gcc  -o monitor monitor.c
	./monitor 0 
	checksum is 63708
	who touched me!

	$ make SUM=63708
	gcc  -o monitor monitor.c
	./monitor 63708
	checksum is 63708
	I'm good...

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
