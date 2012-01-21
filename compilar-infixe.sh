#!/bin/sh

bres alien.res alien.blc alien.bli
inform-infixe -D -X $* \$MAX_OBJ_PROP_COUNT=100 \$MAX_LABELS=2000 alien.inf
blc alien.blc alien.blb

