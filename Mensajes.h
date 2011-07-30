! Mensajes de librería.
!
! Número de Serie: 080625
!
! A partir de la revisión [001115], los mensajes de librería van en
! fichero aparte para hacer más fácil su redefinición.
!
! Recuerda hacer una copia de este fichero, con el nombre
! Mensajes_originales.h por ejemplo, antes de modificarlo.
!
! Puedes tener diferentes ficheros de mensajes (Mensajes_graciosos.h,
! Mensajes_primera_persona.h, etc.) pero el que será incluido en el
! juego por defecto será el llamado Mensajes.h (si quieres usar otro,
! inclúyelo en tu código antes de incluir Gramatica.h)
!
! --------IMPORTANTE--------------------
! Recuerda que si sólo vas a redefinir unos pocos mensajes y no todos,
! es mejor usar el mecanismo de "MensajesLibreria". Este mecanismo
! consiste en escribir un objeto llamado MensajesLibreria antes de
! Include "Acciones", y en la rutina antes de ese objeto capturar las
! acciones para las cuales quieres cambiar el mensaje. Por ejemplo,
! para cambiar el mensaje "Cantas fatal", que se genera por defecto
! ante la acción cantar, pondrías:
!
!  Object MensajesLibreria
!  with antes [;
!           Cantar:  "Tío, la música no es lo tuyo.";
!       ];
!
!  Algunas acciones generan diferentes mensajes según el caso. Por
!  ejemplo, la acción Coger puede generar:
!   - Cogido (en caso de éxito)
!   - Siempre te tienes a ti mismo (en caso de COGETE)
!   - No creo que Pepe le gustara (en caso de COGE PEPE)
!   - Ya tienes el hacha (en caso de que ya tenga el objeto)
!  etc...
!
!  En la variable ml_n se guarda un numero que indica cuál de los
!  mensajes anteriores debe ser mostrado. Por otra parte, en la
!  variable ml_o se guarda el objeto que debe ser nombrado en el
!  mensaje. Así, para cambiar los cuatro mensajes anteriores desde
!  MensajesLibreria deberíamos hacer un switch sobre la variable ml_n
!  para elegir el mensaje adecuado, y usar el objeto ml_o como parte
!  del mensaje. Por ejemplo:
!
!   Object MensajesLibreria
!   with  antes [;
!           Cantar: "Tío, lo tuyo no es la música.";
!           Coger: switch (ml_n)
!                  {
!                    1: print_ret "Vale, pillad", (o) ml_o, ".";
!                    2: print_ret "¡Pero cómo vas a ", (coge) "rte a ti mismo,
!                       melón!";
!                    3: print_ret (_El) ml_o, " no se deja", (n) ml_o,
!                       ".";
!                    5: print_ret "¡Pero si ya ", (lo) ml_o, "
!                       tienes!";
!                  }
!          ];
!
! Observa como se usa (o) ml_o para imprimir "o", "a", "os" o "as"
! según el género y número del objeto. (n) ml_o imprime una "n" o
! nada, según el número del objeto (por ejemplo: El perro no se deja,
! y Las abejas no se dejan). (lo) ml_o imprime "lo" "la" "los" o
! "las".
!
! Si vas a cambiar muchos mensajes, el sistema de MensajesLibreria
! sigue siendo válido, pero consume más memoria. Puedes entrar a
! modificar directamente este fichero Mensajes.h
!
! También puedes usar este fichero como fuente de información para
! saber los diferentes valores de ml_n asociados con cada acción y el
! mensaje más apropiado para cada caso.
!
! La función se halla profusamente comentada para ayudarte a saber
! cuándo se genera cada mensaje.

! Movido aquí en [020415]

Constant HAY__TX      = " ves";
Constant HAYP__TX     = " ves";
Constant HAY2__TX     = "ves ";
Constant HAYP2__TX    = "ves ";

! Añadido en [020804]

Constant PARTICULA_TE = "te";

!****************************************************************
! DEFINICIÓN DE MENSAJES DE LIBRERÍA
!****************************************************************
! Esta rutina engloba todas las respuestas por defecto a todas las
! acciones de librería, así como los mensajes de error del parser y
! otras cadenas de texto que el parser necesita mostrar a veces.
!
! Sus contenidos pueden agruparse en cuatro grandes categorías:
!
!  1) Mensajes de las acciones que no hacen nada. Son meros mensajes
!  del estilo de "no ocurre nada", pero adaptados para cada posible
!  acción. Son muy fáciles de redefinir.
!
!  2) Mensajes de las acciones que hacen cosas. En este caso hay
!  mensajes de éxito o de error, según la acción haya podido
!  realizarse o no. Ten en cuenta que el mensaje de éxito no se
!  imprimirá si el objeto lo impide en su rutina "despues".
!  Son bastante fáciles de modificar, guiándote por los comentarios.
!
!  3) Mensajes de los metacomandos (como SAVE, LOAD...) No creo que
!  merezca la pena cambiarlos.
!
!  4) Mensajes "Miscelanea", donde están todos los errores de parsing
!  y otros. Algunos son fáciles de cambiar, otros son más complejos.

