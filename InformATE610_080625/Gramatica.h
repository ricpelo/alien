! ----------------------------------------------------------------------------
!  GRAMATICA: Gramática española
!
!  Para usar con Inform 6.21, InformATE! 6/10E
!  Número de Serie: 080625, Revisión: 6/10E
!
!  (c) Zak 2000, 2001
! ----------------------------------------------------------------------------

! Message "...Incluyendo Gramatica ";

System_file;

#Ifdef DEBUG;
  [ ActivarAcentosSub;
    quitacentos = 0;
    "Los acentos no serán eliminados del comando recibido.";
  ];

  [ DesactivarAcentosSub;
    quitacentos = 1;
    "Los acentos serán eliminados del comando recibido, pero sólo en
      las palabras que de otro modo no serían comprendidas.";
  ];
#Endif; ! DEBUG

! Elección del dialecto (afecta a la interpretación del
! verbo COGER únicamente)

[ DialectoSub;
  print "Actualmente estás jugando en el dialecto ";
  if (dialecto_sudamericano)
    print "sudamericano";
  else
    print "castellano";
  ". Puedes elegir dialecto usando el comando DIALECTO SUDAMERICANO \
    o bien DIALECTO CASTELLANO.";
];

[ DialectoSudSub;
  dialecto_sudamericano = 2;
  "Elegido dialecto SUDAMERICANO.";
];

[ DialectoCastSub;
  dialecto_sudamericano = 0;
  "Elegido dialecto CASTELLANO.";
];


[ SubirSub;
  <<Ir obj_arriba>>;
];

