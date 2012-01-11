!===============================================================================
!  SGW+DMX: Simple Glulx Wrapper con Damusix (MEJORAS DE ELIUK BLAU)
!  Codigo Fuente --==[ Version Especial para Libreria Española InformATE! ]==--
!===============================================================================
!
!  Archivo :  sgw+dmx.h
!  Fecha   :  2009/02/27
!  Version :  2.3
!  Autor   :  Eliuk Blau
!  e-Mail  :  eliukblau (AT) gmail.com
!
!  ---------------------------------------------------------------------------
!  IMPORTANTE - IMPORTANTE - IMPORTANTE - IMPORTANTE - IMPORTANTE - IMPORTANTE
!  ---------------------------------------------------------------------------
!    Basado en el codigo original de SGW v1.6.1 [2006/03/11]
!    (de Alessandro Schillaci, Vincenzo Scarpa, Paolo Maroncelli)
!
!    Website del autor original :  http://slade.altervista.org
!    e-Mail del autor original  :  silver.slade@tiscalinet.it
!  ---------------------------------------------------------------------------
!  IMPORTANTE - IMPORTANTE - IMPORTANTE - IMPORTANTE - IMPORTANTE - IMPORTANTE
!  ---------------------------------------------------------------------------
!
!  -- El Marco de Trabajo y el Slide de Imagenes estan inspirados y basados --
!  -- en porciones del codigo de SGW para InformATE!, de Mapache y Depresiv --
!
!===============================================================================
!  **** LA DOCUMENTACION SIGUIENTE CORRESPONDE A UNA TRADUCCION LIBRE DEL ****
!  ****   TEXTO ESCRITO POR EL AUTOR ORIGINAL, SR. ALESSANDRO SCHILLACI   ****
!===============================================================================
!
!  PARA QUE SIRVE ESTO:
!  --------------------
!
!  SGW+DMX es un pequeño y sencillo wrapper para Glulx, especialmente creado
!  para programadores con un nivel novato en Inform-Glulx.
!
!  Con esta extension es posible mostrar una imagen o simplemente tocar un
!  sonido o musica, usando un reducido conjunto de rutinas que "envuelven"
!  las verdaderas funciones de la API Glk de Glulx. Adicionalmente se puede
!  especificar y utilizar los diferentes estilos de texto que Glulx provee.
!
!  SGW+DMX es tan simple de usar que facilmente se puede "actualizar"
!  una aventura escrita originalmente para la Maquina-Z a una aventura
!  con soporte multimedia para la moderna Maquina Glulx.
!
!  Lo mejor de todo es que utilizando SGW+DMX se puede programar una aventura
!  que compile tanto para Glulx como para la Maquina-Z, sin apenas variar el
!  codigo. Si se utilizan solo las funciones provistas por esta extension,
!  no sera necesario modificar nada para obtener codigo biplataforma.
!
!  SGW+DMX ha sido concebida pensando especialmente para su uso junto con
!  la extension Damusix. Asi podras dotar a tu juego de funcionalidades
!  de audio muy potentes a la vez que bien sencillas de utilizar.
!
!  La extension SGW+DMX implementa las siguientes caracteristicas:
!
!  * 2 Ventanas Graficas:
!      - una para mostrar imagenes grandes (Ej.: de la localidad actual)
!      - una para mostrar imagenes chicas (Ej.: descripcion de objetos)
!
!  * 3 Canales de Audio:
!      - music: canal para la musica de fondo
!      - chan1: canal 1 para los efectos de sonido
!      - chan2: canal 2 para los efectos de sonido
!
!  NOTA: Si usas Damusix junto con SGW+DMX, los tres canales de audio antes
!        mencionados ya no seran creados y todas las funciones relacionadas
!        con el sonido de SGW+DMX seran inhabilitadas. Entonces ya podras
!        manejar el sistema de audio completo directamente con Damusix.
!
!===============================================================================
!
!  COMO USAR SGW+DMX:
!  ------------------
!
!  Tan sencillo como seguir las siguientes instrucciones:
!
!  1) Incluye SGW+DMX en el codigo fuente de tu juego despues de incluir
!     el propio Parser de InformATE! (pero antes del archivo de Gramatica).
!     Ejemplo:
!
!       Include "EParser";
!       Include "sgw+dmx";       ! Incluir la extension SGW+DMX
!       Include ">aventura.bli"; ! Incluir los recursos (imagenes y sonidos)
!       Include "Acciones";
!       !--------------------
!       ! ... mas codigo ...
!       !--------------------
!       Include "Mensajes";
!       Include "Gramatica";
!
!     SGW+DMX utiliza la extension "infglk.h" para compilar correctamente.
!     Viene incluida en el paquete de SGW+DMX, asi que recuerda copiarla
!     en el directorio de tus librerias para InformATE!
!
!  2) En la rutina Inicializar(), llama a la rutina initializeSGW(x) para
!     indicarle a SGW+DMX que prepare las ventanas graficas y el sistema
!     de audio. El argumento 'x' corresponde a la altura que debera tener
!     la ventana superior para imagenes grandes (por ejemplo, para las
!     imagenes de localidad). Ejemplo:
!
!       initializeSGW(240);
!
!     Esto va a configurar el tamaño de la ventana superior para permitir
!     mostrar imagenes de "idealmente" 240px de altura. No es obligatorio
!     que la imagen realmente tenga esa altura, pues si tiene una altura
!     mayor que la indicada para la ventana entonces dicha imagen sera
!     "redimensionada" para ajustarse a la altura de la ventana.
!
!     Si vas a ocupar Damusix, la rutina initializeSGW() tambien se encargara
!     de inicializar el Gestor de Audio, ejecutando automaticamente la rutina
!     Damusix.InicializarGlk(), por lo que no tienes que preocuparte de
!     hacerlo tu mismo, a mano, en la rutina Inicializar() de tu juego.
!     SGW+DMX lo hara por ti.
!
!  3) Una vez que SGW+DMX este inicializada ya puedes intentar reproducir
!     un sonido o mostrar alguna imagen. La rutina playSound() sirve para
!     tocar la musica y sonidos. Para mostrar imagenes puedes usar las
!     siguientes rutinas:
!
!       viewImageCenter(img) -> Imagen centrada en la ventana grande
!       viewImageRight(img)  -> Imagen a la derecha en la ventana grande
!       viewImageLeft(img)   -> Imagen a la izquierda en la ventana grande
!
!       viewImageSlide(img)  -> Imagen con deslizamiento en la ventana chica
!       closeImageSlide()    -> Si la ventana chica esta abierta, la cierra
!
!     En ninguna de estas rutinas es necesario especificar el tamaño
!     de la imagen. Lo averiguaran por ellas mismas.
!
!  4) Puedes configurar los colores que quieres que tenga el juego.
!     Simplemente tienes que declarar las siguientes constantes antes
!     de incluir SGW+DMX:
!
!       Constant SCBACK = $110101;      ! estilo fondo
!       Constant SCTEXT = $DDBB99;      ! estilo texto
!       Constant SCEMPH = $FFFFDD;      ! estilo enfasis
!       Constant SCHEAD = $EEDDAA;      ! estilo cabecera (nombre localidades)
!       Constant SCINPU = $DDEEAA;      ! estilo input del jugador
!       Constant SCUSR1 = CLR_GG_BLUE;  ! estilo configurable User1
!       Constant SCUSR2 = CLR_GG_PINK;  ! estilo configurable User2
!
!     Opcionalmente, puedes indicar colores personalizados tambien
!     para la Linea de Estado del juego:
!
!       Constant LIBACK = $30FF30;  ! estilo fondo linea de estado
!       Constant LITEXT = $0000A0;  ! estilo texto linea de estado
!
!     Los colores deben estar expresados en formato RRGGBB, mediante un numero
!     hexadecimal. Si no sabes el valor hexadecimal de algun color, puedes
!     averiguarlo facilmente con cualquier programa de retoque fotografico.
!     Hay una serie de constantes faciles para los colores usados con
!     mayor frecuencia:
!
!       CLR_GG_AZURE       CLR_GG_BLACK
!       CLR_GG_BLUE        CLR_GG_BROWN
!       CLR_GG_CYAN        CLR_GG_GREEN
!       CLR_GG_GREY        CLR_GG_MAGENTA
!       CLR_GG_ORANGE      CLR_GG_PINK
!       CLR_GG_PURPLE      CLR_GG_RED
!       CLR_GG_YELLOW      CLR_GG_WHITE
!
!  5) Al mostrar mensajes de texto puedes usar diferentes estilos.
!     Ejemplos:
!
!       print "Estilo de Texto: ", (s_emph) "Emphasized", "^";
!       print "Estilo de Texto: ", (s_bold) "Bold", " (como Máquina-Z)^";
!       print "Estilo de Texto: ", (s_pref) "Preformatted", "^";
!       print "Estilo de Texto: ", (s_fixed) "Fixed", " (como Máquina-Z)^";
!       print "Estilo de Texto: ", (s_head) "Header", "^";
!       print "Estilo de Texto: ", (s_subhead) "Subheader", "^";
!       print "Estilo de Texto: ", (s_alert) "Alert", "^";
!       print "Estilo de Texto: ", (s_reverse) "Reverse", " (como Máquina-Z)^";
!       print "Estilo de Texto: ", (s_note) "Note", "^";
!       print "Estilo de Texto: ", (s_underline) "Underline/Italic", " (como Máquina-Z)^";
!       print "Estilo de Texto: ", (s_block) "BlockQuote", "^";
!       print "Estilo de Texto: ", (s_input) "Input", "^";
!       print "Estilo de Texto: ", (s_user1) "User1", "^";
!       print "Estilo de Texto: ", (s_user2) "User2", "^";
!
!  6) Si no quieres ocupar graficos simplemente tienes que declarar
!     la siguiente constante antes de incluir SGW+DMX:
!
!       Constant SGW_SIN_GRAFICOS;
!
!     Ahora tu juego solo tendra sonido, sin capacidades graficas.
!
!  7) Si quieres usar Damusix para gestionar el audio, tienes que
!     declarar la siguiente constante antes de incluir SGW+DMX:
!
!       Constant SGW_CON_DAMUSIX;
!
!     Ahora SGW+DMX incluira e inicializara automaticamente la
!     extension Damusix. Todas las funciones nativas de audio de
!     SGW+DMX seran inhabilitadas con este cambio y ya podras usar
!     sin problemas las rutinas de Damusix. Ademas, SGW+DMX hara
!     todos los ajustes necesarios en el Marco de Trabajo (ver
!     siguiente item) para que se usen las rutinas de Damusix
!     que son mucho mas potentes.
!
!  8) SGW+DMX implementa automaticamente un simple "Marco de Trabajo"
!     que te hara la vida mas facil a la hora de programar tu juego.
!     El Marco de Trabajo mostrara una Imagen y tocara una Musica de
!     Fondo para cada Localidad de manera automatica. Tambien mostrara
!     una imagen para cada Objeto que sea "examinado" durante el juego.
!
!     Para que una Localidad u Objeto muestren su Imagen, deben tener
!     una propiedad 'sgw_img' con la imagen que deseas.
!
!     Para que una Localidad toque su Musica de Fondo, debe tener
!     una propiedad 'sgw_mus' con la musica que deseas. Opcionalmente
!     puedes indicar un volumen para aquella musica, incluyendo una
!     propiedad 'sgw_vol' con el porcentaje de volumen (0-100) que
!     deseas. Hay tres constantes faciles que puedes usar tambien:
!     VOLUMEN_ALTO (100%), VOLUMEN_MEDIO (75%), VOLUMEN_BAJO (50%).
!     Ejemplos:
!
!       Object La_Localidad "Una Localidad Cualquiera"
!         has luz,
!         with
!           sgw_img grafico_localidad, ! el grafico de la localidad
!           sgw_mus musica_localidad,  ! la musica de la localidad
!           sgw_vol VOLUMEN_ALTO,      ! el volumen de la musica
!           descripcion "Yeah. Imagen y Musica de Fondo.",
!       ;
!
!       Object El_Objeto "Un Objeto Cualquiera"
!         with
!           sgw_img grafico_objeto, ! el grafico del objeto
!           descripcion "Cool. Este objeto tiene una Imagen.",
!       ;
!
!     Si una localidad no tiene luz, el Marco de Trabajo no mostrara
!     su imagen, limitandose solo a dibujar la ventana grafica vacia.
!     Sin embargo, opcionalmente puedes indicar una imagen que sea
!     representativa de "la oscuridad", y el Marco de Trabajo la
!     mostrara en cada localidad que no este iluminada. Para usar
!     este comportamiento, debes declarar la siguiente variable
!     global antes de incluir SGW+DMX, asignandole el valor de
!     la imagen que representara "la oscuridad":
!
!       Global SGW_IMAGEN_OSCURIDAD = OSCURIDAD_TETRICA;
!
!     En este ejemplo, OSCURIDAD_TETRICA sera la imagen que se
!     va a mostrar cuando las localidades no tengan iluminacion.
!     Como SGW_IMAGEN_OSCURIDAD es una variable global, nada te
!     impide asignarle una nueva imagen en cualquier otra parte
!     del juego.
!
!     El Marco de Trabajo hace uso de las rutinas TrasElPrompt()
!     y RutinaPostJuego(). Si necesitas implementar una version
!     propia de estas rutinas en tu juego, simplemente escribelas
!     antes de incluir SGW+DMX. No olvides que debes llamar en
!     alguna parte de ellas a la rutina del Marco de Trabajo. Asi,
!     dentro de TrasElPrompt() debes llamar a SGW_MarcoDeTrabajo(1) y
!     dentro de RutinaPostJuego() debes llamar a SGW_MarcoDeTrabajo(2).
!     Con esto, el Marco de Trabajo seguira funcionando normalmente.
!     Ejemplos:
!
!       [ TrasElPrompt ;
!           SGW_MarcoDeTrabajo(1);
!           !---------------------------------------------------------
!           ! ... todo el codigo tuyo que necesites poner aqui ...
!           !---------------------------------------------------------
!       ];
!
!       [ RutinaPostJuego ;
!           SGW_MarcoDeTrabajo(2);
!           !---------------------------------------------------------
!           ! ... todo el codigo tuyo que necesites poner aqui ...
!           !---------------------------------------------------------
!           rfalse; ! IMPORTANTE: SIN ESTO NO SE MUESTRA NINGUN TEXTO
!       ];
!
!     Por otro lado, si no quieres usar el Marco de Trabajo solo
!     debes declarar la siguiente constante antes de incluir SGW+DMX:
!
!       Constant SGW_SIN_MARCO_DE_TRABAJO;
!
!     Ahora SGW+DMX compilara sin el Marco de Trabajo, lo cual seria
!     algo muy triste, la verdad... =P
!
!  9) NOTA TECNICA: La extension SGW+DMX ocupa los siguientes Puntos
!     de Entrada Glk para funcionar correctamente: IdentifyGlkObject()
!     y HandleGlkEvent(). Si necesitas implementar una version propia
!     de estas rutinas en tu juego, simplemente escribelas antes de
!     incluir SGW+DMX. Pero no debes olvidar algo MUY IMPORTANTE:
!
!     - Dentro de IdentifyGlkObject() debes llamar a:
!       SGW_IdentifyGlk(fase,tipo,ref,rock);
!
!     - Dentro de HandleGlkEvent() debes llamar a:
!       SGW_HandleGlk(ev);
!
!     Ejemplos:
!     ---------
!
!       [ IdentifyGlkObject fase tipo ref rock;
!           ! IdentifyGlkObject de libreria SGW
!           SGW_IdentifyGlk(fase,tipo,ref,rock);
!           !------------------------------------------------------------------
!           ! ESTA LINEA ES NECESARIA SOLO SI ESTAS USANDO DAMUSIX:
!           ! Damusix.IdentificarSonidos(fase);
!           !------------------------------------------------------------------
!           !------------------------------------------------------------------
!           ! ... todo el codigo tuyo que necesites poner aqui ...
!           !------------------------------------------------------------------
!       ];
!
!       [ HandleGlkEvent ev;
!           ! HandleGlkEvent de libreria SGW
!           SGW_HandleGlk(ev);
!           !------------------------------------------------------------------
!           ! ESTA LINEA ES NECESARIA SOLO SI ESTAS USANDO DAMUSIX:
!           ! Damusix.NotificarFade(ev); ! solo si usas Fades en "tiempo-real"
!           !------------------------------------------------------------------
!           !------------------------------------------------------------------
!           ! ... todo el codigo tuyo que necesites poner aqui ...
!           !------------------------------------------------------------------
!       ];
!
!     Con esto, SGW+DMX funcionara normalmente y podras programar
!     tus propias versiones de los Puntos de Entrada Glk mencionados.
!
!===============================================================================
!
!  FUNCIONES GRAFICAS:
!  -------------------
!
!    testGraphics(f)       : testea soporte de graficos (f=1, mostrar avisos)
!    initializeSGW(x)      : inicia SGW+DMX (x=alto en pixeles de vent. grande)
!    clearMainWindow()     : limpia ventana principal (textos e imagen superior)
!    clearGraphicWindow()  : limpia la ventana grafica grande (imagen superior)
!    clearTextWindow()     : limpia la ventana del buffer de texto del juego
!    clearStatusLine()     : limpia la ventana de la linea de estado
!    closeAllWindows()     : cierra *todas* las ventanas graficas
!    openGraphicWindow(x)  : abre la ventana grafica grande (x=alto en pixeles)
!    closeGraphicWindow()  : cierra la ventana grafica grande (si esta abierta)
!    viewImageCenter(img)  : muestra 'img' centrada en vent. grande
!    viewImageRight(img)   : muestra 'img' a la derecha en vent. grande
!    viewImageLeft(img)    : muestra 'img' a la izquierda en vent. grande
!    viewImageSlide(img,f) : muestra 'img' en vent. chica (f=1, no deslizar)
!    closeImageSlide()     : cierra la ventana grafica chica (si esta abierta)
!
!  FUNCIONES DE AUDIO:
!  -------------------
!
!    testSounds(f)            : testea soporte de sonidos (f=1, mostrar avisos)
!    playSound(canal,sonido,repeticiones,volumen) : toca un sonido o musica
!    setVolume(volumen,canal) : cambia el volumen del canal de audio indicado
!    silenceChannel(canal)    : detiene el sonido del canal de audio indicado
!    silenceAll() : detiene todos los sonidos (canales: music, chan1 y chan2)
!
!  OTRAS FUNCIONES:
!  ----------------
!
!    wait("txt",x) : espera una pulsacion de tecla, con un texto y un tiempo
!                    de espera opcionales (x=0, no temporizar la espera).
!
!===============================================================================
!
!  COMPATIBILIDAD - Lista de Cambios efectuados en SGW+DMX para InformATE!
!  respecto del codigo original en SGW+DMX para Inform6 + Lib. 6/11:
!
!  (01) La comprobacion de la existencia de la Libreria 6/11 oficial es
!       removida por ser inaplicable en el caso de InformATE!, eliminando
!       asi las sentencias de la compilacion condicional y el mensaje de
!       error en caso de no existencia de la constante LIBRARY_VERSION o
!       si acaso existe, pero LIBRARY_VERSION < 611.
!
!  (02) La llamada a DrawStatusLine() en la rutina slideViewPausa()
!       se cambia por su equivalente DibujarLineaEstado() de InformATE!
!
!  (03) La rutina initializeSGW(), si se compila con Damusix, llamara
!       automaticamente a Damusix.InicializarGlk() ya que en InformATE!
!       el Gestor de Damusix debe ser inicializado explicitamente porque
!       no existe el mecanismo de inicializacion automatica de extensiones
!       que proporciona la Lib. 6/11 (ver Doc de 'Damusix para InformATE!')
!
!  (04) Se hacen varios cambios en el codigo del Marco de Trabajo y en
!       la rutina SGW_IdentifyGlk() para adaptar variables y acciones
!       a sus nombres españolizados de InformATE! Estos cambios son:
!         - Se cambia 'noun' por 'uno'
!         - Se cambia 'action' por 'accion'
!         - Se cambia 'thedark' por 'laoscuridad'
!         - Se cambia 'location' por 'localizacion'
!         - Se cambia 'real_location' por 'localizacion_real'
!         - Se cambia AfterPrompt() por TrasElPrompt()
!         - Se cambia GamePostRoutine() por RutinaPostJuego()
!         - Se cambia '##Examine' por '##Examinar'
!
!  (05) Se portan algunas rutinas propias de la Lib. 6/11 y utilizadas
!       en SGW+DMX que no existen en InformATE! (porque usa Lib. 6/10):
!         - Rutina ClearScreen()      [version Z y Glulx]
!         - Rutina KeyDelay()         [version Z y Glulx]
!         - Rutina KeyCharPrimitive() [solo Z; InformATE! ya la trae en Glulx]
!
!  (06) Se adapta la documentacion para ser coherente con la sintaxis
!       españolizada de InformATE!
!
!===============================================================================
!
!  LICENCIA DE SGW+DMX:
!  --------------------
!
!  Si modificas la extension SGW+DMX, estare muy agradecido si me mandas el
!  codigo fuente por e-Mail.
!
!  If you modify the SGW+DMX extension, I would be grateful if you send me
!  the source code by e-Mail.
!
!  Copyright (c) 2008 Nicolas Merino Quezada (aka Eliuk Blau).
!
!  This program is free software: you can redistribute it and/or modify it
!  under the terms of the GNU Lesser General Public License as published
!  by the Free Software Foundation, either version 3 of the License.
!
!  This program is distributed in the hope that it will be useful, but
!  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
!  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
!  License for more details.
!
!  You should have received a copy of the GNU Lesser General Public License
!  along with this program. If not, see <http://www.gnu.org/licenses/>.
!
!===============================================================================
!
!  Log:
!  2009/02/27  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v2.3 **
!                         - Nuevas rutinas:
!                           * clearGraphicWindow()
!                           * clearTextWindow()
!                           * clearStatusLine()
!                         - La rutina clearMainWindow() se compacta. Ahora
!                           utiliza clearGraphicWindow() y clearTextWindow().
!                         - El Marco de Trabajo ahora permite declarar una
!                           imagen para el grafico de las localidades que
!                           no tengan luz, en vez de solo mostrar la
!                           ventana vacia.
!                         - Se actualiza la documentacion de acuerdo a los
!                           cambios realizados. Version actual: DocV 2.3.
!  2009/02/10  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v2.2 **
!                         - Actualizacion solo por motivo de correccion en
!                           codigo de SGW+DMX Demo (v1.2) y documentacion.
!                         - Se corrigen insignificantes despistes en
!                           la documentacion. Version actual: DocV 2.2.
!  2009/01/03  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v2.1 **
!                         - Actualizacion para compatibilidad con la nueva
!                           extension de soporte: Dainunek v3.
!  2008/10/23  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v2.0 **
!                         - Se hacen grandes correcciones del codigo. Habian
!                           errores que se arrastraban de la version original
!                           de SGW (v1.6.1). SGW es funcional, pero realmente
!                           no esta programada muy bien. En esta version de
!                           SGW+DMX se corrigen, compactan y mejoran todos
!                           los codigos que lo necesitaran, eliminando asi
!                           toda la 'basura historica' de la SGW original
!                           (con todo respeto... =P).
!                         - Dos rutinas son eliminadas por ser redundantes:
!                           * MyRedrawGraphicsWindows(), porque hacia lo mismo
!                             que viewImageSGW() [ahora se ocupa esta ultima]
!                           * ResetMusicChannels(), porque hacia lo mismo
!                             que silenceAll() [ahora se ocupa esta ultima]
!                         - Se corrigen 'exhaustivamente' todas las rutinas
!                           relacionadas con la reproduccion de sonidos, para
!                           que ahora comprueben siempre si el interprete
!                           tiene soporte de sonido o no. Se evitan asi
!                           muchos potenciales Bugs.
!                         - IMPORTANTE!! Se cambia la licencia de SGW+DMX.
!                           Ahora esta licenciada bajo los terminos de LGPLv3.
!                         - Se comienza a versionar la documentacion. En
!                           este release corresponde a DocV 2.0.
!  2008/08/08  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v1.4 **
!                         - Se programan dos nuevas rutinas de testeo del
!                           interprete Glulx:
!                           * testGraphics() --> testea soporte Graficos
!                           * testSounds()   --> testea soporte Sonidos
!                         - Rutina testGlulx() ya no es necesaria y se
!                           elimina del codigo. En su lugar se usan las
!                           dos nuevas rutinas mencionadas anteriormente.
!                         - Nueva rutina wait() que espera una pulsacion
!                           de tecla, con un texto y tiempo de espera
!                           opcionales.
!                         - Se mejoran y compactan las siguientes rutinas:
!                           * clearMainWindow()
!                           * closeAllWindows()
!  2008/08/02  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v1.3 **
!                         - En rutina testGlulx() se elimina comprobacion
!                           de SoundNotify, porque Gargoyle reporta que
!                           no tiene SoundNotify cuando se compila sin usar
!                           ningun sonido. Esto no ocurre si hay sonidos en
!                           el juego. Lo anterior es una pifia de Gargoyle,
!                           no de SGW+DMX. Para que el aviso de "no se soporta
!                           Soundnotify" ya no se muestre, se elimina ese test.
!                           Este cambio no influye ni tiene ningun efecto
!                           negativo en el codigo compilado final.
!  2008/07/26  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v1.2 **
!                         - Se incorpora la posibilidad de iniciar SGW+DMX sin
!                           la ventana grafica superior (luego puede abrirse),
!                           simplemente haciendo 'initializeSGW(0)' en la
!                           rutina Initialise() del juego.
!                         - Incorporada nueva rutina: closeGraphicWindow(),
!                           que cierra la ventana grafica superior.
!                         - Mejor definicion de estilos de texto para las
!                           ventanas de buffer, barra de estado y 'box'
!                           (los boxs ahora tienen aspecto coherente).
!                         - Ahora se pueden indicar colores personalizados
!                           para la Linea de Estado del juego, definiendo
!                           las constantes:
!                           * LIBACK (color para fondo de linea de estado)
!                           * LITEXT (color para texto de linea de estado)
!                         - Se corrige potencial Bug que podia hacer que al
!                           ejecutar clearMainWindow() el sistema arrojara
!                           un error run-time si la ventana grafica superior
!                           no estaba abierta en ese momento.
!                         - Se elimina codigo de creacion de ventana para
!                           la barra de estado, debido a que nunca se ejecuta
!                           porque es la propia Lib. Inform la que se encarga
!                           de preparar y abrir dicha ventana. (Redundante.)
!                         - Ahora se recupera correctamente el estado de la
!                           ventana grafica superior ante situaciones de UNDO
!                           o de carga de una partida grabada anteriormente.
!                           Se re-abre la ventana con el tamaño correcto
!                           automaticamente si es necesario.
!  2008/07/17  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** SGW+DMX v1.1 **
!                         - Se corrige un BUG por despiste que hacia que
!                           no se re-pintara ni recuperara bien la ventana
!                           grafica pequeña para objetos (con Slide). Ahora
!                           la imagen se re-pinta correctamente ante cambios
!                           de tamaño de la ventana de juego (incluso durante
!                           el efecto de Slide) y se restaura correctamente
!                           ante los comandos UNDO o RESTORE. =D Happy!
!  2008/07/13  Eliuk Blau - Se termina de programar y corregir BUGs.
!                           Lista la version 1.0 de esta extension.
!  2008/06/04  Eliuk Blau - Se crea el archivo.
!
!===============================================================================

