! BajoNivel.h
! ----------------------------------------
! Modificado: baltasarq. 27/08/2006
! Ahora se puede poner también estilo de letra proporcional en Glulxe y en Z
!
! Modificado: baltasarq. 22/04/2002
! Ahora se puede poner estilo negrita, cursiva y normal en Glulxe y en Z
!
! (c) 2000 Zak McKracken (17/Octubre/2000)
!
! Las funciones definidas en este módulo vienen también en la librería
! SIX v2, por lo que si usas SIX no necesitas incluir este módulo (no
! podrás, de hecho).
!
! Este módulo implementa las funciones BorrarPantalla
! y EsperarTecla. Estas funciones solían escribirse en ensamblador de
! la máquina Z a base de @read y @erase_window. Pero este método
! complica la adaptación del juego para su compilación bajo Glulx.
!
! Incluyendo este módulo, el programador puede poner simplemente
! BorrarPantalla(); en lugar de @erase_window -1. Cuando compile para
! la máquina Z, el efecto será el mismo, pero cuando compile para
! Glulx, se convertirá en llamadas a Glk para borrar la pantalla.
!
! De forma análoga EsperarTecla(); espera a que se pulse una tecla
! antes de continuar. Pueden pasársele dos parámetros, opcionales. El
! primero sería un texto a mostrar antes de esperar, y el segundo el
! tiempo máximo a esperar en décimas de segundo. Por ejemplo:
!
! EsperarTecla("[Pulsa una tecla]", 100);
!
! esperaría un máximo de 10 segundos, tras lo cual retornaría como si
! el jugador hubiera pulsado una tecla. Si se pulsa una tecla, se
! retorna el código de la misma, si no se pulsa y el tiempo se agota,
! se retorna cero.
!
! Si se omite el segundo parámetro, la espera será infinita. Si se
! omiten ambos parámetros, no se muestra texto y la espera es
! infinita. Para omitir el primer parámetro pero no el segundo la
! llamada ha de ser algo como:
!
! EsperarTecla(0, 100);
!
! En cuyo caso no se escribiría nada y se esperarían 10 segundos.
! [NOTA: La espera temporizada puede no estar disponible en algunos
! intérpretes, que harán pausa infinita siempre]
!
System_file;

#ifndef WORDSIZE;
Constant WORDSIZE = 2;
Constant TARGET_ZCODE;
#endif;

#ifdef TARGET_ZCODE;
[ BorrarPantalla ;
  @erase_window -1;
];

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

[ Negrita;
      style bold;
];

[ Italica;
      style underline;
];

[ Normal;
      font on;
      style roman;
];

[ Proporcional;
      font off;
];
#endif;

#ifdef TARGET_GLULX;
[ BorrarPantalla w;
    if (w==0) w=gg_mainwin;
    if (gg_quotewin) ! Cerrar la ventana de boxes
    {
        glk($0024, gg_quotewin, 0); ! close_window
        gg_quotewin = 0;
    }
    glk($002A, w);  ! window_clear
];

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

Constant GLK_ESTILO_NORMAL 0;
Constant GLK_ESTILO_ENFASIS 1;
Constant GLK_ESTILO_ALERTA 5;
Constant GLK_ESTILO_PREFORMATEADO 2;
Constant GLK_ESTILO_NOTA 6;
Constant GLK_ESTILO_CITA 7;

[ Normal;
      glk($0086, GLK_ESTILO_NORMAL); 
];

[ Negrita;
      glk($0086, GLK_ESTILO_ALERTA);
];

[ Italica;
      glk($0086, GLK_ESTILO_NOTA);
];

[ Proporcional;
     glk($0086, GLK_ESTILO_PREFORMATEADO);
];
#endif;
