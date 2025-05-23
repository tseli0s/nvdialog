# Makefile for libnvdialog
# Unless you're building on older GNU/Linux distributions, you probably don't
# want to use this Makefile. Instead, you're advised to use the CMake script which
# is much more reliable and maintainable.

CC=gcc
SRC=src/*.c src/backend/gtk/*.c src/backend/sandbox/*.c
PUBHEADER=include/*/*
CFLAGS=-Wall -Wextra -O3 -s -Wno-unused-parameter -fstack-protector-all -fPIC -shared -Iinclude/ -Ivendor/ -Isrc/impl/ -DNVD_SANDBOX_SUPPORT=1
OUTFILE=libnvdialog.so
EXFLAGS=`pkg-config --libs --cflags gtk+-3.0`
NVDIALOG_MAXBUF=4096

all: $(SRC) $(PUBHEADER)
	$(CC) $(SRC) -o $(OUTFILE) $(CFLAGS) $(EXFLAGS) -DNVDIALOG_MAXBUF=$(NVDIALOG_MAXBUF)
	@echo "Finished, run 'make install' as root to install the library."

install: $(OUTFILE) $(PUBHEADER)
	@[ -d /usr/include/nvdialog ] || mkdir /usr/include/nvdialog
	@cp $(PUBHEADER) /usr/include/nvdialog/
	@cp $(OUTFILE)   /usr/lib
	@cp $(OUTFILE)   /usr/lib/$(OUTFILE).2 # Just to avoid compatibility issues.
	@echo "Successful."

clean: $(OUTFILE) build/
	@rm -rv $(OUTFILE) build/ && echo "Done."