#ifndef _SGWDMX_H_;  ! se ha incluido ya?

Message "[*** SGW+DMX v2.3 por Eliuk Blau (varias mejoras y compatibilidad con Damusix) ***]";
Message "[Basada en SGW v1.6.1 por Alessandro Schillaci, Vincenzo Scarpa y Paolo Maroncelli]";
System_file; Constant _SGWDMX_H_;

!===============================================================================
! COMPROBACIONES INICIALES
!-------------------------------------------------------------------------------
! ERROR: Se necesita el Compilador Inform v6.30 o superior
#ifndef VN_1630;
  Message "[SGW+DMX: ERROR - No se puede compilar el codigo del juego]";
  Message "[SGW+DMX: -> Se necesita el Compilador Inform v6.30 o superior]";
  Message fatalerror "";
#endif; ! VN_1630

!===============================================================================
! IMPLEMENTACION AUTOMATICA DE LOS PUNTOS DE ENTRADA GLK MEDIANTE DAINUNEK
!-------------------------------------------------------------------------------
#ifdef SGW_CON_DAMUSIX; ! == SI SE QUIERE USAR SGW JUNTO CON EXTENSION DAMUSIX ==
  #ifdef TARGET_GLULX; ! *** IMPLEMENTACION PUNTOS DE ENTRADA GLK CON DAINUNEK ***
    !-------------------------------------------------------------------------------
    ! el programador proporciona rutina IdentifyGlkObject() en el codigo del juego
    #ifdef IdentifyGlkObject;
      #ifndef DAINUNEK_IGO; ! codigo segun Dainunek
        Message "[SGW+DMX: Usando rutina IdentifyGlkObject() proporcionada por el juego]";
        Message "[SGW+DMX: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
        Message "[SGW+DMX: -> < SGW_IdentifyGlk(fase,tipo,ref,rock) > ** OBLIGATORIO **]";
      #endif; ! DAINUNEK_IGO
    #endif; ! IdentifyGlkObject

    ! el programador proporciona rutina HandleGlkEvent() en el codigo del juego
    #ifdef HandleGlkEvent;
      #ifndef DAINUNEK_HGE; ! codigo segun Dainunek
        Message "[SGW+DMX: Usando rutina HandleGlkEvent() proporcionada por el juego]";
        Message "[SGW+DMX: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
        Message "[SGW+DMX: -> < SGW_HandleGlk(ev) > ** OBLIGATORIO **]";
      #endif; ! DAINUNEK_HGE
    #endif; ! HandleGlkEvent

    !-------------------------------------------------------------------------------
    ! PARA LA INICIALIZACION UNIFICADA DE EXTENSIONES (PUNTOS DE ENTRADA GLK)
    Include "Dainunek";

    ! ERROR: Se necesita la Extension Dainunek v3 o superior
    #ifndef _DAINUNEK_VERSION_;
      Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
      Message "[DAMUSIX: -> Se necesita la Extension Dainunek v3 o superior]";
      Message fatalerror "";
    #endif;
    #iftrue (_DAINUNEK_VERSION_ < 3);
      Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
      Message "[DAMUSIX: -> Se necesita la Extension Dainunek v3 o superior]";
      Message fatalerror "";
    #endif; ! _DAINUNEK_VERSION_

    #ifdef DAINUNEK_OK;
      Object SGW_Glk Dainunek
        with
          IdentifyGlk [ fase tipo ref rock;
            ! IdentifyGlkObject de libreria SGW
            SGW_IdentifyGlk(fase,tipo,ref,rock);
          ],
          HandleGlk [ ev;
            ! HandleGlkEvent de libreria SGW
            SGW_HandleGlk(ev);
          ],
      ;
    #endif; ! DAINUNEK_OK
    !-------------------------------------------------------------------------------
  #endif; ! *** FIN DE IMPLEMENTACION DE PUNTOS DE ENTRADA GLK CON DAINUNEK  ***
