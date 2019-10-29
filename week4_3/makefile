# Made by Youri de Vor
#
# Improved makefile which builds and runs the target lzdecompressortoasm
.PHONY: run clean

run: compressed.asm

clean:
	rm lzcompressortoasm compressed.asm

lzcompressortoasm:
	g++ *.cpp *.hpp -o lzcompressortoasm

compressed.asm: lzcompressortoasm
	./lzcompressortoasm
