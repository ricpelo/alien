Include "Gipi.h";
ZIPI_Menu ZIPI_Menu0
with
  ZIPI_titulo "Sistema de pistas interactivas",
  ZIPI_item
    ZIPI_Menu1
    ZIPI_Separador
    ZIPI_Menu3
    ZIPI_Menu4
    ZIPI_Menu7
    ZIPI_Menu8
    ZIPI_Separador
    ZIPI_Menu17
;
ZIPI_Menu ZIPI_Menu1
with
  ZIPI_titulo "Información general - Lee esto primero",
  ZIPI_item
    ZIPI_Otro0
    ZIPI_Otro1
    ZIPI_Otro2
    ZIPI_Otro3
    ZIPI_Otro4
    ZIPI_Otro5
    ZIPI_Otro6
    ZIPI_Menu2
    ZIPI_Otro14
;
ZIPI_Menu ZIPI_Menu2
with
  ZIPI_titulo "Problemas y preguntas frecuentes",
  ZIPI_item
    ZIPI_Otro7
    ZIPI_Otro8
    ZIPI_Otro9
    ZIPI_Otro10
    ZIPI_Otro11
    ZIPI_Otro12
    ZIPI_Otro13
;
ZIPI_Menu ZIPI_Menu3
with
  ZIPI_titulo "En la nave",
  ZIPI_item
    ZIPI_Pista0
    ZIPI_Pista1
    ZIPI_Pista2
    ZIPI_Pista3
    ZIPI_Pista4
;
ZIPI_Menu ZIPI_Menu4
with
  ZIPI_titulo "En el exterior",
  ZIPI_item
    ZIPI_Pista5
    ZIPI_Pista6
    ZIPI_Menu5
;
ZIPI_Menu ZIPI_Menu5
with
  ZIPI_titulo "¿Cómo entro en el procesador atmosférico?",
  ZIPI_item
    ZIPI_Pista7
    ZIPI_Pista8
    ZIPI_Menu6
;
ZIPI_Menu ZIPI_Menu6
with
  ZIPI_titulo "¿Y ahora?       ",
  ZIPI_item
    ZIPI_Pista9
    ZIPI_Pista10
;
ZIPI_Menu ZIPI_Menu7
with
  ZIPI_titulo "En el procesador atmosférico",
  ZIPI_item
    ZIPI_Pista11
    ZIPI_Pista12
    ZIPI_Pista13
    ZIPI_Pista14
    ZIPI_Pista15
    ZIPI_Pista16
;
ZIPI_Menu ZIPI_Menu8
with
  ZIPI_titulo "En el complejo de la colonia minera",
  ZIPI_item
    ZIPI_Pista17
    ZIPI_Menu9
    ZIPI_Pista25
    ZIPI_Menu12
    ZIPI_Pista28
    ZIPI_Pista29
    ZIPI_Menu13
;
ZIPI_Menu ZIPI_Menu9
with
  ZIPI_titulo "Estancias del complejo - información general",
  ZIPI_item
    ZIPI_Pista18
    ZIPI_Menu10
;
ZIPI_Menu ZIPI_Menu10
with
  ZIPI_titulo "Zonas del complejo",
  ZIPI_item
    ZIPI_Otro15
    ZIPI_Menu11
;
ZIPI_Menu ZIPI_Menu11
with
  ZIPI_titulo "Zonas del complejo (¿has leído la advertencia anterior?)",
  ZIPI_item
    ZIPI_Pista19
    ZIPI_Pista20
    ZIPI_Pista21
    ZIPI_Pista22
    ZIPI_Pista23
    ZIPI_Pista24
;
ZIPI_Menu ZIPI_Menu12
with
  ZIPI_titulo "¡A por Jason!",
  ZIPI_item
    ZIPI_Pista26
    ZIPI_Pista27
;
ZIPI_Menu ZIPI_Menu13
with
  ZIPI_titulo "¿Y ahora, qué?",
  ZIPI_item
    ZIPI_Pista30
    ZIPI_Pista31
    ZIPI_Pista32
    ZIPI_Menu14
    ZIPI_Menu16
    ZIPI_Pista39
;
ZIPI_Menu ZIPI_Menu14
with
  ZIPI_titulo "La puerta cerrada del nivel -1",
  ZIPI_item
    ZIPI_Pista33
    ZIPI_Pista34
    ZIPI_Menu15
    ZIPI_Pista37
;
ZIPI_Menu ZIPI_Menu15
with
  ZIPI_titulo "¿Qué hago dentro?",
  ZIPI_item
    ZIPI_Pista35
    ZIPI_Pista36
;
ZIPI_Menu ZIPI_Menu16
with
  ZIPI_titulo "¡Nos vamos!",
  ZIPI_item
    ZIPI_Pista38
;
ZIPI_Menu ZIPI_Menu17
with
  ZIPI_titulo "Información adicional (mapas y solución)",
  ZIPI_item
    ZIPI_Menu18
    ZIPI_Separador
    ZIPI_Menu20
;
ZIPI_Menu ZIPI_Menu18
with
  ZIPI_titulo "Mapas (sólo para casos de extrema necesidad)",
  ZIPI_item
    ZIPI_Otro16
    ZIPI_Otro17
    ZIPI_Menu19
;
ZIPI_Menu ZIPI_Menu19
with
  ZIPI_titulo "El complejo",
  ZIPI_item
    ZIPI_Otro18
    ZIPI_Otro19
    ZIPI_Otro20
;
ZIPI_Menu ZIPI_Menu20
with
  ZIPI_titulo "Solución (prohibido leer esto)",
  ZIPI_item
    ZIPI_Otro21
    ZIPI_Otro22
    ZIPI_Otro23
    ZIPI_Menu21
;
ZIPI_Menu ZIPI_Menu21
with
  ZIPI_titulo "El complejo",
  ZIPI_item
    ZIPI_Otro24
    ZIPI_Otro25
    ZIPI_Otro26
    ZIPI_Otro27
    ZIPI_Otro28
    ZIPI_Otro29
;
ZIPI_Pista ZIPI_Pista0
with
  ZIPI_titulo "¿Qué tengo que hacer en la nave?",
  ZIPI_pistas
    "Examina todo lo que te rodea (eso siempre)."
    "Pero, básicamente, lo que tienes que hacer es salir al exterior."
    "Para salir, tienes que abrir la compuerta de la nave..."
    "... pero no puedes hacerlo manualmente."
    "Pide a la computadora que lo haga por ti."
    "~MADRE, ABRE LA COMPUERTA~."
    "Aunque sin oxígeno en el exterior, no podrás salir hasta que te hayas puesto el traje atmosférico."
;
ZIPI_Pista ZIPI_Pista1
with
  ZIPI_titulo "¿Por qué tengo que usar los trajes atmosféricos?",
  ZIPI_pistas
    "Cuando llegáis al planeta, la atmósfera es irrespirable debido a un fallo en el procesador atmosférico."
    "El procesador atmosférico es un edificio en el que se procesa la atmósfera del planeta para producir oxígeno respirable."
    "¿Es posible respirar en el exterior sin necesidad de trajes? La respuesta es que..."
    "... SÍ, pero para ello tendrás que arreglar primero el procesador atmosférico."
