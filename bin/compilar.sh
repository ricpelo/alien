#!/bin/sh

cd Alpha_pack/ZIPI_NG
./compilar-zipi.sh
cd ../..
front alien alien.inf $* +include_path=,lib,Alpha_pack,Alpha_pack/ZIPI_NG,InformATE610_git
meta.sh

