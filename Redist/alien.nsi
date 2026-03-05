Name "A·L·I·E·N: La aventura - Edición Especial"
OutFile "ALIEN_EE_260305.exe"

InstallDir "$PROGRAMFILES\A·L·I·E·N - La aventura (Edición Especial)"
InstallDirRegKey HKCU "Software\ALIEN_EE" ""

RequestExecutionLevel admin

!include "MUI2.nsh"

!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "Spanish"

Section "Programa principal" SEC01

SetOutPath "$INSTDIR"

File "alien.blb"
File "alien.ico"
File "Alien.url"
File "Alpha_Aventuras.url"
File "CAAD Club de Aventuras AD.url"
File "CAAD.ico"
File "copyright"
File "COPYING"
File "README.md"
File "cover.jpg"
File "FAQ"
File "INSTALL"

File "GNU General Public License.txt"
File "holocubo.pdf"
File "instrucciones.pdf"
File "Leame.ico"

File "Liberation License.txt"
File "Libertine OFL.txt"

File /r "../../garglk/build/dist/*"

WriteUninstaller "$INSTDIR\Uninstall.exe"

WriteRegStr HKCU "Software\ALIEN_EE" "" $INSTDIR

CreateDirectory "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Jugar a A·L·I·E·N.lnk" \
"$INSTDIR\glulxe.exe" "alien.blb" "$INSTDIR\alien.ico"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Instrucciones.lnk" \
"$INSTDIR\instrucciones.pdf" "" "$INSTDIR\Leame.ico"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Holocubo.lnk" \
"$INSTDIR\holocubo.pdf"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Vídeo introductorio.lnk" \
"$INSTDIR\Vídeo.url"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Web CAAD.lnk" \
"$INSTDIR\CAAD Club de Aventuras AD.url"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Web A·L·I·E·N.lnk" \
"$INSTDIR\Alien.url"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Web Alpha Aventuras.lnk" \
"$INSTDIR\Alpha_Aventuras.url"

CreateShortcut "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)\Desinstalar.lnk" \
"$INSTDIR\Uninstall.exe"

SectionEnd


Section "Acceso directo en escritorio" SEC02

CreateShortcut "$DESKTOP\Jugar a A·L·I·E·N.lnk" \
"$INSTDIR\glulxe.exe" "alien.blb" "$INSTDIR\alien.ico"

SectionEnd


Section "Uninstall"

Delete "$DESKTOP\Jugar a A·L·I·E·N.lnk"

RMDir /r "$SMPROGRAMS\A·L·I·E·N - La aventura (Edición Especial)"

RMDir /r "$INSTDIR"

DeleteRegKey HKCU "Software\ALIEN_EE"

SectionEnd
