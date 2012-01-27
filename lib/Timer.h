Include "infglk";

System_file;

#ifdef HandleGlkEvent;
  Message "[TIMER: Usando rutina HandleGlkEvent() proporcionada por el juego]";
  Message "[TIMER: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
  Message "[TIMER: -> < ControlTimer.HandleGlk(ev, context, buffer) > ]";
#endif; ! HandleGlkEvent

[ HandleGlkEvent ev context buffer;
  ControlTimer.HandleGlk(ev, context, buffer);
];

[ EsperarTecla s delay;
  return ControlTimer.CTEsperarTecla(s, delay);
];

#ifndef VR;
  [ VR valor;
    if (ZRegion(valor) == 2)
      return valor();
    else
      return valor;
  ];
#endif;

Class GestorTimer
  with
    condicion true,
    duracion  0,
    evento [; rfalse; ],
    AsignarGestor [ pos;
      ControlTimer.AsignarGestor(self, pos);
    ],
    ActivarMutex [;
      ControlTimer.ActivarMutex(self);
    ];

Object ControlTimer
!  private
  with
    timers 0 0 0 0 0 0 0 0 0 0,
    timer_actual 0,
    timer_maximo 0,
    tick 0,
    contador_ticks 1,
    mutex 0,
    ha_imprimido_algo true,
    RestaurarLineaOrdenes [ buffer;
      if (banderafin == 1) {
        print "^^";
        M__L(##Miscelanea, 3);
        ActualizarEstatus();
        AfterGameOver();
      }
      M__L(##Prompt);
      buffer-->0 = gg_event-->2;
      glk_request_line_event(gg_mainwin, buffer + WORDSIZE,
                             INPUT_BUFFER_LEN - WORDSIZE, buffer-->0);
      return 1;
    ],
    RecalcularMaximo [ i max;
      max = -1;
      for (i = 0: i < self.#timers / WORDSIZE: i++) {
        if (self.&timers-->i > max) {
          max = self.&timers-->i;
        }
      }
      self.timer_maximo = max;
    ],
    ActivarTimer [ t;
      if (t ~= self.timer_actual) {
        self.timer_actual = t;
        glk_request_timer_events(t);
      }
    ],
    DesactivarTimer [;
      self.ActivarTimer(0);
    ],
!  with
    CTEsperarTecla [ s delay;
      if (s) print (string) s;
      glk($00D6, delay * 5);                ! request_timer_events
      glk($00D2, gg_mainwin);               ! glk_request_char_event(gg_mainwin);
      while (1) {
        glk($00C0, gg_arguments);           ! glk_select(gg_arguments);
        if ((gg_arguments-->0) == 2) break; ! 2=evType_CharInput
        if ((gg_arguments-->0) == 1) {
          glk($00D3, gg_mainwin);           ! cancel_char_event
          glk($00D6, self.tick);
          return 0;
        }
      }
      glk($00D6, self.tick);
      return gg_arguments-->2;
    ],
    HandleGlk [ev context buffer i t;
      context = context;
      switch (ev-->0) {
        evtype_Timer:
          self.ReiniciarImpresion();
          for (i = 0: i < self.#timers / WORDSIZE: i++) {
            t = self.&timers-->i;
            if (t ~= 0 && self.contador_ticks % t.duracion == 0) {
              if (self.mutex == 0 or t) {
                if (VR(t.condicion)) {
                  if (t.evento()) {
                    break;
                  }
                }
              }
            }
          }
          if (self.contador_ticks >= self.timer_maximo) {
            self.contador_ticks = 1;
          } else {
            self.contador_ticks++;
          }
          if (self.ha_imprimido_algo) {
            return self.RestaurarLineaOrdenes(buffer);
          } else {
            return 1;
          }
      }
    ],
    AsignarGestor [ g pos i;
      if (pos ~= 0) {
        if (pos < 0 || pos >= self.#timers / WORDSIZE) {
          #ifdef DEBUG;
            "ERROR: La posición para el gestor de timer sobrepasa los límites.";
          #endif;
          #ifndef DEBUG;
            rtrue;
          #endif;
        }
      } else {  
        for (i = 0: i < self.#timers / WORDSIZE: i++) {
          if (self.&timers-->i == 0) break;
        }
        if (i < self.#timers / WORDSIZE) {
          pos = i;
        } else {
          #ifdef DEBUG;
            "ERROR: Superado número máximo de gestores de timer.";
          #endif;
          #ifndef DEBUG;
            rtrue;
          #endif;
        }
      }
      self.&timers-->pos = g;
      if (g.duracion > self.timer_maximo) {
        self.timer_maximo = g.duracion;
      }
    ],
    EliminarGestor [ g pos i d;
      if (g ~= 0 && g ofclass GestorTimer) {
        pos = -1;
        for (i = 0: i < self.#timers / WORDSIZE: i++) {
          if (self.&timers-->i == g) {
            pos = i;
            break;
          }
        }
        if (pos == -1) {
          rfalse;
        }
      } else if (pos < 0 || pos >= self.#timers / WORDSIZE) {
        rfalse;
      }
      d = (self.&timers-->pos).duracion;
      self.&timers-->pos = 0;
      if (d == self.timer_maximo) {
        self.RecalcularMaximo();
      }
    ],
    PrepararImpresion [;
      if (~~(self.ha_imprimido_algo)) {
        self.ha_imprimido_algo = true;
        glk_cancel_line_event(gg_mainwin, gg_event);    ! Cancelamos la entrada de usuario
      }
    ],
    ReiniciarImpresion [;
      self.ha_imprimido_algo = false;
    ],
    AsignarTick [ t;
      self.tick = t;
    ],
    ActivarTick [;
      self.ActivarTimer(self.tick);
    ],
    DesactivarTick [;
      self.ActivarTimer(0);
    ],
    ReactivarTick [;
      self.DesactivarTick();
      self.ActivarTick();
    ],
    ActivarMutex [ g;
      self.mutex = g;
    ],
    DesactivarMutex [;
      self.mutex = 0;
    ],
    Reiniciar [ i;
      self.DesactivarTimer();
      self.tick = 0;
      self.timer_actual = 0;
      self.timer_maximo = 0;
      self.contador_ticks = 1;
      self.mutex = 0;
      self.ha_imprimido_algo = true;
      for (i = 0: i < self.#timers / WORDSIZE: i++) {
        self.&timers-->i = 0;
      }
    ];

