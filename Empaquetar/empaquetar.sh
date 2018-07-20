#!/bin/sh

VER=180720
BASE=alphaaventuras-alien-ee
SOURCE=${BASE}_${VER}
DEST=Alien_EE

rm -rf $DEST
mkdir $DEST

cp ../alien.blb $DEST
cp ../garglk.ini $DEST
cp ../doc/COPYING $DEST
cp ../Redist/copyright $DEST
cp ../Redist/Alien.url $DEST
cp ../Redist/CAAD\ Club\ de\ Aventuras\ AD.url $DEST
cp ../Redist/Alpha_Aventuras.url $DEST
cp ../Redist/holocubo.pdf $DEST
cp ../Redist/instrucciones.pdf $DEST
cp ../Redist/INSTALL $DEST
cp ../Redist/cover.jpg $DEST
cp ../Redist/Vídeo.url $DEST
cp ../Redist/FAQ $DEST
zip -r9 ${DEST}_${VER}.zip $DEST
rm -r $DEST

cp ../alien.blb                $SOURCE/usr/share/games/$BASE/
cp ../garglk.ini               $SOURCE/usr/share/games/$BASE/
cp ../Redist/copyright         $SOURCE/usr/share/doc/$BASE/
cp ../Redist/FAQ               $SOURCE/usr/share/doc/$BASE/
cp ../Redist/holocubo.pdf      $SOURCE/usr/share/doc/$BASE/
cp ../Redist/instrucciones.pdf $SOURCE/usr/share/doc/$BASE/
cp ../Redist/cover.jpg         $SOURCE/usr/share/doc/$BASE/
cp ../README.md                $SOURCE/usr/share/doc/$BASE/

cd $SOURCE
dpkg-buildpackage -uc -us -rfakeroot
cd ..
rm $SOURCE-1_amd64.buildinfo $SOURCE-1_amd64.changes $SOURCE-1.dsc $SOURCE-1.tar.gz
