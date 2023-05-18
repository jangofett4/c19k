#!/bin/sh

mkdir -p obj bin iso
git submodule update
cp ./limine/limine-cd-efi.bin iso
cp ./limine/limine-cd.bin iso
cp ./limine/limine.sys iso