;
ZIPI_Pista ZIPI_Pista2
with
  ZIPI_titulo "¿Cómo consigo los trajes atmosféricos?",
  ZIPI_pistas
    "Tendrás que abrir el compartimento de los trajes."
    "¿No puedes abrirlo manualmente? Pide a Madre que lo haga por ti."
    "~MADRE, ABRE EL COMPARTIMENTO~."
;
ZIPI_Pista ZIPI_Pista3
with
  ZIPI_titulo "¿Cómo consigo que Jason salga de la nave?",
  ZIPI_pistas
    "Jason sólo saldrá de la nave si lleva puesto su traje atmosférico."
    "Pídele que se lo ponga..."
    "... o simplemente déjalo a su alcance. Él se lo pondrá."
    "Para ello, tal vez necesites abrir previamente el compartimento para trajes."
    "~JASON, COGE TU TRAJE~ o ~JASON, PONTE TU TRAJE~."
;
ZIPI_Pista ZIPI_Pista4
with
  ZIPI_titulo "¿Hay algo más que pueda hacer en la nave?",
  ZIPI_pistas
    "¿La has recorrido completamente?"
    "¿Has visitado la popa de la nave?"
    "Dirígete al OESTE desde la localidad de inicio."
    "¿Ves algo interesante?"
    "¿Qué habrá en ese armario?"
    "¿Y en esa caja?"
    "Recógelo todo. Te puede ser de utilidad en el futuro."
;
ZIPI_Pista ZIPI_Pista5
with
  ZIPI_titulo "¿Es normal que Jason se quede en la nave?",
  ZIPI_pistas
    "Jason se quedará en la nave si no lleva puesto su traje atmosférico."
    "Puedes continuar explorando sin él."
    "En ese caso, podréis comunicaros como si estuviériais juntos, gracias al transmisor que llevas en tu oído."
    "¿Es recomendable moverte sin tener a Jason a tu lado? Pues..."
    "... francamente, NO."
    "Haz que Jason se ponga su traje y que salga contigo."
;
ZIPI_Pista ZIPI_Pista6
with
  ZIPI_titulo "¿Cómo entro en el complejo minero?",
  ZIPI_pistas
    "La puerta es imposible de abrir manualmente."
    "Y no hay ningún tipo de cerradura o panel de control que se pueda accionar."
    "Definitivamente: NO puedes abrir esa puerta."
    "Intenta antes arreglar el procesador atmosférico."
    "Al final no será necesario abrir esa puerta..."
    "... porque el monstruo habrá abierto un buen agujero con su sangre ácida."
;
ZIPI_Pista ZIPI_Pista7
with
  ZIPI_titulo "¿Cómo entro en el procesador atmosférico?",
  ZIPI_pistas
    "Tienes que abrir la puerta."
    "Para abrir la puerta tienes que usar el panel de control situado junto a ella."
    "Primero hay que hacer funcionar el panel de control, y luego teclear un código de acceso."
;
ZIPI_Pista ZIPI_Pista8
with
  ZIPI_titulo "¿Qué hago con el panel de control?",
  ZIPI_pistas
    "Está un poco destrozado... ¿Has probado a soldar los cables?"
    "No, me temo que así no conseguirás nada..."
    "El problema es que no le llega energía suficiente."
    "¿Cómo podrías suministrar energía a sus circuitos fácilmente?"
    "Mira en tu inventario... ¿Hay algo que consuma energía?"
    "Si no es así... ¿has mirado bien dentro de la nave? Algo que dé luz..."
    "La linterna consume la energía de una batería."
    "Conecta la batería al panel de control."
;
ZIPI_Pista ZIPI_Pista9
with
  ZIPI_titulo "¿Cómo consigo el código de acceso?",
  ZIPI_pistas
    "¿El panel ya dispone de energía? Entonces sólo falta teclear el código correcto."
    "Ese código te lo puede facilitar alguien."
    "Ese alguien puede ser Madre o el robot."
    "El robot conoce un código, porque iba a arreglar el procesador, aunque se quedó a mitad de camino."
    "Prueba a empujar al robot hasta la puerta."
    "Madre también sabe el código."
    "El código es 759812. Ve al panel de control y tecléalo."
    "¡Vaya! Ese código ya no sirve, porque el panel de control se ha reiniciado."
    "Hay que identificar el nuevo código usando la semilla."
;
ZIPI_Pista ZIPI_Pista10
with
  ZIPI_titulo "¿Para qué sirve la semilla?",
  ZIPI_pistas
    "La clave que da el robot ya no sirve, y el panel dice que la semilla es 9957."
    "Al reiniciarse el panel, el código de acceso se ha regenerado a partir de la semilla."
    "Pregúntale a Madre sobre la semilla."
    "Dale a Madre el valor de la semilla que indica el display."
    "~MADRE, LA SEMILLA ES 9957~."
    "Madre te dirá que el nuevo código es el 258741. Tecléalo en el panel."
;
ZIPI_Pista ZIPI_Pista11
with
  ZIPI_titulo "¡Está oscuro! ¡No veo nada!",
  ZIPI_pistas
    "No hay luz artificial en ningún edificio. Necesitas otra fuente de luz."
    "¿Has probado con la linterna?"
    "Pero la batería se ha descargado para poder abrir la puerta..."
    "Deberás recargarla."
    "Hay un cargador de baterías en la nave."
    "~RECARGA LAS BATERIAS~ en la sala de proa de la nave."
;
ZIPI_Pista ZIPI_Pista12
with
  ZIPI_titulo "¿Mejor solo o acompañado?",
  ZIPI_pistas
    "¿Has probado a entrar solo?"
    "Si entras solo, el monstruo sale y te mata..."
    "Está claro que es mejor llegar acompañado."
;
ZIPI_Pista ZIPI_Pista13
with
  ZIPI_titulo "¡Socorro!",
  ZIPI_pistas
    "¿El monstruo se ha llevado a Jason?"
    "Al menos estás vivo... ¡Y Jason también!"
    "Hay que rescatar a Jason."
    "Sigue el rastro de ácido que ha dejado el monstruo, pero..."
    "... recuerda que el procesador atmosférico sigue estropeado."
;
ZIPI_Pista ZIPI_Pista14
with
  ZIPI_titulo "¿Cómo arreglo el procesador atmosférico?",
  ZIPI_pistas
    "Todo está gobernado por la unidad central."
    "Hay que abrir la caja de conexiones."
    "Para ello necesitas una herramienta adecuada."
    "Nada más adecuado que un destornillador. Quita con él el tornillo que cierra la tapa."
    "~ABRE LA CAJA DE CONEXIONES CON EL DESTORNILLADOR~."