#endif; ! SGW_CON_DAMUSIX
!===============================================================================

#ifdef SGW_SIN_GRAFICOS;
  message "[SGW+DMX: Compilando sin graficos (solamente sonidos)]";
#endif;

! SIMPLEMENTE PARA EVITAR UN WARNING CUANDO SE COMPILA PARA MAQUINA-Z
#ifdef SGW_SIN_MARCO_DE_TRABAJO; #endif;

! SIMPLEMENTE PARA EVITAR UN WARNING CUANDO SE COMPILA PARA MAQUINA-Z Y GLULX
#ifdef SGW_IMAGEN_OSCURIDAD; #endif;

#ifdef TARGET_GLULX;

  Include "infglk"; ! NECESARIO PARA EL FUNCIONAMIENTO DE SGW (NO BORRAR)

  #ifdef SGW_CON_DAMUSIX;
    !-------------------------------------------------------------------------------
    Message "[SGW+DMX: Usando extension Damusix para Gestionar el Audio en Glulx]";
    Message "[SGW+DMX: -> IMPORTANTISIMO: TODAS LAS RUTINAS SGW RELACIONADAS CON]";
    Message "[SGW+DMX: -> LA REPRODUCCION DE AUDIO HAN SIDO INHABILITADAS.......]";
    Message "[SGW+DMX: -> *** RECUERDA USAR LAS RUTINAS SIMILARES DE DAMUSIX ***]";
    !-------------------------------------------------------------------------------
    ! DreamBytes Adventures:
    ! Ad(M)inistrador (U)nificado de (S)on(I)do en Glul(X)
    Include "Damusix";

  #ifnot; ! SI SE VA A UTILIZAR EL SISTEMA DE AUDIO NATIVO DE SGW

    Message "[SGW+DMX: Usando Audio Nativo de SGW (sin Damusix)... :( que triste!]";

    Constant GG_MUSICCHAN_ROCK       = 410;  ! Music Channel Rock
    Constant GG_MUSICCHANSOUND1_ROCK = 411;  ! Sound Channel 1 Rock
    Constant GG_MUSICCHANSOUND2_ROCK = 412;  ! Sound Channel 2 Rock

    Global current_music = 0;        ! Current Location Music
    Global gg_SoundSupport = true;   ! Capacidad de Sonido soportada?
    Global gg_VolumeSupport = true;  ! Cambios de Volumen soportados?

  #endif; ! SGW_CON_DAMUSIX

  Constant GG_BIGWIN_ROCK = 210;  ! Image Location Window Rock
  Constant GG_OBJWIN_ROCK = 211;  ! Image Object Window Rock

  Global gg_bigwin = 0;           ! Image Location Window Reference
  Global gg_objwin = 0;           ! Image Object window Reference

  Global curr_pic     = 0;        ! Current Location Picture
  Global curr_pic_pos = 0;        ! Current Location Picture Position
  Global curr_obj_pic = 0;        ! Current Object Picture (Slide Window)

  Global current_loc = 0;         ! Current Location (Marco de Trabajo)

  ! Position constants - added by Paolo Maroncelli
  Constant POS_CENTRADO   = 0;  ! valor cambiado para compat. con drawImage()
  Constant POS_IZQUIERDA  = 1;  ! valor cambiado para compat. con drawImage()
  Constant POS_DERECHA    = 2;  ! valor cambiado para compat. con drawImage()