[ MLIdioma ml_n ml_o;
  Prompt:
    print "^>";
    ! El prompt aparece justo antes de pedir una nueva línea al
    ! jugador. Puede definirse para que sea una frase, o se genere una
    ! frase aleatoria en cada turno.


!====================================================
! ACCIONES QUE NO HACEN NADA
!====================================================
! Las siguientes acciones generan un texto como respuesta, pero no
! cambian el estado del juego. No mueven objetos.

  Quemar:        "Con esa peligrosa acción no lograrías nada.";
  Rezar:         "No obtienes nada práctico de tus oraciones.";
  Despertarse:   "La cruda realidad es que esto no es un sueño.";
  DespertarOtro: "No parece necesario hacer eso.";
  Besar:         "No creo que debas.";
  Pensar:        "Vaya. Qué buena idea.";
  Oler:          "No hueles nada extraño.";
  Escuchar:      "No escuchas nada fuera de lo común.";
  Probar:        "No saboreas nada inesperado.";
  Tocar:
    ! Tocar genera tres mensajes diferentes
    !  1: Si se intenta tocar a un ser animado
    !  2: Tocar un objeto normal del juego
    !  3: Tocarse a si mismo
    switch(ml_n)
    {
      1: "¡Las manos quietas!";
      2: "No notas nada extraño al tacto.";
      3: "Si crees que eso servirá de algo...";
    }
  Excavar:     "Excavar no servirá de nada aquí.";
  Cortar:      "Cortándo", (lo) ml_o, " no lograrás gran cosa.";
  Saltar:      "Saltas en el sitio, sin ningún resultado.";
  SaltarSobre, ! SaltarSobre y Atar generan el mismo mensaje
  Atar:        "No lograrás nada así.";
  Beber:       "Eso no parece potable.";
  Llenar:      "No puedes llenar", (lo) ml_o, ".";

  LoSiento:    "Oh, no es necesario que te disculpes.";
  ! Esta acción se genera si el jugador pone "LO SIENTO",
  ! "PERDONA" o cosas similares.

  Tacos:       "Los verdaderos aventureros no usan ese vocabulario.";
  ! Y esta si usa como primera palabra (verbo) un taco.

  Soso:        "Bastante.";
  ! Y esta si usa como primera palabra algún insulto más suave

  Si, No:      "Sólo era una pregunta retórica.";
  ! Cuando el jugador pone SI o NO, a secas, se genera esta
  ! acción. Está pensado por si el juego suelta una frase del estilo
  ! de "¿Pero tú eres tonto?" y el jugador responde NO.
  ! De todas formas, hay un problema, y es que NO es normalmente la
  ! acción Ir al noroeste. Si queremos que NO sea provisionalmente
  ! la acción No, entonces el juego debe poner un 1 en la variable
  ! PreguntaSiNo, antes de escribir el texto "¿Pero tú eres tonto?".
  ! En este caso, el parser interpretará "NO" como la acción No,
  ! pero sólo en el siguiente turno. Después recuperará su antiguo
  ! significado de Ir al Noroeste.

  Atacar:      "La violencia no es la solución.";
  ! La acción atacar se genera también al intentar "romper" objetos

  Nadar:       "No hay agua suficiente en la que nadar.";
  Columpiar:   "No es adecuad", (o) ml_o, " para columpiarse.";
  Soplar:      "Tu soplido no produce ningún efecto.";
  Frotar:      "Ya ", (esta) ml_o, " bastante limpi", (o) ml_o, ".";

  Fijar:       "No, no puedes.";
  ! Fijar sale ante la frase FIJA OBJETO o AJUSTA OBJETO

  PonerA:      "Eso no puede regularse a ningún valor.";
  ! PonerA sale ante la frase AJUSTA DIAL A 23 o FIJA CONTROL EN
  ! ACTIVADO, o PON REGULADOR A 30

  Gesticular:  "Te ves ridícul", (o) jugador, " gesticulando así.";
  ! La acción Gesticular sale ante las frases "gesticula", "agita la
  ! mano", "sacude la mano", "saluda con la mano"...

  Agitar:
  ! Agitar genera dos mensajes diferentes:
  !  1: Si se intenta agitar un objeto que no está en el inventario
  !  2: Si se agita un objeto que sí está en el inventario
    switch (ml_n)
    {
      1: "No l",(o) ml_o, " tienes.";
      2: "Te sientes ridícul", (o) jugador, " agitando ", (el) ml_o, ".";
    }

  Tirar, Empujar, Girar:
  ! Las acciones Tirar, Empujar y Girar generan todas ellas los
  ! mismos mensajes, pero pueden darse 4 casos:
  !   1: Que el objeto tenga el atributo 'estatico'
  !   2: Que el objeto tenga el atributo 'escenario'
  !   3: El objeto no tiene 'estatico' ni 'escenario'
  !   4: El objeto es un ser animado
  ! [Nota, si el objeto tiene ambos 'estatico' y 'escenario' se
  ! está también en el caso 1]
    switch(ml_n)
    {
      1: "Está", (n)ml_o, " firmemente sujet", (o)ml_o, ".";
      2: "No eres capaz.";
      3: "No ocurre nada, aparentemente.";
      4: "Eso sería, como poco, maleducado.";
    }

  EmpujarDir:
  ! La acción EmpujarDir se genera ante frases como EMPUJA EL COCHE
  ! HACIA EL NORTE. Hay 3 casos posibles:
  !   1: Si el juego no ha previsto la posibilidad de empujar ese
  !      objeto hacia una dirección (o sea, no llama a la rutina
  !      PermitirEmujarDir). Esta es la respuesta por defecto más
  !      habitual.
  !   2: Si el jugador pone tras HACIA algo que no es una dirección.
  !      (respuesta por defecto en este caso)
  !   3: Si intenta empujar hacia arriba o hacia abajo
    switch(ml_n)
    {
     1: "No creo que empujar ", (el) ml_o, " sirva para nada.";
     2: "Eso no es una dirección.";
     3: "No, no puedes en esa dirección.";
    }

 Retorcer:
    ! Dos casos:
    !  1: Tratar de retorcer un ser animado
    !  2: Cualquier otro objeto
    switch(ml_n)
    {
     1: "¡Las manos quietas!";
     2: "No consigues nada haciendo eso.";
    }
 Lanzar:
    ! Dos casos:
    !  1: Lanzar cosas a objetos inanimados
    !  2: Lanzar cosas a objetos animados
    switch(ml_n)
    {
     1: "No serviría de nada.";
     2: "En el último momento te echas atrás.";
    }

 MirarDebajo:
    ! Dos casos:
    !  1: Error, estamos a oscuras
    !  2: Éxito, mensaje por defecto.
    switch(ml_n)
    {
     1: "Está muy oscuro.";
     2: "No ves nada interesante.";
    }

! Añadido en la versión [020423]. Es utilizado por DireccionBrujula.
 MirarHacia:
   "No observas nada digno de mención al mirar hacia ", (el) ml_o, ".";

 Hablar:
    ! Dos casos:
    !  1: El jugador habla consigo mismo
    !  2: Hablar con cualquier otro ser animado
    ! [Nota: Hablar con un objeto inanimado no está permitido por el
    ! parser, que da un error y no llega a generar la acción]
    ! [Los errores de parser se tratan en la sección "Miscelanea" de
    ! esta rutina, al final]
    switch(ml_n)
    {
     1: "Hablas sol", (o) jugador, " durante un rato.";
     2: "No has provocado ninguna reacción.";
    }
 Responder,
 Preguntar:      "No hay respuesta.";
 Orden:
    print_ret (_El) ml_o, " tiene", (n) ml_o, " mejores cosas que hacer.";
 Comprar:        "No hay nada en venta.";
 Cantar:         "Cantas fatal.";
 Trepar:         "No creo que vayas a lograr nada así.";
 Esperar:        "Pasa el tiempo...";
 Dormir:         "No estás especialmente somnolient", (o) jugador, ".";
 Consultar:      "No descubres nada interesante en ", (el) ml_o,
     " sobre ese tema.";

!==================================================================
! ACCIONES QUE HACEN ALGO
!==================================================================
! Las siguientes acciones pueden fracasar (dando un mensaje
! apropiado) o tener éxito. Si fracasan, se imprime un mensaje de error
! por defecto y no llega a modificarse el estado del juego
!
! Si tienen éxito, modificarán el estado del juego de algún modo
! (activando algún atributo de algún objeto, o moviendo un objeto de
! una parte a otra). Tras el éxito, se llamará a la rutina "despues"
! del objeto, y si éste no imprime nada, entonces se imprimirá un
! mensaje de éxito de librería.
!
! Aquí se definen tanto los mensajes de fracaso como los de éxito,
! pero no las acciones concretas que modifican el estado del juego
!

 Coger:
    ! Hay 13 casos diferentes. Se trata de 1 mensaje de éxito y 11
    ! mensajes de error y un aviso
    !  1: Éxito
    !  2: Error, el objeto cogido es el propio jugador
    !  3: Error, el objeto cogido es animado
    !  4: Error, el jugador está subido o metido en el objeto que
    !     intenta coger
    !  5: Error, el jugador ya tenía ese objeto
    !  6: Error, el objeto está en poder de un ser animado [ml_o
    !     apunta al ser, no al objeto, el cual puede obtenerse en la
    !     variable "uno"]
    !  7: Error, el objeto es un sub-objeto de otro (está dentro de un
    !     objeto que tiene el atributo "transparente", pero no tiene el
    !     atributo "recipiente" ni "soporte")
    !  8: Error, el objeto está dentro de otro, pero este otro no es
    !     recipiente ni soporte ni transparente (probablemente un error
    !     de programación)
    !  9: Error, el objeto está dentro de un recipiente cerrado.
    ! 10: Error, el objeto es escenario
    ! 11: Error, el objeto es estatico (no puede ser llevado de la
    !     localidad en que se halla)
    ! 12: Error, el jugador lleva demasiados objetos
    ! 13: Mensaje de aviso, la librería ha decidido mover objetos del
    !     inventario al "objeto saco" para hacer sitio y que el jugador
    !     pueda coger el objeto. [El objeto saco es uno que puede
    !     declarar el programador. Si el jugador lo coge y lo lleva
    !     consigo, la librería lo usará automáticamente como mochila
    !     para descargar al jugador cuando sea necesario]
    switch(ml_n)
    {
     1: if (dialecto_sudamericano) print "Tomad";
     	else print "Cogid";
	print_ret (o) ml_o, ".";
     2: "Siempre te tienes a ti mism", (o) jugador, ".";
     3: "No creo que ", (al) ml_o, " le", (s) ml_o, " gustara.";
     4: print "Tienes que ";
	if (ml_o has soporte) print "bajarte "; else print "salirte ";
	print_ret (del) ml_o, " antes.";
     5: "Ya tienes ", (el) ml_o, ".";
     6:	"Parece que pertenece", (n) uno, " ", (al) ml_o, ".";
     7: "Parece", (n) ml_o, " formar parte ", (del) ml_o, ".";
     8: "No ", (esta) ml_o, " disponible", (s)ml_o, ".";
     9: print_ret (_El) ml_o, " no ", (esta) ml_o, " abiert", (o) ml_o, ".";
     10: "Difícilmente podrías llevarte eso.";
     11: print_ret (_El) ml_o, " está fij", (o) ml_o, " en el sitio.";
     12: "Ya llevas demasiadas cosas.";
     13: "(colocas ", (el) ml_o, " en ", (el) OBJETO_SACO,
	 " para hacer sitio)";
    }

 Dejar:
    ! 2 mensajes de error, 1 aviso y 1 de éxito:
    !   1: Error, el objeto dejado no está en poder del jugador, pero
    !      está en la localidad.
    !   2: Error, el objeto dejado no está en poder del jugador ni en
    !      la localidad.
    !   3: Aviso, el objeto era una prenda que el jugador llevaba
    !      puesta y la librería va a quitársela automáticamente para
    !      poder dejarla.
    !   4: Éxito
    switch(ml_n)
    {
     1: "Para dejar ", (el)ml_o, " deberías tener", (lo) ml_o, ".";
     2: "No ", (lo) ml_o, " tienes.";
     3: "(primero te quitas ", (el) ml_o, ")";
     4: "Dejad", (o) ml_o, ".";
    }

 Sacar:
    ! 2 mensajes de error y 1 de éxito
    !   1: El recipiente que contiene el objeto que el jugador quiere
    !      sacar, está cerrado. (ml_o apunta al objeto, no al
    !      recipiente, el cual puede obtenerse con parent(ml_o))
    !   2: El objeto no está dentro del recipiente que el jugador ha
    !     dicho.
    !   3: Éxito
    switch(ml_n)
    {
     1: "Por desgracia ", (el) parent(ml_o), " ",(esta) parent(ml_o),
	 " cerrad", (o) parent(ml_o), ".";
     2: if (otro has animado)
	 "¡Pero si no ", (lo) ml_o, " tiene", (n) otro, "!";
	"¡Pero si no ", (esta) ml_o, " ahí ahora!";
     3: if (palabra_verbo=='quita') "Quitad", (o)ml_o, ".";
	"Sacad", (o) ml_o, ".";
    }

 PonerSobre:
    ! 1: Error, el objeto no está en poder del jugador. [Nota,
    !    conviene mirar en este caso si el objeto es animado o no,
    !    para generar un mensaje más adecuado]
    ! 2: Error, el jugador intenta poner un objeto sobre sí mismo
    ! 3: Error, el jugador intenta poner el objeto sobre otro que no
    !    tiene el atributo "soporte"
    ! 4: Error, el jugador intenta poner un objeto sobre el propio
    !    jugador.
    ! 5: Aviso, el objeto es una prenda puesta. La librería va a
    !    quitárselo automáticamente antes de reintentar la acción
    !    PonerSobre
    ! 6: Error, se intenta poner el objeto sobre otro en el que ya no
    !    queda sitio (el número de objetos que caben en el soporte se
    !    indica en su propiedad "capacidad")
    ! 7: Éxito. Mensaje a mostrar para cada objeto puesto cuando se
    !    ponen muchos (ej: PON TODO SOBRE LA MESA)
    ! 8: Éxito. Mensaje a mostrar cuando se pone un solo objeto sobre
    !    otro.
    switch(ml_n)
    {
     1: if (ml_o has animado)
	 "Antes tendrías que ", (coge) "rl", (o) ml_o, ", y no sé si se dejará",
	     (n) ml_o, ".";
	else
   	    "Necesitas tener ", (el) ml_o,
	 	" para poder poner", (lo) ml_o,
	 	" donde sea.";
     2: "No puedes poner un objeto sobre sí mismo.";
     3: "Poner cosas sobre ", (el) ml_o, " no servirá de nada.";
     4: "Te falta destreza.";
     5: "(primero te ", (lo) ml_o, " quitas)^";
     6: "No queda sitio en ", (el) ml_o, " para poner nada más.";
     7: "Hecho.";
     8: "Colocas ", (el) ml_o, " sobre ", (el) otro, ".";
    }

  Meter:
    ! 1: Error, el objeto no está en poder del jugador. [Nota,
    !    conviene mirar en este caso si el objeto es animado o no,
    !    para generar un mensaje más adecuado]
    ! 2: Error, el jugador intenta meter el objeto en otro que no
    !    tiene el atributo "recipiente"
    ! 3: Error, el jugador intenta meter el objeto en un recipiente
    !    cerrado.
    ! 4: Error, el objeto es una prenda que el jugador lleva puesta.
    !    [ESTE MENSAJE NO SE GENERA NUNCA, PARECE UN BUG DE LA
    !    LIBRERÍA. Véase en su lugar el mensaje 6]
    ! 5: Error, se intenta poner un objeto dentro de sí mismo
    ! 6: Aviso, el objeto es una prenda puesta, la librería va a
    !    quitársela de forma automática antes de reintentar Meter.
    ! 7: Error, no queda sitio en el recipiente (el número de objetos
    !    que un recipiente puede contener se indica en su propiedad
    !    "capacidad").
    ! 8: Éxito. Mensaje a mostrar para cada objeto metido cuando se
    !    meten muchos (ej: METE TODO EN LA BOLSA)
    ! 9: Éxito. Mensaje a mostrar cuando se mete un solo objeto dentro
    !    de otro
    switch(ml_n)
    {
     1: if (ml_o has animado) "Antes tendrías que ", (coge)"rl", (o) ml_o,
	 " y no sé si se dejará",(n)ml_o,".";
	else
	"Necesitas tener ", (el) ml_o,
	 " para poder meter", (lo) ml_o,
	 " donde sea.";
     2: "No se pueden meter cosas dentro ", (del) ml_o, ".";
     3: print_ret (_El) ml_o, " ", (esta) ml_o, " cerrad", (o) ml_o, ".";
     4: "Tienes que quitarte", (lo) ml_o, " antes.";
     5: "No puedes poner un objeto dentro de sí mismo.";
     6: "(primero te ", (lo) ml_o, " quitas)^";
     7: "No queda sitio en ", (el) ml_o, ".";
     8: "Hecho.";
     9: "Metes ", (el) ml_o, " dentro ", (del) otro, ".";
    }

 Transferir:
    ! ESTOS MENSAJES NUNCA SON GENERADOS POR LA
    ! LIBRERÍA. Probablemente se mantienen para compatibilidad.
    !  1: El objeto que el jugador menciona no está en la localidad
    !  2: El objeto que el jugador menciona no está en su poder (pero
    !     está en la localidad)
    ! En lugar de estos mensajes, la librería intentará una acción
    ! Coger, por lo que los mensajes generados están agrupados en la
    ! sección dedicada a Coger.
    switch(ml_n)
    {
     1: print_ret (_El) ml_o, "no está",(n) ml_o, " a mano.";
     2: "Debes ", (coge)"r", " antes ", (el) ml_o, ".";
    }

  VaciarEn:
    ! 1: Error, el jugador intenta vaciar un objeto en otro que no es
    !    un recipiente.
    ! 2: Error, el jugador intenta vaciar un objeto sobre un
    !    recipiente cerrado.
    ! 3: Error, el jugador intenta vaciar un objeto que no tiene nada
    !    dentro.
    ! 4: Error, el jugador intenta vaciar un objeto sobre sí mismo.
    ! [NOTA: No hay mensajes de éxito para esta acción, ya que en caso
    ! de haber superado los test anteriores, la librería genera
    ! finalmente la acción Transferir, la cual a su vez, generará la
    ! acción PonerSobre o Meter, según el segundo objeto sea soporte o
    ! recipiente. Por tanto los mensajes de éxito serán los de las
    ! acciones PonerSobre o Meter.
    switch(ml_n)
    {
      1:
        print_ret (_El) ml_o, " no puede tener cosas dentro.";
      2:
        print_ret (_El) ml_o, " ", (esta) ml_o, " cerrad", (o) ml_o, ".";
      3:
        print_ret (_El) ml_o, " ya ", (esta) ml_o, " vací", (o)ml_o, ".";
      4:
        "No puedes vaciar ", (el) ml_o, "sobre sí.";
    }

  Dar:
    ! 1: Error, el jugador intenta dar un objeto que no tiene
    ! 2: Error, el jugador se da el objeto a sí mismo
    ! 3: Aviso, se ha enviado la acción Dar al PNJ, pero este no ha
    !    respondido. En este caso ml_o apunta al PNJ y no al objeto
    !    que le hemos dado.
    ! [Observar que por defecto el objeto sigue en poder del
    ! jugador. Si queremos que el PNJ lo acepte, hay que programarlo
    ! como parte de su rutina Vida]
    switch(ml_n)
    {
     1: "No tienes ", (el) ml_o, ".";
     2: "Manoseas ", (el) ml_o,
	 " un ratito, pero no consigues gran cosa.";
     3: print_ret (_El) ml_o, " no parece", (n) ml_o, " interesad", (o)ml_o,
 ".";
    }

  Mostrar:
    ! 1: Error, el jugador intenta mostrar un objeto que no tiene.
    ! 2: Aviso, se ha enviado la acción Mostrar al PNJ, pero este no
    !    ha respondido. En este caso ml_n apunta al PNJ y no al objeto
    !    que le hemos mostrado.
    switch(ml_n)
    {
     1: "No tienes ", (el)ml_o, ".";
     2: print_ret (_El) ml_o, " no muestra", (n) ml_o, " interés.";
    }

  Meterse:
    ! CUIDADO. La acción Meterse se genera en muy diversas
    ! circunstancias: VETE HACIA EL PUENTE, VETE AL PUENTE, VETE POR
    ! EL PUENTE, PASA POR EL PUENTE, ENTRA EN EL PUENTE, ENTRA AL
    ! PUENTE, CRUZA EL PUENTE, CRUZA POR EL PUENTE, METETE EN EL
    ! PUENTE, METETE POR EL PUENTE, ATRAVIESA EL PUENTE, BAJA POR EL
    ! PUENTE.  Todas ellas generarían la acción <Meterse Puente>
    !
    ! Además, los intentos de entrar en un "entrable", también, como
    ! por ejemplo: SIENTATE EN EL BANCO, ECHATE EN EL BANCO, SUBETE AL
    ! BANCO, SUBETE EN EL BANCO, SUBE AL BANCO, SUBE POR EL BANCO,
    ! SALTA AL BANCO. Todas ellas generarían <Meterse Banco>
    !
    ! Puesto que hay muchos verbos diferentes que dan lugar a la misma
    ! acción, es necesaria alguna forma de imprimir qué verbo concreto
    ! ha sido el que la ha desencadenado, para poder generar mensajes
    ! como "No puedes entrar ahí", "No puedes sentarte ahí", "No
    ! puedes subirte ahí", etc.. según el verbo usado. Para esto puede
    ! usarse una llamada a IdiomaVerbo(palabra_verbo). palabra_verbo
    ! contiene el verbo usado por el jugador (convertido en forma
    ! imperativa), y IdiomaVerbo lo que hace es imprimir la forma
    ! infinitiva.
    !
    ! Mensajes que puede generar esta acción:
    !  1: Error, el jugador ya está en/sobre el objeto en cuestión
    !  2: Error, el objeto al que intenta entrar/subirse/meterse no
    !     tiene el atributo "entrable"
    !  3: Error, el objeto en que intenta entrar/meterse/subirse, es
    !     un entrable y recipiente, pero está cerrado.
    !  4: Error, el objeto en que intenta entrar/meterse/subirse, está
    !     en poder del jugador
    !  5: Éxito, el jugador sube/entra en el objeto
    !  6: Aviso, el jugador estaba en otro objeto, la librería
    !     intentará una acción <Salir> automática, antes de reintentar lo
    !     que el jugador le ha ordenado.
    !  7: Aviso, el objeto en que el jugador intenta meterse, está
    !     dentro de otros objetos. La librería intentará de forma
    !     automática meter al jugador en el objeto desde el cual pueda
    !     acceder al que el jugador ha indicado.
    switch(ml_n)
    {
     1: print "Pero si ya estás ";
	if (ml_o has soporte) print "sobre "; else print "en ";
	print_ret (el) ml_o, ".";
     2: print "No es algo donde puedas "; IdiomaVerbo(palabra_verbo); ".";
     3: "No puedes entrar en ", (el) ml_o, " porque está", (n) ml_o,
        " cerrad", (o) ml_o, ".";
     4: print "No puedes "; IdiomaVerbo(palabra_verbo);
        " ahí mientras no lo sueltes.";
     5:
	if (ml_o has soporte) print "Subes ", (al) ml_o;
	else print "Entras en ", (el) ml_o;
	print_ret ".";
     6:
	if (ml_o has soporte) print "(te bajas "; else print "(sales ";
	print (del) ml_o; ")";
     7: if (ml_o has soporte) "(te subes ", (al) ml_o, ")^";
	if (ml_o has recipiente) "(te metes en ", (el) ml_o, ")^";
	"(entras en ", (el) ml_o, ")^";
    }

 Salirse:
    ! Esta acción se genera ante la frase SAL DEL ARMARIO o
    ! similares. Ante SAL a secas la acción es Salir.
    ! Si el jugador no está en el objeto indicado, se genera el
    ! siguiente mensaje de error. Si está, la librería generará una
    ! acción Salir, por lo que el mensaje de éxito será el de Salir.
    "Pero si no estás en ", (el) ml_o, ".";

 Salir:
    ! 1: Error, el jugador no está subido/sentado/metido en ningún
    !    objeto. [Nota, si la localidad tiene la propiedad "afuera",
    !    entonces la acción Salir lo sacará de la localidad. En caso
    !    contrario es cuando se genera este error]
    ! 2: Error, el jugador está dentro de un recipiente cerrado.
    ! 3: Éxito, el jugador sale/baja del objeto
    switch(ml_n)
    {
     1: print "No estás en ningún sitio del que debas ";
	IdiomaVerbo(palabra_verbo); ".";
     2: "No puedes salir ", (del) ml_o, " porque está cerrad", (o)ml_o, ".";
     3: if (ml_o has soporte) print "Bajas ";
	else print "Sales ";
	print_ret (del) ml_o, ".";
    }

 IrAmbiguo: ! El jugador ha dicho IR sin especificar a dónde
    "Tienes que especificar en qué dirección ir.";

 Ir:
    ! La acción Ir se genera si el jugador pone IR NORTE, o si pone
    ! simplemente NORTE.
    !   1: Error, el jugador está dentro/subido en un objeto del que
    !      tiene que salir antes
    !   2: Error, la localidad no tiene salida en esa dirección (y
    !      tampoco tiene la propiedad no_puedes_ir, ya que en este caso
    !      se habría impreso el valor de esa propiedad
    !   3: Error, el jugador ha intentado ir hacia arriba, pero allí
    !      hay una puerta cerrada
    !   4: Error, el jugador ha intentado ir hacia abajo, pero allí
    !      hay una puerta cerrada.
    !   5: Error, en la dirección que ha dicho el jugador hay una
    !      puerta cerrada
    !   6: Error, en la dirección que ha dicho el jugador hay una
    !      puerta, pero ésta no tiene una propiedad puerta_a
    !      (probablemente un error de programación del juego)
    switch(ml_n)
    {
     1: print "Tienes que ";
     	if (ml_o has soporte) print "bajarte "; else print "salir ";
     	print_ret (del) ml_o, " antes.";
     2: "No puedes ir por ahí.";
     3: "Eres incapaz de trepar por ", (el) ml_o, ".";
     4: "Eres incapaz de bajar por ", (el) ml_o, ".";
     5: "No puedes pasar a través ", (del) ml_o, ".";
     6: "No puedes ir porque ", (el) ml_o, " no lleva", (n) ml_o, " a ningún sitio.";
    }

 Mirar:
    ! La acción Mirar se genera cuando el jugador pone MIRAR, pero
    ! también de forma automática al entrar en una localidad nueva, o
    ! cuando el jugador sale/se baja de un objeto en el que estaba.
    !
    ! Algunos de los mensajes que se definen aquí aparecen en el
    ! "título" de la localidad (lo que aparece en negrita antes de la
    ! descripción de la localidad)
    !
    !  1: aclaración a añadir tras el título si el jugador está subido
    !     en un objeto
    !  2: aclaración a añadir tras el título si el jugador está dentro
    !     de un objeto
    !  3: aclaración a añadir tras el título si el jugador ha sido
    !     transformado en otro personaje, mediante una llamada a
    !     CambiarJugador(nuevo, 1); (si el 1, la librería no intentará
    !     mostrar este mensaje)
    !  4: Una vez que la librería ha mostrado la descripción de la
    !     localidad, si el jugador estaba encima de un soporte, la
    !     librería generará este mensaje 4 para mostrar qué más cosas
    !     hay sobre el soporte
    !  Restantes:
    !     Son usados por la librería para listar los objetos "simples"
    !     que hay en la localidad. Son objetos "simples" los que no
    !     dan su propia auto-descripción a través de la propiedad
    !     "describir" o "inicial".
    switch(ml_n)
    {
     1: print " (sobre ", (el) ml_o, ")";
     2: print " (en ", (el) ml_o, ")";
     3: print " (como ", (object) ml_o,")";
     4: print "^Sobre ", (el) ml_o;
	EscribirListaDesde(child(ml_o),
                      ESPANOL_BIT + RECURSIVO_BIT + INFOPARCIAL_BIT
                      + BREVE_BIT + HAY_BIT + OCULTAR_BIT);
	".";
     default:
	if (ml_o~=localizacion)
     	{   if (ml_o has soporte) print "^Sobre "; else print "^En ";
	    print (el) ml_o;
	    print " puedes ver ";
	}
	else print "^Puedes ver ";
	if (n==5) print "también ";
	EscribirListaDesde(child(ml_o),
                      ESPANOL_BIT + BANDERAUX_BIT + RECURSIVO_BIT
                      + INFOPARCIAL_BIT + BREVE_BIT + OCULTAR_BIT);
	if (ml_o~=localizacion) ".";
	".";
    }

  Examinar:
    !  1: Error, el jugador intenta examinar un objeto, pero está a
    !     oscuras.
    !  2: Éxito, pero el objeto examinado no tiene descripcion
    !  3: Éxito, pero el objeto examinado no tiene descripcion, aunque
    !     tiene el atributo conmutable, por lo que la librería genera
    !     este mensaje para indicar si está apagado o encendido.
    switch(ml_n)
    {
     1: "Está demasiado oscuro, no puedes ver nada.";
     2: "No observas nada especial en ", (el) ml_o, ".";
     3: print (_El) ml_o, " ", (esta) ml_o;
	if (ml_o has encendido) " encendid", (o)ml_o, ".";
	else " apagad", (o)ml_o,".";
    }

  BuscarEn:
    ! La acción BuscarEn se genera ante la frase MIRA EN RECIPIENTE,
    ! MIRA EN SOPORTE, REGISTRA OBJETO.
    !
    !  1: Error, estamos a oscuras.
    !  2: Éxito examinando soporte, pero no hay nada sobre él.
    !  3: Éxito examinando soporte, listar lo que hay.
    !  4: El objeto examinado no es soporte ni recipiente, mensaje
    !     estándar indicando que no se encuentra nada.
    !  5: Error, El objeto examinado es recipiente, pero está cerrado.
    !  6: Éxito, el objeto examinado es recipiente abierto, pero no
    !     tiene nada dentro.
    !  7: Éxito, el objeto examinado es recipiente abierto y tiene
    !     cosas dentro. Listarlas.
    switch(ml_n)
    {
     1: "Está muy oscuro.";
     2: "No hay nada sobre ", (el) ml_o, ".";
     3: print "Sobre ", (el) ml_o;
	EscribirListaDesde(child(ml_o),
                      BREVE_BIT + ESPANOL_BIT + HAY_BIT + OCULTAR_BIT);
	".";
     4: "No encuentras nada interesante.";
     5: "No puedes ver lo que hay dentro ", (del) ml_o, " porque ",
	 (esta) ml_o, " cerrad", (o)ml_o, ".";
     6: print_ret (_El) ml_o, " ", (esta) ml_o, " vací", (o)ml_o,".";
     7: print "En ", (el) ml_o;
	EscribirListaDesde(child(ml_o),
                      BREVE_BIT + ESPANOL_BIT + HAY_BIT + OCULTAR_BIT);
	".";
    }

  QuitarCerrojo:
    ! QuitarCerrojo se genera ante ABRE <objeto> CON <objeto2>, o también
    ! ante QUITA CERROJO A <objeto> (en este segundo caso no se
    ! especifica la "llave" que abre la puerta).
    !
    !  1: Error, el objeto que se intenta abrir, no tiene el atributo
    !    cerrojo.
    !  2: Error, el objeto que se intenta abrir tiene atributo
    !     "cerrojo", pero no tiene atributo "cerrojoechado"
    !  3: Error, el <objeto2> que se intenta usar como llave, no
    !     coincide con la propiedad "con_llave" del <objeto> que
    !     intenta ser abierto.
    !  4: Éxito. El <objeto> se abre (con <objeto2> si éste ha sido
    !     especificado, el cual podemos encontrarlo en la variable "otro"
    switch(ml_n)
    {
     1: "No parece", (n) ml_o," tener ningún tipo de cerrojo.";
     2:	print_ret (_El) ml_o, " ya tenía", (n) ml_o, " abierto el cerrojo.";
     3: if (otro) "No parece", (n) ml_o, " encajar en la cerradura.";
	"Necesitas algún tipo de llave.";
     4: if (otro) "Quitas el cerrojo ", (al) ml_o, " con ", (el) otro, ".";
	"Quitas el cerrojo ", (al) ml_o, ".";
    }

 EcharCerrojo:
    ! EcharCerrojo se genera con CIERRA <objeto> CON <objeto2>, o
    ! también ante ECHA CERROJO A <objeto>. (sin especificar un
    ! segundo objeto en este caso)
    !
    !  1: Error, el objeto que se intenta cerrar no tiene la propiedad
    !     "cerrojo".
    !  2: Error, el objeto que se intenta cerrar tiene la propiedad
    !     "cerrojo", pero ya tiene también "cerrojoechado
    !  3: Error, el objeto tiene "cerrojo", pero está "abierto". No se
    !     le puede echar el cerrojo hasta que no se cierre.
    !  4: Error, el <objeto2> especificado no coincide con el que el
    !     <objeto> indica en su propiedad "con_llave".
    !  5: Éxito, el <objeto> es cerrado (con <objeto2> si este es
    !     especificado, el cual puede encontrarse en la variable
    !     "otro")
    switch(ml_n)
    {
      1: "No parece", (n) ml_o, " tener ningún tipo de cerrojo.";
      2: if (ml_o provides con_llave)
	  print_ret (_El) ml_o, " ya estaba", (n) ml_o, " cerrad", (o) ml_o,
	  " con llave.";
	else
	  print_ret (_El) ml_o, " ya tiene", (n) ml_o, " echado el cerrojo.";
      3: "Primero tendrás que cerrar ", (el) ml_o, ".";
      4: if (otro) "No parece", (n) ml_o, " encajar en la cerradura.";
	"Necesitas algún tipo de llave.";
      5: if (otro) "Cierras ", (el) ml_o," con ", (el) otro, ".";
	"Echas el cerrojo ", (al) ml_o, ".";
    }

 Encender:
    ! Generada al intentar ENCIENDE OBJETO si el objeto tiene el
    ! atributo "conmutable". Observar que si no lo tiene, la acción
    ! que se genera será sin embargo Quemar.
    !
    !   1: Error, el objeto no es conmutable (este error no aparecerá
    !      si el jugador pone ENCIENDE OBJETO, ya que en este caso la
    !      acción generada será Quemar objeto, pero puede aparecer si
    !      pone CONECTA OBJETO)
    !   2: Error, el objeto ya tenía el atributo "encendido"
    !   3: Éxito, el objeto tiene ahora activado "encendido".
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda encenderse.";
     2: print_ret "Ya estaba", (n) ml_o, " encendid", (o) ml_o, ".";
     3: "Enciendes ", (el) ml_o, ".";
    }

 Apagar:
    !  1: Error, el objeto no tiene el atributo "conmutable"
    !  2: Error, el objeto ya tenia desactivado el atributo
    !    "encendido"
    !  3: Éxito, el objeto tiene ahora desactivado "encendido"
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda apagarse.";
     2: print_ret "Ya estaba", (n) ml_o, " apagad", (o) ml_o, ".";
     3: "Apagas ", (el) ml_o, ".";
    }

  Abrir:
    !  1: Error, el objeto no tiene el atributo "abrible"
    !  2: Error, el objeto es abrible, pero tiene "cerrojoechado"
    !  3: Error, el objeto es abrible, pero ya tiene el atributo
    !     "abierto"
    !  4: Éxito, el objeto se abre, y además era recipiente y tenía
    !     cosas dentro. Se muestra entonces la lista de objetos que
    !     había en su interior (si había algo)
    !  5: Éxito, el objeto se abre (pero no tiene nada en su
    !     interior, o no era recipiente).
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda abrirse.";
     2: "Está", (n) ml_o, " cerrad", (o) ml_o, " con llave.";
     3: "Ya estaba", (n) ml_o, " abiert", (o) ml_o, ".";
     4: print "Abres ", (el) ml_o, ", descubriendo ";
	if (EscribirListaDesde(child(ml_o),
                      	  ESPANOL_BIT + BREVE_BIT + OCULTAR_BIT)==0) "nada.";
	".";
     5: "Abres ", (el) ml_o, ".";
    }

  Cerrar:
    !  1: Error, el objeto no tiene el atributo "abrible"
    !  2: Error, el objeto es "abrible" pero ya estaba quitado su
    !     atributo "abierto" (o sea, estaba ya cerrado)
    !  3: Éxito.
    switch(ml_n)
    {
     1: print_ret "No es algo que pueda cerrarse.";
     2: "Ya estaba", (n) ml_o, " cerrad", (o)ml_o, ".";
     3: "Cierras ", (el) ml_o, ".";
    }

  Desvestir:
    !  1: Error, el objeto no tenia el atributo "puesto"
    !  2: Éxito.
    switch(ml_n)
    {
     1: "No llevas puesto eso.";
     2: "Te quitas ", (el) ml_o, ".";
    }

  Vestir:
    !  1: Error, el objeto no tiene el atributo "prenda"
    !  2: Error, el jugador no tiene el objeto
    !  3: Error, el objeto ya tiene el atributo "puesto"
    !  4: Éxito.
    switch(ml_n)
    {
     1: "¡No puedes ponerte eso!";
     2: "No ", (lo) ml_o, " tienes.";
     3: "¡Ya ", (lo) ml_o, " llevas puest", (o) ml_o, "!.";
     4: "Te pones ", (el) ml_o, ".";
    }

  Comer:
    !  1: Error, el objeto no tiene el atributo "comestible"
    !  2: Éxito. [NOTA: la librería permite por defecto comerse
    !    cualquier cosa que tenga el atributo "comestible", pero la
    !    única acción que causa esto es que el objeto en cuestión
    !    desaparece del juego al ser comido]
    switch(ml_n)
    {
     1: "Eso es simplemente incomestible.";
     2: "Te comes ", (el) ml_o, ". No está mal.";
    }

!================================================================
! META COMANDOS
!================================================================
! Los siguientes verbos no consumen turno. No son acciones dentro del
! juego, sino fuera de él.
! Será raro que quieras redefinir estos mensajes.

 Pronombres:
    ! Esta acción (generada por el verbo PRONOMBRES) muestra una lista
    ! de qué significa en ese momento para el parser cada pronombre
    ! -lo, -la, -los, -las...
    !
    !  1: Texto introductorio
    !  2: La palabra "es"
    !  3: texto a mostrar si el pronombre no está definido
    !  4: Si el juego no define pronombres
    switch(ml_n)
    {
     1: print "En este momento, ";
     2: print "es ";
     3: print "no está definido";
     4: "el juego no conoce ningún pronombre.";
    }
 Finalizar:
    !  1: Respuesta al comando FIN
    !  2: Respuesta si el jugador escribe algo distinto de "si" o "no"
    switch(ml_n)
    {
     1: print "Por favor, responde sí o no.";
     2: print "¿Seguro que quieres abandonar el juego? ";
    }
 Reiniciar:
    !  1: Respuesta al comando REINICIAR
    !  2: Si no se puede reiniciar
    switch(ml_n)
    {
     1: print "¿Seguro que quieres reiniciar el juego? ";
     2: "Error.";
    }
 Restaurar:
    ! 1: Si no se pudo cargar la partida con LOAD
    ! 2: Éxito (no llega a mostrarse, porque en caso de éxito el
    !    estado del juego cambia al momento en que se salvó. El "Ok"
    !    que se ve entonces es el del comando Salvar.
    switch(ml_n)
    {
     1: "Error. No se pudo recuperar la partida.";
     2: "Ok.";
    }

 Salvar:
    ! 1: Si no se pudo guardar el juego
    ! 2: Éxito
    switch(ml_n)
    {
     1: "Error. No se pudo guardar.";
     2: "Ok.";
    }

 Verificar:
    ! 1: Éxito
    ! 2: Error en la verificación
    switch(ml_n)
    {
     1: "Fichero de juego verificado e intacto.";
     2: "El fichero de juego no parece intacto, puede estar corrompido
	(a menos que estés jugando con un intérprete muy primitivo que
	no sea capaz de realizar la comprobación).";
    }

 ActivarTranscripcion:
    ! 1: Error, ya estaba activada la transcripción
    ! 2: Éxito (parte inicial del mensaje, la librería añade el título
    !    del juego obtenido de la constante Historia)
    ! 3: Error, no se ha podido activar la transcripción
    switch (ml_n)
    {
     1: "La transcripción ya estaba activada.";
     2: "Iniciando la transcripción de";
     3: "Intento de iniciar la transcripción fallido.";
    }

 DesactivarTranscripcion:
    ! 1: Error, ya estaba desactivada la transcripción
    ! 2: Éxito
    ! 3: Error, no se ha podido desactivar la transcripción
    switch (ml_n)
    {
     1: "La transcripción ya estaba desactivada.";
     2: "^Fin de la transcripción.";
     3: "Intento de finalizar la transcripción fallido.";
    }

#Ifndef NO_PUNTUACION;
  ActivarNotificacion:
    "Notificación de puntuación activada.";

  DesactivarNotificacion:
    "Notificación de puntuación desactivada.";
#Endif; ! NO_PUNTUACION

#Ifndef NO_LUGARES;
 Lugares:
    ! El verbo "LUGARES" muestra un listado de los lugares que el
    ! jugador ha visitado. Aquí debemos escribir el texto
    ! introductorio a esa lista.
    print "Has visitado: ";
#Endif; ! NO_LUGARES

 ModoM1:
    ! La acción ModoM1 se genera ante el comando BREVE (o NORMAL). La
    ! librería imprime la constante Historia y a continuación este
    ! mensaje.
    " está ahora en su modo normal ~breve~, que da solo descripciones
    largas de los lugares la primera vez que son visitadas, y
    descripciones cortas en otro caso.";

 ModoM2:
    ! La acción ModoM2 se genera ante el comando LARGO. La
    ! librería imprime la constante Historia y a continuación este
    ! mensaje.
    " está ahora en su modo ~largo~, que siempre da descripciones
    largas de los lugares (incluso si ya habías estado antes).";

 ModoM3:
    ! La acción ModoM3 se genera ante el comando SUPERBREVE. La
    ! librería imprime la constante Historia y a continuación este
    ! mensaje.
    " está ahora en su modo ~superbreve~, que siempre da descripciones
    cortas de los lugares (incluso si nunca habías estado antes).";

#Ifndef NO_LUGARES;
 Objetos:
    ! Ante el verbo "OBJETOS" se genera esta acción, que muestra una
    ! lista de todos los objetos que el jugador ha manipulado a lo
    ! largo del juego, junto con una indicación de qué hizo con ellos.
    !
    !  1: Texto introductorio a la lista
    !  2: Si no ha manejado aún ninguno
    !  3: indicación de que lo lleva puesto
    !  4: indicación de que lo lleva en su inventario
    !  5: indicación de quién lo tiene ahora (si lo tiene un PNJ)
    !  6: indicación de dónde está el objeto (si está en una localidad)
    !  7: indicación de dónde está el objeto (si está en un "entrable")
    !  8: indicación de dónde está el objeto (si está en un recipiente)
    !  9: indicación de dónde está el objeto (si está en un soporte)
    !  10: indicación de que se ha perdido (no está en ninguno de los
    !     casos anteriores)
    switch(ml_n)
    {
     1: "Objetos que has manejado:^";
     2: "Ninguno.";
     3: print "   (puest", (o) ml_o, ")";
     4: print "   (l", (o) ml_o, " llevas)";
     5: print "   (en poder ", (del) ml_o, ")";
     6: print "   (en ", (name) ml_o, ")";
     7: print "   (en ", (el) ml_o, ")";
     8: print "   (dentro ", (del) ml_o, ")";
     9: print "   (en ", (el) ml_o, ")";
     10: print "   (perdid", (o) ml_o, ")";
 }
#Endif; ! NO_LUGARES

#Ifndef NO_PUNTUACION;
 Puntuacion:
    ! Puntuación del juego. Puede activarse porque el jugador lo pide
    ! (con el verbo "PUNTUACION") o porque el juego ha terminado. En
    ! este ultimo caso, la variable "banderafin" valdrá true.
    if (banderafin) print "En este juego, tu puntuación ha sido ";
    else print "Hasta el momento tu puntuación es ";
    print puntuacion, " de un total de ", PUNTUACION_MAX,
	", en ", turnos, " turno";
    if (turnos>1) print "s"; return;

 PuntuacionTotal:
    ! Puntuación en modo "explicativo". Puede activarse porque el
    ! jugador lo pida con el verbo "PUNTUACION LARGA" o porque el
    ! juego haya terminado (y la constante HAY_TAREAS está definida).
    !
    !  1: texto introductorio al desglose de puntos
    !  2: texto de objetos importantes (los que tienen el atributo
    !     "valepuntos")
    !  3: texto de lugares importantes (los que tienen el atributo
    !     "valepuntos")
    !  4: texto final, tras la suma total impresa por la librería
    switch(ml_n)
    {
     1: if (banderafin) print "La puntuación se desglosó ";
	else          print "La puntuación se desglosa ";
	"de la siguiente manera:^";
     2: "por encontrar objetos importantes";
     3: "por visitar lugares importantes";
     4: print "total (de ", PUNTUACION_MAX
	 ; ")";
    }
#Endif; ! NO_PUNTUACION

 Inv:
    ! Inventario
    !  1: Mensaje si el inventario está vacío
    !  2: Encabezado del inventario, antes de la lista de objetos
    !     generada por la librería
    switch(ml_n)
    {
     1: "No llevas nada.";
     2: print "Llevas";
    }
!================================================================
! MISCELANEA
!================================================================
! Esta es una falsa acción, que se usa simplemente para agrupar aquí
! todos los mensajes de error del parser, los mensajes ante algunos
! metacomandos, o algunos mensajes de librería no relacionados con
! acción alguna. La asignación de números a mensajes es bastante
! caprichosa.

! Debajo de cada mensaje un comentario indica en qué condiciones se
! genera.

 Miscelanea:
    switch(ml_n)
    {
     1: "(Sólo considero los dieciséis primeros objetos)^";
	! El jugador ha especificado objetos múltiples, pero el parser
	! tiene una lista que no admite más de 16, de modo que los
	! restantes objetos no serán procesados.

     2: "¡No sé a qué objetos te refieres!";
	! El jugador ha usado objetos múltiples, pero por alguna razón
	! la lista del parser está vacía.

     3: TextoLlamativo(" Has muerto ");
	! Mensaje fin de juego. Has muerto.

     4: TextoLlamativo(" Has ganado ");
	! Mensaje fin de juego de victoria.

     5: ! Mensaje a mostrar tras el fin del juego, para pedir al
	! jugador si quiere reiniciar, recuperar, anular, puntuación,
	! curiosidades o terminar.
	print "^¿Quieres REINICIAR, RECUPERAR un juego guardado";
                  #Ifdef DEATH_MENTION_ANULAR;
                  print ", ANULAR tu último movimiento";
                  #Endif;
  #Ifndef NO_PUNTUACION;
	if (HAY_TAREAS==0)
	    print ", ver la PUNTUACIÓN de este juego";
  #Endif; ! NO_PUNTUACION
	if (banderafin==2 && HAY_CURIOSIDADES==0)
	    print ", ver algunas CURIOSIDADES";
	" o TERMINAR?";

     6: "[Tu intérprete no puede ~deshacer~ acciones, ¡lo siento!]";
	! Error si el intérprete no tiene "undo"

     7: "~deshacer~ falló. [No todos los intérpretes lo tienen.]";
	! Otro error si el intérprete no tiene "undo", pero no había
	! sido detectado correctamente

     8: "Por favor, da una de las respuestas anteriores.";
	! Si el jugador no responde correctamente a la pregunta del
	! mensaje [Miscelanea,5]

     9: "^¡Te has quedado a oscuras!";
	! Mensaje cuando se detecta, al final del turno, que ya no hay
	! luz.

     10: "¿Perdón?";
	! Mensaje cuando el jugador introduce una linea en blanco (no
	! llega a generarse acción alguna, por tanto no se consume
	! turno ni se ejecutan daemons)

     11: "[No puedes ~deshacer~ lo que no has hecho.]";
	! Si el jugador intenta "undo" al principio del juego

     12: "[No puedes ~deshacer~ dos veces seguidas. ¡Lo siento!]";
	! Si el jugador pone "undo" dos veces

     13: "[Retrocediendo al turno anterior.]";
	! Éxito en el "undo"

     14: "Lo siento, eso no puede corregirse.";
	! Si el jugador pone EEPA (verbo para corregir), pero el
	! parser no recordaba ninguna palabra mal
	! El comando EEPA se usa así, por ejemplo:
	!   > SACA MAZANA VERDE DE LA CESTA
	!   No veo eso por aquí
	!   > EEPA MANZANA
	!   Sacas la manzana verde de la cesta de mimbre.

     15: "No te preocupes.";
	! Si el jugador pone EEPA sólo (sin especificar la palabra
	! corregida)

     16: "~eepa~ sólo puede corregir una palabra.";
	! Si el jugador pone EEPA seguido de dos o más palabras

     17: "Está muy oscuro y no puedes ver nada.";
	! Descripción del objeto Oscuridad

     18: print "ti mism", (o) jugador;
	! Nombre corto del objeto jugador

     19: "Tan buen aspecto como siempre.";
	! Descripción del objeto jugador

     20: "Para repetir un comando como ~rana, salta~, escribe
	~repite~, en lugar de ~rana, repite~.";
	! Cuando el jugador pone PNJ, REPITE para que el PNJ haga otra
	! vez la última acción.

     21: "No hay comando que repetir.";
	! Cuando el jugador pone REPITE como primer comando del juego.

     22: "No puedes empezar la frase con una coma.";
	! Cuando ha empezado la frase con una coma :-)

     23: "Parece que quieres hablar con alguien, pero no veo con
	quién.";
	! Cuando el jugador pone PEPE, COGE HACHA, pero no hay un
	! objeto que responda al nombre PEPE.

     24: "No puedes hablar con ", (el) ml_o, ".";
	! Si el jugador intenta hablar con un objeto que no es
	! "animado" ni "hablable" ("hablable" debe ponerse a objetos
	! inanimados con los que se podría hablar, como un micrófono)

     25: "Para hablar con alguien intenta ~alguien, hola~ o algo
	así.";
	! Si hay palabras no comprendidas entre el nombre del PNJ y
	! la coma, como p. ej.: PEPE XADASDGG, SALTA

     26: "(primero tratas de ", (coge)"r ", (el) ml_o, ")";
	! Si la gramática especifica que una acción debe efectuarse
	! sobre un objeto en poder del jugador (token "held"), pero el
	! jugador lo intenta sobre un objeto que no tiene, pero que
	! está accesible, el parser intentará automáticamente coger
	! ese objeto antes de efectuar la acción. En este mensaje se
	! avisa al jugador de esta intención.

! ================================================================
! ERRORES DE PARSING
! Estos errores son generados por la librería, a menos que el
! programador proporcione su propia función ErrorParser para
! manejo de errores.

     27:! El parser se ha atascado. Es el tipo de error más
	! genérico. Si el parser puede, dará un error más concreto
	! (uno de los siguientes)
	"No entendí esa frase.";

     28:! Al parser le sobran palabras, aunque ha entendido gran parte
	! de la orden. Si la variable parser_listo es 1, debemos
	! sugerir al jugador un comando para ejecutar, basado en lo
	! que había entendido el parser hasta el momento y esperar a
	! que el jugador responda Si o No para ejecutar ese comando.
	! Si parser_listo es 0, un simple mensaje de error basta
	! Si parser_listo es 2, no pregunta y realiza la acción
	!modo_mantenido=0;
	!^^^^^^^^^^^ [030305] esto ahora se controla desde EParser.h
        ! [010515] Si parte del comando era la
	! conjunción Y, el parser queda en "modo mantenido", lo que
	! puede causar errores en la interpretación de comandos
	! subsiguientes, por si acaso, lo desactivamos
	switch (parser_listo)
	{
	  1:
	    print "No entiendo la última parte. ¿Quieres ";
            ImprimirComando(0); print "?^^>";
            si_pl=SiONo();
          0:
            print "No entendí la última parte de la frase.^";  ! [030305]
            si_pl=false;
          2:
            si_pl=true;
        }

     29: ! El parser esperaba un token de tipo número
	"No comprendí ese número.";

     30: ! El parser no ha comprendido el nombre del objeto al que se
	! refiere el jugador, o ese objeto no está aquí.
	"No veo eso que dices.";

     31: ! Este error parece que no se genera nunca. Un posible bug de
	! librería, o restos de versiones arcaicas
 	"¡Pareces haber dicho muy poca cosa!";

     32: ! El objeto que el jugador intenta usar no está en su
	! poder. El parser ha intentado "cogerlo de forma automática",
	! pero ha fallado
	"¡No tienes eso!";

     33: ! El jugador ha intentado usar objetos múltiples (o "TODO")
	! con un verbo que en su gramática no lo admite.
	"No puedes especificar objetos múltiples con ese verbo.";

     34: ! El jugador ha intentado objetos múltiples para "uno" y para
	! "otro", como en METE TODO EN TODO.
 	"Sólo puedes especificar objetos múltiples una vez en cada
	línea.";

     35: ! El jugador ha usado un pronombre, como COMELO, pero el
	! parser no tiene asignado un valor a ese pronombre.
 	"No estoy seguro de a qué se refiere ~", (address) palabra_pronombre,
	 "~.";

     36: ! El jugador ha puesto una lista de objetos y ha usado la
	! palabra EXCEPTO para exceptuar algo que no estaba incluido
	! en la lista, por ejemplo: COGE TODAS LAS MONEDAS EXCEPTO EL
	! SACO.
	"Has exceptuado algo que no estaba incluido.";

     37:! La gramática de un verbo obliga a que el objeto sobre el que
	! se actúe sea animado (tiene un token de tipo "creature"),
	! pero el jugador lo ha intentado sobre un objeto que no es
	! animado.
	"Sólo puedes hacer eso con seres animados.";

     38: ! La primera palabra usada por el jugador es desconocida (o
	! la primera palabra tras la coma, si se trata de una orden a
	! un PNJ)
	"No conozco ese verbo.";

     39: ! El jugador intenta acciones sobre las palabras que están en
	! la propiedad "irrelevante" de la localidad
 	"Eso no es importante.";

     40: ! El jugador ha usado un pronombre, como EXAMINALO, pero el
	! pronombre se refiere a un objeto que ya no está visible.
 	"Ahora mismo no puedes ver lo que representa el pronombre ~",
	  (address) palabra_pronombre,
	 "~ (", (el) objeto_pronombre, ").";

     41: ! Este error no sale nunca. Probablemente sigue aquí por
	! razones de compatibilidad, o por despiste de Graham ¿Tal vez
	! ha sido sustituido en versiones más recientes por el mensaje
	! número 28?
	"No entendí la última parte de la orden.";

     42: ! El jugador ha solicitado un numero de objetos en una lista
	! de objetos múltiples, pero el parser no es capaz de
	! encontrar tantos. Por ejemplo: COGE SEIS MONEDAS.
	! En ml_o se recibe el número de objetos hallados por el
	! parser.
 	if (ml_o==0) "No hay suficientes.";
         else if (ml_o==1){
	 print "Aquí sólo hay un";
	 if (objeto_multiple-->1) print (o) objeto_multiple-->1;
	 else print "o";
	 " disponible.";
        }
	else
	   "Sólo hay ", (number) ml_o, " disponibles para esa acción.";

     43: ! El jugador ha puesto TODO como objeto múltiple, pero el
	! parser no ha encontrado ningún objeto. En realidad este
	! error parece no producirse nunca (otro bug de librería) ya
	! que el que siempre acaba generándose es el siguiente (44)
 	"¡No encuentro nada para hacer eso!";

     44: ! El jugador ha intentado objetos múltiples usando TODO
         ! pero el parser no ha encontrado ninguno. Por ejemplo, COGE
         ! TODO o DEJA TODO si no hay nada cerca o en el inventario.
         ! Modificado en [020621] para dar un mensaje más coherente
         ! si el jugador tiene algún objeto en su inventario.
       if (accion_que_seria == ##Dejar) {
         print "¡Pero si no llevas nada";
         if (children (jugador))
           " de eso!";
         else
           "!";
       }
       print "No hay nada para ";
       IdiomaVerbo(palabra_verbo);
       ".";

     45:! El jugador ha nombrado un PNJ ambiguo (hay más de uno con el
	! mismo nombre cerca). El parser le pide aclaración. Este
	! mensaje es la primera parte de la pregunta, el resto lo pone
	! el parser (que es la lista de PNJs entre los que
	! duda). Debemos poner a 1 la variable PreguntaCualExactamente
	! cuando se generan este tipo de preguntas aclaratorias.
 	print "¿Quién concretamente, ";
	PreguntaCualExactamente=1;
	ImprimirListaDudosos("o");
	print "?^";

     46:! El jugador ha nombrado un objeto ambiguo (hay más de uno con el
	! mismo nombre cerca). El parser le pide aclaración. Este
	! mensaje es la primera parte de la pregunta, el resto lo pone
	! el parser (que es la lista de objetos entre los que
	! duda). Debemos poner a 1 la variable PreguntaCualExactamente
	! cuando se generan este tipo de preguntas aclaratorias.
 	print "¿Cuál concretamente, ";
	PreguntaCualExactamente=1;
	ImprimirListaDudosos("o");
	print "?^";

     47: ! El jugador ha respondido "TODOS" o "AMBOS" a una pregunta
	! aclaratoria como la anterior, pero el verbo no admite
	! objetos múltiples
	print "Lo siento, sólo puedes referirte a un objeto aquí. ¿Cuál
	    exactamente?^";
	PreguntaCualExactamente=1;

     48: !El jugador ha escrito una frase u orden a PSI incompleta,
         !como BESA (verbo aplicado sobre PSIs normalmente).
         !El parser le pregunta para que complete la frase
 	PreguntaCualExactamente=1;
	if (IniciarPregunta()==0) print "A quién";
	if (actor ~= jugador) print " tiene que ";
	else print " quieres ";
     	IdiomaImprimirComando();
	if (actor~=jugador) print " ", (el) actor;
	print "?^";

     49: !El jugador ha escrito una frase u orden a PSI incompleta,
         !como COGE (verbo aplicado sobre objetos normalmente).
         !El parser le pregunta para que complete la frase
	PreguntaCualExactamente=1;
	if (IniciarPregunta()==0) print "Qué";
	if (actor ~= jugador) print " tiene que ";
	else print " quieres ";
     	IdiomaImprimirComando();
	if (actor~=jugador) print " ", (el) actor;
	print "?^";

#Ifndef NO_PUNTUACION;
     50: ! El jugador acaba de realizar una acción que puntúa (la
	! librería ha detectado que la variable puntuacion ha cambiado
	! de valor). Se informa de ello al jugador. El parámetro ml_o
	! contiene el incremento (o decremento) en la puntuación.
	print "Tu puntuación ha ";
	if (ml_o > 0)
          print "aumentado";
        else {
          ml_o = -ml_o;
          print "disminuido";
        }
	print " en ", (number) ml_o, " punto";
	if (ml_o > 1) print "s";
#Endif; ! NO_PUNTUACION

     51: ! El jugador ha intentado una acción con objeto múltiple
	! (como COGE TODO). Esta acción es convertida por el parser en
	! una serie de acciones COGE OBJETO1, COGE OBJETO2, etc... Si
	! en la ejecución de alguna de estas acciones encuentra que la
	! localidad del jugador ha cambiado, debe abortar el
	! proceso. Este mensaje informa de ello al jugador.
	!
	"(Ya que ha ocurrido algo dramático, se ha recortado la lista
	de objetos sobre los que actuabas)";

     52: ! En los menús, se espera a que el jugador escriba un número
	! para mostrar una entrada del menú. Si pulsa un numero
	! incorrecto, se saca este mensaje. El parámetro ml_o contiene
	! el número más alto válido
	"^Escribe un número del 1 al ", ml_o,
	 ", 0 para volver a mostrarlo, o pulsa Intro.";

     53: ! Mensaje que muestra el sistema de menús cuando espera una
	! tecla
 	"^[Por favor, pulsa ESPACIO]";
    }

 ListaMiscelanea:
    ! Los siguientes mensajes se muestran como aclaraciones cuando se
    ! está listando el inventario del jugador, o los objetos que hay
    ! en una localidad. Junto a cada mensaje se comenta qué
    ! condiciones deben darse en ese objeto para que se muestre ese
    ! mensaje aclaratorio

    switch(ml_n)
    {
     1: print " (alumbrando)";
	! El objeto tiene "luz" y la localidad no
     2: print " (que ", (esta) ml_o, " cerrad", (o) ml_o, ")";
	! El objeto tiene "recipiente" pero no "abierto"
     3: print " (cerrad", (o) ml_o, " y alumbrando)";
	! Casos 2 y 1 juntos
     4: print " (que ", (esta) ml_o, " vací", (o) ml_o, ")";
	! El objeto es un recipiente abierto (o transparente) y no
	! tiene nada en su interior
     5: print " (vací", (o) ml_o, " y alumbrando)";
	! Casos 1 y 4 juntos
     6: print " (que ", (esta) ml_o, " cerrad", (o) ml_o, " y vací",
	 (o) ml_o, ")";
	! El objeto tiene "recipiente", no "abierto", pero sí
	! "transparente"
     7: print " (cerrad", (o) ml_o, ", vací", (o) ml_o, " y
	    alumbrando)";
	! Casos 1 y 6 juntos

