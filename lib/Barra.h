! INFSP VERSION (inform 6/11)

! Módulo barra.h 2.0 para INFSP
! (C) 2001 Presi (Enrique D. Bosch) [kifcu@confluencia.net]
! Puede distribuirse libremente bajo licencia GNU LGPL
!
! es biplataforma Z/Glulx
!
! Implementa lo necesario para crear barras de estado (lineas de estado
! en argot Informate) potentes de manera sencilla
!
! Para informacion sobre su uso ver documentacion adjunta
!
! Pasada a InformATE y modificada (un poco) por Sothoth
! (c) Alpha Aventuras
!

Message "Modulo de barra de estado (barra.h) 2.0 del Presi";

System_file;

#ifndef WORDSIZE;
Constant WORDSIZE = 2;
Constant TARGET_ZCODE;
#endif;

! Constantes de modo:
Constant BE_SIMPLE    = 1;
Constant BE_COMPUESTO = 0;

! Constantes de línea invertida:
Constant BE_INV_TOTAL   = 1;
Constant BE_INV_PARCIAL = 2;
Constant BE_INV_NO      = 0;

! Constantes de alineación para modo simple:
Constant BE_IZQUIERDA = 0;
Constant BE_DERECHA   = 1;
Constant BE_CENTRO    = 2;

! Constantes de tipo de ítem:
Constant BE_TEXTO           = 1;
Constant BE_LOCALIDAD       = 2;
Constant BE_AVENTURA        = 3;
Constant BE_HORA_24         = 4;
Constant BE_SOLO_HORA_24    = 5;
Constant BE_HORA_AMPM       = 6;
Constant BE_SOLO_HORA_AMPM  = 7;
Constant BE_TURNOS          = 8;
Constant BE_SOLO_TURNOS     = 9;
Constant BE_PUNTUACION      = 10;
Constant BE_SOLO_PUNTUACION = 11;
Constant BE_SALIDAS         = 12;
Constant BE_SOLO_SALIDAS    = 13;
Constant BE_BRUJULA         = 14;
Constant BE_BRUJULA_BONITA  = 15;

Constant BE_NO_CAMBIAR = -1;
Constant BE_JUNTO      = -1;


