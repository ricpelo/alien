
[Setup]
AppName=A·L·I·E·N
OutputBaseFilename=ALIEN_EE_180720
OutputDir=..
AppVerName=A·L·I·E·N: La aventura - Edición Especial (180720)
DefaultDirName={pf}\Juegos Conversacionales\A·L·I·E·N - La aventura (Edición Especial)
DefaultGroupName=Juegos Conversacionales\A·L·I·E·N - La aventura (Edición Especial)
UninstallDisplayIcon={app}\Desinstalar.exe
Compression=lzma
SolidCompression=true

[Languages]
Name: Spanish; MessagesFile: "compiler:Languages\Spanish.isl "

[Tasks]
Name: escritorio; Description: Crear un acceso directo en el escritorio; GroupDescription: Iconos adicionales:

[Files]
Source: alien.blb; DestDir: {app}
Source: alien.ico; DestDir: {app}
Source: Alien.url; DestDir: {app}
Source: Alpha_Aventuras.url; DestDir: {app}
Source: "CAAD Club de Aventuras AD.url"; DestDir: {app}
Source: CAAD.ico; DestDir: {app}
Source: copyright; DestDir: {app}
Source: COPYING; DestDir: {app}
Source: README.md; DestDir: {app}
Source: cover.jpg; DestDir: {app};
Source: libfreetype-6.dll; DestDir: {app}
Source: garglk.ini; DestDir: {app}
Source: gargoyle.exe; DestDir: {app}
Source: glulxe.exe; DestDir: {app}
Source: "GNU General Public License.txt"; DestDir: {app}
Source: holocubo.pdf; DestDir: {app};
Source: instrucciones.pdf; DestDir: {app}; Flags: isreadme
Source: Leame.ico; DestDir: {app}
Source: "Liberation License.txt"; DestDir: {app}
Source: "Libertine OFL.txt"; DestDir: {app}
Source: libgcc_s_sjlj-1.dll; DestDir: {app}
Source: libgarglk.dll; DestDir: {app}
Source: libjpeg-8.dll; DestDir: {app}
Source: libogg-0.dll; DestDir: {app}
Source: libpng16-16.dll; DestDir: {app}
Source: libvorbis-0.dll; DestDir: {app}
Source: libvorbisfile-3.dll; DestDir: {app}
Source: mikmod.dll; DestDir: {app}
Source: SDL.dll; DestDir: {app}
Source: "Gargoyle License.txt"; DestDir: {app}
Source: SDL_mixer.dll; DestDir: {app}
Source: SDL_sound.dll; DestDir: {app}
Source: smpeg.dll; DestDir: {app}
Source: Vídeo.url; DestDir: {app}
Source: zlib1.dll; DestDir: {app}

[Icons]
Name: {group}\Jugar a A·L·I·E·N - La aventura (Edición Especial); Filename: {app}\glulxe.exe; IconFilename: {app}\alien.ico; Parameters: alien.blb; WorkingDir: {app}\; IconIndex: 0; Comment: Juega a A·L·I·E·N - La aventura (Edición Especial)
Name: {group}\Instrucciones - Cómo jugar; Filename: {app}\instrucciones.pdf; Comment: Cómo jugar una aventura conversacional; IconFilename: {app}\Leame.ico; IconIndex: 0
Name: {group}\Holocubo (requiere contraseña); Filename: {app}\holocubo.pdf; Comment: Documento informativo (sólo puede abrirse con la contraseña correcta); IconFilename: {app}\alien.ico; IconIndex: 0
Name: {group}\Vídeo introductorio; Filename: {app}\Vídeo.url; Comment: Vídeo de introducción a la aventura, en YouTube; IconFilename: {app}\alien.ico; IconIndex: 0
Name: {group}\Visita la web del CAAD; Filename: {app}\CAAD Club de Aventuras AD.url; Comment: Visita la web del CAAD para participar en el mundo aventurero y resolver las dudas del juego en los foros; IconFilename: {app}\CAAD.ico; IconIndex: 0
Name: {group}\Visita la web de A·L·I·E·N; Filename: {app}\Alien.url; Comment: Visita la web de A·L·I·E·N; IconFilename: {app}\CAAD.ico; IconIndex: 0
Name: {group}\Visita la web de Alpha Aventuras; Filename: {app}\Alpha_Aventuras.url; Comment: Visita la web de Alpha Aventuras, el equipo creador de A·L·I·E·N; IconFilename: {app}\CAAD.ico; IconIndex: 0
Name: {userdesktop}\Jugar a A·L·I·E·N - La aventura (Edición Especial); Filename: {app}\glulxe.exe; IconFilename: {app}\alien.ico; Parameters: alien.blb; WorkingDir: {app}\; IconIndex: 0; Comment: Juega a A·L·I·E·N: La aventura - Edición Especial; Tasks: escritorio
Name: {group}\Desinstalar A·L·I·E·N - La aventura (Edición Especial); Filename: {uninstallexe}; Comment: Desinstala A·L·I·E·N - Esperamos que lo hayas disfrutado

[Dirs]
Name: {app}\

