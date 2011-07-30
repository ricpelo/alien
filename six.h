! SIX.h v2.2
!----------------------------------------------------------------
!
!  La versión SIX de la máquina Z utiliza un modelo de pantalla
! rígido, definido en VSIX.doc. Esta implementación (v2.0) es
! biplataforma, lo que significa que puede generar código tanto para
! la máquina Z6 (SIX) como para Glulx.
!
!  En el caso de generación Glulx, se respeta exactamente el mismo
! modelo de pantalla, a pesar de que Glk soportaría una flexibilidad
! mucho  mayor. Para aprovechar esta flexibilidad habría que programar
! directamente con llamadas a Glk o usar otra librería específica para
! Glk.
!
! La ventaja de SIX es que permite que un mismo programa sin cambios
! pueda compilarse para ser ejecutado con IznoguZ (interprete Z que
! admite la versión SIX) o con Glulxe.
!
!  (c) 2000 Zak McKracken
!
! Modificaciones:
!  1.0   Primera versión
!  2.0   Versión biplataforma Z/Glulx
!  2.1   Mejoradas un par de funciones:
!         EsperarTecla() Ahora funciona también si no recibe
!            parámetros
!         BorrarPantalla() Cierra la ventana de Boxes bajo Glulx,
!            además de borrar la pantalla principal
!  2.2   Las constantes de alineamiento sólo se definen si no estaban
!        ya definidas, para hacer compatible la librería con infglk.h
!

System_file;
#Ifndef imagealign_InlineUp;
Constant imagealign_InlineUp     1;
#Endif;
#Ifndef imagealign_InlineDown;
Constant imagealign_InlineDown   2;
#Endif;
#Ifndef imagealign_InlineCenter;
Constant imagealign_InlineCenter 3; 
#Endif;
#Ifndef imagealign_MarginLeft;
Constant imagealign_MarginLeft   4; 
#Endif;
#Ifndef imagealign_MarginRight;
Constant imagealign_MarginRight  5; 
#Endif;

!================================================================
! Conjunto de rutinas de inicialización específicas para Glk
!================================================================
! (solo se compilan si el objetivo es Glulx)

#ifndef TARGET_ZCODE;
! En primer lugar, todas las funciones horribles de bajo nivel que
! necesita Glk para inicializar sus objetos
!
! Constantes y variable para identificar a la ventana gráfica dentro
! de la lista de objetos creados por Glk
Constant GG_VENTANAGRAFICA_ROCK 210;
Global gg_ventanagrafica = 0;


! La rutina IdentifyGlkObject (que debe ser programada como parte del
! juego) es llamada por la librería, para que tomes nota de qué
! objetos Glk existen. (Esto es necesario porque después de un comando
! restore, restart o undo, puede que las variables globales que
! contenían referencias a objetos Glk tengan valores erróneos)
!
! Tendrán lugar tres fases
!
! * La librería llama a IdentifyGlkObject() con fase==0. Aquí la
! rutina debe inicializar con cero  todas las referencias a objetos
! Glk.
!
! * La librería llama a IdentifyGlkObject() con fase==1. Esto ocurre
! una vez para cada ventana, stream o fileref que no sean reconocidos
! por la librería (la librería ya conoce las ventanas, streams y
! filerefs que ella misma ha abierto, que son la ventana para la línea
! de estado, la ventana principal del texto, y los ficheros y streams
! relacionados con las operaciones de guardar juego, transcribir texto
! o almacenar comandos. Los objetos de los que tú debes ocuparte es de
! los que tú hayas creado). Debes inicializar la referencia adecuada
! para el objeto. En el parámetro "tipo"  recibes el tipo de objeto
! (0, 1 y 2 para ventanas, streams y ficheros respectivamente). En el
! parámetro "ref" recibes el valor que hay que asignarle a la
! referencia, y en "rock" una constante que identifica unívocamente al
! objeto GLK (el valor de "rock" con que fue creado)
!
! * La librería llama a IdentifyGlkObject() con fase==2. Esto ocurre
! una vez, después de las otras llamadas, y te da la oportunidad de
! reconocer objetos que no son ventanas, streams o ficheros. Si no has
! creado ningún objeto así, puedes ignorar este trozo.
!
! Pero también puedes aprovechar para actualizar todos tus objetos
! Glk, de acuerdo con el estado que acaba de ser restaurado. Por
! ejemplo, repintar los gráficos o activar un sonido de fondo
! adecuado.
!
[ IdentifyGlkObject fase tipo ref rock;
    if (fase == 0) {
        ! Inicializar a cero todos nuestros objetos glk
        gg_ventanagrafica = 0;
        return;
    }

    if (fase == 1) {
        switch (tipo) {
	 0: ! Es una ventana
	    switch (rock) {
	     GG_VENTANAGRAFICA_ROCK: gg_ventanagrafica = ref;
	    }
	 1: ! Es un stream
	    ! Pero este juego no ha creado ninguno
	 2: ! Es un fichero
	    ! Pero este juego no ha creado ninguno
        }
        return;
    }
    
    if (fase == 2) {

        ! Ahora que todos los objetos han sido recuperados, y todas
	! las variables globales gg_* inicializadas, podemos pasar a
	! restaurar el estado de los gráficos

	! Aqui habria que llamar a algun punto de entrada
	! proporcionado por el programador, que se ocupe de repintar
	! la ventana gráfica. Pero esto es dependiente del juego, ya
	! que puede que la ventana conste simplemente de un gráfico, o
	! bien de una serie de ellos (fondo, marco, localidad, objetos
	! flotantes sobre la imagen, etc...)
	!
	 RepintarGraficos();
    }
];

