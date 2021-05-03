PREFIX 	=
CC 	= $(PREFIX)gcc
AR 	= $(PREFIX)ar
RANLIB	= $(PREFIX)ranlib
CFLAGS	= -O2 -std=c11

TARGET = build/libRG.a

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

$(TARGET): $(OBJECTS)
	$(AR) cru $@ $?
	$(RANLIB) $@

$(OBJECTS): %.o: %.c
	$(CC) -c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) $< -o $@

test: $(TARGET)
	$(CC) tests/compress.c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) -L./build -lRG -L../jabcode/src/jabcode/build -ljabcode -lpng16 -lz -ltiff -lm -o ./tests/compress.out
	$(CC) tests/encrypt.c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) -L./build -lRG -L../jabcode/src/jabcode/build -ljabcode -lpng16 -lz -ltiff -lm -o ./tests/encrypt.out
	$(CC) tests/jabenc.c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) -L./build -lRG -L../jabcode/src/jabcode/build -ljabcode -lpng16 -lz -ltiff -lm -o ./tests/jabenc.out
	$(CC) tests/jabdec.c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) -L./build -lRG -L../jabcode/src/jabcode/build -ljabcode -lpng16 -lz -ltiff -lm -o ./tests/jabdec.out
	$(CC) tests/decrypt.c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) -L./build -lRG -L../jabcode/src/jabcode/build -ljabcode -lpng16 -lz -ltiff -lm -o ./tests/decrypt.out
	$(CC) tests/decompress.c -I. -I./include -I../jabcode/src/jabcode/include $(CFLAGS) -L./build -lRG -L../jabcode/src/jabcode/build -ljabcode -lpng16 -lz -ltiff -lm -o ./tests/decompress.out
	cd tests && ./compress.out && ./encrypt.out && ./jabenc.out && ./jabdec.out && ./decrypt.out && ./decompress.out

clean:
	rm -f $(TARGET) $(OBJECTS) $(TEST_TARGET)
