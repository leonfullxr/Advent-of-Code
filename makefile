###############################################################################
# makefile
###############################################################################

SHELL := /usr/bin/bash
.ONESHELL:

###############################################################################

dat: arg=$1

	mkdir Day$1
	cd Day$1
	touch input.txt
	touch Day$1.cpp


.SUFFIXES:
.PHONY: x, pc1, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors

x: monitor_em_exe
	./$<

pc1: prodcons1_su_exe
	./$<

%_exe: %.cpp scd.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $< scd.cpp

clean:
	rm -f *_exe
