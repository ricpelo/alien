!================================================================
! Espanol.h
!
! Número de Serie: 080625
!
! Definición de todo lo relacionado con el idioma Español (artículos,
! nombres, pre-parsing, etc.)
!
! Esta versión es biplataforma (Z/Glulxe), para usarse con InformATE!
! 6/10 y el compilador 6.10 o superior, preferiblemente con el
! compilador biplataforma de Andrew Plotkin.
!
! (C) Zak 2000, 2001
!
!

System_file;

! ---------------------------------------------------------------------------
!   Parte I.   Asuntos preliminares
! ---------------------------------------------------------------------------

Constant VersionIdioma = "Librería Española InformATE! 080625";

! Definición de caractéres "baratos". Esto permite que estas letras
! ocupen menos bits en la máquina Z. No funciona si se intenta la
! compilación por módulos.

#Ifdef TARGET_ZCODE;
  Zcharacter 'á';                    ! a con acento
  Zcharacter 'é';                    ! e con acento
  Zcharacter 'í';                    ! i con acento
  Zcharacter 'ó';                    ! o con acento
  Zcharacter 'ú';                    ! u con acento
  Zcharacter 'ñ';                    ! n con virguilla
  Zcharacter 'Ñ';                    ! N con virguilla
  Zcharacter 'ü';                    ! u con dieresis
  Zcharacter '¿';                    ! abrir interrogación
  Zcharacter '¡';                    ! abrir exclamación
#Endif;

!----------------------------------------------
! CONSTANTES Y CLASES ESPECIFICAS DE INFORMATE
!----------------------------------------------

Constant G_MASCULINO = 0;
Constant G_FEMENINO  = 1;
Constant G_PLURAL    = 3;

Class VerboIrregular;

!------------------------------------
! Globales específicas de InformatE!
!------------------------------------

global PreguntaCualExactamente = 0;
! Esta variable se pone a 1 cuando se le pregunta al jugador ¿Cuál
! exactamente...? esto indica que puede ser necesario re-traducir la
! respuesta que el jugador dé, ya que puede que simplemente el jugador
! cambie de idea y en lugar de responder a nuestra pregunta introduzca
! un comando completamente nuevo.

global PreguntaSiNo = 0;
! Esta variable debe ponerse a 1 manualmente si queremos que el verbo
! 'no' sea accesible como respuesta (y no como punto cardinal). La
! variable sólo afecta a la siguiente respuesta del jugador y vuelve a
! hacerse cero automáticamente.

Global bandera_todo_vale;
Global quitacentos = 1;
Global dialecto_sudamericano = 0;
Array  texto_impreso --> 52;


!--------------------------------------------------
! Atributos y propiedades específicas de InformatE!
!--------------------------------------------------

Property additive adjetivos;
Property genero 0;
Property imperativo alias name;
Property irrelevante alias name;
Property nombre alias name;
Property additive nombre_f;
Property additive nombre_fp;
Property nombre_m alias name;
Property additive nombre_mp;
Property si_abierta alias si_abierto;
Property si_apagada alias si_apagado;
Property si_cerrada alias si_cerrado;
Property si_encendida alias si_encendido;

#Ifdef ADMITIR_COMANDO_SALIDAS;
  Property salidas;
#Endif;

Attribute abierta   alias abierto;
Attribute encendida alias encendido;
Attribute estatica  alias estatico;
Attribute femenina  alias femenino;
Attribute movida    alias movido;
Attribute oculta    alias oculto;
Attribute puesta    alias puesto;
Attribute visitada  alias visitado;
Attribute nombreusado;

! Los dos siguientes nombres en inglés se usan en algunas rutinas de
! veneer, por eso es necesario que existan en su nombre original
! (la parte veneer es interna del compilador y no puede ser
! redefinida)

Attribute workflag alias banderaux;

#Ifdef DEBUG;
  [ DebugAttribute a;
    DepurarAtributo(a);
  ];
#Endif; ! DEBUG

!================================================================
! Los puntos cardinales
!================================================================

