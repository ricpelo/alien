! Módulo barra.h 1.0 para InformatE 6/7E o 6/10E
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

message "Modulo de barra de estado (barra.h) 1.0 del Presi";

system_file;

#ifndef WORDSIZE;
constant WORDSIZE=2;
constant TARGET_ZCODE;
#endif;


constant BE_SIMPLE=1;      ! constantes de modo
constant BE_COMPUESTO=0;

constant BE_INV_TOTAL=1;       ! constantes de linea
constant BE_INV_PARCIAL=2;     ! invertido en modo simple
constant BE_INV_NO=0;

constant BE_IZQUIERDA=0;   ! constantes de alineacion
constant BE_DERECHA=1;     ! para modo simple
constant BE_CENTRO=2;

constant BE_TEXTO=1;       ! constantes de tipo de item
constant BE_LOCALIDAD=2;   ! en modo compuesto
constant BE_AVENTURA=3;
constant BE_HORA_24=4;
constant BE_SOLO_HORA_24=5;
constant BE_HORA_AMPM=6;
constant BE_SOLO_HORA_AMPM=7;
constant BE_TURNOS=8;
constant BE_SOLO_TURNOS=9;
constant BE_PUNTUACION=10;
constant BE_SOLO_PUNTUACION=11;

constant BE_NO_CAMBIAR=-1;
constant BE_JUNTO=-1;


class objeto_barra_estado         ! declaracion de clase
  with                            ! y parametros por defecto
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
    dibujar                              ! rutina dibujar, debe ser llamada
     [ ancho lin pos aux i n x y ctex;   ! desde la funcion DibujarLineaEstado
       aux = aux;
       if (self.numero_lineas) lin=self.numero_lineas;
                          else lin=(self.#lineas_inv)/WORDSIZE;
       ctex=0;
       if (self.numero_items) n=self.numero_items*4;
                         else n=(self.#disposicion)/WORDSIZE;
    #ifdef TARGET_ZCODE;
       @split_window lin;
       @set_window 1;
       ancho=0->33;
       if (~~ancho) ancho=80;
       style roman;
       if (self.modo)   ! modo simple
         {
           pos=self.posicion;
           for (i=1: i<=lin: i++)
             {
               @set_cursor i 1;
               self.limpiar_linea(i,ancho);
               if (i==pos)
                 {
                   if (self.&lineas_inv-->(i-1)) style reverse;
                   switch (self.alineacion)
                    {
                      BE_IZQUIERDA:
                        @set_cursor pos 1;
                      BE_DERECHA:
                        aux=ancho-self.longitud;
                        @set_cursor pos aux;
                      BE_CENTRO:
                        aux=(ancho-self.longitud)/2;
                        @set_cursor pos aux;
                    }                 
                   self.imprimir_item(self.item);
                   style roman;
                 }
             }
         }
       else      ! modo compuesto
         {
           for (i=1: i<=lin: i++)
             {
               @set_cursor i 1;
               self.limpiar_linea(i,ancho);
             }
           for (i=0: i<n: i=i+4)
             {                           ! recorre la propiedad disposicion
               x=self.&disposicion-->i;
               if (x~=BE_JUNTO)
                 {
                   x=(x*ancho)/80;   ! calcula el proporcinal de tanto por 80
                   y=self.&disposicion-->(i+1);
                   @set_cursor y x;
                 }
               if (self.&disposicion-->(i+2)) style reverse;
               ctex=self.imprimir_item(self.&disposicion-->(i+3),ctex);
               style roman;
             }
         }
       @set_window 0;
  #endif;
  #ifdef TARGET_GLULX;
       pos=self.posicion-1;
       if (gg_statuswin == 0) return;
       glk($002F, gg_statuswin); ! set_window
       StatusLineHeight(lin);
       glk($0025, gg_statuswin, gg_arguments, gg_arguments+4); ! window_get_size
       ancho = gg_arguments-->0;
       glk($002A, gg_statuswin); ! window_clear
       if (self.modo)         ! modo simple
         {
           switch (self.alineacion)
            {
              BE_IZQUIERDA:
                glk($002B, gg_statuswin, 1, pos); ! window_move_cursor
              BE_DERECHA:
                glk($002B, gg_statuswin, ancho-self.longitud, pos); ! window_move_cursor
              BE_CENTRO:
                glk($002B, gg_statuswin, (ancho-self.longitud)/2, pos); ! window_move_cursor
            }
           self.imprimir_item(self.item);
         }
       else         ! modo compuesto
         {
           for (i=0: i<n: i=i+4)
             {                          ! recorre la propiedad disposicion
               x=self.&disposicion-->i;
               if (x~=BE_JUNTO)
                 {
                   x=(x*ancho)/80;   ! calcula el proporcinal de tanto por 80
                   y=(self.&disposicion-->(i+1))-1;
                   glk($002B, gg_statuswin, x, y);
                 }
               ctex=self.imprimir_item(self.&disposicion-->(i+3),ctex);
             }
         }
       glk($002F, gg_mainwin); ! set_window
  #endif;
     ],
    cambiar_lineas_inv              ! funcion de usuario para modificar
     [ n v;                         ! en tiempo de ejecucion
                                    ! la propiedad lineas_inv
       self.&lineas_inv-->(n-1)=v;
     ],
    cambiar_disposicion             ! funcion de usuario para modificar
     [ n x y inv item;              ! en tiempo de ejecucion
                                    ! la propiedad disposicion
       n = --n*4;
       if (x~=BE_NO_CAMBIAR) self.&disposicion-->n=x;
       if (y~=BE_NO_CAMBIAR) self.&disposicion-->(n+1)=y;
       if (inv~=BE_NO_CAMBIAR) self.&disposicion-->(n+2)=inv;
       if (item~=BE_NO_CAMBIAR) self.&disposicion-->(n+3)=item;
     ],
  private
    limpiar_linea           ! limpia una linea en roman o en reverso
     [i ancho;
       i = i; ancho = ancho;
  #ifdef TARGET_ZCODE; 
       if ((self.&lineas_inv-->(i-1))==BE_INV_TOTAL) style reverse;
       spaces(ancho);
       style roman;
  #endif;
     ],
    imprimir_item           ! imprime un item de disposicion
     [ it ctex;
       !style bold;
       glk($0086, style_SubHeader);
                            ! para llamar a su rutina correspondiente
       switch (it)
        {
          BE_TEXTO:             ! ctex es el contador de items de texto
            self.texto(++ctex); ! para llamar a su rutina correspondiente
          BE_LOCALIDAD:
            print (name) localizacion;
          BE_AVENTURA:
            print (string) historia;
  #ifdef HORA24_PRESENTE;                ! si hora24.h no ha sido incluido
          BE_HORA_24:                    ! las horas se desactivan
            print "Hora: ",(hora24) la_hora;
          BE_SOLO_HORA_24:
            print (hora24) la_hora;
          BE_HORA_AMPM:
            print "Hora: ";
            IdiomaHoraDelDia(objeto_hora24.horas(la_hora),objeto_hora24.minutos(la_hora));
          BE_SOLO_HORA_AMPM:
            IdiomaHoraDelDia(objeto_hora24.horas(la_hora),objeto_hora24.minutos(la_hora));
  #endif;
          BE_TURNOS:
            print "Turnos: ",turnos;
          BE_SOLO_TURNOS:
            print turnos;
          BE_PUNTUACION:
            print "Punt.: ",puntuacion;
          BE_SOLO_PUNTUACION:
            print puntuacion;
        }
       style roman;
       return ctex;
     ];