#endif; ! TARGET_GLULX

!===============================================================================
! NECESARIO PARA COMPILACION EN Z Y GLULX: *** No cambiar lineas de posicion ***
!-------------------------------------------------------------------------------
Global music = 0;                 ! Music Channel Reference
Global chan1 = 0;                 ! Sound Channel 1 Reference
Global chan2 = 0;                 ! Sound Channel 2 Reference

Constant VOLUMEN_ALTO   = 100;    ! valor cambiado a porcent. (compat. Damusix)
Constant VOLUMEN_MEDIO  = 75;     ! valor cambiado a porcent. (compat. Damusix)
Constant VOLUMEN_BAJO   = 50;     ! valor cambiado a porcent. (compat. Damusix)

Global bigwin_alto = 0;  ! ELIUK: Altura con la que se ha abierto actualmente
                         ! la ventana grafica superior. Es necesaria para
                         ! recuperar correctamente la ventana grafica superior
                         ! a su estado y tamaño anterior al momento de cargar
                         ! una partida o hacer UNDO, por citar unos ejemplos.

Default BORDEWIN = 10;   ! ELIUK: Borde para las Ventanas Graficas.
                         ! Si no quieres tener borde, define la constante
                         ! BORDEWIN con valor cero antes de incluir SGW+DMX
                         ! en el codigo de tu juego. Ejemplo...
                         !   Constant BORDEWIN = 0;
!-------------------------------------------------------------------------------

! Colors constants - added by Vincenzo Scarpa (ELIUK: ahora definidas con 'Default')
Default CLR_GG_AZURE     = $30ffff;
Default CLR_GG_BLACK     = $000000;
Default CLR_GG_BLUE      = $0000a0;
Default CLR_GG_BROWN     = $7f3f00;
Default CLR_GG_CYAN      = $30ffff;
Default CLR_GG_GREEN     = $30ff30;
Default CLR_GG_GREY      = $bfbfbf;
Default CLR_GG_MAGENTA   = $ff30ff;
Default CLR_GG_ORANGE    = $ff7f00;
Default CLR_GG_PINK      = $ff7fff;
Default CLR_GG_PURPLE    = $ff30ff;
Default CLR_GG_RED       = $ff3030;
Default CLR_GG_YELLOW    = $ffff30;
Default CLR_GG_WHITE     = $ffffff;

! ELIUK: Constantes de color usadas 'por defecto' en SGW+DMX
Default CLR_GG_PERSBACK  = $110101;
Default CLR_GG_PERSTEXT  = $DDBB99;
Default CLR_GG_PERSEMPH  = $FFFFDD;
Default CLR_GG_PERSHEAD  = $EEDDAA;
Default CLR_GG_PERSINPU  = $DDEEAA;
Default CLR_GG_PERSUSR1  = $30FFFF; ! ELIUK =P
Default CLR_GG_PERSUSR2  = $30FF30; ! ELIUK =P

! ELIUK: Colores personalizados para las ventanas de texto
Default SCBACK  = CLR_GG_PERSBACK;
Default SCTEXT  = CLR_GG_PERSTEXT;
Default SCEMPH  = CLR_GG_PERSEMPH;
Default SCHEAD  = CLR_GG_PERSHEAD;
Default SCINPU  = CLR_GG_PERSINPU;
Default SCUSR1  = CLR_GG_PERSUSR1; ! ELIUK =P
Default SCUSR2  = CLR_GG_PERSUSR2; ! ELIUK =P

! ELIUK: Colores personalizados para la Linea de Estado
Default LIBACK  = SCTEXT; ! se invierte el color
Default LITEXT  = SCBACK; ! se invierte el color


!===============================================================================
! FUNCIONES PORTADAS DESDE LIB. INFORM 6/11 (porque no existen en InformATE!)
!-------------------------------------------------------------------------------
! ELIUK: Las siguientes rutinas estan copiadas directamente de la Lib. 6/11
! con los retoques oportunos (InformATE! no las tiene porque usa la Lib. 6/10)

! Algunas constantes utilizadas por las rutinas portadas
Default WIN_ALL     = 0;
Default WIN_STATUS  = 1;
Default WIN_MAIN    = 2;

! Limpia el contenido de la ventana principal, la barra de estado o ambas
[ ClearScreen window;
   #ifdef TARGET_GLULX;
     if (window == WIN_ALL or WIN_MAIN) {
       glk($002A, gg_mainwin);
       if (gg_quotewin) {
         glk($0024, gg_quotewin, 0); ! close_window
         gg_quotewin = 0;
       }
     }
     if (gg_statuswin && window == WIN_ALL or WIN_STATUS) {
       glk($002A, gg_statuswin);
     }
   #ifnot; ! COMPILACION PARA MAQUINA Z
     switch (window) {
       WIN_ALL:    @erase_window -1;
       WIN_STATUS: @erase_window 1;
       WIN_MAIN:   @erase_window 0;
     }
   #endif; ! TARGET_
];

! Rutina 'tonta' requerida por la version Z de KeyDelay()
[ KeyTimerInterrupt;
    rtrue;
];

! Espera X decimas de segundo por la pulsacion de una tecla
[ KeyDelay tenths  key done ix;
   #ifdef TARGET_GLULX;
     glk($00D2, gg_mainwin); ! request_char_event
     glk($00D6, tenths*100); ! request_timer_events
     while (~~done) {
       glk($00C0, gg_event); ! select
       ix = HandleGlkEvent(gg_event, 1, gg_arguments);
       if (ix == 2) {
         key = gg_arguments-->0;
         done = true;
       }
       else if (ix >= 0 && gg_event-->0 == 1 or 2) {
         key = gg_event-->2;
         done = true;
       }
     }
     glk($00D3, gg_mainwin); ! cancel_char_event
     glk($00D6, 0); ! request_timer_events
     return key;
   #ifnot; ! COMPILACION PARA MAQUINA Z
     done = ix; ! para evitar warning de variables no usadas
     @read_char 1 tenths KeyTimerInterrupt -> key;
     return key;
   #endif; ! TARGET_
];

#ifdef TARGET_ZCODE;
! Espera por la pulsacion de una tecla.
! NOTA: Solo es necesaria la version Z de esta rutina, porque InformATE!
! curiosamente trae la version Glulx, pero no una version para Maquina-Z
[ KeyCharPrimitive win key;
    if (win) { @set_window win; }
    @read_char 1 -> key;
    return key;
];
#endif; ! TARGET_ZCODE


!===============================================================================
! FUNCIONES DE ESTILOS DE TEXTO - added by Vincenzo Scarpa
!-------------------------------------------------------------------------------

! Text in Emphasized style
[ s_emph text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Emphasized);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     style bold;
     print (string) text;
     style roman;
   #endif; ! TARGET_
];

! Text in Bold style (like Inform)
[ s_bold text;
    print (s_emph) text;
];

! Text in Preformatted style
[ s_pref text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Preformatted);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     font off;
     print (string) text;
     font on;
   #endif; ! TARGET_
];

! Text in Fixed style (like Inform)
[ s_fixed text;
    print (s_pref) text;
];

! Text in Header style
[ s_head text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Header);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     print (s_bold) text;
   #endif; ! TARGET_
];

! Text in Subheader style
[ s_subhead text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Subheader);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     print (s_bold) text;
   #endif; ! TARGET_
];

! Text in Alert style
[ s_alert text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Alert);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     style reverse;
     print (string) text;
     style roman;
   #endif; ! TARGET_
];

! Text in Reverse style (like Inform)
[ s_reverse text;
    print (s_alert) text;
];

! Text in Note style
[ s_note text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Note);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     style underline;
     print (string) text;
     style roman;
   #endif; ! TARGET_
];

! Text in Underline/Italic style (like Inform)
[ s_underline text;
    print (s_note) text;
];

! Text in BlockQuote style
[ s_block text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_BlockQuote);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     print (string) text;
   #endif; ! TARGET_
];

! Text in Input style
[ s_input text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_Input);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     print (string) text;
   #endif; ! TARGET_
];

! Text in User1 style ! ELIUK
[ s_user1 text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_User1);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     print (string) text;
   #endif; ! TARGET_
];

! Text in User2 style ! ELIUK
[ s_user2 text;
   #ifdef TARGET_GLULX;
     glk_set_style(style_User2);
     print (string) text;
     glk_set_style(style_Normal);
   #ifnot; ! COMPILACION PARA MAQUINA Z
     print (string) text;
   #endif; ! TARGET_
];


!===============================================================================
! FUNCIONES GRAFICAS
!-------------------------------------------------------------------------------

! INICIALIZA SGW+DMX (se debe indicar altura de las imagenes para vent. grafica)
[ initializeSGW h;
    #ifdef TARGET_GLULX;
      closeAllWindows();       ! Cerramos todas las ventanas de SGW+DMX
      openGraphicWindow(h);    ! ahora abrimos la ventana grafica superior
      clearStatusLine();       ! borramos la barra de estado (por si acaso)
      clearMainWindow();       ! y finalmente limpiamos la ventana principal
      !-------------------------------------------------------------------------
      testGraphics(1);         ! Testeamos el soporte de graficos (con aviso)
      !-------------------------------------------------------------------------
      #ifndef SGW_CON_DAMUSIX;
        if(testSounds(1)) {    ! Testeamos el soporte de sonidos (con aviso)
          ! INICIALIZA LOS CANALES DE AUDIO NATIVOS DE SGW+DMX
          if (music == 0) { music = glk_schannel_create(GG_MUSICCHAN_ROCK);       }
          if (chan1 == 0) { chan1 = glk_schannel_create(GG_MUSICCHANSOUND1_ROCK); }
          if (chan2 == 0) { chan2 = glk_schannel_create(GG_MUSICCHANSOUND2_ROCK); }
          silenceAll(); ! Silence all audio channels
        }
      #ifnot; ! SI COMPILAMOS CON DAMUSIX...
        Damusix.InicializarGlk(); ! INICIALIZAMOS GESTOR DE DAMUSIX (IMPORTANTE!)
      #endif; ! SGW_CON_DAMUSIX
      !-------------------------------------------------------------------------
    #ifnot; ! TARGET_ZCODE
      !-------------------------------------------------------------------------
      ! EVITA WARNINGS EN COMPILACION PARA CODIGO Z. IMPORTANTE: Simplemente es
      ! para evitar unos warnings si de declaran las constantes de estilo Glulx
      ! y se compila para Codigo-Z. Ademas, evita warning de variable no usada.
        h = SCBACK|SCTEXT|SCEMPH|SCHEAD|SCINPU|SCUSR1|SCUSR2|LIBACK|LITEXT;
      !-------------------------------------------------------------------------
    #endif; ! TARGET_
];