Class DireccionBrujula
  with
    articulos "El" "el" "",
    cantidad 0,
    descripcion [;
      if (MirarHaciaSub (self) == false)
        M__L (##MirarHacia, 0, self);  ! A partir de [020423] se utiliza un
                                       ! mensaje de librería
    ],
  has
    escenario;

Object Brujula "brújula"
  has
    oculto;

Ifndef SIN_DIRECCIONES;
  DireccionBrujula -> obj_n "norte"
    with
      nombre 'n//' 'norte' 'lado',
      direcc_puerta al_n;

  DireccionBrujula -> obj_s "sur"
    with
      nombre 's//' 'sur' 'lado',
      direcc_puerta al_s;

  DireccionBrujula -> obj_e "este"
    with
      nombre 'e//' 'este' 'lado',
      direcc_puerta al_e;

  DireccionBrujula -> obj_o "oeste"
    with
      nombre 'w//' 'o//' 'oeste' 'lado',
      direcc_puerta al_o;

  DireccionBrujula -> obj_ne "nordeste"
    with
      nombre 'ne' 'nordeste' 'noreste' 'lado',
      direcc_puerta al_ne;

  DireccionBrujula -> obj_no "noroeste"
    with
      nombre 'no' 'nw' 'noroeste' 'lado',
      direcc_puerta al_no;

  DireccionBrujula -> obj_se "sudeste"
    with
      nombre 'se' 'sureste' 'sudeste' 'lado',
      direcc_puerta al_se;

  DireccionBrujula -> obj_so "sudoeste"
    with
      nombre 'so' 'sw' 'suroeste' 'sudoeste' 'lado',
      direcc_puerta al_so;

  DireccionBrujula -> obj_arriba "arriba",
    with
      nombre 'u//' 'arriba' 'r//' 'sube' 'techo' 'lado' 'cielo',
      direcc_puerta arriba,
    has
      propio;

  DireccionBrujula -> obj_abajo "abajo"
    with
      nombre 'd//' 'abajo' 'b//' 'baja' 'suelo',
      direcc_puerta abajo,
    has
      propio;
Endif; ! SIN_DIRECCIONES

DireccionBrujula -> obj_afuera "exterior"
  with
    direcc_puerta afuera;

DireccionBrujula -> obj_adentro "interior"
  with
    direcc_puerta adentro;



! ---------------------------------------------------------------------------
!   Parte II.   Vocabulario
! ---------------------------------------------------------------------------
Constant OTRAVEZ1__WD = 'repetir';
Constant OTRAVEZ2__WD = 're';
Constant OTRAVEZ3__WD = 'g//';
Constant OOPS1__WD    = 'oops';
Constant OOPS2__WD    = 'epa';
Constant OOPS3__WD    = 'eepa';
Constant ANULAR1__WD  = 'undo';
Constant ANULAR2__WD  = 'deshacer';
Constant ANULAR3__WD  = 'anular';

Constant TODO1__WD    = 'todos';
Constant TODO2__WD    = 'todas';
Constant TODO3__WD    = 'todo';
Constant TODO4__WD    = 'ambos';
Constant TODO5__WD    = 'ambas';
Constant Y1__WD       = 'y//';
Constant Y2__WD       = 'y//';
Constant Y3__WD       = 'e//';
Constant SALVO1__WD   = 'excepto';
Constant SALVO2__WD   = 'menos';
Constant SALVO3__WD   = 'salvo';
Constant YO1__WD      = '-me';
Constant YO2__WD      = '-te';
Constant YO3__WD      = '-se';
Constant DE1__WD      = '.de';       ! no usados nunca, pues provocan
Constant DE2__WD      = '.de';       ! interferencia con la preposición "de"
Constant DE3__WD      = '.de';       ! usada por algunos verbos, como en
Constant DE4__WD      = '.de';       ! "saca objeto de la caja"
Constant OTRO1__WD    = 'otro';
Constant OTRO2__WD    = 'otra';
Constant OTRO3__WD    = 'otro';
Constant DESPUES1__WD = 'ydespues';
Constant DESPUES11_WD = 'despues';
Constant DESPUES2__WD = 'yluego';
Constant DESPUES21_WD = 'luego';
Constant DESPUES3__WD = 'yentonces';
Constant DESPUES31_WD = 'entonces';

Constant NO1__WD      = 'n//';
Constant NO2__WD      = 'no';
Constant NO3__WD      = 'no';
Constant SI1__WD      = 's//';
Constant SI2__WD      = 'si';
Constant SI3__WD      = 'si';

Constant CURIOSIDADES__WD = 'curiosidades';
Constant PUNTUACION1__WD  = 'puntuacion';
Constant PUNTUACION2__WD  = 'punt';
Constant TERMINAR1__WD    = 'q//';
Constant TERMINAR2__WD    = 'terminar';
Constant REINICIAR__WD    = 'reiniciar';
Constant RECUPERAR__WD    = 'recuperar';

Array IdiomaPronombres table

!   palabra  GNAs que pueden                conectado
!            seguirle:                      a:
!              a     i
!              s  p  s  p
!              mfnmfnmfnmfn

    '-lo'    $$101000100001                    NULL
    '-los'   $$000101000101                    NULL
    '-la'    $$010000010000                    NULL
    '-las'   $$000010000010                    NULL
    '-le'    $$110000110000                    NULL
    '-les'   $$000110000110                    NULL
    'él'     $$100000100000                    NULL
    'ella'   $$010000010000                    NULL
    'ellos'  $$000100000100                    NULL
    'ellas'  $$000010000010                    NULL;

Array IdiomaDescriptores table

    !palabra  GNAs que pueden     tipo de   conectado
    !              seguirles:  descriptor:       con:
    !          a     i
    !          s  p  s  p
    !          mfnmfnmfnmfn

    'mi'     $$110110110110    POSESIVO_PK      0
    'este'   $$100000100000    POSESIVO_PK      0
    'estos'  $$000100000100    POSESIVO_PK      0
    'esta'   $$010000010000    POSESIVO_PK      0
    'estas'  $$000010000010    POSESIVO_PK      0
    'ese'    $$100000100000    POSESIVO_PK      1
    'esa'    $$010000010000    POSESIVO_PK      1
    'esos'   $$000100000100    POSESIVO_PK      1
    'esas'   $$000010000010    POSESIVO_PK      1
    'su'     $$110000110000    POSESIVO_PK      '-le'
    'sus'    $$000110000110    POSESIVO_PK      '-le'
    'el'     $$100000100000    DEFINIDO_PK       NULL
    'la'     $$010000010000    DEFINIDO_PK       NULL
    'los'    $$000100000100    DEFINIDO_PK       NULL
    'las'    $$000010000010    DEFINIDO_PK       NULL
    'un'     $$100000100000    INDEFINIDO_PK     NULL
    'una'    $$010000010000    INDEFINIDO_PK     NULL
    'unos'   $$000100000100    INDEFINIDO_PK     NULL
    'unas'   $$000010000010    INDEFINIDO_PK     NULL
    'algún'  $$100000100000    INDEFINIDO_PK     NULL
   'algunos' $$000100000100    INDEFINIDO_PK     NULL
   'algunas' $$000010000010    INDEFINIDO_PK     NULL
 'encendido' $$100000100000    luz        	 NULL
 'encendida' $$010000010000    luz        	 NULL
'encendidos' $$000100000100    luz        	 NULL
'encendidas' $$000010000010    luz        	 NULL
   'apagado' $$100000100000    (-luz)     	 NULL
   'apagada' $$010000010000    (-luz)     	 NULL
  'apagados' $$000100000100    (-luz)     	 NULL
  'apagadas' $$000010000010    (-luz)     	 NULL;

Array IdiomaNumeros table
    'un' 1 'uno' 1 'una' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'dieciséis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19
    'veinte' 20;

! ---------------------------------------------------------------------------
!   Parte III.   Traducción
! ---------------------------------------------------------------------------

!---
! Funciones de ayuda a la depuración
!---

[ ImprimeBuffer b desde l i;
    for (i=desde:i<desde+l:i++)
	print (char) b->i;
];

[ ImprimeTodoElBuffer b;
#Ifdef TARGET_ZCODE;
   ImprimeBuffer(b, 2, b->1);
#Ifnot; !TARGET_GLULX
   ImprimeBuffer(b, WORDSIZE, b-->0);
#Endif;
];


!----------------------------------------------------------------
! [010515] Rutina nueva, que recibe una palabra de diccionario y un
! lugar donde buscar, y retorna "true" si alguno de los objetos de ese
! lugar tiene esa palabra en su campo nombre, nombre_f...
!
! Es usada por la rutina ArreglarLosY, pues se mira si la palabra que
! viene detrás de la Y es un nombre, y si lo es, si es aplicable a algún
! objeto cercano. Observar que fallará en los objetos que proporcionen
! su proio parse_nombre.
!----------------------------------------------------------------
[ EncajeSimplon w donde i;
  objectloop(i in donde) {
    if (PalabraEnPropiedad(w, i, nombre)) rtrue;
    if (PalabraEnPropiedad(w, i, nombre_f)) rtrue;
    if (PalabraEnPropiedad(w, i, nombre_mp)) rtrue;
    if (PalabraEnPropiedad(w, i, nombre_fp)) rtrue;
    if (PalabraEnPropiedad(w, i, adjetivos)) rtrue;
    if (children(i) && EncajeSimplon(w, i)) rtrue;
  }
  rfalse;
];


! ----------------------------------------------------------------------------
!  Las siguientes pueden ser útiles para los programadores de los
!  ficheros de definición de lenguaje
! ----------------------------------------------------------------------------

[ InsertarLetraBuffer i ch buf y;

    !   inserta el caracter ch en el buffer buf, en la posición i
    !   Cuidado de que el buffer no se desborde

#Ifdef TARGET_ZCODE;
    y = buf->1;
    if (y > buf->0) y = buf->0;
#Ifnot; !TARGET_GLULX
    y = buf-->0;
    if (y > INPUT_BUFFER_LEN) y = INPUT_BUFFER_LEN;
#Endif;

   !   Mover el texto siguiente una posición adelante
   for (y=y+WORDSIZE: y>i : y--) buf->y = buf->(y-1);

   ! Insertar la letra
   buf->i = ch;

  !   Ahora la longitud del texto se ha incrementado en 1
#Ifdef TARGET_ZCODE;
   if (buf->1 < buf->0)
    (buf->1)++;
#Ifnot; !TARGET_GLULX
    if (buf-->0 < INPUT_BUFFER_LEN)
      (buf-->0)++;
#Endif;
];


[ BorrarBuffer b p i;
    ! Rellena con espacios el buffer
    for (i=2:i<INPUT_BUFFER_LEN:i++) b->i=' ';
    Tokenise__(b, p);
];



!----------------------------------------------------------------
! QuitarAcentos
!
! La siguiente función prueba a quitar los acentos de las palabras que
! no hayan podido ser interpretadas. De este modo, el jugador puede usar
! o no los acentos. Para ello el juego debe definir las palabras sin acentos
! por ejemplo:
! object sillon "sillón confortable"
! with name 'sillon' 'confortable'
!
! Si el jugador pone: "mira sillon", la palabra encaja directamente y es
! comprendida. Si pone "mira sillón", no es comprendida, de modo que se
! le quita el acento y se reintenta el parsing.
!
! Este caso no es especialmente importante, pues el programador
! siempre puede definir 'sillon' y 'sillón', ambos como nombres para
! el objeto. Pero el asunto es más importante para el caso de los
! verbos, ya que si el jugador teclea "cógelo" este es separado en
! "cóge" y "-lo" y el verbo "cóge" (con acento) no sería
! comprendido.
!
! La llamada a esta función puede desactivarse con el comando de
! debugging "acentos sí" de modo que los acentos que teclee el jugador
! no serán eliminados (con propósitos de depuración)

#Ifdef TARGET_ZCODE;
[ QuitarAcentos buffer parse x i word at len;

#Ifdef DEBUG;
    if (parser_trace >= 7) ! imprimir el buffer recibido
    {
      	print "^[ QuitarAcentos:  ";
      	print "Buffer recibido: |";
	ImprimeTodoElBuffer(buffer);
      	print "|^  ";
    }
#Endif; ! DEBUG
    for (x=0:x<parse->1:x++) ! para cada palabra
    {
	word = parse-->(x*2 + 1);
	at = parse->(x*4 + 5);
	len = parse->(x*4 + 4);
	if (word==0) ! no comprendida
	{
#Ifdef DEBUG;
	    if (parser_trace>=7)
	    {
		print "NO COMPRENDIDO: |";
		ImprimeBuffer(buffer, at, len);
	    	print "|^";
	    }
#Endif; ! DEBUG
	    for (i=at:i<at+len:i++)
		switch(buffer->i)
		{
	    	 'á': buffer->i='a';
	    	 'é': buffer->i='e';
	    	 'í': buffer->i='i';
	    	 'ó': buffer->i='o';
	    	 'ú': buffer->i='u';
	    	 'ü': buffer->i='u';
	    	 'ñ': buffer->i='n';
!	    	 '?': buffer->i=' ';
!	    	 '¿': buffer->i=' ';
!	    	 '!': buffer->i=' ';
!		 '¡': buffer->i=' ' ;
		}
	    tokenise__(buffer, parse);
	}
    }

#Ifdef DEBUG;
    if (parser_trace>=7)
    {
	print "Buffer sin acentos: |";
	ImprimeTodoElBuffer(buffer);
    	print "|^";
    }
#Endif; ! DEBUG
];
#Ifnot; !TARGET_GLULX
[ QuitarAcentos buffer parse x i word at len;

#Ifdef DEBUG;
    if (parser_trace>=7) ! imprimir el buffer recibido
    {
      	print "^[ QuitarAcentos:  ";
      	print "Buffer recibido: |";
	ImprimeTodoElBuffer(buffer);
      	print "|^  ";
    }
#Endif; ! DEBUG
    for (x=0:x<parse-->0:x++) ! para cada palabra
    {
	word = parse-->(x*3 + 1);
	at = parse-->(x*3 + 3);
	len = parse-->(x*3 + 2);
	if (word==0) ! no comprendida
	{
#Ifdef DEBUG;
	    if (parser_trace>=7)
	    {
		print "NO COMPRENDIDO: |";
		ImprimeBuffer(buffer, at, len);
	    	print "|^";
	    }
#Endif; ! DEBUG
	    for (i=at:i<at+len:i++)
                ! [080625] Quitados caracteres en mayúscula
		switch(buffer->i)
		{
		  225: buffer->i='a';       ! 225: á
		  233: buffer->i='e';       ! 233: é
		  237: buffer->i='i';       ! 237: í
		  243: buffer->i='o';       ! 243: ó
		  250, 252: buffer->i='u';  ! 250: ú, 252: ü
		  241: buffer->i='n';       ! 241: ñ
!	    	 '?': buffer->i=' ';
!	    	 191: buffer->i=' ';
!	    	 '!': buffer->i=' ';
!		 161: buffer->i=' ' ;
		}
	    tokenise__(buffer, parse);
	}
    }

#Ifdef DEBUG;
    if (parser_trace>=7)
    {
	print "Buffer sin acentos: |";
	ImprimeTodoElBuffer(buffer);
    	print "|^";
    }
#Endif; ! DEBUG
];
#Endif; ! TARGET_



!-----------------------------------------------------
! IdiomaAInformes
!
! Esta parte es interesante. Debe separar los sufijos pronominales
! como en "cogela" "mirale", claro que no basta con ver si las dos
! últimas letras del verbo son "la" "le", etc, pues el verbo podría
! terminar de forma "natural" en esas letras (como en "habla"). Así
! que hay que separar el sufijo sólo si el verbo no ha sido hallado en
! el diccionario.
!
[ IdiomaAInformes ;
    EspanolAInformes(buffer, parse);
];

! La función que verdaderamente hace la traducción es la siguiente. Ha
! sido separada de IdiomaAInformes porque es llamada también desde
! IdiomaEsVerbo, pero recibe un buffer diferente para procesar.
#Ifdef TARGET_ZCODE;
[ EspanolAInformes buf pars x i word at len romper_en siguiente retokenise;

    tokenise__( buf, pars);
    retokenise=0;
#Ifdef DEBUG;
    if (parser_trace>=7) !imprimir el buf recibido
    {
      	print "^[ EspanolAInformes:  ";
      	print "Buffer recibido: |";
      	for(i=2:i<2+buf->1:i++) print (char) buf->i;
      	print "|^  ";
    }
#Endif; ! DEBUG
    if (quitacentos) QuitarAcentos(buf, pars);
    for (x=0:x<pars->1:x++) !para cada palabra
    {
	word = pars-->(x*2 + 1);
	at = pars->(x*4 + 5);
	len = pars->(x*4 + 4);
	if (dialecto_sudamericano && (word == 'coge'))
	{
	  ! Un poco bestia, pero funciona. En caso de dialecto sudamericano,
	  ! cambiar un par de letras convierte "coge" en "jode"
	  buf->(at)     = 'j';
	  buf->(at + 2) = 'd';
	  retokenise    = 1;
	  if (dialecto_sudamericano == 1)  ! [071030]
	  {
	    print "[Este juego utiliza por defecto el dialecto sudamericano,
		    por lo que aquí COGER es entendido como una palabra
		    malsonante. Por favor, utiliza TOMAR en su lugar, o bien
		    elige el dialecto castellano con DIALECTO CASTELLANO.]^";
	    dialecto_sudamericano = 2;
	  }
	}
	if (word=='del' or 'al')
	{
	    buf->(at+len-1)=' ';	! convertir "del" "al" en "de"
	                                ! "a" respectivamente
	    retokenise=1;
	}


	! Si el jugador ha escrito "no", y previamente el programador
	! había puesto a 1 el flag "PreguntaSiNo" (que indica que
	! acaba de hacerse una pregunta que podría admitir NO como
	! respuesta), en ese caso cambiamos "no" por "xo". La
	! gramática define el verbo "xo" para generar la acción NO
	! (negar), y así lo distinguimos de la acción "Ir noroeste"
	if ((word=='no')&&(PreguntaSiNo==1))
	{
	    buf->(at+len-1)='x';
	    PreguntaSiNo=0;
	    retokenise=1;
	}

        ! "pegar" las expresiones "y luego" "y despues" "y entonces"
        ! para que queden "yluego" "ydespues" "yentonces"
        ! que es como las reconoce el parser
        if (word=='y//')
	{
	   siguiente= pars-->((x+1)*2+1);
	   if (siguiente==DESPUES11_WD or DESPUES21_WD or DESPUES31_WD)
	   {
	       for (i=1:i<(pars->((x+1)*4+4))+2:i++)
                   buf->(at+i)=buf->(at+i+1);
	       retokenise=1;
	   }
	}
	if (word==0) ! no comprendida
	{
#Ifdef DEBUG;
	    if (parser_trace>=7)
	    {
		print "NO COMPRENDIDO: |";
	    	for (i=at:i<at+len:i++) print (char) buf->i;
	    	print "|^";
	    }
#Endif; ! DEBUG

	    if (len > 2) !sólo si tiene más de tres letras
	    {
		romper_en=0;
		if ((buf->(at+len-1)=='s') &&
		    (buf->(at+len-2)=='a' or 'o' or 'e') &&
		    (buf->(at+len-3)=='l'))
		    romper_en=3;
		if ((buf->(at+len-1)=='a' or 'o' or 'e') &&
		    (buf->(at+len-2)=='l'))
		    romper_en=2;
		if ((buf->(at+len-1)=='e') &&
		    (buf->(at+len-2)=='m' or 't' or 's'))
		    romper_en=2;  ! [001108] Antes ponía == ¡seré burro!
		if (romper_en)
		{
		    ! [990524]
		    ! Antes de modificar el buffer, comprobemos si
		    ! servirá para algo, es decir, si la palabra que
		    ! queda una vez separado el sufijo existe en el
		    ! diccionario y es un verbo
		    i=BuscarEnDiccionario(buf+at, len-romper_en);

		    if (i) if ((i->#dict_par1)&1)
		    {
		    	InsertarLetraBuffer(at+len-romper_en, '-', buf);
		    	InsertarLetraBuffer(at+len-romper_en, ' ', buf);
		    	tokenise__(buf,pars);
		    }
		    !#Ifdef ADMITIR_INFINITIVOS;
		    if (QuitandoRFinal(buf+at, len-romper_en)||
			BuscarEntreVerbosIrregulares(buf+at, len-romper_en))
		    {
		    	InsertarLetraBuffer(at+len-romper_en, '-', buf);
		    	InsertarLetraBuffer(at+len-romper_en, ' ', buf);
			tokenise__(buf,pars);
		    }
!#Endif;
                }
	    }
	}
    }

    tokenise__(buf, pars);
    ArreglarLosY(buf, pars);

    ! Como paso final, quitamos las palabras que aparezcan dos veces
    ! seguidas. Esto puede ocurrir si el jugador teclea un comando
    ! incompleto, como "MIRA HACIA", y el parser le pregunta "¿Hacia
    ! donde quieres mirar?" y el jugador responde "HACIA EL NORTE". En
    ! este caso se construiría la orden concatenada: "MIRA HACIA HACIA
    ! EL NORTE".
    if (PreguntaCualExactamente==1)
    {
	PreguntaCualExactamente=0;
    	EliminarDuplicados(buf, pars);
    }

#Ifdef DEBUG;
    if (parser_trace>=7)
    {
	print "Buffer traducido a informese: ^|";
	for (i=2:i<2+buf->1:i++)
	    print (char) buffer->i;
	print "| (", pars->1," palabras) ^";
    }
#Endif; ! DEBUG
];


[ ArreglarLosY buf pars
    word at len x i retoke;

    for (x=0:x<pars->1:x++) !para cada palabra
    {
	word = pars-->(x*2 + 1);
	if (word=='y//')
	{
	    i= pars-->((x+1)*2+1); ! Palabra siguiente
	    ! [010515] arreglado bug. at y len no apuntaban a la
	    ! palabra siguiente, sino a la propia 'y', por lo que no
	    ! eran reconocidos los verbos en infinitivo
	    at = parse->(x*4 + 9);
	    len = parse->(x*4 + 8);

	    ! [010515] Añadido. Si la palabra es noun, se retorna
	    ! (aunque pueda ser también un verbo) de este modo, en
	    ! COGE VINO Y CAVA, si el juego tiene un objeto llamado
	    ! "cava", la frase será parseada como tratando de coger
	    ! dos objetos, llamados "vino" y "cava". Si el juego no
	    ! define el sustantivo "cava", la frase será parseada como
	    ! dos acciones en secuencia <<Coger vino>> y <<Excavar>>
	    if (i && (i->#dict_par1)&128) {
	      if (EncajeSimplon(i, localizacion)) continue;
	    }
	    if (i && ((i->#dict_par1)&1)||QuitandoRFinal(buf+at,len)||
		BuscarEntreVerbosIrregulares(buf+at, len))
	    {
	    	at = parse->(x*4 + 5);
		buf->(at)='.';
		retoke=true;
	    }
	}
    }
    if (retoke) tokenise__(buf, pars);
];
#Endif;
#Ifdef TARGET_GLULX; ! TARGET_GLULX
[ EspanolAInformes buf pars x i word at len romper_en siguiente retokenise;

    retokenise=0;
#Ifdef DEBUG;
    if (parser_trace>=7) !imprimir el buf recibido
    {
      	print "^[ EspanolAInformes:  ";
      	print "Buffer recibido: |";
	ImprimeTodoElBuffer(buf);
      	print "|^  ";
    }
#Endif; ! DEBUG
    if (quitacentos) QuitarAcentos(buf, pars);
    for (x=0:x<pars-->0:x++) !para cada palabra
    {
	word = pars-->(x*3 + 1);
	len = pars-->(x*3 + 2);
	at = pars-->(x*3 + 3);
	if (dialecto_sudamericano && (word == 'coge'))
	{
	  ! Un poco bestia, pero funciona. En caso de dialecto sudamericano,
	  ! cambiar un par de letras convierte "coge" en "jode"
	  buf->(at)     = 'j';
	  buf->(at + 2) = 'd';
	  retokenise    = 1;
	  if (dialecto_sudamericano == 1)  ! [071030]
	  {
	    print "[Este juego utiliza por defecto el dialecto sudamericano,
		    por lo que aquí COGER es entendido como una palabra
		    malsonante. Por favor, utiliza TOMAR en su lugar, o bien
		    elige el dialecto castellano con DIALECTO CASTELLANO.]^";
	    dialecto_sudamericano = 2;
	  }
	}
	if (word=='del' or 'al')
	{
	    buf->(at+len-1)=' ';	! convertir "del" "al" en "de"
	                                ! "a" respectivamente
	    retokenise=1;
	}


	! Si el jugador ha escrito "no", y previamente el programador
	! había puesto a 1 el flag "PreguntaSiNo" (que indica que
	! acaba de hacerse una pregunta que podría admitir NO como
	! respuesta), en ese caso cambiamos "no" por "xo". La
	! gramática define el verbo "xo" para generar la acción NO
	! (negar), y así lo distinguimos de la acción "Ir noroeste"
	if ((word=='no')&&(PreguntaSiNo==1))
	{
	    buf->(at+len-1)='x';
	    PreguntaSiNo=0;
	    retokenise=1;
	}

        ! "pegar" las expresiones "y luego" "y despues" "y entonces"
        ! para que queden "yluego" "ydespues" "yentonces"
        ! que es como las reconoce el parser
        if (word=='y//')
	{
	   siguiente= pars-->((x+1)*3+1);
	   if (siguiente==DESPUES11_WD or DESPUES21_WD or DESPUES31_WD)
	   {
	       for (i=1:i<(pars-->((x+1)*3+2))+2:i++)
                   buf->(at+i)=buf->(at+i+1);
	       retokenise=1;
	   }
	}
	if (word==0) ! no comprendida
	{
#Ifdef DEBUG;
	    if (parser_trace>=7)
	    {
		print "NO COMPRENDIDO: |";
		ImprimeBuffer(buf, at, len);
	    	print "|^";
	    }
#Endif; ! DEBUG

	    if (len > 2) !sólo si tiene más de tres letras
	    {
		romper_en=0;
		if ((buf->(at+len-1)=='s') &&
		    (buf->(at+len-2)=='a' or 'o' or 'e') &&
		    (buf->(at+len-3)=='l'))
		    romper_en=3;
		if ((buf->(at+len-1)=='a' or 'o' or 'e') &&
		    (buf->(at+len-2)=='l'))
		    romper_en=2;
		if ((buf->(at+len-1)=='e') &&
		    (buf->(at+len-2)=='m' or 't' or 's'))
		    romper_en=2;
		if (romper_en)
		{
		    ! [990524]
		    ! Antes de modificar el buffer, comprobemos si
		    ! servirá para algo, es decir, si la palabra que
		    ! queda una vez separado el sufijo existe en el
		    ! diccionario y es un verbo
		    i=BuscarEnDiccionario(buf+at, len-romper_en);
		    if (i) if ((i->#dict_par1)&1)
		    {
		    	InsertarLetraBuffer(at+len-romper_en, '-', buf);
		    	InsertarLetraBuffer(at+len-romper_en, ' ', buf);
		    	tokenise__(buf,pars);
		    }
		    !#Ifdef ADMITIR_INFINITIVOS;
		    if (QuitandoRFinal(buf+at, len-romper_en)||
			BuscarEntreVerbosIrregulares(buf+at, len-romper_en))
		    {
		    	InsertarLetraBuffer(at+len-romper_en, '-', buf);
		    	InsertarLetraBuffer(at+len-romper_en, ' ', buf);
			tokenise__(buf,pars);
		    }
!		    #Endif;
		}
	    }
	}
    }

    if (retokenise==1)
	tokenise__(buf, pars);

    ArreglarLosY(buf, pars);
    ! Como paso final, quitamos las palabras que aparezcan dos veces
    ! seguidas. Esto puede ocurrir si el jugador teclea un comando
    ! incompleto, como "MIRA HACIA", y el parser le pregunta "¿Hacia
    ! donde quieres mirar?" y el jugador responde "HACIA EL NORTE". En
    ! este caso se construiría la orden concatenada: "MIRA HACIA HACIA
    ! EL NORTE".
    if (PreguntaCualExactamente==1)
    {
	PreguntaCualExactamente=0;
    	EliminarDuplicados(buf, pars);
    }

#Ifdef DEBUG;
    if (parser_trace>=7)
    {
	print "Buffer traducido a informese: ^|";
	ImprimeTodoElBuffer(buf);
	print "| (", pars-->0," palabras) ^";
    }
#Endif; ! DEBUG
];

[ ArreglarLosY buf pars
    word at len x i retoke;

    for (x=0:x<pars-->0:x++) !para cada palabra
    {
	word = pars-->(x*3 + 1);
	if (word=='y//')
	{
	    i= pars-->((x+1)*3+1); ! Palabra siguiente
	    ! [010515] arreglado bug. at y len no apuntaban a la
	    ! palabra siguiente, sino a la propia 'y', por lo que no
	    ! eran reconocidos los verbos en infinitivo.
	    len = pars-->(x*3 + 5);
	    at = pars-->(x*3 + 6);
	    ! [010515] Añadido. Si la palabra es noun, se retorna
	    ! (aunque pueda ser también un verbo) de este modo, en
	    ! COGE VINO Y CAVA, si el juego tiene un objeto llamado
	    ! "cava", la frase será parseada como tratando de coger
	    ! dos objetos, llamados "vino" y "cava". Si el juego no
	    ! define el sustantivo "cava", la frase será parseada como
	    ! dos acciones en secuencia <<Coger vino>> y <<Excavar>>
	    if (i && (i->#dict_par1)&128) {
	      if (EncajeSimplon(i, localizacion)) continue;
	    }
	    if (i && ((i->#dict_par1)&1)||QuitandoRFinal(buf+at,len)||
		BuscarEntreVerbosIrregulares(buf+at, len))
	    {
	    	at = pars-->(x*3 + 3);
		buf->(at)='.';
		retoke=true;
	    }
	}
    }
    if (retoke) tokenise__(buf, pars);
];

#Endif; !TARGET_

#Ifdef TARGET_ZCODE;
[ EliminarDuplicados buf pars
    word at len x i siguiente cambiado;

!    @tokenise buffer parse;
#Ifdef DEBUG;
    if (parser_trace>=8) !imprimir el buffer recibido
    {
      	print "^[ EliminarDuplicados:  ";
      	print "Buffer recibido: |";
        ImprimeTodoElBuffer(buf);
      	print "| (", pars->1, " palabras)^";
    }
#Endif; ! DEBUG
    for (x=0:x<(pars->1)-1:x++) !para cada palabra
    {
	word = pars-->(x*2 + 1);
	siguiente = pars-->((x+1)*2 +1);
	at = pars->(x*4 + 5);
	len = pars->(x*4 + 4);
	if ((word==siguiente) && (word~=0))
	{
#Ifdef DEBUG;
	    if (parser_trace>=8) print "¡Encontrados duplicados!:",
		(address) word, "=", (address) siguiente, ".^";
#Endif; ! DEBUG
	    for (i=at:i<at+len:i++) buf->i=' ';
	    cambiado=1;
	}
    }
    if (cambiado)
	tokenise__(buf, pars);
];
#Endif;
#Ifdef TARGET_GLULX;
[ EliminarDuplicados buf pars
    word at len x i siguiente cambiado;

    tokenise__(buf, pars);
#Ifdef DEBUG;
    if (parser_trace>=8) ! imprimir el buffer recibido
    {
      	print "^[ EliminarDuplicados:  ";
      	print "Buffer recibido: |";
        ImprimeTodoElBuffer(buf);
      	print "| (", pars-->0, " palabras)^";
    }
#Endif; ! DEBUG
    for (x=0:x<(pars-->0)-1:x++) !para cada palabra
    {
	word = pars-->(x*3 + 1);
	siguiente = pars-->((x+1)*3 +1);
	len = pars-->(x*3 + 2);
	at = pars-->(x*3 + 3);
	if ((word==siguiente) && (word~=0))
	{
#Ifdef DEBUG;
	    if (parser_trace>=8) print "¡Encontrados duplicados!:",
		(address) word, "=", (address) siguiente, ".^";
#Endif; ! DEBUG
	    for (i=at:i<at+len:i++) buf->i=' ';
	    cambiado=1;
	}
    }
    if (cambiado)
	tokenise__(buf, pars);
];
#Endif;


! La siguiente función debe devolver si el verbo recibido es
! reconocido o no. Se recibe el buffer completo y "pos" indica qué
! palabra dentro del buffer "pars" es el supuesto verbo.
! Hay que devolver la dirección de diccionario del verbo en cuestión.
!
! Lo usamos para admitir infinitivos. El método es:
!   Si la palabra corresponde a una palabra de diccionario, no hacemos
!   nada (retornamos esa palabra, sin molestarnos en comprobar que sea
!   un verbo. Ya lo hará el parser).
!
!   Si la palabra no está en el diccionario, miramos si termina en
!   'r', y de ser así se la quitamos y re-tokenizamos. Si de este modo
!   se obtiene una palabra en el diccionario, retornamos su valor (sin
!   comprobar que sea un verbo, ya lo hará el parser).
!
!   Si tampoco de este modo se reconoce, comparamos la palabra dada
!   con todos los verbos irregulares conocidos. Si en uno de ellos
!   encontramos coincidencia, retornamos el primer elemento de la
!   propiedad "imperativo" del verbo en cuestión.
!
[ IdiomaEsVerbo buf pars pos
    i;

    pos--;
#Ifdef DEBUG;
    if (parser_trace>=7) !imprimir el buffer recibido
    {
	print "^[ IdiomaEsVerbo:  ";
	print "Buffer recibido: |";
	ImprimeTodoElBuffer(buf);
	print "|, pos=", pos, "^  ";
    }
#Endif; ! DEBUG
    if (PreguntaCualExactamente)
	EspanolAInformes(buf, pars);

    ! Si la palabra se reconoce, devolverla sin más
#Ifdef TARGET_ZCODE;
    if (pars-->(pos*2+1)~=0)
    {
#Ifdef DEBUG;
	if (parser_trace>=7) print " el verbo ~", (address)
	    pars-->(pos*2+1), "~ está en el diccionario.^";
#Endif; ! DEBUG
	return	(pars-->(pos*2+1));
    }
#Ifnot; ! TARGET_GLULX
    if (pars-->(pos*3+1)~=0)
    {
#Ifdef DEBUG;
	if (parser_trace>=7) print " el verbo ~", (address)
	    pars-->(pos*3+1), "~ está en el diccionario.^";
#Endif; ! DEBUG
	return	(pars-->(pos*3+1));
    }
#Endif; ! TARGET_

!Ifdef ADMITIR_INFINITIVOS;

    ! Si no, probar a ver si se reconoce sin la 'r' final
#Ifdef TARGET_ZCODE;
    i=QuitandoRFinal(buf + pars->((pos+1)*4+1),
		     pars->((pos+1)*4));
#Ifnot; ! TARGET_GLULX
    i=QuitandoRFinal(buf + pars-->(pos*3 + 3), pars-->(pos*3 +2));
#Endif; ! TARGET_


! Si no la ha reconocido, intentamos ver si es un verbo irregular
    if (i~=0)
    {
#Ifdef DEBUG;
	if (parser_trace>=7) print "^ Verbo reconocido
	    al quitarle la 'r' final.^]";
#Endif; ! DEBUG
    }
    else
    {
#Ifdef DEBUG;
	if (parser_trace>=7) print "^ Verbo no reconocido sin la
	    'r'. ^Probando irregulares...";
#Endif; ! DEBUG
#Ifdef TARGET_ZCODE;
	i=BuscarEntreVerbosIrregulares(buf + pars->((pos+1)*4+1),
		     		       pars->((pos+1)*4));
#Ifnot; ! TARGET_GLULX
        i=BuscarEntreVerbosIrregulares(buf + pars-->(pos*3 + 3),
				       pars-->(pos*3 +2));
#Endif; ! TARGET_
#Ifdef DEBUG;
	if (parser_trace>=7)
	{
	    if (i==0) print "No reconocido como irregular.^";
	    else print "Reconocido como el verbo ", (address) i, "^";
	}
#Endif; ! DEBUG
    }
!#Endif;
    return i;
];
!#Endif;

!#Ifdef ADMITIR_INFINITIVOS;
[ QuitandoRFinal texto longitud
    i;

#Ifdef DEBUG;
    if (parser_trace>=9) {
	print "^[ QuitandoRFinal: buffer recibido |";
	ImprimeBuffer(texto, 0, longitud);
	print "|^";
    }
#Endif; ! DEBUG
    if (texto->(longitud-1)~='r')
    {
#Ifdef DEBUG;
	if (parser_trace>=9) print "No termina en 'r'^";
#Endif; ! DEBUG
	return 0;
    }

    i=BuscarEnDiccionario(texto, longitud-1);
    if (dialecto_sudamericano && (i == 'coge'))
    {
      if (dialecto_sudamericano == 1)  ! [071030]
      {
        print "[Este juego utiliza por defecto el dialecto sudamericano,
                por lo que aquí COGER es entendido como una palabra
                malsonante. Por favor, utiliza TOMAR en su lugar, o bien
                elige el dialecto castellano con DIALECTO CASTELLANO.]^";
        dialecto_sudamericano = 2;
      }
      return 'jode';
    }
    if ((i->#dict_par1)&1) return i;
    else
    {
#Ifdef DEBUG;
	if (parser_trace>=9) print "Está en el diccionario, pero no es
	    verbo.^";
#Endif; ! DEBUG
	return 0;
    }
];

[ BuscarEntreVerbosIrregulares texto longitud
    verbo i k;

    objectloop (verbo ofclass VerboIrregular)
    {
#Ifdef DEBUG;
	if (parser_trace>=8) print "^[Buscando irregulares. Probando
	    con ~", (name) verbo, "~.-->";
#Endif; ! DEBUG
#Ifdef TARGET_ZCODE;
	texto_impreso-->0 = 50;
    	@output_stream 3 texto_impreso;
    	print (name) verbo;
    	@output_stream -3;
	k=texto_impreso-->0;
#Endif;
#Ifdef TARGET_GLULX;
        k=PrintAnyToArray(texto_impreso+WORDSIZE, 46, verbo);
#Endif; !TARGET_

    	!Si sus longitudes no coinciden no es necesario seguir comparando
    	if (k~=longitud) jump NoCoincide;

    	!Si sus longitudes coinciden, miramos letra a letra
    	for (i=0:i<k:i++)
    	    if ((texto->i)~=(texto_impreso->(i+WORDSIZE)))
		jump NoCoincide; ! si una sola letra no coincide,
	! Si ha pasado los test anteriores, hemos hallado una
	! coincidencia
#Ifdef DEBUG;
	if (parser_trace>=8) print "¡coincide!^";
#Endif; ! DEBUG
	return (verbo.&imperativo-->0);

	.NoCoincide;
#Ifdef DEBUG;
	if (parser_trace>=8) print "no coincide^";
#Endif; ! DEBUG
    }
    return 0;
];
!#Endif;




! ---------------------------------------------------------------------------
!   Parte IV.   Imprimir
! ---------------------------------------------------------------------------


! Definimos una función para imprimir el verbo coger. Esto hace más fácil
! la adaptación de los juegos a los dialectos sudamericanos, en los
! que debe usarse "tomar" en lugar de "coger"
!
! La variable global que elige el dialecto se fija en tiempo de
! ejecución con el meta-verbo "dialecto". También puede fijarse en
! Inicializar para que su valor por defecto sea 1.
!
[ coge sufijo;
    if (dialecto_sudamericano)
	print "toma";
    else print "coge";
    print (string) sufijo;
];

! La siguiente es la versión con la primera letra mayúscula

[ MCoge sufijo;
    if (dialecto_sudamericano)
	print "Toma";
    else print "Coge";
    print (string) sufijo;
];

! Y finalmente una versión con todo mayúsculas

[ MMCoge sufijo;
    if (dialecto_sudamericano)
	print "TOMA";
    else print "COGE";
    print (string) sufijo;
];



Constant IdiomaGeneroAnimado   = masculino;
Constant IdiomaGeneroInanimado = masculino;

Constant IdiomaContracciones = 1;     ! Para el español
! No se produce contracción del artículo. Sólo de las preposiciones
! como en "del" y "al", pero eso no está contemplado por el manual
! del traductor, por lo que es necesario otro tipo de truco

[ IdiomaContraccion ;
    return 0;
];

Array IdiomaArticulos -->
    ! Forma de contracción 0:
    ! Cdef   Def  Indef
    "El " "el " "un "
    "La " "la " "una "
    "Los " "los " "unos "
    "Las " "las " "unas ";

                 !             a           i
                 !             s     p     s     p
                 !             m f n m f n m f n m f n
Array IdiomaGNAsAArticulos --> 0 1 0 2 3 2 0 1 0 2 3 2;

[ IdiomaDirecciones d;
    switch(d)
 {   al_n: print "norte";
     al_s: print "sur";
     al_e: print "este";
     al_o: print "oeste";
     al_ne: print "nordeste";
     al_no: print "noroeste";
     al_se: print "sudeste";
     al_so: print "suroeste";
     arriba: print "arriba";
     abajo: print "abajo";
     adentro: print "dentro";
     afuera: print "fuera";
     default: return ErrorDeEjecucion(9,d);
    }
];

[ IdiomaNumero n venti m;
    if (n==0) { print "cero"; rfalse; }
    if (n<0) { print "menos "; n=-n; }
    if (n>=1000) {
    	if (n<2000) print "mil";
    	else { IdiomaNumero(n/1000,1); print " mil";}
        n=n%1000;
        if (n~=0) print " ";
        }
    if (n>=100)  {
	 CientosEspanol(n/100);
         if (n%100~=0) print " ";
	 n=n%100;
    }
    if (n==0) rfalse;

    if (n<10) {
	DigitoEspanol(n); rfalse; }
    if (n>=20)
    {   m=n/10;
      	if (n%10~=0) {
      	    if (m==2) print "veinti";
      	} else {
      	    if (m==2) print "veinte";
      	}
        if (m==3) print "treinta";
      	if (m==4) print "cuarenta";
      	if (m==5) print "cincuenta";
      	if (m==6) print "sesenta";
      	if (m==7) print "setenta";
      	if (m==8) print "ochenta";
      	if (m==9) print "noventa";
      	if (n%10==0) rfalse;
      	if (m>2) print " y ";
      	DigitoEspanol(n%10, (m==2)&&(venti==0)); rfalse;
    }
    if (n==10) { print "diez"; rfalse; }
    if (n==11) { print "once"; rfalse; }
    if (n==12) { print "doce"; rfalse; }
    if (n==13) { print "trece"; rfalse; }
    if (n==14) { print "catorce"; rfalse; }
    if (n==15) { print "quince"; rfalse; }
    if (n==16) { print "dieciséis"; rfalse; }
    if (n==17) { print "diecisiete"; rfalse; }
    if (n==18) { print "dieciocho"; rfalse; }
    print "diecinueve";
];

[ DigitoEspanol n venti;
    if (n==1) { print "un"; rfalse; }
    if (n==2) {
         if (venti) {print "dós";} else {print "dos"; };
         rfalse; }
    if (n==3) {
         if (venti) {print "trés";} else {print "tres"; };
         rfalse; }
    if (n==4) { print "cuatro"; rfalse; }
    if (n==5) { print "cinco"; rfalse; }
    if (n==6) {
         if (venti) {print "séis";} else {print "seis"; };
         rfalse; }
    if (n==7) { print "siete"; rfalse; }
    if (n==8) { print "ocho"; rfalse; }
    if (n==9) { print "nueve"; rfalse; }
];

[ CientosEspanol n;

if (n==1) { print "ciento"; rfalse; }
if (n==2) { print "dos";}
if (n==3) { print "tres";}
if (n==4) { print "cuatro";}
if (n==5) { print "quinientos"; rfalse;}
if (n==6) { print "seis";}
if (n==7) { print "sete";}
if (n==8) { print "ocho";}
if (n==9) { print "nove";}
print "cientos"; rfalse;
];

[ IdiomaHoraDelDia hours mins i;
   i = hours%12;
   if (i == 0) i = 12;
   if (i < 10) print " ";
   print i, ":", mins/10, mins%10;
   if ((hours/12) > 0) print " pm"; else print " am";
];

[ IdiomaVerbo i aux;

    if (ImprimirIrregular(i)==0)
    {
	if (ImprimirVerbo(i)==0){
 	    print (address) i; print "r";
    	}
    }

    if (i=='mete') rtrue;

#Ifdef TARGET_ZCODE;
    ! Comprobemos si era un verbo reflexivo (-te)
    !
    texto_impreso-->0 = 50;
    @output_stream 3 texto_impreso;
    print (address) i;
    @output_stream -3;
    aux=2;
    if (texto_impreso->(texto_impreso->1+1)=='e')
    if (texto_impreso->(texto_impreso->1) == 't' or 's' or 'm')
    {
	if (actor ~= jugador) print "se";
	    else print (string) PARTICULA_TE;
    }
#Endif;
#Ifdef TARGET_GLULX;
    aux=PrintAnyToArray(texto_impreso, 50, i);
    if ((texto_impreso->(aux-1)=='e')&&
	(texto_impreso->(aux-2) == 't' or 's' or 'm'))
    {
	if (actor ~= jugador) print "se";
	    else print (string) PARTICULA_TE;
    }
#Endif;
    rtrue;

];


[ ImprimirIrregular v i;
  ! Imprime los verbos irregulares (es decir, aquellos en los que no basta
  ! añadir una "r" al imperativo). Por ejemplo, si el jugador teclea "friega"
  ! la respuesta por defecto sería "¿Qué quieres friegar?"
  ! Para evitar esto, el programador debe definir un objeto de la clase
  ! VerboIrregular, con nombre "fregar" y propiedad name = "friega"
  ! Esta rutina busca entre los verbos así definidos, en el campo name
  ! y si encuentra una coincidencia imprime el nombre del objeto para
  ! el cual se halló.

  ! Para mayor flexibilidad aún, se permite que el programador incluya
  ! una rutina en la propiedad nombre_corto del verbo, por si el nombre
  ! del verbo a imprimir es variable según el momento en que se llame.
  ! Si existe nombre_corto para el verbo en cuestión, se ejecuta dicha rutina
  ! de lo contrario se imprime el nombre de ese verbo sin más.

  ! Ver SpanishG.h para ejemplos de declaración de verbos irregulares.

  objectloop (i ofclass VerboIrregular)
   if (PalabraEnPropiedad(v, i, imperativo)) {
     if (i.&nombre_corto~=0) return(ImprimirOEjecutar(i, nombre_corto, 1));
     else { print (name) i; rtrue;}}
  rfalse;
];


Constant TECLASIG__TX   = "S = Siguiente";
Constant TECLAANT__TX   = "    P=Previo";
Constant QKEY1__TX      = "Q=Volver al juego";
Constant QKEY2__TX      = "Q = Menú anterior";
Constant RKEY__TX       = "INTRO = leer este tema";

Constant TECLASIG1__KY  = 'S';
Constant TECLASIG2__KY  = 's';
Constant TECLAANT1__KY  = 'P';
Constant TECLAANT2__KY  = 'p';
Constant QKEY1__KY      = 'Q';
Constant QKEY2__KY      = 'q';

Constant PUNTUACION__TX = "Punt.: ";
Constant JUGADAS__TX    = "Movim.: ";
Constant HORA__TX       = "Hora: ";
Constant NOPUEDESIR__TX = "No puedes ir por ahí.";
Constant PREVIOYO__TX   = "tu antiguo ~yo~";
Constant TUMISMO__TX    = "ti mismo";
Constant OSCURIDAD__TX  = "Oscuridad";

! En la revisión [020415] las constantes HAY*__TX se han trasladado al
! fichero Mensajes, pues dependen del tiempo, persona y número verbales.

Constant ESASC__TX      = "esas cosas";
Constant ESO__TX        = "eso";
Constant O__TX          = " o ";
Constant NADA__TX       = "nada";
Constant Y__TX          = " y ";
Constant QUIEN__TX      = "que ";  ! Al parecer, aquí sobraban los espacios
Constant ELCUAL__TX     = "que ";  ! de antes de los 'que'. [020423]

! Funciones para manejar concordancias de género y número en los
! mensajes de respuesta genéricos.
!
! o -> escribe la terminación -o -a -os -as según el género y número
! del objeto recibido, para hacer concordar los adjetivos.
!
! n -> escribe la terminación -"" -n según el número del objeto, para
! hacer concordar el verbo en plural.
!
! esta -> escribe "está" o "están" según el número del objeto.
!
! del -> escribe "del" "de la" "de los" "de las" según el género y
! número del objeto. En realidad, determina qué artículo habría de ir
! y si éste es "el" realiza la contracción "del".
!
! al -> como del, pero con "al" "a la" "a los" "a las".
!
! lo -> Escribe "lo" "la" "le" "los" "las" "les" (pronombre) según el
! género y número del objeto y según sea animado o no.
!

[ o obj gna;

    gna=ObtenerGNADeObjeto(obj);
    switch(gna)
    {
     0,6: print "o";
     1,7: print "a";
     3,9: print "os";
     4,10: print "as";
    }
];

[ e obj gna;

    gna=ObtenerGNADeObjeto(obj);
    switch(gna)
    {
     0,6: print "e";
     1,7: print "a";
     3,9: print "es";
     4,10: print "as";
    }
];


[ n obj;
    if (obj == jugador) print "s";
    else if (obj has nombreplural) print "n";
];

[ s obj;
    if (obj has nombreplural) print "s";
];

[ esta obj;
    print "está", (n) obj;
];

[ es obj;
    if (obj has nombreplural) print "son";
    else print "es";
];

[ _Es obj;
    if (obj has nombreplural) print "Son";
    else print "Es";
];

[ _s obj;
    if (obj has nombreplural) print "es";
];

[ el_ obj;
    if (obj hasnt propio) PonerArticuloDelante(obj,1,-1);
];

[ un_ obj;
    if (obj hasnt propio) PonerArticuloDelante(obj,2,-1);
];


[ el obj;
    print (the) obj;
];

[ _El obj;
    print (The) obj;
];

![ un obj;
!    if (un_(obj)) print " ";
!    print (name) obj;
!];

[ un obj;
  if (obj has propio) print "a ";
  print (a) obj;
];


[ _nombre_ obj;
    print (name) obj;
];

[ numero obj;
    print (number) obj;
];


! "al" y "del" plantean un bonito problema. La contracción debe
! producirse si el artículo es "el", pero esto no se sabe consultando
! el GNA, pues hay palabras como "aguila" que son femeninas y no
! obstante usan "el" como artículo.
! El truquillo consiste en llamar a (el) para averiguar qué artículo
! se imprimiría (pero capturando la salida de ese print y guardándola
! en una variable). Si el artículo en cuestión empieza por 'e', se
! produce la contracción.
!
! Para capturar la salida a una variable, es necesario descender al
! lenguaje ensamblador de la Z machine. Este truco lo aprendí del
! Designers manual (respuesta al ejercicio 96, página 249)
!
[ del_ obj;
    if (obj has propio) {        ! 030305
            print "de ";
            rtrue;
    }

#Ifdef TARGET_ZCODE;
    texto_impreso-->0 = 50;
    @output_stream 3 texto_impreso;
    print (the)obj;
    @output_stream -3;
    if (texto_impreso->2 == 'e') print "d";
    else print "de ";
#Ifnot; !TARGET_GLULX
    PrintAnyToArray(texto_impreso, 50, PonerArticuloDelante, obj, 1, -1);
    if (texto_impreso->0 == 'e') print "d";
    else print "de ";
#Endif;
    if (obj hasnt propio) PonerArticuloDelante(obj, 1, -1);
];

! Con "al" el truco es más complejo, ya que si el artículo impreso por
! el_ empieza por "e", hay que cambiar esta "e" por una "a". Y si no
! empieza por "e" hay que poner una "a" delante.
! Además debemos capturar el caso de que no se imprima artículo alguno
! (si el objeto proporciona una propiedad "articulos" con cadenas
! vacías).

#Ifdef TARGET_ZCODE;
[ al_ obj;
    texto_impreso-->0 = 50;
    @output_stream 3 texto_impreso;
    print (the) obj;
    @output_stream -3;
    if (texto_impreso->2 == 'e') print "al ";
    else {
       print "a ";
       if (obj hasnt propio)
          PonerArticuloDelante(obj, 1, -1);
	 }
];
#Endif;
#Ifdef TARGET_GLULX;
[ al_ obj;
    ! [080625] Llamaremos aquí a Defart en lugar de PonerArticuloDelante,
    ! para imitar el comportamiento de al_ en la Máquina-Z, y corregir
    ! así la respuesta ante objetos con nombre propio en Glulx.
    PrintAnyToArray (texto_impreso, 50, Defart, obj);
    if (texto_impreso->0 == 'e') print "al ";
    else {
       print "a ";
       if (obj hasnt propio)
          PonerArticuloDelante(obj, 1, -1);
	 }
];
#Endif; !TARGET_

[ del obj;
    print (del_) obj;
    print (name) obj;
];

[ al obj;
    print (al_) obj;
    print (name) obj;
];


[ lo obj gna;
    gna=ObtenerGNADeObjeto(obj);
    switch(gna)
    {
     0,6: print "lo";
     1,7: print "la";
     3,9: print "los";
     4,10: print "las";
    }
];


! Cuando el usuario teclea un comando incompleto, es necesario que
! el parser genere un mensaje preguntando por lo que falta,
! pero la forma de preguntarlo depende del verbo. Por ej.:
!
! > coge
! ¿Qué quieres coger?
!
! > mete llave
! ¿Dónde quieres meter la llave?
!
! > orco, saca la botella
! ¿De dónde tiene que sacar el orco la botella?
!
! Cuando el parser tiene que imprimir una respuesta de estas,
! simplemente llama a MLIdioma con el número de mensaje Misc, 48 o
! 49. En esta versión de la librería (6/7) es responsabilidad de
! MLIdioma generar el mensaje completo.
!
! En nuestro caso hemos implementado estos mensajes de forma que
! llaman a IniciarPregunta para que escriba una partícula interrogativa
! como "Donde" "De donde", etc. Si no escribe nada, MLIdioma pone
! "Qué" o "A quién" según el tipo de error, a continuación se escribe
! "quieres" o "tiene que" según quién sea el actor. Se llama a
! IdiomaVerbo para que escriba el verbo, y finalmente se añade el
! nombre del objeto directo si lo había, para terminar la pregunta
! cerrando la interrogación.
!
! IniciarPregunta, lo que hace es:
!
! 1) busca preposiciones en el patrón que ha encajado, si las
! encuentra, la pregunta debe comenzar por alguna partícula
! interrogativa. Por ejemplo, si la línea de gramática hallada era
! "saca" uno "de" uno, se hallará la preposición "de" que nos indica
! que la pregunta ha de comenzar con "¿De dónde ...".
!
! 2) Llama a la función "IdiomaPreguntarPrep" que recibe como
! parámetros la preposición y la acción en curso, para que imprima la
! partícula interrogativa adecuada. Esta función tan sólo debe
! escribir esa partícula.
!
! IdiomaPreguntarPrep llama a su vez a PreguntarPreposicion por si el
! programador añade verbos raros con preposiciones raras que no son
! correctamente manejados por esta rutina. Si PreguntarPreposicion
! existe y retorna distinto de cero, IdiomaPreguntarPrep asumirá
! que la partícula interrogativa ya ha sido escrita por
! PreguntarPreposicion y no hará nada más.
!
[ IdiomaPreguntarPrep prepos accion;

    if (PreguntarPreposicion(prepos, accion)) return;

    switch (prepos)
    {
     'de': print "De dónde";
     'en', 'dentro', 'encima': print "Dónde";
     'bajo','debajo':print "Debajo de qué";
     'sobre', 'acerca':print "Sobre qué";
     'contra': print "Contra qué";
     'hacia':print "Hacia dónde";
     'con':if (accion==##Hablar or ##Atacar)  print "Con quién";
	else print "Con qué";
     'por':if (accion==##Preguntar) print "Por qué";
	else print "Por dónde";
     'una', 'un' : print "A quién";
     #n$a:  switch(accion)
     {
      ##Ir:                  print "Hacia dónde";
      ##Meterse, ##Trepar:      print "Dónde";
      ##Lanzar, ##Dar, ##Mostrar, ##Responder, ##Hablar, ##Preguntar:
	 print "A quién";
      ##BuscarEn:              print "A través de qué";
      ##Atar:                 print "A qué";
      ##Transferir:            print "A dónde";
      default:               print "A quién";
     };
    }
];

! A partir del patrón que ha construido el parser, se determina cuál
! es la primera preposición usada detrás del verbo.
! Esto será usado por la función IniciarPregunta y por IdiomaEsVerbo
!
[ AveriguarPreposicion
    ;
    if (patron-->(contadorp-1) >= CODIGO_REPARSE)
	return (Num__DirDicc((patron-->(contadorp-1))-CODIGO_REPARSE));
    else return NULL;
];

[ AveriguarPrimeraPreposicion
    i k p found;
    p=NULL;
    for (k=contadorp:k>=1:k--)
    {
	if (patron-->k == PATRON_NULO) continue;
	i=patron-->k;
    	if (i>=CODIGO_REPARSE)
    	{
	    i=Num__DirDicc(i-CODIGO_REPARSE);
	    p=i;    ! nos quedamos con la primera
	    found=k;
    	}
    }
    if (found==(contadorp -1)) return NULL;
    else return p;
];


! Averigua si es necesaria una partícula interrogativa. Llama a
! IdiomaPreguntarPrep para que la imprima.
!
! Retorna 1 si ha sido impresa la partícula interrogativa, y 0 en caso
! contrario, (y entonces la función que la llamó "MLIdioma", sabe
! que es necesario escribir "Qué" o "A quién" ya que en este caso lo
! que faltaba era el objeto directo en lugar del complemento.
!
[ IniciarPregunta
    p;

    print "¿";
    p=AveriguarPreposicion();
    if (p~=NULL) {
	IdiomaPreguntarPrep(p, accion_que_seria);
	return 1;
	}
    return 0;

];

[ IdiomaImprimirComando from i k spacing_flag prep;

  if (from==0)
  {   i=palabra_verbo;
      if (IdiomaVerbo(i) == 0)
          if (ImprimirVerbo(i) == 0)
              print (address) i;
      from++; spacing_flag = true;
  }

  for (k=from:k<contadorp:k++)
  {   i=patron-->k;
      if (i == PATRON_NULO) continue;
!      if (spacing_flag) print (char) ' ';
      if (i==0) {
	  ! [990701] Verificar si la preposicion es NULL antes de
	  ! tratar de imprimirla. Gracias a Alpha Aventuras
	  prep=AveriguarPrimeraPreposicion();
	  if (prep~=NULL)
	      print " ",(address) prep;
	  print " ", (string) ESASC__TX; jump TokenPrinted;
      }
      if (i==1) {
	  prep=AveriguarPrimeraPreposicion();
	  if (prep~=NULL)
	      print " ",(address) prep;
	  print " ",(string) ESO__TX; jump TokenPrinted;
      }
      if (i>=CODIGO_REPARSE) continue;
      else {
	  if (i==jugador) print "te";
	  else  {
	      prep=AveriguarPrimeraPreposicion();
	      switch(prep){
	       'a//': print " ", (al) i;
	       'de': print " ", (del) i;
	       NULL: print " ", (el) i;
 	       default: print " ", (address) prep, " ", (el) i;
	      }
	  }
	  continue;
      }
      .TokenPrinted;
      spacing_flag = true;
  }
];


! [001115]
! Los mensajes de librería van ahora en fichero aparte
! [010515] Cambiado de sitio el punto de inclusión de Mensajes.h
! para dar la oportunidad al usuario de incluir su propio Mensajes
! si lo desea (antes del include Gramatica)
! Include "Mensajes";


[ IdiomaImprimirNombreCorto obj aux;

    aux=aux;
    if (obj provides genero)
    {
#Ifdef DEBUG;
	if (parser_trace>=10)
	    print "[",  obj, " tiene ~genero~=", obj.genero,
	    	".]^";
	aux=debug_flag; debug_flag=0;
#Endif; ! DEBUG
        switch(obj.genero)
    	{
     	 0: give obj ~femenino ~nombreplural;
     	 1: give obj femenino ~nombreplural;
     	 3: give obj ~femenino nombreplural;
     	 4: give obj femenino nombreplural;
    	}
#Ifdef DEBUG;
    debug_flag=aux;
#Endif; ! DEBUG
    	rfalse;
    }

    else{
#Ifdef DEBUG;
	if (parser_trace>=10)
	    print "[", obj, " no tiene la propiedad ~genero~.]";
#Endif; ! DEBUG
	rfalse;
    }
];


! Esta función de elegir objetos asigna más puntuación al objeto que
! ha sido llamado por su 'nombre' (por tanto toman prioridad sobre los
! que son llamados solo por su 'adjetivo'). Se excluye al propio
! jugador de la lista, y los objetos de escenario.

[ EligeObjetos obj codigo prio;

    prio=ElegirObjetos(obj,codigo);
    if (codigo>=2)
    {
    	if (obj has nombreusado){
 	    if (bandera_todo_vale==0) prio=prio+10;
	}
	if ((obj == jugador) || ((obj has escenario) && (obj notin Brujula)))
	  prio=prio-10;
    }
    return prio;
];