[ BajarSub p;         ! 021230
  p=parent(jugador);
  if ((p~=localizacion) && (p has soporte))
     if (uno~=nothing) <<Salirse uno>>;
     else <<Salirse p>>;
  if (uno==nothing)  <<Ir obj_abajo>>;
  if (uno has puerta) <<Meterse uno>>;
  M__L(##Meterse,2,uno);
];

Ifdef ADMITIR_COMANDO_SALIDAS;
  [ SalidasSub i flag flag2 j loc;
    print "Salidas visibles:";
    if (localizacion == LaOscuridad)
      loc = localizacion_real;
    else
      loc = localizacion;
    j = 0;
    objectloop (i in Brujula) {
      if (loc provides Salidas)
        switch (loc.Salidas (i))
        {
          false:
            flag  = false;           ! Mostrar la salida si existe la
            flag2 = false;           ! propiedad al_* y no es un string.
          true:
            j++;                     ! La dirección ya ha sido escrita.
            flag2 = true;
          2:
            flag2 = true;            ! No imprimir esta.
          default:
            flag  = true;            ! Imprimirla siempre.
        };  ! de switch

        if (loc provides (i.direcc_puerta) &&
          metaclass (loc.(i.direcc_puerta)) ~= nothing or string ||
          flag == true && flag2 == false)
        {
          if (j == 0)
            print " ";
          else
            print ", ";
          IdiomaDirecciones (i.direcc_puerta);
          j++;
        }  ! de if
    }  ! de objectloop
    if (j == 0)
      " ninguna.";
    ".";
  ];
Endif;  ! ADMITIR_COMANDO_SALIDAS

! TODO: ¿De verdad son necesarias tantas formas inglesas de los comandos?

#Ifndef NO_PUNTUACION;
Verb meta 'puntuacion' 'puntos' 'puntuaci'
  *                                   -> Puntuacion
  * 'total'/'detallada'               -> PuntuacionTotal;
VerboIrregular "conocer la puntuación" with imperativo 'puntuacion' 'puntos';

Verb meta 'total' 'pt'
  *                                   -> PuntuacionTotal;
VerboIrregular "conocer la puntuación detallada" with imperativo 'total' 'pt';
#Endif; ! NO_PUNTUACION

Verb meta 'q//' 'quit' 'terminar' 'fin' 'acabar' 'abandonar'
  *                                   -> Finalizar;
VerboIrregular "abandonar el juego" with imperativo 'q//' 'quit' 'terminar'
  'fin' 'acabar' 'abandonar';

Verb meta 'recuperar' 'cargar' 'load' 'restaurar' 'restore'
  *                                   -> Restaurar;
VerboIrregular "cargar un juego previamente guardado en disco" with imperativo
  'cargar' 'recuperar' 'load' 'restaurar' 'restore';

Verb meta 'reiniciar'
  *                                   -> Reiniciar;
VerboIrregular "reiniciar el juego" with imperativo 'reiniciar';

Verb meta 'verificar'
  *                                   -> Verificar;
VerboIrregular "verificar la corrección del juego" with imperativo 'verificar';

Verb meta 'save' 'guardar' 'salvar'
  *                                   -> Salvar;
VerboIrregular "guardar en disco el estado del juego" with imperativo 'save'
  'guardar' 'salvar';

Verb meta 'script' 'transcripcion'
  *                                   -> ActivarTranscripcion
  * 'off'/'no'                        -> DesactivarTranscripcion
  * 'on'/'si'                         -> ActivarTranscripcion;
VerboIrregular "activar la transcripción a disco" with imperativo 'script'
  'transcripcion';

Verb meta 'noscript' 'unscript' 'notranscripcion'
  *                                   -> DesactivarTranscripcion;
VerboIrregular "desactivar la transcripción a disco" with imperativo 'unscript'
  'noscript' 'notranscripcion';

Verb meta 'superbreve' 'corto'
  *                                   -> ModoM3;
VerboIrregular "cambiar a modo SUPERBREVE" with imperativo 'superbreve' 'corto';

Verb meta 'verbose' 'largo'
  *                                   -> ModoM2;
VerboIrregular "cambiar a modo LARGO" with imperativo 'verbose' 'largo';

Verb meta 'breve' 'normal'
  *                                   -> ModoM1;
VerboIrregular "cambiar a modo NORMAL" with imperativo 'breve' 'normal';

Verb meta 'pronombres'
  *                                   -> Pronombres;
VerboIrregular "ver el estado de los pronombres" with imperativo 'pronombres';

#Ifndef NO_PUNTUACION;
Verb meta 'notify' 'notificar' 'notificacion'
  * 'on'/'si'                         -> ActivarNotificacion
  * 'off'/'no'                        -> DesactivarNotificacion;
VerboIrregular "cambiar el estado de la NOTIFICACIÓN de PUNTOS" with imperativo
  'notificar' 'notify';
#Endif; ! NO_PUNTUACION

Verb meta 'version'
  *                                   -> Version;
VerboIrregular "conocer el número de VERSIÓN del juego" with imperativo
  'version';

Verb meta 'dialecto'
  *                                   -> Dialecto
  * 'sudamericano'                    -> DialectoSud
  * 'castellano'                      -> DialectoCast;
VerboIrregular "cambiar el dialecto del juego" with imperativo 'dialecto';

#Ifndef NO_LUGARES;
  Verb meta 'places' 'lugares'
    *                                 -> Lugares;
  VerboIrregular "listar los lugares visitados" with imperativo 'places'
    'lugares';

  Verb meta 'objects' 'objetos'
    *                                 -> Objetos;
  VerboIrregular "listar los objetos que se han tenido" with imperativo
 'objects'
    'objetos';
#Endif;  ! NO_LUGARES

! ----------------------------------------------------------------------------
!  Comandos para depuración
! ----------------------------------------------------------------------------

! TODO: ¿Añadimos formas infinitivas para los comandos de depuración?

#Ifdef DEBUG;
  Verb meta 'acentos'
    *                                 -> ActivarAcentos
    * 'on'/'si'	                      -> ActivarAcentos
    * 'off'/'no'                      -> DesactivarAcentos;

  Verb meta 'trace' 'traza'
    *                                 -> ActivarTraza
    * number                          -> NivelTraza
    * 'on'/'si'                       -> ActivarTraza
    * 'off'/'no'                      -> DesactivarTraza;

  Verb meta 'actions' 'acciones'
    *                                 -> ActivarAcciones
    * 'on'/'si'                       -> ActivarAcciones
    * 'off'/'no'                      -> DesactivarAcciones;

  Verb meta 'routines' 'messages' 'rutinas' 'mensajes'
    *                                 -> ActivarRutinas
    * 'on'/'si'                       -> ActivarRutinas
    * 'off'/'no'                      -> DesactivarRutinas;

! TODO: ¿Añadimos aquí también 'relojes'?

  Verb meta 'timers' 'daemons' 'temporizadores'
    *                                 -> ActivarRelojes
    * 'on'/'si'	                      -> ActivarRelojes
    * 'off'/'no'                      -> DesactivarRelojes;

  Verb meta 'recording' 'grabacion'
    *                                 -> ActivarComandos
    * 'on'/'si'                       -> ActivarComandos
    * 'off'/'no'                      -> DesactivarComandos;

  Verb meta 'changes' 'cambios'
    *                                 -> CambiosOn
    * 'on'/'si'                       -> CambiosOn
    * 'off'/'no'                      -> CambiosOff;

! TODO: ¿Alguna forma en español para este comando?

  Verb meta 'replay'
    *                                 -> LeerComandos;

  Verb meta 'random' 'aleatorio' 'predecible'
    *                                 -> Predecible;

  Verb meta 'xroba'
    * multi                           -> XRobar;

  Verb meta 'xmueve'
    * noun 'a//' noun                 -> XMover;

  Verb meta 'tree' 'arboljuego' 'xarbol'
    *                                 -> XArbol
    * noun                            -> XArbol;

  Verb meta 'xir' 'irdonde'
    * number                          -> XIrA
    * noun                            -> IrDonde;

  Verb meta 'scope' 'alcance'
    *                                 -> Alcance
    * noun                            -> Alcance;

  Verb meta 'xverbo'
    * special                         -> MostrarVerbo;

  Verb meta 'xobjeto'
    *                                 -> MostrarObjeto
    * multi                           -> MostrarObjeto;

  #Ifdef TARGET_GLULX;

! TODO: ¿Alguna forma española para este comando? ¿Tal vez 'listaglk'?

    Verb meta 'glklist'
      *                               -> Glklist;
  #Endif;  ! TARGET_GLULX
#Endif;  ! DEBUG

! ----------------------------------------------------------------------------
!  Los comandos del juego
! ----------------------------------------------------------------------------

Verb 'coge' 'toma' 'recoge'
  * multi                             -> Coger
  * 'a//' creature                    -> Coger
  * multiinside 'de' noun             -> Sacar;

Verb 'saca'
  * multiinside 'de' noun             -> Sacar
  * 'a//' creature 'de' noun          -> Sacar;

! [001115] El verbo quita genera ahora la acción Quitar, pero
! esta acción es reconvertida por la librería en Desvestir,
! Coger o Sacar.

Verb 'quita' 'quitale'
  * noun                                                     -> Quitar
  * noun 'de' noun                                           -> Quitar
  * 'a//' creature 'de' noun                                 -> Quitar
  * noun 'a//' noun                                          -> Quitar
  * 'cerrojo'/'pestillo'/'cierre' 'a//' noun                 -> QuitarCerrojo
  * 'el' 'cerrojo'/'pestillo'/'cierre' 'a//' noun            -> QuitarCerrojo
  * 'cerrojo'/'pestillo'/'cierre' 'a//' noun 'con' held      -> QuitarCerrojo
  * 'el' 'cerrojo'/'pestillo'/'cierre' 'a//' noun 'con' held -> QuitarCerrojo;
VerboIrregular "quitarle" with imperativo 'quitale';

Verb 'sacate' 'quitate' 'sacarse' 'quitarse' 'quitarte' 'sacarte' 'sacarme' 'quitarme' 'quitame' 'sacame'
  * noun                              -> Desvestir;
VerboIrregular "quitar" with imperativo 'sacate' 'quitate' 'sacarse' 'quitarse'
  'quitarte' 'sacarte' 'sacarme' 'quitarme' 'quitame' 'sacame';

Verb 'ponte' 'viste' 'vistete' 'ponerse' 'vestirse' 'ponerte' 'vestirte' 'ponerme' 'vestirme' 'ponme' 'visteme'
  * held                              -> Vestir
  * 'con' held                        -> Vestir;
VerboIrregular "poner" with imperativo 'pon' 'ponte' 'viste' 'vistete'
  'ponerse' 'vestirse' 'ponerte' 'vestirte' 'ponerme' 'vestirme' 'ponme' 'visteme';

Verb 'pon' 'mete' 'echa' 'inserta' 'coloca'
  * multiexcept 'en' recipiente                              -> Meter
  * multiexcept 'en' noun                                    -> PonerSobre
  * multiexcept 'dentro' 'de' noun                           -> Meter
  * multiexcept 'sobre' noun                                 -> PonerSobre
  * noun 'a//' topic                                         -> PonerA
  * 'a//' creature 'en' recipiente                           -> Meter
  * 'a//' creature 'en' noun                                 -> PonerSobre
  * 'a//' creature 'dentro' 'de' noun                        -> Meter
  * 'a//' creature 'sobre' noun                              -> PonerSobre
  * multiexcept 'encima' 'de' noun                           -> PonerSobre
  * 'a//' creature 'encima' 'de' noun                        -> PonerSobre
  * 'cerrojo'/'pestillo'/'cierre' 'a//' noun                 -> EcharCerrojo
  * 'el' 'cerrojo'/'pestillo'/'cierre' 'a//' noun            -> EcharCerrojo
  * 'cerrojo'/'pestillo'/'cierre' 'a//' noun 'con' held      -> EcharCerrojo
  * 'el' 'cerrojo'/'pestillo'/'cierre' 'a//' noun 'con' held -> EcharCerrojo;

Verb 'vacia'
    * noun                           	-> Vaciar
    * noun 'dentro' 'de' noun        	-> VaciarEn
    * noun 'en' noun                 	-> VaciarEn
    * noun 'sobre' noun              	-> VaciarEn
    * noun 'encima' 'de' noun        	-> VaciarEn;
Verb 'transfiere' 'cambia'
    * noun 'a//' noun                 	-> Transferir;
VerboIrregular "transferir"  with imperativo 'transfiere';
Verb 'deja' 'suelta'
    * multiheld                      	-> Dejar
    * 'a//' creature			-> Dejar
    * multiexcept 'en' recipiente     	-> Meter
    * multiexcept 'en' noun             -> PonerSobre
    * multiexcept 'dentro' 'de' noun 	-> Meter
    * multiexcept 'sobre' noun       	-> PonerSobre
    * multiexcept 'encima' 'de' noun 	-> PonerSobre;
VerboIrregular "soltar" with imperativo 'suelta';
Verb 'lanza' 'arroja'
    * held 'a//' noun                  	-> Lanzar
    * held 'por' noun                	-> Lanzar
    * 'a//' creature 'por'/'contra' noun-> Lanzar
    * held 'contra' noun             	-> Lanzar;
Verb 'tira'
    * 'de' noun                      	-> Tirar
    * multiheld                      	-> Dejar
    * multiexcept 'en' recipiente     	-> Meter
    * multiexcept 'en' noun     	-> PonerSobre
    * multiexcept 'dentro' 'de' noun 	-> Meter
    * multiexcept 'sobre' noun       	-> PonerSobre
    * multiexcept 'encima' 'de' noun 	-> PonerSobre
    * held 'a//' noun                  	-> Lanzar
    * held 'por' noun                	-> Meter
    * held 'contra' noun             	-> Lanzar;
Verb 'da' 'regala' 'dale' 'dase' 'ofrece' 'darse'
    * held 'a//' creature		-> Dar
    * 'a//' creature held		-> Dar reverse
    * creature held			-> Dar reverse
    * 'una' 'patada' 'a//' noun        	-> Atacar
    * 'un' 'punetazo' 'a//' noun	-> Atacar
    * 'un' 'golpe' 'a//' noun          	-> Atacar;
VerboIrregular "darle" with imperativo 'dale' 'dase' 'darse';
Verb 'muestra' 'ensena'
    * creature held                     -> Mostrar reverse
    * 'a//' creature held		-> Mostrar reverse
    * held 'a//' creature		-> Mostrar;
VerboIrregular "mostrar" with imperativo 'muestra';

[ UnaDireccion; if (uno in Brujula) rtrue; rfalse; ];
Verb 'anda' 'camina' 'corre' 'ir' 've' 'vete' 'vuelve'
    *                               	-> IrAmbiguo
    * noun=UnaDireccion               	-> Ir
    * 'a//' noun=UnaDireccion           -> Ir
    * 'hacia' noun=UnaDireccion       	-> Ir
    * noun                          	-> Meterse
    * 'a//' noun                      	-> Meterse
    * 'hacia' noun                  	-> Meterse
    * 'por' noun                    	-> Meterse;
VerboIrregular "ir" with imperativo 've' 'vete' 'ir';
VerboIrregular "volver" with imperativo 'vuelve';

Verb 'pasa'
    * 'por' noun			-> Meterse;
Verb 'inventario' 'inv' 'i//'
    *                                 	-> Inv
    * 'breve'/'estrecho'               	-> InvAlto
    * 'largo'/'ancho'                  	-> InvAncho;
VerboIrregular "mostrar inventario" with imperativo 'i//' 'inv' 'inventario';
Verb 'look' 'l//' 'mira' 'm//' 'ver'
    *                                	-> Mirar
    * 'a//' creature                    -> Examinar
    * noun                           	-> Examinar
    * 'a//'/'hacia' noun		-> Examinar
    * 'en' noun                      	-> BuscarEn
    * 'dentro' 'de' noun             	-> BuscarEn
    * 'sobre' noun                   	-> BuscarEn
    * 'bajo' noun                    	-> MirarDebajo
    * 'debajo' 'de' noun             	-> MirarDebajo
    * 'a//' 'traves' 'de' noun		-> BuscarEn
    * 'por' noun                     	-> BuscarEn;
VerboIrregular "mirar"  with imperativo 'l//' 'look' 'm//';
Verb 'consulta'
    * creature 'sobre' topic            -> Preguntar
    * 'a//' creature 'sobre' topic	-> Preguntar
    * 'sobre' topic 'a//' creature	-> Preguntar reverse
    * noun 'sobre' topic            	-> Consultar
    * noun 'acerca' 'de' topic	        -> Consultar
    * topic 'en' noun			-> Consultar reverse;
Verb 'abre'
    * noun                           	-> Abrir
    * 'a//' creature                    -> Abrir
    * noun 'con' held                	-> QuitarCerrojo;
VerboIrregular "abrir" with imperativo 'abre';
Verb 'cierra'
    * noun                           	-> Cerrar
    * noun 'con' 'pestillo'		-> EcharCerrojo
    * noun 'con' held                	-> EcharCerrojo;
VerboIrregular "cerrar"  with imperativo 'cierra';
Verb 'destapa' 'descubre'
    * noun				-> Abrir;
VerboIrregular "descubrir"  with imperativo 'descubre';
Verb 'tapa' 'cubre'
    * noun				-> Cerrar;
VerboIrregular "cubrir" with imperativo 'cubre';
Verb 'entra' 'cruza'
    *                                	-> Entrar
    * 'en'/'por' noun                  	-> Meterse
    * 'a//' noun                       	-> Meterse
    * noun                           	-> Meterse;
Verb 'metete' 'meterse' 'meterte' 'meterme' 'meteme'
    * 'en'/'por' noun			-> Meterse;
VerboIrregular "meter" with imperativo 'metete' 'meterse' 'meterte' 'meterme' 'meteme';
Verb  'atraviesa'
    * noun				-> Meterse;
VerboIrregular "atravesar" with imperativo 'atraviesa';
Verb 'sienta' 'echate' 'sientate' 'echarse' 'sentarse' 'echarte' 'sentarte'
    * 'en' noun                      	-> Meterse;
VerboIrregular "sentar" with imperativo 'sienta' 'sientate' 'sentarse'
    'echarte' 'sentarte';
VerboIrregular "echar" with imperativo 'echate' 'echarse';
Verb 'sal' 'fuera' 'afuera' 'salte' 'bajate' 'levantate' 'bajarse'
    'levantarse' 'salirse' 'bajarte' 'levantarte' 'salirte'
    *                                	-> Salir
    * 'de' noun                      	-> Salirse
!    * 'por' noun                     	-> Meterse
    * 'fuera'                        	-> Salir
    * 'afuera'                       	-> Salir;
VerboIrregular "salir" with imperativo 'sal' 'fuera' 'afuera' 'salte'
    'salirse' 'salirte';
VerboIrregular "bajar" with imperativo 'bajate' 'bajarse' 'bajarte';
VerboIrregular "levantar" with imperativo 'levantate' 'levantarse'
    'levantarte';
Verb 'baja'                                          ! 021230
    *                                   -> Bajar
    * noun                              -> Bajar
    * 'de' noun                         -> Salirse
    * 'por' noun                        -> Bajar;
Verb 'examina' 'x//' 'describe' 'inspecciona' 'observa' 'ex'
    * noun                           	-> Examinar
    * 'a//' creature                    -> Examinar;
VerboIrregular "examinar" with imperativo 'x//' 'describe' 'ex';
Verb 'lee'
    * noun                           	-> Examinar
    * 'sobre' topic 'en' noun    	-> Consultar
    * topic 'en' noun            	-> Consultar;
Verb 'si'
    *                                	-> Si;
VerboIrregular "responder ~sí~" with imperativo 'si' 'y//';
Verb 'nx'
    *                                	-> No;
VerboIrregular "responder ~no~" with imperativo 'nx';

Verb 'perdon' 'perdona' 'disculpa'
    *                                   -> LoSiento
    * topic                             -> LoSiento;
Verb 'siento' 'lamento'
    * topic                             -> LoSiento;
Verb 'lo'
    * 'siento'/'lamento'                -> LoSiento
    * 'siento'/'lamento' topic          -> LoSiento;

Verb 'mierda' 'jode' 'joder' 'puta' 'cono' 'cabron' 'puto'
    *                                   -> Tacos
    * topic                        	-> Tacos;
Verb 'aburrido' 'tonto' 'bobo' 'idiota'
    *                                	-> Soso
    * topic                        	-> Soso;
Verb 'busca'
    * 'en' noun                      	-> BuscarEn
    * topic 'en' noun             	-> Consultar
    * 'en' noun 'sobre' topic		-> Consultar
    * 'en' noun topic			-> Consultar
    * 'en' noun 'acerca' 'de' topic	-> Consultar;
Verb 'registra' 'rebusca'
    * 'a//' creature                    -> BuscarEn
    * noun				-> BuscarEn
    * 'en' noun				-> BuscarEn;
Verb 'ondea' 'sacude' 'agita'
    * creature                          -> Atacar
    * 'a//' creature                    -> Atacar
    * 'la' 'mano'                   	-> Gesticular
    * 'las' 'manos'                     -> Gesticular
    * noun                           	-> Agitar;
VerboIrregular "sacudir" with imperativo 'sacude';
Verb 'gesticula'
    *                                   -> Gesticular;
Verb 'saluda'
    * 'con' 'la' 'mano'			-> Gesticular;
Verb 'ajusta' 'fija' 'set'
    * noun                           	-> Fijar
    * noun 'en'/'a//' topic		-> PonerA;
VerboIrregular "ajustar" with imperativo 'set';
Verb 'pulsa'
    * noun				-> Empujar;
Verb 'empuja' 'mueve' 'desplaza' 'menea'
    * noun                           	-> Empujar
    * multi 'a//' noun            	-> Transferir
    * 'a//' creature                    -> Empujar
    * noun 'hacia' noun              	-> EmpujarDir
    * noun noun                      	-> EmpujarDir;
VerboIrregular "mover" with imperativo 'mueve';
Verb 'gira'  'atornilla' 'desatornilla'
    * noun                           	-> Girar;
Verb 'conecta'
    * noun                           	-> Encender
    * noun 'a//'/'con' noun 		-> Atar;
Verb 'enciende' 'prende'
    * conmutable			-> Encender
    * noun				-> Quemar;
VerboIrregular "encender" with imperativo 'enciende';
Verb 'desconecta' 'apaga'
    * noun                           	-> Apagar
    * 'a//' creature                    -> Apagar;
Verb 'rompe' 'aplasta' 'golpea'
    'destruye' 'patea' 'pisotea'
    * noun                           	-> Atacar
    * 'a//' creature			-> Atacar;
VerboIrregular "destruir" with imperativo 'destruye';
Verb 'ataca' 'mata' 'asesina' 'tortura' 'noquea'
    * 'a//' creature                    -> Atacar
    * noun                              -> Atacar;
Verb 'lucha'
    * 'con' creature                    -> Atacar
    * creature                          -> Atacar;
Verb 'espera' 'z//'
    *                                	-> Esperar;
VerboIrregular "esperar" with imperativo 'z//';
Verb 'responde' 'di' 'grita' 'dile'
    * 'a//' creature topic              -> Responder reverse
    * topic 'a//' creature		-> Responder;
VerboIrregular "decir" with imperativo 'di' 'dile';
Verb 'cuenta' 'narra' 'explica' 'habla'
    * creature 'de' topic		-> Hablar
    * creature 'sobre' topic		-> Hablar
    * creature topic                   	-> Hablar
    * 'a//' creature 'de'/'sobre' topic -> Hablar
    * 'a//' creature  topic		-> Hablar
    * 'con' creature 'sobre' topic	-> Hablar
    * 'con' creature 'de' topic		-> Hablar
    * 'con' creature 'acerca' 'de' topic -> Hablar
    * 'sobre' topic 'con' creature	-> Hablar reverse
    * 'acerca' 'de' topic 'con' creature -> Hablar reverse
    * 'de' topic 'con'/'a//' creature	-> Hablar reverse
    * topic 'a//' creature		-> Hablar reverse;
VerboIrregular "contar" with imperativo 'cuenta';
Verb 'pregunta' 'interroga'
    * creature 'sobre'/'por' topic      -> Preguntar
    * 'a//' creature 'sobre'/'por' topic -> Preguntar
    * 'sobre'/'por' topic 'a//' creature -> Preguntar reverse
    * topic 'a//' creature		-> Preguntar reverse
    * 'a//' creature 'acerca' 'de' topic -> Preguntar;
Verb 'pide' 'pidele'
    * 'a//' creature noun		-> Pedir
    * noun 'a//' creature		-> Pedir reverse;
VerboIrregular "pedir" with imperativo 'pide' 'pidele';

Verb 'come' 'comerse' 'comerte' 'comete' 'ingiere' 'mastica' 'traga'
    * held				-> Comer;
VerboIrregular "comer" with imperativo 'comete' 'comerse' 'comerte';
VerboIrregular "ingerir" with imperativo 'ingiere';

Verb 'duerme' 'ronca' 'descansa'
    *					-> Dormir;
VerboIrregular "dormir" with imperativo 'duerme';
Verb 'canta'
    *					-> Cantar;
Verb 'escala' 'trepa'
    * 'a//' noun			-> Trepar
    * noun                            	-> Trepar
    * 'por' noun                      	-> Trepar;
Verb 'subete' 'subirse' 'subirte'
    * 'a//'/'en' noun			-> Meterse;
Verb 'sube'
    *                                   -> Subir
    * noun                              -> Meterse   ! 021230
    * 'a//' / 'en' / 'por'  noun        -> Meterse;
VerboIrregular "subir" with imperativo 'sube' 'subete' 'subirse' 'subirte';
Verb 'compra' 'adquiere'
    * noun                           	-> Comprar;
VerboIrregular "adquirir" with imperativo 'adquiere';

Verb 'aprieta' 'estruja' 'tuerce' 'retuerce'
    * noun                           	-> Retorcer
    * 'a//' creature                    -> Retorcer;
VerboIrregular "apretar" with imperativo 'aprieta';
VerboIrregular "retorcer" with imperativo 'retuerce';
VerboIrregular "torcer" with imperativo 'tuerce';

Verb 'nada'
    *                                	-> Nadar;
Verb 'balanceate' 'columpiate' 'meneate' 'balancearse' 'columpiarse'
    'menearse' 'balancearte' 'columpiarte' 'menearte'
    * 'en' noun                      	-> Columpiar;
VerboIrregular "balancear" with imperativo 'balanceate' 'meneate'
    'balancearse' 'menearse' 'balancearse' 'menearse';
VerboIrregular "columpiar" with imperativo 'columpiate' 'columpiarse'
 'columpiarse';
Verb 'sopla'
    * noun                           	-> Soplar;
Verb 'reza' 'ora'
    *                                	-> Rezar;
Verb 'despierta' 'espabila'
    *                                	-> Despertarse
    * creature                       	-> DespertarOtro
    * 'a//' creature                    -> DespertarOtro;
Verb 'espabilate' 'espabilarse' 'espabilarte'
    *					-> Despertarse;
VerboIrregular "despertar" with imperativo 'despierta' 'espabilate'
    'espabilarse' 'espabilarte';
Verb 'besa' 'abraza'
    * creature                       	-> Besar
    * 'a//' creature                    -> Besar;
Verb 'piensa'
    *                                	-> Pensar;
VerboIrregular "pensar" with imperativo 'piensa';
Verb 'huele' 'olfatea'
    *                                	-> Oler
    * 'a//' noun			-> Oler
    * noun                           	-> Oler;
VerboIrregular "oler" with imperativo 'huele';
Verb 'escucha' 'oye'
    *                                	-> Escuchar
    * 'a//' noun			-> Escuchar
    * noun                           	-> Escuchar;
VerboIrregular "oir" with imperativo 'oye';
Verb 'saborea' 'paladea' 'prueba' 'lame'
    * noun                           	-> Probar
    * 'a//' noun			-> Probar;
VerboIrregular "probar" with imperativo 'prueba';
Verb 'toca' 'palpa'
    * noun                           	-> Tocar
    * 'a//' creature                    -> Tocar;
Verb 'lava' 'limpia' 'pule' 'abrillanta' 'friega' 'frota'
    * noun                           	-> Frotar
    * 'a//' creature                    -> Frotar;
VerboIrregular "pulir" with imperativo 'pule';
VerboIrregular "fregar" with imperativo 'friega';
Verb 'ata' 'enlaza' 'enchufa' 'une'
    * noun                           	-> Atar
    * 'a//' creature                    -> Atar
    * 'a//' creature 'a//' noun         -> Atar
    * noun 'a//' noun                  	-> Atar;
VerboIrregular "unir" with imperativo 'une';
Verb 'quema'
    * noun                           	-> Quemar
    * 'a//' creature                    -> Quemar
    * 'a//' creature 'con' held         -> Quemar
    * noun 'con' held                	-> Quemar;
Verb 'bebe'
    * noun                           	-> Beber;
Verb 'llena' 'rellena'
    * noun                       	-> Llenar;
Verb 'corta' 'rasga'
    * noun                           	-> Cortar
    * noun 'con' held                	-> Cortar;
Verb 'salta' 'brinca'
    *                                	-> Saltar
    * noun                           	-> SaltarSobre
    * 'a//' noun                      	-> Meterse
    * 'sobre' noun                   	-> SaltarSobre
    * 'por' 'encima' 'de' noun		-> SaltarSobre;
Verb 'cava' 'excava'
    * 'en' noun				-> Excavar
    * noun                              -> Excavar
    * noun 'con' held                   -> Excavar
    * 'en' noun 'con' held              -> Excavar;

Ifdef ADMITIR_COMANDO_SALIDAS;
! A partir de la revisión [021025] el verbo Salidas ya no es metaverbo.

  Verb 'salidas' 'exits'
    *                                   -> Salidas;
  Extend only 'x//' first
    *                                   -> Salidas;
Endif;  ! ADMITIR_COMANDO_SALIDAS


! Nuevo en la revisión [001101]. Xir es análogo a Xarbol pero no incluye
! en la lista los objetos de librería ni los verbos irregulares
#Ifdef DEBUG;
[ XlistaSub i;
    objectloop(i)
      	if (i ofclass Object && parent(i)==0){
 	    if (i ofclass VerboIrregular) continue;
	    if (i == Brujula or ParserInform
		or LibreriaInform or MensajesLibreria) continue;
	    Xobj(i);
	}
];
Verb meta 'xlista'
    *					-> XLista;
#Endif;

! ----------------------------------------------------------------------------
!  This routine is no longer used here, but provided to help existing games
!  which use it as a general parsing routine:

![ ConTopic w; consultar_desde = np;
!  do w=SiguientePalabraParar();
!  until (w==-1 || (w=='to' && accion_que_seria==##Responder));
!  np--;
!  consultar_num_palabras = np-consultar_desde;
!  if (consultar_num_palabras==0) return -1;
!  if (accion_que_seria==##Preguntar or ##Responder or ##Hablar)
!  {   w=np; np=consultar_desde; numero_interpretado=SiguientePalabra();
!      if (numero_interpretado=='the' && consultar_num_palabras>1)
!              numero_interpretado=SiguientePalabra();
!      np=w; return 1;
!  }
!  return 0;
!];
! ----------------------------------------------------------------------------
!  Final task: provide trivial routines if the user hasn't already:
! ----------------------------------------------------------------------------

#Stub PasaElTiempo    0;
#Stub Curiosidades    0;
#Stub MensajeMuerte   0;
#Stub CaminarAOscuras 0;
#Stub LugarNuevo      0;
#Stub RutinaMirar     0;
#Stub MasAlla         0;
#Stub RutinaPreJuego  0;
#Stub RutinaPostJuego 0;
#Stub TrasElPrompt    0;
#Stub AntesDelParsing 0;
#Stub ImprimirTareas  1;
#Stub AlAlcance       1;
#Stub VerboDesconocido 1;
#Stub ImprimirVerbo    1;
#Stub ErrorParser     1;
#Stub InterpretarNumero 2;
#Stub ElegirObjetos   2;
#Stub PreguntarPreposicion 0;
#Stub MirarHaciaSub   1;
#Ifndef ImprimirRango;
Constant Crear__IR;
#Endif;
#Ifdef Crear__IR;
[ ImprimirRango; "."; ];
#Endif;
#Ifndef InterpretarNombre;
Constant Crear__IN;
#Endif;
#Ifdef Crear__IN;


!
! La rutina InterpretarNombre se ocupa de ignorar "de" cuando aparece entre
! dos palabras reconocidas como nombres de un mismo objeto. Así, si
! un objeto tiene en su campo "name" los valores "caja" "madera" "caoba"
! InterpretarNombre aceptará "caja de madera" "caja de caoba" e incluso
! "caja de madera de caoba". En cambio, ante la cadena "caja de bolsa", sólo
! aceptará la primera palabra (caja) dejando sin procesar "de bolsa", lo
! que permite la posterior interpretacion de frases como "saca caja de bolsa"
! E incluso "saca caja de madera de caoba de bolsa"
! De paso también ignora artículos con lo que también se admite:
! "saca la caja de madera de caoba de la bolsa"
!
! InterpretarNombre debe retornar un número que indica cuántas palabras admite
! como pertenecientes al objeto. En nuestro ejemplo, ante "caja de madera"
! debe retornar 3, pero ante "caja de bolsa" debe retornar 1.
!
[ InterpretarNombre obj n dudas seguir gen p aux;

    n=0;   ! numero de palabras reconocidas de momento
    seguir=1;  ! seguir mirando palabras para ver si las siguientes
               ! se refieren a este mismo objeto

    aux=aux;
    #Ifdef DEBUG;
    aux=debug_flag;
    debug_flag=0; ! Desactivar trazado de give
    #Endif;
    give obj ~nombreusado;
    gen=5; ! 1=masculino, 2=femenino,
              ! 3=masculino plural, 4= femenino plural
              ! 5=sin determinar
    while(seguir)
    {
	p=SiguientePalabra();
	if ((p=='de')&&(n==0)) return 0;

!	 if (PalabraEnPropiedad(p, obj, nombre))
!	     ! Una palabra que se refiere al objeto
!	 {
!	     n++;		! la contamos
!	     n=n+dudas;		! añadimos todos los "de" "la"...
!				 ! que estaban sin contar
!	     dudas=0;		! y resetamos el contador de "de"s
!	     continue;		! volvemos al while
!	 }
	if (PalabraEnPropiedad(p, obj, nombre_m))
	    ! Una palabra que se refiere al objeto
	{
            if (p) banderas_dicc_nombre = (p->#dict_par1) & $$01110100;
	    if (gen==5) gen=G_MASCULINO;
            n++;		! la contamos
	    n=n+dudas;		! añadimos todos los "de" "la"...
				! que estaban sin contar
	    dudas=0;		! y resetamos el contador de "de"s
	    continue;		! volvemos al while
	}
	if (PalabraEnPropiedad(p, obj, nombre_f))
	    ! Una palabra que se refiere al objeto
	{
            if (p) banderas_dicc_nombre = (p->#dict_par1) & $$01110100;
	    if (gen==5) gen=G_FEMENINO;
            n++;		! la contamos
	    n=n+dudas;		! añadimos todos los "de" "la"...
				! que estaban sin contar
	    dudas=0;		! y resetamos el contador de "de"s
	    continue;		! volvemos al while
	}
	if (PalabraEnPropiedad(p, obj, nombre_mp))
	    ! Una palabra que se refiere al objeto
	{
            if (p) banderas_dicc_nombre = (p->#dict_par1) & $$01110100;
	    if (gen==5) gen=G_MASCULINO+G_PLURAL;
            n++;		! la contamos
	    n=n+dudas;		! añadimos todos los "de" "la"...
				! que estaban sin contar
	    dudas=0;		! y resetamos el contador de "de"s
	    continue;		! volvemos al while
	}
	if (PalabraEnPropiedad(p, obj, nombre_fp))
	{
            if (p) banderas_dicc_nombre = (p->#dict_par1) & $$01110100;
	    if (gen==5) gen=G_FEMENINO+G_PLURAL;
            n++;		! la contamos
	    n=n+dudas;		! añadimos todos los "de" "la"...
				! que estaban sin contar
	    dudas=0;		! y resetamos el contador de "de"s
	    continue;		! volvemos al while
	}
	if (PalabraEnPropiedad(p, obj, adjetivos))
	{
            if (p) banderas_dicc_nombre = (p->#dict_par1) & $$01110100;
            n++;		! la contamos
	    n=n+dudas;		! añadimos todos los "de" "la"...
				! que estaban sin contar
	    dudas=0;		! y resetamos el contador de "de"s
	    continue;		! volvemos al while
	}

	! Si la palabra no fue reconocida, miraremos si se trata
	! de 'de' o un artículo. En este caso mantenemos la duda y
	! seguimos mirando palabras, hasta que una de ellas encaje
	! en este objeto, en cuyo caso se retornan todas las que se
	! han leido, o bien se encuentre una que no encaja en cuyo
	! caso se retorna las que se habían encontrado antes del "de"

	else if (p== 'el' or 'la' or 'los' or 'las' or
		 'de')
	{
		dudas++; continue;
	}
	else seguir=0;   ! Si no fue reconocida, ni un articulo, ni "de"
			 ! nos damos por vencidos
    }
    if (obj provides genero)
    	switch(gen)
    	{ ! Los casos del switch estaban mal.
          ! Bug corregido en 001030
     	 0: give obj ~femenino ~nombreplural;
     	 1: give obj femenino ~nombreplural;
     	 3: give obj ~femenino nombreplural;
     	 4: give obj femenino nombreplural;
    	}
    if (gen<5) give obj nombreusado;
!    if (obj provides genero) obj.genero=gen;
#Ifdef DEBUG;
    debug_flag=aux;
#Endif;
    return n;
    !return -1;
];

#Endif;
#Default Historia 0;
#Default Titular 0;

#Ifdef TARGET_GLULX;
#Stub IdentifyGlkObject 4;
#Stub HandleGlkEvent  2;
#Stub InitGlkWindow   1;
#Endif; ! TARGET_GLULX

! [010515] Cambiado de sitio el punto de inclusión de Mensajes.h
! para dar la oportunidad al usuario de incluir su propio Mensajes
! si lo desea (antes del include Gramatica)
#Ifndef MLIdioma;
include "Mensajes";
#Endif;

#Ifdef INFIX;
include "infixe";
#Endif;



! ----------------------------------------------------------------------------
