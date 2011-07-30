! EParser.h
!================================================================
! Adaptación para InformATE! de la librería biplataforma 6/10
!----------------------------------------------------------------
!
! Número de Serie: 080625
!
! Esta adaptación ha sido realizada mediante un conversor automático
! y posteriores retoques manuales.
! Los comentarios permanecen en inglés, así como todas las variables y
! constantes añadidas para el soporte Glulx.
!
! Conversión (c) Zak 2000
!
! ----------------------------------------------------------------------------
!  (c) Graham Nelson 1993, 1994, 1995, 1996, 1997, 1998, 1999
!      but freely usable (see manuals)
! ----------------------------------------------------------------------------

System_file;

Ifdef INFIX; Ifndef DEBUG; Constant DEBUG; Endif; Endif;
Ifdef STRICT_MODE; Ifndef DEBUG; Constant DEBUG; Endif; Endif;

Constant NumSerieLib      = "080625";
Constant RevisionLib      = "6/10E";
Constant Grammar__Version = 2;

! Algunos avisos
Message "InformATE! 6/10 biplataforma";

#Ifndef VN_1610;
  Message fatalerror "*** La versión 6/10 necesita Inform v6.10 o superior ***";
#Endif; ! VN_

Ifdef MODULE_MODE;
  Message fatalerror "*** La librería InformATE! no soporta el uso de
    módulos. Debes compilar sin la opción -M ***";
Endif;


! Antiguo enlazlpa.h, incluido ahora como parte de EParser.h
!================================================================
! Adaptación para InformATE! de la librería biplataforma 6/10
!----------------------------------------------------------------
! Esta adaptación ha sido realizada mediante un conversor automático
! y posteriores retoques manuales.
! Los comentarios permanecen en inglés, así como todas las variables y
! constantes añadidas para el soporte Glulx.
!
! Conversión (c) Zak 2000, 2001
!
! ----------------------------------------------------------------------------

! Declaraciones de atributos y propiedades
! (que también están en la librería inglesa)

Attribute abierto;
Attribute abrible;
Attribute animado;
Attribute ausente;
Attribute banderaux;
Attribute cerrojo;
Attribute cerrojoechado;
Attribute comestible;
Attribute conmutable;
Attribute encendido;
Attribute entrable;
Attribute escenario;
Attribute estatico;
Attribute general;
Attribute hablable;
Attribute luz;
Attribute movido;
Attribute oculto;
Attribute prenda;
Attribute propio;
Attribute puerta;
Attribute puesto;
Attribute recipiente;
Attribute soporte;
Attribute transparente;
Attribute valepuntos;
Attribute visitado;

Attribute femenino;
Attribute masculino;
Attribute neutro;
Attribute nombreplural;

#Ifdef TARGET_ZCODE;
  Constant NULL         = $ffff;
  Constant WORD_HIGHBIT = $8000;
#Ifnot; ! TARGET_GLULX
  Constant NULL         = $ffffffff;
  Constant WORD_HIGHBIT = $80000000;
#Endif; ! TARGET_

Property additive antes   NULL;
Property additive despues NULL;
Property additive vida    NULL;

Property abajo;
Property adentro;
Property afuera;
Property al_e;
Property al_n;
Property al_ne;
Property al_no;
Property al_o;
Property al_s;
Property al_se;
Property al_so;
Property arriba;

Property con_llave;
Property direcc_puerta;
Property gramatica;
Property listarse;
Property listar_juntos;
Property additive ordenes;
Property plural;
Property puerta_a;
Property reaccionar_antes;
Property reaccionar_despues;
Property suma_al_alcance;

Property articulo "un";
Property additive describir NULL;
Property descripcion;
Property inicial;
Property si_abierto;
Property si_apagado;
Property si_cerrado;
Property si_encendido;

Property no_puedes_ir 0;

Property esta_en;         !  For fiddly reasons this can't alias

Property additive cada_turno NULL;
Property cantidad;
Property daemon;
Property additive tiempo_agotado NULL;
Property tiempo_restante;

Property capacidad 100;

Property nombre_corto 0;
Property nombre_corto_indef 0;
Property parse_nombre 0;

Property articulos;
Property descripcion_dentro;

! ================== Fin de enlazlpa.h ==================

Fake_Action DejarSalir;
Fake_Action Recibir;
Fake_Action RecibirLanzamiento;
Fake_Action Orden;
Fake_Action ElMismo;
Fake_Action HalladoPlural;
Fake_Action ListaMiscelanea;
Fake_Action Miscelanea;
Fake_Action Prompt;
Fake_Action NoComprendido;

! TODO: ¿Para qué sirven estas acciones falsas si se ha definido NO_LUGARES?

Ifdef NO_LUGARES;
  Fake_Action Lugares;
  Fake_Action Objetos;
Endif;

[ Main; LibreriaInform.jugar(); ];

! ================== Fin de EParser.h ==================

!****************************************************************
!****************************************************************
!****************************************************************
!****************************************************************
!****************************************************************
!****************************************************************
! Incluimos aquí mismo el parser.
! No tiene sentido mantenerlo en eparserm porque no se admite la
! compilación por módulos.

! Eparserm.h
!================================================================
! Adaptación para InformATE! de la librería biplataforma 6/10
!----------------------------------------------------------------
! Esta adaptación ha sido realizada mediante un conversor automático
! y posteriores retoques manuales.
! Los comentarios permanecen en inglés, así como todas las variables y
! constantes añadidas para el soporte Glulx.
!
! Conversión (c) Zak 2000, 2001
!
! ----------------------------------------------------------------------------
!  PARSERM:  Core of parser.
!
!  Supplied for use with Inform 6                         Serial number 000629
!                                                                 Release 6/10
!  (c) Graham Nelson 1993, 1994, 1995, 1996, 1997, 1998, 1999
!      but freely usable (see manuals)
! ----------------------------------------------------------------------------
!  Inclusion of "enlazlpa"
!                   (which defines properties and attributes)
!  Global variables, constants and arrays
!                1: outside of the parser
!                2: used within the parser
!  Inclusion of natural language definition file
!                   (which creates a compass and direction-objects)
!  Darkness and player objects
!  Definition of gramatica token numbering system used by Inform
!
!  The ParserInform object
!          keyboard reading
!          level 0: outer shell, conversation, errors
!                1: grammar lines
!                2: tokens
!                3: object lists
!                4: scope and ambiguity resolving
!                5: object comparisons
!                6: word comparisons
!                7: reading words and moving tables about
!          pronoun management
!
!  The LibreriaInform object
!          main game loop
!          accion processing
!          end of turn sequence
!          scope looping, antes/despues sequence, sending messages out
!          timers, daemons, time of day, score notification
!          light and darkness
!          changing player personality
!          tracing code (only present if DEBUG is set)
!
!  Status line printing, menu display
!  Printing object names with articles
!  Miscellaneous utility routines
!  Game banner, "version" verb, run-time errors
! ----------------------------------------------------------------------------

! ============================================================================
!   Variables globales y sus declaraciones asociadas de constantes y vectores
! ----------------------------------------------------------------------------

Global localizacion = LibreriaInform;  ! Debe ser el primer Global definido
Global lineaEstado1;                 ! Debe ser el segundo
Global lineaEstado2;                 ! Debe ser el tercero
                                     ! (para mostrar la línea de estado)

! ------------------------------------------------------------------------------
!   Z-Machine and interpreter issues
! ------------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;
  Global objeto_raiz;                ! Largest valid number of any tree object
  Global interprete_estandar;        ! The version number of the Z-Machine
                                     ! Standard which the interpreter claims
                                     ! to support, in form (upper byte).(lower)
! ### these globals are not meaningful... well, maybe interprete_estandar,
! but I'll decide that later.
#Endif; ! TARGET_ZCODE

Global bandera_deshacer;             ! Can the interpreter provide "undo"?
Global just_undone;                  ! Can't have two successive UNDOs

#Ifdef TARGET_ZCODE;
  Global modo_transcripcion;         ! true when game scripting is on
  Ifdef DEBUG;
    Global xcommsdir;                ! true if command recording is on
  Endif;
#Endif; ! TARGET_ZCODE

#Ifdef TARGET_GLULX;
  Constant GG_MAINWIN_ROCK     201;
  Constant GG_STATUSWIN_ROCK   202;
  Constant GG_QUOTEWIN_ROCK    203;
  Constant GG_SAVESTR_ROCK     301;
  Constant GG_SCRIPTSTR_ROCK   302;
  Constant GG_COMMANDWSTR_ROCK 303;
  Constant GG_COMMANDRSTR_ROCK 304;
  Constant GG_SCRIPTFREF_ROCK  401;
  Array gg_event     --> 4;
  Array gg_arguments --> 8;
  Global gg_mainwin           = 0;
  Global gg_statuswin         = 0;
  Global gg_quotewin          = 0;
  Global gg_scriptfref        = 0;
  Global gg_scriptstr         = 0;
  Global gg_savestr           = 0;
  Global gg_statuswin_cursize = 0;
  Global gg_statuswin_size    = 1;
  Ifdef DEBUG;
    Global gg_commandstr = 0;
    Global gg_command_reading = 0;   ! true if gg_commandstr is being replayed
  Endif;
#Endif; ! TARGET_GLULX

! ------------------------------------------------------------------------------
!   Time and score
! (for linkage reasons, the task_* arrays are created not here but in verblib.h)
! ------------------------------------------------------------------------------

Global turnos = 1;                   ! Number of turns of play so far
Global la_hora = NULL;               ! Current time (in minutes since midnight)
Global hora_freq = 1;                ! How often time is updated
Global hora_incr;                    ! By how much

#Ifndef MAX_RELOJES;
  Constant MAX_RELOJES 32;           ! Max number timers/daemons active at once
#Endif;

Array  los_relojes --> MAX_RELOJES;
Global relojes_activos;              ! Number of timers/daemons actives

Global puntuacion;                   ! La puntuación actual
Global punt_anterior;                ! Score last turn (for testing for changes)

! Notificación de cambios en la puntuación
#Ifndef NO_PUNTUACION;
  Global modo_notificar = true;
#Ifnot;
  Global modo_notificar = false;
#Endif; ! NO_PUNTUACION
Global puntos_sitios;                ! Contribution to puntuacion made by
                                     ! visiting
Global puntos_cosas;                 ! Contribution made by acquisition

! ------------------------------------------------------------------------------
!   The player
! ------------------------------------------------------------------------------

Global jugador;                      ! Which object the human is playing through
Global banderafin;                   ! Normally 0, or false; 1 for dead;
                                     ! 2 for victorious, and higher numbers
                                     ! represent exotic forms of death

! ------------------------------------------------------------------------------
!   Light and room descriptions
! ------------------------------------------------------------------------------

Global banderaluz = true;            ! Is there currently luz to see by?
Global localizacion_real;            ! When in darkness,localizacion=LaOscuridad
                                     ! and this holds the real localizacion
Global techo_de_visibilidad;         ! Highest object in tree visible from
                                     ! the jugador's point of view (usually
                                     ! the room, sometimes darkness, sometimes
                                     ! a closed non-transparente recipiente).

Global modomirar = 1;                ! 1=standard, 2=verbose, 3=brief room descs
Global bandera_imprime_jugador;      ! If set, print something like "(as Fred)"
                                     ! in room descriptions, to reveal whom
                                     ! the human is playing through
Global ultimadesc;                   ! Value of localizacion at time of most
                                     ! recent room descripcion printed out

! ------------------------------------------------------------------------------
!   List writing  (style bits are defined as Constants in "accionm.h")
! ------------------------------------------------------------------------------

Global estilo_ac;                    ! Current list-writer style
Global valor_lj;                     ! Common value of listar_juntos
Global listando_junto;               ! Object number of one member of a group
                                     ! being listed together
Global tamanio_listando;             ! Size of such a group
Global indentacion_eld;              ! Current level of indentation printed by
                                     ! EscribirListaDesde routine

Global etapa_inventario = 1;         ! 1 or 2 according to the context in which
                                     ! "listarse" routines of objects are called
Global estilo_inventario;            ! List-writer style currently used while
                                     ! printing inventories

! ------------------------------------------------------------------------------
!   Menus and printing
! ------------------------------------------------------------------------------

Global bandera_guapo = true;         ! Use character graphics, or plain text?
Global anidacion_menu;               ! Level of nesting (0 = root menu)
Global elemento_menu;                ! These are used in communicating
Global ancho_elemento = 8;           ! with the menu-creating routines
Global nombre_elemento = "---";

Global ml_n;                         ! Parameters used by MensajesLibreria
Global ml_o;                         ! mechanism

#Ifdef DEBUG;
  Global debug_flag;                 ! Bitmap of flags for tracing actions,
                                     ! calls to object routines, etc.
  Global x_cuenta_ambito;            ! Used in printing a list of everything
                                     ! in scope
#Endif; ! DEBUG

! ------------------------------------------------------------------------------
!   Action processing
! ------------------------------------------------------------------------------

Global accion;                       ! Action currently being asked to perform
Global dat1;                         ! 0 (nothing), 1 (number) or first noun
Global dat2;                         ! 0 (nothing), 1 (number) or otro noun
Global uno;                          ! First noun or numerical value
Global otro;                         ! Second noun or numerical value

Global tate_callao;                  ! If true, attempt to perform the accion
                                     ! silently (e.g. for implicit takes,
                                     ! implicit opening of unlocked doors)

