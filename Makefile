# Compiler to use. gcc is recommended but any compiler implementing the C11 standard should work.
# clang is a good alternative on some platforms.
CC       ?= gcc
PKGCONF  := pkg-config
CFLAGS   := -std=c11 -Wall -Wextra -Wconversion -Winline -Werror=format -Werror=format-security -Werror=write-strings
CFLAGS   += -DNVDIALOG_MAXBUF=4096 -DNVD_EXPORT_SYMBOLS
CFLAGS   += $(shell $(PKGCONF) --cflags gtk+-3.0)
LDFLAGS  := $(shell $(PKGCONF) --libs gtk+-3.0)
INCLUDES := -Iinclude -Isrc/impl -Ivendor

# Set this to 0 to build nvdialog as a dynamic library instead.
# (If it's one, nvdialog will be built as a static library)
BUILD_STATIC ?= 1

ifeq ($(BUILD_STATIC),1)
    TARGET := libnvdialog.a
    CFLAGS += -DNVD_STATIC_LINKAGE
else
    TARGET := libnvdialog.so
    CFLAGS += -fPIC
endif

# Installation directory. /usr/local works for most people but you can also use /usr
# if you want or install it under ~/.local.
INSTALLPREFIX ?= /usr/local
LIBDIR   := $(INSTALLPREFIX)/lib
INCDIR   := $(INSTALLPREFIX)/include/nvdialog
DIALOGDIR:= $(INCDIR)/dialogs

COMMON_SRC := $(wildcard src/*.c)
GTK_SRC    := $(wildcard src/backend/gtk/*.c)
SRC        := $(COMMON_SRC) $(GTK_SRC)
OBJDIR     := build
OBJ        := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJ)
ifeq ($(BUILD_STATIC),1)
	ar rcs $@ $(OBJ)
else
	$(CC) -shared -o $@ $(OBJ) $(LDFLAGS)
endif

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

install:
	mkdir -p $(LIBDIR)
	mkdir -p $(INCDIR)
	mkdir -p $(DIALOGDIR)
	cp $(TARGET) $(LIBDIR)/
	cp include/nvdialog_*.h $(INCDIR)/
	cp include/dialogs/nvdialog_*.h $(DIALOGDIR)/

uninstall:
	rm -f $(LIBDIR)/$(TARGET)
	rm -rf $(INCDIR)

clean:
	rm -rfv $(OBJDIR) $(TARGET)
