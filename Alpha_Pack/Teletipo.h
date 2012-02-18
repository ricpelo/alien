!
! Teletipo.h
!
! Presenta un vector de cadenas en pantalla.
! Hace una pausa tras cada cadena.
! Visualiza cada cadena caracter a caracter.
! Prácticamente copiado literalmente de Escr, de Baltasarq,
! pero con muchas mejoras.
!

System_file;

Constant TAM_BUFFER_TELETIPO = 310;
Array buffer_teletipo --> TAM_BUFFER_TELETIPO;

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

#ifndef WaitDelay;
[ WaitDelay delay;
  return ControlTimer.CT_WaitDelay(delay);
];
#endif;

Class Teletipo
  with
    elementos 0,
    gancho_antes 0,
    gancho_despues 0, 
    hazPausaLetra [;
      if (self.pausaLetra > -1) {
        WaitDelay(self.pausaLetra);
      }
    ],
    hazPausaMensaje [ multi;
      if (self.pausaMensaje > -1) {
        KeyDelay(self.pausaMensaje * multi);
      }
    ],
    pausaLetra 1,
    pausaMensaje 150,
    visualiza [ str n p lon tipo_mensaje tipo_letra tipo_pausa;
      if (str ~= 0) self.&elementos-->0 = str;
      buffer_teletipo-->0 = TAM_BUFFER_TELETIPO - WORDSIZE;

      ! Para cada cadena a visualizar
      for (n = 0: n < self.#elementos / WORDSIZE: n++) {
        ! Para cada una de las cadenas
        ! Convertirlas a vector
        lon = PrintAnyToArray(buffer_teletipo + WORDSIZE, TAM_BUFFER_TELETIPO, self.&elementos-->n);

        tipo_mensaje = self.&elementos-->(n + 1);
        tipo_letra = self.&elementos-->(n + 2);
        tipo_pausa = self.&elementos-->(n + 3);
        
        if (tipo_letra & LETRA_NORMAL)  style roman;
        if (tipo_letra & LETRA_NEGRITA) glk_set_style(style_User1);
        if (tipo_letra & LETRA_CURSIVA) style underline;
        if (tipo_letra & LETRA_FIJA)    glk_set_style(style_Preformatted);
        if (tipo_letra & LETRA_INVERSA) style reverse;

        if (tipo_mensaje == POR_MENSAJE ||
           (tipo_mensaje == POR_LETRA && ~~hayTeletipo)) {
          print (string) self.&elementos-->n;
        } else {
          if (self.gancho_antes ~= 0) {
            self.gancho_antes();
          }
          ! Visualizar las letras una a una
          for (p = WORDSIZE : p < (lon + WORDSIZE) : p++) {
            print (char) buffer_teletipo->p;
            self.hazPausaLetra();
          }
          if (self.gancho_despues ~= 0) {
            self.gancho_despues();
          }
        }          
        switch (tipo_pausa) {
          SIN_PAUSA:     break;
          ESPERAR_TECLA: KeyDelay();
          PAUSA_NORMAL:  self.hazPausaMensaje(1);
          PAUSA_DOBLE:   self.hazPausaMensaje(2);
          PAUSA_TRIPLE:  self.hazPausaMensaje(3);
          default:       self.hazPausaMensaje(tipo_pausa);
        }
        style roman;
        n = n + 3;
      }
    ];

