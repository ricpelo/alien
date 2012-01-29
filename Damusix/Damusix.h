!===============================================================================
!  DREAMBYTES ADVENTURES: AD(M)INISTRADOR (U)NIFICADO DE (S)ON(I)DO EN GLUL(X)
!  Codigo Fuente
!===============================================================================
!
!  Archivo :  damusix.h
!  Fecha   :  2009/01/03
!  Version :  3/090103
!  Autor   :  Eliuk Blau
!  e-Mail  :  eliukblau (AT) gmail.com
!
!  Descripcion: Extension usada por DreamBytes Adventures para la programacion
!               de juegos de Ficcion Interactiva en Inform6, que proporciona un
!               Administrador Unificado de Sonido en Glulx capaz de gestionar
!               todas las funciones necesarias para la reproduccion de musica
!               y efectos de sonido en esta grandiosa maquina virtual. El
!               Gestor Avanzado de Damusix encapsula todo el codigo necesario
!               para el trabajo con el audio, permitiendo al programador hacer
!               uso de estas funcionalidades mediante una interface de
!               manejo sencilla.
!
!               El Gestor Avanzado de Audio de Damusix implementa 10 canales
!               "normales" para la reproduccion de sonidos con CONTROL TOTAL
!               (tocarlos, detenerlos, volumen individual, repeticion, etc.);
!               10 canales "virtuales" para una reproduccion de sonidos mas
!               limitada, pero con la ventaja de no tener que "asignar un
!               canal" previamente a un sonido concreto, permitiendo asi que
!               varios sonidos puedan tocarse al mismo tiempo sin interrumpirse
!               mutuamente ni tener que "asignarlos" cada vez a un canal
!               "normal" (el Gestor asignara los canales automaticamente);
!               y 1 canal especialmente dedicado al trabajo con la "lista de
!               reprod. de sonidos" que facilita Damusix. Esta "lista" tiene
!               espacio suficiente para 10 sonidos que luego tocara en el orden
!               en que hayan sido agregados, uno por uno. La "lista" puede ser
!               util para reproducir cadenas de sonidos.
!
!               Adicionalmente, los sonidos asignados a canales "normales"
!               pueden generar notificaciones del tipo evtype_SoundNotify que
!               el programador podra capturar en la rutina HandleGlkEvent()
!               de la libreria Inform.
!
!               La extension Damusix tambien permite realizar efectos de FadeIn
!               y FadeOut con los sonidos asignados a un canal "normal". Estos
!               efectos de Fade pueden ser o no en "tiempo-real". Un Fade en
!               "tiempo-real" transcurrira de fondo mientras el juego corre
!               normalmente. Un Fade en "tiempo-no-real" hara primero el efecto
!               y una vez haya finalizado, recien entonces devolvera el control
!               de la ejecucion al codigo a continuacion. Los Fades en "tiempo
!               real" pueden ser abortados en cualquier momento si el
!               programador lo necesita.
!
!               Resumen de Caracteristicas de la extension Damusix:
!               ---------------------------------------------------
!               * 10 Canales "Normales" con Control Total del Audio
!               * 10 Canales "Virtuales" para sonidos sin "canal asignado"
!               * Lista de Reproduccion de Sonidos (con espacio para 10 items)
!               * Control de Volumen Global del Gestor
!               * Control de Volumen Individual de cada Sonido
!               * Utilizacion con Abstraccion por Sonidos o por Canales
!               * Efectos de FadeIn y FadeOut en "tiempo-real/tiempo-no-real"
!               * Activar/Desactivar el Audio limpiamente (sin cambiar volumen)
!               * Comprobacion Automatica de Soporte de Audio a nivel de Glk
!               * Mecanismo de "Proteccion de Sonidos" ante UNDO/RESTORE
!               * Muchas caracteristicas mas... =D
!
!               Esta extension esta inspirada profundamente en el modulo
!               "efectos.h" de Jose Luis Diaz [aka Zak] (para la libreria
!               InformATE!); y en el manual Gull y el codigo fuente del juego
!               Jukebox, de Adam Cadre. Se les da el debido reconocimiento a
!               estos autores por su excelente trabajo.
!
!               Damusix requiere para funcionar correctamente:
!                 - Compilador Inform v6.30 o superior
!                 - Libreria Inform 6/11
!                 - Libreria "infglk.h"
!
!               Si modificas la extension Damusix, estare muy agradecido si
!               me mandas el codigo fuente por e-Mail.
!
!               If you modify the Damusix extension, I would be grateful if
!               you send me the source code by e-Mail.
!
!               Copyright (c) 2008 Nicolas Merino Quezada (aka Eliuk Blau).
!
!               This program is free software: you can redistribute it and/or
!               modify it under the terms of the GNU Lesser General Public
!               License as published by the Free Software Foundation, either
!               version 3 of the License.
!
!               This program is distributed in the hope that it will be useful,
!               but WITHOUT ANY WARRANTY; without even the implied warranty of
!               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
!               GNU Lesser General Public License for more details.
!
!               You should have received a copy of the GNU Lesser General
!               Public License along with this program. If not, see
!               <http://www.gnu.org/licenses/>.
!
!-------------------------------------------------------------------------------

#ifndef _DAMUSIX_H_;  ! se ha incluido ya?

Message "[DAMUSIX: <(DA): Ad(M)inistrador (U)nificado de (S)on(I)do en Glul(X)>]";
System_file; Constant _DAMUSIX_H_;

!===============================================================================
! COMPROBACIONES INICIALES
!-------------------------------------------------------------------------------
! ERROR: Se necesita el Compilador Inform v6.30 o superior
#ifndef VN_1630;
  Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAMUSIX: -> Se necesita el Compilador Inform v6.30 o superior]";
  Message fatalerror "";
#endif; ! VN_1630

! ERROR: Se necesita la Libreria Inform 6/11 o superior
#ifndef LIBRARY_VERSION;
  Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAMUSIX: -> Se necesita la Libreria Inform 6/11 o superior]";
  Message fatalerror "";
#endif;
#iftrue (LIBRARY_VERSION < 611);
  Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAMUSIX: -> Se necesita la Libreria Inform 6/11 o superior]";
  Message fatalerror "";
#endif; ! LIBRARY_VERSION

!-------------------------------------------------------------------------------
! ERROR SI SE ACTIVA COMPILACION PARA MAQUINA-Z
#ifdef TARGET_ZCODE;
  Message "[DAMUSIX: ERROR - Se esta generando codigo para la Maquina Z]";
  Message "[DAMUSIX: -> La extension solo funcionara en la Maquina Glulx]";
  Message fatalerror "";
#endif; ! TARGET_ZCODE

!===============================================================================
! IMPLEMENTACION AUTOMATICA DE LOS PUNTOS DE ENTRADA GLK MEDIANTE DAINUNEK
!-------------------------------------------------------------------------------
! el programador proporciona rutina IdentifyGlkObject() en el codigo del juego
#ifdef IdentifyGlkObject;
  #ifndef DAINUNEK_IGO; ! codigo segun Dainunek
    Message "[DAMUSIX: Usando rutina IdentifyGlkObject() proporcionada por el juego]";
    Message "[DAMUSIX: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
    Message "[DAMUSIX: -> < Damusix.IdentificarSonidos(fase) > ** OBLIGATORIO **]";
  #endif; ! DAINUNEK_IGO
#endif; ! IdentifyGlkObject

! el programador proporciona rutina HandleGlkEvent() en el codigo del juego
#ifdef HandleGlkEvent;
  #ifndef DAINUNEK_HGE; ! codigo segun Dainunek
    Message "[DAMUSIX: Usando rutina HandleGlkEvent() proporcionada por el juego]";
    Message "[DAMUSIX: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A...]";
    Message "[DAMUSIX: -> < Damusix.NotificarFade(ev) > ** OPTATIVO **]";
  #endif; ! DAINUNEK_HGE
#endif; ! HandleGlkEvent

!-------------------------------------------------------------------------------
! PARA LA INICIALIZACION UNIFICADA DE EXTENSIONES (PUNTOS DE ENTRADA GLK)
Include "Dainunek";

! ERROR: Se necesita la Extension Dainunek v3 o superior
#ifndef _DAINUNEK_VERSION_;
  Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAMUSIX: -> Se necesita la Extension Dainunek v3 o superior]";
  Message fatalerror "";
#endif;
#iftrue (_DAINUNEK_VERSION_ < 3);
  Message "[DAMUSIX: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAMUSIX: -> Se necesita la Extension Dainunek v3 o superior]";
  Message fatalerror "";
#endif; ! _DAINUNEK_VERSION_

#ifdef DAINUNEK_OK;
  Object Damusix_Glk Dainunek
    with
      IdentifyGlk [ fase;
        ! Identificar todos los Objetos de Sonido presentes en Damusix
        Damusix.IdentificarSonidos(fase);
      ],
      HandleGlk [ ev;
        ! Notificar Efecto de Fade (In, Out) en "tiempo-real" de Damusix
        Damusix.NotificarFade(ev);
      ],
  ;
#endif; ! DAINUNEK_OK
!-------------------------------------------------------------------------------

! LIBRERIA ABSOLUTAMENTE NECESARIA (para el trabajo con Glk)
Include "infglk";

!===============================================================================

! APROVECHAMOS METODO DE LA LIB. 6/11 PARA LA INICIALIZACION DE EXTENSIONES:
! en este caso, llamamos siempre en inicio del juego [justo antes de rutina
! Initialise()] a Damusix.InicializarGlk() para que se creen correctamente
! los todos los canales de audio y se preparen adecuadamente para su uso
Object "(Damusix_Ext)" LibraryExtensions
  with
    ext_initialise [ ;
      ! INICIALIZA GESTOR DE AUDIO DAMUSIX Y CANALES (NORMALES/VIRTUALES/LISTA)
      Damusix.InicializarGlk();
    ],
;

!===============================================================================

! LA VERSION DE LA EXTENSION DAMUSIX
Constant _DAMUSIX_VERSION_ = "3/090103";

#ifdef DEBUG;
  ! CONSTANTES PARA INTERNACIONALIZACION DE MENSAJES DE AVISO/ADVERTENCIA
  Constant ERROR_GLK_NO_FULL_AUDIO =
             "[AVISO: ¡Tu intérprete no soporta completamente el audio!]^
              [-No se reproducirán los sonidos ni las músicas de fondo-]^";

  Constant ERROR_LISTA_REPROD_LLENA =
             "[ERROR: ¡La Lista de Reproducción de sonidos se ha llenado!]^
              [-Imposible agregar un sonido si la Lista ya está completa-]^";

  Constant ERROR_TOCAR_LISTA_DURANTE_FADE =
             "[ERROR: ¡Actualmente ya está en proceso un trabajo de Fade!]^
              [-Imposible tocar la Lista de Reproducción durante un Fade-]^";

  Constant ERROR_HACER_FADE_DURANTE_FADE =
             "[ERROR: ¡Actualmente ya está en proceso un trabajo de Fade!]^
              [-Imposible ejecutar uno nuevo hasta que termine el actual-]^";