! La rutina HandleGlkEvent, si existe, es llamada después de cada
! evento Glk, desde la rutina  KeyboardPrimitive() y
! KeyCharPrimitive(). (el parámetro contexto indica de cuál de las dos
! viene, con el valor 0 o 1, respectivamente).
!
! Se trata de repintar los gráficos si las ventanas han cambiado de
! tamaño o posición.
[ HandleGlkEvent ev contexto;
    contexto = 0; ! No usamos este parámetro
    switch (ev-->0) {
     5: ! evtype_Arrange
	RepintarGraficos();
     6: ! evtype_Redraw
	RepintarGraficos();
    }
];

! Funciones varias que comprueban la disponibilidad de gráficos en el
! intérprete que se esté usando.
! ¿Hay gráficos disponibles?
Global AvisadoNoHayGraficos = false;
[ ComprobarGraficos res;
    res = glk($0004, 6, 0); ! gestalt(gestalt_Graphics)
    if (res == 0) {
        if (~~AvisadoNoHayGraficos) {
            AvisadoNoHayGraficos = true;
    	    print "[Aunque estás jugando una versión gráfica del juego, tu
		intérprete no puede mostrar los gráficos]^";
        }
        rfalse;
    }
    rtrue;
];

! ¿Se pueden pintar gráficos en las ventanas gráficas?
Global AvisadoNoHayGraficosWin = false;
[ ComprobarGraficosWin res;
    if (~~ComprobarGraficos())
        rfalse;
    res = glk($0004, 7, 5); ! gestalt(gestalt_DrawImage, wintype_Graphics)
    if (res == 0) {
        if (~~AvisadoNoHayGraficosWin) {
            AvisadoNoHayGraficosWin = true;
            print "[Tu intérprete no soporta gráficos en ventana 
		gráfica, no podrás ver las imágenes de las 
		localidades. Lo siento.]^^";
        }
        rfalse;
    }
    rtrue;
];

! ¿Podemos pintar imágenes en ventanas de texto?
Global AvisadoNoHayGraficosTexto = false;
[ ComprobarGraficosTexto res;
    if (~~ComprobarGraficos())
        rfalse;
    res = glk($0004, 7, 3); ! gestalt(gestalt_DrawImage, wintype_TextBuffer)
    if (res == 0) {
        if (~~AvisadoNoHayGraficosTexto) {
            AvisadoNoHayGraficosTexto = true;
            print "[Tu intérprete no soporta gráficos mezlcados con 
		el texto, no podrás ver los gráficos de los objetos 
		al examinarlos. Lo siento.]^^";
        }
        rfalse;
    }
    rtrue;
];

[ glk_abrir_graficos altura w;
    if (~~ComprobarGraficosWin()) return 0;
    w=glk($0023, gg_mainwin, $12, altura, 5, GG_VENTANAGRAFICA_ROCK);
    ! $0023 = glk_open_win
    ! $12 = winmethod_above|winmethod_fixed
    ! 5 = winttype_graphics
    if (w==0) 
    {
	print "[Tu intérprete fue incapaz de abrir una ventana
	    gráfica, aunque dijo que podría hacerlo.]^^";
	return 0;
    }
    return w;
];
#endif;