;
ZIPI_Pista ZIPI_Pista15
with
  ZIPI_titulo "¿Y ahora?",
  ZIPI_pistas
    "Al abrir la caja de conexiones, ves que hay un circuito dañado."
    "Hay que soldar ese circuito para arreglarlo."
    "¿Quién puede ayudarte a soldar? ¿Has mirado por los alrededores?"
    "El androide es un robot de mantenimiento. Entre otras cosas, puede soldar."
    "Pero no puedes con él: pesa demasiado."
    "Ve empujándolo hasta llegar al interior del procesador atmosférico."
    "~EMPUJA AL ROBOT HACIA EL NORTE~, luego al norte otra vez, y luego adentro."
;
ZIPI_Pista ZIPI_Pista16
with
  ZIPI_titulo "¿Qué me queda?",
  ZIPI_pistas
    "¿Ya tienes al experto soldador delante del circuito dañado?"
    "Sólo te queda pedirle que lo arregle."
    "~ROBOT, ARREGLA EL CIRCUITO~."
;
ZIPI_Pista ZIPI_Pista17
with
  ZIPI_titulo "El complejo - información general",
  ZIPI_pistas
    "El complejo está construido alrededor de la veta de mineral."
    "Las zonas del interior del complejo se comunican entre sí mediante túneles."
    "Hay cuatro balcones que dan a la veta, situados al N, S, E y O de la misma."
    "Por las zonas más al oeste podrás encontrar puertas cerradas hacia los hábitats."
    "El complejo tiene tres niveles: el nivel 0 en la superficie y los niveles -1 y -2 subterráneos."
    "El nivel -2 tiene aún zonas sin acabar."
;
ZIPI_Pista ZIPI_Pista18
with
  ZIPI_titulo "Generalidades",
  ZIPI_pistas
    "El complejo contiene todo lo necesario para vivir en un paraje tan inhóspito como éste."
    "Si sigues leyendo, sabrás cosas que puedes descubrir fácilmente por ti mismo, simplemente moviéndote por el mapa."
    "En el nivel 0 encuentras la la oficina y el aula."
    "En el nivel -1 está el comedor, la despensa, la cocina, la enfermería, la sala de seguridad y el laboratorio."
    "La zona de emergencia se encuentra aislada por una puerta en el nivel -1, hacia el sur."
    "En el nivel -2 encuentras las salas de ventilación y el ascensor de emergencia."
    "Jason queda atrapado en una vaina viscosa situada en una sala de ventilación."
;
ZIPI_Pista ZIPI_Pista19
with
  ZIPI_titulo "La sala de seguridad",
  ZIPI_pistas
    "¿De qué son esos dos cables que salen de la consola de control?"
    "Transmiten imágenes captadas por cámaras de seguridad."
    "Las cámaras están en la oficina y el laboratorio."
    "La consola de control registra y graba esas imágenes. Las puedes reproducir."
    "Pulsa el botón que pone ~Reproducir~..."
    "... al menos DOS veces."
;
ZIPI_Pista ZIPI_Pista20
with
  ZIPI_titulo "La oficina",
  ZIPI_pistas
    "Examínalo todo."
    "¿Has estado ya en la sala de seguridad?"
    "Si es así, verás que hay un cuadro que oculta algo."
    "Quítalo de la pared."
    "¿Anotaste el código de la caja fuerte cuando viste la grabación de seguridad?"
    "El código es 111582."
;
ZIPI_Pista ZIPI_Pista21
with
  ZIPI_titulo "El aula",
  ZIPI_pistas
    "Ese proyector tiene que servir para algo..."
    "¿Has estado ya en la oficina?"
    "Si es así, tal vez tengas algo que proyectar."
    "Proyecta el holocubo y examina la pantalla."
;
ZIPI_Pista ZIPI_Pista22
with
  ZIPI_titulo "El laboratorio",
  ZIPI_pistas
    "Examínalo todo."
    "¿Has mirado en las estanterías?"
    "En una de ellas hay algo."
    "Es un bisturí láser. Cógelo."
    "La necesitarás para cortar la vaina donde se encuentra atrapado Jason."
;
ZIPI_Pista ZIPI_Pista23
with
  ZIPI_titulo "La enfermería",
  ZIPI_pistas
    "Examínalo todo."
    "¿Has mirado en los armarios?"
    "En concreto: ¿has mirado en los cajones?"
    "En uno de los cajones hay algo."
    "Es una jeringa de adrenalina. Cógela."
    "La necesitarás para reanimar a Jason cuando caiga inconsciente."
;
ZIPI_Pista ZIPI_Pista24
with
  ZIPI_titulo "La despensa, la cocina y el comedor",
  ZIPI_pistas
    "A veces se oyen ruidos raros por esa zona, procedentes de la despensa."
    "Lo mejor es que estés allí el menor tiempo posible."
    "Mejor aún: evita esas tres estancias en todo lo posible."
;
ZIPI_Pista ZIPI_Pista25
with
  ZIPI_titulo "El monstruo - información general",
  ZIPI_pistas
    "El monstruo se mueve libremente y al azar por todo el complejo."
    "Cuando esté a menos de 50 metros de tu situación, el detector de movimiento te lo indicará."
    "Si te lo encuentras... ¡corre!"
    "A veces desaparece para volver a aparecer instantes más tarde en otro sitio."
    "En general, evítalo a toda costa."
;
ZIPI_Pista ZIPI_Pista26
with
  ZIPI_titulo "¿Dónde está Jason?",
  ZIPI_pistas
    "Hay que encontrar a Jason. Aún está vivo."
    "Lo más fácil es seguir el rastro de sangre dejado en el suelo por el monstruo."
    "Si aún no has arreglado el procesador atmosférico, recuerda que la linterna gasta baterías."
    "¿Has perdido el rastro de sangre?"
    "Baja hasta el nivel -2."
    "Dirígete al oeste, y sube a las salas de ventilación."
    "Jason está dentro de la vaina mucosa que está incrustada en un hueco en el techo."
;
ZIPI_Pista ZIPI_Pista27
with
  ZIPI_titulo "¿Cómo lo salvo?",
  ZIPI_pistas
    "¿Ya has encontrado a Jason?"
    "Está dentro de una vaina mucosa, muy dura."
    "Necesitas un instrumento cortante y muy potente para poder cortar la dura vaina."
    "¿Has mirado en el laboratorio?"
    "Está en el nivel -1, por el sureste."
    "Mira en una de las estanterías."
    "Recoge el bisturí láser y abre la vaina con él."
    "Saca a Jason de la vaina."
;
ZIPI_Pista ZIPI_Pista28
with
  ZIPI_titulo "¿Para qué sirven las cámaras de seguridad?",
  ZIPI_pistas
    "Hay dos cámaras de seguridad."
    "Hay una en la oficina y otra en el laboratorio."
    "Observa el cable que sale de la cámara."
    "Si lo sigues, te llevará hasta el otro extremo."
    "A la consola de control, en la sala de seguridad."
