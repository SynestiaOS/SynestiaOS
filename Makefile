SUBDIRS += Libraries/LibC \
	Board/RaspberryPi3 \
	Kernel 

include Makefile.subdir

all: subdirs