Global codigo_razon;                 ! Reason for calling a "vida" rule
                                     ! (an accion or fake such as ##Besar)

Global accion_recibir;               ! Either ##PonerSobre or ##Meter, whichever
                                     ! is accion being tried when an object's
                                     ! "antes" rule is checking "Receive"

! ==============================================================================
!   Parser variables: first, for communication to the parser
! ------------------------------------------------------------------------------

Global parser_listo = 1;             ! Ponerlo a 0 para que el parser
                                     ! no intente ejecutar las acciones que
                                     ! no ha comprendido del todo.
                                     ! Si se pone a 1 preguntará al jugador para
                                     ! desambiguar
                                     ! Si se pone a 2 no hará la pregunta
                                     ! de desambiguación al jugador y sí
                                     ! realizará la acción
Global si_pl = 0;                    ! Desde Mensajes.h se devuelve 1 si
                                     ! el jugador respondió "si" a la pregunta
                                     ! de desencadenada por parser_listo=1
#Ifdef DEBUG;  ! [080625]
Global parser_trace = 0;             ! Set this to 1 to make the parser trace
                                     ! tokens and lines
#Endif; ! DEBUG
Global accion_parser;                ! For the use of the parser when calling
Global parser_uno;                   ! user-supplied routines
Global parser_dos;                   !
Array  inputobjs --> 16;             ! For parser to write its results in
Global parser_inflexion;             ! A property (usually "nombre") to find
                                     ! object names in

! ------------------------------------------------------------------------------
!   Parser output
! ------------------------------------------------------------------------------

Global actor;                        ! Person asked to do something
Global localizacion_actor;           ! Like localizacion, but for the actor
Global meta;                         ! Verb is a meta-command (such as "save")

Array  objeto_multiple --> 64;       ! List of multiple parametros
Global banderamulti;                 ! Multiple-object flag
Global bandera_demasiados;           ! Flag for "multiple match too large"
                                     ! (e.g. if "take all" took over 100 things)

Global palabra_especial;             ! Dictionary address for "special" token
Global numero_especial;              ! Number typed for "special" token
Global numero_interpretado;          ! For user-supplied parsing routines
Global consultar_desde;              ! Word that a "consult" topic starts on
Global consultar_num_palabras;       ! ...and number of words in topic

! ------------------------------------------------------------------------------
!   Implicit taking
! ------------------------------------------------------------------------------

Global modo_noposeido;               ! To do with implicit taking
Global amodo_noposeido;              !     "old copy of modo_noposeido", ditto
Global no_poseido;                   ! Object to be automatically taken as an
                                     ! implicit command
Array  resultados_guardados --> 16;  ! Delayed command (while the take happens)

! ------------------------------------------------------------------------------
!   Error numbers when parsing a gramatica line
! ------------------------------------------------------------------------------

Global tipoerror;                    ! Error number on current line
Global mejor_tipoerror;              ! Preferred error number so far
Global proxmejor_tipoerror;          ! Preferred one, if PREGUNTAAMBITO_PE
                                     ! disallowed

Constant ATASCADO_PE       = 1;
Constant HASTAQUI_PE       = 2;
Constant NUMERO_PE         = 3;
Constant NOVEO_PE          = 4;
Constant MUYPOCO_PE        = 5;
Constant NOTIENES_PE       = 6;
Constant MULTI_PE          = 7;
Constant MMULTI_PE         = 8;
Constant PRONOM_PE         = 9;
Constant EXCEPTO_PE        = 10;
Constant ANIMA_PE          = 11;
Constant VERBO_PE          = 12;
Constant ESCENARIO_PE      = 13;
Constant YANOPRON_PE       = 14;
Constant KKFINAL_PE        = 15;
Constant HAYPOCOS_PE       = 16;
Constant NADA_PE           = 17;
Constant PREGUNTAAMBITO_PE = 18;

! ------------------------------------------------------------------------------
!   Pattern-matching against a single gramatica line
! ------------------------------------------------------------------------------

Array  patron  --> 32;               ! For the current patron match
Global contadorp;                    ! and a marker within it
Array  patron2 --> 32;               ! And another, which stores the best match
Global contadorp2;                   ! so far
Constant PATRON_NULO = $ffff;        ! Entry for a token producing no text

Array  linea_tipot  --> 32;          ! For storing an analysed gramatica line
Array  linea_tdatos --> 32;
Array  linea_token  --> 32;

Global parametros;                   ! Parameters (objects) entered so far
Global nsns;                         ! Number of special_numbers entered so far
Global numero_especial1;             ! First number, if one was typed
Global numero_especial2;             ! Second number, if two were typed

! ------------------------------------------------------------------------------
!   Inferences and looking ahead
! ------------------------------------------------------------------------------

Global parametros_deseados;          ! Number of parametros needed
                                     ! (which may change in parsing)

Global deducedesde;                  ! The point from which the rest of the
                                     ! command must be inferred
Global prepdeducida;                 ! And the preposition inferred
Global no_deducir;                   ! Another dull flag

Global accion_que_seria;             ! (If the current line were accepted.)
Global accion_invertida;             ! (Parameters would be reversed in order.)
Global aviso_avanzar;                ! What a later-named thing will be

! ------------------------------------------------------------------------------
!   At the level of individual tokens now
! ------------------------------------------------------------------------------

Global ttipo_encontrado;             ! Used to break up tokens into type
Global tdatos_encontrado;            ! and data (by AnalizarToken)
Global filtro_token;                 ! For noun filtering by user routines

Global long_de_uno;                  ! Set by DominioNombre to no of words in
                                     ! noun
#Ifdef TARGET_ZCODE;
  Constant CODIGO_REPARSE = 10000;   ! Signals "reparse the text" as a reply
                                     ! from DominioNombre
#Ifnot; ! TARGET_GLULX
  Constant CODIGO_REPARSE = $40000000; ! The parser rather gunkily adds
                                     ! addresses to CODIGO_REPARSE for some
                                     ! purposes.
                                     ! And expects the result to be greater
                                     ! than CODIGO_REPARSE (signed comparison).
                                     ! So Glulx Inform is limited to a single
                                     ! gigabyte of storage, for the moment.
#Endif; ! TARGET_

Global elsiguiente;                  ! The token after the one now being matched

Global modo_multi;                   ! Multiple mode
Global multi_esperado;               ! Number of things needed in multitude
Global multi_hallado;                ! Number of things actually found
Global multi_contexto;               ! What token the multi-obj was accepted for

Global modo_indef;                   ! "Indefinite" mode - ie, "take a brick"
                                     ! is in this mode
Global indef_tipo;                   ! Bit-map holding types of specification
Global indef_esperado;               ! Number of items wanted (100 for all)
Global indef_suponer_p;              ! Plural-guessing flag
Global indef_propietario;            ! Object which must hold these items
Global indef_casos;                  ! Possible gender and numbers of them
Global indef_posibambig;             ! Has a possibly dangerous assumption
                                     ! been made about meaning of a descriptor?
Global indef_numero_en;              ! Word at which a number like "two" was
                                     ! parsed (for backtracking)
Global permitir_plurales;            ! Whether plurals presently allowed or not

Global regla_coger_todo;             ! Slightly different rules apply to
                                     ! "take all" than other uses of multiple
                                     ! objects, to make adjudication produce
                                     ! more pragmatically useful results
                                     ! (Not a flag: possible values 0, 1, 2)

Global banderas_dicc_nombre;         ! Of the noun currently being parsed
                                     ! (a bitmap in #dict_par1 format)
Global palabra_pronombre;            ! Records which pronoun ("it", "them", ...)
                                     ! caused an error
Global objeto_pronombre;             ! And what obj it was thought to refer to
Global palabra__pronombre;           ! Saved value
Global objeto__pronombre;            ! Saved value

! ------------------------------------------------------------------------------
!   Searching through scope and parsing "scope=Routine" gramatica tokens
! ------------------------------------------------------------------------------

Constant RAZON_PARSING            = 0; ! Possible reasons for searching scope
Constant RAZON_HABLAR             = 1;
Constant RAZON_CADA_TURNO         = 2;
Constant RAZON_REACCIONAR_ANTES   = 3;
Constant RAZON_REACCIONAR_DESPUES = 4;
Constant RAZON_BUCLEALCANCE       = 5;
Constant RAZON_TESTALCANCE        = 6;

Global razon_alcance = RAZON_PARSING; ! Current reason for searching scope

Global token_alcance;                ! For "scope=Routine" grammar tokens
Global error_alcance;
Global estadio_alcance;              ! 1, 2 then 3

Global bandera_paa = 0;              ! For SumarAlAlcance routines
Global paa_tfl;                      !

Global bandera_puesto_en;            ! To do with PonerAlAlcance

! ------------------------------------------------------------------------------
!   The match list of candidate objects for a given token
! ------------------------------------------------------------------------------

Constant TAMANIO_LISTA_ENCAJAN = 128;
Array  lista_encajan  --> 64;        ! An array of matched objects so far
Array  encajan_clases --> 64;        ! An array of equivalence classes for them
Array  encajan_puntos --> 64;        ! An array of match scores for them
Global numero_de_encajados;          ! How many items in it?  (0 means none)
Global numero_de_clases;             ! How many equivalence classes?
Global long_encajado;                ! How many words long are these matches?
Global encajado_desde;               ! At what word of the input do they begin?
Global bestguess_score;              ! What did the best-guess object score?

! ------------------------------------------------------------------------------
!   Low level textual manipulation
! ------------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

  Constant INPUT_BUFFER_LEN = 120;   ! Length of buffer array (although we
                                     ! leave an extra byte to allow for
                                     ! interpreter bugs)

  Array buffer    -> 121;            ! Buffer for parsing main line of input
  Array parse     -> 65;             ! Parse table mirroring it
  Array buffer2   -> 121;            ! Buffers for supplementary questions
  Array parse2    -> 65;             !
  Array bufferaux -> 121;            ! usado en BuscarEnDiccionario [001115]
  Array parseaux  -> 65;
  Array buffer3   -> 121;            ! Buffer retaining input for "again"

#Ifnot; ! TARGET_GLULX

  Constant INPUT_BUFFER_LEN = 260;   ! No extra byte necessary
  Constant MAX_BUFFER_WORDS = 20;
  Constant PARSE_BUFFER_LEN = 244;   ! 4 + MAX_BUFFER_WORDS*4;

  Array buffer    -> INPUT_BUFFER_LEN;
  Array parse     -> PARSE_BUFFER_LEN;
  Array buffer2   -> INPUT_BUFFER_LEN;
  Array parse2    -> PARSE_BUFFER_LEN;
  Array bufferaux -> INPUT_BUFFER_LEN; ! usado en BuscarEnDiccionario [001110]
  Array parseaux  -> PARSE_BUFFER_LEN;
  Array buffer3   -> INPUT_BUFFER_LEN;

#Endif; ! TARGET_

Constant palabra_coma = 'coma,';     ! An "untypeable word" used to substitute
                                     ! for commas in parse buffers

Global np;                           ! Word number within "parse" (from 1)
Global num_palabras;                 ! Number of words typed
Global palabra_verbo;                ! Verb word (eg, take in "take all" or
                                     ! "dwarf, take all") - address in dict
Global palabra_verbonum;             ! its number in typing order (eg, 1 or 3)
Global gramatica_normal_tras;        ! Point from which usual grammar is parsed
                                     ! (it may vary from the above if user's
                                     ! routines match multi-word verbs)

Global eepa_desde;                   ! The "first mistake" word number
Global eepa_guardado;                ! Used in working this out
Array  oops_workspace -> 64;         ! Used temporarily by "oops" routine

Global modo_mantenido;               ! Flag: is there some input from last time
Global mant_np;                      ! left over?  (And a save value for np.)
                                     ! (Used for full stops and "then".)

! ----------------------------------------------------------------------------
Array PowersOfTwo_TB                 ! Used in converting case numbers to
  --> $$100000000000                 ! case bitmaps
      $$010000000000
      $$001000000000
      $$000100000000
      $$000010000000
      $$000001000000
      $$000000100000
      $$000000010000
      $$000000001000
      $$000000000100
      $$000000000010
      $$000000000001;
! ============================================================================


! ============================================================================
!  Constants, and one variable, needed for the language definition file
! ----------------------------------------------------------------------------

Constant POSESIVO_PK  = $100;
Constant DEFINIDO_PK   = $101;
Constant INDEFINIDO_PK = $102;
Global caso_nombre_corto;

! ----------------------------------------------------------------------------
Include "Espanol";                   !  The natural language definition,
                                     !  whose filename is taken from the ICL
                                     !  language_name variable
! ----------------------------------------------------------------------------

#Ifndef CasosLenguaje;
  Constant CasosLenguaje = 1;
#Endif;

! ------------------------------------------------------------------------------
!   Pronouns support for the cruder (library 6/2 and earlier) version:
!   only needed in English
! ------------------------------------------------------------------------------

#Ifdef EnglishNaturalLanguage;
  Global itobj = NULL;               ! The object which is currently "it"
  Global himobj = NULL;              ! The object which is currently "him"
  Global herobj = NULL;              ! The object which is currently "her"

  Global old_itobj = NULL;           ! The object which is currently "it"
  Global old_himobj = NULL;          ! The object which is currently "him"
  Global old_herobj = NULL;          ! The object which is currently "her"
#Endif; ! EnglishNaturalLanguage

! ============================================================================


! ============================================================================
! "Darkness" is not really a place: but it has to be an object so that the
!  localizacion-nombre on the status line can be "Darkness".
! ----------------------------------------------------------------------------

Object LaOscuridad "(objeto oscuridad)"
  with
    inicial 0,
    nombre_corto OSCURIDAD__TX,
    descripcion [;
      return M__L(##Miscelanea, 17);
    ];

Object objjugador "(objeto jugador)"
  with
    nombre_corto [;
      return M__L(##Miscelanea, 18);
    ],
    descripcion [;
      return M__L(##Miscelanea, 19);
    ],
    antes          NULL,
    despues        NULL,
    vida           NULL,
    cada_turno     NULL,
    tiempo_agotado NULL,
    describir      NULL,
    capacidad      100,
    parse_nombre   0,
    ordenes        0,
    cantidad       0,
  has
    oculto animado propio transparente;

! ============================================================================
!  The definition of the token-numbering system used by Inform.
! ----------------------------------------------------------------------------

Constant TT_ILEGAL        = 0;       ! Types of grammar token: illegal
Constant TT_ELEMENTAL     = 1;       !     (one of those below)
Constant TT_PREPOSICION   = 2;       !     e.g. 'into'
Constant TT_FILTRO_RUTINA = 3;       !     e.g. noun=CagedCreature
Constant TT_FILTRO_ATRIB  = 4;       !     e.g. comestible
Constant TT_ALCANCE       = 5;       !     e.g. scope=Spells
Constant TT_RPG           = 6;       !     a general parsing routine

Constant TOKEN_NOMBRE       = 0;     ! The elementary gramatica tokens, and
Constant TOKEN_POSEIDO      = 1;     ! the numbers compiled by Inform to
Constant TOKEN_MULTI        = 2;     ! encode them
Constant TOKEN_MULTIPOSEIDO = 3;
Constant TOKEN_MULTIEXCEPTO = 4;
Constant TOKEN_MULTIDENTRO  = 5;
Constant TOKEN_CRIATURA     = 6;
Constant TOKEN_ESPECIAL     = 7;
Constant TOKEN_NUMERO       = 8;
Constant TOKEN_TEMA         = 9;


Constant RPG_FALLO        = -1;      ! Return values from General Parsing
Constant RPG_PREPOSICION  = 0;       ! Routines
Constant RPG_NUMERO       = 1;
Constant RPG_MULTIPLE     = 2;
Constant RPG_REPARSE      = CODIGO_REPARSE;
Constant RPG_NOMBRE       = $ff00;
Constant RPG_POSEIDO      = $ff01;
Constant RPG_MULTI        = $ff02;
Constant RPG_MULTIPOSEIDO = $ff03;
Constant RPG_MULTIEXCEPTO = $ff04;
Constant RPG_MULTIDENTRO  = $ff05;
Constant RPG_CRIATURA     = $ff06;

Constant TOKEN_FINAL      = 15;      ! Value used to mean "end of grammar line"

#Iftrue (Grammar__Version == 1);
[ AnalizarToken token m;

    tdatos_encontrado = token;

    if (token < 0)   { ttipo_encontrado = TT_ILEGAL; return; }
    if (token <= 8)  { ttipo_encontrado = TT_ELEMENTAL; return; }
    if (token < 15)  { ttipo_encontrado = TT_ILEGAL; return; }
    if (token == 15) { ttipo_encontrado = TT_ELEMENTAL; return; }
    if (token < 48)  { ttipo_encontrado = TT_FILTRO_RUTINA;
                       tdatos_encontrado = token - 16;
                       return; }
    if (token < 80)  { ttipo_encontrado = TT_RPG;
                       tdatos_encontrado = #preactions_table-->(token-48);
                       return; }
    if (token < 128) { ttipo_encontrado = TT_ALCANCE;
                       tdatos_encontrado = #preactions_table-->(token-80);
                       return; }
    if (token < 180) { ttipo_encontrado = TT_FILTRO_ATRIB;
                       tdatos_encontrado = token - 128;
                       return; }

    ttipo_encontrado = TT_PREPOSICION;
    m=#adjectives_table;
    for (::)
    {   if (token==m-->1) { tdatos_encontrado = m-->0; return; }
        m=m+4;
    }
    m=#adjectives_table; ErrorDeEjecucion(1);
    tdatos_encontrado = m;
];

[ DesempaquetarLineaGramatica line_address i m;
  for (i = 0 : i < 32 : i++)
  {   linea_token-->i = TOKEN_FINAL;
      linea_tipot-->i = TT_ELEMENTAL;
      linea_tdatos-->i = TOKEN_FINAL;
  }
  for (i = 0: i <= 5 :i++)
  {   linea_token-->i = line_address->(i+1);
      AnalizarToken(linea_token-->i);
      if ((ttipo_encontrado == TT_ELEMENTAL) && (tdatos_encontrado == TOKEN_NOMBRE)
          && (m == line_address->0))
      {   linea_token-->i = TOKEN_FINAL;
          break;
      }
      linea_tipot-->i = ttipo_encontrado;
      linea_tdatos-->i = tdatos_encontrado;
      if (ttipo_encontrado ~= TT_PREPOSICION) m++;
  }
  accion_que_seria = line_address->7;
  accion_invertida = false;
  parametros_deseados = line_address->0;
  return line_address + 8;
];
#Ifnot;
[ AnalizarToken token;

    if (token == TOKEN_FINAL)
    {   ttipo_encontrado = TT_ELEMENTAL;
        tdatos_encontrado = TOKEN_FINAL;
        return;
    }

    ttipo_encontrado = (token->0) & $$1111;
    tdatos_encontrado = (token+1)-->0;
];
#Ifdef TARGET_ZCODE;
[ DesempaquetarLineaGramatica line_address i;
  for (i = 0 : i < 32 : i++)
  {   linea_token-->i = TOKEN_FINAL;
      linea_tipot-->i = TT_ELEMENTAL;
      linea_tdatos-->i = TOKEN_FINAL;
  }
  accion_que_seria = 256*(line_address->0) + line_address->1;
  accion_invertida = ((accion_que_seria & $400) ~= 0);
  accion_que_seria = accion_que_seria & $3ff;
  line_address--;
  parametros_deseados = 0;
  for (i=0::i++)
  {   line_address = line_address + 3;
      if (line_address->0 == TOKEN_FINAL) break;
      linea_token-->i = line_address;
      AnalizarToken(line_address);
      if (ttipo_encontrado ~= TT_PREPOSICION) parametros_deseados++;
      linea_tipot-->i = ttipo_encontrado;
      linea_tdatos-->i = tdatos_encontrado;
  }
  return line_address + 1;
];
#Ifnot; ! TARGET_GLULX
[ DesempaquetarLineaGramatica line_address i;
  for (i = 0 : i < 32 : i++)
  {   linea_token-->i = TOKEN_FINAL;
      linea_tipot-->i = TT_ELEMENTAL;
      linea_tdatos-->i = TOKEN_FINAL;
  }
  @aloads line_address 0 accion_que_seria;
  accion_invertida = (((line_address->2) & 1) ~= 0);
  line_address = line_address - 2;
  parametros_deseados = 0;
  for (i=0::i++)
  {   line_address = line_address + 5;
      if (line_address->0 == TOKEN_FINAL) break;
      linea_token-->i = line_address;
      AnalizarToken(line_address);
      if (ttipo_encontrado ~= TT_PREPOSICION) parametros_deseados++;
      linea_tipot-->i = ttipo_encontrado;
      linea_tdatos-->i = tdatos_encontrado;
  }
  return line_address + 1;
];
#Endif; ! TARGET_
#Endif;

!  To protect against a bug in early versions of the "Zip" interpreter:
!  Of course, in Glulx, this routine actually performs work.

#Ifdef TARGET_ZCODE;

[ Tokenise__ b p; b->(2 + b->1) = 0; @tokenise b p; ];

#Ifnot; ! TARGET_GLULX

Array gg_tokenbuf -> DICT_WORD_SIZE;

[ GGWordCompare str1 str2 ix jx;
  for (ix=0 : ix < DICT_WORD_SIZE : ix++) {
    jx = (str1->ix) - (str2->ix);
    if (jx ~= 0)
      return jx;
  }
  return 0;
];

[ Tokenise__ buf tab
    cx numwords len bx ix wx wpos wlen val res dictlen entrylen;
  len = buf-->0;
  buf = buf+WORDSIZE;

  ! First, split the buffer up into words. We use the standard Infocom
  ! list of word separators (comma, period, double-quote).

  cx = 0;
  numwords = 0;
  while (cx < len) {
    while (cx < len && buf->cx == ' ')
      cx++;
    if (cx >= len)
      break;
    bx = cx;
    if (buf->cx == '.' or ',' or '"')
      cx++;
    else {
      while (cx < len && buf->cx ~= ' ' or '.' or ',' or '"')
        cx++;
    }
    tab-->(numwords*3+2) = (cx-bx);
    tab-->(numwords*3+3) = WORDSIZE+bx;
    numwords++;
    if (numwords >= MAX_BUFFER_WORDS)
      break;
  }
  tab-->0 = numwords;

  ! Now we look each word up in the dictionary.

  dictlen = #dictionary_table-->0;
  entrylen = DICT_WORD_SIZE + 7;

  for (wx=0 : wx < numwords : wx++) {
    wlen = tab-->(wx*3+2);
    wpos = tab-->(wx*3+3);

    ! Copy the word into the gg_tokenbuf array, clipping to DICT_WORD_SIZE
    ! characters and lower case.
    if (wlen > DICT_WORD_SIZE)
      wlen = DICT_WORD_SIZE;
    cx = wpos-WORDSIZE;
    for (ix=0 : ix < wlen : ix++)
      ! [080625] No es necesario pasar otra vez a minúscula
      ! gg_tokenbuf->ix = glk($00A0, buf->(cx+ix)); ! glk_char_to_lower
      gg_tokenbuf->ix = buf->(cx + ix);
    for ( : ix < DICT_WORD_SIZE : ix++)
      gg_tokenbuf->ix = 0;

    val = #dictionary_table + WORDSIZE;
    @binarysearch gg_tokenbuf DICT_WORD_SIZE val entrylen dictlen
      1 1 res;
    tab-->(wx*3+1) = res;
  }
];

#Endif; ! TARGET_GLULX

! ============================================================================
!  The ParserInform object abstracts the front end of the parser.
!
!  ParserInform.parse_input(results)
!  returns only when a sensible request has been made, and puts into the
!  "results" buffer:
!
!  --> 0 = The accion number
!  --> 1 = Number of parametros
!  --> 2, 3, ... = The parametros (object numbers), but
!                  0 means "put the multiple object list here"
!                  1 means "put one of the special numbers here"
!
! ----------------------------------------------------------------------------

Object ParserInform "(Parser de Inform)"
  with parse_input
       [ results; Parser__parse(results);
       ], has propio;

! ----------------------------------------------------------------------------
!  The Teclado routine actually receives the jugador's words,
!  putting the words in "a_buffer" and their dictionary addresses in
!  "a_table".  It is assumed that the table is the same one on each
!  (standard) call.
!
!  It can also be used by miscellaneous routines in the game to ask
!  yes-no questions and the like, without invoking the rest of the parser.
!
!  Return the number of words typed
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

[ KeyboardPrimitive  a_buffer a_table;
  read a_buffer a_table;
];

#Ifnot; ! TARGET_GLULX

[ KeyCharPrimitive win nostat done res ix jx ch;
  jx = ch; ! squash compiler warnings
  if (win == 0)
    win = gg_mainwin;
#Ifdef DEBUG;
  if (gg_commandstr ~= 0 && gg_command_reading ~= false) {
    ! get_line_stream
    done = glk($0091, gg_commandstr, gg_arguments, 31);
    if (done == 0) {
      glk($0044, gg_commandstr, 0); ! stream_close
      gg_commandstr = 0;
      gg_command_reading = false;
      ! fall through to normal user input.
    }
    else {
      ! Trim the trailing newline
      if (gg_arguments->(done-1) == 10)
        done = done-1;
      res = gg_arguments->0;
      if (res == '\') {
        res = 0;
        for (ix=1 : ix<done : ix++) {
          ch = gg_arguments->ix;
          if (ch >= '0' && ch <= '9') {
            @shiftl res 4 res;
            res = res + (ch-'0');
          }
          else if (ch >= 'a' && ch <= 'f') {
            @shiftl res 4 res;
            res = res + (ch+10-'a');
          }
          else if (ch >= 'A' && ch <= 'F') {
            @shiftl res 4 res;
            res = res + (ch+10-'A');
          }
        }
      }
      jump KCPContinue;
    }
  }
#Endif;
  done = false;
  glk($00D2, win); ! request_char_event
  while (~~done) {
    glk($00C0, gg_event); ! select
    switch (gg_event-->0) {
      5: ! evtype_Arrange
        if (nostat) {
          glk($00D3, win); ! cancel_char_event
          res = $80000000;
          done = true;
          break;
        }
        DibujarLineaEstado();
      2: ! evtype_CharInput
        if (gg_event-->1 == win) {
          res = gg_event-->2;
          done = true;
        }
    }
    ix = HandleGlkEvent(gg_event, 1, gg_arguments);
    if (ix == 2) {
      res = gg_arguments-->0;
      done = true;
    }
    else if (ix == -1) {
      done = false;
    }
  }
#Ifdef DEBUG;
  if (gg_commandstr ~= 0 && gg_command_reading == false) {
    if (res < 32 || res >= 256 || (res == '\' or ' ')) {
      glk($0081, gg_commandstr, '\'); ! put_buffer_char
      done = 0;
      jx = res;
      for (ix=0 : ix<8 : ix++) {
        @ushiftr jx 28 ch;
        @shiftl jx 4 jx;
        ch = ch & $0F;
        if (ch ~= 0 || ix == 7) done = 1;
        if (done) {
          if (ch >= 0 && ch <= 9)
            ch = ch + '0';
          else
            ch = (ch - 10) + 'A';
          glk($0081, gg_commandstr, ch); ! put_buffer_char
        }
      }
    }
    else {
      glk($0081, gg_commandstr, res); ! put_buffer_char
    }
    glk($0081, gg_commandstr, 10); ! put_char_stream (newline)
  }
#Endif;
.KCPContinue;
  return res;
];

[ KeyboardPrimitive  a_buffer a_table done ix;
#Ifdef DEBUG;
  if (gg_commandstr ~= 0 && gg_command_reading ~= false) {
    ! get_line_stream
    done = glk($0091, gg_commandstr, a_buffer+WORDSIZE,
      (INPUT_BUFFER_LEN-WORDSIZE)-1);
    if (done == 0) {
      glk($0044, gg_commandstr, 0); ! stream_close
      gg_commandstr = 0;
      gg_command_reading = false;
      print "[Completada la reproducción de comandos.]^";
      ! fall through to normal user input.
    }
    else {
      ! Trim the trailing newline
      if ((a_buffer+WORDSIZE)->(done-1) == 10)
        done = done-1;
      a_buffer-->0 = done;
      glk($0086, 8); ! set input style
      glk($0084, a_buffer+WORDSIZE, done); ! put_buffer
      glk($0086, 0); ! set normal style
      print "^";
      jump KPContinue;
    }
  }
#Endif;
  done = false;
  glk($00D0, gg_mainwin, a_buffer+WORDSIZE, INPUT_BUFFER_LEN-WORDSIZE,
    0); ! request_line_event
  while (~~done) {
    glk($00C0, gg_event); ! select
    switch (gg_event-->0) {
      5: ! evtype_Arrange
        DibujarLineaEstado();
      3: ! evtype_LineInput
        if (gg_event-->1 == gg_mainwin) {
          a_buffer-->0 = gg_event-->2;
          done = true;
        }
    }
    ix = HandleGlkEvent(gg_event, 0, a_buffer);
    if (ix == 2)
      done = true;
    else if (ix == -1)
      done = false;
  }
#Ifdef DEBUG;
  if (gg_commandstr ~= 0 && gg_command_reading == false) {
    ! put_buffer_stream
    glk($0085, gg_commandstr, a_buffer+WORDSIZE, a_buffer-->0);
    glk($0081, gg_commandstr, 10); ! put_char_stream (newline)
  }
#Endif;
.KPContinue;
  ! [080625] Pasamos todo el buffer a minúscula antes de llamar a Tokenise__
  for (ix = 0: ix < a_buffer-->0: ix++)
    a_buffer->(ix + WORDSIZE) =
      glk($00A0, a_buffer->(ix + WORDSIZE)); ! glk_char_to_lower
  Tokenise__(a_buffer,a_table);
  ! It's time to close any quote window we've got going.
  if (gg_quotewin) {
    glk($0024, gg_quotewin, 0); ! close_window
    gg_quotewin = 0;
  }
];

#Endif; ! TARGET_

[ Teclado  a_buffer a_table  nw i w w2 x1 x2;

    ActualizarEstatus();
    .FreshInput;

!  Save the start of the buffer, in case "oops" needs to restore it
!  to the previous time's buffer

    for (i=0:i<64:i++) oops_workspace->i = a_buffer->i;

!  In case of an array entry corruption that shouldn't happen, but would be
!  disastrous if it did:

#Ifdef TARGET_ZCODE;
   a_buffer->0 = INPUT_BUFFER_LEN;
   a_table->0 = 15;  ! Allow to split input into this many words
#Endif; ! TARGET_

!  Print the prompt, and read in the words and dictionary addresses

    M__L(##Prompt);
    TrasElPrompt();
    #IfV5; DibujarLineaEstado(); #Endif;
    KeyboardPrimitive(a_buffer, a_table);
#Ifdef TARGET_ZCODE;
    nw=a_table->1;
#Ifnot; ! TARGET_GLULX
    nw=a_table-->0;
#Endif; ! TARGET_

!  If the line was blank, get a fresh line
    if (nw == 0)
    { M__L(##Miscelanea,10); jump FreshInput; }

!  Unless the opening word was "oops", return
!  Conveniently, a_table-->1 is the first word in both ZCODE and GLULX.

    w=a_table-->1;
    if (w == OOPS1__WD or OOPS2__WD or OOPS3__WD) jump DoOops;

#IfV5;
!  Undo handling

!  In Graham's 6/9 code, the following line tests (parse->1==1) instead
!  of (nw==1). I believe that's wrong. In particular, it prevents "undo"
!  from working during "Which do you mean...?" disambiguation, because
!  input at that prompt goes into parse2 instead of parse.

    if ((w == ANULAR1__WD or ANULAR2__WD or ANULAR3__WD) && (nw==1))
    {   if (turnos==1)
        {   M__L(##Miscelanea,11); jump FreshInput;
        }
        if (bandera_deshacer==0)
        {   M__L(##Miscelanea,6); jump FreshInput;
        }
        if (bandera_deshacer==1) jump UndoFailed;
#Ifdef TARGET_ZCODE;
        ! The just_undone check shouldn't be done in Glulx, as multiple
        ! undo is possible.
        if (just_undone==1)
        {   M__L(##Miscelanea,12); jump FreshInput;
        }
        @restore_undo i;
#Ifnot; ! TARGET_GLULX
        @restoreundo i;
        i = (~~i);
#Endif; ! TARGET_
        if (i==0)
        {   .UndoFailed;
            M__L(##Miscelanea,7);
        }
        jump FreshInput;
    }
#Ifdef TARGET_ZCODE;
    @save_undo i;
#Ifnot; ! TARGET_GLULX
    @saveundo i;
    if (i == -1) {
        GGRecoverObjects();
        i = 2;
    }
    else
        i = (~~i);
#Endif; ! TARGET_
    just_undone=0;
    bandera_deshacer=2;
    if (i==-1) bandera_deshacer=0;
    if (i==0) bandera_deshacer=1;
    if (i==2)
    {
#Ifdef TARGET_ZCODE;
        style bold;
#Ifnot; ! TARGET_GLULX
        glk($0086, 4); ! set subheader style
#Endif; ! TARGET_
        print (name) localizacion, "^";
#Ifdef TARGET_ZCODE;
        style roman;
#Ifnot; ! TARGET_GLULX
        glk($0086, 0); ! set normal style
#Endif; ! TARGET_
        M__L(##Miscelanea,13);
        just_undone=1;
        jump FreshInput;
    }
#Endif;

    return nw;

    .DoOops;
    if (eepa_desde == 0)
    {   M__L(##Miscelanea,14); jump FreshInput; }
    if (nw == 1)
    {   M__L(##Miscelanea,15); jump FreshInput; }
    if (nw > 2)
    {   M__L(##Miscelanea,16); jump FreshInput; }

!  So now we know: there was a previous mistake, and the jugador has
!  attempted to correct a single word of it.

    for (i=0:i<INPUT_BUFFER_LEN:i++) buffer2->i = a_buffer->i;
#Ifdef TARGET_ZCODE;
    x1 = a_table->9; ! Start of word following "oops"
    x2 = a_table->8; ! Length of word following "oops"
#Ifnot; ! TARGET_GLULX
    x1 = a_table-->6; ! Start of word following "oops"
    x2 = a_table-->5; ! Length of word following "oops"
#Endif; ! TARGET_

!  Repair the buffer to the text that was in it antes the "oops"
!  was typed:

    for (i=0:i<64:i++) a_buffer->i = oops_workspace->i;
    Tokenise__(a_buffer,a_table);

!  Work out the position in the buffer of the word to be corrected:

#Ifdef TARGET_ZCODE;
    w = a_table->(4*eepa_desde + 1); ! Start of word to go
    w2 = a_table->(4*eepa_desde);    ! Length of word to go
#Ifnot; ! TARGET_GLULX
    w = a_table-->(3*eepa_desde);      ! Start of word to go
    w2 = a_table-->(3*eepa_desde - 1); ! Length of word to go
#Endif; ! TARGET_

!  Write spaces over the word to be corrected:

    for (i=0:i<w2:i++) a_buffer->(i+w) = ' ';

    if (w2 < x2)
    {   ! If the replacement is longer than the original, move up...

        for (i=INPUT_BUFFER_LEN-1:i>=w+x2:i--)
            a_buffer->i = a_buffer->(i-x2+w2);

        ! ...increasing buffer size accordingly.

#Ifdef TARGET_ZCODE;
        a_buffer->1 = (a_buffer->1) + (x2-w2);
#Ifnot; ! TARGET_GLULX
        a_buffer-->0 = (a_buffer-->0) + (x2-w2);
#Endif; ! TARGET_

    }

!  Write the correction in:

    for (i=0:i<x2:i++) a_buffer->(i+w) = buffer2->(i+x1);

    Tokenise__(a_buffer,a_table);
#Ifdef TARGET_ZCODE;
    nw=a_table->1;
#Ifnot; ! TARGET_GLULX
    nw=a_table-->0;
#Endif; ! TARGET_

    return nw;
];



! ----------------------------------------------------------------------------
!  To simplify the picture a little, a rough map of the main routine:
!
!  (A)    Get the input, do "oops" and "again"
!  (B)    Is it a direction, and so an implicit "go"?  If so go to (K)
!  (C)    Is anyone being addressed?
!  (D)    Get the verb: try all the syntax lines for that verb
!  (E)    Break down a syntax line into analysed tokens
!  (F)    Look ahead for advance warning for multiexcept/multiinside
!  (G)    Parse each token in turn (calling InterpretarToken to do most of the work)
!  (H)    Cheaply parse otherwise unrecognised conversation and return
!  (I)    Print best possible error message
!  (J)    Retry the whole lot
!  (K)    Last thing: check for "then" and further instructions(s), return.
!
!  The strategic points (A) to (K) are marked in the commentary.
!
!  Note that there are three different places where a return can happen.
! ----------------------------------------------------------------------------

[ Parser__parse  results   syntax line num_lines line_address i j k
                           token l m;

!  **** (A) ****

!  Firstly, in "not held" mode, we still have a command left over from last
!  time (eg, the user typed "eat biscuit", which was parsed as "take biscuit"
!  last time, with "eat biscuit" tucked away until now).  So we return that.

    if (modo_noposeido==1)
    {   for (i=0:i<8:i++) results-->i=resultados_guardados-->i;
        modo_noposeido=0; rtrue;
    }

    if (modo_mantenido==1)
    {   modo_mantenido=0;
        Tokenise__(buffer,parse);
        jump ReParse;
    }

  .ReType;

    Teclado(buffer,parse);

  .ReParse;

    parser_inflexion = nombre;

!  Initially assume the command is aimed at the jugador, and the verb
!  is the first word

#Ifdef TARGET_ZCODE;
    num_palabras=parse->1;
#Ifnot; ! TARGET_GLULX
    num_palabras=parse-->0;
#Endif; ! TARGET_
    np=1;
#Ifdef IdiomaAInformes;
    IdiomaAInformes();
#IfV5;
!   Re-tokenise:
    Tokenise__(buffer,parse);
#Endif;
#Endif;

    AntesDelParsing();
#Ifdef TARGET_ZCODE;
    num_palabras=parse->1;
#Ifnot; ! TARGET_GLULX
    num_palabras=parse-->0;
#Endif; ! TARGET_

    k=0;
#Ifdef DEBUG;
    if (parser_trace>=2)
    {   print "[ ";
        for (i=0:i<num_palabras:i++)
        {
#Ifdef TARGET_ZCODE;
            j=parse-->(i*2 + 1);
#Ifnot; ! TARGET_GLULX
            j=parse-->(i*3 + 1);
#Endif; ! TARGET_
            k=DireccionDePalabra(i+1);
            l=LongitudDePalabra(i+1);
            print "~"; for (m=0:m<l:m++) print (char) k->m; print "~ ";

            if (j == 0) print "?";
            else
            {
#Ifdef TARGET_ZCODE;
                if (CompararSinSigno(j, 0-->4)>=0
                    && CompararSinSigno(j, 0-->2)<0) print (address) j;
                else print j;
#Ifnot; ! TARGET_GLULX
                if (j->0 == $60) print (address) j;
                else print j;
#Endif; ! TARGET_
            }
            if (i ~= num_palabras-1) print " / ";
        }
        print " ]^";
    }
#Endif;
    palabra_verbonum=1;
    actor=jugador;
    localizacion_actor = TopeAlcanzable(jugador);
    gramatica_normal_tras = 0;

  .AlmostReParse;

    token_alcance = 0;
    accion_que_seria = NULL;

!  Begin from what we currently think is the verb word

  .BeginCommand;
    np=palabra_verbonum;
    palabra_verbo = SiguientePalabraParar();

!  If there's no input here, we must have something like
!  "person,".

    if (palabra_verbo==-1)
    {   mejor_tipoerror = ATASCADO_PE; jump GiveError; }

!  Now try for "again" or "g", which are special cases:
!  don't allow "again" if nothing has previously been typed;
!  simply copy the previous text across

    if (palabra_verbo==OTRAVEZ2__WD or OTRAVEZ3__WD) palabra_verbo=OTRAVEZ1__WD;
    if (palabra_verbo==OTRAVEZ1__WD)
    {   if (actor~=jugador)
        {   M__L(##Miscelanea,20); jump ReType; }
#Ifdef TARGET_ZCODE;
        if (buffer3->1==0)
        {   M__L(##Miscelanea,21); jump ReType; }
#Ifnot; ! TARGET_GLULX
        if (buffer3-->0==0)
        {   M__L(##Miscelanea,21); jump ReType; }
#Endif; ! TARGET_
        for (i=0:i<INPUT_BUFFER_LEN:i++) buffer->i=buffer3->i;
        jump ReParse;
    }

!  Save the present input in case of an "again" next time

    if (palabra_verbo~=OTRAVEZ1__WD)
        for (i=0:i<INPUT_BUFFER_LEN:i++) buffer3->i=buffer->i;

    if (gramatica_normal_tras==0)
    {   i = EjecutarRutinas(actor, gramatica);
        #Ifdef DEBUG;
        if (parser_trace>=2 && actor.gramatica~=0 or NULL)
            print " [La propiedad Gramatica ha retornado ", i, "]^";
        #Endif;
        if (i<0) { gramatica_normal_tras = palabra_verbonum; i=-i; }
        if (i == 1) {
            results-->0 = accion;
            results-->1 = 2;  ! [080625] Aquí va el número de parámetros
            results-->2 = uno;
            results-->3 = otro;
            rtrue;
        }
        if (i~=0) { palabra_verbo = i; np--; palabra_verbonum--; }
        else
        {   np = palabra_verbonum; palabra_verbo=SiguientePalabra();
        }
    }
    else gramatica_normal_tras=0;

!  **** (B) ****

    #Ifdef IdiomaEsVerbo;
    if (palabra_verbo==0)
    {   i = np; palabra_verbo=IdiomaEsVerbo(buffer, parse, palabra_verbonum);
        np = i;
    }
    #Endif;

!  If the first word is not listed as a verb, it must be a direction
!  or the nombre of someone to talk to

    if (palabra_verbo==0 || ((palabra_verbo->#dict_par1) & 1) == 0)
    {

!  So is the first word an object contained in the special object "compass"
!  (i.e., a direction)?  This needs use of DominioNombre, a routine which
!  does the object matching, returning the object number, or 0 if none found,
!  or CODIGO_REPARSE if it has restructured the parse table so the whole parse
!  must be begun again...

        np=palabra_verbonum; modo_indef = false; filtro_token = 0;
        l=DominioNombre(Brujula,0,0); if (l==CODIGO_REPARSE) jump ReParse;

!  If it is a direction, send back the results:
!  accion=IrSub, no of arguments=1, argument 1=the direction.

        if (l~=0)
        {   results-->0 = ##Ir;
            accion_que_seria = ##Ir;
            results-->1 = 1;
            results-->2 = l;
            jump LookForMore;
        }

!  **** (C) ****

!  Only check for a comma (a "someone, do something" command) if we are
!  not already in the middle of one.  (This simplification stops us from
!  worrying about "robot, wizard, you are an idiot", telling the robot to
!  tell the wizard that she is an idiot.)

        if (actor==jugador)
        {   for (j=2:j<=num_palabras:j++)
            {   i=SiguientePalabra(); if (i==palabra_coma) jump Conversation;
            }

            palabra_verbo=VerboDesconocido(palabra_verbo);
            if (palabra_verbo~=0) jump VerbAccepted;
        }

        mejor_tipoerror=VERBO_PE; jump GiveError;

!  SiguientePalabra nudges the word number np on by one each time, so we've now
!  advanced past a comma.  (A comma is a word all on its own in the table.)

      .Conversation;
        j = np - 1;
        if (j==1) { M__L(##Miscelanea,22); jump ReType; }

!  Use DominioNombre (in the context of "animado creature") to see if the
!  words make sense as the nombre of someone held or nearby

        np=1; elsiguiente=TOKEN_POSEIDO;
        razon_alcance = RAZON_HABLAR;
        l=DominioNombre(jugador,localizacion_actor,6);
        razon_alcance = RAZON_PARSING;
        if (l==CODIGO_REPARSE) jump ReParse;

        if (l==0) { M__L(##Miscelanea,23); jump ReType; }

!  The object addressed must at least be "hablable" if not actually "animado"
!  (the distinction allows, for instance, a microphone to be spoken to,
!  without the parser thinking that the microphone is human).

        if (l hasnt animado && l hasnt hablable)
        {   M__L(##Miscelanea, 24, l); jump ReType; }

!  Check that there aren't any mystery words between the end of the person's
!  nombre and the comma (eg, throw out "dwarf sdfgsdgs, go north").

        if (np~=j)
        {   M__L(##Miscelanea, 25); jump ReType; }

!  The jugador has now successfully named someone.  Adjust "him", "her", "it":

        ActualizarPronombre(l);

!  Set the global variable "actor", adjust the number of the first word,
!  and begin parsing again from there.

        palabra_verbonum=j+1;

!  Stop things like "me, again":

        if (l == jugador)
        {   np = palabra_verbonum;
            if (SiguientePalabraParar() == OTRAVEZ1__WD or OTRAVEZ2__WD or OTRAVEZ3__WD)
            {   M__L(##Miscelanea,20); jump ReType;
            }
        }

        actor=l;
        localizacion_actor=TopeAlcanzable(l);
        #Ifdef DEBUG;
        if (parser_trace>=1)
            print "[El actor es ", (the) actor, " que está en ",
                (name) localizacion_actor, "]^";
        #Endif;
        jump BeginCommand;
    }


!  **** (D) ****

   .VerbAccepted;

!  We now definitely have a verb, not a direction, whether we got here by the
!  "take ..." or "person, take ..." method.  Get the meta flag for this verb:

    meta=((palabra_verbo->#dict_par1) & 2)/2;

!  You can't order other people to "full score" for you, and so on...

    if (meta==1 && actor~=jugador)
    {   mejor_tipoerror=VERBO_PE; meta=0; jump GiveError; }

!  Now let i be the corresponding verb number, stored in the dictionary entry
!  (in a peculiar 255-n fashion for traditional Infocom reasons)...

    i=$ff-(palabra_verbo->#dict_par2);

!  ...then look up the i-th entry in the verb table, whose address is at word
!  7 in the Z-machine (in the header), so as to get the address of the syntax
!  table for the given verb...

#Ifdef TARGET_ZCODE;
    syntax=(0-->7)-->i;
#Ifnot; ! TARGET_GLULX
    syntax=(#grammar_table)-->(i+1);
#Endif; ! TARGET_

!  ...and then see how many lines (ie, different patrons corresponding to the
!  same verb) are stored in the parse table...

    num_lines = (syntax -> 0) - 1;

!  ...and now go through them all, one by one.
!  To prevent palabra_pronombre 0 being misunderstood,

   palabra_pronombre=NULL; objeto_pronombre=NULL;

   #Ifdef DEBUG;
   if (parser_trace>=1)
        print "[Interpretando el verbo '", (address) palabra_verbo,
              "' (", num_lines+1, " líneas)]^";
   #Endif;

   mejor_tipoerror=ATASCADO_PE; proxmejor_tipoerror=ATASCADO_PE;

!  "mejor_tipoerror" is the current failure-to-match error - it is by default
!  the least informative one, "don't understand that sentence".
!  "proxmejor_tipoerror" remembers the best alternative to having to ask a
!  scope token for an error message (i.e., the best not counting PREGUNTAAMBITO_PE).


!  **** (E) ****

    line_address = syntax + 1;

    for (line=0:line<=num_lines:line++)
    {
        for (i = 0 : i < 32 : i++)
        {   linea_token-->i = TOKEN_FINAL;
            linea_tipot-->i = TT_ELEMENTAL;
            linea_tdatos-->i = TOKEN_FINAL;
        }

!  Unpack the syntax line from Inform format into three arrays; ensure that
!  the sequence of tokens ends in an TOKEN_FINAL.

        line_address = DesempaquetarLineaGramatica(line_address);

        #Ifdef DEBUG;
        if (parser_trace >= 1)
        {   if (parser_trace >= 2) new_line;
            print "[línea ", line; DepurarLineaGramatica();
            print "]^";
        }
        #Endif;

!  We aren't in "not holding" or inferring modes, and haven't entered
!  any parametros on the line yet, or any special numbers; the multiple
!  object is still empty.

        no_poseido=0;
        deducedesde=0;
        parametros=0;
        nsns=0; palabra_especial=0; numero_especial=0;
        objeto_multiple-->0 = 0;
        multi_contexto = 0;
        tipoerror=ATASCADO_PE;

!  Put the word marker back to just despues the verb

        np=palabra_verbonum+1;

!  **** (F) ****
!  There are two special cases where parsing a token now has to be
!  affected by the result of parsing another token later, and these
!  two cases (multiexcept and multiinside tokens) are helped by a quick
!  look ahead, to work out the future token now.  We can only carry this
!  out in the simple (but by far the most common) case:
!
!      multiexcept <one or more prepositions> noun
!
!  and similarly for multiinside.

        aviso_avanzar = NULL; modo_indef = false;
        for (i=0,m=false,contadorp=0:linea_token-->contadorp ~= TOKEN_FINAL:contadorp++)
        {   token_alcance = 0;

            if (linea_tipot-->contadorp ~= TT_PREPOSICION) i++;

            if (linea_tipot-->contadorp == TT_ELEMENTAL)
            {      if (linea_tdatos-->contadorp == TOKEN_MULTI)
 		    m=true;
	         ! [001115] Añadida la comprobación TOKEN_MULTIPOSEIDO
		 ! para capturar correctamente el caso DEJA TODO
		 if (linea_tdatos-->contadorp == TOKEN_MULTIPOSEIDO) {
		     m=true;
		     indef_propietario=actor;
		 }
                if (linea_tdatos-->contadorp
                    == TOKEN_MULTIEXCEPTO or TOKEN_MULTIDENTRO  && i==1)
                {   !   First non-preposition is "multiexcept" or
                    !   "multiinside", so look ahead.

                    #Ifdef DEBUG;
                    if (parser_trace>=2) print " [Intentando anticipar]^";
                    #Endif;

                    !   We need this to be followed by 1 or more prepositions.

                    contadorp++;
                    if (linea_tipot-->contadorp == TT_PREPOSICION)
                    {   while (linea_tipot-->contadorp == TT_PREPOSICION)
                            contadorp++;

                        if ((linea_tipot-->contadorp == TT_ELEMENTAL)
                            && (linea_tdatos-->contadorp == TOKEN_NOMBRE))
                        {
                            !  Advance past the last preposition

                            while (np <= num_palabras)
                            {   if (SiguientePalabra() == linea_tdatos-->(contadorp-1))
                                {   l = DominioNombre(localizacion_actor, actor,
                                            TOKEN_NOMBRE);
                                    #Ifdef DEBUG;
                                    if (parser_trace>=2)
                                    {   print " [Avanzando hasta el token ~noun~: ";
                                        if (l==CODIGO_REPARSE)
                                            print "petición de re-interpretar]^";
                                        if (l==1) print "pero se ha
					    encontrado múltiple]^";
                                        if (l==0) print "error ", tipoerror, "]^";
                                        if (l>=2) print (the) l, "]^";
                                    }
                                    #Endif;
                                    if (l==CODIGO_REPARSE) jump ReParse;
                                    if (l>=2) aviso_avanzar = l;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }

!  Slightly different line-parsing rules will apply to "take multi", to
!  prevent "take all" behaving correctly but misleadingly when there's
!  nothing to take.

        regla_coger_todo = 0;
        if (m && parametros_deseados==1 && (accion_que_seria==##Coger
	    or ##Dejar))
            regla_coger_todo = 1;

!  And now start again, properly, forearmed or not as the case may be.
!  As a precaution, we clear all the variables again (they may have been
!  disturbed by the call to DominioNombre, which may have called outside
!  code, which may have done anything!).

        no_poseido=0;
        deducedesde=0;
        parametros=0;
        nsns=0; palabra_especial=0; numero_especial=0;
        objeto_multiple-->0 = 0;
        tipoerror=ATASCADO_PE;
        np=palabra_verbonum+1;

!  **** (G) ****
!  "Patron" gradually accumulates what has been recognised so far,
!  so that it may be reprinted by the parser later on

        for (contadorp=1::contadorp++)
        {   patron-->contadorp = PATRON_NULO; token_alcance=0;

            token = linea_token-->(contadorp-1);
            elsiguiente = linea_token-->contadorp;

            #Ifdef DEBUG;
            if (parser_trace >= 2)
               print " [línea ", line, " token ", contadorp, " palabra ", np, " : ",
                     (DepurarToken) token, "]^";
            #Endif;

            if (token ~= TOKEN_FINAL)
            {   razon_alcance = RAZON_PARSING;
                parser_inflexion = nombre;
                AnalizarToken(token);
                l = ParseToken__(ttipo_encontrado, tdatos_encontrado, contadorp-1, token);
                while (l<-200) l = ParseToken__(TT_ELEMENTAL, l + 256);
                razon_alcance = RAZON_PARSING;

                if (l==RPG_PREPOSICION)
                {   if (ttipo_encontrado~=TT_PREPOSICION
                        && (ttipo_encontrado~=TT_ELEMENTAL
                            || tdatos_encontrado~=TOKEN_TEMA)) parametros_deseados--;
                    l = true;
                }
                else
                if (l<0) l = false;
                else
                if (l~=RPG_REPARSE)
                {   if (l==RPG_NUMERO)
                    {   if (nsns==0) numero_especial1=numero_interpretado;
                        else numero_especial2=numero_interpretado;
                        nsns++; l = 1;
                    }
                    if (l==RPG_MULTIPLE) l = 0;
                    results-->(parametros+2) = l;
                    parametros++;
                    patron-->contadorp = l;
                    l = true;
                }

                #Ifdef DEBUG;
                if (parser_trace >= 3)
                {   print "  [el token ha ";
                    if (l==CODIGO_REPARSE) print "causado petición de reinterpretar]^";
                    if (l==0) print "causado fallo con error ", tipoerror, "]^";
                    if (l==1) print "sido interpretado con éxito]^";
                }
                #Endif;

                if (l==CODIGO_REPARSE) jump ReParse;
                if (l==false) break;
            }
            else
            {

!  If the jugador has entered enough already but there's still
!  text to wade through: store the patron away so as to be able to produce
!  a decent error message if this turnos out to be the best we ever manage,
!  and in the mean time give up on this line

!  However, if the superfluous text begins with a comma or "then" then
!  take that to be the start of another instruction

                if (np <= num_palabras)
                {   l=SiguientePalabra();
                    if (l==DESPUES1__WD or DESPUES2__WD or
			DESPUES3__WD or palabra_coma
			or Y1__WD or Y2__WD or Y3__WD)
                    {   modo_mantenido=1; mant_np=np-1; }
                    else
                    {   for (m=0:m<32:m++) patron2-->m=patron-->m;
                        contadorp2=contadorp;
                        tipoerror=HASTAQUI_PE; break;
                    }
                }

!  Now, we may need to revise the multiple object because of the single one
!  we now know (but didn't when the list was drawn up).

                if (parametros>=1 && results-->2 == 0)
                {   l=RevisarMulti(results-->3);
                    if (l~=0) { tipoerror=l; break; }
                }
                if (parametros>=2 && results-->3 == 0)
                {   l=RevisarMulti(results-->2);
                    if (l~=0) { tipoerror=l; break; }
                }

!  To trap the case of "take all" inferring only "yourself" when absolutely
!  nothing else is in the vicinity...
                if (regla_coger_todo==2 && results-->2 == actor)
                {   mejor_tipoerror = NADA_PE; jump GiveError;
                }

                #Ifdef DEBUG;
                if (parser_trace>=1)
                    print "[Línea interpretada con éxito]^";
                #Endif;

!  The line has successfully matched the text.  Declare the input error-free...

                eepa_desde = 0;

!  ...explain any inferences made (using the patron)...
#Ifdef IMPRIMIR_DEDUCCIONES;
                if (deducedesde~=0)
                {   print "("; ImprimirComando(deducedesde); print ")^";
                }
#Endif;
!  ...copy the accion number, and the number of parametros...

                results-->0 = accion_que_seria;
                results-->1 = parametros;

!  ...reverse first and otro parametros if need be...

                if (accion_invertida && parametros==2)
                {   i = results-->2; results-->2 = results-->3;
                    results-->3 = i;
                    if (nsns == 2)
                    {   i = numero_especial1; numero_especial1=numero_especial2;
                        numero_especial2=i;
                    }
                }

!  ...and to reset "it"-style objects to the first of these parametros, if
!  there is one (and it really is an object)...

                if (parametros > 0 && results-->2 >= 2)
                    ActualizarPronombre(results-->2);

!  ...and worry about the case where an object was allowed as a parameter
!  even though the jugador wasn't holding it and should have been: in this
!  event, keep the results for next time round, go into "not holding" mode,
!  and for now tell the jugador what's happening and return a "take" request
!  instead...

                if (no_poseido~=0 && actor==jugador)
                {   modo_noposeido=1;
                    for (i=0:i<8:i++) resultados_guardados-->i = results-->i;
                    results-->0 = ##Coger;
                    results-->1 = 1;
                    results-->2 = no_poseido;
                    M__L(##Miscelanea, 26, no_poseido);
                }

!  (Notice that implicit takes are only generated for the jugador, and not
!  for other actors.  This avoids entirely logical, but misleading, text
!  being printed.)

!  ...and return from the parser altogether, having successfully matched
!  a line.

                if (modo_mantenido==1) { np=mant_np; jump LookForMore; }
                rtrue;
            }
        }

!  The line has failed to match.
!  We continue the outer "for" loop, trying the next line in the gramatica.

        if (tipoerror>mejor_tipoerror) mejor_tipoerror=tipoerror;
        if (tipoerror~=PREGUNTAAMBITO_PE && tipoerror>proxmejor_tipoerror)
          proxmejor_tipoerror=tipoerror;

!  ...unless the line was something like "take all" which failed because
!  nothing matched the "all", in which case we stop and give an error now.

        if (regla_coger_todo == 2 && mejor_tipoerror==NADA_PE) break;

! Añadido para evitar que DEJA TODO cause problemas cuando no hay nada
! qué dejar

        if (accion_que_seria == ##Dejar && mejor_tipoerror==NADA_PE) break;
   }

!  The gramatica is exhausted: every line has failed to match.

!  **** (H) ****

  .GiveError;
        tipoerror=mejor_tipoerror;

!  Errors are handled differently depending on who was talking.

!  If the command was addressed to somebody else (eg, "dwarf, sfgh") then
!  it is taken as conversation which the parser has no business in disallowing.

    if (actor~=jugador)
    {   if (gramatica_normal_tras>0)
        {   palabra_verbonum = gramatica_normal_tras;
            jump AlmostReParse;
        }
        np=palabra_verbonum;
        palabra_especial=SiguientePalabra();
        if (palabra_especial==palabra_coma)
        {   palabra_especial=SiguientePalabra();
            palabra_verbonum++;
        }
        numero_especial=IntentarNumero(palabra_verbonum);
        results-->0=##NoComprendido;
        results-->1=2;
        results-->2=1; numero_especial1=palabra_especial;
        results-->3=actor;
        consultar_desde = palabra_verbonum; consultar_num_palabras = num_palabras-consultar_desde+1;
        rtrue;
    }

!  **** (I) ****

!  If the jugador was the actor (eg, in "take dfghh") the error must be printed,
!  and fresh input called for.  In three cases the oops word must be jiggled.

    if (ErrorParser(tipoerror)~=0) jump ReType;
    palabra_pronombre = palabra__pronombre; objeto_pronombre = objeto__pronombre;

    if (tipoerror==ATASCADO_PE)   { M__L(##Miscelanea, 27); eepa_desde=1; }
    if (tipoerror==HASTAQUI_PE) {

       if (parser_listo)
         {
          for (m=0:m<32:m++) patron-->m = patron2-->m;
              contadorp=contadorp2;
         }

!         accion=accion_que_seria;
!         uno=results-->2;
!         otro=results-->3;

    #Ifdef DEBUG;
         if (parser_trace>0)
           print "[Entendido sólo hasta la palabra número ", eepa_desde,".]^";
    #Endif;

         M__L(##Miscelanea, 28);
         if (si_pl)                     ! 030305
           {
             modo_mantenido=0;
             num_palabras=eepa_desde;
             np=1;
           #Ifdef DEBUG;
             if (parser_trace>0)
               print "[Reparseando hasta la palabra número ",num_palabras,".]^";
           #Endif;
             jump AlmostReParse;
           }
    }
    if (tipoerror==NUMERO_PE)  M__L(##Miscelanea, 29);
    if (tipoerror==NOVEO_PE) { M__L(##Miscelanea, 30); eepa_desde=eepa_guardado; }
    if (tipoerror==MUYPOCO_PE)  M__L(##Miscelanea, 31);
    if (tipoerror==NOTIENES_PE) { M__L(##Miscelanea, 32); eepa_desde=eepa_guardado; }
    if (tipoerror==MULTI_PE)   M__L(##Miscelanea, 33);
    if (tipoerror==MMULTI_PE)  M__L(##Miscelanea, 34);
    if (tipoerror==PRONOM_PE)   M__L(##Miscelanea, 35);
    if (tipoerror==EXCEPTO_PE)  M__L(##Miscelanea, 36);
    if (tipoerror==ANIMA_PE)   M__L(##Miscelanea, 37);
    if (tipoerror==VERBO_PE)    M__L(##Miscelanea, 38);
    if (tipoerror==ESCENARIO_PE) M__L(##Miscelanea, 39);
    if (tipoerror==YANOPRON_PE)
    {   if (objeto_pronombre == NULL) M__L(##Miscelanea, 35);
                            else M__L(##Miscelanea, 40);
    }
    if (tipoerror==KKFINAL_PE) M__L(##Miscelanea, 41);
    if (tipoerror==HAYPOCOS_PE)  M__L(##Miscelanea, 42, multi_hallado);
    if (tipoerror==NADA_PE) { if (multi_esperado==100) M__L(##Miscelanea, 43);
                             else M__L(##Miscelanea, 44);  }

    if (tipoerror==PREGUNTAAMBITO_PE)
    {   estadio_alcance=3;
        if (indirect(error_alcance)==-1)
        {   mejor_tipoerror=proxmejor_tipoerror; jump GiveError;  }
    }

!  **** (J) ****

!  And go (almost) right back to square one...

    jump ReType;

!  ...being careful not to go all the way back, to avoid infinite repetition
!  of a deferred command causing an error.


!  **** (K) ****

!  At this point, the return value is all prepared, and we are only looking
!  to see if there is a "then" followed by subsequent instruction(s).

   .LookForMore;

   if (np>num_palabras) rtrue;

   i=SiguientePalabra();
   if (i==DESPUES1__WD or DESPUES2__WD or DESPUES3__WD or palabra_coma)
   {   if (np>num_palabras)
       {   modo_mantenido = false; return; }
       i = DireccionDePalabra(palabra_verbonum);
       j = DireccionDePalabra(np);
       for (:i<j:i++) i->0 = ' ';
       i = SiguientePalabra();
       if (i==OTRAVEZ1__WD or OTRAVEZ2__WD or OTRAVEZ3__WD)
       {   !   Delete the words "then again" from the again buffer,
           !   in which we have just realised that it must occur:
           !   prevents an infinite loop on "i. again"

           i = DireccionDePalabra(np-2)-buffer;
           if (np > num_palabras) j = INPUT_BUFFER_LEN-1;
           else j = DireccionDePalabra(np)-buffer;
           for (:i<j:i++) buffer3->i = ' ';
       }
       Tokenise__(buffer,parse); modo_mantenido = true; return;
   }
   mejor_tipoerror=HASTAQUI_PE; jump GiveError;
];

[ TopeAlcanzable person act;
  act = parent(person); if (act == 0) return person;
  if (person == jugador && localizacion == LaOscuridad) return LaOscuridad;
  while (parent(act)~=0
         && (act has transparente || act has soporte
             || (act has recipiente && act has abierto)))
      act = parent(act);
  return act;
];

! ----------------------------------------------------------------------------
!  Descriptores()
!
!  Handles descriptive words like "my", "his", "another" and so on.
!  Skips "the", and leaves np pointing to the first misunderstood word.
!
!  Allowed to set up for a plural only if allow_p is set
!
!  Returns error number, or 0 if no error occurred
! ----------------------------------------------------------------------------

Constant OTRO_BIT  =   1;     !  These will be used in Adjudicate()
Constant MI_BIT     =   2;     !  to disambiguate choices
Constant ESO_BIT   =   4;
Constant PLURAL_BIT =   8;
Constant ENCENDIDO_BIT    =  16;
Constant APAGADO_BIT  =  32;

[ BorrarDescriptores;
   modo_indef=0; indef_tipo=0; indef_esperado=0; indef_suponer_p=0;
   indef_posibambig = false;
   indef_propietario = nothing;
   indef_casos = $$111111111111;
   indef_numero_en = 0;
];

[ Descriptores allow_multiple  o x flag cto type n;

   BorrarDescriptores();
   if (np > num_palabras) return 0;

   for (flag=true:flag:)
   {   o=SiguientePalabraParar(); flag=false;

       for (x=1:x<=IdiomaDescriptores-->0:x=x+4)
           if (o == IdiomaDescriptores-->x)
           {   flag = true;
               type = IdiomaDescriptores-->(x+2);
               if (type ~= DEFINIDO_PK) modo_indef = true;
               indef_posibambig = true;
               indef_casos = indef_casos & (IdiomaDescriptores-->(x+1));

               if (type == POSESIVO_PK)
               {   cto = IdiomaDescriptores-->(x+3);
                   switch(cto)
                   {  0: indef_tipo = indef_tipo | MI_BIT;
                      1: indef_tipo = indef_tipo | ESO_BIT;
                      default: indef_propietario = ValorDelPronombre(cto);
                        if (indef_propietario == NULL) indef_propietario = ParserInform;
                   }
               }

               if (type == luz)
                   indef_tipo = indef_tipo | ENCENDIDO_BIT;
               if (type == -luz)
                   indef_tipo = indef_tipo | APAGADO_BIT;
           }

       if (o==OTRO1__WD or OTRO2__WD or OTRO3__WD)
                            { modo_indef=1; flag=1;
                              indef_tipo = indef_tipo | OTRO_BIT; }
       if (o==TODO1__WD or TODO2__WD or TODO3__WD or TODO4__WD or TODO5__WD)
                            { modo_indef=1; flag=1; indef_esperado=100;
                              if (regla_coger_todo == 1)
                                  regla_coger_todo = 2;
                              indef_tipo = indef_tipo | PLURAL_BIT; }
       if (permitir_plurales && allow_multiple)
       {   n=IntentarNumero(np-1);
           if (n==1)        { modo_indef=1; flag=1; }
           if (n>1)         { indef_suponer_p=1;
                              modo_indef=1; flag=1; indef_esperado=n;
                              indef_numero_en=np-1;
                              indef_tipo = indef_tipo | PLURAL_BIT; }
       }
       if (flag==1
           && SiguientePalabraParar() ~= DE1__WD or DE2__WD or DE3__WD or DE4__WD)
           np--;  ! Skip 'of' despues these
   }
   np--;
   if ((indef_esperado > 0) && (~~allow_multiple)) return MULTI_PE;
   return 0;
];

! ----------------------------------------------------------------------------
!  TestCriatura: Will this person do for a "creature" token?
! ----------------------------------------------------------------------------

[ TestCriatura obj;
  if (obj has animado) rtrue;
  if (obj hasnt hablable) rfalse;
  if (accion_que_seria == ##Preguntar or ##Responder or ##Hablar or ##Pedir) rtrue;
  rfalse;
];

[ CadenaDePreposiciones wd index;
  if (linea_tdatos-->index == wd) return wd;
  if ((linea_token-->index)->0 & $20 == 0) return -1;
  do
  {   if (linea_tdatos-->index == wd) return wd;
      index++;
  }
  until ((linea_token-->index == TOKEN_FINAL)
         || (((linea_token-->index)->0 & $10) == 0));
  return -1;
];

! ----------------------------------------------------------------------------
!  InterpretarToken(type, data):
!      Parses the given token, from the current word number np, with exactly
!      the specification of a general parsing routine.
!      (Except that for "topic" tokens and prepositions, you need to supply
!      a position in a valid gramatica line as third argument.)
!
!  Returns:
!    RPG_REPARSE  for "reconstructed input, please re-parse from scratch"
!    RPG_PREPOSICION  for "token accepted with no result"
!    $ff00 + x    for "please parse InterpretarToken(TT_ELEMENTAL, x) instead"
!    0            for "token accepted, result is the multiple object list"
!    1            for "token accepted, result is the number in numero_interpretado"
!    object num   for "token accepted with this object as result"
!    -1           for "token rejected"
!
!  (A)            Analyse the token; handle all tokens not involving
!                 object lists and break down others into elementary tokens
!  (B)            Begin parsing an object list
!  (C)            Parse descriptors (articulos, pronouns, etc.) in the list
!  (D)            Parse an object nombre
!  (E)            Parse connectives ("and", "but", etc.) and go back to (C)
!  (F)            Return the conclusion of parsing an object list
! ----------------------------------------------------------------------------

[ InterpretarToken given_ttype given_tdata token_n x y;
  x = elsiguiente; elsiguiente = TOKEN_NOMBRE;
  y = ParseToken__(given_ttype,given_tdata,token_n);
  if (y == RPG_REPARSE) Tokenise__(buffer,parse);
  elsiguiente = x; return y;
];

[ ParseToken__ given_ttype given_tdata token_n
             token l o i j k and_parity single_object desc_wn many_flag
             token_allows_multiple;

!  **** (A) ****

   filtro_token = 0;

   switch(given_ttype)
   {   TT_ELEMENTAL:
           switch(given_tdata)
           {   TOKEN_ESPECIAL:
                   l=IntentarNumero(np);
                   palabra_especial=SiguientePalabra();
                   #Ifdef DEBUG;
                   if (l~=-1000)
                       if (parser_trace>=3)
                           print "  [Leido special como el número ", l, "]^";
                   #Endif;
                   if (l==-1000)
                   {   #Ifdef DEBUG;
                       if (parser_trace>=3)
                         print "  [Leida palabra special en la posición ", np, "]^";
                       #Endif;
                       l = palabra_especial;
                   }
                   numero_interpretado = l; return RPG_NUMERO;

               TOKEN_NUMERO:
                   l=IntentarNumero(np++);
                   if (l==-1000) { tipoerror=NUMERO_PE; return RPG_FALLO; }
                   #Ifdef DEBUG;
                   if (parser_trace>=3) print "  [Leído número como ", l, "]^";
                   #Endif;
                   numero_interpretado = l; return RPG_NUMERO;

               TOKEN_CRIATURA:
                   if (accion_que_seria==##Responder or ##Preguntar or ##Pedir or ##Hablar)
                       razon_alcance = RAZON_HABLAR;

               TOKEN_TEMA:
                   consultar_desde = np;
                   if ((linea_tipot-->(token_n+1) ~= TT_PREPOSICION)
                       && (linea_token-->(token_n+1) ~= TOKEN_FINAL))
                       ErrorDeEjecucion(13);
                   do o=SiguientePalabraParar();
                   until (o==-1 || CadenaDePreposiciones(o, token_n+1) ~= -1);
                   np--;
                   consultar_num_palabras = np-consultar_desde;
                   if (consultar_num_palabras==0) return RPG_FALLO;
                   if (accion_que_seria==##Preguntar or ##Responder or ##Hablar)
                   {   o=np; np=consultar_desde; numero_interpretado=SiguientePalabra();
                       #Ifdef EnglishNaturalLanguage;
                       if (numero_interpretado=='the' && consultar_num_palabras>1)
                           numero_interpretado=SiguientePalabra();
                       #Endif;
                       np=o; return 1;
                   }
                   return RPG_PREPOSICION;
           }

       TT_PREPOSICION:
           #Iffalse (Grammar__Version == 1);
!  Is it an unnecessary alternative preposition, when a previous choice
!  has already been matched?
           if ((token->0) & $10) return RPG_PREPOSICION;
           #Endif; ! Grammar__Version

!  If we've run out of the jugador's input, but still have parametros to
!  specify, we go into "infer" mode, remembering where we are and the
!  preposition we are inferring...

           if (np > num_palabras)
           {   if (deducedesde==0 && parametros<parametros_deseados)
               {   deducedesde = contadorp; prepdeducida = token;
                   patron-->contadorp = CODIGO_REPARSE + DirDicc__Num(given_tdata);
               }

!  If we are not inferring, then the line is wrong...

               if (deducedesde==0) return -1;

!  If not, then the line is right but we mark in the preposition...

               patron-->contadorp = CODIGO_REPARSE + DirDicc__Num(given_tdata);
               return RPG_PREPOSICION;
           }

           o = SiguientePalabra();

           patron-->contadorp = CODIGO_REPARSE + DirDicc__Num(o);

!  Whereas, if the jugador has typed something here, see if it is the
!  required preposition... if it's wrong, the line must be wrong,
!  but if it's right, the token is passed (jump to finish this token).

           if (o == given_tdata) return RPG_PREPOSICION;
           #Iffalse (Grammar__Version == 1);
           if (CadenaDePreposiciones(o, token_n) ~= -1)
               return RPG_PREPOSICION;
           #Endif; ! Grammar__Version
           return -1;

       TT_RPG:
           l=indirect(given_tdata);
           #Ifdef DEBUG;
           if (parser_trace>=3)
               print "  [La rutina de parsing de usuario ha retornado ", l, "]^";
           #Endif;
           return l;

       TT_ALCANCE:
           token_alcance = given_tdata;
           estadio_alcance = 1;
           l = indirect(token_alcance);
           #Ifdef DEBUG;
           if (parser_trace>=3)
               print "  [La rutina de alcance ha retornado
		   multiple-flag de ", l, "]^";
           #Endif;
           if (l==1) given_tdata = TOKEN_MULTI; else given_tdata = TOKEN_NOMBRE;

       TT_FILTRO_ATRIB:
           filtro_token = 1 + given_tdata;
           given_tdata = TOKEN_NOMBRE;

       TT_FILTRO_RUTINA:
           filtro_token = given_tdata;
           given_tdata = TOKEN_NOMBRE;
   }

   token = given_tdata;

!  **** (B) ****

!  There are now three possible ways we can be here:
!      parsing an elementary token other than "special" or "number";
!      parsing a scope token;
!      parsing a noun-filter token (either by routine or attribute).
!
!  In each case, token holds the type of elementary parse to
!  perform in matching one or more objects, and
!  filtro_token is 0 (default), an attribute + 1 for an attribute filter
!  or a routine address for a routine filter.

   token_allows_multiple = false;
   if (token == TOKEN_MULTI or TOKEN_MULTIPOSEIDO or TOKEN_MULTIEXCEPTO
                or TOKEN_MULTIDENTRO) token_allows_multiple = true;

   many_flag = false; and_parity = true; no_deducir = false;

!  **** (C) ****
!  We expect to find a list of objects next in what the jugador's typed.

  .ObjectList;

   #Ifdef DEBUG;
   if (parser_trace>=3) print "  [Lista de objetos a partir de la posición ", np, "]^";
   #Endif;

!  Take an advance look at the next word: if it's "it" or "them", and these
!  are unset, set the appropriate error number and give up on the line
!  (if not, these are still parsed in the usual way - it is not assumed
!  that they still refer to something in scope)

    o=SiguientePalabra(); np--;

    palabra_pronombre = NULL; objeto_pronombre = NULL;
    l = ValorDelPronombre(o);
    if (l ~= 0)
    {   palabra_pronombre = o; objeto_pronombre = l;
        if (l == NULL)
        {   !   Don't assume this is a use of an unset pronoun until the
            !   descriptors have been checked, because it might be an
            !   articulo (or some such) instead

            for (l=1:l<=IdiomaDescriptores-->0:l=l+4)
                if (o == IdiomaDescriptores-->l) jump AssumeDescriptor;
            palabra__pronombre=palabra_pronombre; objeto__pronombre=objeto_pronombre;
            tipoerror=PRONOM_PE; return RPG_FALLO;
        }
    }

    .AssumeDescriptor;

    if (o==YO1__WD or YO2__WD or YO3__WD)
    {   palabra_pronombre = o; objeto_pronombre = jugador;
    }

    permitir_plurales = true; desc_wn = np;

    .TryAgain;
!   First, we parse any descriptive words (like "the", "five" or "every"):
    l = Descriptores(token_allows_multiple);
    if (l~=0) { tipoerror=l; return RPG_FALLO; }

    .TryAgain2;

!  **** (D) ****

!  This is an actual specified object, and is therefore where a typing error
!  is most likely to occur, so we set:

    eepa_desde = np;

!  So, two cases.  Case 1: token not equal to "held" (so, no implicit takes)
!  but we may well be dealing with multiple objects

!  In either case below we use DominioNombre, giving it the token number as
!  context, and two places to look: among the actor's possessions, and in the
!  present location.  (Note that the order depends on which is likeliest.)

    if (token ~= TOKEN_POSEIDO)
    {   i=objeto_multiple-->0;
	! [001115] Sólo se admiten los objetos en propiedad del actor.
	if (token==TOKEN_MULTIPOSEIDO)
	    indef_propietario=actor;

        #Ifdef DEBUG;
        if (parser_trace>=3)
            print "  [Llamando a DominioNombre para la localizacion y actor]^";
        #Endif;
        l=DominioNombre(localizacion_actor, actor, token);
        if (l==CODIGO_REPARSE) return l;                  ! Reparse after Q&A
        if (l==0) {   if (indef_posibambig)
                      {   BorrarDescriptores(); np = desc_wn; jump
			  TryAgain2; }

     ! [001115] Un tipo de error más correcto cuando se ha
     ! intentado "dejar todo" y no se lleva nada.
     ! Modificado en [020621] para corregir un bug que impedía que
     ! funcionaran otras formas con "dejar".
     if (token == TOKEN_MULTIPOSEIDO) {
       o = SiguientePalabraParar();
       if (o == -1)
         tipoerror=NADA_PE;
       else
         np--;
     }
     else
       tipoerror = NoLoVeo();

	    jump FailToken; } ! Choose best error

        #Ifdef DEBUG;
        if (parser_trace>=3)
        {   if (l>1)
                print "  [DN ha retornado ", (the) l, "]^";
            else
            {   print "  [DN añadió a la lista de objetos múltiples:^";
                k=objeto_multiple-->0;
                for (j=i+1:j<=k:j++)
                    print "  Elemento ", j, ": ", (The) objeto_multiple-->j,
                          " (", objeto_multiple-->j, ")^";
                print "  La lista tiene ahora tamaño ", k, "]^";
            }
        }
        #Endif;

        if (l==1)
        {   if (~~many_flag)
                many_flag = true;
            else                                  ! Merge with earlier ones
            {   k=objeto_multiple-->0;            ! (with either parity)
                objeto_multiple-->0 = i;
                for (j=i+1:j<=k:j++)
                {   if (and_parity) AniadirMulti(objeto_multiple-->j);
                    else SustraerMulti(objeto_multiple-->j);
                }
                #Ifdef DEBUG;
                if (parser_trace>=3)
                    print "  [Mezclando los ", k-i, " objetos nuevos
			con los ", i, " antiguos]^";
                #Endif;
            }
        }
        else
        {   ! A single object was indeed found

            if (long_encajado == 0 && indef_posibambig)
            {   !   So the answer had to be inferred from no textual data,
                !   and we know that there was an ambiguity in the descriptor
                !   stage (such as a word which could be a pronoun being
                !   parsed as an articulo or possessive).  It's worth having
                !   another go.

                BorrarDescriptores(); np = desc_wn; jump TryAgain2;
            }

            if (token==TOKEN_CRIATURA && TestCriatura(l)==0)
            {   tipoerror=ANIMA_PE; jump FailToken; } !  Animation is required

            if (~~many_flag)
                single_object = l;
            else
            {   if (and_parity) AniadirMulti(l); else SustraerMulti(l);
                #Ifdef DEBUG;
                if (parser_trace>=3)
                    print "  [Combinando ", (the) l, " con la lista]^";
                #Endif;
            }
        }
    }

!  Case 2: token is "held" (which fortunately can't take multiple objects)
!  and may generate an implicit take

    else

    {   l=DominioNombre(actor,localizacion_actor,token);       ! Same as above...
        if (l==CODIGO_REPARSE) return RPG_REPARSE;
        if (l==0)
        {   if (indef_posibambig)
            {   BorrarDescriptores(); np = desc_wn; jump TryAgain2; }
            tipoerror=NoLoVeo(); return RPG_FALLO;            ! Choose best error
        }

!  ...until it produces something not held by the actor.  Then an implicit
!  take must be tried.  If this is already happening anyway, things are too
!  confused and we have to give up (but saving the oops marker so as to get
!  it on the right word afterwards).
!  The point of this last rule is that a sequence like
!
!      > read newspaper
!      (taking the newspaper first)
!      The dwarf unexpectedly prevents you from taking the newspaper!
!
!  should not be allowed to go into an infinite repeat - read becomes
!  take then read, but take has no effect, so read becomes take then read...
!  Anyway for now all we do is record the number of the object to take.

        o=parent(l);
        if (o~=actor)
        {   if (modo_noposeido==1)
            {   eepa_guardado=eepa_desde; tipoerror=NOTIENES_PE; jump FailToken;
            }
            no_poseido = l;
            #Ifdef DEBUG;
            if (parser_trace>=3)
                print "  [De momento admito el objeto ", (the) l, "]^";
            #Endif;
        }
        single_object = l;
    }

!  The following moves the word marker to just past the named object...

    np = eepa_desde + long_encajado;

!  **** (E) ****

!  Object(s) specified now: is that the end of the list, or have we reached
!  "and", "but" and so on?  If so, create a multiple-object list if we
!  haven't already (and are allowed to).

    .NextInList;

    o=SiguientePalabra();

    if (o==Y1__WD or Y2__WD or Y3__WD or SALVO1__WD or SALVO2__WD or SALVO3__WD
           or palabra_coma)
    {
        #Ifdef DEBUG;
        if (parser_trace>=3) print "  [Leida la conjunción '", (address) o, "']^";
        #Endif;

        if (~~token_allows_multiple)
        {   tipoerror=MULTI_PE; jump FailToken;
        }

        if (o==SALVO1__WD or SALVO2__WD or SALVO3__WD) and_parity = 1-and_parity;

        if (~~many_flag)
        {   objeto_multiple-->0 = 1;
            objeto_multiple-->1 = single_object;
            many_flag = true;
            #Ifdef DEBUG;
            if (parser_trace>=3)
                print "  [Creando lista nueva desde ", (the) single_object, "]^";
            #Endif;
        }
        no_deducir = true; deducedesde=0;           ! Don't print (inferences)
        jump ObjectList;                          ! And back around
    }

    np--;   ! Word marker back to first not-understood word

!  **** (F) ****

!  Happy or unhappy endings:

    .PassToken;

    if (many_flag)
    {   single_object = RPG_MULTIPLE;
        multi_contexto = token;
    }
    else
    {   if (modo_indef==1 && indef_tipo & PLURAL_BIT ~= 0)
        {   if (indef_esperado<100 && indef_esperado>1)
            {   multi_hallado=1; multi_esperado=indef_esperado;
                tipoerror=HAYPOCOS_PE;
                jump FailToken;
            }
        }
    }
    return single_object;

    .FailToken;

!  If we were only guessing about it being a plural, try again but only
!  allowing singulars (so that words like "six" are not swallowed up as
!  Descriptores)

    if (permitir_plurales && indef_suponer_p==1)
    {   permitir_plurales=false; np=desc_wn; jump TryAgain;
    }
    return -1;
];

! ----------------------------------------------------------------------------
!  DominioNombre does the most substantial part of parsing an object nombre.
!
!  It is given two "domains" - usually a localizacion and then the actor who is
!  looking - and a context (i.e. token type), and returns:
!
!   0    if no match at all could be made,
!   1    if a multiple object was made,
!   k    if object k was the one decided upon,
!   CODIGO_REPARSE if it asked a question of the jugador and consequently rewrote
!        the jugador's input, so that the whole parser should start again
!        on the rewritten input.
!
!   In the case when it returns 1<k<CODIGO_REPARSE, it also sets the variable
!   long_de_uno to the number of words in the input text matched to the
!   noun.
!   In the case k=1, the multiple objects are added to objeto_multiple by
!   hand (not by AniadirMulti, because we want to allow duplicates).
! ----------------------------------------------------------------------------

[ DominioNombre domain1 domain2 context    first_word i j k l
                                        answer_words;

#Ifdef DEBUG;
  if (parser_trace>=4)
  {   print "   [DominioNombre llamado para la posición ", np, "^";
      print "   ";
      if (modo_indef)
      {   print "buscando un objeto indefinido: ";
          if (indef_tipo & OTRO_BIT)  print "otro ";
          if (indef_tipo & MI_BIT)     print "mio ";
          if (indef_tipo & ESO_BIT)   print "ese ";
          if (indef_tipo & PLURAL_BIT) print "plural ";
          if (indef_tipo & ENCENDIDO_BIT)    print "con luz ";
          if (indef_tipo & APAGADO_BIT)  print "sin luz ";
          if (indef_propietario ~= 0) print "que pertenece a:",
            (name) indef_propietario;
          new_line;
          print "   número de esperados: ";
          if (indef_esperado == 100) print "todos"; else print indef_esperado;
          new_line;
          print "   GNAs más probables de los nombres: ", indef_casos, "^";
      }
      else print "buscando objeto definido^";
  }
#Endif;

  long_encajado=0; numero_de_encajados=0; encajado_desde=np; bandera_puesto_en=0;

  BuscarEnAlcance(domain1, domain2, context);

#Ifdef DEBUG;
  if (parser_trace>=4) print "   [DN ha encontrado ", numero_de_encajados, " aciertos]^";
#Endif;

  np=encajado_desde+long_encajado;

!  If nothing worked at all, leave with the word marker skipped past the
!  first unmatched word...

  if (numero_de_encajados==0) { np++; rfalse; }

!  Suppose that there really were some words being parsed (i.e., we did
!  not just infer).  If so, and if there was only one match, it must be
!  right and we return it...

  if (encajado_desde <= num_palabras)
  {   if (numero_de_encajados==1) { i=lista_encajan-->0; return i; }

!  ...now suppose that there was more typing to come, i.e. suppose that
!  the user entered something beyond this noun.  If nothing ought to follow,
!  then there must be a mistake, (unless what does follow is just a full
!  stop, and or comma)

      if (np<=num_palabras)
      {   i=SiguientePalabra(); np--;
          if (i ~=  Y1__WD or Y2__WD or Y3__WD or palabra_coma
                 or DESPUES1__WD or DESPUES2__WD or DESPUES3__WD
                 or SALVO1__WD or SALVO2__WD or SALVO3__WD)
          {   if (elsiguiente==TOKEN_FINAL) rfalse;
          }
      }
  }

!  Now look for a good choice, if there's more than one choice...

  numero_de_clases=0;

  if (numero_de_encajados==1) i=lista_encajan-->0;
  if (numero_de_encajados>1)
  {   i=Adjudicate(context);
      if (i==-1) rfalse;
      if (i==1) rtrue;       !  Adjudicate has made a multiple
                             !  object, and we pass it on
  }

!  If i is non-zero here, one of two things is happening: either
!  (a) an inference has been successfully made that object i is
!      the intended one from the user's specification, or
!  (b) the user finished typing some time ago, but we've decided
!      on i because it's the only possible choice.
!  In either case we have to keep the patron up to date,
!  note that an inference has been made and return.
!  (Except, we don't note which of a pile of identical objects.)

  if (i~=0)
  {   if (no_deducir) return i;
      if (deducedesde==0) deducedesde=contadorp;
      patron-->contadorp = i;
      return i;
  }

!  If we get here, there was no obvious choice of object to make.  If in
!  fact we've already gone past the end of the jugador's typing (which
!  means the match list must contain every object in scope, regardless
!  of its nombre), then it's foolish to give an enormous list to choose
!  from - instead we go and ask a more suitable question...

  if (encajado_desde > num_palabras) jump Incomplete;

!  Now we print up the question, using the equivalence classes as worked
!  out by Adjudicate() so as not to repeat ourselves on plural objects...

  if (context==TOKEN_CRIATURA)
      M__L(##Miscelanea, 45); else M__L(##Miscelanea, 46);

!  ...and get an answer:

  .WhichOne;
#Ifdef TARGET_ZCODE;
  for (i=2:i<INPUT_BUFFER_LEN:i++) buffer2->i=' ';
#Endif; ! TARGET_ZCODE
  answer_words=Teclado(buffer2, parse2);

!  Conveniently, parse2-->1 is the first word in both ZCODE and GLULX.
  first_word=(parse2-->1);

!  Take care of "all", because that does something too clever here to do
!  later on:

  if (first_word==TODO1__WD or TODO2__WD or TODO3__WD or TODO4__WD or TODO5__WD)
  {
      if (context == TOKEN_MULTI or TOKEN_MULTIPOSEIDO or TOKEN_MULTIEXCEPTO
                     or TOKEN_MULTIDENTRO)
      {   l=objeto_multiple-->0;
          for (i=0:i<numero_de_encajados && l+i<63:i++)
          {   k=lista_encajan-->i;
              objeto_multiple-->(i+1+l) = k;
          }
          objeto_multiple-->0 = i+l;
          rtrue;
      }
      M__L(##Miscelanea, 47);
      jump WhichOne;
  }

!  If the first word of the reply can be interpreted as a verb, then
!  assume that the jugador has ignored the question and given a new
!  command altogether.
!  (This is one time when it's convenient that the directions are
!  not themselves verbs - thus, "north" as a reply to "Which, the north
!  or south puerta" is not treated as a fresh command but as an answer.)

  #Ifdef IdiomaEsVerbo;
  if (first_word==0)
  {   j = np; first_word=IdiomaEsVerbo(buffer2, parse2, 1); np = j;
  }
  #Endif;
  if (first_word ~= 0)
  {   j=first_word->#dict_par1;
      if ((0~=j&1) && (first_word ~= 'long' or 'short' or 'normal'
                                     or 'brief' or 'full' or 'verbose'))
      {   CopiarBuffer(buffer, buffer2);
          return CODIGO_REPARSE;
      }
  }

!  Now we insert the answer into the original typed command, as
!  words additionally describing the same object
!  (eg, > take red button
!       Which one, ...
!       > music
!  becomes "take music red button".  The parser will thus have three
!  words to work from next time, not two.)

#Ifdef TARGET_ZCODE;

  k = DireccionDePalabra(encajado_desde) - buffer; l=buffer2->1+1;
  for (j=buffer + buffer->0 - 1: j>= buffer+k+l: j--)
      j->0 = 0->(j-l);
  for (i=0:i<l:i++) buffer->(k+i) = buffer2->(2+i);
  buffer->(k+l-1) = ' ';
  buffer->1 = buffer->1 + l;
  if (buffer->1 >= (buffer->0 - 1)) buffer->1 = buffer->0;

#Ifnot; ! TARGET_GLULX

  k = DireccionDePalabra(encajado_desde) - buffer;
  l = (buffer2-->0) + 1;
  for (j=buffer+INPUT_BUFFER_LEN-1 : j >= buffer+k+l : j--)
      j->0 = j->(-l);
  for (i=0:i<l:i++)
      buffer->(k+i) = buffer2->(WORDSIZE+i);
  buffer->(k+l-1) = ' ';
  buffer-->0 = buffer-->0 + l;
  if (buffer-->0 > (INPUT_BUFFER_LEN-WORDSIZE))
      buffer-->0 = (INPUT_BUFFER_LEN-WORDSIZE);

#Endif; ! TARGET_

!  Having reconstructed the input, we warn the parser accordingly
!  and get out.

  return CODIGO_REPARSE;

!  Now we come to the question asked when the input has run out
!  and can't easily be guessed (eg, the jugador typed "take" and there
!  were plenty of things which might have been meant).

  .Incomplete;

  if (context==TOKEN_CRIATURA)
      M__L(##Miscelanea, 48); else M__L(##Miscelanea, 49);

#Ifdef TARGET_ZCODE;
  for (i=2:i<INPUT_BUFFER_LEN:i++) buffer2->i=' ';
#Endif; ! TARGET_ZCODE
  answer_words=Teclado(buffer2, parse2);

  first_word=(parse2-->1);
  #Ifdef IdiomaEsVerbo;
  if (first_word==0)
  {   j = np; first_word=IdiomaEsVerbo(buffer2, parse2, 1); np = j;
  }
  #Endif;

!  Once again, if the reply looks like a command, give it to the
!  parser to get on with and forget about the question...

  if (first_word ~= 0)
  {   j=first_word->#dict_par1;
      if (0~=j&1)
      {   CopiarBuffer(buffer, buffer2);
          return CODIGO_REPARSE;
      }
  }

!  ...but if we have a genuine answer, then:
!
!  (1) we must glue in text suitable for anything that's been inferred.

  if (deducedesde ~= 0)
  {   for (j = deducedesde: j<contadorp: j++)
      {   if (patron-->j == PATRON_NULO) continue;
#Ifdef TARGET_ZCODE;
          i=2+buffer->1; (buffer->1)++; buffer->(i++) = ' ';
#Ifnot; ! TARGET_GLULX
          i = WORDSIZE + buffer-->0;
          (buffer-->0)++; buffer->(i++) = ' ';
#Endif; ! TARGET_

#Ifdef DEBUG;
          if (parser_trace >= 5)
              print "[Pegando a la deducción el código del patrón ", patron-->j,
                    "]^";
#Endif; ! DEBUG

! Conveniently, parse2-->1 is the first word in both ZCODE and GLULX.

          parse2-->1 = 0;

          ! An inferred object.  Best we can do is glue in a pronoun.
          ! (This is imperfect, but it's very seldom needed anyway.)

          if (patron-->j >= 2 && patron-->j < CODIGO_REPARSE)
          {   ActualizarPronombre(patron-->j);
              for (k=1: k<=IdiomaPronombres-->0: k=k+3)
                  if (patron-->j == IdiomaPronombres-->(k+2))
                  {   parse2-->1 = IdiomaPronombres-->k;
#Ifdef DEBUG;
                      if (parser_trace >= 5)
                          print "[Usando pronombre '", (address) parse2-->1,
                                "']^";
#Endif; ! DEBUG
                      break;
                  }
          }
          else
          {   ! An inferred preposition.
              parse2-->1 = Num__DirDicc(patron-->j - CODIGO_REPARSE);
#Ifdef DEBUG;
              if (parser_trace >= 5)
                  print "[Usando preposición '", (address) parse2-->1, "']^";
#Endif; ! DEBUG
          }

          ! parse2-->1 now holds the dictionary address of the word to glue in.

          if (parse2-->1 ~= 0)
          {   k = buffer + i;
#Ifdef TARGET_ZCODE;
              @output_stream 3 k;
              print (address) parse2-->1;
              @output_stream -3;
              k = k-->0;
              for (l=i:l<i+k:l++) buffer->l = buffer->(l+2);
              i = i + k; buffer->1 = i-2;
#Ifnot; ! TARGET_GLULX
              k = PrintAnyToArray(buffer+i, INPUT_BUFFER_LEN-i, parse2-->1);
              i = i + k; buffer-->0 = i - WORDSIZE;
#Endif; ! TARGET_
          }
      }
  }

!  (2) we must glue the newly-typed text onto the end.

#Ifdef TARGET_ZCODE;
  i=2+buffer->1; (buffer->1)++; buffer->(i++) = ' ';
  for (j=0: j<buffer2->1: i++, j++)
  {   buffer->i = buffer2->(j+2);
      (buffer->1)++;
      if (buffer->1 == INPUT_BUFFER_LEN) break;
  }
#Ifnot; ! TARGET_GLULX
  i = WORDSIZE + buffer-->0;
  (buffer-->0)++; buffer->(i++) = ' ';
  for (j=0: j<buffer2-->0: i++, j++)
  {   buffer->i = buffer2->(j+WORDSIZE);
      (buffer-->0)++;
      if (buffer-->0 == INPUT_BUFFER_LEN) break;
  }
#Endif; ! TARGET_

#Ifdef TARGET_ZCODE;

!  (3) we fill up the buffer with spaces, which is unnecessary, but may
!      help incorrectly-written interpreters to cope.

  for (:i<INPUT_BUFFER_LEN:i++) buffer->i = ' ';

#Endif; ! TARGET_ZCODE

  return CODIGO_REPARSE;
];

! ----------------------------------------------------------------------------
!  The Adjudicate routine tries to see if there is an obvious choice, when
!  faced with a list of objects (the lista_encajan) each of which matches the
!  jugador's specification equally well.
!
!  To do this it makes use of the context (the token type being worked on).
!  It counts up the number of obvious choices for the given context
!  (all to do with where a candidate is, except for 6 (animado) which is to
!  do with whether it is animado or not);
!
!  if only one obvious choice is found, that is returned;
!
!  if we are in indefinite mode (don't care which) one of the obvious choices
!    is returned, or if there is no obvious choice then an unobvious one is
!    made;
!
!  at this stage, we work out whether the objects are distinguishable from
!    each other or not: if they are all indistinguishable from each other,
!    then choose one, it doesn't matter which;
!
!  otherwise, 0 (meaning, unable to decide) is returned (but remember that
!    the equivalence classes we've just worked out will be needed by other
!    routines to clear up this mess, so we can't economise on working them
!    out).
!
!  Returns -1 if an error occurred
! ----------------------------------------------------------------------------
Constant SCORE__CHOOSEOBJ = 1000;
Constant SCORE__IFGOOD = 500;
Constant SCORE__UNCONCEALED = 100;
Constant SCORE__BESTLOC = 60;
Constant SCORE__NEXTBESTLOC = 40;
Constant SCORE__NOTCOMPASS = 20;
Constant SCORE__NOTSCENERY = 10;
Constant SCORE__NOTACTOR = 5;
Constant SCORE__GNA = 1;
Constant SCORE__DIVISOR = 20;

[ Adjudicate context i j k good_flag good_ones last n flag offset sovert;

#Ifdef DEBUG;
  if (parser_trace>=4)
  {   print "   [Adjudicando lista de aciertos de tamaño ", numero_de_encajados,
          " en el contexto ", context, "^";
      print "   ";
      if (modo_indef)
      {   print "tipo indefinido: ";
          if (indef_tipo & OTRO_BIT)  print "otro ";
          if (indef_tipo & MI_BIT)     print "mio ";
          if (indef_tipo & ESO_BIT)   print "ese ";
          if (indef_tipo & PLURAL_BIT) print "plural ";
          if (indef_tipo & ENCENDIDO_BIT)    print "con luz ";
          if (indef_tipo & APAGADO_BIT)  print "sin luz ";
          if (indef_propietario ~= 0) print "perteneciente a:",
            (name) indef_propietario;
          new_line;
          print "   número de objetos necesario: ";
          if (indef_esperado == 100) print "todos"; else print indef_esperado;
          new_line;
          print "   GNAs más probables de los nombres: ", indef_casos, "^";
      }
      else print "objeto definido^";
  }
#Endif;

  j=numero_de_encajados-1; good_ones=0; last=lista_encajan-->0;
  for (i=0:i<=j:i++)
  {   n=lista_encajan-->i;
      encajan_puntos-->i = 0;

      good_flag = false;

      switch(context) {
       TOKEN_POSEIDO, TOKEN_MULTIPOSEIDO:
	  if (parent(n)==actor) good_flag = true;
       TOKEN_MULTIEXCEPTO:
	  if (aviso_avanzar == -1) {
	      good_flag = true;
	  } else {
	      if (n ~= aviso_avanzar) good_flag = true;
	  }
       TOKEN_MULTIDENTRO:
              if (aviso_avanzar == -1) {
                  if (parent(n) ~= actor) good_flag = true;
              } else {
                  if (n in aviso_avanzar) good_flag = true;
              }
       TOKEN_CRIATURA: if (TestCriatura(n)==1) good_flag = true;
       TOKEN_MULTI: if (n~=actor) good_flag= true;
	  ! [001115] Para evitar que el actor sea incluido
       default: good_flag = true;
      }
      if (good_flag) {
          encajan_puntos-->i = SCORE__IFGOOD;
          good_ones++; last = n;
      }
  }
  if (good_ones==1) return last;

  ! If there is ambiguity about what was typed, but it definitely wasn't
  ! animado as required, then return anything; higher up in the parser
  ! a suitable error will be given.  (This prevents a question being asked.)

  if (context==TOKEN_CRIATURA && good_ones==0) return lista_encajan-->0;

  if (modo_indef==0) indef_tipo=0;

  PuntuacionListaEncajes(context);
  if (numero_de_encajados == 0) return -1;

  if (modo_indef == 0)
  {   !  Is there now a single highest-scoring object?
      i = SingleBestGuess();
      if (i >= 0)
      {
#Ifdef DEBUG;
          if (parser_trace>=4)
              print "   Se retorna un único objeto ganador.]^";
#Endif;
          return i;
      }
  }

  if (modo_indef==1 && indef_tipo & PLURAL_BIT ~= 0)
  {   if (context ~= TOKEN_MULTI or TOKEN_MULTIPOSEIDO or TOKEN_MULTIEXCEPTO
                     or TOKEN_MULTIDENTRO)
      {   tipoerror=MULTI_PE; return -1; }
      i=0; offset=objeto_multiple-->0; sovert = -1;
      for (j=MejorIntuicion():j~=-1 && i<indef_esperado
           && i+offset<63:j=MejorIntuicion())
      {   flag=0;
          if (j hasnt oculto && j hasnt puesto) flag=1;
          if (sovert == -1) sovert = bestguess_score/SCORE__DIVISOR;
          else {
              if (indef_esperado == 100
                  && bestguess_score/SCORE__DIVISOR < sovert) flag=0;
          }
          if (context==TOKEN_MULTIPOSEIDO or TOKEN_MULTIEXCEPTO
              && parent(j)~=actor) flag=0;
          if (accion_que_seria == ##Coger or ##Sacar && parent(j)==actor) flag=0;
          k=EligeObjetos(j,flag);
          if (k==1) flag=1; else { if (k==2) flag=0; }
          if (flag==1)
          {   i++; objeto_multiple-->(i+offset) = j;
#Ifdef DEBUG;
              if (parser_trace>=4) print "   Aceptado^";
#Endif;
          }
          else
          {   i=i;
#Ifdef DEBUG;
              if (parser_trace>=4) print "   Rechazado^";
#Endif;
          }
      }
      if (i<indef_esperado && indef_esperado<100)
      {   tipoerror=HAYPOCOS_PE; multi_esperado=indef_esperado;
          multi_hallado=i;
          return -1;
      }
      objeto_multiple-->0 = i+offset;
      multi_contexto=context;
#Ifdef DEBUG;
      if (parser_trace>=4)
          print "   Creado objeto múltiple de tamaño ", i, "]^";
#Endif;
      return 1;
  }

  for (i=0:i<numero_de_encajados:i++) encajan_clases-->i=0;

  n=1;
  for (i=0:i<numero_de_encajados:i++)
      if (encajan_clases-->i==0)
      {   encajan_clases-->i=n++; flag=0;
          for (j=i+1:j<numero_de_encajados:j++)
              if (encajan_clases-->j==0
                  && Identicos(lista_encajan-->i, lista_encajan-->j)==1)
              {   flag=1;
                  encajan_clases-->j=encajan_clases-->i;
              }
          if (flag==1) encajan_clases-->i = 1-n;
      }
  n--; numero_de_clases = n;

#Ifdef DEBUG;
  if (parser_trace>=4)
  {   print "   Agrupados en ", n, " posibilidades por el nombre:^";
      for (i=0:i<numero_de_encajados:i++)
          if (encajan_clases-->i > 0)
              print "   ", (The) lista_encajan-->i,
                  " (", lista_encajan-->i, ")  ---  grupo ",
                  encajan_clases-->i, "^";
  }
#Endif;

  if (modo_indef == 0)
  {   if (n > 1)
      {   k = -1;
          for (i=0:i<numero_de_encajados:i++)
          {   if (encajan_puntos-->i > k)
              {   k = encajan_puntos-->i;
                  j = encajan_clases-->i; j=j*j;
                  flag = 0;
              }
              else
              if (encajan_puntos-->i == k)
              {   if ((encajan_clases-->i) * (encajan_clases-->i) ~= j)
                      flag = 1;
              }
          }
          if (flag)
          {
#Ifdef DEBUG;
              if (parser_trace>=4)
                  print "   Incapaz de decidir el mejor grupo, preguntar al jugador.]^";
#Endif;
              return 0;
          }
#Ifdef DEBUG;
          if (parser_trace>=4)
              print "   Los mejores candidatos son todos del mismo grupo.^";
#Endif;
      }
  }

!  When the jugador is really vague, or there's a single collection of
!  indistinguishable objects to choose from, choose the one the jugador
!  most recently acquired, or if the jugador has none of them, then
!  the one most recently put where it is.

  if (n==1) no_deducir = true;
  return MejorIntuicion();
];

! ----------------------------------------------------------------------------
!  RevisarMulti  revises the multiple object which already exists, in the
!    luz of information which has come along since then (i.e., the otro
!    parameter).  It returns a parser error number, or else 0 if all is well.
!    This only ever throws things out, never adds new ones.
! ----------------------------------------------------------------------------

[ RevisarMulti second_p  i low;

#Ifdef DEBUG;
  if (parser_trace>=4)
      print "   Revisando la lista de objetos múltiple de tamaño ", objeto_multiple-->0,
            " con segundo=", (name) second_p, "^";
#Endif;

  if (multi_contexto==TOKEN_MULTIEXCEPTO or TOKEN_MULTIDENTRO)
  {   for (i=1, low=0:i<=objeto_multiple-->0:i++)
      {   if ( (multi_contexto==TOKEN_MULTIEXCEPTO
                && objeto_multiple-->i ~= second_p)
               || (multi_contexto==TOKEN_MULTIDENTRO
                   && objeto_multiple-->i in second_p))
          {   low++; objeto_multiple-->low = objeto_multiple-->i;
          }
      }
      objeto_multiple-->0 = low;
  }

  if (multi_contexto==TOKEN_MULTI && accion_que_seria == ##Coger)
  {   for (i=1, low=0:i<=objeto_multiple-->0:i++)
          if (TopeAlcanzable(objeto_multiple-->i)==TopeAlcanzable(actor))
              low++;
#Ifdef DEBUG;
      if (parser_trace>=4)
          print "   Token 2 caso plural: número con actor ", low, "^";
#Endif;
      if (regla_coger_todo==2 || low>0)
      {   for (i=1, low=0:i<=objeto_multiple-->0:i++)
          {   if (TopeAlcanzable(objeto_multiple-->i)==TopeAlcanzable(actor))
              {   low++; objeto_multiple-->low = objeto_multiple-->i;
              }
          }
          objeto_multiple-->0 = low;
      }
  }

  i=objeto_multiple-->0;
#Ifdef DEBUG;
  if (parser_trace>=4)
      print "   Hecho: nuevo tamaño ", i, "^";
#Endif;
  if (i==0) return NADA_PE;
  return 0;
];

! ----------------------------------------------------------------------------
!  PuntuacionListaEncajes  scores the match list for quality in terms of what the
!  jugador has vaguely asked for.  Points are awarded for conforming with
!  requirements like "my", and so on.  Remove from the match list any
!  entries which fail the basic requirements of the descriptors.
! ----------------------------------------------------------------------------

[ PuntuacionListaEncajes context its_owner its_score obj i j threshold met a_s l_s;

!  if (indef_tipo & OTRO_BIT ~= 0) threshold++;
  if (indef_tipo & MI_BIT ~= 0)    threshold++;
  if (indef_tipo & ESO_BIT ~= 0)  threshold++;
  if (indef_tipo & ENCENDIDO_BIT ~= 0)   threshold++;
  if (indef_tipo & APAGADO_BIT ~= 0) threshold++;
  if (indef_propietario ~= nothing)      threshold++;

#Ifdef DEBUG;
  if (parser_trace>=4) print "   Puntuando la lista de aciertos: modo indef ", modo_indef,
      " tipo ", indef_tipo,
      ", que satisfaga ", threshold, " requisitos:^";
#Endif;

  a_s = SCORE__NEXTBESTLOC; l_s = SCORE__BESTLOC;
  if (context == TOKEN_POSEIDO or TOKEN_MULTIPOSEIDO or TOKEN_MULTIEXCEPTO) {
      a_s = SCORE__BESTLOC; l_s = SCORE__NEXTBESTLOC;
  }

  for (i=0: i<numero_de_encajados: i++) {
      obj = lista_encajan-->i; its_owner = parent(obj); its_score=0;

!      if (indef_tipo & OTRO_BIT ~=0
!          &&  obj~=itobj or himobj or herobj) met++;
      if (indef_tipo & MI_BIT ~=0  &&  its_owner==actor) met++;
      if (indef_tipo & ESO_BIT ~=0  &&  its_owner==localizacion_actor) met++;
      if (indef_tipo & ENCENDIDO_BIT ~=0  &&  obj has luz) met++;
      if (indef_tipo & APAGADO_BIT ~=0  &&  obj hasnt luz) met++;
      if (indef_propietario~=0 && its_owner == indef_propietario) met++;

      if (met < threshold)
      {
#Ifdef DEBUG;
          if (parser_trace >= 4)
              print "   ", (The) lista_encajan-->i,
                    " (", lista_encajan-->i, ") en ", (the) its_owner,
                    " es rechazado (no encajan los descriptores)^";
#Endif;
          lista_encajan-->i=-1;
      }
      else
      {   its_score = 0;
          if (obj hasnt oculto) its_score = SCORE__UNCONCEALED;

          if (its_owner==actor)   its_score = its_score + a_s;
          else
          if (its_owner==localizacion_actor) its_score = its_score + l_s;
          else
          if (its_owner ~= Brujula) its_score = its_score + SCORE__NOTCOMPASS;

          its_score = its_score + SCORE__CHOOSEOBJ * EligeObjetos(obj, 2);

          if (obj hasnt escenario) its_score = its_score + SCORE__NOTSCENERY;
          if (obj ~= actor) its_score = its_score + SCORE__NOTACTOR;

          !   A small bonus for having the correct GNA,
          !   for sorting out ambiguous articles and the like.

          if (indef_casos & (PowersOfTwo_TB-->(ObtenerGNADeObjeto(obj))))
              its_score = its_score + SCORE__GNA;

          encajan_puntos-->i = encajan_puntos-->i + its_score;
#Ifdef DEBUG;
          if (parser_trace >= 4)
              print "     ", (The) lista_encajan-->i,
                    " (", lista_encajan-->i, ") en ", (the) its_owner,
                    " : ", encajan_puntos-->i, " puntos^";
#Endif;
      }
  }

  for (i=0:i<numero_de_encajados:i++)
  {   while (lista_encajan-->i == -1)
      {   if (i == numero_de_encajados-1) { numero_de_encajados--; break; }
          for (j=i:j<numero_de_encajados:j++)
          {   lista_encajan-->j = lista_encajan-->(j+1);
              encajan_puntos-->j = encajan_puntos-->(j+1);
          }
          numero_de_encajados--;
      }
  }
];

! ----------------------------------------------------------------------------
!  MejorIntuicion makes the best guess it can out of the match list, assuming
!  that everything in the match list is textually as good as everything else;
!  however it ignores items marked as -1, and so marks anything it chooses.
!  It returns -1 if there are no possible choices.
! ----------------------------------------------------------------------------

! Modificada en la revisión [020415] de modo que si hay varios objetos con la
! mayor puntuación, se elija uno de ellos al azar, en vez de elegir siempre al
! primero.

[ MejorIntuicion  earliest its_score best i mejores aleat j;

  earliest=0; best=-1; mejores=0;
  for (i=0:i<numero_de_encajados:i++)
  {   if (lista_encajan-->i >= 0)
      {   its_score=encajan_puntos-->i;
          if (its_score>best) {
            best=its_score;
            earliest=i;
            mejores=1;
          }
          else if (its_score == best)
            mejores++;
      }
  }
  if (mejores > 1) {
    aleat = random (mejores);
    for (i = 0, j = 0: i < numero_de_encajados: i++)
    ! Antes se inicializaba j = 1 (bug corregido en [020423])
    {
      if (lista_encajan-->i >= 0)
      {
        its_score = encajan_puntos-->i;
        if (its_score == best)
          j++;
        if (j == aleat)
        {
          earliest = i;
          break;
        }
      }
    }
  }
#Ifdef DEBUG;
  if (parser_trace>=4)
      if (best < 0)
          print "   Mejor intuición no tiene donde elegir^";
      else
          print "   Mejor intuición ", (the) lista_encajan-->earliest,
                " (", lista_encajan-->earliest, ")^";
#Endif;
  if (best<0) return -1;
  i=lista_encajan-->earliest;
  lista_encajan-->earliest=-1;
  bestguess_score = best;
  return i;
];

! ----------------------------------------------------------------------------
!  SingleBestGuess returns the highest-scoring object in the match list
!  if it is the clear winner, or returns -1 if there is no clear winner
! ----------------------------------------------------------------------------

[ SingleBestGuess  earliest its_score best i;

  earliest=-1; best=-1000;
  for (i=0:i<numero_de_encajados:i++)
  {   its_score=encajan_puntos-->i;
      if (its_score==best) earliest = -1;
      if (its_score>best) { best=its_score; earliest=lista_encajan-->i; }
  }
  bestguess_score = best;
  return earliest;
];

! ----------------------------------------------------------------------------
!  Identicos decides whether or not two objects can be distinguished from
!  each other by anything the jugador can type.  If not, it returns true.
! ----------------------------------------------------------------------------

! Modificado en la versión [020423] para comparar además de nombre, las otras
! propiedades de la librería española InformATE! que sirven también para nombrar
! los objetos: nombre_f, nombre_fp, nombre_mp y adjetivos. Si se programan bien
! los juegos, con esto se puede solucionar el problema de la desambiguación.

[ Identicos o1 o2 p1 p2 n1 n2 i j flag pasada;

  if (o1==o2) rtrue;  ! This should never happen, but to be on the safe side
  if (o1==0 || o2==0) rfalse;  ! Similarly
  if (parent (o1) == Brujula || parent (o2) == Brujula) rfalse; ! Saves time

!  What complicates things is that o1 or o2 might have a parsing routine,
!  so the parser can't know from here whether they are or aren't the same.
!  If they have different parsing routines, we simply assume they're
!  different.  If they have the same routine (which they probably got from
!  a class definition) then the decision process is as follows:
!
!     the routine is called (with self being o1, not that it matters)
!       with uno and otro being set to o1 and o2, and accion being set
!       to the fake accion TheSame.  If it returns -1, they are found
!       identical; if -2, different; and if >=0, then the usual method
!       is used instead.

  if (o1.parse_nombre~=0 || o2.parse_nombre~=0)
  {   if (o1.parse_nombre ~= o2.parse_nombre) rfalse;
      accion_parser=##ElMismo; parser_uno=o1; parser_dos=o2;
      j=np; i=EjecutarRutinas(o1,parse_nombre); np=j;
      if (i==-1) rtrue; if (i==-2) rfalse;
  }

!  This is the default algorithm: do they have the same words in their
!  "nombre" (i.e. property no. 1) properties.  (Note that the following allows
!  for repeated words and words in different ordenes.)

!  p1 = o1.&1; n1 = (o1.#1)/WORDSIZE;  ! Para mí, referirse a una propiedad
!  p2 = o2.&1; n2 = (o2.#1)/WORDSIZE;  ! con un número es una burrada

! ¿TODO? OJO: Este método compara si cada una de las propiedades de nombres y
! demás a buscar tiene las mismas palabras, pero entre ellas mismas (esto es,
! por ejemplo entre adjetivos de o1 y de o2), no entre sí (como, por ejemplo,
! entre las de nombre de o1 y adjetivos de o2).
!
! Posiblemente lo ideal fuera mirar si todas las palabras de todas estas
! propiedades de o1 están en las propiedades de o2 y viceversa.

! pasada almacenará el número de pasada por el que se va, para saber si toca
! comparar nombre(1), adjetivos(2), nombre_f(3), nombre_mp(4) o nombre_fp(5)

  for (pasada = 1: pasada < 6: pasada++) {
    switch (pasada) {
      1:
        p1 = o1.&nombre; n1 = (o1.#nombre)/WORDSIZE;
        p2 = o2.&nombre; n2 = (o2.#nombre)/WORDSIZE;
      2:
        p1 = o1.&adjetivos; n1 = (o1.#adjetivos)/WORDSIZE;
        p2 = o2.&adjetivos; n2 = (o2.#adjetivos)/WORDSIZE;
      3:
        p1 = o1.&nombre_f; n1 = (o1.#nombre_f)/WORDSIZE;
        p2 = o2.&nombre_f; n2 = (o2.#nombre_f)/WORDSIZE;
      4:
        p1 = o1.&nombre_mp; n1 = (o1.#nombre_mp)/WORDSIZE;
        p2 = o2.&nombre_mp; n2 = (o2.#nombre_mp)/WORDSIZE;
      5:
        p1 = o1.&nombre_fp; n1 = (o1.#nombre_fp)/WORDSIZE;
        p2 = o2.&nombre_fp; n2 = (o2.#nombre_fp)/WORDSIZE;
    }  ! del switch

    !  for (i=0:i<n1:i++) { print (address) p1-->i, " "; } new_line;
    !  for (i=0:i<n2:i++) { print (address) p2-->i, " "; } new_line;

    for (i = 0: i < n1: i++)
    {
      flag = 0;
      for (j = 0: j < n2: j++)
        if (p1-->i == p2-->j)
          flag = 1;
      if (flag == 0) rfalse;
    }

    for (j = 0: j < n2: j++)
    {
      flag = 0;
      for (i = 0: i < n1: i++)
        if (p1-->i == p2-->j)
          flag = 1;
      if (flag == 0) rfalse;
    }
  }  ! del for

!  print "Which are identical!^";
  rtrue;
];

! ----------------------------------------------------------------------------
!  ImprimirComando reconstructs the command as it presently reads, from
!  the patron which has been built up
!
!  If from is 0, it starts with the verb: then it goes through the patron.
!  The other parameter is "emptyf" - a flag: if 0, it goes up to contadorp:
!  if 1, it goes up to contadorp-1.
!
!  Note that verbs and prepositions are printed out of the dictionary:
!  and that since the dictionary may only preserve the first six characters
!  of a word (in a V3 game), we have to hand-code the longer words needed.
!
!  (Recall that patron entries are 0 for "multiple object", 1 for "special
!  word", 2 to CODIGO_REPARSE-1 are object numbers and CODIGO_REPARSE+n means
!  the preposition n)
! ----------------------------------------------------------------------------

[ ImprimirComando from i k spacing_flag;

  if (from==0)
  {   i=palabra_verbo;
      if (IdiomaVerbo(i) == 0)
          if (ImprimirVerbo(i) == 0)
              print (address) i;
      from++; spacing_flag = true;
  }

  for (k=from:k<contadorp:k++)
  {   i=patron-->k;
      if (i == PATRON_NULO) continue;
      if (spacing_flag) print (char) ' ';
      if (i==0) { print (string) ESASC__TX; jump TokenPrinted; }
      if (i==1) { print (string) ESO__TX; jump TokenPrinted; }
      if (i>=CODIGO_REPARSE) print (address) Num__DirDicc(i-CODIGO_REPARSE);
      ! Las dos siguientes líneas (no comentadas) han sido añadidas en
      ! [020621] para que se imprima "¿Quieres ir hacia el norte?" y no
      ! "¿Quieres ir el norte?"
      else if (i in Brujula && palabra_verbo == 'vete' or 've' or 'camina' or
        'anda' or 'corre' or 'vuelve' or 'ir') print "hacia ", (the) i;
      else print (the) i;
      .TokenPrinted;
      spacing_flag = true;
  }
];

! ----------------------------------------------------------------------------
!  The NoLoVeo routine returns a good error number for the situation where
!  the last word looked at didn't seem to refer to any object in context.
!
!  The idea is that: if the actor is in a localizacion (but not inside something
!  like, for instance, a tank which is in that localizacion) then an attempt to
!  refer to one of the words listed as meaningful-but-irrelevant there
!  will cause "you don't need to refer to that in this game" rather than
!  "no such thing" or "what's 'it'?".
!  (The advantage of not having looked at "irrelevant" local nouns until now
!  is that it stops them from clogging up the ambiguity-resolving process.
!  Thus game objects always triumph over escenario.)
! ----------------------------------------------------------------------------

[ NoLoVeo  i w e;
    eepa_guardado=eepa_desde;

    if (token_alcance~=0) {
      error_alcance = token_alcance; return PREGUNTAAMBITO_PE;
    }

    np--; w=SiguientePalabra();
    e=NOVEO_PE;
    if (w==palabra_pronombre)
    {   palabra__pronombre=palabra_pronombre;
        objeto__pronombre=objeto_pronombre;
        e=YANOPRON_PE;
    }
    i=actor; while (parent(i) ~= 0) i = parent(i);
    if (i has visitado && SeRefiere(i,np-1)==1) e=ESCENARIO_PE;
    if (tipoerror>e) return tipoerror;
    return e;
];

! ----------------------------------------------------------------------------
!  The AniadirMulti routine adds object "o" to the multiple-object-list.
!
!  This is only allowed to hold 63 objects at most, at which point it ignores
!  any new entries (and sets a global flag so that a warning may later be
!  printed if need be).
! ----------------------------------------------------------------------------

[ AniadirMulti o i j;
  i=objeto_multiple-->0;
  if (i==63) { bandera_demasiados=1; rtrue; }
  for (j=1:j<=i:j++)
      if (o==objeto_multiple-->j)
          rtrue;
  i++;
  objeto_multiple-->i = o;
  objeto_multiple-->0 = i;
];

! ----------------------------------------------------------------------------
!  The SustraerMulti routine deletes object "o" from the multiple-object-list.
!
!  It returns 0 if the object was there in the first place, and 9 (because
!  this is the appropriate error number in Parser()) if it wasn't.
! ----------------------------------------------------------------------------

[ SustraerMulti o i j k et;
  i=objeto_multiple-->0; et=0;
  for (j=1:j<=i:j++)
      if (o==objeto_multiple-->j)
      {   for (k=j:k<=i:k++)
              objeto_multiple-->k = objeto_multiple-->(k+1);
          objeto_multiple-->0 = --i;
          return et;
      }
  et=9; return et;
];

! ----------------------------------------------------------------------------
!  The FiltrarMulti routine goes through the multiple-object-list and throws
!  out anything without the given attribute "attr" set.
! ----------------------------------------------------------------------------

[ FiltrarMulti attr  i j o;
  .MFiltl;
  i=objeto_multiple-->0;
  for (j=1:j<=i:j++)
  {   o=objeto_multiple-->j;
      if (o hasnt attr) { SustraerMulti(o); jump Mfiltl; }
  }
];

! ----------------------------------------------------------------------------
!  The FiltroUsuario routine consults the user's filter (or checks on attribute)
!  to see what already-accepted nouns are acceptable
! ----------------------------------------------------------------------------

[ FiltroUsuario obj;

  if (filtro_token > 0 && filtro_token < 49)
  {   if (obj has (filtro_token-1)) rtrue;
      rfalse;
  }
  uno = obj;
  return indirect(filtro_token);
];

! ----------------------------------------------------------------------------
!  MoverPalabra copies word at2 from parse buffer b2 to word at1 in "parse"
!  (the main parse buffer)
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

[ MoverPalabra at1 b2 at2 x y;
  x=at1*2-1; y=at2*2-1;
  parse-->x++ = b2-->y++;
  parse-->x = b2-->y;
];

#Ifnot; ! TARGET_GLULX

[ MoverPalabra at1 b2 at2 x y;
  x=at1*3-2; y=at2*3-2;
  parse-->x++ = b2-->y++;
  parse-->x++ = b2-->y++;
  parse-->x = b2-->y;
];

#Endif; ! TARGET_

! ----------------------------------------------------------------------------
!  BuscarEnAlcance  domain1 domain2 context
!
!  Works out what objects are in scope (possibly asking an outside routine),
!  but does not look at anything the jugador has typed.
! ----------------------------------------------------------------------------

[ BuscarEnAlcance domain1 domain2 context i;

  i=0;
!  Everything is in scope to the debugging commands

#Ifdef DEBUG;
   ! Bug corregido en 001101
   ! Las palabras que se comprobaban aquí eran las originales en
   ! inglés en vez de su nueva versión en español
    if (razon_alcance==RAZON_PARSING
      && palabra_verbo == 'xroba' or 'xarbol' or 'xmueve'
               or 'irdonde' or 'scope' or 'xobjeto' or
               'alcance' or 'xir')
  {
#Ifdef TARGET_ZCODE;
      for (i=objjugador:i<=objeto_raiz:i++)
          if (i ofclass Object && (parent(i)==0 || parent(i) ofclass Object))
              PonerAlAlcance(i);
#Ifnot; ! TARGET_GLULX
      objectloop (i)
          if (i ofclass Object && (parent(i)==0 || parent(i) ofclass Object))
              PonerAlAlcance(i);
#Endif; ! TARGET_
      rtrue;
  }
#Endif;

!  First, a scope token gets priority here:

  if (token_alcance ~= 0)
  {   estadio_alcance=2;
      if (indirect(token_alcance)~=0) rtrue;
  }

!  Next, call any user-supplied routine adding things to the scope,
!  which may circumvent the usual routines altogether if they return true:

  if (actor==domain1 or domain2 && AlAlcance(actor)~=0) rtrue;

!  Pick up everything in the localizacion except the actor's possessions;
!  then go through those.  (This ensures the actor's possessions are in
!  scope even in Darkness.)

  if (context==TOKEN_MULTIDENTRO && aviso_avanzar ~= -1)
  {   if (SeVeATraves(aviso_avanzar)==1)
          DentroDelAlcance(aviso_avanzar, 0, context);
  }
  else
  {   if (domain1~=0 && domain1 has soporte or recipiente)
          DentroDelAlcance_O(domain1, domain1, context);
      DentroDelAlcance(domain1, domain2, context);
      if (domain2~=0 && domain2 has soporte or recipiente)
          DentroDelAlcance_O(domain2, domain2, context);
      DentroDelAlcance(domain2, 0, context);
  }

!  A special rule applies:
!  in Darkness as in luz, the actor is always in scope to himself.

  if (LaOscuridad == domain1 or domain2)
  {   DentroDelAlcance_O(actor, actor, context);
      if (parent(actor) has soporte or recipiente)
          DentroDelAlcance_O(parent(actor), parent(actor), context);
  }
];

! ----------------------------------------------------------------------------
!  SeVeATraves is used at various places: roughly speaking, it determines
!  whether o being in scope means that the contents of o are in scope.
! ----------------------------------------------------------------------------

[ SeVeATraves o;
  if (o has soporte
      || (o has transparente)
      || (o has recipiente && o has abierto))
      rtrue;
  rfalse;
];

! ----------------------------------------------------------------------------
!  PonerAlAlcance is provided for routines outside the library, and is not
!  called within the parser (except for debugging purposes).
! ----------------------------------------------------------------------------

[ PonerAlAlcance thing;
   if (razon_alcance~=RAZON_PARSING or RAZON_HABLAR)
   {   EfectuarAccionesAlcance(thing); rtrue; }
   np=encajado_desde; IntentarEncajarObjeto(thing); bandera_puesto_en=1;
];

! ----------------------------------------------------------------------------
!  EfectuarAccionesAlcance
! ----------------------------------------------------------------------------

[ EfectuarAccionesAlcance thing s p1;
  s = razon_alcance; p1=parser_uno;
#Ifdef DEBUG;
  if (parser_trace>=6)
      print "[EAA sobre ", (the) thing, ", razón = ", razon_alcance,
      ", p1 = ", parser_uno, ", p2 = ", parser_dos, "]^";
#Endif;
  switch(razon_alcance)
  {   RAZON_REACCIONAR_ANTES:
          if (thing.reaccionar_antes==0 or NULL) return;
#Ifdef DEBUG;
          if (parser_trace>=2)
              print "[reaccionar_antes para ", (the) thing, "]^";
#Endif;
          if (parser_uno==0)
            parser_uno = EjecutarRutinas(thing,reaccionar_antes);
      RAZON_REACCIONAR_DESPUES:
          if (thing.reaccionar_despues==0 or NULL) return;
#Ifdef DEBUG;
          if (parser_trace>=2)
              print "[reaccionar_despues para ", (the) thing, "]^";
#Endif;
          if (parser_uno==0)
            parser_uno = EjecutarRutinas(thing,reaccionar_despues);
      RAZON_CADA_TURNO:
          if (thing.cada_turno == 0 or NULL) return;
#Ifdef DEBUG;
          if (parser_trace>=2)
              print "[cada_turno para ", (the) thing, "]^";
#Endif;
          ImprimirOEjecutar(thing, cada_turno);
      RAZON_TESTALCANCE:
          if (thing==parser_uno) parser_dos = 1;
      RAZON_BUCLEALCANCE:
          indirect(parser_uno,thing); parser_uno=p1;
  }
  razon_alcance = s;
];

! ----------------------------------------------------------------------------
!  DentroDelAlcance looks for objects in the domain which make textual sense
!  and puts them in the match list.  (However, it does not recurse through
!  the otro argument.)
! ----------------------------------------------------------------------------

[ DentroDelAlcance domain nosearch context x y;

   if (domain==0) rtrue;

!  Special rule: the directions (interpreted as the 12 walls of a room) are
!  always in context.  (So, e.g., "examine north wall" is always legal.)
!  (Unless we're parsing something like "all", because it would just slow
!  things down then, or unless the context is "creature".)

   if (modo_indef==0 && domain==localizacion_actor
       && razon_alcance==RAZON_PARSING && context~=TOKEN_CRIATURA)
     DentroDelAlcance (Brujula);

!  Look through the objects in the domain, avoiding "objectloop" in case
!  movements occur, e.g. when trying cada_turno.

   x = child(domain);
   while (x ~= 0)
   {   y = sibling(x);
       DentroDelAlcance_O(x, nosearch, context);
       x = y;
   }
];

[ DentroDelAlcance_O domain nosearch context i ad n;

!  multiexcept doesn't have otro parameter in scope
   if (context==TOKEN_MULTIEXCEPTO && domain==aviso_avanzar) jump DontAccept;

!  If the scope reason is unusual, don't parse.

      if (razon_alcance~=RAZON_PARSING or RAZON_HABLAR)
      {   EfectuarAccionesAlcance(domain); jump DontAccept; }

!  "it" or "them" matches to the it-object only.  (Note that (1) this means
!  that "it" will only be understood if the object in question is still
!  in context, and (2) only one match can ever be made in this case.)

      if (encajado_desde <= num_palabras)  ! If there's any text to match, that is
      {   np=encajado_desde;
          i=PalabraSustantivo();
          if (i==1 && jugador==domain)  HacerEncaje(domain, 1);

          if (i>=2 && i<128 && (IdiomaPronombres-->i == domain))
              HacerEncaje(domain, 1);
      }

!  Construing the current word as the start of a noun, can it refer to the
!  object?

      np = encajado_desde;
      if (IntentarEncajarObjeto(domain) > 0)
          if (indef_numero_en>0 && encajado_desde~=indef_numero_en)
          {   !  This case arises if the jugador has typed a number in
              !  which is hypothetically an indefinite descriptor:
              !  e.g. "take two clubs".  We have just checked the object
              !  against the word "clubs", in the hope of eventually finding
              !  two such objects.  But we also backtrack and check it
              !  against the words "two clubs", in case it turnos out to
              !  be the 2 of Clubs from a pack of cards, say.  If it does
              !  match against "two clubs", we tear up our original
              !  assumption about the meaning of "two" and lapse back into
              !  definite mode.

              np = indef_numero_en;
              if (IntentarEncajarObjeto(domain) > 0)
              {   encajado_desde = indef_numero_en;
                  BorrarDescriptores();
              }
              np = encajado_desde;
          }

      .DontAccept;

!  Shall we consider the possessions of the current object, as well?
!  Only if it's a recipiente (so, for instance, if a dwarf carries a
!  sword, then "drop sword" will not be accepted, but "dwarf, drop sword"
!  will).
!  Also, only if there are such possessions.
!
!  Notice that the parser can see "into" anything flagged as
!  transparente - such as a dwarf whose sword you can get at.

      if (child(domain)~=0 && domain ~= nosearch && SeVeATraves(domain)==1)
          DentroDelAlcance(domain,nosearch,context);

!  Drag any extras into context

   ad = domain.&suma_al_alcance;
   if (ad ~= 0)
   {
       ! Test if the property value is not an object.
#Ifdef TARGET_ZCODE;
       i = (CompararSinSigno(ad-->0,objeto_raiz) > 0);
#Ifnot; ! TARGET_GLULX
       i = (((ad-->0)->0) ~= $70);
#Endif; ! TARGET_

       if (i)
       {   bandera_paa = 2+context;
           EjecutarRutinas(domain, suma_al_alcance);
           bandera_paa = 0;
       }
       else
       {   n=domain.#suma_al_alcance;
           for (i=0:(WORDSIZE*i)<n:i++)
               DentroDelAlcance_O(ad-->i,0,context);
       }
   }
];

[ SumarAlAlcance obj;
   if (bandera_paa>=2)
       DentroDelAlcance_O(obj,0,bandera_paa-2);
   if (bandera_paa==1)
   {   if  (TieneFuenteDeLuz(obj)==1) paa_tfl = 1;
   }
];

! ----------------------------------------------------------------------------
!  HacerEncaje looks at how good a match is.  If it's the best so far, then
!  wipe out all the previous matches and start a new list with this one.
!  If it's only as good as the best so far, add it to the list.
!  If it's worse, ignore it altogether.
!
!  The idea is that "red panic button" is better than "red button" or "panic".
!
!  numero_de_encajados (the number of words matched) is set to the current level
!  of quality.
!
!  We never match anything twice, and keep at most 64 equally good items.
! ----------------------------------------------------------------------------

[ HacerEncaje obj quality i;
#Ifdef DEBUG;
   if (parser_trace>=6) print "    Acierto con calidad ",quality,"^";
#Endif;
   if (filtro_token~=0 && FiltroUsuario(obj)==0)
   {   #Ifdef DEBUG;
       if (parser_trace>=6)
         print "    Acierto eliminado por filtro de token ", filtro_token, "^";
       #Endif;
       rtrue;
   }
   if (quality < long_encajado) rtrue;
   if (quality > long_encajado) { long_encajado=quality; numero_de_encajados=0; }
   else
   {   if (2*numero_de_encajados>=TAMANIO_LISTA_ENCAJAN) rtrue;
       for (i=0:i<numero_de_encajados:i++)
           if (lista_encajan-->i==obj) rtrue;
   }
   lista_encajan-->numero_de_encajados++ = obj;
#Ifdef DEBUG;
   if (parser_trace>=6) print "    Acierto añadido a la lista^";
#Endif;
];

! ----------------------------------------------------------------------------
!  IntentarEncajarObjeto tries to match as many words as possible in what has
!  been typed to the given object, obj. If it manages any words matched at all,
!  it calls HacerEncaje to say so, then returns the number of words (or 1
!  if it was a match because of inadequate input).
! ----------------------------------------------------------------------------

[ IntentarEncajarObjeto obj threshold k w j;

#Ifdef DEBUG;
   if (parser_trace>=5)
       print "    Intentando ", (the) obj, " (", obj, ") en posición ", np, "^";
#Endif;

   banderas_dicc_nombre = 0;

!  If input has run out then always match, with only quality 0 (this saves
!  time).

   if (np > num_palabras)
   {   if (modo_indef ~= 0)
           banderas_dicc_nombre = $$01110000;  ! Reject "plural" bit
       HacerEncaje(obj,0);

       ! [010510] Añadido para evitar que un objeto que en realidad no
       ! ha sido nombrado en este turno pueda ser elegido
       ! automáticamente porque había sido nombrado en un turno
       ! anterior.
       give obj ~nombreusado;

       #Ifdef DEBUG;
       if (parser_trace>=5)
       print "    Acierto (0)^";
       #Endif;
       return 1;
   }

!  Ask the object to parse itself if necessary, sitting up and taking notice
!  if it says the plural was used:

   if (obj.parse_nombre~=0)
   {   accion_parser = NULL; j=np;
       k=EjecutarRutinas(obj,parse_nombre);
       if (k>0)
       {   np=j+k;
           .MMbyPN;

           if (accion_parser == ##HalladoPlural)
               banderas_dicc_nombre = banderas_dicc_nombre | 4;

           if (banderas_dicc_nombre & 4)
           {   if (~~permitir_plurales) k=0;
               else
               {   if (modo_indef==0)
                   {   modo_indef=1; indef_tipo=0; indef_esperado=0; }
                   indef_tipo = indef_tipo | PLURAL_BIT;
                   if (indef_esperado==0) indef_esperado=100;
               }
           }

           #Ifdef DEBUG;
               if (parser_trace>=5)
                   print "    Acierto (", k, ")^";
           #Endif;
           HacerEncaje(obj,k);
           return k;
       }
       if (k==0) jump NoWordsMatch;
   }

!  The default algorithm is simply to count up how many words pass the
!  SeRefiere test:

   accion_parser = NULL;

   w = PalabraSustantivo();

   if (w==1 && jugador==obj) { k=1; jump MMbyPN; }

   if (w>=2 && w<128 && (IdiomaPronombres-->w == obj))
   {   k=1; jump MMbyPN; }

   j=--np;
   threshold = InterpretarNombre(obj);
#Ifdef DEBUG;
   if (threshold>=0 && parser_trace>=5)
       print "    InterpretarNombre ha retornado ", threshold, "^";
#Endif;
   if (threshold<0) np++;
   if (threshold>0) { k=threshold; jump MMbyPN; }

   if (threshold==0 || SeRefiere(obj,np-1)==0)
   {   .NoWordsMatch;
       if (modo_indef~=0)
       {   k=0; accion_parser=NULL; jump MMbyPN;
       }
       rfalse;
   }

   if (threshold<0)
   {   threshold=1;
       banderas_dicc_nombre = (w->#dict_par1) & $$01110100;
       w = SiguientePalabra();
       while (SeRefiere(obj, np-1))
       {   threshold++;
           if (w)
               banderas_dicc_nombre = banderas_dicc_nombre
                                    | ((w->#dict_par1) & $$01110100);
           w = SiguientePalabra();
       }
   }

   k = threshold; jump MMbyPN;
];

! ----------------------------------------------------------------------------
!  SeRefiere works out whether the word at number wnum can refer to the object
!  obj, returning true or false.  The standard method is to see if the
!  word is listed under "nombre" for the object, but this is more complex
!  in languages other than English.
! ----------------------------------------------------------------------------

[ SeRefiere obj wnum   wd k l m;
    if (obj==0) rfalse;

    #Ifdef LanguageRefers;
    k = LanguageRefers(obj,wnum); if (k>=0) return k;
    #Endif;

    k = np; np = wnum; wd = SiguientePalabraParar(); np = k;

    if (parser_inflexion >= 256)
    {   k = indirect(parser_inflexion, obj, wd);
        if (k>=0) return k;
        m = -k;
    } else m = parser_inflexion;
    k=obj.&m; l=(obj.#m)/WORDSIZE-1;
    for (m=0:m<=l:m++)
        if (wd==k-->m) rtrue;
    rfalse;
];

[ PalabraEnPropiedad wd obj prop k l m;
    k=obj.&prop; l=(obj.#prop)/WORDSIZE-1;
    for (m=0:m<=l:m++)
        if (wd==k-->m) rtrue;
    rfalse;
];


#Ifdef TARGET_ZCODE;
! Tremendo bug corregido. Antes usaba el buffer buf2, el cual usa
! tambien el parser para leer comandos incompletos del estilo de "¿a
! cual te refieres exactamente?
! Este bug estaba en la libreria original, pero nunca aparecia porque
! apenas se usa BuscarEnDiccionario. En cambio InformATE lo usa para
! comprobar si quitando la R a un verbo se obtiene una palabra válida.
!
! [Gracias a Presi por detectarlo]
!
[ BuscarEnDiccionario texto longitud
    i;
  for (i=0:i<longitud:i++) {
      bufferaux->(2+i) = texto->i;
  }
  bufferaux->1 = longitud;
  bufferaux->0 = longitud;
  parseaux->0=1;
  Tokenise__(bufferaux,parseaux);
  return parseaux-->1;
];

#Ifnot; ! TARGET_GLULX

[ BuscarEnDiccionario texto longitud
    i;
  for (i=0:i<longitud:i++) bufferaux->(WORDSIZE+i) = texto->i;
  bufferaux-->0 = longitud;
  Tokenise__(bufferaux,parseaux);
  return parseaux-->1;
];

#Endif; ! TARGET_


! ----------------------------------------------------------------------------
!  PalabraSustantivo (which takes no arguments) returns:
!
!   0  if the next word is unrecognised or does not carry the "noun" bit in
!      its dictionary entry,
!   1  if a word meaning "me",
!   the index in the pronoun table (plus 2) of the value field of a pronoun,
!      if the word is a pronoun,
!   the address in the dictionary if it is a recognised noun.
!
!  The "current word" marker moves on one.
! ----------------------------------------------------------------------------

[ PalabraSustantivo i j s;
   i=SiguientePalabra();
   if (i==0) rfalse;
   if (i==YO1__WD or YO2__WD or YO3__WD) return 1;
   s = IdiomaPronombres-->0;
   for (j=1 : j<=s : j=j+3)
       if (i == IdiomaPronombres-->j)
           return j+2;
   if ((i->#dict_par1)&128 == 0) rfalse;
   return i;
];

! ----------------------------------------------------------------------------
!  SiguientePalabra (which takes no arguments) returns:
!
!  0            if the next word is unrecognised,
!  palabra_coma   if a comma
!  DESPUES1__WD    if a full stop
!  or the dictionary address if it is recognised.
!  The "current word" marker is movido on.
!
!  SiguientePalabraParar does the same, but returns -1 when input has run out
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

[ SiguientePalabra i j;
   if (np > parse->1) { np++; rfalse; }
   i=np*2-1; np++;
   j=parse-->i;
   if (j == ',//') j=palabra_coma;
   if (j == './/') j=DESPUES1__WD;
   return j;
];

[ SiguientePalabraParar;
   if (np > parse->1) { np++; return -1; }
   return SiguientePalabra();
];

[ DireccionDePalabra wordnum;
   return buffer + parse->(wordnum*4+1);
];

[ LongitudDePalabra wordnum;
   return parse->(wordnum*4);
];

#Ifnot; ! TARGET_GLULX

[ SiguientePalabra i j;
   if (np > parse-->0) { np++; rfalse; }
   i=np*3-2; np++;
   j=parse-->i;
   if (j == ',//') j=palabra_coma;
   if (j == './/') j=DESPUES1__WD;
   return j;
];

[ SiguientePalabraParar;
   if (np > parse-->0) { np++; return -1; }
   return SiguientePalabra();
];

[ DireccionDePalabra wordnum;
   return buffer + parse-->(wordnum*3);
];

[ LongitudDePalabra wordnum;
   return parse-->(wordnum*3-1);
];

#Endif; ! TARGET_

! ----------------------------------------------------------------------------
!  IntentarNumero is the only routine which really does any character-level
!  parsing, since that's normally left to the Z-machine.
!  It takes word number "wordnum" and tries to parse it as an (unsigned)
!  decimal number, returning
!
!  -1000                if it is not a number
!  the number           if it has between 1 and 4 digits
!  10000                if it has 5 or more digits.
!
!  (The danger of allowing 5 digits is that Z-machine integers are only
!  16 bits long, and anyway this isn't meant to be perfect.)
!
!  Using PalabraNumero, it also catches "one" up to "twenty".
!
!  Note that a game can provide a InterpretarNumero routine which takes priority,
!  to enable parsing of odder numbers ("x45y12", say).
! ----------------------------------------------------------------------------

[ IntentarNumero wordnum   i j c num len mul tot d digit;

   i=np; np=wordnum; j=SiguientePalabra(); np=i;
   j=PalabraNumero(j); if (j>=1) return j;

#Ifdef TARGET_ZCODE;
   i=wordnum*4+1; j=parse->i; num=j+buffer; len=parse->(i-1);
#Ifnot; ! TARGET_GLULX
   i=wordnum*3; j=parse-->i; num=j+buffer; len=parse-->(i-1);
#Endif; ! TARGET_

   tot=InterpretarNumero(num, len);  if (tot~=0) return tot;

   if (len>=4) mul=1000;
   if (len==3) mul=100;
   if (len==2) mul=10;
   if (len==1) mul=1;

   tot=0; c=0; len=len-1;

   for (c=0:c<=len:c++)
   {   digit=num->c;
       if (digit=='0') { d=0; jump digok; }
       if (digit=='1') { d=1; jump digok; }
       if (digit=='2') { d=2; jump digok; }
       if (digit=='3') { d=3; jump digok; }
       if (digit=='4') { d=4; jump digok; }
       if (digit=='5') { d=5; jump digok; }
       if (digit=='6') { d=6; jump digok; }
       if (digit=='7') { d=7; jump digok; }
       if (digit=='8') { d=8; jump digok; }
       if (digit=='9') { d=9; jump digok; }
       return -1000;
     .digok;
       tot=tot+mul*d; mul=mul/10;
   }
   if (len>3) tot=10000;
   return tot;
];

! ----------------------------------------------------------------------------
!  ObtenerGenero returns 0 if the given animado object is femenino, and 1 if masculino
!  (not all games will want such a simple decision function!)
! ----------------------------------------------------------------------------

[ ObtenerGenero person;
   if (person hasnt femenino) rtrue;
   rfalse;
];

[ ObtenerGNADeObjeto obj case gender;
!    if (obj provides genero) return obj.genero;

   if (obj hasnt animado) case = 6;
   if (obj has masculino) gender = masculino;
   if (obj has femenino) gender = femenino;
   if (obj has neutro) gender = neutro;
   if (gender == 0)
   {   if (case == 0) gender = IdiomaGeneroAnimado;
       else gender = IdiomaGeneroInanimado;
   }
   if (gender == femenino) case = case + 1;
   if (gender == neutro) case = case + 2;
   if (obj has nombreplural) case = case + 3;
   return case;
];

! ----------------------------------------------------------------------------
!  Converting between dictionary addresses and entry numbers
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

[ DirDicc__Num w; return (w-(0-->4 + 7))/9; ];
[ Num__DirDicc n; return 0-->4 + 7 + 9*n; ];

#Ifnot; ! TARGET_GLULX

! In Glulx, dictionary entries *are* addresses.
[ DirDicc__Num w; return w; ];
[ Num__DirDicc n; return n; ];

#Endif; ! TARGET_

! ----------------------------------------------------------------------------
!  For copying buffers
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

[ CopiarBuffer bto bfrom i size;
   size=bto->0;
   for (i=1:i<=size:i++) bto->i=bfrom->i;
];

#Ifnot; ! TARGET_GLULX

[ CopiarBuffer bto bfrom i;
   for (i=0:i<INPUT_BUFFER_LEN:i++)
       bto->i=bfrom->i;
];

#Endif; ! TARGET_

! ----------------------------------------------------------------------------
!  Provided for use by language definition files
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

[ LTI_Insert i ch  b y;

  !   Protect us from strict mode, as this isn't an array in quite the
  !   sense it expects
      b = buffer;

  !   Insert character ch into buffer at point i.

  !   Being careful not to let the buffer possibly overflow:

      y = b->1;
      if (y > b->0) y = b->0;

  !   Move the subsequent text along one character:

      for (y=y+2: y>i : y--) b->y = b->(y-1);
      b->i = ch;

  !   And the text is now one character longer:
      if (b->1 < b->0) (b->1)++;
];

#Ifnot; ! TARGET_GLULX

[ LTI_Insert i ch  b y;

  !   Protect us from strict mode, as this isn't an array in quite the
  !   sense it expects
      b = buffer;

  !   Insert character ch into buffer at point i.

  !   Being careful not to let the buffer possibly overflow:

      y = b-->0;
      if (y > INPUT_BUFFER_LEN) y = INPUT_BUFFER_LEN;

  !   Move the subsequent text along one character:

      for (y=y+WORDSIZE: y>i : y--) b->y = b->(y-1);

      b->i = ch;

  !   And the text is now one character longer:
      if (b-->0 < INPUT_BUFFER_LEN)
          (b-->0)++;
];

#Endif; ! TARGET_

! ============================================================================

[ PronombresSub x y c d;

  M__L(##Pronombres, 1);

  c = (IdiomaPronombres-->0)/3;
  if (jugador ~= objjugador) c++;

  if (c==0) return M__L(##Pronombres, 4);

  for (x = 1, d = 0 : x <= IdiomaPronombres-->0: x = x+3)
  {   print "~", (address) IdiomaPronombres-->x, "~ ";
      y = IdiomaPronombres-->(x+2);
      if (y == NULL) M__L(##Pronombres, 3);
      else { M__L(##Pronombres, 2); print (the) y; }
      d++;
      if (d < c-1) print ", ";
      if (d == c-1) print (string) Y__TX;
  }
  if (jugador ~= objjugador)
  {   print "~", (address) YO1__WD, "~ "; M__L(##Pronombres, 2);
      c = jugador; jugador = objjugador;
      print (the) c; jugador = c;
  }
  ".";
];

[ FijarPronombre dword value x;
  for (x = 1 : x <= IdiomaPronombres-->0: x = x+3)
      if (IdiomaPronombres-->x == dword)
      {   IdiomaPronombres-->(x+2) = value; return;
      }
  ErrorDeEjecucion(14);
];

[ ValorDelPronombre dword x;
  for (x = 1 : x <= IdiomaPronombres-->0: x = x+3)
      if (IdiomaPronombres-->x == dword)
          return IdiomaPronombres-->(x+2);
  return 0;
];

[ ReiniciarPalabrasVagas obj; ActualizarPronombre(obj); ];

#Ifdef EnglishNaturalLanguage;
[ PronounOldEnglish;
   if (itobj ~= old_itobj)   FijarPronombre('it', itobj);
   if (himobj ~= old_himobj) FijarPronombre('him', himobj);
   if (herobj ~= old_herobj) FijarPronombre('her', herobj);
   old_itobj = itobj; old_himobj = himobj; old_herobj = herobj;
];
#Endif;

[ ActualizarPronombre obj x bm;

   if (obj == jugador) return;

   #Ifdef EnglishNaturalLanguage;
   PronounOldEnglish();
   #Endif;

   bm = PowersOfTwo_TB-->(ObtenerGNADeObjeto(obj));

   for (x = 1 : x <= IdiomaPronombres-->0: x = x+3)
       if (bm & (IdiomaPronombres-->(x+1)) ~= 0)
           IdiomaPronombres-->(x+2) = obj;

   #Ifdef EnglishNaturalLanguage;
   itobj  = ValorDelPronombre('it');  old_itobj  = itobj;
   himobj = ValorDelPronombre('him'); old_himobj = himobj;
   herobj = ValorDelPronombre('her'); old_herobj = herobj;
   #Endif;
];

! ============================================================================
!  End of the parser propio: the remaining routines are its front end.
! ----------------------------------------------------------------------------

Object LibreriaInform "(Librería Inform)"
  with jugar
       [ i j k l;
#Ifdef TARGET_ZCODE;
       interprete_estandar = $32-->0;
       modo_transcripcion = ((0-->8) & 1);
#Ifnot; ! TARGET_GLULX
       GGInitialise();
#Endif; ! TARGET_

!       CambiarDefecto(no_puedes_ir, NOPUEDESIR__TX);

#Ifdef TARGET_ZCODE;
       buffer->0 = INPUT_BUFFER_LEN;
       buffer2->0 = INPUT_BUFFER_LEN;
       buffer3->0 = INPUT_BUFFER_LEN;
       parse->0 = 64;
       parse2->0 = 64;
#Endif; ! TARGET_ZCODE

       localizacion_real = LaOscuridad;
       jugador = objjugador; actor = jugador;

#Ifdef TARGET_ZCODE;
       objeto_raiz = #largest_object-255;
#Endif; ! TARGET_ZCODE
       objjugador.capacidad = LLEVAR_MAX; ! ### change?
       #Ifdef LanguageInitialise;
       LanguageInitialise();
       #Endif;
       new_line;
       j=Inicializar();
       punt_anterior = puntuacion;
       move jugador to localizacion;
       while (parent(localizacion)~=0) localizacion=parent(localizacion);
       localizacion_real = localizacion;
       objectloop (i in jugador) give i movido ~oculto;

       if (j~=2) Anuncio();

       MoverObjetosFlotantes();
       banderaluz=HayLuz(parent(jugador));
       if (banderaluz == 0)
       {
         localizacion_real = localizacion;
         localizacion      = LaOscuridad;
       }
       <Mirar>;

       ! Esto crea aleatoriedad en algunas plataformas primitivas
       for (i=1:i<=100:i++) j=random(i);

       #Ifdef EnglishNaturalLanguage;
       old_itobj = itobj; old_himobj = himobj; old_herobj = herobj;
       #Endif;

       while (~~banderafin)
       {
           #Ifdef EnglishNaturalLanguage;
               PronounOldEnglish();
               old_itobj = ValorDelPronombre('it');
               old_himobj = ValorDelPronombre('him');
               old_herobj = ValorDelPronombre('her');
           #Endif;

           .very__late__error;

          #Ifndef NO_PUNTUACION;
           if (puntuacion ~= punt_anterior)
           {   if (modo_notificar==1) NotificarLaPuntuacion(); punt_anterior=puntuacion; }
          #Endif; ! NO_PUNTUACION

           .late__error;

           inputobjs-->0 = 0; inputobjs-->1 = 0;
           inputobjs-->2 = 0; inputobjs-->3 = 0; meta=false;

           !  The Parser writes its results into inputobjs and meta,
           !  a flag indicating a "meta-verb".  This can only be set for
           !  commands by the jugador, not for ordenes to others.

           ParserInform.parse_input(inputobjs);

           accion=inputobjs-->0;

           !  --------------------------------------------------------------

           !  Reverse "give fred biscuit" into "give biscuit to fred"

           if (accion==##GiveR or ##ShowR)
           {   i=inputobjs-->2; inputobjs-->2=inputobjs-->3; inputobjs-->3=i;
               if (accion==##GiveR) accion=##Dar; else accion=##Mostrar;
           }

           !  Convert "P, tell me about X" to "ask P about X"

           if (accion==##Hablar && inputobjs-->2==jugador && actor~=jugador)
           {   inputobjs-->2=actor; actor=jugador; accion=##Preguntar;
           }

           !  Convert "ask P for X" to "P, give X to me"

           if (accion==##Pedir && inputobjs-->2~=jugador && actor==jugador)
           {   actor=inputobjs-->2; inputobjs-->2=inputobjs-->3;
               inputobjs-->3=jugador; accion=##Dar;
           }

           !  For old, obsolete code: palabra_especial contains the topic word
           !  in conversation

           if (accion==##Preguntar or ##Hablar or ##Responder)
               palabra_especial = numero_especial1;

           !  --------------------------------------------------------------

           banderamulti=false; amodo_noposeido=modo_noposeido; modo_noposeido=false;
           !  For implicit taking and multiple object detection

          .begin__action;
           dat1 = 0; dat2 = 0; i=inputobjs-->1;
           if (i>=1) dat1=inputobjs-->2;
           if (i>=2) dat2=inputobjs-->3;

           !  dat1 and dat2 hold: object numbers, or 0 for "multiple object",
           !  or 1 for "a number or dictionary address"

           if (dat1 == 1) uno = numero_especial1; else uno = dat1;
           if (dat2 == 1)
           {   if (dat1 == 1) otro = numero_especial2;
               else otro = numero_especial1;
           } else otro = dat2;

           !  --------------------------------------------------------------

           if (actor~=jugador)
           {
           !  The jugador's "ordenes" property can refuse to allow conversation
           !  here, by returning true.  If not, the order is sent to the
           !  other person's "ordenes" property.  If that also returns false,
           !  then: if it was a misunderstood command anyway, it is converted
           !  to an Answer accion (thus "floyd, grrr" ends up as
           !  "say grrr to floyd").  If it was a good command, it is finally
           !  offered to the Order: part of the other person's "vida"
           !  property, the old-fashioned way of dealing with conversation.

               j=EjecutarRutinas(jugador,ordenes);
               if (j==0)
               {   j=EjecutarRutinas(actor,ordenes);
                   if (j==0)
                   {   if (accion==##NoComprendido)
                       {   inputobjs-->3=actor; actor=jugador; accion=##Responder;
                           jump begin__action;
                       }
                       if (EjecutarVida(actor,##Orden)==0) M__L(##Orden,1,actor);
                   }
               }
               jump turn__end;
           }

           !  --------------------------------------------------------------
           !  Generate the accion...

           if ((i==0)
               || (i==1 && dat1 ~= 0)
               || (i==2 && dat1 ~= 0 && dat2 ~= 0))
           {   self.begin_action(accion, uno, otro, 0);
               jump turn__end;
           }

           !  ...unless a multiple object must be substituted.  First:
           !  (a) check the multiple list isn't empty;
           !  (b) warn the jugador if it has been cut short because too long;
           !  (c) generate a sequence of actions from the list
           !      (stopping in the event of death or movement away).

           banderamulti = true;
           j=objeto_multiple-->0;
           if (j==0) { M__L(##Miscelanea,2); jump late__error; }
           if (bandera_demasiados)
           {   bandera_demasiados = false; M__L(##Miscelanea,1); }
           i=localizacion;
           for (k=1:k<=j:k++)
           {   if (banderafin) break;
               if (localizacion ~= i)
               {   M__L(##Miscelanea, 51);
                   break;
               }
               l = objeto_multiple-->k;
               ActualizarPronombre(l);
               print (name) l, ": ";
               if (dat1 == 0)
               {   dat1 = l; self.begin_action(accion, l, otro, 0); dat1 = 0;
               }
               else
               {   dat2 = l; self.begin_action(accion, uno, l, 0); dat2 = 0;
               }
           }

           !  --------------------------------------------------------------

           .turn__end;

           !  No time passes if either (i) the verb was meta, or
           !  (ii) we've only had the implicit take antes the "real"
           !  accion to follow.

           if (modo_noposeido==1) { AnotarObjetosObtenidos(); continue; }
           if (meta) continue;
           if (~~banderafin) self.secuencia_fin_turno();
       }

           if (banderafin~=2) MasAlla();
           if (banderafin==0) jump very__late__error;

           print "^^    ";
           if (banderafin==1) M__L(##Miscelanea,3);
           if (banderafin==2) M__L(##Miscelanea,4);
           if (banderafin>2)  { print " "; MensajeMuerte(); print " "; }
           #Ifndef NO_PUNTUACION;
             PuntuacionSub();
           #Endif; ! NO_PUNTUACION
           ActualizarEstatus();
           AfterGameOver();
       ],

       secuencia_fin_turno
       [ i j;

           turnos++;
           if (la_hora~=NULL)
           {   if (hora_freq>=0) la_hora=la_hora+hora_freq;
               else
               {   hora_incr--;
                   if (hora_incr==0)
                   {   la_hora++;
                       hora_incr = -hora_freq;
                   }
               }
               la_hora=la_hora % 1440;
           }

           #Ifdef DEBUG;
           if (debug_flag & 4 ~= 0)
           {   for (i=0: i<relojes_activos: i++)
               {   j=los_relojes-->i;
                   if (j~=0)
                   {   print (name) (j&~WORD_HIGHBIT), ": ";
                       if (j & WORD_HIGHBIT) print "daemon";
                       else
                           print "reloj al que faltan ",
                                 j.tiempo_restante, " turnos para dispararse";
                       new_line;
                   }
               }
           }
           #Endif;

           for (i=0: i<relojes_activos: i++)
           {   if (banderafin) return;
               j=los_relojes-->i;
               if (j~=0)
               {   if (j & WORD_HIGHBIT) EjecutarRutinas(j&~WORD_HIGHBIT,daemon);
                   else
                   {   if (j.tiempo_restante==0)
                       {   PararReloj(j);
                           EjecutarRutinas(j,tiempo_agotado);
                       }
                       else
                           j.tiempo_restante=j.tiempo_restante-1;
                   }
               }
           }
           if (banderafin) return;

           razon_alcance=RAZON_CADA_TURNO; palabra_verbo=0;
           EfectuarAccionesAlcance(localizacion);
           BuscarEnAlcance(TopeAlcanzable(jugador), jugador, 0);
           razon_alcance=RAZON_PARSING;

           if (banderafin) return;

           PasaElTiempo();

           if (banderafin) return;

           AjustarLuz();

           if (banderafin) return;

           AnotarObjetosObtenidos();
       ],

       begin_action
       [ a n s source   sa sn ss;
           sa = accion; sn = uno; ss = otro;
           accion = a; uno = n; otro = s;
           #Ifdef DEBUG;
           if (debug_flag & 2 ~= 0) TrazarAccion(source);
           #Ifnot;
           source = 0;
           #Endif;
           #Iftrue (Grammar__Version == 1);
           if ((meta || RutinasAntes()==false) && accion<256)
               ActionPrimitive();
           #Ifnot;
           if ((meta || RutinasAntes()==false) && accion<4096)
               ActionPrimitive();
           #Endif;
           accion = sa; uno = sn; otro = ss;
       ],
  has  propio;

#Ifdef TARGET_ZCODE;

[ ActionPrimitive;
  indirect(#actions_table-->accion);
];

#Ifnot; ! TARGET_GLULX

[ ActionPrimitive;
  indirect(#actions_table-->(accion+1));
];

#Endif; ! TARGET_

[ AfterGameOver i;
   .RRQPL;
   M__L(##Miscelanea,5);
   .RRQL;
   print "> ";
#Ifdef TARGET_ZCODE;
   #IfV3; read buffer parse; #Endif;
   temp_global=0;
   #IfV5; read buffer parse DibujarLineaEstado; #Endif;
#Ifnot; ! TARGET_GLULX
   KeyboardPrimitive(buffer, parse);
#Endif; ! TARGET_
   i=parse-->1;
   if (i==TERMINAR1__WD or TERMINAR2__WD)
   {
#Ifdef TARGET_ZCODE;
       quit;
#Ifnot; ! TARGET_GLULX
       quit;
#Endif; ! TARGET_
   }
   if (i==REINICIAR__WD)
   {
#Ifdef TARGET_ZCODE;
       @restart;
#Ifnot; ! TARGET_GLULX
       @restart;
#Endif; ! TARGET_
   }
   if (i==RECUPERAR__WD)      { RestaurarSub(); jump RRQPL; }
#Ifndef NO_PUNTUACION;
   if (i==PUNTUACION1__WD or PUNTUACION2__WD && HAY_TAREAS==0)
   {   new_line; PuntuacionTotalSub(); jump RRQPL; }
#Endif; ! NO_PUNTUACION
   if (banderafin==2 && i==CURIOSIDADES__WD && HAY_CURIOSIDADES==0)
   {   new_line; Curiosidades(); jump RRQPL; }
   #IfV5;
   if (i==ANULAR1__WD or ANULAR2__WD or ANULAR3__WD)
   {   if (bandera_deshacer==0)
       {   M__L(##Miscelanea,6);
           jump RRQPL;
       }
       if (bandera_deshacer==1) jump UndoFailed2;
#Ifdef TARGET_ZCODE;
       @restore_undo i;
#Ifnot; ! TARGET_GLULX
       @restoreundo i;
       i = (~~i);
#Endif; ! TARGET_
       if (i==0)
       {   .UndoFailed2; M__L(##Miscelanea,7);
       }
       jump RRQPL;
   }
   #Endif;
   M__L(##Miscelanea,8);
   jump RRQL;
];

[ R_Process a i j s1 s2;
   s1 = dat1; s2 = dat2;
   dat1 = i; dat2 = j; LibreriaInform.begin_action(a, i, j, 1);
   dat1 = s1; dat2 = s2;
];

[ AnotarObjetosObtenidos i;
  objectloop (i in jugador && i hasnt movido)
  {   give i movido;
      if (i has valepuntos)
      {   puntuacion = puntuacion + PUNTOS_OBJETO;
          puntos_cosas = puntos_cosas + PUNTOS_OBJETO;
      }
  }
];

! ----------------------------------------------------------------------------

[ PruebaDeAlcance obj act a al sr x y;
  x=parser_uno; y=parser_dos;
  parser_uno=obj; parser_dos=0; a=actor; al=localizacion_actor;
  sr=razon_alcance; razon_alcance=RAZON_TESTALCANCE;
  if (act==0) actor=jugador; else actor=act;
  localizacion_actor=TopeAlcanzable(actor);
  BuscarEnAlcance(localizacion_actor,actor,0); razon_alcance=sr; actor=a;
  localizacion_actor=al; parser_uno=x; x=parser_dos; parser_dos=y;
  return x;
];

[ BucleAlcance routine act x y a al;
  x = parser_uno; y=razon_alcance; a=actor; al=localizacion_actor;
  parser_uno=routine; if (act==0) actor=jugador; else actor=act;
  localizacion_actor=TopeAlcanzable(actor);
  razon_alcance=RAZON_BUCLEALCANCE;
  BuscarEnAlcance(localizacion_actor,actor,0);
  parser_uno=x; razon_alcance=y; actor=a; localizacion_actor=al;
];

[ RutinasAntes;
  if (RutinaPreJuego()~=0) rtrue;
  if (EjecutarRutinas(jugador,ordenes)~=0) rtrue;
  if (localizacion~=0 && EjecutarRutinas(localizacion,antes)~=0) rtrue;
  razon_alcance=RAZON_REACCIONAR_ANTES; parser_uno=0;
  BuscarEnAlcance(TopeAlcanzable(jugador),jugador,0); razon_alcance=RAZON_PARSING;
  if (parser_uno~=0) rtrue;
  if (dat1>1 && EjecutarRutinas(dat1,antes)~=0) rtrue;
  rfalse;
];

[ RutinasDespues;
  razon_alcance=RAZON_REACCIONAR_DESPUES; parser_uno=0;
  BuscarEnAlcance(TopeAlcanzable(jugador),jugador,0); razon_alcance=RAZON_PARSING;
  if (parser_uno~=0) rtrue;
  if (localizacion~=0 && EjecutarRutinas(localizacion,despues)~=0) rtrue;
  if (dat1>1 && EjecutarRutinas(dat1,despues)~=0) rtrue;
  return RutinaPostJuego();
];

[ EjecutarVida a j;
#Ifdef DEBUG;
   if (debug_flag & 2 ~= 0) TrazarAccion(2, j);
#Endif;
   codigo_razon = j; return EjecutarRutinas(a,vida);
];

[ ZRegion addr;
  switch(metaclass(addr))       ! Left over from Inform 5
  {   nothing: return 0;
      Object, Class: return 1;
      Routine: return 2;
      String: return 3;
  }
];

[ ImprimirOEjecutar obj prop flag;
  if (obj.#prop > WORDSIZE) return EjecutarRutinas(obj,prop);
  if (obj.prop==NULL) rfalse;
  switch(metaclass(obj.prop))
  {   Class, Object, nothing: return ErrorDeEjecucion(2,obj,prop);
      String: print (string) obj.prop; if (flag==0) new_line; rtrue;
      Routine: return EjecutarRutinas(obj,prop);
  }
];

[ ValorOEjecutar obj prop;
  !### this is entirely unlikely to work. Does anyone care?
  if (obj.prop < 256) return obj.prop;
  return EjecutarRutinas(obj, prop);
];

[ EjecutarRutinas obj prop;
   if (obj == LaOscuridad
       && prop ~= inicial or nombre_corto or descripcion) obj=localizacion_real;
   if (obj.&prop == 0) rfalse;
   sw__var=accion;
   if (prop==vida) sw__var=codigo_razon;
   return obj.prop();
];

#Ifdef TARGET_ZCODE;

[ CambiarDefecto prop val a b;
   ! Use assembly-language here because -S compilation won't allow this:
   @loadw 0 5 -> a;
   b = prop-1;
   @storew a b val;
];

#Ifnot; ! TARGET_GLULX

[ CambiarDefecto prop val;
   ! Use assembly-language here because -S compilation won't allow this:
   ! #cpv__start-->prop = val;
   @astore #cpv__start prop val;
];

#Endif; ! TARGET_

! ----------------------------------------------------------------------------

[ ArrancarReloj obj timer i;
   for (i=0:i<relojes_activos:i++)
       if (los_relojes-->i==obj) rfalse;
   for (i=0:i<relojes_activos:i++)
       if (los_relojes-->i==0) jump FoundTSlot;
   i=relojes_activos++;
   if (i >= MAX_RELOJES) { ErrorDeEjecucion(4); return; }
   .FoundTSlot;
   if (obj.&tiempo_restante==0) { ErrorDeEjecucion(5,obj); return; }
   los_relojes-->i=obj; obj.tiempo_restante=timer;
];

[ PararReloj obj i;
   for (i=0:i<relojes_activos:i++)
       if (los_relojes-->i==obj) jump FoundTSlot2;
   rfalse;
   .FoundTSlot2;
   if (obj.&tiempo_restante==0) { ErrorDeEjecucion(5,obj); return; }
   los_relojes-->i=0; obj.tiempo_restante=0;
];

[ ArrancarDaemon obj i;
   for (i=0:i<relojes_activos:i++)
       if (los_relojes-->i == WORD_HIGHBIT + obj)
           rfalse;
   for (i=0:i<relojes_activos:i++)
       if (los_relojes-->i==0) jump FoundTSlot3;
   i=relojes_activos++;
   if (i >= MAX_RELOJES) ErrorDeEjecucion(4);
   .FoundTSlot3;
   los_relojes-->i = WORD_HIGHBIT + obj;
];

[ PararDaemon obj i;
   for (i=0:i<relojes_activos:i++)
       if (los_relojes-->i == WORD_HIGHBIT + obj) jump FoundTSlot4;
   rfalse;
   .FoundTSlot4;
   los_relojes-->i=0;
];

! ----------------------------------------------------------------------------

[ ActualizarEstatus;
   if (la_hora==NULL)
   {   lineaEstado1=puntuacion; lineaEstado2=turnos; }
   else
   {   lineaEstado1=la_hora/60; lineaEstado2=la_hora%60; }
];

[ PonerLaHora t s;
   la_hora=t; hora_freq=s; hora_incr=0;
   if (s<0) hora_incr=0-s;
];

#Ifndef NO_PUNTUACION;
  [ NotificarLaPuntuacion;
  #Ifdef TARGET_GLULX;
     glk($0086, 6); ! set note style
  #Endif; ! TARGET_GLULX
     print "^[";  M__L(##Miscelanea, 50, puntuacion-punt_anterior);  print ".]^";
  #Ifdef TARGET_GLULX;
     glk($0086, 0); ! set normal style
  #Endif; ! TARGET_GLULX
  ];
#Endif; ! NO_PUNTUACION

! ----------------------------------------------------------------------------

[ AjustarLuz flag i;
   i=banderaluz;
   banderaluz=HayLuz(parent(jugador));

   if (i==0 && banderaluz==1)
   {   localizacion=localizacion_real; if (flag==0) <Mirar>;
   }

   if (i==1 && banderaluz==0)
   {   localizacion_real = localizacion; localizacion = LaOscuridad;
       if (flag==0) { AnotarLlegada();
                      return M__L(##Miscelanea, 9); }
   }
   if (i == 0 && banderaluz == 0)
     localizacion = LaOscuridad;
];

[ HayLuz i j;
   if (i==0) rfalse;
   if (i has luz) rtrue;
   objectloop (j in i)
       if (TieneFuenteDeLuz(j)==1) rtrue;
   if (i has recipiente)
   {   if (i has abierto || i has transparente)
           return HayLuz(parent(i));
   }
   else
   {   if (i has entrable || i has transparente || i has soporte)
           return HayLuz(parent(i));
   }
   rfalse;
];

[ HidesLightSource obj;
    if (obj == jugador) rfalse;
    if (obj has transparente or soporte) rfalse;
    if (obj has recipiente) return (obj hasnt abierto);
    return (obj hasnt entrable);
];

[ TieneFuenteDeLuz i j ad;
   if (i==0) rfalse;
   if (i has luz) rtrue;
   if (i has entrable || SeVeATraves(i)==1)
       if (~~(HidesLightSource(i)))
           objectloop (j in i)
               if (TieneFuenteDeLuz(j)==1) rtrue;
   ad = i.&suma_al_alcance;
   if (parent(i)~=0 && ad ~= 0)
   {   if (metaclass(ad-->0) == Routine)
       {   paa_tfl = 0; bandera_paa = 1;
           EjecutarRutinas(i, suma_al_alcance);
           bandera_paa = 0; if (paa_tfl == 1) rtrue;
       }
       else
       {   for (j=0:(WORDSIZE*j)<i.#suma_al_alcance:j++)
               if (TieneFuenteDeLuz(ad-->j)==1) rtrue;
       }
   }
   rfalse;
];

[ CambiarJugador obj flag i;
!  if (obj.&cantidad==0) return ErrorDeEjecucion(7,obj);
  if (actor==jugador) actor=obj;
  give jugador ~transparente ~oculto;
  i=obj; while(parent(i)~=0) { if (i has animado) give i transparente;
                               i=parent(i); }
  if (jugador==objjugador) jugador.nombre_corto=PREVIOYO__TX;

  jugador=obj;

  if (jugador==objjugador) jugador.nombre_corto=NULL;
  give jugador transparente oculto animado propio;
  i=jugador; while(parent(i)~=0) i=parent(i); localizacion=i;
  localizacion_real=localizacion;
  MoverObjetosFlotantes();
  banderaluz=HayLuz(parent(jugador));
  if (banderaluz==0) localizacion=LaOscuridad;
  bandera_imprime_jugador=flag;
];

! ----------------------------------------------------------------------------

#Ifdef DEBUG;
#Ifdef TARGET_ZCODE;
[ DepurarParametro w x n l;
  x=0-->4; x=x+(x->0)+1; l=x->0; n=(x+1)-->0; x=w-(x+3);
  print w;
  if (w>=1 && w<=objeto_raiz) print " (", (name) w, ")";
  if (x%l==0 && (x/l)<n) print " ('", (address) w, "')";
];
[ DepurarAccion a anames;
#Iftrue (Grammar__Version==1);
  if (a>=256) { print "<acción falsa ", a-256, ">"; return; }
#Ifnot;
  if (a>=4096) { print "<acción falsa ", a-4096, ">"; return; }
#Endif;
  anames = #identifiers_table;
  anames = anames + 2*(anames-->0) + 2*48;
  print (string) anames-->a;
];
[ DepurarAtributo a anames;
  if (a<0 || a>=48) print "<atributo no válido ", a, ">";
  else
  {   anames = #identifiers_table; anames = anames + 2*(anames-->0);
      print (string) anames-->a;
  }
];
#Ifnot; ! TARGET_GLULX
[ DepurarParametro w endmem;
  print w;
  @getmemsize endmem;
  if (w >= 1 && w < endmem) {
    if (w->0 >= $70 && w->0 < $7F) print " (", (name) w, ")";
    if (w->0 >= $60 && w->0 < $6F) print " ('", (address) w, "')";
  }
];
[ DepurarAccion a str;
  if (a>=4096) { print "<acción falsa ", a-4096, ">"; return; }
  if (a<0 || a>=#identifiers_table-->7) print "<acción no válida ", a, ">";
  else {
    str = #identifiers_table-->6;
    str = str-->a;
    if (str) print (string) str;
    else print "<acción sin nombre ", a, ">";
  }
];
[ DepurarAtributo a str;
  if (a<0 || a>=NUM_ATTR_BYTES*8) print "<atributo no válido ", a, ">";
  else {
    str = #identifiers_table-->4;
    str = str-->a;
    if (str) print (string) str;
    else print "<atributo sin nombre ", a, ">";
  }
];
#Endif; ! TARGET_
[ TrazarAccion source ar;
  if (source<2) print "[ Acción ", (DepurarAccion) accion;
  else
  {   if (ar==##Orden)
          print "[ Orden para ", (name) actor, ": ", (DepurarAccion) accion;
      else
          print "[ Método Vida ", (DepurarAccion) ar;
  }
  if (uno~=0)   print " con uno ", (DepurarParametro) uno;
  if (otro~=0) print " y otro ", (DepurarParametro) otro;
  if (source==0) print " ";
  if (source==1) print " (desde un comando < >) ";
  print "]^";
];
[ DepurarToken token;
  AnalizarToken(token);
  switch(ttipo_encontrado)
  {   TT_ILEGAL: print "<número de token ilegal ", token, ">";
      TT_ELEMENTAL:
      switch(tdatos_encontrado)
      {   TOKEN_NOMBRE:        print "noun";
          TOKEN_POSEIDO:        print "held";
          TOKEN_MULTI:       print "multi";
          TOKEN_MULTIPOSEIDO:   print "multiheld";
          TOKEN_MULTIEXCEPTO: print "multiexcept";
          TOKEN_MULTIDENTRO: print "multiinside";
          TOKEN_CRIATURA:    print "creature";
          TOKEN_ESPECIAL:     print "special";
          TOKEN_NUMERO:      print "number";
          TOKEN_TEMA:       print "topic";
          TOKEN_FINAL:       print "END";
      }
      TT_PREPOSICION:
          print "'", (address) tdatos_encontrado, "'";
      TT_FILTRO_RUTINA:
      #Ifdef INFIX; print "noun=", (InfixPrintPA) tdatos_encontrado;
      #Ifnot; print "noun=Rutina(", tdatos_encontrado, ")"; #Endif;
      TT_FILTRO_ATRIB:
          print (DepurarAtributo) tdatos_encontrado;
      TT_ALCANCE:
      #Ifdef INFIX; print "scope=", (InfixPrintPA) tdatos_encontrado;
      #Ifnot; print "scope=Rutina(", tdatos_encontrado, ")"; #Endif;
      TT_RPG:
      #Ifdef INFIX; print (InfixPrintPA) tdatos_encontrado;
      #Ifnot; print "Rutina(", tdatos_encontrado, ")"; #Endif;
  }
];
[ DepurarLineaGramatica contadorp;
  print " * ";
  for (:linea_token-->contadorp ~= TOKEN_FINAL:contadorp++)
  {   if ((linea_token-->contadorp)->0 & $10) print "/ ";
      print (DepurarToken) linea_token-->contadorp, " ";
  }
  print "-> ", (DepurarAccion) accion_que_seria;
  if (accion_invertida) print " reverse";
];
#Ifdef TARGET_ZCODE;
[ MostrarVerboSub address lines da meta i j;
    if (((uno->#dict_par1) & 1) == 0)
      "Prueba poniendo ~xverbo~ seguido del nombre de un verbo.";
    meta=((uno->#dict_par1) & 2)/2;
    i = $ff-(uno->#dict_par2);
    address = (0-->7)-->i;
    lines = address->0;
    address++;
    print "Verb ";
    if (meta) print "meta ";
    da = 0-->4;
    for (j=0:j < (da+5)-->0:j++)
        if (da->(j*9 + 14) == $ff-i)
            print "'", (address) (da + 9*j + 7), "' ";
    new_line;
    if (lines == 0) "no tiene líneas de gramática.";
    for (:lines > 0:lines--)
    {   address = DesempaquetarLineaGramatica(address);
        print "    "; DepurarLineaGramatica(); new_line;
    }
];
#Ifnot; ! TARGET_GLULX
[ MostrarVerboSub address lines i j meta wd dictlen entrylen;
  if (uno == 0 || ((uno->#dict_par1) & 1) == 0)
      "Prueba poniendo ~xverbo~ seguido del nombre de un verbo.";
  meta=((uno->#dict_par1) & 2)/2;
  i = $ff-(uno->#dict_par2);
  address = (#grammar_table)-->(i+1);
  lines = address->0;
  address++;
  print "Verb ";
  if (meta) print "meta ";
  dictlen = #dictionary_table-->0;
  entrylen = DICT_WORD_SIZE + 7;
  for (j=0:j<dictlen:j++) {
    wd = #dictionary_table + WORDSIZE + entrylen*j;
    if (wd->#dict_par2 == $ff-i)
      print "'", (address) wd, "' ";
  }
  new_line;
  if (lines == 0) "no tiene líneas de gramática.";
  for (:lines > 0:lines--) {
    address = DesempaquetarLineaGramatica(address);
    print "    "; DepurarLineaGramatica(); new_line;
  }
];
#Endif; ! TARGET_
[ MostrarObjetoSub c f l a n x numattr;
   if (uno==0) uno=localizacion;
   objectloop (c ofclass Class) if (uno ofclass c) { f++; l=c; }
   if (f == 1) print (name) l, " ~"; else print "Object ~";
   print (name) uno, "~ (", uno, ")";
   if (parent(uno)~=0) print " en ~", (name) parent(uno), "~";
   new_line;
   if (f > 1)
   {   print "  class ";
       objectloop (c ofclass Class) if (uno ofclass c) print (name) c, " ";
       new_line;
   }
#Ifdef TARGET_ZCODE;
   numattr = 48;
#Ifnot; ! TARGET_GLULX
   numattr = NUM_ATTR_BYTES * 8;
#Endif; ! TARGET_
   for (a=0,f=0:a<numattr:a++) if (uno has a) f=1;
   if (f)
   {   print "  has ";
       for (a=0:a<numattr:a++) if (uno has a) print (DepurarAtributo) a, " ";
       new_line;
   }
   if (uno ofclass Class) return;

   f=0;
#Ifdef TARGET_ZCODE;
   l = #identifiers_table-->0;
#Ifnot; ! TARGET_GLULX
   l = INDIV_PROP_START + #identifiers_table-->3;
#Endif; ! TARGET_
   for (a=1:a<=l:a++)
   {   if ((a~=2 or 3) && uno.&a)
       {   if (f==0) { print "  with "; f=1; }
           print (property) a;
           n = uno.#a;
           for (c=0:WORDSIZE*c<n:c++)
           {   print " ";
               x = (uno.&a)-->c;
               if (a==nombre) print "'", (address) x, "'";
               else
               {   if (a==cantidad or capacidad or tiempo_restante)
                       print x;
                   else
                   {   switch(x)
                       {   NULL: print "NULL";
                           0: print "0";
                           1: print "1";
                           default:
                           switch(metaclass(x))
                           {   Class, Object: print (name) x;
                               String: print "~", (string) x, "~";
                               Routine: print "[...]";
                           }
                           print " (", x, ")";
                       }
                   }
               }
           }
           print ",^       ";
       }
   }
!   if (f==1) new_line;
];
#Endif;

! ----------------------------------------------------------------------------
!  Except in Version 3, the DibujarLineaEstado routine does just that: this is
!  provided explicitly so that it can be Replace'd to change the style, and
!  as written it emulates the ordinary Standard game status line, which is
!  drawn in hardware
! ----------------------------------------------------------------------------

#Ifdef TARGET_ZCODE;

#IfV5;
[ DibujarLineaEstado width posa posb;
   @split_window 1; @set_window 1; @set_cursor 1 1; style reverse;
   width = 0->33; posa = width-26; posb = width-13;
   spaces width;
   @set_cursor 1 2;
   if (localizacion == LaOscuridad)
     print (name) localizacion;
   else
   {   FindVisibilityLevels();
       if (techo_de_visibilidad == localizacion)
           print (name) localizacion;
       else print (The) techo_de_visibilidad;
   }
!   if ((0->1)&2 == 0)
   if (la_hora == NULL)
   {   if (width > 76)
       {
       #Ifndef NO_PUNTUACION;
         @set_cursor 1 posa; print (string) PUNTUACION__TX, lineaEstado1;
       #Endif; ! NO_PUNTUACION
         @set_cursor 1 posb; print (string) JUGADAS__TX, lineaEstado2;
       }
       if (width > 63 && width <= 76)
       {
       #Ifndef NO_PUNTUACION;
         @set_cursor 1 posb; print lineaEstado1, "/", lineaEstado2;
       #Ifnot;
         posb = posb + 2;  ! Esto es porque en este caso no hay barra ('/')
         @set_cursor 1 posb; print lineaEstado2;
       #Endif; ! NO_PUNTUACION
       }
   }
   else
   {   @set_cursor 1 posa;
       print (string) HORA__TX;
       IdiomaHoraDelDia(lineaEstado1, lineaEstado2);
   }
   @set_cursor 1 1; style roman; @set_window 0;
];
#Endif;

#Endif; ! TARGET_ZCODE

#Ifdef TARGET_GLULX;

[ StatusLineHeight hgt parwin;
  if (gg_statuswin == 0)
    return;
  if (hgt == gg_statuswin_cursize)
    return;
  parwin = glk($0029, gg_statuswin); ! window_get_parent
  glk($0026, parwin, $12, hgt, 0); ! window_set_arrangement
  gg_statuswin_cursize = hgt;
];

[ DibujarLineaEstado width height posa posb;
    ! If we have no status window, we must not try to redraw it.
    if (gg_statuswin == 0)
        return;

    ! If there is no jugador localizacion, we shouldn't try either.
    if (localizacion == nothing || parent(jugador) == nothing)
        return;

    glk($002F, gg_statuswin); ! set_window
    StatusLineHeight(gg_statuswin_size);

    glk($0025, gg_statuswin, gg_arguments, gg_arguments+4); ! window_get_size
    width = gg_arguments-->0;
    height = gg_arguments-->1;
    posa = width-26; posb = width-13;

    glk($002A, gg_statuswin); ! window_clear

    glk($002B, gg_statuswin, 1, 0); ! window_move_cursor
    if (localizacion == LaOscuridad) {
        print (name) localizacion;
    }
    else {
        FindVisibilityLevels();
        if (techo_de_visibilidad == localizacion)
            print (name) localizacion;
        else
            print (The) techo_de_visibilidad;
    }

    if (width > 66) {
      #Ifndef NO_PUNTUACION;
        glk($002B, gg_statuswin, posa-1, 0); ! window_move_cursor
        print (string) PUNTUACION__TX, lineaEstado1;
      #Endif; ! NO_PUNTUACION
        glk($002B, gg_statuswin, posb-1, 0); ! window_move_cursor
        print (string) JUGADAS__TX, lineaEstado2;
    }
    if (width > 53 && width <= 66) {
      #Ifndef NO_PUNTUACION;
        glk($002B, gg_statuswin, posb-1, 0); ! window_move_cursor
        print lineaEstado1, "/", lineaEstado2;
      #Ifnot;
        glk($002B, gg_statuswin, posb+1, 0); ! window_move_cursor
        print lineaEstado2;
      #Endif; ! NO_PUNTUACION
    }

    glk($002F, gg_mainwin); ! set_window
];

[ Box__Routine maxwid arr ix lines lastnl parwin;
    maxwid = 0; ! squash compiler warning
    lines = arr-->0;

    if (gg_quotewin == 0) {
        gg_arguments-->0 = lines;
        ix = InitGlkWindow(GG_QUOTEWIN_ROCK);
        if (ix == 0)
            gg_quotewin = glk($0023, gg_mainwin, $12, lines, 3,
                GG_QUOTEWIN_ROCK); ! window_open
    }
    else {
        parwin = glk($0029, gg_quotewin); ! window_get_parent
        glk($0026, parwin, $12, lines, 0); ! window_set_arrangement
    }

    lastnl = true;
    if (gg_quotewin) {
        glk($002A, gg_quotewin); ! window_clear
        glk($002F, gg_quotewin); ! set_window
        lastnl = false;
    }

    ! If gg_quotewin is zero here, the quote just appears in the story window.

    glk($0086, 7); ! set blockquote style
    for (ix=0 : ix<lines : ix++) {
        print (string) arr-->(ix+1);
        if (ix < lines-1 || lastnl) new_line;
    }
    glk($0086, 0); ! set normal style

    if (gg_quotewin) {
        glk($002F, gg_mainwin); ! set_window
    }
];

#Endif; ! TARGET_GLULX

#Ifdef TARGET_GLULX;

[ GGInitialise res;
    @gestalt 4 2 res; ! Test if this interpreter has Glk.
    if (res == 0) {
      ! Without Glk, we're entirely screwed.
      quit;
    }
    ! Set the VM's I/O system to be Glk.
    @setiosys 2 0;

    ! First, we must go through all the Glk objects that exist, and see
    ! if we created any of them. One might think this strange, since the
    ! program has just started running, but remember that the jugador might
    ! have just typed "restart".
    GGRecoverObjects();

    res = InitGlkWindow(0);
    if (res ~= 0)
        return;

    ! Now, gg_mainwin and gg_storywin might already be set. If not, set them.

    if (gg_mainwin == 0) {
        ! Open the story window.
        res = InitGlkWindow(GG_MAINWIN_ROCK);
        if (res == 0)
            gg_mainwin = glk($0023, 0, 0, 0, 3, GG_MAINWIN_ROCK); ! window_open
        if (gg_mainwin == 0) {
            ! If we can't even abierto one window, there's no point in going on.
            quit;
        }
    }
    else {
        ! There was already a story window. We should erase it.
        glk($002A, gg_mainwin); ! window_clear
    }

    if (gg_statuswin == 0) {
        res = InitGlkWindow(GG_STATUSWIN_ROCK);
        if (res == 0) {
            gg_statuswin_cursize = gg_statuswin_size;
            gg_statuswin = glk($0023, gg_mainwin, $12, gg_statuswin_cursize,
                4, GG_STATUSWIN_ROCK); ! window_open
        }
    }
    else  ! [080625] Ya hay una barra de estado, la 'blanqueamos'
      glk ($002A, gg_statuswin); ! window_clear
    ! It's possible that the status window couldn't be opened, in which case
    ! gg_statuswin is now zero. We must allow for that later on.

    glk($002F, gg_mainwin); ! set_window

    InitGlkWindow(1);
];

[ GGRecoverObjects id;
    ! If GGRecoverObjects() has been called, all these stored IDs are
    ! invalid, so we start by clearing them all out.
    ! (In fact, despues a restoreundo, some of them may still be good.
    ! For simplicity, though, we assume the general case.)
    gg_mainwin = 0;
    gg_statuswin = 0;
    gg_quotewin = 0;
    gg_scriptfref = 0;
    gg_scriptstr = 0;
    gg_savestr = 0;
    gg_statuswin_cursize = 0;
#Ifdef DEBUG;
    gg_commandstr = 0;
    gg_command_reading = false;
#Endif;
    ! Also tell the game to clear its object references.
    IdentifyGlkObject(0);

    id = glk($0040, 0, gg_arguments); ! stream_iterate
    while (id) {
        switch (gg_arguments-->0) {
            GG_SAVESTR_ROCK: gg_savestr = id;
            GG_SCRIPTSTR_ROCK: gg_scriptstr = id;
#Ifdef DEBUG;
            GG_COMMANDWSTR_ROCK: gg_commandstr = id;
                                 gg_command_reading = false;
            GG_COMMANDRSTR_ROCK: gg_commandstr = id;
                                 gg_command_reading = true;
#Endif;
            default: IdentifyGlkObject(1, 1, id, gg_arguments-->0);
        }
        id = glk($0040, id, gg_arguments); ! stream_iterate
    }

    id = glk($0020, 0, gg_arguments); ! window_iterate
    while (id) {
        switch (gg_arguments-->0) {
            GG_MAINWIN_ROCK: gg_mainwin = id;
            GG_STATUSWIN_ROCK: gg_statuswin = id;
            GG_QUOTEWIN_ROCK: gg_quotewin = id;
            default: IdentifyGlkObject(1, 0, id, gg_arguments-->0);
        }
        id = glk($0020, id, gg_arguments); ! window_iterate
    }

    id = glk($0064, 0, gg_arguments); ! fileref_iterate
    while (id) {
        switch (gg_arguments-->0) {
            GG_SCRIPTFREF_ROCK: gg_scriptfref = id;
            default: IdentifyGlkObject(1, 2, id, gg_arguments-->0);
        }
        id = glk($0064, id, gg_arguments); ! fileref_iterate
    }

    ! Tell the game to tie up any loose ends.
    IdentifyGlkObject(2);
];

! This somewhat obfuscated function will print anything.
! It handles strings, functions (with optional arguments), objects,
! object properties (with optional arguments), and dictionary words.
! It does *not* handle plain integers, but you can use
! DecimalNumber or EnglishNumber to handle that case.
!
! Calling:                           Is equivalent to:
! -------                            ----------------
! PrintAnything()                    <nothing printed>
! PrintAnything(0)                   <nothing printed>
! PrintAnything("string");           print (string) "string";
! PrintAnything('word')              print (address) 'word';
! PrintAnything(obj)                 print (name) obj;
! PrintAnything(obj, prop)           obj.prop();
! PrintAnything(obj, prop, args...)  obj.prop(args...);
! PrintAnything(func)                func();
! PrintAnything(func, args...)       func(args...);
!
[ PrintAnything _vararg_count obj mclass;
    if (_vararg_count == 0)
        return;
    @copy sp obj;
    _vararg_count--;
    if (obj == 0)
        return;

    if (obj->0 == $60) {
        ! Dictionary word. Metaclass() can't catch this case, so we do
        ! it manually.
        print (address) obj;
        return;
    }

    mclass = metaclass(obj);
    switch (mclass) {
        nothing:
            return;
        String:
            print (string) obj;
            return;
        Routine:
            ! Call the function with all the arguments which are already
            ! on the stack.
            @call obj _vararg_count 0;
            return;
        Object:
            if (_vararg_count == 0) {
                print (name) obj;
            }
            else {
                ! Push the object back onto the stack, and call the
                ! veneer routine that handles obj.prop() calls.
                @copy obj sp;
                _vararg_count++;
                @call CA__Pr _vararg_count 0;
            }
            return;
    }
];

! This does the same as PrintAnything, but the output is sent to a
! byte array in memory. The first two arguments must be the array
! address and length; the following arguments are interpreted as
! for PrintAnything. The return value is the number of characters
! output.
! If the output is longer than the array length given, the extra
! characters are discarded, so the array does not overflow.
! (However, the return value is the total length of the output,
! including discarded characters.)

[ PrintAnyToArray _vararg_count arr arrlen str oldstr len;

   @copy sp arr;
   @copy sp arrlen;
   _vararg_count = _vararg_count - 2;

   oldstr = glk($0048); ! stream_get_current
   str = glk($0043, arr, arrlen, 1, 0); ! stream_open_memory
   if (str == 0)
       return 0;

   glk($0047, str); ! stream_set_current

   @call PrintAnything _vararg_count 0;

   glk($0047, oldstr); ! stream_set_current
   @copy $ffffffff sp;
   @copy str sp;
   @glk $0044 2 0; ! stream_close
   @copy sp len;
   @copy sp 0;

   return len;
];

! And this calls PrintAnyToArray on a particular array, jiggering
! the result to be a Glulx C-style ($E0) string.

Constant GG_ANYTOSTRING_LEN 66;
Array AnyToStrArr --> GG_ANYTOSTRING_LEN;
[ ChangeAnyToCString _vararg_count ix len;
   ix = GG_ANYTOSTRING_LEN-2;
   @copy ix sp;
   ix = AnyToStrArr+1;
   @copy ix sp;
   ix = _vararg_count+2;
   @call PrintAnyToArray ix len;
   AnyToStrArr->0 = $E0;
   if (len >= GG_ANYTOSTRING_LEN)
     len = GG_ANYTOSTRING_LEN-1;
   AnyToStrArr->(len+1) = 0;
   return AnyToStrArr;
];

#Endif; ! TARGET_GLULX

! This is a trivial function which just prints a number, in decimal
! digits. It may be useful as a stub to pass to PrintAnything.
[ DecimalNumber num;
    print num;
];

#IfV5;
Array StorageForShortName --> 161;
#Endif;

[ PonerArticuloDelante o acode pluralise  i artform findout;

   if (o provides articulos)
   {
       if ((o.&articulos)-->(acode+caso_nombre_corto*CasosLenguaje))
       print (string)
	   (o.&articulos)-->(acode+caso_nombre_corto*CasosLenguaje),
           " ";
       if (pluralise) return;
       print (PSN__) o; return;
   }

   if (o provides genero)
	i=o.genero;
   else i = ObtenerGNADeObjeto(o);
   if (pluralise>0)
   {   if (i<3 || (i>=6 && i<9)) i = i + 3;
   }
   i = IdiomaGNAsAArticulos-->i;

   artform = IdiomaArticulos
             + 3*WORDSIZE*IdiomaContracciones*(caso_nombre_corto + i*CasosLenguaje);

#Iftrue (IdiomaContracciones == 2);
   if (artform-->acode ~= artform-->(acode+3)) findout = true;
#Endif;
#Iftrue (IdiomaContracciones == 3);
   if (artform-->acode ~= artform-->(acode+3)) findout = true;
   if (artform-->(acode+3) ~= artform-->(acode+6)) findout = true;
#Endif;
#Iftrue (IdiomaContracciones == 4);
   if (artform-->acode ~= artform-->(acode+3)) findout = true;
   if (artform-->(acode+3) ~= artform-->(acode+6)) findout = true;
   if (artform-->(acode+6) ~= artform-->(acode+9)) findout = true;
#Endif;
#Iftrue (IdiomaContracciones > 4);
   findout = true;
#Endif;

#Ifdef TARGET_ZCODE;
   if (interprete_estandar ~= 0 && findout)
   {   StorageForShortName-->0 = 160;
       @output_stream 3 StorageForShortName;
       if (pluralise) print (number) pluralise; else print (PSN__) o;
       @output_stream -3;
       acode = acode + 3*IdiomaContraccion(StorageForShortName + 2);
   }
#Ifnot; ! TARGET_GLULX
   if (findout)
   {   if (pluralise)
           PrintAnyToArray(StorageForShortName, 160, EnglishNumber, pluralise);
       else
           PrintAnyToArray(StorageForShortName, 160, PSN__, o);
       acode = acode + 3*IdiomaContraccion(StorageForShortName);
   }
#Endif; ! TARGET_

   print (string) artform-->acode;
   if (pluralise) return;
   print (PSN__) o;
];

[ PSN__ o;
   if (o==0) { print (string) NADA__TX; rtrue; }
   switch(metaclass(o))
   {   Routine: print "<rutina ", o, ">"; rtrue;
       String:  print "<string ~", (string) o, "~>"; rtrue;
       nothing: print "<número de objeto ilegal ", o, ">"; rtrue;
   }
   if (o==jugador) { print (string) TUMISMO__TX; rtrue; }
   #Ifdef IdiomaImprimirNombreCorto;
   if (IdiomaImprimirNombreCorto(o)) rtrue;
   #Endif;
   if (modo_indef && o.&nombre_corto_indef~=0
       && ImprimirOEjecutar(o, nombre_corto_indef, 1)~=0) rtrue;
   if (o.&nombre_corto~=0 && ImprimirOEjecutar(o,nombre_corto,1)~=0) rtrue;
   print (object) o;
];

[ Indefart o i;
   i = modo_indef; modo_indef = true;
   if (o has propio) { modo_indef = NULL; print (PSN__) o; return; }
   if (o provides articulo)
   {   ImprimirOEjecutar(o,articulo,1); print " ", (PSN__) o; modo_indef = i; return;
   }
   PonerArticuloDelante(o, 2); modo_indef = i;
];
[ Defart o i;
   i = modo_indef; modo_indef = false;
   if (o has propio)
   { modo_indef = NULL; print (PSN__) o; modo_indef = i; return; }
   PonerArticuloDelante(o, 1); modo_indef = i;
];
[ CDefart o i;
   i = modo_indef; modo_indef = false;
   if (o has propio)
   { modo_indef = NULL; print (PSN__) o; modo_indef = i; return; }
   PonerArticuloDelante(o, 0); modo_indef = i;
];

[ PrintShortName o i;
   i = modo_indef; modo_indef = NULL;
   PSN__(o); modo_indef = i;
];

[ EnglishNumber n; IdiomaNumero(n); ];

[ PalabraNumero o i n;
  n = IdiomaNumeros-->0;
  for (i=1:i<=n:i=i+2)
      if (o == IdiomaNumeros-->i)
          return IdiomaNumeros-->(i+1);
  return 0;
];

[ ElementoCualquiera tab;
  if (tab-->0==0) return ErrorDeEjecucion(8);
  return tab-->(random(tab-->0));
];

! ----------------------------------------------------------------------------
!  Useful routine: unsigned comparison (for addresses in Z-machine)
!    Returns 1 if x>y, 0 if x=y, -1 if x<y
! ----------------------------------------------------------------------------

[ CompararSinSigno x y u v;
  if (x==y) return 0;
  if (x<0 && y>=0) return 1;
  if (x>=0 && y<0) return -1;
  u = x&~WORD_HIGHBIT; v= y&~WORD_HIGHBIT;
  if (u>v) return 1;
  return -1;
];

#Ifdef NITFOL_HOOKS;          ! Code contributed by Evin Robertson
#Ifdef TARGET_GLULX;          ! Might be nice for Z-machine games too,
                              ! but I'm not going to try to make this work
                              ! given #Ifdef funniness.

Array magic_array -->         ! This is so nitfol can do typo correction /
                              ! automapping / debugging on Glulx games
    $6e66726d $4d616763 $ff0010 ! Goes to 'NfrmMagc'  10 refers to length
    Magic_Global_Dispatch__
    DI__check_word            ! DI__check_word(buf, length)
    PrintShortName
    WV__Pr RV__Pr CA__Pr      ! obj.prop = x; x = obj.prop; obj.prop(x)
    RA__Pr RL__Pr RA__Sc      ! obj.&prop; obj.#prop; class::prop
    OP__Pr OC__Cl             ! obj provides prop; obj ofclass class
    OB__Move OB__Remove
    OB__Parent__ OB__Child__ OB__Sibling__  ! No explicit veneer for these
    ;

[ OB__Parent__ obj;
    return parent(obj);
];

[ OB__Child__ obj;
    return child(obj);
];

[ OB__Sibling__ obj;
    return sibling(obj);
];

[ Magic_Global_Dispatch__ glbl;
    switch(glbl) {
     0: if(localizacion==LaOscuridad) return localizacion_real;
        return localizacion;
     1: return Player;
     -1: return DireccionBrujula::cantidad; ! Silliness to make exist RA__Sc
                                            ! Should never be called.
    }
    return magic_array;       ! Silences a warning.
];

[ DI__check_word buf wlen  ix val res dictlen entrylen;
    ! Just like in Tokenise__.  In fact, Tokenise__ could call this if
    ! it wanted, instead of doing this itself.
    if (wlen > DICT_WORD_SIZE)
        wlen = DICT_WORD_SIZE;
    for (ix=0 : ix < wlen : ix++) {
        ! [080625] No es necesario pasar otra vez a minúscula
        ! gg_tokenbuf->ix = glk($00A0, buf->ix); ! glk_char_to_lower
        gg_tokenbuf->ix = buf->ix;
    }
    for ( : ix < DICT_WORD_SIZE : ix++) {
        gg_tokenbuf->ix = 0;
    }
    val = #dictionary_table + WORDSIZE;
    entrylen = DICT_WORD_SIZE + 7;
    @binarysearch gg_tokenbuf DICT_WORD_SIZE val entrylen dictlen 1 1 res;
    return res;
];

#Endif;
#Endif;

! ----------------------------------------------------------------------------