;
ZIPI_Pista ZIPI_Pista29
with
  ZIPI_titulo "¿Qué ocurre con los hábitats?",
  ZIPI_pistas
    "Las puertas de los hábitats están cerradas."
    "Y no puedes abrirlas."
    "De hecho, no puedes entrar."
    "No sirven para nada. Sólo están de adorno."
;
ZIPI_Pista ZIPI_Pista30
with
  ZIPI_titulo "¡Corre! ¡Sal del complejo!",
  ZIPI_pistas
    "Intenta salir por la puerta del complejo."
    "¡Vaya! No puedes. El monstruo ha sellado la salida."
    "Habrá que buscar otra forma de salir. Por ahí es imposible."
;
ZIPI_Pista ZIPI_Pista31
with
  ZIPI_titulo "¡Jason cae al suelo inconsciente!",
  ZIPI_pistas
    "Pesa demasiado para moverlo o empujarlo."
    "Y no puedes hablarle: está inconsciente, claro..."
    "Busca algo para reanimarlo..."
    "... alguna sustancia euforizante."
    "Adrenalina."
    "Búscala en la enfermería."
    "En un cajón. Ahí verás una jeringa de adrenalina."
;
ZIPI_Pista ZIPI_Pista32
with
  ZIPI_titulo "Buscando otra salida",
  ZIPI_pistas
    "Está claro que no puedes salir por la entrada principal."
    "Hay otra salida, a la que sólo se accede en casos de emergencia."
    "Es el ascensor de seguridad, situado en el nivel -2 del complejo."
    "Para poder escapar, hay que activar el protocolo de emergencia."
    "Lo que, de paso, hará estallar todo el complejo por los aires."
    "El protocolo de emergencia se activa en la zona de emergencia, en el nivel -1."
    "Pero para entrar necesitas una ~llave~..."
    "... y para activar el protocolo de emergencia, tienes que saber cómo se hace."
    "¿Has estado en la oficina? ¿Y en el aula?"
    "¿Has visto las grabaciones de seguridad?"
;
ZIPI_Pista ZIPI_Pista33
with
  ZIPI_titulo "¿Cómo abro la puerta que está al sur del nivel -1?",
  ZIPI_pistas
    "No puedes abrirla directamente. Antes hay que desbloquearla."
    "¿Llevas algo que entre en la ranura?"
    "¿Has estado ya en la oficina?"
    "Si es así, tal vez tengas algo que entre."
    "Inserta en la ranura la tarjeta que encontraste en la caja fuerte."
;
ZIPI_Pista ZIPI_Pista34
with
  ZIPI_titulo "¿A dónde da la puerta?",
  ZIPI_pistas
    "Debe ser un lugar restringido."
    "Un lugar para casos excepcionales."
    "La zona de emergencia."
;
ZIPI_Pista ZIPI_Pista35
with
  ZIPI_titulo "¿Qué hago dentro de la zona de emergencia?",
  ZIPI_pistas
    "Activar el protocolo de emergencia."
    "Eso hará que todo explote dentro de 10 minutos."
    "Pero también te abrirá una salida."
    "La salida está en el nivel -2."
    "Es el ascensor de emergencia."
;
ZIPI_Pista ZIPI_Pista36
with
  ZIPI_titulo "¿Cómo activo el protocolo de emergencia?",
  ZIPI_pistas
    "¿Has visualizado el holocubo?"
    "Si no, encuéntralo primero..."
    "Entra con Jason y cierra la puerta, pero asegúrate de que el monstruo no está dentro con vosotros."
    "Deja a Jason en la sala este de emergencia."
    "¿Sabes cómo?: ~JASON, QUEDATE AQUI~."
    "Dirígete a la sala oeste de emergencia."
    "Dile a Jason que pulse el botón, e inmediatamente después pulsa tú el que tienes delante.   "
;
ZIPI_Pista ZIPI_Pista37
with
  ZIPI_titulo "¿Cómo puedo acceder al ascensor de emergencia?",
  ZIPI_pistas
    "El ascensor sólo se abre en caso de emergencia, lógicamente."
    "Tienes que activar el protocolo de emergencia."
;
ZIPI_Pista ZIPI_Pista38
with
  ZIPI_titulo "¿Cómo salimos de aquí?",
  ZIPI_pistas
    "¿Has activado el protocolo de emergencia?"
    "Dirígete al ascensor de emergencia."
    "Está en el nivel -2, al oeste del montacargas."
    "Entra en el ascensor, ahora que está abierto."
;
ZIPI_Pista ZIPI_Pista39
with
  ZIPI_titulo "El final",
  ZIPI_pistas
    "¿Has podido escapar vivo del complejo?"
    "¿Y llevas a Jason contigo?"
    "Entonces aún estás a tiempo de escapar..."
    "... ¡pero no hay un minuto que perder!"
    "Entrad en la nave... y rezad lo que sepáis."
;
ZIPI_Otro ZIPI_Otro0
with
  ZIPI_titulo "¿Cómo funciona este sistema de pistas?",
  ZIPI_ejecutar [;
       print "^- Te puedes desplazar por los menús usando las flechas del cursor arriba y abajo. ";
       print "^- Para seleccionar una opción del menú, puedes pulsar las teclas ~Entrar~ o ~P~. ";
       print "^- Para volver al menú anterior, o salir del sistema de pistas, pulsa ~Q~. ";
       print "^- Cuando estés leyendo pistas, pulsa ~P~ para ver la pista siguiente (si es que ";
       print "^  hay más), o pulsa ~Q~ para retroceder a la pantalla anterior. ";
  ];
ZIPI_Otro ZIPI_Otro1
with
  ZIPI_titulo "Acciones y órdenes",
  ZIPI_ejecutar [;
       print "^A·L·I·E·N es una aventura conversacional que te sumerge en un mundo de terror y ";
       print "^ciencia-ficción donde tú eres el protagonista y con el que podrás interactuar ";
       print "^introduciendo órdenes con el teclado. ";
       print "^^";
       print "Dichas órdenes tienen una sintaxis típica de «VERBO» o «VERBO NOMBRE», aunque ";
       print "^pueden construirse órdenes mucho más complejas si fuese necesario. ";
       print "^^";
       print "Algunos ejemplos: ";
       print "^^";
       print "> COGE LA CAJA DE HERRAMIENTAS ";
       print "^> ABRE EL ARMARIO ";
       print "^> COGE EL TRAJE ROJO Y PONTELO ";
       print "^> SACA TODO DE DENTRO DEL ARMARIO ";
       print "^^";
       print "Los verbos se pueden escribir en imperativo («COGE») o infinitivo («COGER»), si bien ";
       print "^se recomienda la primera opción, más que nada porque resulta más corta. Y los ";
       print "^artículos («EL», «LA») se pueden poner, aunque no son necesarios. ";
  ];
