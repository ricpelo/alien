!
! Mapeador.h - Una librería para generar el mapa de la aventura automáticamente
!
! Copyright (c) 2012 Ricardo Pérez López (Alpha Aventuras)
!

! This program is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation, either version 3 of the License, or
! (at your option) any later version.
!
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
!
! You should have received a copy of the GNU General Public License
! along with this program.  If not, see <http://www.gnu.org/licenses/>.


System_file;

Include "infglk";

Message " __________________________________________________________________";
Message "|                                                                  |";
Message "|                 * MAPEADOR:  I M P O R T A N T E *               |";
Message "|                 ==================================               |";
Message "| 1. Pon 'Include ~Mapeador.h~;' despues de 'Include ~SGW+DMX.h~;' |";
Message "| 2. Define la rutina EncenderGraficos()                           |";
Message "| 3. Crea una rutina HandleGlkEvent() y llama desde ella a:        |";
Message "|    Mapa_HandleGlkEvent(ev, context, buffer)                      |";
Message "| 4. Crea una rutina IdentifyGlkObject() y llama desde ella a:     |";
Message "|    Mapa_IdentifyGlkObject(fase, tipo, ref, rock)                 |";
Message "|__________________________________________________________________|";

Constant GG_MAPAWIN_ROCK = 212;

Global gg_mapawin;
Global ladoCuadrado = 41;
Global g_sitio = 0;              ! El sitio actual (se usa en Mapa_HandleGlkEvent)

Default COLOR_LOCAL_MAP          = $ffffff;
Default COLOR_CURSOR_MAP         = $00aaaa;
Default COLOR_ACTUAL_MAP         = $aaaaaa;
Default COLOR_PUERTA_ABIERTA_MAP = $00ff00;
Default COLOR_PUERTA_CERRADA_MAP = $ff0000;
Default COLOR_UPDOWN_MAP         = $0000ff;
Default COLOR_INOUT_MAP          = $0000ff;

Verb meta 'mapa'
  *                 -> Mapa;

[ Mapa_IdentifyGlkObject fase tipo ref rock
  cenx ceny;
   if (fase == 0) { ! Poner cero en todos nuestros objetos glk
      gg_mapawin = 0;
      return;
   }       
   if (fase == 1) { ! Reiniciar correctamente las variables glk
      switch (tipo) {
         0: ! es una ventana
            switch (rock) {
               GG_MAPAWIN_ROCK: gg_mapawin = ref;
            }
         1: ! es un flujo
            ! pero no hay flujos en este ejemplo
         2: ! es una referencia a fichero
            ! pero no hay ficheros en este ejemplo
      }
      return;
   }       
   if (fase == 2) { ! Actualizar nuestras ventanas
      glk_window_get_size(gg_mapawin, gg_arguments, gg_arguments + WORDSIZE);
      cenx = (gg_arguments-->0) / 2; ! ancho / 2
      ceny = (gg_arguments-->1) / 2; ! alto / 2
      RefrescarMapa(g_sitio, cenx, ceny);
   }
];

[ Mapa_HandleGlkEvent ev context buffer
  cenx ceny;
  context = context;
  buffer = buffer;
  switch (ev-->0) {
    evtype_Redraw, evtype_Arrange:
      if (g_sitio ~= 0) {
!        AbrirVentanaMapa();
        glk_window_get_size(gg_mapawin, gg_arguments, gg_arguments + WORDSIZE);
        cenx = (gg_arguments-->0) / 2; ! ancho / 2
        ceny = (gg_arguments-->1) / 2; ! alto / 2
        RefrescarMapa(g_sitio, cenx, ceny);
      }
  }
];

[ EncenderGraficos;
  rfalse;
];

[ DibujarPuertaMapa cenx ceny ck
  color;
  if (ck == 2) color = COLOR_PUERTA_ABIERTA_MAP;
  else         color = COLOR_PUERTA_CERRADA_MAP;
  glk_window_fill_rect(gg_mapawin, color,
                       cenx - ladoCuadrado / 8, ceny - ladoCuadrado / 8,
                       ladoCuadrado / 4 + 1, ladoCuadrado / 4 + 1);
];

