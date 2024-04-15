.PHONY: clean

all: mini-basic.rom

%.bin: %.hex
	objcopy --input-target=ihex --output-target=binary $< $@

e0001.bin: e0001-bank0.bin e0001-bank1.bin
	cat $^ > $@

e0002.bin: e0002-bank0.bin e0002-bank1.bin
	cat $^ > $@

mini-basic.bin: e0001.bin e0002.bin
	cat $^ > $@

mini-basic.rom: mini-basic.bin
	cp -f $< $@
	truncate -s 16K $@

clean:
	rm -f *.bin mini-basic.rom