! ELIUK: Abre la ventana grafica superior (ventana grande)
! [en SGW original esta rutina se llama 'inizializeGlulx()']
[ openGraphicWindow h;
    !---------------------------------------------------------------------------
    ! EVITAR WARNINGS EN COMPILACION PARA CODIGO Z O CON SGW_SIN_GRAFICOS
      h = h;
    !---------------------------------------------------------------------------
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        ! si la ventana grafica superior ya existe, primero la cerramos
        closeGraphicWindow();
        !---------------------------------------------------------------------------
        ! si la altura para abrir la ventana es cero...
        if (h == 0) { return; } ! no hacemos nada y retornamos
        !---------------------------------------------------------------------------
        ! IMPORTANTE: Recordamos altura para poder recuperar vent. al cargar partida
          bigwin_alto = h;
        !---------------------------------------------------------------------------
        !===========================================================================
          h = h+(BORDEWIN*2); ! suma 20px = borde sup. e inf. de 10px (por estetica)
        !---------------------------------------------------------------------------
        ! NOTA SOBRE EL '+(BORDEWIN*2)': La rutina que dibuja los graficos en la
        ! ventana deja siempre por defecto un borde de 10px alrededor de la imagen
        ! (solo por estetica), por lo tanto la imagen se dibujara siempre con 20px
        ! menos de altura. Para compensar esto y que la imagen se dibuje realmente
        ! con su tamaño original, sumamos 20px al propio tamaño de la ventana
        ! grafica. Asi, si defines una ventana de 100px (por ejemplo), entonces
        ! se creara una ventana con una altura efectiva de 120px realmente. Con
        ! estos 20px adicionales, nuestra imagen ya tendra espacio para dibujarse
        ! con su altura "real". Si no te gusta este comportamiento, define la
        ! constante BORDEWIN con valor cero antes de incluir SGW+DMX...
        ! Ejemplo: Constant BORDEWIN = 0;
        !===========================================================================
        !---------------------------------------------------------------------------
        ! si la ventana grafica superior no existe, ahora la abrimos
        if (gg_bigwin == 0) {
          gg_bigwin = glk_window_open(gg_mainwin,
            (winmethod_Above+winmethod_Fixed), h, wintype_Graphics, GG_BIGWIN_ROCK);
        }
        ! si la ventana grafica superior no se ha creado con exito...
        if (gg_bigwin == 0) { return; } ! no hacemos nada y retornamos
        !---------------------------------------------------------------------------
        ! Pintamos el fondo de la ventana grafica con el color que corresponde
        glk_window_set_background_color(gg_bigwin,SCBACK);
        glk_window_clear(gg_bigwin);
      #endif;
    #endif;
];

! ELIUK: Cierra la ventana grafica superior
[ closeGraphicWindow;
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        if (gg_bigwin) { ! si la ventana existe
          glk_window_close(gg_bigwin,0); ! la cerramos
          bigwin_alto = 0; ! dejamos de recordar altura
          gg_bigwin = 0;   ! limpiamos la referencia
        }
      #endif;
    #endif;
];

! ELIUK: Limpia el contenido de la ventana principal del juego
! (la ventana del buffer de texto y la ventana grafica superior)
[ clearMainWindow;
    clearGraphicWindow();
    clearTextWindow();
];

! ELIUK: Limpia solo la ventana grafica superior
[ clearGraphicWindow;
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        if (gg_bigwin) {
          glk_window_set_background_color(gg_bigwin,SCBACK);
          glk_window_clear(gg_bigwin);
        }
      #endif;
    #endif;
];

! ELIUK: Limpia solo la ventana del buffer de texto
[ clearTextWindow;
    #ifdef TARGET_GLULX;
      if (gg_quotewin) { ! si la ventana de "citas" esta abierta...
        glk_window_close(gg_quotewin,0); ! ... la cerramos ahora
        gg_quotewin = 0;
      }
      ! ELIUK: esto sirve solo para ventanas graficas...
      ! glk_window_set_background_color(gg_mainwin,SCBACK);
      glk_window_clear(gg_mainwin);
    #ifnot; ! COMPILACION PARA MAQUINA Z
      ClearScreen(WIN_MAIN); ! esta rutina viene por defecto en Lib. 6/11
    #endif;
];

! ELIUK: Limpia solo la ventana de la linea de estado
[ clearStatusLine;
    ClearScreen(WIN_STATUS); ! esta rutina viene por defecto en Lib. 6/11
];

! Close all windows
[ closeAllWindows;
    #ifdef TARGET_GLULX;
      if (gg_quotewin) { ! si la ventana de "citas" esta abierta...
        glk_window_close(gg_quotewin,0); ! ... la cerramos ahora
        gg_quotewin = 0;
      }
      #ifndef SGW_SIN_GRAFICOS;
        closeImageSlide();    ! cerramos ventana grafica de Slide
        closeGraphicWindow(); ! cerramos ventana grafica superior
      #endif;
    #endif;
];

! Centralized visualization routine - added by Paolo Maroncelli
[ viewImageSGW no_clear;   ! (c) Alpha
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        if (gg_bigwin) {
          if (~~no_clear) glk_window_clear(gg_bigwin);  ! (c) Alpha
          drawImageSGW(gg_bigwin,curr_pic,curr_pic_pos,BORDEWIN,BORDEWIN);
          !-----------------------------------------------------------------------
          ! NOTA SOBRE LOS ULTIMOS DOS ARGUMENTO (BORDEWIN,BORDEWIN):
          ! El 4to argumento (primer 'BORDEWIN') sirve para dejar un borde de
          ! 10px a la izquierda y a la derecha de la imagen. El 5to argumento
          ! (el otro 'BORDEWIN') sirve para dejar un borde de 10px arriba y
          ! abajo de la imagen. Esto se usa nada mas que por razones esteticas
          ! (para que los textos de la barra de estado y del buffer principal
          ! no "toquen" la imagen). Si no te gusta este comportamiento, define
          ! la constante BORDEWIN con valor cero antes de incluir SGW+DMX
          ! [ Ej: Constant BORDEWIN = 0; ]
        }
      #endif;
    #endif;
];

! View an image on the center of the main graphic window
[ viewImageCenter image no_clear;   ! (c) Alpha
    #ifdef TARGET_GLULX;
      curr_pic = image;
      curr_pic_pos = POS_CENTRADO;
      viewImageSGW(no_clear);       ! (c) Alpha
    #ifnot; ! COMPILACION PARA MAQUINA Z
      image = image; ! *** EVITA WARNING ***
    #endif;
];

! View an image on the left of the main graphic window
[ viewImageLeft image;
    #ifdef TARGET_GLULX;
      curr_pic = image;
      curr_pic_pos = POS_IZQUIERDA;
      viewImageSGW();
    #ifnot; ! COMPILACION PARA MAQUINA Z
      image = image; ! *** EVITA WARNING ***
    #endif;
];

! View an image on the right of the main graphic window
[ viewImageRight image;
    #ifdef TARGET_GLULX;
      curr_pic = image;
      curr_pic_pos = POS_DERECHA;
      viewImageSGW();
    #ifnot; ! COMPILACION PARA MAQUINA Z
      image = image; ! *** EVITA WARNING ***
    #endif;
];

! ELIUK: MUESTRA UNA IMAGEN (NO DEBE SER MUY GRANDE) EN LA VENTANA
! GRAFICA LATERAL PARA IMAGENES DE OBJETOS, CON EFECTO DE DESLIZAMIENTO
! (BASADA EN LA BUENA IDEA Y EN PARTE DEL CODIGO DE MAPACHE Y DEPRESIV)
[ viewImageSlide imagen flag
    ancho_img i; ! todas son variables auxiliares
    !-------------------------------------------------------------------------------
    ! EVITAR WARNINGS EN COMPILACION PARA CODIGO Z O CON SGW_SIN_GRAFICOS
      imagen    = imagen;
      flag      = flag;
      ancho_img = i;      ! no importa alterar estas dos variables
    !-------------------------------------------------------------------------------
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        ! si no se pueden pintar graficos...
        if (glk_gestalt(gestalt_Graphics,0) == 0) { return; } ! no hacemos nada

        ! primero cerramos la ventana, por si acaso
        closeImageSlide();

        ! si la imagen no existe...
        if (imagen == 0) { return; } ! terminamos con error

        ! calculamos ancho de la imagen para abrir una ventana apropiada
        glk_image_get_info(imagen,gg_arguments,gg_arguments+WORDSIZE);
        ancho_img = gg_arguments-->0;

        gg_objwin = 0; ! por si acaso (uno nunca sabe... =P)
        ! intentamos abrir la ventana con ancho suficiente para la imagen
        gg_objwin = glk_window_open(gg_mainwin,winmethod_Right+winmethod_Fixed,
          ancho_img+(BORDEWIN*2),wintype_Graphics,GG_OBJWIN_ROCK);

        ! si la ventana no se ha creado con exito...
        if (gg_objwin == 0) { return; } ! terminamos con error

        ! guardamos la imagen actual de la ventana de slide
        curr_obj_pic = imagen;

        ! si hay un Fade activo de Damusix, forzar "no-deslizamiento"
        #ifdef SGW_CON_DAMUSIX;
          if (Damusix.EnFade()) { flag = 1; }
        #endif; ! SGW_CON_DAMUSIX

        ! si queremos el efecto de deslizamiento
        if (~~flag) {
          ! metemos la imagen
          for (i=0 : i<=ancho_img : i=i+4) { ! NOTA: no cambiar el incremento de 'i'
            drawImageSlide(i);    ! pintamos la imagen
            slideViewPausa(15,i); ! hacemos la pausa (importante 'i')
          }
        }
        ! NO BORRAR: para corregir pequeño error de calculo en la posicion final
        ! de la imagen. (El error sucede por 'i=i+4' [mirar "metemos la imagen"],
        ! al final 'i' puede ser mayor que 'ancho_img' y no se ejecuta dibujado
        ! en la posicion final correcta. Con esto lo arreglamos.)
        drawImageSlide(ancho_img);

        ! si queremos el efecto de deslizamiento
        if (~~flag) {
          ! mostramos imagen durante 3 segundos para que se pueda observar
          slideViewPausa(3000,ancho_img); ! (importante 'ancho_img')
          !--------------------------------------------------------------------
          ! sacamos la imagen
          for (i=ancho_img : i>=0 : i=i-4) { ! NOTA: no cambiar el decremento de 'i'
            drawImageSlide(i);    ! pintamos la imagen
            slideViewPausa(15,i); ! hacemos la pausa (importante 'i')
          }
          ! NO BORRAR: para corregir pequeño error de calculo en la posicion final
          ! de imagen. (El error sucede por 'i=i-4' [mirar "sacamos la imagen"],
          ! al final 'i' puede ser menor a cero y no se ejecuta dibujado en la
          ! posicion final correcta. Con esto lo arreglamos.)
          drawImageSlide(-1*BORDEWIN);    ! VALOR NEG. PARA COMPENSAR RESTA INTERNA
          slideViewPausa(15,-1*BORDEWIN); ! IMPORTANTE, NO BORRAR
          !--------------------------------------------------------------------
          ! finalmente cerramos la ventana. Happy!! =D
          closeImageSlide();
        }
        ! AVISO: si el programador no quiere efecto de deslizamiento (activando flag),
        ! entonces debe encargarse el mismo de cerrar la ventana con closeImageSlide()
      #endif;
    #endif;
];

