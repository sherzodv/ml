
BIN_DIR = ../bin
TARGET = testml
TARGET_RELEASE = $(BIN_DIR)/$(TARGET)
TARGET_DEBUG = $(BIN_DIR)/$(TARGET)d
TARGET_WARNING = dummy
TARGET_SHAREDLIB = $(BIN_DIR)/lib$(TARGET).so
TARGET_STATICLIB = $(BIN_DIR)/lib$(TARGET).a
CFLAGS = 
CDEBUGFLAGS = -ggdb -pg -DDEBUG
CRELEASEFLAGS = -O3
CWARNINGFLAGS = -Wall -c
CSHAREDLIBFLAGS = -c -fPIC
CSTATICLIBFLAGS = -c
INCLUDE_DIR = .

HEADERS = mstring.h ustream.h lexer.h
SOURCES = main.c mstring.c ustream.c lexer.c
SRC = $(HEADERS) $(SOURCES)
OBJSRC = main.c ext/utf8proc/utf8proc.c mstring.c ustream.c lexer.c

debug: $(TARGET_DEBUG)
release: $(TARGET_RELEASE)
warnings: $(TARGET_WARNING)
shared: $(TARGET_SHAREDLIB)
static: $(TARGET_STATICLIB)
all: clean debug release shared static

clean:
	rm -f $(TARGET_DEBUG)
	rm -f $(TARGET_RELEASE)
	rm -f $(TARGET_SHAREDLIB)
	rm -f $(TARGET_STATICLIB)
	rm -f -r $(BIN_DIR)/include/*

$(TARGET_DEBUG): $(SRC) 
	cc $(CFLAGS) $(CDEBUGFLAGS) -o $(TARGET_DEBUG) $(OBJSRC) -I$(INCLUDE_DIR)

$(TARGET_RELEASE): $(SRC)
	cc $(CFLAGS) $(CRELEASEFLAGS) -o $(TARGET_RELEASE) $(OBJSRC) -I$(INCLUDE_DIR)

$(TARGET_WARNING): $(SRC)
	cc $(CFLAGS) $(CDEBUGFLAGS) $(CWARNINGFLAGS) $(OBJSRC) -I$(INCLUDE_DIR)

$(TARGET_SHAREDLIB): $(SRC)
	gcc $(CFLAGS) $(CRELEASEFLAGS) $(CSHAREDLIBFLAGS) $(OBJSRC) -I$(INCLUDE_DIR)
	mv *.o $(BIN_DIR)
	gcc -shared -Wl,-soname,$(TARGET_SHAREDLIB) -o $(TARGET_SHAREDLIB) $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.o
	mkdir -p $(BIN_DIR)/include
	rm -f $(BIN_DIR)/include/*
	cp *.h $(BIN_DIR)/include/

$(TARGET_STATICLIB): $(SRC)
	gcc $(CFLAGS) $(CRELEASEFLAGS) $(CSTATICLIBFLAGS) $(OBJSRC) -I$(INCLUDE_DIR)
	mv *.o $(BIN_DIR)
	ar -cvq $(TARGET_STATICLIB) $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.o
	mkdir -p $(BIN_DIR)/include
	rm -f $(BIN_DIR)/include/*
	cp *.h $(BIN_DIR)/include/

