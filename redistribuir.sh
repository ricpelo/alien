#!/bin/sh

# Para Windows:
cp alien.blb  /media/sda1/Documents\ and\ Settings/Ricardo/Mis\ documentos/Redistribuir\ Gargoyle/Empaquetar/Instalador\ EE/
cp garglk.ini /media/sda1/Documents\ and\ Settings/Ricardo/Mis\ documentos/Redistribuir\ Gargoyle/Empaquetar/Instalador\ EE/
cp Redist/*   /media/sda1/Documents\ and\ Settings/Ricardo/Mis\ documentos/Redistribuir\ Gargoyle/Empaquetar/Instalador\ EE/

# Para Linux:
cp Redist/cover.jpg         ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/doc/alphaaventuras-alien-ee/
cp Redist/holocubo.pdf      ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/doc/alphaaventuras-alien-ee/
cp Redist/instrucciones.pdf ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/doc/alphaaventuras-alien-ee/
cp Redist/copyright         ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/doc/alphaaventuras-alien-ee/
cp Redist/copyright         ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/debian/
cp Redist/README            ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/doc/alphaaventuras-alien-ee/
cp Redist/FAQ               ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/doc/alphaaventuras-alien-ee/
cp alien.blb                ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/games/alphaaventuras-alien-ee/
cp garglk.ini               ~/IF/Empaquetar/Alien_EE/alphaaventuras-alien-ee_081124/usr/share/games/alphaaventuras-alien-ee/

# Multiplataforma:
cp alien.blb        ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp garglk.ini       ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp Redist/*.url     ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp doc/COPYING      ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp Redist/copyright ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp Redist/cover.jpg ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp Redist/INSTALL   ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp Redist/FAQ       ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/
cp Redist/*.pdf     ~/IF/Empaquetar/Alien_EE/ZIP/Alien_EE/

# Dropbox:
cp alien.blb  ~/Dropbox/Public
cp garglk.ini ~/Dropbox/Public