[ closeImageSlide ;
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        ! dejamos de recordar la imagen actual para la ventana de slide
        curr_obj_pic = 0;
        ! y si tambien existe la ventana (aun esta abieta), la cerramos
        if (gg_objwin) {
          glk_window_close(gg_objwin,0); ! la cerramos
          gg_objwin = 0;                 ! y limpiamos referencia
        }
      #endif;
    #endif;
];

#ifdef TARGET_GLULX;
  #ifndef SGW_SIN_GRAFICOS;
    !===========================================================================
    ! LAS SIGUIENTES RUTINAS *NUNCA* DEBEN LLAMARSE FUERA DE viewImageSlide()
    !---------------------------------------------------------------------------

    ! ELIUK: RUTINA PRINCIPAL DE DIBUJADO DE IMAGENES EN VENTANA CHICA (SLIDE)
    [ drawImageSlide pos ! se restara a la posicion actual
        alto_img ancho_win alto_win; ! todas son variables auxiliares
        !-----------------------------------------------------------------------
        ! calculamos el alto de la imagen
        glk_image_get_info(curr_obj_pic,gg_arguments,gg_arguments+WORDSIZE);
        alto_img = gg_arguments-->1;
        ! calculamos el tamaño de la ventana
        glk_window_get_size(gg_objwin,gg_arguments,gg_arguments+WORDSIZE);
        ancho_win = gg_arguments-->0;
        alto_win  = gg_arguments-->1;
        !-----------------------------------------------------------------------
        ! ponemos el color de fondo para la ventana
        glk_window_set_background_color(gg_objwin,SCBACK);
        ! limpiamos la ventana con el color de fondo
        glk_window_clear(gg_objwin);
        ! finalmente pintamos la imagen en la posicion que corresponde (y borde)
        glk_image_draw(gg_objwin,curr_obj_pic,(ancho_win-BORDEWIN)-pos,(alto_win-alto_img)/2);
    ];

    ! ELIUK: Hace una pausa con ayuda el Timer y re-pinta la imagen si es necesario
    [ slideViewPausa ms pos; ! ms: duracion pausa; pos: aux para drawImageSlide()
        ! si el timer de Glk no esta soportado...
        if (glk_gestalt(gestalt_Timer,0) == 0) { return; } ! no hacemos nada
        ! provocamos un 'tick' del Timer cada 'ms' milisegundos
        glk_request_timer_events(ms);
        for (::) { ! un bucle infinito
          glk_select(gg_arguments); ! averiguamos el evento generado
          switch (gg_arguments-->0) {
            evtype_Timer: ! se ha producido un Tick del Timer?
              jump FinSlideViewPausa; ! entonces debemos salir del bucle
            !-------------------------------------------------------------------
            evtype_Redraw, evtype_Arrange: ! cambios en las Ventanas Graficas?
              viewImageSGW();       ! repintamos ventana grande
              drawImageSlide(pos);  ! repintamos ventana chica (slide)
              DibujarLineaEstado(); ! repintamos barra de estado (por si acaso)
          }
        }
        .FinSlideViewPausa; ! etiqueta para salir del bucle
        ! finalmente detenemos los 'ticks' del Timer
        glk_request_timer_events(0);
    ];

    !---------------------------------------------------------------------------
    ! FIN DE RUTINAS DE SOPORTE ESPECIFICAS *SOLAMENTE* PARA viewImageSlide()
    !===========================================================================
  #endif;
#endif;

! ELIUK: RUTINA PRINCIPAL DE DIBUJADO DE IMAGENES EN VENTANA SUPERIOR
! (REDIMENSIONARA SI ES NECESARIO, CONSERVANDO LA RELACION DE ASPECTO)
[ drawImageSGW win img pos px py
    px_borde img_w img_h win_w win_h ww hh;
    !---------------------------------------------------------------------------
    ! NOTA:
    ! Argumentos 'px/py' sirven para aplicar un borde alrededor de la imagen
    ! que se va a dibujar. 'px' indica el tamaño en pixeles para los bordes
    ! izquierdo y derecho. 'py' indica el tamaño en pixeles para los bordes
    ! superior e inferior. Es muy util para dar un aspecto mas estetico a
    ! a la imagen si no queremos que se "toque" con las ventanas adyacentes.
    !---------------------------------------------------------------------------
    ! EVITAR WARNINGS EN COMPILACION PARA CODIGO Z O CON SGW_SIN_GRAFICOS
      win = win;
      img = img;
      pos = pos;
      px  = px;
      py  = py;
      win_w = win_h+img_w+img_h+ww+hh; ! no importa alterar estas vars.
    !---------------------------------------------------------------------------
      px_borde = px; ! para el truquito de las posiciones que SGW+DMX facilita
    !---------------------------------------------------------------------------
    #ifdef TARGET_GLULX;
      #ifndef SGW_SIN_GRAFICOS;
        ! si no se pueden pintar graficos...
        if (glk_gestalt(gestalt_Graphics,0) == 0) { return; } ! no hacemos nada
        ! si no hay ventana o si no hay imagen...
        if (win==0 || img==0) { return; } ! no hacemos nada
        !-----------------------------------------------------------------------
        ! averiguamos el tamaño original de la imagen
        glk_image_get_info(img,gg_arguments,gg_arguments+WORDSIZE);
        img_w = (gg_arguments-->0); ! ancho de la imagen
        img_h = (gg_arguments-->1); ! alto de la imagen
        !-----------------------------------------------------------------------
        ! averiguamos el tamaño de la ventana grafica
        glk_window_get_size(win,gg_arguments,gg_arguments+WORDSIZE);
        win_w = (gg_arguments-->0)-(px*2); ! ancho vent. (RESTA pixels_borde*2)
        win_h = (gg_arguments-->1)-(py*2); ! alto vent. (RESTA pixels_borde*2)
        !-----------------------------------------------------------------------
        ww = (win_w*100)/img_w; ! proporcion ancho de ventana respecto de imagen
        hh = (win_h*100)/img_h; ! proporcion alto de ventana respecto de imagen
          ! new_line;             ! -- DEBUG --
          ! print "xx: ",xx,".^"; ! -- DEBUG --
          ! print "yy: ",yy,".^"; ! -- DEBUG --
        !-----------------------------------------------------------------------
        ! si la proporcion de ancho es mayor o igual a la proporcion de
        ! alto, se debe escalar verticalmente la imagen (para compensar)
        if (ww>=hh) { ! '>=' El 'igual' es muy importante (corrige Bug)
            ! print "img_w original: ",img_w,".^"; ! -- DEBUG --
            ! print "img_h original: ",img_h,".^"; ! -- DEBUG --
          img_w = (img_w*hh)/100; ! IMPORTANTISIMO: CALCULO DE PROPORCIONES CON 'hh'
          img_h = (img_h*hh)/100; ! IMPORTANTISIMO: CALCULO DE PROPORCIONES CON 'hh'
          px = px+((win_w-img_w)/2); ! notar que suma valor del borde para 'eje x'
            ! print "img_w calculado: ",img_w,".^"; ! -- DEBUG --
            ! print "img_h calculado: ",img_h,".^"; ! -- DEBUG --
        }
        ! si la proporcion de alto es mayor que la proporcion de ancho,
        ! se debe escalar horizontalmente la imagen (para compensar)
        else if (hh>ww) {
            ! print "img_w original: ",img_w,".^"; ! -- DEBUG --
            ! print "img_h original: ",img_h,".^"; ! -- DEBUG --
          img_w = (img_w*ww)/100; ! IMPORTANTISIMO: CALCULO DE PROPORCIONES CON 'ww'
          img_h = (img_h*ww)/100; ! IMPORTANTISIMO: CALCULO DE PROPORCIONES CON 'ww'
          py = py+((win_h-img_h)/2); ! notar que suma valor del borde para 'eje y'
            ! print "img_w calculado: ",img_w,".^"; ! -- DEBUG --
            ! print "img_h calculado: ",img_h,".^"; ! -- DEBUG --
        }
        !-----------------------------------------------------------------------
        ! ESTE ES UN TRUQUITO PARA PERMITIR LAS POSICIONES QUE SGW+DMX FACILITA
        !glk_window_get_size(win,gg_arguments,0);
        switch (pos) {
          POS_IZQUIERDA:  px = px_borde;
          POS_DERECHA:    px = px_borde+(win_w-img_w);
        }
        !-----------------------------------------------------------------------
        ! DETERMINAMOS SI TENEMOS QUE PINTAR NORMAL (RAPIDO) O ESCALADO (LENTO)
        !-----------------------------------------------------------------------
        ! averiguamos nuevamente el tamaño original de la imagen
        glk_image_get_info(img,gg_arguments,gg_arguments+WORDSIZE);
        !-----------------------------------------------------------------------
        ! si el tamaño original y el "tamaño escalado" son iguales...
        if (img_w==(gg_arguments-->0) && img_h==(gg_arguments-->1)) {
          ! Mostramos la imagen con la rutina Glk de Dibujado Normal
          glk_image_draw(win,img,px,py);
            ! print "Normal.^"; ! -- DEBUG --
            ! print "Win W: ",win_w,", Img W: ", img_w,", Img WR: ",(gg_arguments-->0),".^"; ! -- DEBUG --
            ! print "Win H: ",win_h,", Img H: ", img_h,", Img HR: ",(gg_arguments-->1),".^"; ! -- DEBUG --
        }
        else { ! si el tamaño original y el "tamaño escalado" son distintos...
          ! Mostramos la imagen con la rutina Glk de Dibujado Escalado
          glk_image_draw_scaled(win,img,px,py,img_w,img_h);
            ! print "Escalado.^"; ! -- DEBUG --
            ! print "Win W: ",win_w,", Img W: ", img_w,", Img WR: ",(gg_arguments-->0),".^"; ! -- DEBUG --
            ! print "Win H: ",win_h,", Img H: ", img_h,", Img HR: ",(gg_arguments-->1),".^"; ! -- DEBUG --
        }
      #endif;
    #endif;
];


