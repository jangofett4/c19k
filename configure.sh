#!/bin/sh

mkdir -p obj bin iso
git submodule init
git submodule update
cd limine
make
cd ..
cp ./limine/limine-cd-efi.bin iso
cp ./limine/limine-cd.bin iso
cp ./limine/limine.sys iso