#ifndef LugarReal;
[ LugarReal;
  if (location == thedark) return real_location;
  else                     return location;
];
#endif;

[ DibujarMapa sitio posx posy central
  color sep mitad x y ck;
  if (~~(sitio.dibujado)) {
    sitio.dibujado = true;
    if (sitio == LugarReal()) color = COLOR_ACTUAL_MAP;
    else if (central == 1)    color = COLOR_CURSOR_MAP;
    else                      color = COLOR_LOCAL_MAP;
    mitad = ladoCuadrado / 2;
    glk_window_fill_rect(gg_mapawin, color, posx - mitad, posy - mitad,
                         ladoCuadrado, ladoCuadrado);
    sep = ladoCuadrado + mitad;
    ck = ComprobarSalidaMapa(sitio, e_to); 
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad, posy, ck);
      glk_window_fill_rect(gg_mapawin, $ffffff, posx + mitad, posy,
                           sep - ladoCuadrado + 1, 1);
      DibujarMapa(DestinoSalidaMapa(sitio, e_to), posx + sep, posy, 0);
    }
    ck = ComprobarSalidaMapa(sitio, w_to); 
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad, posy, ck);
      glk_window_fill_rect(gg_mapawin, $ffffff, posx - sep + mitad, posy,
                           sep - ladoCuadrado + 1, 1);
      DibujarMapa(DestinoSalidaMapa(sitio, w_to), posx - sep, posy, 0);
    }
    ck = ComprobarSalidaMapa(sitio, n_to); 
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx, posy - mitad, ck);
      glk_window_fill_rect(gg_mapawin, $ffffff, posx, posy - sep + mitad, 1,
                           sep - ladoCuadrado + 1);
      DibujarMapa(sitio.n_to, posx, posy - sep, 0);
    }
    ck = ComprobarSalidaMapa(sitio, s_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx, posy + mitad, ck);
      glk_window_fill_rect(gg_mapawin, $ffffff, posx, posy + mitad, 1,
                           sep - ladoCuadrado + 1);
      DibujarMapa(sitio.s_to, posx, posy + sep, 0);
    }
    ck = ComprobarSalidaMapa(sitio, nw_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad, posy - mitad, ck);
      for (x = posx - sep + mitad, y = posy - sep + mitad : x <= posx - mitad : x++, y++) {
        glk_window_fill_rect(gg_mapawin, $ffffff, x, y, 1, 1);
      }
      DibujarMapa(sitio.nw_to, posx - sep, posy - sep, 0);
    }
    ck = ComprobarSalidaMapa(sitio, ne_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad, posy - mitad, ck);
      for (x = posx + mitad, y = posy - mitad : x <= posx + sep - mitad : x++, y--) {
        glk_window_fill_rect(gg_mapawin, $ffffff, x, y, 1, 1);
      }
      DibujarMapa(sitio.ne_to, posx + sep, posy - sep, 0);
    }
    ck = ComprobarSalidaMapa(sitio, sw_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad, posy + mitad, ck);
      for (x = posx - sep + mitad, y = posy + sep - mitad : x <= posx - mitad : x++, y--) {
        glk_window_fill_rect(gg_mapawin, $ffffff, x, y, 1, 1);
      }
      DibujarMapa(sitio.sw_to, posx - sep, posy + sep, 0);
    }
    ck = ComprobarSalidaMapa(sitio, se_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad, posy + mitad, ck);
      for (x = posx + mitad, y = posy + mitad : x <= posx + sep - mitad : x++, y++) {
        glk_window_fill_rect(gg_mapawin, $ffffff, x, y, 1, 1);
      }
      DibujarMapa(sitio.se_to, posx + sep, posy + sep, 0);
    }
    ck = ComprobarSalidaMapa(sitio, u_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad / 2, posy - mitad / 2 + mitad / 4, ck);
      glk_window_fill_rect(gg_mapawin, COLOR_UPDOWN_MAP, posx + mitad / 2,
                           posy - mitad / 2, 1, mitad);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapawin, COLOR_UPDOWN_MAP, posx + mitad / 2 + x,
                             posy - mitad / 2 + x, 1, 1);
        glk_window_fill_rect(gg_mapawin, COLOR_UPDOWN_MAP, posx + mitad / 2 - x,
                             posy - mitad / 2 + x, 1, 1);
      }
    }
    ck = ComprobarSalidaMapa(sitio, d_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad / 2, posy + mitad / 2 - mitad / 4, ck);
      glk_window_fill_rect(gg_mapawin, COLOR_UPDOWN_MAP, posx + mitad / 2,
                           posy - mitad / 2, 1, mitad);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapawin, COLOR_UPDOWN_MAP, posx + mitad / 2 + x,
                             posy + mitad / 2 - x, 1, 1);
        glk_window_fill_rect(gg_mapawin, COLOR_UPDOWN_MAP, posx + mitad / 2 - x,
                             posy + mitad / 2 - x, 1, 1);
      }
    }
    ck = ComprobarSalidaMapa(sitio, in_to);
    posx = posx - mitad / 3;
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad / 2 - mitad / 4, posy, ck);
      glk_window_fill_rect(gg_mapawin, COLOR_INOUT_MAP, posx - mitad / 2,
                           posy, mitad, 1);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapawin, COLOR_INOUT_MAP, posx + mitad / 2 - x,
                             posy - x, 1, 1);
        glk_window_fill_rect(gg_mapawin, COLOR_INOUT_MAP, posx + mitad / 2 - x,
                             posy + x, 1, 1);
      }
    }
    ck = ComprobarSalidaMapa(sitio, out_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad / 2 + mitad / 4, posy, ck);
      glk_window_fill_rect(gg_mapawin, COLOR_INOUT_MAP, posx - mitad / 2,
                           posy, mitad, 1);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapawin, COLOR_INOUT_MAP, posx - mitad / 2 + x,
                             posy + x, 1, 1);
        glk_window_fill_rect(gg_mapawin, COLOR_INOUT_MAP, posx - mitad / 2 + x,
                             posy - x, 1, 1);
      }
    }    
  }
];