! Los casos siguientes son similares, pero se muestran cuando
! se solicita a la rutina EscribirListaDesde la opción INFOTOTAL
! La librería puede combinar varios de estos mensajes, por eso no
! deben llevar el cerrar paréntesis al final, que lo añade la
! propia librería
! ************************************
!  NO SE ACONSEJA CAMBIAR ESTOS
! ************************************

     8: print " (alumbrando y que llevas puest", (o) ml_o;
	! El objeto tiene "luz" y "puesto"
     9: print " (alumbrando";
	! El objeto tiene "luz" pero no "puesto"
     10: print " (que llevas puest", (o) ml_o;
	! El objeto tiene "puesto" pero no "luz"
     11: print " (que ", (esta) ml_o, " ";
	! Mensaje introductorio para decir "que está
	! abierto/cerrado/vacío"...
     12: print "abiert", (o)ml_o;
	! Objeto tiene "recipiente", "abrible" y "abierto" (y cosas dentro)
     13: print "abiert", (o)ml_o, " pero vací", (o) ml_o;
	! Objeto tiene "recipiente", "abrible" y "abierto (pero vacío)
     14: print "cerrad", (o) ml_o;
	! Objeto tiene "recipiente", "abrible"  y no "abierto"
     15: print "cerrad", (o) ml_o, " con llave";
	! Objeto tiene "recipiente", "abrible" y "cerrojoechado" o "cerrojo"
     16: print " vací", (o) ml_o;
	! Objeto tiene "recipiente", no "abrible" y "transparente"
     17: print " (que ", (esta) ml_o, " vací", (o) ml_o, ")";
	! Como el caso anterior, pero mensaje más "largo" (que se activa si
	! EscribirListaDesde es llamada sin el modo BREVE_BIT)
     18: print " que contiene ";
	! encabezado a la lista de lo que hay dentro del objeto
     19: print " (sobre ", (el_) ml_o;
	! Si el objeto tiene "soporte", la librería va a listar sus
	! contenidos. Este es el encabezado de la lista
     20: print ", encima ", (del_) ml_o;
	! Como e l9, pero en otra modalidad (que se activa si
	! EscribirListaDesde es llamada sin el modo BREVE_BIT)
     21: print " (en ", (el_) ml_o;
	! Si el contenido tiene "recipiente" y puede verse su interior
	! y hay cosas, la librería va a mostrar sus contenidos. Este
	! es el encabezado de la lista
     22: print ", dentro ", (del_) ml_o;
	! Como el 21, pero en otra modalidad (que se activa si
	! EscribirListaDesde es llamada sin el modo BREVE_BIT)
    }

];
! ---------------------------------------------------------------------------

