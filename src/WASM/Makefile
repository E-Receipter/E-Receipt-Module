PREFIX 	=
CC 	= $(PREFIX)emcc
LCC = $(PREFIX)gcc
CFLAGS	= -O2 -std=c11

TARGET = build/jabcode.js

OBJECTS := $(patsubst ../jabcode/src/jabcode/%.c,objects/%.o,$(wildcard ../jabcode/src/jabcode/*.c))
LOBJECTS := $(patsubst ../jabcode/src/jabcode/%.c,../jabcode/src/jabcode/%.o,$(wildcard ../jabcode/src/jabcode/*.c))
$(TARGET): $(OBJECTS) bindings.c
	$(CC) -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include $(CFLAGS) -s WASM=1 -s "EXPORTED_FUNCTIONS=@exported.json" $(OBJECTS) bindings.c -o $@

$(OBJECTS): objects/%.o: ../jabcode/src/jabcode/%.c
	$(CC) -c -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include $(CFLAGS) $< -o $@

gcc-build: bindings.c
	$(LCC) -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include $(LOBJECTS) $(CFLAGS) -ltiff -lpng16 -lz -lm bindings.c -o build/test.out

clean:
	rm -f $(TARGET) $(OBJECTS)
