PREFIX 	=
CC 	= $(PREFIX)emcc
LCC = $(PREFIX)gcc
CFLAGS	= -O3 -std=c11

TARGET = ../gh-pages/build/jabcode.js

OBJECTS := $(patsubst ../jabcode/src/jabcode/%.c,objects/%.o,$(wildcard ../jabcode/src/jabcode/*.c))
LOBJECTS := $(patsubst ../jabcode/src/jabcode/%.c,../jabcode/src/jabcode/%.o,$(wildcard ../jabcode/src/jabcode/*.c))
ER_OBJECTS := $(patsubst ../E-Receipt/%.c,objects/%.o,$(wildcard ../E-Receipt/*.c))
ER_LOBJECTS := $(patsubst ../E-Receipt/%.c,../E-Receipt/%.o,$(wildcard ../E-Receipt/*.c))
$(TARGET): $(OBJECTS) $(ER_OBJECTS) bindings.c
	$(CC) -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include -I../E-Receipt/ $(CFLAGS) -s WASM=1 -s ENVIRONMENT=worker -s MODULARIZE=1 -s "EXPORTED_FUNCTIONS=@exported.json" $(OBJECTS) $(ER_OBJECTS) bindings.c -o $@

$(OBJECTS): objects/%.o: ../jabcode/src/jabcode/%.c
	$(CC) -c -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include $(CFLAGS) $< -o $@

$(ER_OBJECTS): objects/%.o: ../E-Receipt/%.c
	$(CC) -c -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include -I../E-Receipt/ $(CFLAGS) $< -o $@

gcc-build: bindings.c
	$(LCC) -I../jabcode/src/jabcode/ -I../jabcode/src/jabcode/include -I../E-Receipt/ $(LOBJECTS) $(CFLAGS) -ltiff -lpng16 -lz -lm bindings.c -o build/test.out

clean:
	rm -f $(TARGET) $(OBJECTS)
