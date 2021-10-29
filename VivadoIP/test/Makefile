
VERSION_GIT_REPO := $(shell git describe --abbrev=6 --dirty --always --tags)

CC=gcc
SRC_DIR=../drivers/fw_version_id/src
CFLAGS=-I../drivers/fw_version_id/src/ -DVERSION_GIT_REPO=\"$(VERSION_GIT_REPO)\" -Wno-int-to-pointer-cast
OBJECTS = fw_version_id.o main.o

default: testapp

#%.o: %.c $(HEADERS)
#		gcc -c $< -o $@

fw_version_id.o: $(SRC_DIR)/fw_version_id.c $(SRC_DIR)/fw_version_id.h 
		$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c 
		$(CC) $(CFLAGS) -c $< -o $@

testapp: $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
		-rm -f $(OBJECTS)
		-rm -f testapp

.PHONY: fw_version_id.o