!================================================================
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
! Ahora se implementan las funciones SIX
!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!================================================================

! ================================================================
! Implementación de bajo nivel, específica para la máquina Z
! versión SIX
! ================================================================
#ifdef TARGET_ZCODE;
Array Result --> 0 0 0 0;

[ PonerAltoDeVentanaGrafica h;
    @window_size 2 h 1;
];

[ AnchoDeGrafico pic;
    @picture_data pic result ?Ok;
    return -1;
    .Ok;
    return result-->1;
];

[ AltoDeGrafico pic;
    @picture_data pic result ?Ok;
    return -1;
    .Ok;
    return result-->0;
];

[ CerrarVentanaGrafica;
    @window_size 2 0 0 ;
];

#ifndef EsperarTecla;
[ Volver;
    rtrue;
];

[ EsperarTecla msg delay k;
    if (msg~=0) print (string) msg;
    if (delay==0)
    	@read_char 1 0 0 k;
    else @read_char 1 delay Volver k;
    return k;
];
#endif;

[ AnchoDeVentanaGrafica ancho;
    @get_wind_prop 2 3 -> ancho;
    return ancho;
];

[ AltoDeVentanaGrafica alto;
    @get_wind_prop 2 2 -> alto;
    return alto;
];    

[ PintarGrafico pic x y
    ancho alto;
    @get_wind_prop 2 3 -> ancho;
    @get_wind_prop 2 2 -> alto;
    @picture_data pic result ?Ok;
    print "[Grafico ", pic, " no disponible]^";
    return;
    .Ok;
    if (x==0) x=(ancho-result-->1)/2;
    if (y==0) y=(alto-result-->0)/2;
!    print "[",result-->1, "x", result-->0,"]^";
    @draw_picture pic y x;
];

[ PintarGraficoCentrado pic;
    PintarGrafico(pic);
];

[ PintarGraficoIzquierda pic y alto;
    @get_wind_prop 2 2 -> alto;
    @picture_data pic result ?Ok;
    print "[Grafico ", pic, " no disponible]^";
    return;
    .Ok;
    if (y==0) y=(alto-result-->0)/2;
    @draw_picture pic y 0;
];

[ PintarGraficoDerecha pic y ancho alto x;
    @get_wind_prop 2 3 -> ancho;
    @get_wind_prop 2 2 -> alto;
    @picture_data pic result ?Ok;
    print "[Grafico ", pic, " no disponible]^";
    return;
    .Ok;
    x=ancho-result-->1;
    if (y==0) y=(alto-result-->0)/2;
    @draw_picture pic y x;
];

[ ColorFondoGraficos c;
    @set_colour c 13;
];


[ PatronFondoGraficos pic
    ancho alto x y;

    @get_wind_prop 2 3 -> ancho;
    @get_wind_prop 2 2 -> alto;
    @picture_data pic result ?Ok;
    print "[Fondo ", pic, " no disponible]^";
    return;
    .Ok;
    for (y=0:y<alto:y=y+result-->0)
    	for (x=0:x<ancho:x=x+result-->1)
            @draw_picture pic y x;
];

[ BorrarGraficos ;
    @erase_window 2;
];

[ BorrarPantalla ;
    @erase_window -1;
];

[ ComprobarInterprete;
    if ((0->$1e == 'Z') && (0->$1f == 'N')) rtrue;
    else rfalse;
];

[ PintarGraficoEnLinea pic alineacion;
    if (alineacion==0) alineacion=1;
    @picture_data pic result ?Ok;
    print "[Grafico ", pic, " no disponible]^";
    return;
    .Ok;
    @set_window 3;
    @draw_picture pic alineacion 0;
    @set_window 2;
];
#ifnot;
! ================================================================
! Las mismas funciones anteriores, implementadas ahora para Glulx
! ================================================================
[ PonerAltoDeVentanaGrafica h padre;
    
    if (gg_ventanagrafica==0){ ! Si no existía ventana, se crea
    	gg_ventanagrafica=glk_abrir_graficos(h);
	if (~~gg_ventanagrafica) return;
    }
    else  ! la ventana ya existía, la cambiamos de tamaño
    {
	padre=glk($0029, gg_ventanagrafica); ! $29=glk_window_get_parent
	glk($0026, padre, $12, h, gg_ventanagrafica);
 	! $0026 = glk_window_set_arrangement
	! $12 = winmethod_above|winmethod_fixed
    }
];

