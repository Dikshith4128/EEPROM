# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

CC=gcc
CFLAGS=-Wall -std=gnu99 -O3

EEPROM_PROFILE ?= WL8
include eeprom.mk

CPPFLAGS=$(EEPROM_DEFINES)
LDFLAGS=
OBJECTS=main.o eeprom.o
SOURCESS=$(OBJECTS:.o=.c)
EXECUTABLE=main


all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.c) $(OBJECTS) -o $@ $(LDFLAGS)

rebuild: clean all