ZIPI_Otro ZIPI_Otro2
with
  ZIPI_titulo "Algunas acciones frecuentes",
  ZIPI_ejecutar [;
       print "^Las siguientes son algunas de las acciones que se utilizan de manera más frecuente en ";
       print "^una aventura conversacional: ";
       print "^^";
       print "COGE tal . . . .: Coger el objeto 'tal'. ";
       print "^DEJA tal . . . .: Dejar el objeto 'tal'. ";
       print "^ABRE tal . . . .: Abrir 'tal' (normalmente una puerta o algún recipiente cerrado). ";
       print "^CIERRA tal . . .: Cerrar 'tal' (normalmente una puerta o algún recipiente abierto). ";
       print "^METE tal EN cual: Meter el objeto 'tal' dentro de 'cual' (por ejemplo, una caja). ";
       print "^SACA tal DE cual: Sacar el objeto 'tal' de dentro de 'cual' (por ejemplo, una caja). ";
       print "^PONTE tal . . . : Ponerse el objeto 'tal' (normalmente una prenda de ropa). ";
       print "^QUITATE tal . . : Quitarse el objeto 'tal' (normalmente una prenda de ropa). ";
       print "^ENTRA . . . . . : Entrar dentro de algún sitio, posiblemente a través de una puerta. ";
       print "^SAL . . . . . . : Salir de algún sitio, posiblemente a través de una puerta. ";
       print "^EXAMINA tal (o ";
       print "^EX tal o X tal) : Describir el objeto 'tal' con detalle. ";
       print "^INVENTARIO (o I): Mostrar un listado con los objetos que posees actualmente. ";
  ];
ZIPI_Otro ZIPI_Otro3
with
  ZIPI_titulo "Moverse por el mundo",
  ZIPI_ejecutar [;
       print "^El mundo de A·L·I·E·N está compuesto por multitud de recintos interconectados entre ";
       print "^sí llamados localidades. Las salidas desde tu localidad actual se muestran siempre ";
       print "^a continuación de la descripción de dicha localidad. Para moverte de una localidad ";
       print "^a otra, simplemente teclea la salida correspondiente. ";
       print "^^";
       print "Por ejemplo: supongamos que tu localidad actual tiene como salidas «norte» y ";
       print "^«afuera». En ese caso, para moverte hacia la localidad situada al norte de la ";
       print "^actual, puedes teclear las órdenes NORTE, VETE AL NORTE, IR AL NORTE o simplemente ";
       print "^N. Y para salir fuera, puedes teclear SAL, SALIR o FUERA. Los puntos cardinales se ";
       print "^pueden abreviar a N, S, E, O, NE, SE, NO y SO. ";
  ];
ZIPI_Otro ZIPI_Otro4
with
  ZIPI_titulo "Otros personajes del juego",
  ZIPI_ejecutar [;
       print "^A veces, será necesario enviar órdenes a algún personaje (por ejemplo, al Mayor ";
       print "^Jason). En tal caso, deberás indicar el nombre del personaje seguido de una coma, ";
       print "^y a continuación la orden que deseas enviarle: ";
       print "^^";
       print "> JASON, COGE TU TRAJE ";
       print "^> JASON, SIGUEME ";
       print "^^";
       print "Para hablar con un personaje, o bien preguntarle algo, se usa la misma sintaxis: ";
       print "^^";
       print "> JASON, HABLAME DE TI ";
       print "^> JASON, QUE OPINAS SOBRE EL PLANETA ";
       print "^^";
       print "Saber trabajar conjuntamente con los personajes es crucial para alcanzar el éxito ";
       print "^en esta aventura. ";
  ];
ZIPI_Otro ZIPI_Otro5
with
  ZIPI_titulo "Algunos comandos útiles",
  ZIPI_ejecutar [;
       print "^SONIDO SI/NO . . . . : Activar o desactivar todos los efectos sonoros. ";
       print "^SONIDO FONDO SI/NO . : Activar o desactivar el sonido de fondo. ";
       print "^SONIDO DETECTOR SI/NO: Activar o desactivar el sonido del detector de movimiento. ";
       print "^GRAFICOS SI/NO . . . : Activar o desactivar la visualización de gráficos. ";
       print "^GRAFICOS PEQUEÑOS/ ";
       print "^  MEDIANOS/GRANDES . : Cambia el tamaño de la ventana de gráficos (por omisión ";
       print "^                       se mostrarán en tamaño MEDIANO). ";
       print "^CONFIGURACION . . . .: Muestra un menú de opciones de gráficos y sonido. ";
       print "^SALIDAS (o X) . . . .: Mostrar las salidas visibles en la localidad actual. ";
       print "^SALIDAS SI/NO . . . .: Mostrar (o no) automáticamente las salidas visibles en ";
       print "^                       cada localidad. ";
       print "^SAVE (o GUARDAR) . . : Almacenar la situación actual en un archivo externo, para ";
       print "^                       poder volver a él en cualquier momento. ";
       print "^LOAD (o RECUPERAR) . : Recuperar una situación previamente guardada con SAVE o ";
       print "^                       GUARDAR. ";
       print "^AYUDA . . . . . . . .: Por si alguna vez te encuentras atascado. ";
       print "^REINICIAR . . . . . .: Volver a empezar desde el principio. ";
       print "^ACABAR (o FIN) . . . : Salir de la aventura (cuidado: no guarda la situación actual). ";
  ];
ZIPI_Otro ZIPI_Otro6
with
  ZIPI_titulo "Consejos y ayudas",
  ZIPI_ejecutar [;
       print "^- Examina todo lo que encuentres. Varias veces si hace falta. ";
       print "^- Recoge todos los objetos que puedas; podrían serte de utilidad. ";
       print "^- Habla con los demás personajes de la aventura. A veces te darán pistas útiles. ";
       print "^- El azar es parte de esta aventura. Tenlo en cuenta a la hora de llevar a cabo ";
       print "^  determinadas acciones. ";
       print "^- Graba frecuentemente tu situación con la orden GUARDAR. Nunca se sabe lo que ";
       print "^  puedes encontrarte tras esa esquina... ";
       print "^- Si te encuentras con algún fallo o no sabes cómo avanzar, puedes plantear tus ";
       print "^  dudas en el foro del CAAD o en alpha.aventuras@@64gmail.com. ";
  ];
ZIPI_Otro ZIPI_Otro7
with
  ZIPI_titulo "Al jugar la aventura, las letras se ven feas o con colores extraños",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "   a) [Si usas otro sistema que no sea Windows] Asegúrate de tener instalada^";
       print "      la última versión de Gargoyle (al menos, la 2011.1). Los usuarios de^";
       print "      Windows que instalen la aventura con el programa de instalación no^";
       print "      necesitan comprobar esto, ya que Gargoyle se instala con la aventura.^";
       print "^";
       print "   b) Asegúrate de que exista el archivo 'garglk.ini' en la misma carpeta que^";
       print "      la aventura. Para ello:^";
       print "^";
       print "       i. Si usas Linux, y has instalado la aventura usando el paquete .deb,^";
       print "          comprueba si existe el archivo en esta ruta:^";
       print "^";
       print "            /usr/share/games/alphaaventuras-alien-ee/garglk.ini^";
       print "^";
       print "      ii. Si estas usando la versión multiplataforma, comprueba simplemente^";
       print "          que el archivo 'garglk.ini' se encuentra en la misma carpeta que la^";
       print "          aventura 'alien.blb', junto al resto de los archivos incluidos.^";
       print "^";
       print "   Si todo lo anterior no funciona, instala de nuevo la aventura.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro8
