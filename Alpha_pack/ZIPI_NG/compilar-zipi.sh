#!/bin/sh

echo "Compilando ZIPI..."
rm -f alien.ztm~
LANG=C awk -f zipi.awk alien.ztm > Pistas.h

