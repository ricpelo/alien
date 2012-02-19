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

Message "[ Incluyendo Mapeador.h ]";

Global gg_mapa_win;
Global ladoCuadrado = 41;

Default COLOR_LOCAL_MAP          = $ffffff;
Default COLOR_CURSOR_MAP         = $00aaaa;
Default COLOR_ACTUAL_MAP         = $aaaaaa;
Default COLOR_PUERTA_ABIERTA_MAP = $00ff00;
Default COLOR_PUERTA_CERRADA_MAP = $ff0000;
Default COLOR_UPDOWN_MAP         = $0000ff;
Default COLOR_INOUT_MAP          = $0000ff;

Default ALTO_VENTANA_MAPA        = 700;

Verb meta 'mapa'
  *                 -> Mapa;

[ DibujarPuertaMapa cenx ceny ck
  color;
  if (ck == 2) color = COLOR_PUERTA_ABIERTA_MAP;
  else         color = COLOR_PUERTA_CERRADA_MAP;
  glk_window_fill_rect(gg_mapa_win, color,
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
    glk_window_fill_rect(gg_mapa_win, color, posx - mitad, posy - mitad,
                         ladoCuadrado, ladoCuadrado);
    sep = ladoCuadrado + mitad;
    ck = ComprobarSalidaMapa(sitio, e_to); 
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad, posy, ck);
      else {
        glk_window_fill_rect(gg_mapa_win, $ffffff, posx + mitad, posy,
                             sep - ladoCuadrado + 1, 1);
        DibujarMapa(sitio.e_to, posx + sep, posy, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, w_to); 
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad, posy, ck);
      else {
        glk_window_fill_rect(gg_mapa_win, $ffffff, posx - sep + mitad, posy,
                             sep - ladoCuadrado + 1, 1);
        DibujarMapa(sitio.w_to, posx - sep, posy, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, n_to); 
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx, posy - mitad, ck);
      else {
        glk_window_fill_rect(gg_mapa_win, $ffffff, posx, posy - sep + mitad, 1,
                             sep - ladoCuadrado + 1);
        DibujarMapa(sitio.n_to, posx, posy - sep, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, s_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx, posy + mitad, ck);
      else {
        glk_window_fill_rect(gg_mapa_win, $ffffff, posx, posy + mitad, 1,
                             sep - ladoCuadrado + 1);
        DibujarMapa(sitio.s_to, posx, posy + sep, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, nw_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad, posy - mitad, ck);
      else {
        for (x = posx - sep + mitad, y = posy - sep + mitad : x <= posx - mitad : x++, y++) {
          glk_window_fill_rect(gg_mapa_win, $ffffff, x, y, 1, 1);
        }
        DibujarMapa(sitio.nw_to, posx - sep, posy - sep, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, ne_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad, posy - mitad, ck);
      else {
        for (x = posx + mitad, y = posy - mitad : x <= posx + sep - mitad : x++, y--) {
          glk_window_fill_rect(gg_mapa_win, $ffffff, x, y, 1, 1);
        }
        DibujarMapa(sitio.ne_to, posx + sep, posy - sep, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, sw_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad, posy + mitad, ck);
      else {
        for (x = posx - sep + mitad, y = posy + sep - mitad : x <= posx - mitad : x++, y--) {
          glk_window_fill_rect(gg_mapa_win, $ffffff, x, y, 1, 1);
        }
        DibujarMapa(sitio.sw_to, posx - sep, posy + sep, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, se_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad, posy + mitad, ck);
      else {
        for (x = posx + mitad, y = posy + mitad : x <= posx + sep - mitad : x++, y++) {
          glk_window_fill_rect(gg_mapa_win, $ffffff, x, y, 1, 1);
        }
        DibujarMapa(sitio.se_to, posx + sep, posy + sep, 0);
      }
    }
    ck = ComprobarSalidaMapa(sitio, u_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad / 2, posy - mitad / 2 + mitad / 4, ck);
                                        
      glk_window_fill_rect(gg_mapa_win, COLOR_UPDOWN_MAP, posx + mitad / 2,
                           posy - mitad / 2, 1, mitad);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapa_win, COLOR_UPDOWN_MAP, posx + mitad / 2 + x,
                             posy - mitad / 2 + x, 1, 1);
        glk_window_fill_rect(gg_mapa_win, COLOR_UPDOWN_MAP, posx + mitad / 2 - x,
                             posy - mitad / 2 + x, 1, 1);
      }
    }
    ck = ComprobarSalidaMapa(sitio, d_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad / 2, posy + mitad / 2 - mitad / 4, ck);

      glk_window_fill_rect(gg_mapa_win, COLOR_UPDOWN_MAP, posx + mitad / 2,
                           posy - mitad / 2, 1, mitad);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapa_win, COLOR_UPDOWN_MAP, posx + mitad / 2 + x,
                             posy + mitad / 2 - x, 1, 1);
        glk_window_fill_rect(gg_mapa_win, COLOR_UPDOWN_MAP, posx + mitad / 2 - x,
                             posy + mitad / 2 - x, 1, 1);
      }
    }
    ck = ComprobarSalidaMapa(sitio, in_to);
    posx = posx - mitad / 3;
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx + mitad / 2 - mitad / 4, posy, ck);

      glk_window_fill_rect(gg_mapa_win, COLOR_INOUT_MAP, posx - mitad / 2,
                           posy, mitad, 1);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapa_win, COLOR_INOUT_MAP, posx + mitad / 2 - x,
                             posy - x, 1, 1);
        glk_window_fill_rect(gg_mapa_win, COLOR_INOUT_MAP, posx + mitad / 2 - x,
                             posy + x, 1, 1);
      }
    }
    ck = ComprobarSalidaMapa(sitio, out_to);
    if (ck) {
      if (ck == 2 or 3) DibujarPuertaMapa(posx - mitad / 2 + mitad / 4, posy, ck);
 
      glk_window_fill_rect(gg_mapa_win, COLOR_INOUT_MAP, posx - mitad / 2,
                           posy, mitad, 1);
      for (x = 1 : x <= mitad / 4 : x++) {
        glk_window_fill_rect(gg_mapa_win, COLOR_INOUT_MAP, posx - mitad / 2 + x,
                             posy + x, 1, 1);
        glk_window_fill_rect(gg_mapa_win, COLOR_INOUT_MAP, posx - mitad / 2 + x,
                             posy - x, 1, 1);
      }
    }    
  }
];