with
  ZIPI_titulo "Las letras se ven demasiado grandes o demasiado pequeñas",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Puedes cambiar el tamaño de las letras editando el archivo 'garglk.ini':^";
       print "^";
       print "  a) En Windows estará en la ruta:^";
       print "     @@92Program Files@@92Juegos Conversacionales@@92ALIEN - La aventura - Edición Especial@@92^";
       print "^";
       print "  b) En Linux, si instalaste la aventura con el paquete .deb, estará en:^";
       print "     /usr/share/games/alphaaventuras-alien-ee/^";
       print "^";
       print "  c) En la versión multiplataforma lo encontrarás en la misma ruta que el resto^";
       print "     de los archivos distribuidos con la aventura.^";
       print "^";
       print "  Cuando hayas abierto el archivo 'garglk.ini' con tu editor de textos favorito,^";
       print "  localiza las líneas que empiecen por 'monosize' y 'propsize'. Para ajustar el^";
       print "  tamaño de las letras, simplemente cambia los números que aparezcan al lado.^";
       print "  Poniendo números mayores, las letras se verán más grandes, y viceversa. Asegúrate^";
       print "  de que el 'propsize' sea siempre un poco mayor que el 'monosize'.^";
       print "^";
       print "  Guarda los cambios en el mismo archivo y ejecuta de nuevo la aventura.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro9
with
  ZIPI_titulo "Los gráficos se ven demasiado grandes y es incómodo jugar así",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "   a) Amplía el tamaño de la ventana del juego, maximizándola hasta ocupar^";
       print "      todo el escritorio.^";
       print "^";
       print "   b) Configura la aventura para que use gráficos más pequeños, usando el^";
       print "      comando siguiente dentro del juego:^";
       print "^";
       print "      > CONFIGURACIÓN^";
       print "      ^";
       print "      Una vez dentro, cambia el tamaño de los gráficos a uno pequeño (entre^";
       print "      200 y 350 píxeles puede resultar más adecuado para tu pantalla).^";
       print "^";
       print "   c) Si lo anterior no fuera suficiente, siempre puedes desactivar los gráficos^";
       print "      completamente, aunque no te lo recomendamos, ya que con ello perderías^";
       print "      gran parte del atractivo de la aventura. Para ello, ejecuta el comando^";
       print "      siguiente dentro del juego:^";
       print "^";
       print "      > GRÁFICOS NO^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro10
with
  ZIPI_titulo "Los gráficos se ven demasiado pequeños",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Prueba lo siguiente:^";
       print "^";
       print "   a) Amplía el tamaño de la ventana del juego, maximizándola hasta ocupar^";
       print "      todo el escritorio. Si la ventana es demasiado pequeña, los gráficos^";
       print "      se reescalarán automáticamente para que quepan completos dentro de la^";
       print "      misma, pero se verán muy pequeños.^";
       print "^";
       print "   b) Configura la aventura para que use gráficos más grandes, usando uno de^";
       print "      los comandos siguientes dentro del juego:^";
       print "^";
       print "      > GRÁFICOS MEDIANOS^";
       print "          (esto hará que la aventura use los gráficos a tamaño mediano)^";
       print "^";
       print "      > GRÁFICOS GRANDES^";
       print "          (esto hará que la aventura use los gráficos al tamaño más grande)^";
       print "^";
       print "      > CONFIGURACIÓN^";
       print "          (mostrará un menú donde podrás cambiar el tamaño con más detalle)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro11
with
  ZIPI_titulo "¡No veo gráficos en ningún momento!",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Comprueba lo siguiente:^";
       print "^";
       print "   a) Asegúrate de tener activados los gráficos dentro del juego. Para ello,^";
       print "      usa el comando siguiente dentro del juego:^";
       print "^";
       print "      > GRÁFICOS SI^";
       print "^";
       print "      Ten en cuenta también que los gráficos se apagan automáticamente en^";
       print "      ciertas partes de la aventura, para que el texto ocupe toda la ventana^";
       print "      de juego.^";
       print "^";
       print "   b) Asegúrate de que no estás en un lugar a oscuras y sin ninguna fuente de^";
       print "      luz, como una linterna encendida.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro12
with
  ZIPI_titulo "¡No oigo nada!",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Si no oyes música ni sonidos durante el juego, comprueba lo siguiente:^";
       print "^";
       print "   a) Asegúrate de tener activados los sonidos dentro del juego. Para ello,^";
       print "      usa el comando siguiente dentro del juego:^";
       print "^";
       print "      > SONIDO SI^";
       print "^";
       print "   b) Si no oyes el sonido de fondo, asegúrate de tenerlo activado usando el^";
       print "      comando siguiente:^";
       print "^";
       print "      > SONIDO FONDO SI^";
       print "^";
       print "   c) Si no oyes el sonido del detector de movimiento, asegúrate de tenerlo^";
       print "      activado usando el comando siguiente:^";
       print "^";
       print "      > SONIDO DETECTOR SI^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro13
with
  ZIPI_titulo "Estoy atascado y no sé cómo continuar",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Si andas perdido y no sabes cómo resolver algún puzzle o situación:^";
       print "^";
       print "   a) Usa el sistema de pistas interactivas, tecleando:^";
       print "^";
       print "        > PISTAS^";
       print "^";
       print "      en cualquier momento del juego.^";
       print "^";
       print "   b) Pregunta en el foro del CAAD, en la siguiente dirección:^";
       print "^";
       print "        http://foro.caad.es^";
       print "^";
       print "   c) Contacta con nosotros por alguna de las las estas vías:^";
       print "^";
       print "      - email: alpha.aventuras@@64gmail.com^";
       print "      - web: http://sites.google.com/site/alphaaventuras^";
       print "      - facebook: https://www.facebook.com/alphaaventuras^";
       print "      - wikiCAAD: http://wiki.caad.es/Alpha_Aventuras^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro14
