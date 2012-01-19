#!/bin/sh
blc meta.blc meta.blb
bmerge meta.blb alien.blb alien.gblorb
rm alien.blb
mv alien.gblorb alien.blb