[ TextoLlamativo txt;
    ! Imprime un texto rodeado de asteriscos y en negrita. Es usado
    ! para mostrar el mensaje *** Has muerto *** y *** Has ganado ***
    ! Puedes cambiarlo si quieres que aparezcan en otros formatos.
#Ifdef TARGET_ZCODE;
    #IfV5; style bold; #Endif;
#Ifnot; ! TARGET_GLULX
     glk($0086, 5); ! set alert style
#Endif; ! TARGET_
     print "***", (string) txt, "***"; ! [010508] Corregido bug (string)
#Ifdef TARGET_ZCODE;
     #IfV5; style roman; #Endif;
#Ifnot; ! TARGET_GLULX
     glk($0086, 0); ! set normal style
#Endif; ! TARGET_
      print "^^^";
];


! La siguiente función imprime la lista de objetos entre los que el
! parser tiene dudas (porque todos ellos responden al nombre que ha
! usado el jugador). Esta rutina es llamada desde los mensajes
! (Miscelanea,45) y (Miscelanea,46)

! Modificada en [021025] para que pregunte sólo por aquellos objetos
! empatados a puntuación máxima por la desambiguación.

[ ImprimirListaDudosos conjuncion
    i k marker punt_max num_objs;
  marker = 0;

  for (i = 0, punt_max = -1: i < numero_de_encajados: i++) {
    if (encajan_puntos-->i > punt_max) {
      punt_max = encajan_puntos-->i;
      num_objs = 1;
    }
    else if (encajan_puntos-->i == punt_max)
      num_objs++;
  }

  for (i = 1: i <= numero_de_clases: i++)
  {
      while (((encajan_clases-->marker) ~= i)
             && ((encajan_clases-->marker) ~= -i)) marker++;
      k=lista_encajan-->marker;

      if (encajan_puntos-->marker == punt_max) {
        if (encajan_clases-->marker > 0) print (el) k; else print (un) k;

        if (i < num_objs - 1)  print ", ";
        if (i == num_objs - 1) print " ", (string) conjuncion, " ";
      }
  }
];