! Declaración de clase y parámetros por defecto:
Class objeto_barra_estado
  with
    modo BE_SIMPLE,
    item BE_TEXTO,
    alineacion BE_IZQUIERDA,
    posicion 1,
    longitud 0,
    lineas_inv BE_INV_TOTAL,
    numero_lineas 0,
    numero_items 0,
    disposicion,
    texto,
    anchura 0,
    proporcional true,
    ! Rutina dibujar. Debe ser llamada desde la función DibujarLineaEstado
    dibujar [ ancho lin pos aux i n x y ctex;
      if (self.numero_lineas) lin = self.numero_lineas;
      else                    lin = (self.#lineas_inv)/WORDSIZE;
      ctex = 0;
      if (self.numero_items) n = self.numero_items * 4;
      else                   n = (self.#disposicion) / WORDSIZE;
      #ifdef TARGET_ZCODE;
        @split_window lin;
        @set_window 1;
        if (self.anchura) ancho = self.anchura;
        else              ancho = 0->33;
        if (~~ancho) ancho = 80;
        style roman;
        if (self.modo) {  ! modo simple
          pos = self.posicion;
          for (i = 1: i <= lin: i++) {
            self.locate(i, 1, 1);
            self.limpiar_linea(i, ancho);
            if (i == pos) {
              if (self.&lineas_inv-->(i - 1)) style reverse;
              switch (self.alineacion) {
                BE_IZQUIERDA: self.locate(pos, 1, 1);
                BE_DERECHA:   aux = ancho - self.longitud;
                              self.locate(pos, aux, 1);
                BE_CENTRO:    aux = (ancho - self.longitud) / 2;
                              self.locate(pos, aux, 1);
              }
              self.imprimir_item(self.item);
              style roman;
            }
          }
        } else {     ! Modo compuesto
          for (i = 1: i <= lin: i++) {
            self.locate(i, 1, 1);
            self.limpiar_linea(i, ancho);
          }
          for (i = 0: i < n: i = i + 4) { ! Recorre la propiedad disposicion
            x = self.&disposicion-->i;
            if (x ~= BE_JUNTO) {          ! Calcula el proporcional de tanto por 80
              if (self.proporcional) x = (x * ancho) / 80;
              y = self.&disposicion-->(i + 1);
              self.locate(y, x, 1);
            }
            if (self.&disposicion-->(i + 2)) style reverse;
            ctex = self.imprimir_item(self.&disposicion-->(i + 3), ctex);
            style roman;
          }
        }
        @set_window 0;
      #endif;
      #ifdef TARGET_GLULX;
        aux = aux;
        pos = self.posicion;
        if (gg_statuswin == 0) return;
        glk($002F, gg_statuswin); ! set_window
        StatusLineHeight(lin);
        glk($0025, gg_statuswin, gg_arguments, gg_arguments + 4); ! window_get_size
        if (self.anchura) ancho = self.anchura;
        else              ancho = gg_arguments-->0;
        glk($002A, gg_statuswin); ! window_clear
        if (self.modo) {          ! modo simple
          switch (self.alineacion) {
            BE_IZQUIERDA: self.locate(pos,1,1);
            BE_DERECHA:   self.locate(pos,ancho-self.longitud,1);
            BE_CENTRO:    self.locate(pos,(ancho-self.longitud)/2,1);
          }
          self.imprimir_item(self.item);
        } else {                  ! modo compuesto
          for (i = 0: i < n: i = i + 4) {     ! recorre la propiedad disposicion
            x = self.&disposicion-->i;
            if (x ~= BE_JUNTO) {              ! calcula el proporcional de tanto por 80
              if (self.proporcional) x = (x * ancho) / 80;
              y = (self.&disposicion-->(i + 1));
              self.locate(y, x, 1);
            }
            ctex = self.imprimir_item(self.&disposicion-->(i + 3), ctex);
          }
        }
        glk($002F, gg_mainwin); ! set_window
      #endif;
    ],
    ! Función de usuario para modificar en tiempo de ejecución
    ! la propiedad lineas_inv
    cambiar_lineas_inv [ n v;
      self.&lineas_inv-->(n - 1) = v;
    ],
    ! Función de usuario para modificar en tiempo de ejecución
    ! la propiedad disposición
    cambiar_disposicion [ n x y Inv item;
      n = --n * 4;
      if (x    ~= BE_NO_CAMBIAR) self.&disposicion-->n = x;
      if (y    ~= BE_NO_CAMBIAR) self.&disposicion-->(n + 1) = y;
      if (Inv  ~= BE_NO_CAMBIAR) self.&disposicion-->(n + 2) = Inv;
      if (item ~= BE_NO_CAMBIAR) self.&disposicion-->(n + 3) = item;
    ],
  private
    fila,
    columna,
    columnaab,
    columnadf,
    locate [ fi co alm;
      if (alm) {
        self.fila = fi;
        self.columna = co;
      }
      #ifdef TARGET_ZCODE;
        @set_cursor fi co;
      #ifnot; ! GLULX
        glk($002B, gg_statuswin, co, fi - 1);
      #endif;
    ],
    ! Limpia una línea en roman o en reverso
    limpiar_linea [i ancho;
      i = i; ancho = ancho;
      #ifdef TARGET_ZCODE; 
        if ((self.&lineas_inv-->(i - 1)) == BE_INV_TOTAL) style reverse;
        spaces(ancho);
        style roman;
      #endif;
    ],
    ! Imprime un ítem de disposición
    imprimir_item [ it ctex;
      glk($0086, style_SubHeader);
      ! Para llamar a su rutina correspondiente
      switch (it) {
        BE_TEXTO:             ! ctex es el contador de items de texto
          self.texto(++ctex);
        BE_LOCALIDAD:
          print (_nombre_) localizacion;
        BE_AVENTURA:
          print (string) Historia;
        ! Si Hora24.h no ha sido incluido, las horas se desactivan
        #ifdef HORA24_PRESENTE;
          BE_HORA_24:
            print "Hora: ",(hora24) la_hora;
          BE_SOLO_HORA_24:
            print (hora24) la_hora;
          BE_HORA_AMPM:
            print "Hora: ";
            IdiomaHoraDelDia(objeto_hora24.horas(la_hora), objeto_hora24.minutos(la_hora));
          BE_SOLO_HORA_AMPM:
            IdiomaHoraDelDia(objeto_hora24.horas(la_hora), objeto_hora24.minutos(la_hora));
        #endif;
        BE_TURNOS:
          print "Turnos: ", turnos;
        BE_SOLO_TURNOS:
          print turnos;
        BE_PUNTUACION:
          print "Punt.: ", puntuacion;
        BE_SOLO_PUNTUACION:
          print puntuacion;
        #ifdef ADMITIR_COMANDO_SALIDAS;
          BE_SALIDAS:
            print "Salidas:";
            self.imprimir_brsa(BE_SALIDAS);
          BE_SOLO_SALIDAS:
            self.imprimir_brsa(BE_SALIDAS);
          BE_BRUJULA:
            self.columnaab = self.columna;
            self.columnadf = self.columna + 6;
            self.imprimir_brsa(0);
          BE_BRUJULA_BONITA:
            self.imprimir_mabr();
            self.imprimir_brsa(0);
        #endif;
      }
      return ctex;
    ],
    ! Imprime marco para la brújula bonita
    imprimir_mabr [;
      #ifdef ADMITIR_COMANDO_SALIDAS;
        self.locate(self.fila, self.columna, 0);
        print "   __N__";
        self.locate(self.fila + 1, self.columna, 0);
        print "  /     @@92";
        self.locate(self.fila + 2, self.columna, 0);
        print "O|   +   |E";
        self.locate(self.fila + 3, self.columna, 0);
        print "  @@92_____/";
        self.locate(self.fila + 4, self.columna, 0);
        print "     S";
        self.fila++;
        self.columnaab = self.columna;
        self.columnadf = self.columna + 10;
        self.columna = self.columna + 2;
      #endif;
    ],
    ! Recorre salidas e imprime 
    imprimir_brsa [ x i j siempre nunca;
      #ifdef ADMITIR_COMANDO_SALIDAS;
        if (localizacion == laoscuridad) j = localizacion_real;
        else                             j = localizacion;
        objectloop (i in brujula) {
          if (j provides Salidas)
            switch (j.Salidas(i)) {
              false:   siempre = false;   ! Mostrarla si existe la
                       nunca   = false;   ! propiedad al_* y no es un string
              2, true: nunca   = true;    ! No imprimir esta
              default: siempre = true;    ! Imprimirla siempre
            };
            if (j provides (i.direcc_puerta) &&
                metaclass(j.(i.direcc_puerta)) ~= nothing or string ||
                siempre && ~~nunca)
              if (x == BE_SALIDAS) self.imprimir_cardinal(i.direcc_puerta);
              else                 self.imprimir_brujula(i.direcc_puerta);
        }
      #endif;
    ],
    imprimir_cardinal [ direcc;
      #ifdef ADMITIR_COMANDO_SALIDAS;
        print " ";
        switch (direcc) {
          arriba:  print "AR";
          al_no:   print "NO";
          al_n:    print "N";
          al_ne:   print "NE";
          adentro: print "AD";
          al_o:    print "O";
          al_e:    print "E";
          abajo:   print "AB";
          al_so:   print "SO";
          al_s:    print "S";
          al_se:   print "SE";
          afuera:  print "AF";
        }
      #endif;
    ],
    imprimir_brujula [ direcc;
      #ifdef ADMITIR_COMANDO_SALIDAS;
        switch (direcc) {
          arriba:  self.locate(self.fila,     self.columnaab,   0); print "@@94";
          al_no:   self.locate(self.fila,     self.columna + 2, 0); print "@@92";
          al_n:    self.locate(self.fila,     self.columna + 3, 0); print "|";
          al_ne:   self.locate(self.fila,     self.columna + 4, 0); print "/";
          adentro: self.locate(self.fila,     self.columnadf,   0); print "D";
          al_o:    self.locate(self.fila + 1, self.columna + 1, 0); print "--";
          al_e:    self.locate(self.fila + 1, self.columna + 4, 0); print "--";
          abajo:   self.locate(self.fila + 2, self.columnaab,   0); print "v";
          al_so:   self.locate(self.fila + 2, self.columna + 2, 0); print "/";
          al_s:    self.locate(self.fila + 2, self.columna + 3, 0); print "|";
          al_se:   self.locate(self.fila + 2, self.columna + 4, 0); print "@@92";
          afuera:  self.locate(self.fila + 2, self.columnadf,   0); print "F";
        }
      #endif;
    ];