[ AnchoDeGrafico pic res;
    res = glk($00E0, pic, gg_arguments, gg_arguments+4); ! image_get_info
    if (~~res)  return -1;
    return gg_arguments-->0;
];

[ AltoDeGrafico pic
    res;
    res = glk($00E0, pic, gg_arguments, gg_arguments+4); ! image_get_info
    if (~~res)  return -1;
    return gg_arguments-->1;
];

[ CerrarVentanaGrafica;
    if (gg_ventanagrafica==0) return; ! Ya estaba cerrada
    glk($0024, gg_ventanagrafica, 0); ! close_window
    gg_ventanagrafica = 0;
];

IFNDEF EsperarTecla;
[ EsperarTecla s delay;
    if (s) print (string) s;
    glk($00D6, delay*100); ! request_timer_events
    glk($00D2, gg_mainwin); ! glk_request_char_event(gg_mainwin);
    while(1) 
    {
	glk($00C0, gg_arguments); ! glk_select(gg_arguments);
	if ((gg_arguments-->0) == 2) break; ! 2=evType_CharInput
	if ((gg_arguments-->0) == 1)
	{
	    glk($00D3, gg_mainwin); ! cancel_char_event
    	    glk($00D6, 0); ! request_timer_events (cancelados)
	    return 0;
	}
    }
    return gg_arguments-->2;
];
ENDIF;


[ AnchoDeVentanaGrafica;
    if (gg_ventanagrafica==0) return -1;
    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
    return gg_arguments-->0;
];

[ AltoDeVentanaGrafica;
    if (gg_ventanagrafica==0) return -1;
    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
    return gg_arguments-->1;
];    

[ PintarGrafico pic x y
    ancho alto res anchoi altoi;
    if (gg_ventanagrafica==0) return;

    ! Averiguar tamaño de la imagen
    res = glk($00E0, pic, gg_arguments, gg_arguments+4); ! image_get_info
    if (~~res) {
	print "[Gráfico ", pic, " no disponible]^";
	return;
    }
    anchoi=gg_arguments-->0;
    altoi=gg_arguments-->1;

    ! Averiguar tamaño de la ventana gráfica
    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
    ancho=gg_arguments-->0;
    alto=gg_arguments-->1;
    if (x==0) x=(ancho-anchoi)/2;
    if (y==0) y=(alto-altoi)/2;
!    print "[ ancho=", ancho, " alto=", alto, " anchoi=", anchoi, " altoi=", altoi, "]^";
    glk($00E1, gg_ventanagrafica, pic, x, y); ! image_draw
];

[ PintarGraficoCentrado pic;
    PintarGrafico(pic);
];

[ PintarGraficoIzquierda pic y
    alto altoi;
    alto=AltoDeVentanaGrafica();
    if (alto==-1) return;
    altoi=AltoDeGrafico(pic);
    if (altoi==-1)
    {
    	print "[Grafico ", pic, " no disponible]^";
    	return;
    }
    if (y==0) y=(alto-altoi)/2;
    glk($00E1, gg_ventanagrafica, pic, 0, y); ! image_draw
];

[ PintarGraficoDerecha pic y
    ancho alto x anchoi altoi res;
    if (gg_ventanagrafica==0) return;
    
    ! Averiguar tamaño de la ventana gráfica
    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
    ancho=gg_arguments-->0;
    alto=gg_arguments-->1;

    ! Averiguar tamaño de la imagen
    res = glk($00E0, pic, gg_arguments, gg_arguments+4); ! image_get_info
    if (~~res) {
	print "[Gráfico ", pic, " no disponible]^";
	return;
    }
    anchoi=gg_arguments-->0;
    altoi=gg_arguments-->1;
    x=ancho-anchoi;
    if (y==0) y=(alto-altoi)/2;
    glk($00E1, gg_ventanagrafica, pic, x, y); ! image_draw
];

[ ColorFondoGraficos c
    color;
    if (gg_ventanagrafica==0) return;
    ! Averiguar tamaño de la ventana gráfica
!    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
!    ancho=gg_arguments-->0;
!    alto=gg_arguments-->1;
    color=DesempaquetarColorSIX(c);
!    glk($00EA, gg_ventanagrafica, color, 0, 0, ancho, alto); ! window_fill_rect
    glk($00EB, gg_ventanagrafica, color); ! glk_window_set_background_color
];

