#! /usr/bin/env bash

set -ex

make clean
pushd zloader.ls1b
make clean
make cfg 
make tgt=rom
popd

loongarch32r-linux-gnusf-objdump -d zloader.ls1b/gzrom > gzrom.S
loongarch32r-linux-gnusf-objdump -d Targets/LS1B/compile/ls1b/pmon > pmon.S