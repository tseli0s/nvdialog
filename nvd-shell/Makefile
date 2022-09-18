CXX=clang++
CFLAGS=-Wall -Wextra -pedantic -fstrict-aliasing -lnvdialog -s -O3 -I../include/
SRCS=src/Main.cpp src/Dialogs.cpp src/CommandLine.cpp
OUTFILE=nvd-shell

all: $(SRCS)
	@$(CXX) -o $(OUTFILE) $(SRCS) $(CFLAGS)
	@echo "Done."

install: $(OUTFILE)
	@cp $(OUTFILE) /usr/bin/nvd-shell
	@echo "Done."

clean: $(OUTFILE)
	@rm -f $(OUTFILE)