with
  ZIPI_titulo "Créditos",
  ZIPI_ejecutar [;
       print "A·L·I·E·N: LA AVENTURA - EDICIÓN ESPECIAL (c) 2008-2012 Alpha Aventuras^ ";
       print "^- PROGRAMACIÓN Y DISEÑO: ";
       print "^     Ricardo Pérez López ";
       print "^- GRÁFICOS E IDEA ORIGINAL: ";
       print "^     Manuel Millán Ruiz ";
       print "^- TEXTOS: ";
       print "^     Ricardo Pérez López ";
       print "^     Francisco J. Roldán Domínguez ";
       print "^     Manuel I. Monge García ";
       print "^- MAPEADO Y DOCUMENTACIÓN: ";
       print "^     Francisco J. Roldán Domínguez ";
       print "^     Antonio Matiola Ortiz ";
       print "^- PRUEBAS: ";
       print "^     Ricardo Pérez López ";
       print "^     Manuel Millán Ruiz ";
       print "^     Francisco Picazo Millán ";
       print "^     Manuel I. Monge García^ ";
       print "^  Para más información, usa el comando CRÉDITOS durante el juego. ";
  ];
ZIPI_Otro ZIPI_Otro15
with
  ZIPI_titulo "¡Cuidado!",
  ZIPI_ejecutar [;
       print "^Si sigues adelante, sabrás qué estancias tiene el complejo. Te recomendamos que ";
       print "^intentes descubrirlo por ti mismo, moviéndote por su interior, pero si aún así ";
       print "^quieres continuar con las pistas, entra en la siguiente opción del menú. ";
  ];
ZIPI_Otro ZIPI_Otro16
with
  ZIPI_titulo "La nave",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "        +------+  +------+^";
       print "        | POPA |--| PROA | (localidad de inicio)^";
       print "        +------+  +------+^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro17
with
  ZIPI_titulo "El exterior",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "              +----------+^";
       print "              | EXTERIOR | -> (puerta al procesador atmosférico)^";
       print "              +----------+^";
       print "                    |        ^";
       print "                    |^";
       print "              +----------+^";
       print " (puerta a <- | EXTERIOR |^";
       print "  la nave)    +----------+^";
       print "                    |^";
       print "                    |^";
       print "              +----------+  +----------+^";
       print "              | EXTERIOR |--| EXTERIOR | -> (puerta al complejo)^";
       print "              +----------+  +----------+^";
       print "                 (robot)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro18
with
  ZIPI_titulo "Nivel 0",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "                               +---------+^";
       print "                               | ENTRADA |^";
       print "                               +---------+^";
       print "                                    |^";
       print "                   +--------+  +---------+  +--------+  +-------+^";
       print "                   | TÚNEL  |--| BALCÓN  |--| TÚNEL  |--| AULA  |^";
       print "                   +--------+  +---------+  +--------+  +-------+^";
       print "                        |                        |          |^";
       print "      +---------+  +--------+               +--------+  +-------+^";
       print "      | OFICINA |--| BALCÓN |               | BALCÓN |--| TÚNEL |^";
       print "      +---------+  +--------+               +--------+  +-------+^";
       print "                        |                        |^";
       print "                   +--------+  +---------+  +--------+^";
       print "                   | TÚNEL  |--| BALCÓN  |--| TÚNEL  |^";
       print "                   +--------+  +---------+  +--------+^";
       print "                                    v  (abajo al nivel -1)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro19
with
  ZIPI_titulo "Nivel -1",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "            +-----------+  +----------+  +--------+^";
       print "            |  COMEDOR  |--| DESPENSA |--| COCINA |^";
       print "            +-----------+  +----------+  +--------+^";
       print "                  |                          |^";
       print "            +-----------+                +--------+  +------------+^";
       print "            |  BALCÓN   |                | BALCÓN |--| ENFERMERÍA |^";
       print "            +-----------+                +--------+  +------------+^";
       print "                  |          /@@92               |             |^";
       print "            +-----------+  +----------+  +--------+     +-------+^";
       print "            |   TÚNEL   |--|  BALCÓN* |--| TÚNEL  |-----| TÚNEL |^";
       print "            +-----------+  +----------+  +--------+     +-------+^";
       print "                  |             |  v         |^";
       print "            +-----------+       |      +-------------+   * (sube al nivel 0 o^";
       print "            |  SALA DE  |       |      | LABORATORIO |      baja al nivel -2)^";
       print "            | SEGURIDAD |       |      +-------------+^";
       print "            +-----------+       v ^";
       print "      +---------------+  +------------+  +---------------+^";
       print "      |  SALA OESTE   |--| PASILLO DE |--|   SALA ESTE   |^";
       print "      | DE EMERGENCIA |  | EMERGENCIA |  | DE EMERGENCIA |^";
       print "      +---------------+  +------------+  +---------------+^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro20
with
  ZIPI_titulo "Nivel -2",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "                             +-------------+   +-------------+^";
       print "                             |   SALA DE   |   |   SALA DE   | (vaina en^";
       print "                             | VENTILACIÓN |---| VENTILACIÓN |  hueco del^";
       print "                             |    OESTE    |   |    ESTE     |  techo)^";
       print "         (sube al nivel -1)  +-------------+   +-------------+^";
       print "                      /@@92           /@@92 ^";
       print "  +-----------+  +----------+  +--------+^";
       print "  |   TÚNEL   |--|  BALCÓN  |--| TÚNEL  |^";
       print "  +-----------+  +----------+  +--------+^";
       print "  (ascensor de^";
       print "   emergencia)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro21
with
  ZIPI_titulo "En la nave",
  ZIPI_ejecutar [;
       print "^Vete al oeste y abre el armario. Coge todo lo que puedas y dirígete de nuevo al este. ";
       print "^Dile a Madre que abra el compartimento de trajes. Coge tu traje y póntelo. Dile a ";
       print "^Jason que haga lo mismo. Dile a Madre que abra la compuerta exterior, y salid los dos.^ ";
       print "^Por cierto: la palanca no sirve para nada durante el juego... ";
  ];
ZIPI_Otro ZIPI_Otro22
with
  ZIPI_titulo "En el exterior",
  ZIPI_ejecutar [;
       print "^Vete al norte, abre la linterna, saca la batería de la linterna y colócala en el ";
       print "^panel de control. El panel se enciende y te dice que la semilla es 9957. Si tecleas ";
       print "^el código de acceso que te da el robot (es decir, 759812), verás que ya no es válido. ";
       print "^Indica a Madre el valor de la semilla (~MADRE, LA SEMILLA ES 9957~) y te calculará ";
       print "^el nuevo código, que resulta ser 268741. Teclea ese código en el panel de control. ";
       print "^Recoge la batería. Vuelve al sur. Pide a Madre que abra la compuerta de la nave. ";
       print "^Entra en la nave. Mete la batería en el cargador de baterías. Cógela de nuevo y ";
       print "^métela en la linterna. Haz que Madre abra de nuevo la puerta, y sal otra vez al ";
       print "^exterior. Vete al norte, de nuevo a la entrada del procesador atmosférico. Enciende ";
       print "^la linterna y entra. ";
  ];