#endif; ! DEBUG

!===============================================================================

! CONSTANTES DE UTILIDAD PARA DAMUSIX
Constant DAMUSIX_ERROR_SND = -99;        ! SONIDO INCORRECTO (SIN GESTION/ERRONEO)
Constant DAMUSIX_ERROR_CNL = -66;        ! CANAL INCORRECTO (EL NUMERO ES ERRONEO)
Constant DAMUSIX_GG_ROCK   = 510;        ! ROCK CANAL CERO (en siguientes, sumar 1)
Constant DAMUSIX_VOLMAX    = $10000/100; ! EL VOLUMEN MAXIMO (para los porcentajes)
Constant DAMUSIX_NCANALMAX = 10; ! MAX. DE CANALES NORMALES QUE SE CREARAN  (gg_ncnl)
Constant DAMUSIX_VCANALMAX = 10; ! MAX. DE CANALES VIRTUALES QUE SE CREARAN (gg_vcnl)
Constant DAMUSIX_SNDLSTMAX = 10; ! MAX. DE SONIDOS DISPONIBLES EN 'LISTA DE REPROD.'

! ARRAY PARA EVENTOS USADO SOLO POR DAMUSIX
Array gg_damusix_event --> 4; ! IMPORTANTE!! Siempre debe tener 4 slots

!===============================================================================

