.PHONY: clean

all: mini-basic.rom

%.bin: %.hex
	objcopy --input-target=ihex --output-target=binary $< $@

mini-basic.rom: e0001-bank0.bin e0001-bank1.bin e0002-bank0.bin e0002-bank1.bin
	cat $^ > $@
	truncate -s 16K $@

clean:
	rm -f *.bin mini-basic.rom
