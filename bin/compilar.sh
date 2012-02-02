#!/bin/sh

cd ZIPI_NG
./compilar-zipi.sh
cd ..
front alien alien.inf $* +include_path=,lib,InformATE610_git,Alpha_Pack,ZIPI_NG
meta.sh

