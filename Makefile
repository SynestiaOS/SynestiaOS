SUBDIRS += Libraries/LibC \
	Board/RaspberryPi3 \
	Kernel
#	Tests/os_test

include Makefile.subdir

all: subdirs