ZIPI_Otro ZIPI_Otro23
with
  ZIPI_titulo "El procesador atmosférico",
  ZIPI_ejecutar [;
       print "^El monstruo se llevará a Jason. Recoge su rifle y sal. Vete al sur, y de nuevo al ";
       print "^sur. Empuja al robot al norte, de nuevo al norte, y finalmente adentro. En la ";
       print "^unidad central hay una caja de conexiones. Ábrela con el destornillador. Dentro hay ";
       print "^un circuito roto. Dile al robot que lo suelde. Ya está arreglado el procesador ";
       print "^atmosférico, por lo que ya no necesitarás el traje ni la linterna. Sal de la sala, ";
       print "^sur, sur, este y entra por la puerta del complejo. ";
  ];
ZIPI_Otro ZIPI_Otro24
with
  ZIPI_titulo "El monstruo",
  ZIPI_ejecutar [;
       print "^El monstruo se va moviendo aleatoriamente por el complejo. Tienes que evitarlo. Si te ";
       print "^lo encuentras, sal corriendo de esa habitación, o empezará a seguirte. Si te sigue, ";
       print "^no dejes de moverte (no hagas otra cosa en tu turno, o te matará). El detector de ";
       print "^movimiento te advertirá de su presencia, así que no te debe resultar difícil ";
       print "^esquivarlo. No intentes dispararle, o luchar con él. Tan sólo evítalo. ";
  ];
ZIPI_Otro ZIPI_Otro25
with
  ZIPI_titulo "Rescatando a Jason",
  ZIPI_ejecutar [;
       print "^Si sigues el rastro de sangre en el suelo llegarás hasta Jason, que se encuentra ";
       print "^atrapado en una vaina viscosa. Pero para ganar tiempo, vamos a ir antes al ";
       print "^laboratorio. Sur, este, sur, sur, oeste, abajo, este y sur. En el laboratorio, ";
       print "^examina las estanterías y coge el bisturí láser. Ahora ve a la enfermería a recoger ";
       print "^la jeringa de adrenalina (luego la necesitarás). Norte, norte y este. En la ";
       print "^enfermería, examina todos los cajones, abre el cajón y saca la jeringa. Oeste, sur, ";
       print "^oeste, abajo, este, arriba y este. Llegas a la sala este de ventilación. En un hueco ";
       print "^abierto en el techo la vaina viscosa donde se encuentra Jason. Corta la vaina con el ";
       print "^bisturí láser y saca a Jason. En unos 7 u 8 turnos, Jason caerá al suelo ";
       print "^inconsciente. En ese momento, clávale la inyección de adrenalina y se recuperará. ";
  ];
ZIPI_Otro ZIPI_Otro26
with
  ZIPI_titulo "Investigando",
  ZIPI_ejecutar [;
       print "^Si ahora intentaras salir por la puerta del complejo, comprobarías que el monstruo la ";
       print "^ha sellado, así que tienes que buscar otra salida. Desde la sala donde encontraste a ";
       print "^Jason, vete al oeste, abajo, oeste, arriba, oeste y sur. Llegarás a la sala de ";
       print "^seguridad. Allí verás una consola de control con una pantalla y un teclado. Si pulsas ";
       print "^el botón ~Reproducir~ verás las grabaciones de las cámaras de seguridad de la oficina ";
       print "^y el laboratorio. Descubrirás que, en la oficina, hay una caja fuerte detrás de un ";
       print "^cuadro. La combinación es 111582. En la grabación de seguridad del laboratorio ";
       print "^comprobarás que el monstruo era un espécimen en estudio que luego escapó, sembrando ";
       print "^caos y muerte. Hay que hacer estallar todo esto. ";
  ];
ZIPI_Otro ZIPI_Otro27
with
  ZIPI_titulo "El contenido de la caja fuerte",
  ZIPI_ejecutar [;
       print "^Desde la sala de seguridad, si seguimos los cables llegarás a la oficina y al ";
       print "^laboratorio. Ahora sólo nos interesa la oficina, así que vete al norte, este, ";
       print "^arriba, oeste, norte y oeste. Ya en la oficina, quita el cuadro y verás la caja ";
       print "^fuerte. Teclea la combinación 111582 y abre la caja fuerte, donde encontrarás una ";
       print "^tarjeta y un holocubo. Recoge ambas cosas y dirígete al aula, donde proyectarás ";
       print "^el interior del holocubo. Este, norte, este, este y este, y estarás en el aula. ";
       print "^Coloca el holocubo en el proyector, enciéndelo y examina la pantalla. Así ";
       print "^aprenderás cómo activar el protocolo de emergencia. ¡Cuidado! En ese momento, el ";
       print "^monstruo irá a ti (por aquello de darle emoción a la cosa), así que tendrás que ";
       print "^ser rápido. Otra cosa que puedes hacer es, sencillamente, no examinar la pantalla ";
       print "^(toda la información que necesitas está aquí). ";
  ];
ZIPI_Otro ZIPI_Otro28
with
  ZIPI_titulo "La zona de emergencia",
  ZIPI_ejecutar [;
       print "^Desde el aula vete al oeste, sur, sur, oeste y abajo. Mete la tarjeta en la ranura y ";
       print "^entra por la puerta. Estarás en el pasillo de emergencia. Cierra la puerta por ";
       print "^dentro, pero antes comprueba que Jason está contigo y que el monstruo se queda fuera. ";
       print "^Vete al este y dile a Jason que se quede allí. Vete al oeste y de nuevo al oeste. ";
       print "^Así, estaréis cada uno en una sala de emergencia y delante de un botón. Dile a Jason ";
       print "^que pulse el botón, e inmediatamente después pulsa tú el que tienes delante. Se ";
       print "^activará la autodestrucción. Tienes diez minutos para escapar (hay tiempo de sobra si ";
       print "^no te demoras). ";
  ];
ZIPI_Otro ZIPI_Otro29
with
  ZIPI_titulo "La huida final",
  ZIPI_ejecutar [;
       print "^Dile a Jason que te siga para que te dé el encuentro. Este, abre la puerta y sal. ";
       print "^Baja y vete al oeste. Allí estará el ascensor de emergencia. Estará abierto porque ";
       print "^hemos activado la autodestrucción. Entra en el ascensor (asegúrate de que Jason está ";
       print "^contigo, y siguiéndote) y lograrás salir (por los pelos) del complejo. Saldréis al ";
       print "^exterior, en la localidad donde encontraste al robot al comienzo de la aventura. ";
       print "^Norte, pide a Madre que abra la compuerta de la nave, y entra. Y prepárate... ";
       print "^^";
       print "******** FIN ******** ";
       print "^^";
  ];


[ ZIPI_Intro;
  print "Desplázate con las flechas del cursor. Pulsa ", (s_in) "Enter", " para seleccionar, ", (s_in) "P", " para continuar, o ", (s_in) "Q", " para salir.";
];


[ ZIPI_Empezar ;
!  ZIPI_InitGlk();
  clearMainWindow();
  ZIPI_Intro();
!  barra_estado.numero_lineas = 26;
!  barra_estado.dibujar();
  ZIPI_RunMenu(ZIPI_Menu0, true);
!  barra_estado.numero_lineas = 1;
!  barra_estado.dibujar();
];
