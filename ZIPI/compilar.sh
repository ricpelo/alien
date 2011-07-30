#!/bin/sh

rm -f alien.ztm~
LANG=C awk -f zipi.awk alien.ztm > Pistas.h
cp -f Pistas.h ..

cd ..
./compilar.sh

