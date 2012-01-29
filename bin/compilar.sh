#!/bin/sh

cd ZIPI_NG
./compilar-zipi.sh
cd ..
front alien alien.inf $* +language_name=Spanish +include_path=,lib,INFSP6,InformLibrary611,Alpha_Pack,Damusix,SGW+DMX_NG,ZIPI_NG
meta.sh

