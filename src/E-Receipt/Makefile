PREFIX 	=
CC 	= $(PREFIX)gcc
AR 	= $(PREFIX)ar
RANLIB	= $(PREFIX)ranlib
CFLAGS	= -O2 -std=c11

TARGET = build/libRG.a

TEST_SOURCE = tests/main.c
TEST_TARGET = ./tests/test.out

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

$(TARGET): $(OBJECTS)
	$(AR) cru $@ $?
	$(RANLIB) $@

$(OBJECTS): %.o: %.c
	$(CC) -c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) $< -o $@

test: $(TARGET)
	$(CC) $(TEST_SOURCE) -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS)  -L./build -lRG -o $(TEST_TARGET)
	$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS) $(TEST_TARGET)
