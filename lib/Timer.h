Include "infglk";

System_file;

#ifdef HandleGlkEvent;
  Message "[TIMER: Usando rutina HandleGlkEvent() proporcionada por el juego]";
  Message "[TIMER: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
  Message "[TIMER: -> < ControlTimer.HandleGlk(ev, context, buffer) > ]";
#endif; ! HandleGlkEvent

! Nuestra particular versi�n de HandleGlkEvent:
[ HandleGlkEvent ev context buffer;
  ControlTimer.HandleGlk(ev, context, buffer);
];

! Nuestra particular versi�n de EsperarTecla:
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
    condicion true,          ! Si es false, no se ejecutar� el evento
    duracion  0,             ! N�mero de ticks necesarios para ejecutarse
    evento [; rfalse; ],     ! El evento a ejecutar
    AsignarGestor [ pos;     ! A�ade este gestor a la lista de gestores
      ControlTimer.AsignarGestor(self, pos);
    ],
    EliminarGestor [;        ! Elimina este gestor de la lista de gestores
      ControlTimer.EliminarGestor(self, 0);
    ],
    ActivarMutex [;          ! Activa el mutex sobre este gestor
      ControlTimer.ActivarMutex(self);
    ];

Object ControlTimer
  private
    gestores 0 0 0 0 0 0 0 0 0 0,     ! Array de gestores de eventos
    duracion_maxima 0,                ! Duraci�n m�xima entre los gestores (en n� de ticks) 
    tick 0,                           ! Duraci�n del tick (en ms)
    tick_pausado 0,                   ! Aqu� se guarda el tick cuando se pausa
    contador_ticks 1,                 ! El contador de ticks (va de 1 a duracion_maxima en ciclo)
    mutex 0,                          ! Sem�foro de exclusi�n mutua
    ha_imprimido_algo true,           ! Para saber si hay que restaurar la l�nea de �rdenes
    RestaurarLineaOrdenes [ buffer;   ! Restaura la l�nea de �rdenes
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
    RecalcularMaximo [ i max;         ! Vuelve a calcular la duraci�n m�xima
      max = -1;
      for (i = 0: i < self.#gestores / WORDSIZE: i++) {
        if (self.&gestores-->i > max) {
          max = self.&gestores-->i;
        }
      }
      self.duracion_maxima = max;
    ],
  with
    CTEsperarTecla [ s delay;         ! Nuestra propia versi�n de EsperarTecla
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
    HandleGlk [ev context buffer i t; ! Nuestra versi�n de HandleGlkEvent
      context = context;
      switch (ev-->0) {
        evtype_Timer:
          self.ReiniciarImpresion();
          for (i = 0: i < self.#gestores / WORDSIZE: i++) {
            t = self.&gestores-->i;
            ! Si hay gestor y su duraci�n es m�ltiplo del tick:
            if (t ~= 0 && self.contador_ticks % t.duracion == 0) {
              ! Si no hay mutex o lo tiene asignado el gestor t:
              if (self.mutex == 0 or t) {
                ! Si la condici�n se cumple:
                if (VR(t.condicion)) {
                  ! Si el evento retorna true:
                  if (t.evento()) {
                    break;
                  }
                }
              }
            }
          }
          ! Contador c�clico entre 1 y duracion_maxima:
          if (self.contador_ticks >= self.duracion_maxima) {
            self.contador_ticks = 1;
          } else {
            self.contador_ticks++;
          }
          ! Si se ha imprimido algo en alg�n gestor, restauramos:
          if (self.ha_imprimido_algo) {
            return self.RestaurarLineaOrdenes(buffer);
          } else {
            return 1;
          }
      }
    ],
    AsignarGestor [ g pos i;          ! Asigna un gestor a una posici�n del array
      if (pos ~= 0) {
        if (pos < 0 || pos >= self.#gestores / WORDSIZE) {
          #ifdef DEBUG;
            "ERROR: La posici�n para el gestor de timer sobrepasa los l�mites.";
          #endif;
          #ifndef DEBUG;
            rtrue;
          #endif;
        }
      } else {  
        for (i = 0: i < self.#gestores / WORDSIZE: i++) {
          if (self.&gestores-->i == 0) break;
        }
        if (i < self.#gestores / WORDSIZE) {
          pos = i;
        } else {
          #ifdef DEBUG;
            "ERROR: Superado n�mero m�ximo de gestores de timer.";
          #endif;
          #ifndef DEBUG;
            rtrue;
          #endif;
        }
      }
      self.&gestores-->pos = g;
      if (g.duracion > self.duracion_maxima) {
        self.duracion_maxima = g.duracion;
      }
    ],
    EliminarGestor [ g pos i d;       ! Elimina un gestor dados �l o su posici�n en el array
      if (g ~= 0 && g ofclass GestorTimer) {
        pos = -1;
        for (i = 0: i < self.#gestores / WORDSIZE: i++) {
          if (self.&gestores-->i == g) {
            pos = i;
            break;
          }
        }
        if (pos == -1) {
          rfalse;
        }
      } else if (pos < 0 || pos >= self.#gestores / WORDSIZE) {
        rfalse;
      }
      d = (self.&gestores-->pos).duracion;
      self.&gestores-->pos = 0;
      if (d == self.duracion_maxima) {
        self.RecalcularMaximo();
      }
    ],
    PrepararImpresion [;              ! Llamada por los gestores antes de imprimir algo
      if (~~(self.ha_imprimido_algo)) {
        self.ha_imprimido_algo = true;
        glk_cancel_line_event(gg_mainwin, gg_event);    ! Cancelamos la entrada de usuario
      }
    ],
    ReiniciarImpresion [;             ! Reinicia el indicador de 'imprimido algo'
      self.ha_imprimido_algo = false;
    ],
    AsignarTick [ t;                  ! Asigna la duraci�n del tick
      self.tick = t;
    ],
    ActivarTick [ t;                  ! Activa el timer (opcionalmente, asignando el tick antes)
      if (t ~= 0) {
        self.AsignarTick(t);
      }
      glk_request_timer_events(self.tick);
    ],
    PausarTick [;                     ! Detiene el timer temporalmente
      self.tick_pausado = self.tick;
      self.DesactivarTick();
    ],
    ReanudarTick [;                   ! Reanuda el timer detenido
      self.ActivarTick(self.tick_pausado);
      self.tick_pausado = 0;
    ],
    DesactivarTick [;                 ! Desactiva el timer
      self.AsignarTick(0);
      self.ActivarTick();
    ],
    ReactivarTick [;                  ! Reactiva el timer (�til en algunos casos)
      self.DesactivarTick();
      self.ActivarTick();
    ],
    ActivarMutex [ g;                 ! Activa el mutex sobre un gestor
      self.mutex = g;
    ],
    DesactivarMutex [;                ! Desactiva el mutex si lo hubiera
      self.mutex = 0;
    ],
    Reiniciar [ i;                    ! Pone todas las propiedades a sus valores por defecto
      self.DesactivarTick();
      self.tick = 0;
      self.duracion_maxima = 0;
      self.contador_ticks = 1;
      self.mutex = 0;
      self.ha_imprimido_algo = true;
      for (i = 0: i < self.#gestores / WORDSIZE: i++) {
        self.&gestores-->i = 0;
      }
    ];