[ RefrescarMapa sitio cenx ceny
  o;
  clearMainWindow();
  if (sitio provides sgw_img) drawImageSGW(gg_bigwin, sitio.sgw_img, POS_CENTRADO,
                                           BORDEWIN, BORDEWIN);
  glk_window_get_size(gg_mapawin, gg_arguments, gg_arguments + WORDSIZE);
  glk_window_fill_rect(gg_mapawin, $ffffff, 0, 0, gg_arguments-->0, gg_arguments-->1);
  glk_window_fill_rect(gg_mapawin, $000000, 2, 2, gg_arguments-->0 - 4, gg_arguments-->1 - 4);
  DibujarMapa(sitio, cenx, ceny, 1);
  objectloop (o ofclass Lugar) o.dibujado = false;
  ImprimirBarraEstadoMapa(sitio);
];

[ ImprimirBarraEstadoMapa sitio;
  glk($002F, gg_statuswin); ! select
  glk($002A, gg_statuswin); ! clear
  glk($0086, style_SubHeader);
  ImprimirNombreSitioMapa(sitio);
  glk($0025, gg_statuswin, gg_arguments, gg_arguments + WORDSIZE); ! window_get_size
  glk($002B, gg_statuswin, gg_arguments-->0 - 11, 0); ! locate
  print "| H = Ayuda";
  glk($002F, gg_mainwin);   ! select
  #ifdef IMPRIMIR_DESCRIPCION_MAPA;
  PrintOrRun(sitio, description);
  #endif;
];

[ ImprimirNombreSitioMapa sitio;
  print (name) sitio;
];

