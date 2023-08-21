# NOP-PMON

A `loongarch32r` PMON bootloader used in NSCSCC 2023 for [NOP-Core](https://github.com/NOP-Processor/NOP-Core). This is adapted from the PMON released in [Chiplab](https://gitee.com/loongson-edu/chiplab).

## Build

Configure `loongarch32r-linux-gnusf-` toolchain in `$PATH`, then run

```bash
./build.sh
```

then write `zloader.ls1b/gzrom.bin ` into SPI Flash to boot PMON.