
SUM ?= 0 

ifeq ($(CHECKSUM), y)
  CFLAGS += -DCHECKSUM
endif

all:
	gcc $(CFLAGS) -o monitor monitor.c
	./monitor $(SUM)

clean:
	rm -rf monitor
