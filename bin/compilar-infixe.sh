#!/bin/sh

cd Alpha_pack/ZIPI_NG
./compilar-zipi.sh
cd ../..
bres alien.res alien.blc alien.bli
inform-infixe -D -X $* \$MAX_OBJ_PROP_COUNT=100 \$MAX_LABELS=2000 +include_path=,lib,Alpha_pack,Alpha_pack/ZIPI_NG,InformATE610_git alien.inf
blc alien.blc alien.blb
meta.sh