[ RefrescarMapa sitio cenx ceny
  o;
  clearMainWindow();
  DibujarMapa(sitio, cenx, ceny, 1);
  objectloop (o ofclass Lugar) o.dibujado = false;
  ImprimirNombreSitioMapa(sitio);
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
  openGraphicWindow(ALTO_VENTANA_MAPA);
  gg_mapa_win = gg_bigwin;
];

[ CerrarVentanaMapa;
  clearMainWindow();
  #ifdef EncenderGraficos;
  EncenderGraficos();
  #endif;
  #ifdef ControlTimer;
  ControlTimer.ReanudarTick();
  #endif;
  <<Look>>;
];

[ MapaSub
  cenx ceny sitio tecla;
  AbrirVentanaMapa();
  glk_window_get_size(gg_mapa_win, gg_arguments, gg_arguments + WORDSIZE);
  cenx = (gg_arguments-->0) / 2; ! ancho / 2
  ceny = (gg_arguments-->1) / 2; ! alto / 2
  sitio = LugarReal();
  RefrescarMapa(sitio, cenx, ceny);
  while (true) {
    tecla = KeyDelay();
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
      #ifdef DEBUG;
      ' ':                playerTo(sitio); jump Salir;
      #endif;
    }
  }
.Salir;
  CerrarVentanaMapa();
];