[ EsMapeable sitio;
  #ifdef DEBUG;
  return sitio ofclass Lugar;
  #ifnot;
  return sitio ofclass Lugar && sitio has visited;
  #endif;
];

[ ComprobarSalidaMapa sitio dir
  destino;
  if (sitio provides dir) {
    destino = sitio.dir;
    if (ZRegion(destino) == 3) return 4;
    if (ZRegion(destino) == 2) destino = destino();
    if (destino && destino has door) {
      if (destino has open) return 2;
      else                  return 3;
    }
    return EsMapeable(sitio.dir);
  }
  rfalse;
];

[ DestinoSalidaMapa sitio dir
  destino;
  if (sitio provides dir) {
    destino = sitio.dir;
    if (ZRegion(destino) == 2) destino = destino();
    if (destino has door) {
      if (sitio == destino.ladoa) destino = destino.ladob;
      else                        destino = destino.ladoa;
    }
    return destino;
  }
];

[ ValidarYRefrescarMapa sitio dir cenx ceny;
  if (ComprobarSalidaMapa(sitio, dir) == 1 or 2 or 3) {
    sitio = DestinoSalidaMapa(sitio, dir);
    RefrescarMapa(sitio, cenx, ceny);
  }
  return sitio;
];

[ AbrirVentanaMapa;
  #ifdef ControlTimer;
  ControlTimer.PausarTick();
  #endif;
  gg_mapawin = glk_window_open(gg_mainwin, winmethod_Above + winmethod_Proportional,
                               100, wintype_Graphics, GG_MAPAWIN_ROCK);
  if (gg_mapawin == 0) return;
  glk_window_set_background_color(gg_mapawin, SCBACK);
  glk_window_clear(gg_mapawin);
];

[ CerrarVentanaMapa;
  glk_window_close(gg_mapawin, 0);
  closeAllWindows();
  clearMainWindow();
  EncenderGraficos();
  #ifdef ControlTimer;
  ControlTimer.ReanudarTick();
  #endif;
  <<Look>>;
];

[ AyudaMapa sitio cenx ceny
  altura;
  glk_window_clear(gg_mainwin);
  glk_window_clear(gg_mapawin);
  glk_window_clear(gg_objwin);
  glk_window_clear(gg_statuswin);
  glk($002F, gg_statuswin); ! select
  glk_window_get_size(gg_statuswin, gg_arguments, gg_arguments + WORDSIZE);
  altura = gg_arguments-->1;
  StatusLineHeight(12);
  glk($0086, style_SubHeader);
  glk($002B, gg_statuswin, 0, 0); ! locate
  print "Ayuda del mapa";
  glk($0086, style_Normal);

  print "^
         ^ ", (s_emph) "Cursor arriba", ", ", (s_emph) "8", ", ", (s_emph) "Y", ": ", (s_bold) "Norte",
           "       ", (s_emph) "7", ", ", (s_emph) "T", ": ", (s_bold) "Noroeste",
        "^ ", (s_emph) "Cursor abajo", ", ", (s_emph) "2", ", ", (s_emph) "N", ": ", (s_bold) "Sur",
           "          ", (s_emph) "9", ", ", (s_emph) "U", ": ", (s_bold) "Noreste",
        "^ ", (s_emph) "Cursor izquierda", ", ", (s_emph) "4", ", ", (s_emph) "G", ": ", (s_bold) "Oeste",
           "    ", (s_emph) "1", ", ", (s_emph) "B", ": ", (s_bold) "Suroeste",
        "^ ", (s_emph) "Cursor derecha", ", ", (s_emph) "6", ", ", (s_emph) "J", ": ", (s_bold) "Este",
           "       ", (s_emph) "3", ", ", (s_emph) "M", ": ", (s_bold) "Sureste",
        "^ ", (s_emph) "Inicio", ", ", (s_emph) "5", ": ", (s_bold) "Arriba",
           "                ", (s_emph) "Enter", ", ", (s_emph) "*", ": ", (s_bold) "Entrar",
        "^ ", (s_emph) "Fin", ", ", (s_emph) "0", ": ", (s_bold) "Abajo",
           "                    ", (s_emph) "Retroceso", ", ", (s_emph) "/", ", ", (s_emph) ".", ": ", (s_bold) "Salir",
        "^ ", (s_emph) "Z", ", ", (s_emph) "+", ": ", (s_bold) "Acercar",
           "                    ", (s_emph) "Q", ": ", (s_bold) "Salir",
        "^ ", (s_emph) "X", ", ", (s_emph) "-", ": ", (s_bold) "Alejar";
  print "^^ [ Pulsa una tecla para continuar ]";
  KeyDelay();
  StatusLineHeight(altura);
  glk($0086, style_SubHeader);
  glk($002F, gg_mainwin);   ! select
  RefrescarMapa(sitio, cenx, ceny);
];