!===============================================================================
! FUNCIONES DE AUDIO
!-------------------------------------------------------------------------------

! Plays the sound "sound" for the channel "channel" , with "lenght" and "volume"
[ playSound channel sound lenght volume;
    !-------------------------------------------------------------------------------
    ! EVITAR WARNINGS EN COMPILACION PARA CODIGO Z O CON DAMUSIX INCLUIDA
      channel = channel;
      sound   = sound;
      lenght  = lenght;
      volume  = volume;
    !-------------------------------------------------------------------------------
    #ifdef TARGET_GLULX;
      #ifndef SGW_CON_DAMUSIX;
        if (gg_SoundSupport) {
          if (channel) {
            current_music = sound;
            glk_schannel_stop(channel);
            SetVolume(volume,channel);
            glk_schannel_play_ext(channel, sound, lenght, 0);
          }
        }
      #endif;
    #endif;
];

! Sileces all the audio channels
[ silenceAll;
    #ifdef TARGET_GLULX;
      #ifndef SGW_CON_DAMUSIX;
        if (gg_SoundSupport) {
          if (chan1) { glk_schannel_stop(chan1); }
          if (chan2) { glk_schannel_stop(chan2); }
          if (music) { glk_schannel_stop(music); }
        }
      #endif;
    #endif;
];

! Silences the channel "channel"
[ silenceChannel channel;
    !-------------------------------------------------------------------------------
    ! EVITAR WARNINGS EN COMPILACION PARA CODIGO Z O CON DAMUSIX INCLUIDA
      channel = channel;
    !-------------------------------------------------------------------------------
    #ifdef TARGET_GLULX;
      #ifndef SGW_CON_DAMUSIX;
        if (gg_SoundSupport) {
          if (channel) { glk_schannel_stop(channel); }
        }
      #endif;
    #endif;
];

! Set a volume for the channel
[ setVolume val chan;
    !-------------------------------------------------------------------------------
    ! EVITAR WARNINGS EN COMPILACION PARA CODIGO Z O CON DAMUSIX INCLUIDA
      val  = val;
      chan = chan;
    !-------------------------------------------------------------------------------
    #ifdef TARGET_GLULX;
      #ifndef SGW_CON_DAMUSIX;
        if (gg_SoundSupport) {
          if (~~gg_VolumeSupport) return; ! no volumen? terminamos aqui!
          if (val >= 0 || val <= 100) { ! siempre que este entre 0%-100%
            ! mejoro algoritmo de % de volumen (original era un poco extraño)
            ! [*** y puedo casi asegurar que no funcionaba del todo bien ***]
            glk_schannel_set_volume(chan, val*($10000/100));
          }
        }
      #endif;
    #endif;
];

! ESTA RUTINA ES NECESARIA PARA CALCULAR EL PORCENTAJE DE VOLUMEN DE LA MUSICA
! DE UNA LOCALIDAD SI SE USA DAMUSIX. RECORDAR QUE DAMUSIX UTILIZA UN SISTEMA
! DE PORCENTAJES DE VOLUMEN, PERO TAMBIEN TIENE UN 'VOLUMEN GLOBAL' QUE SE USA
! COMO MAXIMO PARA LOS CANALES. ESTA RUTINA HARA QUE SI EL PROGRAMADOR CAMBIA
! EL VOLUMEN GLOBAL DEL GESTOR, EL PORCENTAJE DE VOLUMEN DE LAS LOCALIDADES
! CONSERVE LA RELACION PORCENTUAL INDICADA, USANDO COMO MAXIMO PARA EL
! CALCULO EL VALOR ACTUAL DEL VOLUMEN GLOBAL DEL GESTOR DE DAMUSIX.
#ifdef TARGET_GLULX;
  #ifdef SGW_CON_DAMUSIX;
  [ CalcVol vol aux;
      aux = Damusix.QueVolumenCanal(DAMUSIX_NCANALMAX - 1); ! (c) Alpha
      if (aux == 0) { return 0; }                           ! (c) Alpha
      aux = Damusix.QueVolumenGlobal();
      if (aux == 0) { return 0; } ! COMPROBACION: evitar division por cero
      return (vol*aux)/100;       ! devolvemos el porcentaje de vol. corregido
      ! como Inform no usa numeros reales, calculo puede ser erroneo con cifras
      ! muy pequeñas. De momento, no es el caso (vol=100,75,50; pero nunca otro)
  ];
  #endif; ! SGW_CON_DAMUSIX
#endif; ! TARGET_GLULX


!===============================================================================
! OTRAS FUNCIONES DE UTILIDAD
!-------------------------------------------------------------------------------
! ELIUK: Esta rutina es un sencillo wrapper para un par de rutinas que ya
! existen por defecto en Lib. 6/11. Son biplataforma y funcionan muy bien,
! asi que hago el wrapper para no repetir codigo que trabaja perfectamente
[ wait msg tpo;
    ! se ha pasado una cadena valida?
    if (msg ofclass String && msg ~= 0) {
      print (string) msg;  ! entonces imprimela
    }
    #ifdef TARGET_GLULX;
      #ifdef SGW_CON_DAMUSIX;
        ! si hay un Fade activo de Damusix, forzar espera "no-temporizada"
        if (Damusix.EnFade()) { tpo = 0; }
      #endif; ! SGW_CON_DAMUSIX
    #endif; ! TARGET_GLULX
    ! ahora elegimos rutina de espera correcta dependiendo de...
    if (tpo > 0) { return KeyDelay(tpo); } ! ... hay temporizacion
    else { return KeyCharPrimitive(); }    ! ... no hay temporizacion
];


!===============================================================================
! FUNCIONES SOLO PARA GLULX
!-------------------------------------------------------------------------------
#ifdef TARGET_GLULX;

! Glk window initialization entry point.
[ InitGlkWindow winrock;
    switch (winrock) {
      GG_MAINWIN_ROCK:
        glk_stylehint_set(wintype_TextBuffer, style_Normal, stylehint_TextColor, SCTEXT);
        glk_stylehint_set(wintype_TextBuffer, style_Normal, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Emphasized, stylehint_TextColor, SCEMPH);
        glk_stylehint_set(wintype_TextBuffer, style_Emphasized, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Header, stylehint_TextColor, SCEMPH);
        glk_stylehint_set(wintype_TextBuffer, style_Header, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Subheader, stylehint_TextColor, SCHEAD);
        glk_stylehint_set(wintype_TextBuffer, style_Subheader, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Alert, stylehint_TextColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Alert, stylehint_BackColor, SCTEXT);
        glk_stylehint_set(wintype_TextBuffer, style_Note, stylehint_TextColor, SCEMPH);
        glk_stylehint_set(wintype_TextBuffer, style_Note, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Input, stylehint_TextColor, SCINPU);
        glk_stylehint_set(wintype_TextBuffer, style_Input, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_Preformatted, stylehint_TextColor, SCTEXT);
        glk_stylehint_set(wintype_TextBuffer, style_Preformatted, stylehint_BackColor, SCBACK);
        glk_stylehint_set(wintype_TextBuffer, style_User1, stylehint_TextColor, SCUSR1); ! ELIUK:
        glk_stylehint_set(wintype_TextBuffer, style_User1, stylehint_BackColor, SCBACK); ! Estilo User1
        glk_stylehint_set(wintype_TextBuffer, style_User2, stylehint_TextColor, SCUSR2); ! ELIUK:
        glk_stylehint_set(wintype_TextBuffer, style_User2, stylehint_BackColor, SCBACK); ! Estilo User2

      GG_STATUSWIN_ROCK:
        glk_stylehint_set(wintype_TextGrid, style_Normal, stylehint_TextColor, LITEXT); ! ElIUK:
        glk_stylehint_set(wintype_TextGrid, style_Normal, stylehint_BackColor, LIBACK); ! para barra

      GG_QUOTEWIN_ROCK:
        glk_stylehint_set(wintype_TextBuffer, style_Blockquote, stylehint_TextColor, SCEMPH); ! ElIUK:
        glk_stylehint_set(wintype_TextBuffer, style_Blockquote, stylehint_BackColor, SCBACK); ! para 'box'
        glk_stylehint_set(wintype_TextBuffer, style_BlockQuote, stylehint_Proportional, 0);
        glk_stylehint_set(wintype_TextBuffer, style_BlockQuote, stylehint_Justification, stylehint_just_Centered);
    }
    rfalse;
];

#ifndef SGW_CON_DAMUSIX; ! SIN DAMUSIX: IMPLEMENTAR NORMALMENTE LOS PUNTOS DE ENTRADA GLK
  ! el programador proporciona rutina IdentifyGlkObject() en el codigo del juego
  #ifdef IdentifyGlkObject;
    Message "[SGW+DMX: Usando rutina IdentifyGlkObject() proporcionada por el juego]";
    Message "[SGW+DMX: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
    Message "[SGW+DMX: -> < SGW_IdentifyGlk(fase,tipo,ref,rock) > ** OBLIGATORIO **]";
  #ifnot;
    [ IdentifyGlkObject fase tipo ref rock;
        ! IdentifyGlkObject de libreria SGW
        SGW_IdentifyGlk(fase,tipo,ref,rock);
    ];
  #endif; ! IdentifyGlkObject

  ! el programador proporciona rutina HandleGlkEvent() en el codigo del juego
  #ifdef HandleGlkEvent;
    Message "[SGW+DMX: Usando rutina HandleGlkEvent() proporcionada por el juego]";
    Message "[SGW+DMX: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
    Message "[SGW+DMX: -> < SGW_HandleGlk(ev) > ** OBLIGATORIO **]";
  #ifnot;
    [ HandleGlkEvent ev;
        ! HandleGlkEvent de libreria SGW
        SGW_HandleGlk(ev);
    ];
  #endif; ! HandleGlkEvent
#endif; ! SGW_CON_DAMUSIX

! IdentifyGlkObject de libreria SGW (Rutina Gancho)
[ SGW_IdentifyGlk fase tipo ref rock
    id; ! auxiliar
    id = 0; ! para evitar warning
    switch (fase) {
      0: ! start
         gg_bigwin    = 0;
         gg_objwin    = 0;
         gg_statuswin = 0;
         #ifndef SGW_CON_DAMUSIX;
           music = 0;
           chan1 = 0;
           chan2 = 0;
         #endif; ! SGW_CON_DAMUSIX
         return;

      1: ! pass ref
         switch (tipo) {
           0: ! window ref
           if (rock==GG_BIGWIN_ROCK) { gg_bigwin = ref; }
           if (rock==GG_OBJWIN_ROCK) { gg_objwin = ref; }
         }
         return;

      2: ! Update objects
         #ifndef SGW_CON_DAMUSIX;
           if(testSounds(0)) { ! Testeamos el soporte de sonidos (sin aviso)
             id = glk_schannel_iterate(0, gg_arguments);
             while (id) {
               switch (gg_arguments-->0) {
                 GG_MUSICCHAN_ROCK:        music = id;
                 GG_MUSICCHANSOUND1_ROCK:  chan1 = id;
                 GG_MUSICCHANSOUND2_ROCK:  chan2 = id;
               }
               id = glk_schannel_iterate(id, gg_arguments);
             }
           }
           ! reseteamos (detenemos) todos los canales de sonido...
           silenceAll(); ! se detienen canales 'music', 'chan1', 'chan2'
           #ifndef SGW_SIN_MARCO_DE_TRABAJO;
             ! este codigo corrige Bug si se hace UNDO y localidad tiene propiedad 'sgw_mus'
             if (localizacion_real provides sgw_mus) {
               if (localizacion_real provides sgw_vol) {
                 playSound(music,localizacion_real.sgw_mus,-1,localizacion_real.sgw_vol);
               }
               else {
                 playSound(music,localizacion_real.sgw_mus,-1,VOLUMEN_ALTO);
               }
             }
           #endif; ! SGW_SIN_MARCO_DE_TRABAJO
         #endif; ! SGW_CON_DAMUSIX
         openGraphicWindow(bigwin_alto); ! re-abrimos ventana grande (util al cargar partida)
         viewImageSGW();                 ! repintamos ventana grande (si estuviera abierta)
         viewImageSlide(curr_obj_pic,1); ! repintamos ventana chica (si estuviera abierta)
         return;
    }
];