! EL OBJETO DAMUSIX QUE LO CONTIENE TODO (constantes, variables y rutinas)
Object Damusix
  !=============================================================================
  !-----------------------------------------------------------------------------
  ! *** RUTINAS Y VARIABLES PRIVADAS RELACIONADAS CON EL TRABAJO DEL KERNEL ***
  !-----------------------------------------------------------------------------
  !=============================================================================
  private
    glk_sin_audio  false, ! la Glk del interprete no puede reproducir audio? (sonido sampleado y MODs)
    audio_activado true,  ! esta ACTIVADA la salida de audio de Damusix? (por defecto siempre activada)
    que_vcnl 0,       ! que numero de canal virtual sera usado para el siguente sonido? (0 al inicio)
    que_fade 0,       ! que tipo de Fade esta haciendo un canal normal? (0==Ninguno; 1==FadeIn; 2==FadeOut)
    vol_fade 0 0 0,   ! datos de volumen para Fades (-->0==vol.inicial; -->1==vol.final; -->2==vol.original)
    cnl_fade -1,      ! canal normal asignado al sonido que esta haciendo el Fade [-1=='sin canal']
    tick_fade 0,      ! guarda calculo del tiempo de cada tick del Fade actual (truco UNDO/RESTORE/RESTART)
    snd_pfadeout 0 0, ! sonido que debe tocarse luego del Fade [-->0==sonido; -->1==notificar?]
    vol_global 100,   ! porcentaje de volumen global actual (valor entre 0%-100% [por defecto 100%])
    vol_vcnl 100,     ! porcentaje de volumen comun actual para canales 'virtuales' (por defecto 100%)
    vol_lcnl 100,     ! porcentaje de volumen comun actual para 'lista de reprod.' (por defecto 100%)
    gg_lcnl 0,                   ! la referencia interna del canal para 'lista de reprod. de sonidos'
    gg_ncnl 0 0 0 0 0 0 0 0 0 0, ! las referencias internas de los 'canales normales'
    gg_vcnl 0 0 0 0 0 0 0 0 0 0, ! las referencias internas de los 'canales virtuales'
    snd_cnl 0 0 0 0 0 0 0 0 0 0, ! el sonido que se toca en cada canal normal
    vol_cnl 0 0 0 0 0 0 0 0 0 0, ! el volumen de cada canal normal (en porcentajes)
    rep_cnl 0 0 0 0 0 0 0 0 0 0, ! el modo de repeticion de cada canal normal ('LOOP' se indica con -1)
    est_cnl 0 0 0 0 0 0 0 0 0 0, ! estado del sonido de cada canal normal (0==det./'rep.finita'; 1==reprod.)
    pib_reg 0 0 0 0 0 0 0 0 0 0 0, ! registro del estado PIB (UNDO/RESTORE/RESTART) [-->10==audio_activado?]
    snd_lst 0 0 0 0 0 0 0 0 0 0  ! array de 'lista de reprod. de sonidos' (slots==DAMUSIX_SNDLSTMAX*2)
            0 0 0 0 0 0 0 0 0 0, ! - la columna par guarda sonidos; la impar, los tiempos de espera

    ! [KERNEL-1] ACTUALIZA TODO LO RELACIONADO CON UN CANAL NORMAL ESPECIFICO
    ! (estado de reproduccion, volumen, sonido inexistente, audio desactivado, etc.)
    ActualizarCanal [ nc esn ! nc: num. canal; esn: arg. oscuro, SoundNotify? (0==no; 1==si)
      pib ! arg. osc., actualizar estado PIB? [usado en ActualizarCanales() desde IdentificarSonidos()]
      flag_ok_play; ! reproducir el canal? (cuando el estado PIB indique que no, valdra FALSE)
      !-------------------------------------------------------------------------
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      !-------------------------------------------------------------------------
      ! detiene el canal si no posee sonido asignado o si el estado del
      ! sonido es cero (detenido o 'lanzado con reproduccion finita')
      if ((self.&snd_cnl-->nc == 0) || (self.&est_cnl-->nc == 0)) {
        ! detenemos el canal actual y retornamos sin hacer nada mas
        glk_schannel_stop(self.&gg_ncnl-->nc);
        self.ActualizarPIB(nc, pib); ! MUY IMPORTANTE: ACTUALIZAMOS ESTADO PIB
        return;
      }
      !-------------------------------------------------------------------------
      ! solo en el caso de que sonido NO DEBA TOCARSE INFINITAMENTE [rep ~= -1]
      ! ponemos el 'estado del sonido'==0 ('lanzado con reproduccion finita')
      if (self.&rep_cnl-->nc ~= -1) { self.&est_cnl-->nc = 0; }
      !-------------------------------------------------------------------------
      ! MUY IMPORTANTE: ACTUALIZAMOS AHORA REGISTRO DEL ESTADO PIB Y AVISAMOS...
      flag_ok_play = self.ActualizarPIB(nc, pib); ! SI SE DEBE 'RE-LANZAR' CANAL
      !-------------------------------------------------------------------------
      ! SI SALIDA DE AUDIO ESTA DESACTIVADA: DETENEMOS CANAL Y EVITAMOS REPROD.
      ! **** NOTA: NO CAMBIAR ESTE TROZO DE CODIGO DE POSICION!!!! ****
      if (~~self.audio_activado) {
        ! detenemos el canal actual y retornamos sin hacer nada mas
        glk_schannel_stop(self.&gg_ncnl-->nc);
        return;
      }
      !-------------------------------------------------------------------------
      ! SI TODO LO ANTERIOR SE HA SUPERADO, INICIAMOS AHORA LA REPRODUCCION
      !-------------------------------------------------------------------------
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        glk_schannel_set_volume(self.&gg_ncnl-->nc, self.&vol_cnl-->nc * DAMUSIX_VOLMAX);
      }
      ! y ahora tocamos ahora el sonido efectivamente...
      if (flag_ok_play) { ! siempre y cuando la actualizacion PIB no lo haya negado!!
        glk_schannel_play_ext(
          self.&gg_ncnl-->nc, ! el canal
          self.&snd_cnl-->nc, ! el sonido
          self.&rep_cnl-->nc, ! las repeticiones
          esn);               ! generar ev. SoundNotify al terminar? (0==no; 1==si)
      }
    ],

    ! [KERNEL-2] REALIZA UNA ACTUALIZACION MASIVA DE TODOS LOS CANALES NORMALES
    ! Ademas se invocara la actualizacion del registro del estado PIB, en el caso
    ! que sea llamada con 'pib'==1 [uso exclusivo en rutina IdentificarSonidos()]
    ActualizarCanales [ pib ! arg. oscuro, actualizar el registro del estado PIB?
      i; ! para iteraciones
      !-------------------------------------------------------------------------
      ! NOTA: aqui no comprobamos si la Glk soporta sonido o si la salida de
      ! audio esta activada, porque ya lo hace la propia rutina de abajo
      !-------------------------------------------------------------------------
      ! recorre todos los canales normales y los actualiza (con su registro PIB)
      for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) { self.ActualizarCanal(i,0,pib); }
      !-------------------------------------------------------------------------
      ! MUY IMPORTANTE: Guarda estado actual de activacion del audio. Esto es
      ! necesario que se haga aqui cuando se ha invocado una actualizacion PIB
      ! [*** EVITA UN POTENCIAL BUG ***] - NO MODIFICAR NI CAMBIAR DE POSICION
      #ifndef DAMUSIX_NO_PROTEGER_SONIDOS;
      if (pib == 1) { self.&pib_reg-->DAMUSIX_NCANALMAX = self.audio_activado; }
      #endif; ! DAMUSIX_NO_PROTEGER_SONIDOS
    ],

    ! [KERNEL-3] ACTUALIZA REGISTRO DEL ESTADO PIB DE UN CANAL NORMAL ESPECIFICO
    ! [usado exclusivamente en la rutina interna del Kernel-1 ActualizarCanal()]
    ! El registro del estado PIB de los canales normales de Damusix es un truco
    ! complejo para lograr que los sonidos no sean re-lanzados si actualmente
    ! estan 'sonando de fondo' (es decir, reproduciendose con 'rep. infinitas'
    ! [est_cnl==1]) y el jugador hace UNDO/RESTORE/RESTART en el juego. La Glk
    ! no tiene un sistema para conservar el 'estado de reproduccion' de los
    ! sonidos, asi que cuando se recuperan referencias [en IdentifyGlkObject()]
    ! es preciso 'volver a lanzar' la reproduccion de todos los sonidos que lo
    ! necesiten. El 'Registro del Estado PIB' es un array que se 'sincroniza'
    ! con los datos de los canales (concretamente, con los sonidos del canal y
    ! con su 'estado de reproduccion', si actualmente esta 'sonando de fondo').
    ! Gracias a una llamada en ensamblador de Glulx, se pueden "proteger" los
    ! datos del registro PIB ante los comandos UNDO/RESTORE/RESTART a fin de
    ! poder "compararlos" con los datos del kernel de Damusix recuperados luego
    ! de cambiar el "estado del juego". Esta "comparacion" logra la "magia" de
    ! hacer que si los sonidos estan actualmente 'sonando de fondo' (segun el
    ! Kernel de Damusix) y si esos mismos sonidos "ya estaban sonando de fondo"
    ! antes del UNDO/RESTORE/RESTART, significa que todavia estan "sonando"
    ! y no se debe volver a lanzarlos. Y se aprovecha para actualizar el PIB.
    ! [La llamada para proteger el registro PIB esta en IdentificarSonidos()]
    ! [Si ActualizarPIB() devuelve TRUE, ActualizarCanal() no debe re-lanzar]
    ! ['PIB' quiere decir: "Playing in the Background" (Sonando de Fondo) =P]
    ActualizarPIB [ nc pib ! nc: num. canal; pib: calc. re-lanzamiento canal?
      ok_play; ! flag val. de ret. que indica si se debe "re-lanzar" el canal
      !=========================================================================
      ! ** LO SIGUIENTE ES SIMPLEMENTE PARA EVITAR UN WARNING SI SE COMPILA **
      ! ** NO UTILIZANDO LA "PROTECCION DE SONIDOS" QUE PROPORCIONA DAMUSIX **
      !-------------------------------------------------------------------------
        #ifdef DAMUSIX_NO_PROTEGER_SONIDOS;
        nc = nc; pib = pib; ! esto evita un warning de variables no usadas
        #endif; ! DAMUSIX_NO_PROTEGER_SONIDOS
      !=========================================================================
      ok_play = true; ! idealmente, siempre se deberia re-lanzar el canal
      #ifndef DAMUSIX_NO_PROTEGER_SONIDOS;
      !-------------------------------------------------------------------------
      ! PARTE 1: ANALIZAMOS SI SE DEBE 'RE-LANZAR' CANAL INDICADO (SEGUN PIB)
      !-------------------------------------------------------------------------
      !** 'pib' VALE 1 SOLO CUANDO se llama desde rutina IdentificarSonidos()**
      if (pib == 1) { ! '1' INDICA QUE SE DEBE "CALCULAR" SI HAY QUE RE-LANZAR
        ! si el sonido asignado actualmente al canal es igual que el sonido
        ! "previo-al-cambio-de-estado-del-juego" (registrado en el PIB)...
        if (self.&snd_cnl-->nc == self.&pib_reg-->nc) {
          ! y si el PIB indica que antes del "cambio-de-estado" el audio
          ! SI ESTABA ACTIVADO (porque podemos 'recuperar' con el audio
          ! desactivado, caso en el que no hay que 're-lanzar' canales)
          if (self.&pib_reg-->DAMUSIX_NCANALMAX == true) { ! NO BORRAR!!
            ok_play = false; ! indicamos que no se debe "re-lanzar" el canal
          }
        }
      }
      else {
        !** 'pib' NO VALE 1 CUANDO se llama fuera de IdentificarSonidos()**
        ! (el resto de rutinas del Gestor SIEMPRE DEBERIAN RE-LANZAR CANAL)
        ! [ahora aprovechamos de guardar el estado de activacion del audio]
        ! [si 'pib'==1, activ. se guarda desde la rut. ActualizarCanales()]
        self.&pib_reg-->DAMUSIX_NCANALMAX = self.audio_activado; ! NO BORRAR!!
      }
      !-------------------------------------------------------------------------
      ! PARTE 2: ACTUALIZAMOS AHORA REGISTRO DEL ESTADO PIB DEL CANAL INDICADO
      !-------------------------------------------------------------------------
      if (self.&est_cnl-->nc == 1) { ! si canal actual ESTA 'SONANDO DE FONDO'
        self.&pib_reg-->nc = self.&snd_cnl-->nc; ! guardamos ese dato en el PIB
      }
      else { ! si el canal actual NO ESTA 'SONANDO DE FONDO', guardamos...
        self.&pib_reg-->nc = 0; ! un valor nulo en el PIB (MUY IMPORTANTE!!)
        !-----------------------------------------------------------------------
        ! Este sistema lo unico que hace es "recordar" solamente aquellos
        ! canales que estan 'sonando de fondo' y "calcular", en consecuencia,
        ! sus "potenciales re-lanzamientos". Si un canal no esta 'sonando de
        ! fondo', no tiene motivo de ser "recordado" por el registro PIB. =P
        !-----------------------------------------------------------------------
      }
      #endif; ! DAMUSIX_NO_PROTEGER_SONIDOS
      !-------------------------------------------------------------------------
      ! MUY IMPORTANTE: Finalmente retornamos indicando si se permite o no...
      return ok_play; ! 're-lanzar' el canal [ActualizarCanal() usa este valor]
    ],

    ! Realiza una pausa con ayuda del Timer [usada por TocarLista() y Fade***X()]
    HacerPausa [ ms; ! los milisegundos que durara la pausa temporizada
      ! provocamos un 'tick' del Timer cada 'ms' milisegundos
      glk_request_timer_events(ms);
      for (::) { ! un bucle infinito
        glk_select(gg_damusix_event); ! averiguamos el evento generado
        switch (gg_damusix_event-->0) {
          evtype_Timer: ! se genero un 'tick' del Timer?
            jump Damusix_HacerPausaFin; ! entonces debemos salir del bucle
          !---------------------------------------------------------------------
          evtype_Arrange,evtype_Redraw: ! se produjo cambio en las Ventanas?
            DrawStatusLine(); ! entonces debemos redibujar la barra de estado y...
            HandleGlkEvent(gg_damusix_event,1,gg_arguments); ! actualizar ventanas
        }
      }
      .Damusix_HacerPausaFin; ! etiqueta auxiliar para salir del bucle
      ! finalmente detenemos los 'ticks' del Timer
      glk_request_timer_events(0);
    ],

    ! Esta rutina se llama automaticamente luego de hacer UNDO/RESTORE/RESTART
    ! [es llamada desde IdentificarSonidos()] y simplemente sirve para comprobar
    ! si en el "nuevo estado del juego" existe un Fade activo. De ser asi, se
    ! reinicia el Timer (podria estar desprogramado) para continuar el Fade
    RecuperarFade [ ;
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { return; }
      !-------------------------------------------------------------------------
      ! hay en proceso algun trabajo de Fade? Si no: no hacemos nada mas
      if (~~self.EnFade()) { return; }
      !-------------------------------------------------------------------------
      ! SI EL CANAL EN FADE ESTA 'SONANDO DE FONDO' ACTUALMENTE...
      if (self.&est_cnl-->(self.cnl_fade) == 1) {
        glk_request_timer_events(self.tick_fade); ! reiniciamos el Timer
      }
      else { ! SI EL CANAL EN FADE NO ESTA 'SONANDO DE FONDO' ACTUALMENTE...
        self.AbortarFade(); ! acabamos con el efecto de Fade totalmente!!
      }
    ],

    ! Hace efecto de Fade (1==FadeIn o 2==FadeOut) [es llamada por NotificarFade()]
    HacerFade [ ;
      ! que tipo de Fade? (segun tipo: subimos/bajamos porcentaje de volumen)
      switch (self.que_fade) {
        1: ! en FadeIn
           self.&vol_fade-->0 = (self.&vol_fade-->0)+1; ! subimos 1 unidad vol.
           !--------------------------------------------------------------------
           ! mientras 'volumen inicial' sea menor o igual al 'volumen final'
           if ((self.&vol_fade-->0) <= (self.&vol_fade-->1)) {
             ! cambiamos % de volumen que corresponde en este 'tick' del Timer
             self.VolumenCanal(self.cnl_fade, self.&vol_fade-->0);
             !------------------------------------------------------------------
             ! si llegamos al 'volumen final', es momento de terminar el Fade
             if ((self.&vol_fade-->0) >= (self.&vol_fade-->1)) {
               self.AbortarFade(); ! abortamos el efecto de Fade
               return; ! y terminamos aqui
             }
           }

        2: ! en FadeOut
           self.&vol_fade-->0 = (self.&vol_fade-->0)-1; ! bajamos 1 unidad vol.
           !--------------------------------------------------------------------
           ! mientras 'volumen inicial' sea mayor o igual al 'volumen final'
           if ((self.&vol_fade-->0) >= (self.&vol_fade-->1)) {
             ! cambiamos % de volumen que corresponde en este 'tick' del Timer
             self.VolumenCanal(self.cnl_fade, self.&vol_fade-->0);
             !------------------------------------------------------------------
             ! si llegamos al 'volumen final', es momento de terminar el Fade
             if ((self.&vol_fade-->0) <= (self.&vol_fade-->1)) {
               self.AbortarFade(); ! abortamos el efecto de Fade
               !----------------------------------------------------------------
               ! ademas, si tenemos un sonido post-fadeout lo tocamos
               if (self.snd_pfadeout ~= 0) {
                 ! tocamos el sonido y si tiene que notificar eventos lo hacemos constar
                 self.Tocar(self.&snd_pfadeout-->0, self.&snd_pfadeout-->1);
               }
               !----------------------------------------------------------------
               return; ! y terminamos aqui
             }
           }
      }
    ],

    ! Comprueba si el interprete tiene soporte completo de audio; si no lo tiene,
    ! activa el valor del flag 'glk_sin_audio' para reportarlo al kernel de Damusix
    GlkAudio [
      aux; ! se deben mostrar avisos textuales (1==si, 0==no)
      ! Comprobamos si interprete tiene SOPORTE COMPLETO de audio y avisamos al Kernel
      if (self.TestAudio()) { self.glk_sin_audio = false; } ! tiene soporte completo
      else { self.glk_sin_audio = true; } ! no tiene soporte completo de audio
      !-------------------------------------------------------------------------
      #ifdef DEBUG;
        ! si el audio no esta soportado, avisa de la situacion
        if ((aux==1) && (self.glk_sin_audio)) {
          glk_set_style(style_Preformatted);
          new_line;
          print (string) ERROR_GLK_NO_FULL_AUDIO; ! mensaje de aviso
          new_line;
          glk_set_style(style_Normal);
        }
      #endif; ! DEBUG
      !-------------------------------------------------------------------------
      aux = aux; ! simplemente para evitar un warning del compilador
    ],

  !=============================================================================
  !-----------------------------------------------------------------------------
  ! *** INICIALIZAR DAMUSIX (EL PROGRAMADOR JAMAS DEBE LLAMAR A ESTA RUTINA)***
  !-----------------------------------------------------------------------------
  !=============================================================================
  with
    ! [AUX. KERNEL] INICIALIZA EL GESTOR DE AUDIO DE DAMUSIX Y TODOS SUS CANALES
    ! (NORMALES/VIRTUALES) *NOTA: EL PROGRAMADOR JAMAS DEBE LLAMAR A ESTA RUTINA
    InicializarGlk [
      i;  ! para iteraciones
      !-------------------------------------------------------------------------
      ! si el audio no esta soportado, no se hace nada mas...
      self.GlkAudio(1); if (self.glk_sin_audio) { return; } ! (1==mostrar avisos)
      !-------------------------------------------------------------------------
      ! MUY IMPORTANTE: BORRAMOS COMPLETAMENTE EL REGISTRO DEL ESTADO PIB...
      ! [esto es vital para obtener un inicio de juego limpio en un 'RESTART']
      #ifndef DAMUSIX_NO_PROTEGER_SONIDOS;
      for (i=0 : i<=DAMUSIX_NCANALMAX : i=i+1) { self.&pib_reg-->i = 0; }
      #endif; ! DAMUSIX_NO_PROTEGER_SONIDOS
      !-------------------------------------------------------------------------
      ! creamos los canales normales, efectivamente, en array Damusix.gg_ncnl
      for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) {
        ! solo si el canal no existe tiene sentido crearlo
        if (self.&gg_ncnl-->i == 0) {
          ! rock_inicial+i = rocks para canales 'normales'
          self.&gg_ncnl-->i = glk_schannel_create(DAMUSIX_GG_ROCK+i); ! 510+i
        }
      }
      !-------------------------------------------------------------------------
      ! creamos los canales virtuales, efectivamente, en array Damusix.gg_vcnl
      for (i=0 : i<DAMUSIX_VCANALMAX : i=i+1) {
        ! solo si el canal no existe tiene sentido crearlo
        if (self.&gg_vcnl-->i == 0) {
          ! rock_inicial+canales_normales+i = rocks para canales 'virtuales'
          self.&gg_vcnl-->i = glk_schannel_create(DAMUSIX_GG_ROCK+DAMUSIX_NCANALMAX+i);
        }
      }
      !-------------------------------------------------------------------------
      ! creamos el canal para la 'lista de reproduccion de sonidos' en gg_lcnl
        if (self.gg_lcnl == 0) { ! solo si el canal no existe tiene sentido crearlo
          ! rock_inicial+canales_normales+canales_virtuales = rock para canal 'lista de reprod.'
          self.gg_lcnl = glk_schannel_create(DAMUSIX_GG_ROCK+DAMUSIX_NCANALMAX+DAMUSIX_VCANALMAX);
        }
    ],

  !=============================================================================
  !-----------------------------------------------------------------------------
  ! *** RUTINAS GANCHO DE DAMUSIX RELACIONADAS CON LOS PUNTOS DE ENTRADA GLK ***
  !-----------------------------------------------------------------------------
  !=============================================================================

    ! IDENTIFICA LOS OBJETOS GLK QUE SON SONIDOS [para IdentifyGlkObject()]
    IdentificarSonidos [ fase ! la fase actual
      id i; ! id: el canal identificado; i: para iteraciones
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si el audio no esta soportado, no se hace nada mas...
      self.GlkAudio(0); if (self.glk_sin_audio) { return; } ! (0==no mostrar avisos)
      !=========================================================================
      ! MUY IMPORTANTE: PROTEGEMOS AREA DE MEMORIA DEL REGISTRO DEL ESTADO PIB
      !-------------------------------------------------------------------------
        #ifndef DAMUSIX_NO_PROTEGER_SONIDOS;
        i = self.&pib_reg;  ! usamos variable local 'i' solo por comodidad
        id = self.#pib_reg; ! usamos variable local 'id' solo por comodidad
        @protect i id;      ! ahora invocamos la proteccion del registro (asm)
        #endif; ! DAMUSIX_NO_PROTEGER_SONIDOS
      !=========================================================================
      ! FASE 0: Elimina las referencias a los canales de sonido (objetos gg_*)
      ! [las pone todas a cero]
      if (fase == 0) {
        !-----------------------------------------------------------------------
        ! NOTA: 'DAMUSIX_NCANALMAX' Y 'DAMUSIX_VCANALMAX' SON ABSOLUTAMENTE
        ! NECESARIOS PARA RECORRER TODOS LOS CANALES, NO IMPORTA SI NO SE HAN
        ! CREADO EFECTIVAMENTE TODOS (SI NO, NO ELIMINA BIEN SUS REFERENCIAS)
        !-----------------------------------------------------------------------
        ! recorre todos los canales 'normales' creados y borra sus referencias
        for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) { self.&gg_ncnl-->i = 0; }
        ! recorre todos los canales 'virtuales' creados y borra sus referencias
        for (i=0 : i<DAMUSIX_VCANALMAX : i=i+1) { self.&gg_vcnl-->i = 0; }
        ! borra la referencia del canal para la 'lista de reprod. de sonidos'
        self.gg_lcnl = 0;
        ! y retornamos porque no hay nada mas que hacer aqui
        return;
      }
      !
      !=========================================================================
      ! OBSERVACION: Damusix no utiliza la FASE 1 porque no es necesaria
      !              para las funciones de audio en Inform-Glulx.
      !=========================================================================
      !
      !-------------------------------------------------------------------------
      ! FASE 2: Se inicializan los objetos gg_* que apuntan a los canales de
      ! sonido (afecta a 'gg_ncnl', 'gg_vcnl' y 'gg_lcnl')
      if (fase == 2) {
        ! itera en los canales de sonido para identificar
        ! el primer objeto de sonido y guarda su referencia
        ! en el array de la libreria Inform 'gg_arguments'
        id = glk_schannel_iterate(0, gg_arguments);
        ! ahora comienza la busqueda efectiva y la asignacion de
        ! referencias actuales a cada uno de los distintos canales
        while (id) {
          !---------------------------------------------------------------------
          ! NOTA: 'DAMUSIX_NCANALMAX' Y 'DAMUSIX_VCANALMAX' SON ABSOLUTAMENTE
          ! NECESARIOS PARA RECORRER TODOS LOS CANALES, NO IMPORTA SI NO SE HAN
          ! CREADO EFECTIVAMENTE TODOS (SI NO, NO RECUPERA BIEN SUS REFERENCIAS)
          !---------------------------------------------------------------------
          ! si son los canales 'normales' de Damusix, asigna sus referencias
          !---------------------------------------------------------------------
          for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) {
            ! rock_inicial+i = rocks para canales 'normales'
            if (gg_arguments-->0 == DAMUSIX_GG_ROCK+i) { ! 510+i
              self.&gg_ncnl-->i = id;
            }
          }
          !---------------------------------------------------------------------
          ! si son los canales 'virtuales' de Damusix, asigna sus referencias
          !---------------------------------------------------------------------
          for (i=0 : i<DAMUSIX_VCANALMAX : i=i+1) {
            ! rock_inicial+canales_normales+i = rocks para canales 'virtuales'
            if (gg_arguments-->0 == DAMUSIX_GG_ROCK+DAMUSIX_NCANALMAX+i) {
              self.&gg_vcnl-->i = id;
            }
          }
          !---------------------------------------------------------------------
          ! si es canal para 'lista de reprod.' de Damusix, asigna su referencia
          !---------------------------------------------------------------------
          ! rock_inicial+canales_normales+canales_virtuales = rock para canal 'lista de reprod.'
          if (gg_arguments-->0 == DAMUSIX_GG_ROCK+DAMUSIX_NCANALMAX+DAMUSIX_VCANALMAX) {
            self.gg_lcnl = id;
          }
          ! volver a iterar para encontrar mas objetos de sonido
          id = glk_schannel_iterate(id, gg_arguments);
        }
        !-----------------------------------------------------------------------
        ! == FINALMENTE ==
        ! IMPORTANTE: SI NO SE USAN LAS SIGUIENTES RUTINAS, LOS SONIDOS DE
        ! LOS CANALES USADOS POR DAMUSIX SEGUIRAN REPRODUCIENDOSE SIN CONTROL
        !-----------------------------------------------------------------------
        ! actualiza el estado de todos canales normales de sonido (reprod., detener, etc.)
        self.ActualizarCanales(1); ! IMPORTANTE: 1==arg.osc. [ver NOTA en ActualizarPIB()]
        ! detiene reproduccion en todos los canales virtuales y en el canal de la 'lista'
        self.PararCanalesExtra();
        ! comprobamos si en el "nuevo-estado-del-juego" existe un efecto de Fade activo
        self.RecuperarFade(); ! en tal caso, timer sera reiniciado, recuperando el Fade
        ! y retornamos porque ya no hay nada mas que hacer aqui...
        return;
      }
    ],

    ! IMPLEMENTA LO NECESARIO EN HandleGlkEvent() PARA HACER LOS FADES EN "TIEMPO-REAL"
    NotificarFade [ ev; ! el evento capturado
      if (ev-->0 == evtype_Timer) { ! si es un 'tick' del Timer
        if (self.EnFade()) { self.HacerFade(); } ! si hay Fade activo, hacemos el efecto
      }
    ],

  !=============================================================================
  !-----------------------------------------------------------------------------
  ! ** RUTINAS 'NO TECNICAS' RELACIONADAS CON LA REPROD. DE AUDIO DE DAMUSIX **
  !-----------------------------------------------------------------------------
  !=============================================================================

    ! Asigna sonido, porcentaje de volumen y modo de repeticion a un canal especifico
    AsignarCanal [ snd nc vol rep; ! snd: sonido; nc: canal; vol: volumen [-1==Global]; rep: repet.
      ! si el sonido no existe o tiene valor incorrecto, no puede ser asigando
      if (snd < 1) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! si el volumen es menor a 0% o mayor a 100%, lo deja en el valor del volumen global
      if ((vol < 0) || (vol > 100)) { vol = self.vol_global; }
      ! si la cantidad de repeticiones es 0 o es menor a -1, la deja en 1 rep.
      if ((rep == 0) || (rep < -1)) { rep = 1; }
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si esta en proceso un trabajo de Fade a un sonido cuyo
      ! canal es el mismo con el que vamos a trabajar en este momento
        if (self.cnl_fade == nc) { self.AbortarFade(); } ! abortamos el Fade
      !-------------------------------------------------------------------------
      ! asigna el sonido al canal indicado (si nc==0, se asume canal 0)
      self.&snd_cnl-->nc = snd;
      ! asigna el porcentaje de volumen del canal
      self.&vol_cnl-->nc = vol;
      ! asigna el modo de repeticion del canal
      self.&rep_cnl-->nc = rep;
      ! pone el estado de reproduccion del canal en cero (detenido)
      self.&est_cnl-->nc = 0;
      ! finalmente actualiza el canal
      self.ActualizarCanal(nc);
    ],

    ! Libera la asignacion de un sonido a un canal especifico
    LiberarCanal [ snd ! snd: el sonido
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si esta en proceso un trabajo de Fade a un sonido cuyo
      ! canal es el mismo con el que vamos a trabajar en este momento
        if (self.cnl_fade == nc) { self.AbortarFade(); } ! abortamos el Fade
      !-------------------------------------------------------------------------
      ! libera el sonido asignado al canal indicado (con valor cero)
      self.&snd_cnl-->nc = 0;
      ! limpia el porcentaje de volumen del canal
      self.&vol_cnl-->nc = 0;
      ! limpia el modo de repeticion del canal
      self.&rep_cnl-->nc = 0;
      ! pone el estado de reproduccion del canal en cero (detenido)
      self.&est_cnl-->nc = 0;
      ! finalmente actualiza el canal
      self.ActualizarCanal(nc);
    ],

    ! Activa la salida de audio de Damusix
    ActivarAudio [ ;
      ! activa el modo bullicioso
      self.audio_activado = true;
      ! actualiza el estado de todos canales normales de sonido
      self.ActualizarCanales();
    ],

    ! Desactiva la salida de audio de Damusix
    DesactivarAudio [ ;
      ! activa el modo silencioso
      self.audio_activado = false;
      ! actualiza el estado de todos canales normales de sonido
      self.ActualizarCanales();
      ! detiene reproduccion en todos los canales virtuales y en canal de la 'lista'
      self.PararCanalesExtra();
    ],

    ! Reproduce el sonido previamente asignado a un canal
    Tocar [ snd esn ! snd: el sonido a tocar; esn (1=='generar eventos SoundNotify')
      nc; ! variable auxiliar (numero de canal)
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si esta en proceso un trabajo de Fade a un sonido cuyo
      ! canal es el mismo con el que vamos a trabajar en este momento
        if (self.cnl_fade == nc) { self.AbortarFade(); } ! abortamos el Fade
      !-------------------------------------------------------------------------
      ! pone el estado de reproduccion en uno (reproduciendo)
      self.&est_cnl-->nc = 1;
      ! finalmente actualiza el canal
      self.ActualizarCanal(nc, esn); ! llamado con arg. oscuro 'esn' (si es 1, notificar)
    ],

    ! Detiene el sonido previamente asignado a un canal
    Parar [ snd ! snd: el sonido a parar
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si esta en proceso un trabajo de Fade a un sonido cuyo
      ! canal es el mismo con el que vamos a trabajar en este momento
        if (self.cnl_fade == nc) { self.AbortarFade(); } ! abortamos el Fade
      !-------------------------------------------------------------------------
      ! pone el estado de reproduccion en cero (detenido)
      self.&est_cnl-->nc = 0;
      ! finalmente actualiza el canal
      self.ActualizarCanal(nc);
    ],

    ! Reproduce un sonido en alguno de los canales virtuales
    TocarV [ snd vol; ! snd: sonido; vol: porcent. de volumen (por omision Vol.Comun, -1==Global)
      ! si el sonido no existe o tiene valor incorrecto, no puede ser reprod. 'virtualmente'
      if (snd < 1) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      ! si la salida de audio esta desactivada, no se hace nada mas
      if (~~self.audio_activado) { return; }
      ! si el volumen es menor a 1% o mayor a 100%, hay que corregir su valor...
      if ((vol < 1) || (vol > 100)) {
        if (vol == -1) { vol = self.vol_global; } ! si vale -1 usamos Vol.Global, si no...
        else { vol = self.vol_vcnl; } ! usamos Vol.Comun actual para canales 'virtuales'
      }
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        glk_schannel_set_volume(self.&gg_vcnl-->self.que_vcnl, vol * DAMUSIX_VOLMAX);
      }
      ! y ahora tocamos el sonido efectivamente (en alguno de los canales virtuales)
      ! [NOTA: sonido solo tocara 1 vez y no generara ningun evento de notificacion]
      glk_schannel_play_ext(self.&gg_vcnl-->self.que_vcnl, snd, 1, 0);
      !-------------------------------------------------------------------------
      ! IMPORTANTE: incrementamos el numero de la variable que indica cual
      ! de todos los canales virtuales se usara para la siguiente reproduccion
      self.que_vcnl++;
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si llegamos al ultimo canal virtual de la lista, regresamos  y...
      if (self.que_vcnl > DAMUSIX_VCANALMAX-1) { self.que_vcnl = 0; } ! usamos el 1ro
    ],

    ! Crea la 'lista de reprod. de sonidos', agregando un sonido y su tiempo de duracion
    CrearLista [ snd ms ! snd: el sonido; ms: milisegundos que dura el sonido (para espera)
      i; ! para iteraciones
      ! si el sonido no existe o tiene valor incorrecto, no puede ser agregado a la lista
      if (snd < 1) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! si la cantidad de milisegundos es menor a 1, la deja en 1000ms (1 segundo)
      if (ms < 1) { ms = 1000; }
      ! ahora 'construimos' la lista de reproduccion de sonidos
      for (i=0 : i<(DAMUSIX_SNDLSTMAX*2) : i=i+2) { ! recorremos cada una de las filas de la lista
        if (self.&snd_lst-->i == 0) {  ! siempre que exista una fila disponible ('1er slot'==0)
          self.&snd_lst-->i = snd;     ! se agrega el sonido concreto... (en 1er slot)
          self.&snd_lst-->(i+1) = ms;  ! ... su tiempo de duracion... (en 2do slot)
          return;                      ! y terminamos aqui
        }
      }
      !-------------------------------------------------------------------------
      #ifdef DEBUG;
        ! si la lista de reproduccion de sonidos ya no tiene slots libres
        ! (se ha llenado) se debe lanzar un aviso de error en el modo DEBUG
        glk_set_style(style_Preformatted);
        new_line;
        print (string) ERROR_LISTA_REPROD_LLENA; ! mensaje de aviso
        new_line;
        glk_set_style(style_Normal);
      #endif; ! DEBUG
      !-------------------------------------------------------------------------
    ],

    ! Limpia la 'lista de reproduccion de sonidos', eliminando todo su contenido
    LimpiarLista [
      i; ! para iteraciones
      ! recorremos la lista completa y ponemos a cero cada uno de sus slots
      for (i=0 : i<(DAMUSIX_SNDLSTMAX*2) : i=i+1) { self.&snd_lst-->i = 0; }
    ],

    ! Reproduce el contenido previamente agregado a la 'lista de reprod. de sonidos'
    TocarLista [ vol ! vol: porcentaje de volumen (por omision Vol.Comun, -1==Global)
      i; ! para iteraciones
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { jump Damusix_TocarListaFin; }
      ! si la salida de audio esta desactivada, no se hace nada mas
      if (~~self.audio_activado) { jump Damusix_TocarListaFin; }
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { jump Damusix_TocarListaFin; }
      !-------------------------------------------------------------------------
      ! si ya esta en proceso un trabajo de Fade, no se permite tocar la 'lista'
      if (self.EnFade()) {
        #ifdef DEBUG;
          glk_set_style(style_Preformatted);
          new_line;
          print (string) ERROR_TOCAR_LISTA_DURANTE_FADE; ! mensaje de aviso
          new_line;
          glk_set_style(style_Normal);
        #endif; ! DEBUG
        jump Damusix_TocarListaFin;
      }
      !-------------------------------------------------------------------------
      ! si el volumen es menor a 1% o mayor a 100%, hay que corregir su valor...
      if ((vol < 1) || (vol > 100)) {
        if (vol == -1) { vol = self.vol_global; } ! si vale -1 usamos Vol.Global, si no...
        else { vol = self.vol_lcnl; } ! usamos Vol.Comun actual para 'lista de reproduccion'
      }
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        glk_schannel_set_volume(self.gg_lcnl, vol * DAMUSIX_VOLMAX);
      }
      ! ahora comenzamos a tocar los sonidos de la 'lista de reprod.' en orden, uno a uno
      for (i=0 : i<(DAMUSIX_SNDLSTMAX*2) : i=i+2) { ! recorremos cada una de las filas de la lista
        if (self.&snd_lst-->i ~= 0) { ! siempre que la fila actual no este vacia ('1er slot'~=0)
          glk_schannel_play_ext(self.gg_lcnl, self.&snd_lst-->i, 1, 0); ! tocamos el sonido
          self.HacerPausa(self.&snd_lst-->(i+1));                       ! hacemos la pausa
        }
      }
      !-------------------------------------------------------------------------
      .Damusix_TocarListaFin; ! ETIQUETA ESPECIAL PARA SITUACIONES DE ERROR
      !-------------------------------------------------------------------------
      ! finalmente limpiamos toda la lista de reprod. de sonidos (slots a cero)
      self.LimpiarLista();
    ],

    ! Establece el modo de repeticion de un sonido (cuantas veces se tocara)
    Repeticion [ snd rep ! snd: el sonido; rep: el numero de repeticiones
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! si la cantidad de repeticiones es 0 o es menor a -1, la deja en 1 rep.
      if ((rep == 0) || (rep < -1)) { rep = 1; }
      ! establece el modo de repeticion del canal especificado
      self.&rep_cnl-->nc = rep;
    ],

    ! Establece el volumen de un sonido
    Volumen [ snd vol ! snd: el sonido; vol: porcentaje de volumen [-1==Vol.Global]
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! si el volumen es menor a 0% o mayor a 100%, lo deja en el valor del volumen global
      if ((vol < 0) || (vol > 100)) { vol = self.vol_global; }
      ! establece el volumen del canal especificado
      self.&vol_cnl-->nc = vol;
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      !-------------------------------------------------------------------------
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        ! finalmente actualiza el volumen
        glk_schannel_set_volume(self.&gg_ncnl-->nc, self.&vol_cnl-->nc * DAMUSIX_VOLMAX);
      }
    ],

    ! Establece el volumen comun para todos los canales 'virtuales'
    VolumenV [ vol ! vol: porcentaje de volumen [-1==Vol.Global]
      i; ! para iteraciones
      ! si el volumen es menor a 0% o mayor a 100%, lo deja en el valor del volumen global
      if ((vol < 0) || (vol > 100)) { vol = self.vol_global; }
      ! recuerda el nuevo volumen comun para los canales 'virtuales'
      self.vol_vcnl = vol;
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      !-------------------------------------------------------------------------
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        ! finalmente actualiza el volumen
        for (i=0 : i<DAMUSIX_VCANALMAX : i=i+1) {
          glk_schannel_set_volume(self.&gg_vcnl-->i, self.vol_vcnl * DAMUSIX_VOLMAX);
        }
      }
    ],

    ! Establece el volumen comun para la 'lista de reproduccion de sonidos'
    VolumenLista [ vol; ! vol: porcentaje de volumen [-1==Vol.Global]
      ! si el volumen es menor a 0% o mayor a 100%, lo deja en el valor del volumen global
      if ((vol < 0) || (vol > 100)) { vol = self.vol_global; }
      ! recuerda el nuevo volumen comun para la 'lista de reproduccion'
      self.vol_lcnl = vol;
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      !-------------------------------------------------------------------------
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        ! finalmente actualiza el volumen
        glk_schannel_set_volume(self.gg_lcnl, self.vol_lcnl * DAMUSIX_VOLMAX);
      }
    ],

    ! Establece el volumen global para todos los sonidos gestionados por Damusix
    VolumenGlobal [ vol ! el porcentaje de volumen global
      i; ! para iteraciones
      ! si el volumen es menor a 0% o mayor a 100%, lo deja justo en 100%
      if ((vol < 0) || (vol > 100)) { vol = 100; }
      ! recuerda el nuevo valor de volumen global
      self.vol_global = vol;
      !-------------------------------------------------------------------------
      ! NOTA: aqui no comprobamos si la Glk soporta sonido o si la salida de
      ! audio esta activada, porque ya lo hacen las propias rutinas de abajo
      !-------------------------------------------------------------------------
      ! actualizamos todos los canales de sonido 'normales' con su nuevo volumen
      for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) { self.VolumenCanal(i, self.vol_global); }
      ! actualizamos todos los canales de sonido 'virtuales' con su nuevo volumen
      self.VolumenV(self.vol_global);
      ! finalmente actualizamos el canal de la 'lista de reprod.' con su nuevo volumen
      self.VolumenLista(self.vol_global);
    ],

    ! Hace FadeIn a un sonido en "tiempo-real"
    FadeIn [ snd ms volfinal ! snd: sonido; ms: duracion; volfinal: vol. final
      nc; ! variable auxiliar (numero de canal)
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { return; }
      !-------------------------------------------------------------------------
      ! si ya esta en proceso un trabajo de Fade, no se permite lanzar otro
      if (self.EnFade()) {
        #ifdef DEBUG;
          glk_set_style(style_Preformatted);
          new_line;
          print (string) ERROR_HACER_FADE_DURANTE_FADE; ! mensaje de aviso
          new_line;
          glk_set_style(style_Normal);
        #endif; ! DEBUG
        return;
      }
      !-------------------------------------------------------------------------
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! si Vol.Final es menor a 1% o mayor a 100%, fijar valor segun Vol.Global
      if ((volfinal < 1) || (volfinal > 100)) { volfinal = self.vol_global; }
      !-------------------------------------------------------------------------
      ! *** COMPROB. DE SEGURIDAD: EVITAR DIV. POR CERO EN CODIGO POSTERIOR ***
      ! SI EL VOLUMEN ACTUAL DEL CANAL ES IGUAL O SUPERIOR A VOLUMEN GLOBAL,
      ! ENTONCES ESTA AL MAXIMO Y NO ES NECESARIO REALIZAR EFECTO DE FadeIn
      ! EN 'TIEMPO-REAL' [ADEMAS EVITA UN POTENCIAL BUG (DIVISION POR CERO)]
      if (self.QueVolumenCanal(nc) >= volfinal) { return; } ! **terminar aqui!!
      !-------------------------------------------------------------------------
      ! ajusta el modo de Fade (FadeIn==1)
      self.que_fade = 1;
      ! recuerda el canal asignado al sonido al que se le va a hacer Fade
      self.cnl_fade = nc;
      ! hacemos una copia del volumen inicial
      self.&vol_fade-->0 = self.QueVolumenCanal(nc);
      ! hacemos una copia del volumen final
      self.&vol_fade-->1 = volfinal;
      ! si duracion en msegs. es menor a 100, la deja en 100ms (1ms * 1% vol.)
      if (ms < 100) { ms = 100; }
      ! calculamos tiempo de cada 'tick' y lo recordamos (truco UNDO/RESTORE/RESTART)
      self.tick_fade = ms / ((self.&vol_fade-->1) - (self.&vol_fade-->0));
      ! finalmente activamos el timer para que comience el Fade de "tiempo-real"
      glk_request_timer_events(self.tick_fade);
    ],

    ! Hace FadeOut a un sonido en "tiempo-real"
    FadeOut [ snd ms volfinal sndpfo sndpesn ! snd: sonido; ms: duracion; volfinal: vol. final
      ! sndpfo: sonido Post-FadeOut; sndpesn: (1=='generar SoundNotify' el sonido Post-FadeOut)
      nc; ! variable auxiliar (numero de canal)
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { return; }
      !-------------------------------------------------------------------------
      ! si ya esta en proceso un trabajo de Fade, no se permite lanzar otro
      if (self.EnFade()) {
        #ifdef DEBUG;
          glk_set_style(style_Preformatted);
          new_line;
          print (string) ERROR_HACER_FADE_DURANTE_FADE; ! mensaje de aviso
          new_line;
          glk_set_style(style_Normal);
        #endif; ! DEBUG
        return;
      }
      !-------------------------------------------------------------------------
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! si Vol.Final es menor a 1% o mayor a 100%, fijar 0% de volumen (minimo)
      if ((volfinal < 1) || (volfinal > 100)) { volfinal = 0; } ! vol. minimo
      !-------------------------------------------------------------------------
      ! *** COMPROB. DE SEGURIDAD: EVITAR DIV. POR CERO EN CODIGO POSTERIOR ***
      ! SI EL VOLUMEN ACTUAL DEL CANAL ES MENOR O IGUAL 0%, ENTONCES ESTA AL
      ! MINIMO Y NO ES NECESARIO REALIZAR EFECTO DE FadeOut EN 'TIEMPO-REAL'
      ! [ADEMAS EVITA UN POTENCIAL BUG (DIVISION POR CERO)]
      if (self.QueVolumenCanal(nc) <= volfinal) { return; } ! **terminar aqui!!
      !-------------------------------------------------------------------------
      ! ajusta el modo de Fade (FadeOut==2)
      self.que_fade = 2;
      ! recuerda el canal asignado al sonido al que se le va a hacer Fade
      self.cnl_fade = nc;
      ! hacemos una copia del volumen inicial
      self.&vol_fade-->0 = self.QueVolumenCanal(nc);
      ! hacemos una copia del volumen final
      self.&vol_fade-->1 = volfinal;
      ! guardamos una copia del volumen inicial como 'volumen original'
      self.&vol_fade-->2 = self.&vol_fade-->0;
      ! si duracion en msegs. es menor a 100, la deja en 100ms (1ms * 1% vol.)
      if (ms < 100) { ms = 100; }
      ! si 'volumen final' no es cero, entonces NO DEBE USARSE sonido post-fadeout
      if (self.&vol_fade-->1 ~= 0) { sndpfo = 0; sndpesn = 0; }
      ! guardamos el sonido post-fadeout (si es cero, es que no hay sonido posterior)
      ! y si ese sonido debe notificar eventos cuando termine de reproducirse
      self.&snd_pfadeout-->0 = sndpfo;
      self.&snd_pfadeout-->1 = sndpesn;
      ! calculamos tiempo de cada 'tick' y lo recordamos (truco UNDO/RESTORE/RESTART)
      self.tick_fade = ms / ((self.&vol_fade-->0) - (self.&vol_fade-->1));
      ! finalmente activamos el timer para que comience el Fade de "tiempo-real"
      glk_request_timer_events(self.tick_fade);
    ],

    ! Aborta cualquier efecto de Fade en "tiempo-real" que pudiera estar en proceso
    !---------------------------------------------------------------------------
    ! [IMPORTANTE: esta rutina detendra los 'ticks' del Timer SOLAMENTE cuando
    ! este EN PROCESO un efecto de Fade. Debido a limitaciones de la Glk, se
    ! sabe que AbortarFade() no detendra los 'ticks' correctamente ante un
    ! comando RESTART o RESTORE/UNDO (si se carga una posicion en la cual no
    ! existia ningun efecto de Fade en proceso). Esta simple 'irregularidad'
    ! en el comportamiento de la rutina puede corregirse con un breve truco,
    ! pero se ha decido no hacerlo, porque la correccion podria traer 'efectos
    ! colaterales' en el codigo ajeno a Damusix implementado por el programador
    ! (la solucion es detener el Timer SIEMPRE, pero... ¿y si el juego lo esta
    ! usando para una funcion propia? Mejor NO DETENERLO injustificadamente)
    ! A pesar de todo, AbortarFade() SIEMPRE DETIENE CORRECTAMENTE los Fades
    ! activos, incluso si el Timer sige produciendo 'ticks' sin control]
    AbortarFade [
      nc; ! variable auxiliar (numero de canal)
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { return; }
      !-------------------------------------------------------------------------
      ! hay en proceso algun trabajo de Fade? Si no: no hacemos nada mas
      if (~~self.EnFade()) { return; }
      !-------------------------------------------------------------------------
      glk_request_timer_events(0); ! detenemos los 'ticks' del Timer...
      self.tick_fade = 0;          ! y borramos el calculo de 'ticks' guardado
      !-------------------------------------------------------------------------
      ! recordamos temporalmente el numero del canal en Fade (se usa mas abajo)
      ! [IMPORTANTE: asi evitamos una llamada recursiva perpetua en PararCanal()]
      nc = self.cnl_fade;
      ! reseteamos ahora la variable que guardaba el numero del canal en Fade
      self.cnl_fade = -1; ! -1=='sin canal' (no hay canal en Fade)
      !-------------------------------------------------------------------------
      ! si es FadeOut, adicionalmente paramos el canal que estaba en Fade
      ! si su volumen actual ha llegado al % minimo (0%) luego del efecto
      if ((self.que_fade == 2) && (self.&vol_fade-->1 <= 0)) {
        self.PararCanal(nc); ! detenemos la reproduccion del canal y...
        ! aprovechamos de hacer un truquito para que se recupere volumen...
        self.&vol_fade-->1 = self.&vol_fade-->2; ! original antes del FadeOut
      }
      !-------------------------------------------------------------------------
      ! establecemos ahora el volumen final para el sonido que estaba en Fade
      self.VolumenCanal(nc,self.&vol_fade-->1); ! usamos copia del Vol.Final
      ! limpiamos la copia del volumen inicial
      self.&vol_fade-->0 = 0;
      ! limpiamos la copia del volumen final
      self.&vol_fade-->1 = 0;
      ! borramos la copia del 'volumen original'...
      self.&vol_fade-->2 = 0; ! ... solo usada en FadeOut
      ! y finalmente ponemos el modo de Fade en cero (sin Fades)
      self.que_fade = 0;
    ],

    ! Hace FadeIn a un sonido en "tiempo-no-real" (devuelve control al finalizar efecto)
    SimpleFadeIn [ snd ms volfinal ! snd: sonido; ms: duracion; volfinal: vol. final
      nc vol i; ! nc: aux. (num. canal); vol: aux. (vol. inicial) i: para iteraciones
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { return; }
      !-------------------------------------------------------------------------
      ! si ya esta en proceso un trabajo de Fade, no se permite lanzar otro
      if (self.EnFade()) {
        #ifdef DEBUG;
          glk_set_style(style_Preformatted);
          new_line;
          print (string) ERROR_HACER_FADE_DURANTE_FADE; ! mensaje de aviso
          new_line;
          glk_set_style(style_Normal);
        #endif; ! DEBUG
        return;
      }
      !-------------------------------------------------------------------------
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! si Vol.Final es menor a 1% o mayor a 100%, fijar valor segun Vol.Global
      if ((volfinal < 1) || (volfinal > 100)) { volfinal = self.vol_global; }
      !-------------------------------------------------------------------------
      ! si duracion en msegs. es menor a 1, la deja en 100ms (1ms * 1% volumen)
      if (ms < 1) { ms = 100; }
      !-------------------------------------------------------------------------
      ! averiguamos vol. actual del sonido y lo recordamos como 'vol. inicial'
      vol = self.QueVolumenCanal(nc);
      !-------------------------------------------------------------------------
      ! == NOTA: ELECCION DEL ALGORITMO ==
      ! El volumen en Damusix siempre se mide en porcentajes, con un maximo de
      ! 100%. Por lo tanto, el tiempo de duracion para un Fade debe ser de al
      ! menos 100ms (porque se cambia 1% por cada 1ms). En este primer caso,
      ! se utilizara un 'algoritmo sencillo' que simplemente cambia 1 unidad
      ! de volumen en cada iteracion y luego realiza una espera calculada. Por
      ! el contrario, si el tiempo de duracion para el Fade es menor a 100ms,
      ! entonces debera utilizarse un 'algoritmo complejo' que hace justamente
      ! lo contrario al anterior: cambia X unidades de volumen calculadas segun
      ! un nuevo maximo de volumen, luego espera 1ms y todo el proceso se repite
      ! tantas veces como msegs. de duracion deba tener el efecto de Fade.
      !-------------------------------------------------------------------------
      ! ALGORITMO SENCILLO
      !-------------------------------------------------------------------------
      if (ms >= 100) {
        ! Se va a subir volumen poco a poco desde 'vol.inicial' hasta 'vol.final'
        ! NOTA: 'vol+1' hace que la iteracion comience en % de volumen directamente
        ! superior al % de 'vol.inicial': asi no se itera 2 veces con el mismo valor
        for (i=vol+1 : i<=volfinal : i=i+1) {
          ! cambiamos en 1 unidad el porcentaje de volumen
          self.VolumenCanal(nc, i);
          !---------------------------------------------------------------------
          ! finalmente hacemos una pausa durante un 'intervalo de tiempo' que se
          ! calcula segun la duracion total especificada para el efecto de Fade.
          ! Nunca hay division por cero, porque 'vol' no llega a valer 'volfinal';
          ! es la propia comprobacion inicial del bucle 'for' la que se encarga de
          self.HacerPausa(ms/(volfinal-vol)); ! evitar un posible error de calculo
        }
      }
      !-------------------------------------------------------------------------
      ! ALGORITMO COMPLEJO
      !-------------------------------------------------------------------------
      else {
        ! si el volumen actual del sonido al que se le va a hacer el efecto
        ! de Fade es mayor o igual que el 'volumen final', terminamos la
        ! rutina porque el efecto es totalmente inaplicable en este caso...
        if (vol >= volfinal) { return; } ! terminamos aqui sin hacer nada mas
        !-----------------------------------------------------------------------
        ! iteramos tantas veces como numero de msegs. de duracion para el Fade
        ! (con pausa de 1ms, asi que efecto siempre durara el tiempo indicado)
        ! NOTA: 'i=1' sirve para evitar una iteracion extra, de otro modo el
        ! efecto de Fade tendria una duracion total erronea con 1ms adicional
        for (i=1 : i<=ms : i=i+1) {
          ! tomamos como 'valor base' para el volumen, la cantidad de msegs. de
          ! duracion total del efecto de Fade y a partir de este valor calculamos
          ! las unidades de volumen que corresponde cambiar en cada iteracion...
          self.VolumenCanal(nc,(i*(volfinal-vol)/ms)+vol); ! no cambiar formula
          !---------------------------------------------------------------------
          ! y finalmente hacemos una pausa durante 1ms que se repetira...
          self.HacerPausa(1); ! ...tantas veces como msegs. dure el efecto
        }
      }
    ],

    ! Hace FadeOut a un sonido en "tiempo-no-real" (devuelve control al finalizar efecto)
    SimpleFadeOut [ snd ms volfinal ! snd: sonido; ms: duracion; volfinal: vol. final
      nc vol i; ! nc: aux. (num. canal); vol: aux. (vol. inicial) i: para iteraciones
      ! el interprete puede manejar el Timer? Si no: no hacemos nada mas
      if (glk_gestalt(gestalt_Timer,0) == 0) { return; }
      !-------------------------------------------------------------------------
      ! si ya esta en proceso un trabajo de Fade, no se permite lanzar otro
      if (self.EnFade()) {
        #ifdef DEBUG;
          glk_set_style(style_Preformatted);
          new_line;
          print (string) ERROR_HACER_FADE_DURANTE_FADE; ! mensaje de aviso
          new_line;
          glk_set_style(style_Normal);
        #endif; ! DEBUG
        return;
      }
      !-------------------------------------------------------------------------
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! si Vol.Final es menor a 1% o mayor a 100%, fijar 0% de volumen (minimo)
      if ((volfinal < 1) || (volfinal > 100)) { volfinal = 0; } ! vol. minimo
      !-------------------------------------------------------------------------
      ! si duracion en msegs. es menor a 1, la deja en 100ms (1ms * 1% volumen)
      if (ms < 1) { ms = 100; }
      !-------------------------------------------------------------------------
      ! averiguamos vol. actual del sonido y lo recordamos como 'vol. inicial'
      vol = self.QueVolumenCanal(nc);
      !-------------------------------------------------------------------------
      ! == NOTA: ELECCION DEL ALGORITMO ==
      ! El volumen en Damusix siempre se mide en porcentajes, con un maximo de
      ! 100%. Por lo tanto, el tiempo de duracion para un Fade debe ser de al
      ! menos 100ms (porque se cambia 1% por cada 1ms). En este primer caso,
      ! se utilizara un 'algoritmo sencillo' que simplemente cambia 1 unidad
      ! de volumen en cada iteracion y luego realiza una espera calculada. Por
      ! el contrario, si el tiempo de duracion para el Fade es menor a 100ms,
      ! entonces debera utilizarse un 'algoritmo complejo' que hace justamente
      ! lo contrario al anterior: cambia X unidades de volumen calculadas segun
      ! un nuevo maximo de volumen, luego espera 1ms y todo el proceso se repite
      ! tantas veces como msegs. de duracion deba tener el efecto de Fade.
      !-------------------------------------------------------------------------
      ! ALGORITMO SENCILLO
      !-------------------------------------------------------------------------
      if (ms >= 100) {
        ! Se va a bajar volumen poco a poco desde 'vol.inicial' hasta 'vol.final'
        ! NOTA: 'vol-1' hace que la iteracion comience en % de volumen directamente
        ! inferior al % de 'vol.inicial': asi no se itera 2 veces con el mismo valor
        for (i=vol-1 : i>=volfinal : i=i-1) {
          ! cambiamos en 1 unidad el porcentaje de volumen
          self.VolumenCanal(nc, i);
          !---------------------------------------------------------------------
          ! finalmente hacemos una pausa durante un 'intervalo de tiempo' que se
          ! calcula segun la duracion total especificada para el efecto de Fade.
          ! Nunca hay division por cero, porque 'vol' no llega a valer 'volfinal';
          ! es la propia comprobacion inicial del bucle 'for' la que se encarga de
          self.HacerPausa(ms/(vol-volfinal)); ! evitar un posible error de calculo
        }
      }
      !-------------------------------------------------------------------------
      ! ALGORITMO COMPLEJO
      !-------------------------------------------------------------------------
      else {
        ! si el volumen actual del sonido al que se le va a hacer el efecto
        ! de Fade es menor o igual que el 'volumen final', terminamos la
        ! rutina porque el efecto es totalmente inaplicable en este caso...
        if (vol <= volfinal) { return; } ! terminamos aqui sin hacer nada mas
        !-----------------------------------------------------------------------
        ! iteramos tantas veces como numero de msegs. de duracion para el Fade
        ! (con pausa de 1ms, asi que efecto siempre durara el tiempo indicado)
        ! NOTA: 'i=1' sirve para evitar una iteracion extra, de otro modo el
        ! efecto de Fade tendria una duracion total erronea con 1ms adicional
        for (i=1 : i<=ms : i=i+1) {
          ! tomamos como 'valor base' para el volumen, la cantidad de msegs. de
          ! duracion total del efecto de Fade y a partir de este valor calculamos
          ! las unidades de volumen que corresponde cambiar en cada iteracion...
          self.VolumenCanal(nc,(i*(volfinal-vol)/ms)+vol); ! no cambiar formula
          !---------------------------------------------------------------------
          ! y finalmente hacemos una pausa durante 1ms que se repetira...
          self.HacerPausa(1); ! ...tantas veces como msegs. dure el efecto
        }
      }
      !-------------------------------------------------------------------------
      ! NOTA: aqui no detenemos el sonido ni reestablecemos su volumen con Vol.
      ! Global actual: esta rutina no es de "tiempo-real" asi que estos ajustes
      ! finales se dejan en manos del programador en el propio codigo del juego
      !-------------------------------------------------------------------------
    ],

  !=============================================================================
  !-----------------------------------------------------------------------------
  ! ** RUTINAS 'TECNICAS' RELACIONADAS CON LA REPRODUCC. DE AUDIO DE DAMUSIX **
  !-----------------------------------------------------------------------------
  !=============================================================================

    ! [TECNICO] REPRODUCE CUALQUIER SONIDO ASIGNADO AL CANAL ESPECIFICADO
    ! (no considera los sonidos, solo importan los canales)
    TocarCanal [ nc esn; ! nc: numero de canal; esn (1=='generar eventos SoundNotify')
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si esta en proceso un trabajo de Fade a un sonido cuyo
      ! canal es el mismo con el que vamos a trabajar en este momento
        if (self.cnl_fade == nc) { self.AbortarFade(); } ! abortamos el Fade
      !-------------------------------------------------------------------------
      ! pone el estado de reproduccion en uno (reproduciendo)
      self.&est_cnl-->nc = 1;
      ! finalmente actualiza el canal
      self.ActualizarCanal(nc, esn); ! llamado con arg. oscuro 'esn' (si es 1, notificar)
    ],

    ! [TECNICO] DETIENE CUALQUIER SONIDO ASIGNADO AL CANAL ESPECIFICADO
    ! (no considera el sonido, solo importa el canal)
    PararCanal [ nc; ! numero de canal
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      !-------------------------------------------------------------------------
      ! IMPORTANTE: si esta en proceso un trabajo de Fade a un sonido cuyo
      ! canal es el mismo con el que vamos a trabajar en este momento
        if (self.cnl_fade == nc) { self.AbortarFade(); } ! abortamos el Fade
      !-------------------------------------------------------------------------
      ! pone el estado de reproduccion en cero (detenido)
      self.&est_cnl-->nc = 0;
      ! finalmente actualiza el canal
      self.ActualizarCanal(nc);
    ],

    ! [TECNICO] DETIENE LA REPRODUCCION EN TODOS CANALES VIRTUALES Y TAMBIEN EN EL
    ! EL CANAL DE LA 'LISTA DE REPRODUCCION DE SONIDOS' [usado por varias rutinas]
    PararCanalesExtra [
      i; ! para iteraciones
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      ! recorre todos los canales virtuales y los detiene correctamente
      for (i=0 : i<DAMUSIX_VCANALMAX : i=i+1) { glk_schannel_stop(self.&gg_vcnl-->i); }
      ! tambien detenemos el canal de 'lista de reproduccion de sonidos' (por si acaso)
      glk_schannel_stop(self.gg_lcnl);
    ],

    ! [TECNICO] DETIENE TODOS LOS CANALES INICIALIZADOS
    ! (no considera los sonidos, solo importan los canales)
    PararTodo [
      i; ! para iteraciones
      ! abortar cualquier efecto de Fade que este en proceso actualmente
      self.AbortarFade();
      ! recorre todos los canales normales y los detiene correctamente
      for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) { self.PararCanal(i); }
      ! detiene reprod. en todos los canales virtuales y en canal de la 'lista'
      self.PararCanalesExtra();
    ],

    ! [TECNICO] ESTABLECE EL MODO DE REPETICION DE UN CANAL (CUANTAS VECES SE TOCARA)
    ! (no considera los sonidos, solo importan los canales)
    RepeticionCanal [ nc rep; ! nc: numero de canal; rep: el numero de repeticiones
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! si la cantidad de repeticiones es 0 o es menor a -1, la deja en 1 rep.
      if ((rep == 0) || (rep < -1)) { rep = 1; }
      ! establece el modo de repeticion del canal especificado
      self.&rep_cnl-->nc = rep;
    ],

    ! [TECNICO] ESTABLECE EL VOLUMEN DE UN CANAL
    ! (no considera los sonidos, solo importan los canales)
    VolumenCanal [ nc vol; ! nc: numero de canal; vol: porcentaje de volumen [-1==Vol.Global]
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! si el volumen es menor a 0% o mayor a 100%, lo deja en el valor del volumen global
      if ((vol < 0) || (vol > 100)) { vol = self.vol_global; }
      ! establece el volumen del canal especificado
      self.&vol_cnl-->nc = vol;
      ! si el audio no esta soportado, no se hace nada mas
      if (self.glk_sin_audio) { return; }
      !-------------------------------------------------------------------------
      ! el interprete puede cambiar el volumen? Si es asi: cambialo ahora
      if (glk_gestalt(gestalt_SoundVolume,0)) {
        ! finalmente actualiza el volumen
        glk_schannel_set_volume(self.&gg_ncnl-->nc, self.&vol_cnl-->nc * DAMUSIX_VOLMAX);
      }
    ],

  !=============================================================================
  !-----------------------------------------------------------------------------
  ! ** RUTINAS DE CONSULTA SOBRE EL ESTADO DEL KERNEL QUE DEVUELVEN UN VALOR **
  !-----------------------------------------------------------------------------
  !=============================================================================

    ! [TECNICO] AVERIGUA EL CANAL QUE SE LA HA ASIGNADO A UN SONIDO ESPECIFICO
    BuscarCanal [ snd ! snd: el sonido
      i; ! para iteraciones
      for (i=0 : i<DAMUSIX_NCANALMAX : i=i+1) {
        ! si el sonido es distinto de cero (es decir, si existe)
        if (snd ~= 0) {
          ! si lo encuentra devuelve el numero de canal
          if (self.&snd_cnl-->i == snd) { return i; }
        }
      }
      ! si no, es porque el sonido no ha sido asignado a ningun
      ! canal; se devuelve valor especial 'DAMUSIX_ERROR_SND'
      return DAMUSIX_ERROR_SND;
    ],

    ! [TECNICO] AVERIGUA EL SONIDO QUE SE LA HA ASIGNADO A UN CANAL ESPECIFICO
    BuscarSonido [ nc; ! nc: numero de canal
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.&snd_cnl-->nc; ! devuelve el sonido asignado a canal especificado
    ],

    ! [UTILITARIA] Comprueba si el interprete tiene SOPORTE COMPLETO de audio
    ! (implica la reproduccion de sonidos sampleados y de modulos musicales)
    TestAudio [ ;
      ! si el interprete PUEDE REPRODUCIR sonidos sampleados y modulos musicales
      if (glk_gestalt(gestalt_Sound,0) && glk_gestalt(gestalt_SoundMusic,0)) {
        return 1;
      }
      ! si alguna de las comprobaciones fallo, no hay soporte completo de audio
      else { return 0; }
    ],

    ! Comprueba el estado actual de la salida de audio de Damusix
    ! [segun se haya llamado o no a ActivarAudio()/DesactivarAudio()]
    HayAudio [ ;
      ! devuelve 1 si la salida de audio esta activada
      if (self.audio_activado) { return 1; }
      ! devuelve 0 si la salida de audio esta desactivada (modo silencioso)
      else { return 0; }
    ],

    ! Averigua la cantidad de sonidos agregados actualmente a 'lista de reproduccion'
    SonidosLista [
      cont i; ! cont: var.aux. (contador de sonidos); i: para iteraciones
      cont = 0; ! limpiamos el valor inicial del contador, 'por si acaso'
      ! comenzamos a contar la cantidad de sonidos agregados a 'lista de reproduccion'
      for (i=0 : i<(DAMUSIX_SNDLSTMAX*2) : i=i+2) { ! recorremos cada una de las filas de la lista
        ! siempre que la fila actual no este vacia ('1er slot'~=0), incrementamos el contador
        if (self.&snd_lst-->i ~= 0) { cont++; }
      }
      return cont; ! devolvemos el total de sonidos contados en la lista
    ],

    ! Averigua el modo de repeticion de un sonido (cuantas veces se tocara)
    QueRepeticion [ snd ! snd: el sonido
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.&rep_cnl-->nc; ! el modo de rep. asignado al canal del sonido
    ],

    ! Averigua el volumen de un sonido
    QueVolumen [ snd ! snd: el sonido
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! si el sonido no tiene canal asignado, no hace nada mas
      if (nc == DAMUSIX_ERROR_SND) { return DAMUSIX_ERROR_SND; } ! devuelve con error
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.&vol_cnl-->nc; ! el vol. asignado al canal del sonido
    ],

    ! Averigua el volumen comun actual para todos los canales 'virtuales'
    QueVolumenV [ ;
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.vol_vcnl;
    ],

    ! Averigua el volumen comun actual para la 'lista de reproduccion de sonidos'
    QueVolumenLista [ ;
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.vol_lcnl;
    ],

    ! Averigua el volumen global actual de todos los sonidos gestionados por Damusix
    QueVolumenGlobal [ ;
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.vol_global;
    ],

    ! Comprueba si actualmente esta sonando de fondo el sonido-musica especificado
    ! (es decir, reproduciendolo con 'repeticiones infinitas' [est_cnl==1])
    SonandoDeFondo [ snd ! el sonido a comprobar
      nc; ! variable auxiliar (numero de canal)
      ! buscar el canal de ese sonido
      nc = self.BuscarCanal(snd);
      ! IMPORTANTE: si el sonido no tiene canal asignado, significa que NO ESTA SONANDO
      if (nc == DAMUSIX_ERROR_SND) { return 0; } ! ... y devuelve 0: no sonando de fondo
      ! devuelve el estado del sonido en ese canal (0==det. o 'rep. finita'; 1==reprod.)
      return self.&est_cnl-->nc;
    ],

    ! Comprueba si actualmente esta en proceso un efecto de Fade en "tiempo-real"
    EnFade [ ;
      ! devuelve 1 si se esta haciendo un Fade actualmente
      if (self.que_fade == 1 or 2) { return 1; }
      ! devuelve 0 si no hay ningun Fade en proceso
      else { return 0;}
    ],

    ! [TECNICO] AVERIGUA EL MODO DE REPETICION DE UN CANAL (CUANTAS VECES SE TOCARA)
    QueRepeticionCanal [ nc; ! nc: numero de canal
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.&rep_cnl-->nc; ! devuelve el modo de repeticion del canal especificado
    ],

    ! [TECNICO] AVERIGUA EL VOLUMEN DE UN CANAL
    QueVolumenCanal [ nc; ! nc: numero de canal
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! devuelve el valor establecido en las variables del kernel de Damusix
      return self.&vol_cnl-->nc; ! devuelve el volumen del canal especificado
    ],

    ! [TECNICO] COMPRUEBA SI ACTUALMENTE EL CANAL ESPECIFICADO ESTA SONANDO DE FONDO
    ! CUALQUIER SONIDO-MUSICA (es decir, reprod. con 'rep. infinitas' [est_cnl==1])
    SonandoDeFondoCanal [ nc; ! numero de canal
      ! si el canal es menor a 0, o es mayor que la cantidad inicializada, no hace nada mas
      if ((nc < 0) || (nc > DAMUSIX_NCANALMAX-1)) { return DAMUSIX_ERROR_CNL; } ! devuelve con error
      ! devuelve estado de reproduccion del canal (0==det. o 'rep. finita'; 1==reprod.)
      return self.&est_cnl-->nc;
    ],
;

#endif; ! fin de _DAMUSIX_H_
