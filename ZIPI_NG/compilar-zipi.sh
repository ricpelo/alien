#!/bin/sh

echo "Compilando ZIPI..."
rm -f alien.ztm~
LANG=C awk -f zipi.awk alien.ztm > Pistas.h
#cp -f Pistas.h ..
#cd ..
#ln -sf ZIPI_NG/Pistas.h .
#cd ..
#./compilar.sh