! HandleGlkEvent de libreria SGW (Rutina Gancho)
[ SGW_HandleGlk ev;
    switch (ev-->0) {
      evtype_Redraw, evtype_Arrange: ! cambios en las Ventanas Graficas?
        viewImageSGW();              ! repintamos la ventana grande
        viewImageSlide(curr_obj_pic,1); ! repintamos la ventana chica (si estuviera abierta)
      !-------------------------------------------------------------------------
      !#ifndef SGW_CON_DAMUSIX;
      !  evtype_SoundNotify: glk_schannel_play_ext(music, current_music, 1, 1);
      !-------------------------------------------------------------------------
      ! La linea de arriba estaba sobrando, al parecer. No hace nada util...
      ! De hecho nunca se ejecuta... al menos no por la propia SGW...
      ! [la rutina playSound() de SGW *NUNCA* genera SoundNotifys]
      !#endif; ! SGW_CON_DAMUSIX
      !-------------------------------------------------------------------------
    }
];

! ELIUK: Testea el soporte de Graficos del Interprete Glulx
[ testGraphics flag aux;
    aux = true;  ! NO CAMBIAR - NO BORRAR (MUY IMPORTANTE)
    flag = flag; ! EVITA WARNINGS EN COMPILACION SIN GRAFICOS
    #ifndef SGW_SIN_GRAFICOS;
      if (~~glk_gestalt(gestalt_Graphics, 0)) {
        aux = false;
        if (flag) {
          print "^[¡Este Intérprete Glulx NO soporta Gráficos!]^";
        }
      }

      if (~~glk_gestalt(gestalt_GraphicsTransparency, 0)) {
        if (flag) {
          print "^[¡Este Intérprete Glulx NO soporta Transparencia!]^";
        }
      }
    #endif;
    return aux;
];

! ELIUK: Testea el soporte de Sonidos del Interprete Glulx
[ testSounds flag aux;
    aux = true;  ! NO CAMBIAR - NO BORRAR (MUY IMPORTANTE)
    flag = flag; ! EVITA WARNINGS EN COMPILACION SIN GRAFICOS
    #ifndef SGW_CON_DAMUSIX;
      ! NO BORRAR NI CAMBIAR las dos lineas siguientes...
      gg_SoundSupport = true;   ! reseteamos estos valores para...
      gg_VolumeSupport = true;  ! ... obtener una comprobacion 'limpia'

      if (~~glk_gestalt(gestalt_Sound, 0)) {
        aux = false;
        gg_SoundSupport = false; ! reportamos que no hay soporte de Sonido
        if (flag) {
          print "^[¡Este Intérprete Glulx NO soporta Sonido!]^";
        }
      }

      if (~~glk_gestalt(gestalt_SoundMusic, 0)) {
        aux = false;
        if (flag) {
          print "^[¡Este Intérprete Glulx NO soporta Música MOD!]^";
        }
      }

      if (~~glk_gestalt(gestalt_SoundVolume, 0)) {
        gg_VolumeSupport = false; ! reportamos que no hay soporte de Volumen
        if (flag) {
          print "^[¡Este Intérprete Glulx NO soporta Cambios de Volumen!]^";
        }
      }
    #endif; ! SGW_CON_DAMUSIX
    return aux;
];

!===============================================================================
! ************* MARCO DE TRABAJO (FRAMEWORK) CON AUTOMATIZACIONES *************
!-------------------------------------------------------------------------------
! > MOSTRAR IMAGENES Y TOCAR MUSICA (CON SU PROPIO VOLUMEN) PARA CADA LOCALIDAD
! > MOSTRAR AUTOMATICAMENTE LAS IMAGENES DE LOS OBJETOS ANTE LA ACCION EXAMINAR
!-------------------------------------------------------------------------------
#ifdef SGW_SIN_MARCO_DE_TRABAJO;
  Message "[SGW+DMX: Compilando sin el Marco de Trabajo... :( que triste!]";
#ifnot; ! se implementara automaticamente el Marco de Trabajo

  !-------------------------------------------------------------------------------
  ! Este objeto solo existe para evitar que el compilador haga warnings si alguna
  ! de las tres propiedades del Marco de Trabajo nunca se usa en codigo del juego
    Object with sgw_img, sgw_mus, sgw_vol; ! objeto 'tonto' para evitar warnings
  !-------------------------------------------------------------------------------

  #ifdef TrasElPrompt; ! el programador a definido su propia rutina TrasElPrompt()
    Message "[SGW+DMX: Usando rutina TrasElPrompt() proporcionada por el juego......]";
    Message "[SGW+DMX: -> SI QUIERES IMAGEN Y MUSICA AUTOMATICAS PARA CADA LOCALIDAD]";
    Message "[SGW+DMX: -> NO OLVIDES LLAMAR EN TU RUTINA A < SGW_MarcoDeTrabajo(1) >]";
  #ifnot; ! si no, la implementa el propio Marco de Trabajo
    [ TrasElPrompt ;
        SGW_MarcoDeTrabajo(1);
    ];
  #endif; ! TrasElPrompt

  #ifdef RutinaPostJuego; ! el programador a definido su propia rutina RutinaPostJuego()
    Message "[SGW+DMX: Usando rutina RutinaPostJuego() proporcionada por el juego...]";
    Message "[SGW+DMX: -> SI QUIERES MOSTRAR AUTOMATICAMENTE IMAGENES DE LOS OBJETOS]";
    Message "[SGW+DMX: -> NO OLVIDES LLAMAR EN TU RUTINA A < SGW_MarcoDeTrabajo(2) >]";
  #ifnot; ! si no, la implementa el propio Marco de Trabajo
    [ RutinaPostJuego ;
        SGW_MarcoDeTrabajo(2);
        rfalse; ! MUY IMPORTANTE: SIN ESTO NO SE MUESTRA NINGUN TEXTO
    ];
  #endif; ! RutinaPostJuego

  ! Centraliza las Actividades del Marco de Trabajo (aux == numero de actividad)
  [ SGW_MarcoDeTrabajo aux;
      ! SELECTOR DE LA ACTIVIDAD QUE DEBE REALIZAR EL MARCO DE TRABAJO
      switch (aux) {
        !------------------------------------------------------------------------
        ! ACTIVIDAD 1: Imagenes y Musica de Fondo automaticas para cada Localidad
        !------------------------------------------------------------------------
        1:
          if (current_loc == localizacion_real) { return; }
          else {
            current_loc = localizacion_real;
            #ifndef SGW_SIN_GRAFICOS;
              if (localizacion == laoscuridad) {
                #ifdef SGW_IMAGEN_OSCURIDAD;
                  viewImageCenter(SGW_IMAGEN_OSCURIDAD);
                #ifnot;
                  glk_window_set_background_color(gg_bigwin,SCBACK);
                  glk_window_clear(gg_bigwin);
                #endif; ! SGW_IMAGEN_OSCURIDAD
              }
              else {
                if (localizacion provides sgw_img) {
                  viewImageCenter(localizacion.sgw_img);
                }
                else {
                  glk_window_set_background_color(gg_bigwin,SCBACK);
                  glk_window_clear(gg_bigwin);
                }
              }
            #endif; ! SGW_SIN_GRAFICOS

            if (localizacion_real provides sgw_mus) {
              if (localizacion_real provides sgw_vol) {
                #ifndef SGW_CON_DAMUSIX;
                  playSound(music,localizacion_real.sgw_mus,-1,localizacion_real.sgw_vol);
                #ifnot;
                  if (Damusix.SonandoDeFondo(localizacion_real.sgw_mus) == 0) {
                    Damusix.AsignarCanal(localizacion_real.sgw_mus,DAMUSIX_NCANALMAX-1,CalcVol(localizacion_real.sgw_vol),-1);
                    Damusix.TocarCanal(DAMUSIX_NCANALMAX-1);
                  }
                  else { Damusix.Volumen(localizacion_real.sgw_mus,CalcVol(localizacion_real.sgw_vol)); }
                #endif; ! SGW_CON_DAMUSIX
              }
              else {
                #ifndef SGW_CON_DAMUSIX;
                  playSound(music,localizacion_real.sgw_mus,-1,VOLUMEN_ALTO);
                #ifnot;
                  if (Damusix.SonandoDeFondo(localizacion_real.sgw_mus) == 0) {
                    Damusix.AsignarCanal(localizacion_real.sgw_mus,DAMUSIX_NCANALMAX-1,CalcVol(VOLUMEN_ALTO),-1);
                    Damusix.TocarCanal(DAMUSIX_NCANALMAX-1);
                  }
                  else { Damusix.Volumen(localizacion_real.sgw_mus,CalcVol(VOLUMEN_ALTO)); }
                #endif; ! SGW_CON_DAMUSIX
              }
            }
            else {
              #ifndef SGW_CON_DAMUSIX;
                silenceChannel(music);
              #ifnot;
                Damusix.PararCanal(DAMUSIX_NCANALMAX-1); ! NOTA: usamos ultimo canal para musica de loc.
              #endif; ! SGW_CON_DAMUSIX
            }
          }
        !-----------------------------------------------------------------------
        ! = = = = = = = = = = = = = FIN DE ACTIVIDAD 1 = = = = = = = = = = = = =
        !-----------------------------------------------------------------------

        !-----------------------------------------------------------------------
        ! ACTIVIDAD 2: Imagenes automaticas al EXAMINAR cada Objeto
        !-----------------------------------------------------------------------
        2:
          if(accion == ##Examinar && uno provides sgw_img) {
            viewImageSlide(uno.sgw_img);
          }
          else {
            closeImageSlide();
          }
          ! NOTA: 'rfalse' necesario lo hacemos en la propia RutinaPostJuego()
        !-----------------------------------------------------------------------
        ! = = = = = = = = = = = = = FIN DE ACTIVIDAD 2 = = = = = = = = = = = = =
        !-----------------------------------------------------------------------

        !=======================================================================
        default: rfalse; ! con numero de actividad incorrecto, no hacemos nada
      }
  ];
#endif; ! SGW_SIN_MARCO_DE_TRABAJO

#endif; ! TARGET_GLULX

#endif; ! fin de _SGWDMX_H_