[ MapaSub
  cenx ceny sitio tecla;
  AbrirVentanaMapa();
  glk_window_get_size(gg_mapawin, gg_arguments, gg_arguments + WORDSIZE);
  cenx = (gg_arguments-->0) / 2; ! ancho / 2
  ceny = (gg_arguments-->1) / 2; ! alto / 2
  sitio = LugarReal();
  RefrescarMapa(sitio, cenx, ceny);
  while (true) {
    g_sitio = sitio;
    tecla = KeyDelay();
    glk_window_get_size(gg_mapawin, gg_arguments, gg_arguments + WORDSIZE);
    cenx = (gg_arguments-->0) / 2; ! ancho / 2
    ceny = (gg_arguments-->1) / 2; ! alto / 2
    switch (tecla) {
      'q', 'Q':           jump Salir;
      'z', 'Z', '+':      ladoCuadrado = ladoCuadrado + 20;
                          RefrescarMapa(sitio, cenx, ceny);
      'x', 'X', '-':      if (ladoCuadrado > 21) {
                            ladoCuadrado = ladoCuadrado - 20;
                            RefrescarMapa(sitio, cenx, ceny);
                          }
      -5, '2', 'n', 'N':  sitio = ValidarYRefrescarMapa(sitio, s_to,   cenx, ceny);
      -4, '8', 'y', 'Y':  sitio = ValidarYRefrescarMapa(sitio, n_to,   cenx, ceny);
      -2, '4', 'g', 'G':  sitio = ValidarYRefrescarMapa(sitio, w_to,   cenx, ceny);
      -3, '6', 'j', 'J':  sitio = ValidarYRefrescarMapa(sitio, e_to,   cenx, ceny);
      '7', 't', 'T':      sitio = ValidarYRefrescarMapa(sitio, nw_to,  cenx, ceny);
      '9', 'u', 'U':      sitio = ValidarYRefrescarMapa(sitio, ne_to,  cenx, ceny);
      '1', 'b', 'B':      sitio = ValidarYRefrescarMapa(sitio, sw_to,  cenx, ceny);
      '3', 'm', 'M':      sitio = ValidarYRefrescarMapa(sitio, se_to,  cenx, ceny);
      -12, 'a', 'A', '5': sitio = ValidarYRefrescarMapa(sitio, u_to,   cenx, ceny); ! Inicio
      -13, 'z', 'Z', '0': sitio = ValidarYRefrescarMapa(sitio, d_to,   cenx, ceny); ! Fin
      -6, '*':            sitio = ValidarYRefrescarMapa(sitio, in_to,  cenx, ceny); ! Enter
      -7, '.', '/':       sitio = ValidarYRefrescarMapa(sitio, out_to, cenx, ceny); ! Retroceso
      'h', 'H':           AyudaMapa(sitio, cenx, ceny);
      #ifdef DEBUG;
      ' ':                playerTo(sitio); jump Salir;
      #endif;
    }
  }
.Salir;
  CerrarVentanaMapa();
  g_sitio = 0;
];

! Fin
