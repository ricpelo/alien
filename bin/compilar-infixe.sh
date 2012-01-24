#!/bin/sh

cd ZIPI_NG
compilar-zipi.sh
cd ..
bres alien.res alien.blc alien.bli
inform-infixe -D -X $* \$MAX_OBJ_PROP_COUNT=100 \$MAX_LABELS=2000 +include_path=,lib,InformATE610_git,Alpha_Pack,Damusix,SGW+DMX_NG,ZIPI_NG alien.inf
blc alien.blc alien.blb