[ ColorFondoGraficosRGB r g b
    ancho alto;
    if (gg_ventanagrafica==0) return;
    ! Averiguar tamaño de la ventana gráfica
    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
    ancho=gg_arguments-->0;
    alto=gg_arguments-->1;
    glk($00EA, gg_ventanagrafica, r*65536+g*256+b, 0, 0, ancho, alto); ! window_fill_rect
];


[ PatronFondoGraficos pic
    ancho alto anchoi altoi x y res;

    if (gg_ventanagrafica==0) return;

    ! Averiguar tamaño de la imagen
    res = glk($00E0, pic, gg_arguments, gg_arguments+4); ! image_get_info
    if (~~res) {
	print "[Fondo gráfico ", pic, " no disponible]^";
	return;
    }
    anchoi=gg_arguments-->0;
    altoi=gg_arguments-->1;

    ! Averiguar tamaño de la ventana gráfica
    glk($0025, gg_ventanagrafica, gg_arguments, gg_arguments+4); ! window_get_size
    ancho=gg_arguments-->0;
    alto=gg_arguments-->1;
    
    for (y=0:y<alto:y=y+altoi)
    	for (x=0:x<ancho:x=x+anchoi)
    	    glk($00E1, gg_ventanagrafica, pic, x, y); ! image_draw
];

[ BorrarGraficos ;
    if (gg_ventanagrafica==0) return;
    glk($002A, gg_ventanagrafica); ! window_clear
];

[ BorrarPantalla w;
    if (w==0) w=gg_mainwin;
    if (gg_quotewin) ! Cerrar la ventana de boxes
    {
    	glk($0024, gg_quotewin, 0); ! close_window
    	gg_quotewin = 0;
    }
    glk($002A, w);  ! window_clear
];

[ ComprobarInterprete;
    ComprobarGraficos();
    rtrue;
    ! Glulxe siempre admite Glk, aunque no pueda
    ! mostrar gráficos. El juego siempre podrá ser ejecutado.
];

[ PintarGraficoEnLinea pic alineacion
    res;
    if (alineacion==0) alineacion=1;
    if (~~ComprobarGraficosTexto()) return;
    res = glk($00E0, pic, 0, 0); ! image_get_info
    if (~~res) {
    	print "[Grafico en-línea ", pic, " no disponible]^";
    	return;
    }
    glk($00E1, gg_mainwin, pic, alineacion, 0); ! image_draw
];


[ DesempaquetarColorSIX c
    r g b;
    ! La inversa del anterior. Recibe un número que representa un
    ! color codificado en 16 bits por el método 5-6-5 y devuelve un
    ! entero de 32 bits que representa el color en 8-8-8-8 (los 8
    ! primeros bits a cero, los 24 siguientes, RGB)

    r=(c/2048) * 8;
    g=((c%2048)/32) * 4;
    b=(c%32) * 8;
    return r*256*256+g*256+b;
];

#Stub RepintarGraficos 0;
#endif;

!================================================================
! Finalmente, rutinas de alto nivel que no dependen de la
! implementación
!================================================================

[ RGBcolor r g b;

    ! Recibe tres componentes r, g, b (de 8 bits cada una) y retorna
    ! un color codificado en 16 bits, por el metodo 5-6-5

    r=r/8;
    g=g/4;
    b=b/8;
    return r*2048+g*32+b;
];


[ GraficoPausa pic color pausa
    alto;

    #ifndef TARGET_ZCODE;
    if (~~ComprobarGraficos()) 
    {
    	EsperarTecla("^^Pulsa una tecla para seguir...sin gráficos...",pausa);
	return;
    }
    #endif;
    alto=AltoDeGrafico(pic);
    if (alto==-1)
        "[No se encuentra el dibujo numero ", pic, "]";
    CerrarVentanaGrafica();
    PonerAltoDeVentanaGrafica(alto+20);
    if (color)
    {
	ColorFondoGraficos(color);
    	BorrarGraficos();    ! Hasta que no se borra no se
	                     ! actualiza el color de fondo
    }
    PintarGrafico(pic);
    EsperarTecla("Pulsa una tecla para seguir...",pausa);
    CerrarVentanaGrafica();
];
