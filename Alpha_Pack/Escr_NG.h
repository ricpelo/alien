! Escr_NG.h
! Presenta un vector de cadenas en pantalla.
! Hace una pausa tras cada cadena.
! Visualiza cada cadena caracter a caracter.

System_file;

#ifndef  ESCR_LIB;
Constant ESCR_LIB;

Message "Compilando librería de escritura letra a letra. Baltasar, el arquero.";

Constant MAX_TAM_BUFFER = 310;
Array escr_buffer_lib --> MAX_TAM_BUFFER;

#ifdef TARGET_GLULX;
Constant ESCR_PRIMERA_LETRA 4;
#endif;
#ifdef TARGET_ZCODE;
Constant ESCR_PRIMERA_LETRA 2;
#endif;

! Tipos de mensaje:

Constant POR_LETRA = 0;
Constant POR_MENSAJE = 1;

! Tipos de pausa:

Constant SIN_PAUSA = -1;
Constant PAUSA_NORMAL = 0;
Constant ESPERAR_TECLA = 1;
Constant PAUSA_DOBLE = 2;
Constant PAUSA_TRIPLE = 3;

! Tipos de letra:

Constant LETRA_NORMAL  = $$00001;
Constant LETRA_NEGRITA = $$00010;
Constant LETRA_CURSIVA = $$00100;
Constant LETRA_FIJA    = $$01000;
Constant LETRA_INVERSA = $$10000;

! Hace lo mismo que EsperarTimer pero no guarda ni restaura
! el timer anterior:
[ EsperarTimerSimple espera;
  glk($00D6, espera * 5);            ! request_timer_events
  while (1) {
    glk($00C0, gg_arguments);        ! glk_select(gg_arguments);
    if ((gg_arguments-->0) == 1) {
      glk($00D6, 0);                 ! request_timer_events
      break;
    }
  }
];


class Escritura
  class Vector
  private
    sonido 0,
    volumen 0,
  with
    hazPausaLetra [;
      if ( self.pausaLetra > -1 ) {
        EsperarTimerSimple(self.pausaLetra);
      }
    ],
    hazPausaMensaje [ multi;
      if ( self.pausaMensaje > -1 ) {
        EsperarTecla(0, self.pausaMensaje * multi);
      }
    ],
    pausaLetra 1,
    pausaMensaje 150,
    visualiza [ n p lon tipo_mensaje tipo_letra tipo_pausa timer;
      escr_buffer_lib-->0 = MAX_TAM_BUFFER - ESCR_PRIMERA_LETRA;

      ! Para cada cadena a visualizar
      for (n = 0 : n < self.longitud() : n++) {
        ! Para cada una de las cadenas
        ! Convertirlas a vector
        lon = PrintAnyToArray(escr_buffer_lib + WORDSIZE, MAX_TAM_BUFFER, (self.elemento(n)));
!        lon = (self.elemento(n)).print_to_array(escr_buffer_lib);

        tipo_mensaje = self.elemento(n + 1);
        tipo_letra = self.elemento(n + 2);
        tipo_pausa = self.elemento(n + 3);
        
        if (tipo_letra & LETRA_NORMAL)  style roman;
        if (tipo_letra & LETRA_NEGRITA) style bold;    
        if (tipo_letra & LETRA_CURSIVA) style underline;
        if (tipo_letra & LETRA_FIJA)    glk_set_style(style_Preformatted);
        if (tipo_letra & LETRA_INVERSA) style reverse;

        if (tipo_mensaje == POR_MENSAJE) {
          print (string) self.elemento(n);          
        } else {
          timer = control_timer.timer_actual; 
          ! Visualizar las letras una a una
          for (p = ESCR_PRIMERA_LETRA : p < (lon + ESCR_PRIMERA_LETRA) : p++) {
            print (char) escr_buffer_lib->p;
                
            #ifdef TARGET_GLULX;
              ! Tocar un sonido, esperar a pulsar una tecla o que pase un tiempo
              if ( self.sonido ~= 0 ) {
                Damusix.Tocar(Teletipo_ogg);
              }
              self.hazPausaLetra();
            #endif;
            #ifdef TARGET_ZCODE;
              self.hazPausaLetra();
            #endif;
          }
          if (timer ~= 0) {
            control_timer.desactivar();
            ActivarTimer();
          }
        }          
        switch (tipo_pausa) {
          SIN_PAUSA:     break;
          ESPERAR_TECLA: EsperarTecla();
          PAUSA_NORMAL:  self.hazPausaMensaje(1);
          PAUSA_DOBLE:   self.hazPausaMensaje(2);
          PAUSA_TRIPLE:  self.hazPausaMensaje(3);
          default:       self.hazPausaMensaje(tipo_pausa);
        }
        style roman;
        n = n + 3;
      }
    ];
#endif;
