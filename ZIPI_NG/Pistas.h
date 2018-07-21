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
  ZIPI_titulo "Informaci�n general - Lee esto primero",
  ZIPI_item
    ZIPI_Otro0
    ZIPI_Otro1
    ZIPI_Otro2
    ZIPI_Otro3
    ZIPI_Otro4
    ZIPI_Otro5
    ZIPI_Otro6
    ZIPI_Menu2
    ZIPI_Otro16
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
    ZIPI_Otro14
    ZIPI_Otro15
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
  ZIPI_titulo "�C�mo entro en el procesador atmosf�rico?",
  ZIPI_item
    ZIPI_Pista7
    ZIPI_Pista8
    ZIPI_Menu6
;
ZIPI_Menu ZIPI_Menu6
with
  ZIPI_titulo "�Y ahora?       ",
  ZIPI_item
    ZIPI_Pista9
    ZIPI_Pista10
;
ZIPI_Menu ZIPI_Menu7
with
  ZIPI_titulo "En el procesador atmosf�rico",
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
  ZIPI_titulo "Estancias del complejo - informaci�n general",
  ZIPI_item
    ZIPI_Pista18
    ZIPI_Menu10
;
ZIPI_Menu ZIPI_Menu10
with
  ZIPI_titulo "Zonas del complejo",
  ZIPI_item
    ZIPI_Otro17
    ZIPI_Menu11
;
ZIPI_Menu ZIPI_Menu11
with
  ZIPI_titulo "Zonas del complejo (�has le�do la advertencia anterior?)",
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
  ZIPI_titulo "�A por Jason!",
  ZIPI_item
    ZIPI_Pista26
    ZIPI_Pista27
;
ZIPI_Menu ZIPI_Menu13
with
  ZIPI_titulo "�Y ahora, qu�?",
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
  ZIPI_titulo "�Qu� hago dentro?",
  ZIPI_item
    ZIPI_Pista35
    ZIPI_Pista36
;
ZIPI_Menu ZIPI_Menu16
with
  ZIPI_titulo "�Nos vamos!",
  ZIPI_item
    ZIPI_Pista38
;
ZIPI_Menu ZIPI_Menu17
with
  ZIPI_titulo "Informaci�n adicional (mapas y soluci�n)",
  ZIPI_item
    ZIPI_Menu18
    ZIPI_Separador
    ZIPI_Menu20
;
ZIPI_Menu ZIPI_Menu18
with
  ZIPI_titulo "Mapas (s�lo para casos de extrema necesidad)",
  ZIPI_item
    ZIPI_Otro18
    ZIPI_Otro19
    ZIPI_Menu19
;
ZIPI_Menu ZIPI_Menu19
with
  ZIPI_titulo "El complejo",
  ZIPI_item
    ZIPI_Otro20
    ZIPI_Otro21
    ZIPI_Otro22
;
ZIPI_Menu ZIPI_Menu20
with
  ZIPI_titulo "Soluci�n (prohibido leer esto)",
  ZIPI_item
    ZIPI_Otro23
    ZIPI_Otro24
    ZIPI_Otro25
    ZIPI_Menu21
;
ZIPI_Menu ZIPI_Menu21
with
  ZIPI_titulo "El complejo",
  ZIPI_item
    ZIPI_Otro26
    ZIPI_Otro27
    ZIPI_Otro28
    ZIPI_Otro29
    ZIPI_Otro30
    ZIPI_Otro31
;
ZIPI_Pista ZIPI_Pista0
with
  ZIPI_titulo "�Qu� tengo que hacer en la nave?",
  ZIPI_pistas
    "Examina todo lo que te rodea (eso siempre)."
    "Pero, b�sicamente, lo que tienes que hacer es salir al exterior."
    "Para salir, tienes que abrir la compuerta de la nave..."
    "... pero no puedes hacerlo manualmente."
    "Pide a la computadora que lo haga por ti."
    "~MADRE, ABRE LA COMPUERTA~."
    "Aunque sin ox�geno en el exterior, no podr�s salir hasta que te hayas puesto el traje atmosf�rico."
;
ZIPI_Pista ZIPI_Pista1
with
  ZIPI_titulo "�Por qu� tengo que usar los trajes atmosf�ricos?",
  ZIPI_pistas
    "Cuando lleg�is al planeta, la atm�sfera es irrespirable debido a un fallo en el procesador atmosf�rico."
    "El procesador atmosf�rico es un edificio en el que se procesa la atm�sfera del planeta para producir ox�geno respirable."
    "�Es posible respirar en el exterior sin necesidad de trajes? La respuesta es que..."
    "... S�, pero para ello tendr�s que arreglar primero el procesador atmosf�rico."
;
ZIPI_Pista ZIPI_Pista2
with
  ZIPI_titulo "�C�mo consigo los trajes atmosf�ricos?",
  ZIPI_pistas
    "Tendr�s que abrir el compartimento de los trajes."
    "�No puedes abrirlo manualmente? Pide a Madre que lo haga por ti."
    "~MADRE, ABRE EL COMPARTIMENTO~."
;
ZIPI_Pista ZIPI_Pista3
with
  ZIPI_titulo "�C�mo consigo que Jason salga de la nave?",
  ZIPI_pistas
    "Jason s�lo saldr� de la nave si lleva puesto su traje atmosf�rico."
    "P�dele que se lo ponga..."
    "... o simplemente d�jalo a su alcance. �l se lo pondr�."
    "Para ello, tal vez necesites abrir previamente el compartimento para trajes."
    "~JASON, COGE TU TRAJE~ o ~JASON, PONTE TU TRAJE~."
;
ZIPI_Pista ZIPI_Pista4
with
  ZIPI_titulo "�Hay algo m�s que pueda hacer en la nave?",
  ZIPI_pistas
    "�La has recorrido completamente?"
    "�Has visitado la popa de la nave?"
    "Dir�gete al OESTE desde la localidad de inicio."
    "�Ves algo interesante?"
    "�Qu� habr� en ese armario?"
    "�Y en esa caja?"
    "Rec�gelo todo. Te puede ser de utilidad en el futuro."
;
ZIPI_Pista ZIPI_Pista5
with
  ZIPI_titulo "�Es normal que Jason se quede en la nave?",
  ZIPI_pistas
    "Jason se quedar� en la nave si no lleva puesto su traje atmosf�rico."
    "Puedes continuar explorando sin �l."
    "En ese caso, podr�is comunicaros como si estuvi�riais juntos, gracias al transmisor que llevas en tu o�do."
    "�Es recomendable moverte sin tener a Jason a tu lado? Pues..."
    "... francamente, NO."
    "Haz que Jason se ponga su traje y que salga contigo."
;
ZIPI_Pista ZIPI_Pista6
with
  ZIPI_titulo "�C�mo entro en el complejo minero?",
  ZIPI_pistas
    "La puerta es imposible de abrir manualmente."
    "Y no hay ning�n tipo de cerradura o panel de control que se pueda accionar."
    "Definitivamente: NO puedes abrir esa puerta."
    "Intenta antes arreglar el procesador atmosf�rico."
    "Al final no ser� necesario abrir esa puerta..."
    "... porque el monstruo habr� abierto un buen agujero con su sangre �cida."
;
ZIPI_Pista ZIPI_Pista7
with
  ZIPI_titulo "�C�mo entro en el procesador atmosf�rico?",
  ZIPI_pistas
    "Tienes que abrir la puerta."
    "Para abrir la puerta tienes que usar el panel de control situado junto a ella."
    "Primero hay que hacer funcionar el panel de control, y luego teclear un c�digo de acceso."
;
ZIPI_Pista ZIPI_Pista8
with
  ZIPI_titulo "�Qu� hago con el panel de control?",
  ZIPI_pistas
    "Est� un poco destrozado... �Has probado a soldar los cables?"
    "No, me temo que as� no conseguir�s nada..."
    "El problema es que no le llega energ�a suficiente."
    "�C�mo podr�as suministrar energ�a a sus circuitos f�cilmente?"
    "Mira en tu inventario... �Hay algo que consuma energ�a?"
    "Si no es as�... �has mirado bien dentro de la nave? Algo que d� luz..."
    "La linterna consume la energ�a de una bater�a."
    "Conecta la bater�a al panel de control."
;
ZIPI_Pista ZIPI_Pista9
with
  ZIPI_titulo "�C�mo consigo el c�digo de acceso?",
  ZIPI_pistas
    "�El panel ya dispone de energ�a? Entonces s�lo falta teclear el c�digo correcto."
    "Ese c�digo te lo puede facilitar alguien."
    "Ese alguien puede ser Madre o el robot."
    "El robot conoce un c�digo, porque iba a arreglar el procesador, aunque se qued� a mitad de camino."
    "Prueba a empujar al robot hasta la puerta."
    "Madre tambi�n sabe el c�digo."
    "El c�digo es 759812. Ve al panel de control y tecl�alo."
    "�Vaya! Ese c�digo ya no sirve, porque el panel de control se ha reiniciado."
    "Hay que identificar el nuevo c�digo usando la semilla."
;
ZIPI_Pista ZIPI_Pista10
with
  ZIPI_titulo "�Para qu� sirve la semilla?",
  ZIPI_pistas
    "La clave que da el robot ya no sirve, y el panel dice que la semilla es 9957."
    "Al reiniciarse el panel, el c�digo de acceso se ha regenerado a partir de la semilla."
    "Preg�ntale a Madre sobre la semilla."
    "Dale a Madre el valor de la semilla que indica el display."
    "~MADRE, LA SEMILLA ES 9957~."
    "Madre te dir� que el nuevo c�digo es el 258741. Tecl�alo en el panel."
;
ZIPI_Pista ZIPI_Pista11
with
  ZIPI_titulo "�Est� oscuro! �No veo nada!",
  ZIPI_pistas
    "No hay luz artificial en ning�n edificio. Necesitas otra fuente de luz."
    "�Has probado con la linterna?"
    "Pero la bater�a se ha descargado para poder abrir la puerta..."
    "Deber�s recargarla."
    "Hay un cargador de bater�as en la nave."
    "~RECARGA LAS BATERIAS~ en la sala de proa de la nave."
;
ZIPI_Pista ZIPI_Pista12
with
  ZIPI_titulo "�Mejor solo o acompa�ado?",
  ZIPI_pistas
    "�Has probado a entrar solo?"
    "Si entras solo, el monstruo sale y te mata..."
    "Est� claro que es mejor llegar acompa�ado."
;
ZIPI_Pista ZIPI_Pista13
with
  ZIPI_titulo "�Socorro!",
  ZIPI_pistas
    "�El monstruo se ha llevado a Jason?"
    "Al menos est�s vivo... �Y Jason tambi�n!"
    "Hay que rescatar a Jason."
    "Sigue el rastro de �cido que ha dejado el monstruo, pero..."
    "... recuerda que el procesador atmosf�rico sigue estropeado."
;
ZIPI_Pista ZIPI_Pista14
with
  ZIPI_titulo "�C�mo arreglo el procesador atmosf�rico?",
  ZIPI_pistas
    "Todo est� gobernado por la unidad central."
    "Hay que abrir la caja de conexiones."
    "Para ello necesitas una herramienta adecuada."
    "Nada m�s adecuado que un destornillador. Quita con �l el tornillo que cierra la tapa."
    "~ABRE LA CAJA DE CONEXIONES CON EL DESTORNILLADOR~."
;
ZIPI_Pista ZIPI_Pista15
with
  ZIPI_titulo "�Y ahora?",
  ZIPI_pistas
    "Al abrir la caja de conexiones, ves que hay un circuito da�ado."
    "Hay que soldar ese circuito para arreglarlo."
    "�Qui�n puede ayudarte a soldar? �Has mirado por los alrededores?"
    "El androide es un robot de mantenimiento. Entre otras cosas, puede soldar."
    "Pero no puedes con �l: pesa demasiado."
    "Ve empuj�ndolo hasta llegar al interior del procesador atmosf�rico."
    "~EMPUJA AL ROBOT HACIA EL NORTE~, luego al norte otra vez, y luego adentro."
;
ZIPI_Pista ZIPI_Pista16
with
  ZIPI_titulo "�Qu� me queda?",
  ZIPI_pistas
    "�Ya tienes al experto soldador delante del circuito da�ado?"
    "S�lo te queda pedirle que lo arregle."
    "~ROBOT, ARREGLA EL CIRCUITO~."
;
ZIPI_Pista ZIPI_Pista17
with
  ZIPI_titulo "El complejo - informaci�n general",
  ZIPI_pistas
    "El complejo est� construido alrededor de la veta de mineral."
    "Las zonas del interior del complejo se comunican entre s� mediante t�neles."
    "Hay cuatro balcones que dan a la veta, situados al N, S, E y O de la misma."
    "Por las zonas m�s al oeste podr�s encontrar puertas cerradas hacia los h�bitats."
    "El complejo tiene tres niveles: el nivel 0 en la superficie y los niveles -1 y -2 subterr�neos."
    "El nivel -2 tiene a�n zonas sin acabar."
;
ZIPI_Pista ZIPI_Pista18
with
  ZIPI_titulo "Generalidades",
  ZIPI_pistas
    "El complejo contiene todo lo necesario para vivir en un paraje tan inh�spito como �ste."
    "Si sigues leyendo, sabr�s cosas que puedes descubrir f�cilmente por ti mismo, simplemente movi�ndote por el mapa."
    "En el nivel 0 encuentras la la oficina y el aula."
    "En el nivel -1 est� el comedor, la despensa, la cocina, la enfermer�a, la sala de seguridad y el laboratorio."
    "La zona de emergencia se encuentra aislada por una puerta en el nivel -1, hacia el sur."
    "En el nivel -2 encuentras las salas de ventilaci�n y el ascensor de emergencia."
    "Jason queda atrapado en una vaina viscosa situada en una sala de ventilaci�n."
;
ZIPI_Pista ZIPI_Pista19
with
  ZIPI_titulo "La sala de seguridad",
  ZIPI_pistas
    "�De qu� son esos dos cables que salen de la consola de control?"
    "Transmiten im�genes captadas por c�maras de seguridad."
    "Las c�maras est�n en la oficina y el laboratorio."
    "La consola de control registra y graba esas im�genes. Las puedes reproducir."
    "Pulsa el bot�n que pone ~Reproducir~..."
    "... al menos DOS veces."
;
ZIPI_Pista ZIPI_Pista20
with
  ZIPI_titulo "La oficina",
  ZIPI_pistas
    "Exam�nalo todo."
    "�Has estado ya en la sala de seguridad?"
    "Si es as�, ver�s que hay un cuadro que oculta algo."
    "Qu�talo de la pared."
    "�Anotaste el c�digo de la caja fuerte cuando viste la grabaci�n de seguridad?"
    "El c�digo es 111582."
;
ZIPI_Pista ZIPI_Pista21
with
  ZIPI_titulo "El aula",
  ZIPI_pistas
    "Ese proyector tiene que servir para algo..."
    "�Has estado ya en la oficina?"
    "Si es as�, tal vez tengas algo que proyectar."
    "Proyecta el holocubo y examina la pantalla."
;
ZIPI_Pista ZIPI_Pista22
with
  ZIPI_titulo "El laboratorio",
  ZIPI_pistas
    "Exam�nalo todo."
    "�Has mirado en las estanter�as?"
    "En una de ellas hay algo."
    "Es un bistur� l�ser. C�gelo."
    "La necesitar�s para cortar la vaina donde se encuentra atrapado Jason."
;
ZIPI_Pista ZIPI_Pista23
with
  ZIPI_titulo "La enfermer�a",
  ZIPI_pistas
    "Exam�nalo todo."
    "�Has mirado en los armarios?"
    "En concreto: �has mirado en los cajones?"
    "En uno de los cajones hay algo."
    "Es una jeringa de adrenalina. C�gela."
    "La necesitar�s para reanimar a Jason cuando caiga inconsciente."
;
ZIPI_Pista ZIPI_Pista24
with
  ZIPI_titulo "La despensa, la cocina y el comedor",
  ZIPI_pistas
    "A veces se oyen ruidos raros por esa zona, procedentes de la despensa."
    "Lo mejor es que est�s all� el menor tiempo posible."
    "Mejor a�n: evita esas tres estancias en todo lo posible."
;
ZIPI_Pista ZIPI_Pista25
with
  ZIPI_titulo "El monstruo - informaci�n general",
  ZIPI_pistas
    "El monstruo se mueve libremente y al azar por todo el complejo."
    "Cuando est� a menos de 50 metros de tu situaci�n, el detector de movimiento te lo indicar�."
    "Si te lo encuentras... �corre!"
    "A veces desaparece para volver a aparecer instantes m�s tarde en otro sitio."
    "En general, ev�talo a toda costa."
;
ZIPI_Pista ZIPI_Pista26
with
  ZIPI_titulo "�D�nde est� Jason?",
  ZIPI_pistas
    "Hay que encontrar a Jason. A�n est� vivo."
    "Lo m�s f�cil es seguir el rastro de sangre dejado en el suelo por el monstruo."
    "Si a�n no has arreglado el procesador atmosf�rico, recuerda que la linterna gasta bater�as."
    "�Has perdido el rastro de sangre?"
    "Baja hasta el nivel -2."
    "Dir�gete al oeste, y sube a las salas de ventilaci�n."
    "Jason est� dentro de la vaina mucosa que est� incrustada en un hueco en el techo."
;
ZIPI_Pista ZIPI_Pista27
with
  ZIPI_titulo "�C�mo lo salvo?",
  ZIPI_pistas
    "�Ya has encontrado a Jason?"
    "Est� dentro de una vaina mucosa, muy dura."
    "Necesitas un instrumento cortante y muy potente para poder cortar la dura vaina."
    "�Has mirado en el laboratorio?"
    "Est� en el nivel -1, por el sureste."
    "Mira en una de las estanter�as."
    "Recoge el bistur� l�ser y abre la vaina con �l."
    "Saca a Jason de la vaina."
;
ZIPI_Pista ZIPI_Pista28
with
  ZIPI_titulo "�Para qu� sirven las c�maras de seguridad?",
  ZIPI_pistas
    "Hay dos c�maras de seguridad."
    "Hay una en la oficina y otra en el laboratorio."
    "Observa el cable que sale de la c�mara."
    "Si lo sigues, te llevar� hasta el otro extremo."
    "A la consola de control, en la sala de seguridad."
;
ZIPI_Pista ZIPI_Pista29
with
  ZIPI_titulo "�Qu� ocurre con los h�bitats?",
  ZIPI_pistas
    "Las puertas de los h�bitats est�n cerradas."
    "Y no puedes abrirlas."
    "De hecho, no puedes entrar."
    "No sirven para nada. S�lo est�n de adorno."
;
ZIPI_Pista ZIPI_Pista30
with
  ZIPI_titulo "�Corre! �Sal del complejo!",
  ZIPI_pistas
    "Intenta salir por la puerta del complejo."
    "�Vaya! No puedes. El monstruo ha sellado la salida."
    "Habr� que buscar otra forma de salir. Por ah� es imposible."
;
ZIPI_Pista ZIPI_Pista31
with
  ZIPI_titulo "�Jason cae al suelo inconsciente!",
  ZIPI_pistas
    "Pesa demasiado para moverlo o empujarlo."
    "Y no puedes hablarle: est� inconsciente, claro..."
    "Busca algo para reanimarlo..."
    "... alguna sustancia euforizante."
    "Adrenalina."
    "B�scala en la enfermer�a."
    "En un caj�n. Ah� ver�s una jeringa de adrenalina."
;
ZIPI_Pista ZIPI_Pista32
with
  ZIPI_titulo "Buscando otra salida",
  ZIPI_pistas
    "Est� claro que no puedes salir por la entrada principal."
    "Hay otra salida, a la que s�lo se accede en casos de emergencia."
    "Es el ascensor de seguridad, situado en el nivel -2 del complejo."
    "Para poder escapar, hay que activar el protocolo de emergencia."
    "Lo que, de paso, har� estallar todo el complejo por los aires."
    "El protocolo de emergencia se activa en la zona de emergencia, en el nivel -1."
    "Pero para entrar necesitas una ~llave~..."
    "... y para activar el protocolo de emergencia, tienes que saber c�mo se hace."
    "�Has estado en la oficina? �Y en el aula?"
    "�Has visto las grabaciones de seguridad?"
;
ZIPI_Pista ZIPI_Pista33
with
  ZIPI_titulo "�C�mo abro la puerta que est� al sur del nivel -1?",
  ZIPI_pistas
    "No puedes abrirla directamente. Antes hay que desbloquearla."
    "�Llevas algo que entre en la ranura?"
    "�Has estado ya en la oficina?"
    "Si es as�, tal vez tengas algo que entre."
    "Inserta en la ranura la tarjeta que encontraste en la caja fuerte."
;
ZIPI_Pista ZIPI_Pista34
with
  ZIPI_titulo "�A d�nde da la puerta?",
  ZIPI_pistas
    "Debe ser un lugar restringido."
    "Un lugar para casos excepcionales."
    "La zona de emergencia."
;
ZIPI_Pista ZIPI_Pista35
with
  ZIPI_titulo "�Qu� hago dentro de la zona de emergencia?",
  ZIPI_pistas
    "Activar el protocolo de emergencia."
    "Eso har� que todo explote dentro de 10 minutos."
    "Pero tambi�n te abrir� una salida."
    "La salida est� en el nivel -2."
    "Es el ascensor de emergencia."
;
ZIPI_Pista ZIPI_Pista36
with
  ZIPI_titulo "�C�mo activo el protocolo de emergencia?",
  ZIPI_pistas
    "�Has visualizado el holocubo?"
    "Si no, encu�ntralo primero..."
    "Entra con Jason y cierra la puerta, pero aseg�rate de que el monstruo no est� dentro con vosotros."
    "Deja a Jason en la sala este de emergencia."
    "�Sabes c�mo?: ~JASON, QUEDATE AQUI~."
    "Dir�gete a la sala oeste de emergencia."
    "Dile a Jason que pulse el bot�n, e inmediatamente despu�s pulsa t� el que tienes delante.   "
;
ZIPI_Pista ZIPI_Pista37
with
  ZIPI_titulo "�C�mo puedo acceder al ascensor de emergencia?",
  ZIPI_pistas
    "El ascensor s�lo se abre en caso de emergencia, l�gicamente."
    "Tienes que activar el protocolo de emergencia."
;
ZIPI_Pista ZIPI_Pista38
with
  ZIPI_titulo "�C�mo salimos de aqu�?",
  ZIPI_pistas
    "�Has activado el protocolo de emergencia?"
    "Dir�gete al ascensor de emergencia."
    "Est� en el nivel -2, al oeste del montacargas."
    "Entra en el ascensor, ahora que est� abierto."
;
ZIPI_Pista ZIPI_Pista39
with
  ZIPI_titulo "El final",
  ZIPI_pistas
    "�Has podido escapar vivo del complejo?"
    "�Y llevas a Jason contigo?"
    "Entonces a�n est�s a tiempo de escapar..."
    "... �pero no hay un minuto que perder!"
    "Entrad en la nave... y rezad lo que sep�is."
;
ZIPI_Otro ZIPI_Otro0
with
  ZIPI_titulo "�C�mo funciona este sistema de pistas?",
  ZIPI_ejecutar [;
       print "^- Te puedes desplazar por los men�s usando las flechas del cursor arriba y abajo. ";
       print "^- Para seleccionar una opci�n del men�, puedes pulsar las teclas ~Entrar~ o ~P~. ";
       print "^- Para volver al men� anterior, o salir del sistema de pistas, pulsa ~Q~. ";
       print "^- Cuando est�s leyendo pistas, pulsa ~P~ para ver la pista siguiente (si es que ";
       print "^  hay m�s), o pulsa ~Q~ para retroceder a la pantalla anterior. ";
  ];
ZIPI_Otro ZIPI_Otro1
with
  ZIPI_titulo "Acciones y �rdenes",
  ZIPI_ejecutar [;
       print "^A�L�I�E�N es una aventura conversacional que te sumerge en un mundo de terror y ";
       print "^ciencia-ficci�n donde t� eres el protagonista y con el que podr�s interactuar ";
       print "^introduciendo �rdenes con el teclado. ";
       print "^^";
       print "Dichas �rdenes tienen una sintaxis t�pica de �VERBO� o �VERBO NOMBRE�, aunque ";
       print "^pueden construirse �rdenes mucho m�s complejas si fuese necesario. ";
       print "^^";
       print "Algunos ejemplos: ";
       print "^^";
       print "> COGE LA CAJA DE HERRAMIENTAS ";
       print "^> ABRE EL ARMARIO ";
       print "^> COGE EL TRAJE ROJO Y PONTELO ";
       print "^> SACA TODO DE DENTRO DEL ARMARIO ";
       print "^^";
       print "Los verbos se pueden escribir en imperativo (�COGE�) o infinitivo (�COGER�), si bien ";
       print "^se recomienda la primera opci�n, m�s que nada porque resulta m�s corta. Y los ";
       print "^art�culos (�EL�, �LA�) se pueden poner, aunque no son necesarios. ";
  ];
ZIPI_Otro ZIPI_Otro2
with
  ZIPI_titulo "Algunas acciones frecuentes",
  ZIPI_ejecutar [;
       print "^Las siguientes son algunas de las acciones que se utilizan de manera m�s frecuente en ";
       print "^una aventura conversacional: ";
       print "^^";
       print "COGE tal . . . .: Coger el objeto 'tal'. ";
       print "^DEJA tal . . . .: Dejar el objeto 'tal'. ";
       print "^ABRE tal . . . .: Abrir 'tal' (normalmente una puerta o alg�n recipiente cerrado). ";
       print "^CIERRA tal . . .: Cerrar 'tal' (normalmente una puerta o alg�n recipiente abierto). ";
       print "^METE tal EN cual: Meter el objeto 'tal' dentro de 'cual' (por ejemplo, una caja). ";
       print "^SACA tal DE cual: Sacar el objeto 'tal' de dentro de 'cual' (por ejemplo, una caja). ";
       print "^PONTE tal . . . : Ponerse el objeto 'tal' (normalmente una prenda de ropa). ";
       print "^QUITATE tal . . : Quitarse el objeto 'tal' (normalmente una prenda de ropa). ";
       print "^ENTRA . . . . . : Entrar dentro de alg�n sitio, posiblemente a trav�s de una puerta. ";
       print "^SAL . . . . . . : Salir de alg�n sitio, posiblemente a trav�s de una puerta. ";
       print "^EXAMINA tal (o ";
       print "^EX tal o X tal) : Describir el objeto 'tal' con detalle. ";
       print "^INVENTARIO (o I): Mostrar un listado con los objetos que posees actualmente. ";
  ];
ZIPI_Otro ZIPI_Otro3
with
  ZIPI_titulo "Moverse por el mundo",
  ZIPI_ejecutar [;
       print "^El mundo de A�L�I�E�N est� compuesto por multitud de recintos interconectados entre ";
       print "^s� llamados localidades. Las salidas desde tu localidad actual se muestran siempre ";
       print "^a continuaci�n de la descripci�n de dicha localidad. Para moverte de una localidad ";
       print "^a otra, simplemente teclea la salida correspondiente. ";
       print "^^";
       print "Por ejemplo: supongamos que tu localidad actual tiene como salidas �norte� y ";
       print "^�afuera�. En ese caso, para moverte hacia la localidad situada al norte de la ";
       print "^actual, puedes teclear las �rdenes NORTE, VETE AL NORTE, IR AL NORTE o simplemente ";
       print "^N. Y para salir fuera, puedes teclear SAL, SALIR o FUERA. Los puntos cardinales se ";
       print "^pueden abreviar a N, S, E, O, NE, SE, NO y SO. ";
  ];
ZIPI_Otro ZIPI_Otro4
with
  ZIPI_titulo "Otros personajes del juego",
  ZIPI_ejecutar [;
       print "^A veces, ser� necesario enviar �rdenes a alg�n personaje (por ejemplo, al Mayor ";
       print "^Jason). En tal caso, deber�s indicar el nombre del personaje seguido de una coma, ";
       print "^y a continuaci�n la orden que deseas enviarle: ";
       print "^^";
       print "> JASON, COGE TU TRAJE ";
       print "^> JASON, SIGUEME ";
       print "^^";
       print "Para hablar con un personaje, o bien preguntarle algo, se usa la misma sintaxis: ";
       print "^^";
       print "> JASON, HABLAME DE TI ";
       print "^> JASON, QUE OPINAS SOBRE EL PLANETA ";
       print "^^";
       print "Saber trabajar conjuntamente con los personajes es crucial para alcanzar el �xito ";
       print "^en esta aventura. ";
  ];
ZIPI_Otro ZIPI_Otro5
with
  ZIPI_titulo "Algunos comandos �tiles",
  ZIPI_ejecutar [;
       print "^SONIDO SI/NO . . . . : Activar o desactivar todos los efectos sonoros. ";
       print "^SONIDO FONDO SI/NO . : Activar o desactivar el sonido de fondo. ";
       print "^SONIDO DETECTOR SI/NO: Activar o desactivar el sonido del detector de movimiento. ";
       print "^GRAFICOS SI/NO . . . : Activar o desactivar la visualizaci�n de gr�ficos. ";
       print "^GRAFICOS PEQUE�OS/ ";
       print "^  MEDIANOS/GRANDES . : Cambia el tama�o de la ventana de gr�ficos (por omisi�n ";
       print "^                       se mostrar�n en tama�o MEDIANO). ";
       print "^CONFIGURACION . . . .: Muestra un men� de opciones de gr�ficos y sonido. ";
       print "^SALIDAS (o X) . . . .: Mostrar las salidas visibles en la localidad actual. ";
       print "^SALIDAS SI/NO . . . .: Mostrar (o no) autom�ticamente las salidas visibles en ";
       print "^                       cada localidad. ";
       print "^SAVE (o GUARDAR) . . : Almacenar la situaci�n actual en un archivo externo, para ";
       print "^                       poder volver a �l en cualquier momento. ";
       print "^LOAD (o RECUPERAR) . : Recuperar una situaci�n previamente guardada con SAVE o ";
       print "^                       GUARDAR. ";
       print "^AYUDA . . . . . . . .: Por si alguna vez te encuentras atascado. ";
       print "^REINICIAR . . . . . .: Volver a empezar desde el principio. ";
       print "^ACABAR (o FIN) . . . : Salir de la aventura (cuidado: no guarda la situaci�n actual). ";
  ];
ZIPI_Otro ZIPI_Otro6
with
  ZIPI_titulo "Consejos y ayudas",
  ZIPI_ejecutar [;
       print "^- Examina todo lo que encuentres. Varias veces si hace falta. ";
       print "^- Recoge todos los objetos que puedas; podr�an serte de utilidad. ";
       print "^- Habla con los dem�s personajes de la aventura. A veces te dar�n pistas �tiles. ";
       print "^- El azar es parte de esta aventura. Tenlo en cuenta a la hora de llevar a cabo ";
       print "^  determinadas acciones. ";
       print "^- Graba frecuentemente tu situaci�n con la orden GUARDAR. Nunca se sabe lo que ";
       print "^  puedes encontrarte tras esa esquina... ";
       print "^- Si te encuentras con alg�n fallo o no sabes c�mo avanzar, puedes plantear tus ";
       print "^  dudas en el foro del CAAD o en alpha.aventuras@@64gmail.com. ";
  ];
ZIPI_Otro ZIPI_Otro7
with
  ZIPI_titulo "Al jugar la aventura, las letras se ven feas o con colores extra�os",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "   a) [Si usas otro sistema que no sea Windows] Aseg�rate de tener instalada^";
       print "      la �ltima versi�n de Gargoyle (al menos, la 2011.1). Los usuarios de^";
       print "      Windows que instalen la aventura con el programa de instalaci�n no^";
       print "      necesitan comprobar esto, ya que Gargoyle se instala con la aventura.^";
       print "^";
       print "   b) Aseg�rate de que exista el archivo 'garglk.ini' en la misma carpeta que^";
       print "      la aventura. Para ello:^";
       print "^";
       print "       i. Si usas Linux, y has instalado la aventura usando el paquete .deb,^";
       print "          comprueba si existe el archivo en esta ruta:^";
       print "^";
       print "            /usr/share/games/alphaaventuras-alien-ee/garglk.ini^";
       print "^";
       print "      ii. Si estas usando la versi�n multiplataforma, comprueba simplemente^";
       print "          que el archivo 'garglk.ini' se encuentra en la misma carpeta que la^";
       print "          aventura 'alien.blb', junto al resto de los archivos incluidos.^";
       print "^";
       print "   Si todo lo anterior no funciona, instala de nuevo la aventura.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro8
with
  ZIPI_titulo "Las letras se ven demasiado grandes o demasiado peque�as",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Puedes cambiar el tama�o de las letras editando el archivo 'garglk.ini':^";
       print "^";
       print "  a) En Windows estar� en la ruta:^";
       print "     @@92Program Files@@92Juegos Conversacionales@@92ALIEN - La aventura - Edici�n Especial@@92^";
       print "^";
       print "  b) En Linux, si instalaste la aventura con el paquete .deb, estar� en:^";
       print "     /usr/share/games/alphaaventuras-alien-ee/^";
       print "^";
       print "  c) En la versi�n multiplataforma lo encontrar�s en la misma ruta que el resto^";
       print "     de los archivos distribuidos con la aventura.^";
       print "^";
       print "  Cuando hayas abierto el archivo 'garglk.ini' con tu editor de textos favorito,^";
       print "  localiza las l�neas que empiecen por 'monosize' y 'propsize'. Para ajustar el^";
       print "  tama�o de las letras, simplemente cambia los n�meros que aparezcan al lado.^";
       print "  Poniendo n�meros mayores, las letras se ver�n m�s grandes, y viceversa. Aseg�rate^";
       print "  de que el 'propsize' sea siempre un poco mayor que el 'monosize'.^";
       print "^";
       print "  Guarda los cambios en el mismo archivo y ejecuta de nuevo la aventura.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro9
with
  ZIPI_titulo "Los gr�ficos se ven demasiado grandes y es inc�modo jugar as�",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "   a) Ampl�a el tama�o de la ventana del juego, maximiz�ndola hasta ocupar^";
       print "      todo el escritorio.^";
       print "^";
       print "   b) Configura la aventura para que use gr�ficos m�s peque�os, usando el^";
       print "      comando siguiente dentro del juego:^";
       print "^";
       print "      > CONFIGURACI�N^";
       print "      ^";
       print "      Una vez dentro, cambia el tama�o de los gr�ficos a uno peque�o (entre^";
       print "      200 y 350 p�xeles puede resultar m�s adecuado para tu pantalla).^";
       print "^";
       print "   c) Si lo anterior no fuera suficiente, siempre puedes desactivar los gr�ficos^";
       print "      completamente, aunque no te lo recomendamos, ya que con ello perder�as^";
       print "      gran parte del atractivo de la aventura. Para ello, ejecuta el comando^";
       print "      siguiente dentro del juego:^";
       print "^";
       print "      > GR�FICOS NO^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro10
with
  ZIPI_titulo "Los gr�ficos se ven demasiado peque�os",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Prueba lo siguiente:^";
       print "^";
       print "   a) Ampl�a el tama�o de la ventana del juego, maximiz�ndola hasta ocupar^";
       print "      todo el escritorio. Si la ventana es demasiado peque�a, los gr�ficos^";
       print "      se reescalar�n autom�ticamente para que quepan completos dentro de la^";
       print "      misma, pero se ver�n muy peque�os.^";
       print "^";
       print "   b) Configura la aventura para que use gr�ficos m�s grandes, usando uno de^";
       print "      los comandos siguientes dentro del juego:^";
       print "^";
       print "      > GR�FICOS MEDIANOS^";
       print "          (esto har� que la aventura use los gr�ficos a tama�o mediano)^";
       print "^";
       print "      > GR�FICOS GRANDES^";
       print "          (esto har� que la aventura use los gr�ficos al tama�o m�s grande)^";
       print "^";
       print "      > CONFIGURACI�N^";
       print "          (mostrar� un men� donde podr�s cambiar el tama�o con m�s detalle)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro11
with
  ZIPI_titulo "�No veo gr�ficos en ning�n momento!",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Comprueba lo siguiente:^";
       print "^";
       print "   a) Aseg�rate de tener activados los gr�ficos dentro del juego. Para ello,^";
       print "      usa el comando siguiente dentro del juego:^";
       print "^";
       print "      > GR�FICOS SI^";
       print "^";
       print "      Ten en cuenta tambi�n que los gr�ficos se apagan autom�ticamente en^";
       print "      ciertas partes de la aventura, para que el texto ocupe toda la ventana^";
       print "      de juego.^";
       print "^";
       print "   b) Aseg�rate de que no est�s en un lugar a oscuras y sin ninguna fuente de^";
       print "      luz, como una linterna encendida.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro12
with
  ZIPI_titulo "�No oigo nada!",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Si no oyes m�sica ni sonidos durante el juego, comprueba lo siguiente:^";
       print "^";
       print "   a) Aseg�rate de tener activados los sonidos dentro del juego. Para ello,^";
       print "      usa el comando siguiente dentro del juego:^";
       print "^";
       print "      > SONIDO SI^";
       print "^";
       print "   b) Si no oyes el sonido de fondo, aseg�rate de tenerlo activado usando el^";
       print "      comando siguiente:^";
       print "^";
       print "      > SONIDO FONDO SI^";
       print "^";
       print "   c) Si no oyes el sonido del detector de movimiento, aseg�rate de tenerlo^";
       print "      activado usando el comando siguiente:^";
       print "^";
       print "      > SONIDO DETECTOR SI^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro13
with
  ZIPI_titulo "Mi lector de pantalla para ciegos no lee bien los ~teletipo~",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "   Algunos lectores de pantalla usados por personas con deficiencias visuales^";
       print "   tienen problemas para leer los mensajes que aparecen letra a letra (mensajes^";
       print "   'teletipo'). En tal caso, puedes desactivar el efecto 'teletipo' usando el^";
       print "   comando:^";
       print "^";
       print "   > CONFIGURACI�N^";
       print "^";
       print "   Entra en el submen� ~Accesibilidad~ y desactiva la opci�n ~Efecto teletipo~.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro14
with
  ZIPI_titulo "Tengo dificultades motrices y el alien siempre me alcanza",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "   Si tienes dificultades para escribir con la velocidad necesaria para que el^";
       print "   alien no te alcance, puedes desactivar los eventos en tiempo real usando el^";
       print "   comando:^";
       print "^";
       print "   > CONFIGURACI�N^";
       print "^";
       print "   Entra en el submen� ~Accesibilidad~ y desactiva la opci�n ~Tiempo real~. De^";
       print "   esta forma, el juego no avanzar� mientras no teclees ninguna orden.^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro15
with
  ZIPI_titulo "Estoy atascado y no s� c�mo continuar",
  ZIPI_ejecutar [;
       font off;
       print "^";
       print "  Si andas perdido y no sabes c�mo resolver alg�n puzzle o situaci�n:^";
       print "^";
       print "   a) Usa el sistema de pistas interactivas, tecleando:^";
       print "^";
       print "        > PISTAS^";
       print "^";
       print "      en cualquier momento del juego.^";
       print "^";
       print "   b) Pregunta en el foro del CAAD, en la siguiente direcci�n:^";
       print "^";
       print "        http://foro.caad.es^";
       print "^";
       print "   c) Contacta con nosotros por alguna de las las estas v�as:^";
       print "^";
       print "      - email: alpha.aventuras@@64gmail.com^";
       print "      - web: http://sites.google.com/site/alphaaventuras^";
       print "      - facebook: https://www.facebook.com/alphaaventuras^";
       print "      - wikiCAAD: http://wiki.caad.es/Alpha_Aventuras^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro16
with
  ZIPI_titulo "Cr�ditos",
  ZIPI_ejecutar [;
       print "A�L�I�E�N: LA AVENTURA - EDICI�N ESPECIAL (c) 2008-2012 Alpha Aventuras^ ";
       print "^- PROGRAMACI�N Y DISE�O: ";
       print "^     Ricardo P�rez L�pez ";
       print "^- GR�FICOS E IDEA ORIGINAL: ";
       print "^     Manuel Mill�n Ruiz ";
       print "^- TEXTOS: ";
       print "^     Ricardo P�rez L�pez ";
       print "^     Francisco J. Rold�n Dom�nguez ";
       print "^     Manuel I. Monge Garc�a ";
       print "^- MAPEADO Y DOCUMENTACI�N: ";
       print "^     Francisco J. Rold�n Dom�nguez ";
       print "^     Antonio Matiola Ortiz ";
       print "^- PRUEBAS: ";
       print "^     Ricardo P�rez L�pez ";
       print "^     Manuel Mill�n Ruiz ";
       print "^     Francisco Picazo Mill�n ";
       print "^     Manuel I. Monge Garc�a^ ";
       print "^  Para m�s informaci�n, usa el comando CR�DITOS durante el juego. ";
  ];
ZIPI_Otro ZIPI_Otro17
with
  ZIPI_titulo "�Cuidado!",
  ZIPI_ejecutar [;
       print "^Si sigues adelante, sabr�s qu� estancias tiene el complejo. Te recomendamos que ";
       print "^intentes descubrirlo por ti mismo, movi�ndote por su interior, pero si a�n as� ";
       print "^quieres continuar con las pistas, entra en la siguiente opci�n del men�. ";
  ];
ZIPI_Otro ZIPI_Otro18
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
ZIPI_Otro ZIPI_Otro19
with
  ZIPI_titulo "El exterior",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "              +----------+^";
       print "              | EXTERIOR | -> (puerta al procesador atmosf�rico)^";
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
ZIPI_Otro ZIPI_Otro20
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
       print "                   | T�NEL  |--| BALC�N  |--| T�NEL  |--| AULA  |^";
       print "                   +--------+  +---------+  +--------+  +-------+^";
       print "                        |                        |          |^";
       print "      +---------+  +--------+               +--------+  +-------+^";
       print "      | OFICINA |--| BALC�N |               | BALC�N |--| T�NEL |^";
       print "      +---------+  +--------+               +--------+  +-------+^";
       print "                        |                        |^";
       print "                   +--------+  +---------+  +--------+^";
       print "                   | T�NEL  |--| BALC�N  |--| T�NEL  |^";
       print "                   +--------+  +---------+  +--------+^";
       print "                                    v  (abajo al nivel -1)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro21
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
       print "            |  BALC�N   |                | BALC�N |--| ENFERMER�A |^";
       print "            +-----------+                +--------+  +------------+^";
       print "                  |          /@@92               |             |^";
       print "            +-----------+  +----------+  +--------+     +-------+^";
       print "            |   T�NEL   |--|  BALC�N* |--| T�NEL  |-----| T�NEL |^";
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
ZIPI_Otro ZIPI_Otro22
with
  ZIPI_titulo "Nivel -2",
  ZIPI_ejecutar [;
       print "^^";
       font off;
       print "                             +-------------+   +-------------+^";
       print "                             |   SALA DE   |   |   SALA DE   | (vaina en^";
       print "                             | VENTILACI�N |---| VENTILACI�N |  hueco del^";
       print "                             |    OESTE    |   |    ESTE     |  techo)^";
       print "         (sube al nivel -1)  +-------------+   +-------------+^";
       print "                      /@@92           /@@92 ^";
       print "  +-----------+  +----------+  +--------+^";
       print "  |   T�NEL   |--|  BALC�N  |--| T�NEL  |^";
       print "  +-----------+  +----------+  +--------+^";
       print "  (ascensor de^";
       print "   emergencia)^";
       font on;
  ];
ZIPI_Otro ZIPI_Otro23
with
  ZIPI_titulo "En la nave",
  ZIPI_ejecutar [;
       print "^Vete al oeste y abre el armario. Coge todo lo que puedas y dir�gete de nuevo al este. ";
       print "^Dile a Madre que abra el compartimento de trajes. Coge tu traje y p�ntelo. Dile a ";
       print "^Jason que haga lo mismo. Dile a Madre que abra la compuerta exterior, y salid los dos.^ ";
       print "^Por cierto: la palanca no sirve para nada durante el juego... ";
  ];
ZIPI_Otro ZIPI_Otro24
with
  ZIPI_titulo "En el exterior",
  ZIPI_ejecutar [;
       print "^Vete al norte, abre la linterna, saca la bater�a de la linterna y col�cala en el ";
       print "^panel de control. El panel se enciende y te dice que la semilla es 9957. Si tecleas ";
       print "^el c�digo de acceso que te da el robot (es decir, 759812), ver�s que ya no es v�lido. ";
       print "^Indica a Madre el valor de la semilla (~MADRE, LA SEMILLA ES 9957~) y te calcular� ";
       print "^el nuevo c�digo, que resulta ser 268741. Teclea ese c�digo en el panel de control. ";
       print "^Recoge la bater�a. Vuelve al sur. Pide a Madre que abra la compuerta de la nave. ";
       print "^Entra en la nave. Mete la bater�a en el cargador de bater�as. C�gela de nuevo y ";
       print "^m�tela en la linterna. Haz que Madre abra de nuevo la puerta, y sal otra vez al ";
       print "^exterior. Vete al norte, de nuevo a la entrada del procesador atmosf�rico. Enciende ";
       print "^la linterna y entra. ";
  ];
ZIPI_Otro ZIPI_Otro25
with
  ZIPI_titulo "El procesador atmosf�rico",
  ZIPI_ejecutar [;
       print "^El monstruo se llevar� a Jason. Recoge su rifle y sal. Vete al sur, y de nuevo al ";
       print "^sur. Empuja al robot al norte, de nuevo al norte, y finalmente adentro. En la ";
       print "^unidad central hay una caja de conexiones. �brela con el destornillador. Dentro hay ";
       print "^un circuito roto. Dile al robot que lo suelde. Ya est� arreglado el procesador ";
       print "^atmosf�rico, por lo que ya no necesitar�s el traje ni la linterna. Sal de la sala, ";
       print "^sur, sur, este y entra por la puerta del complejo. ";
  ];
ZIPI_Otro ZIPI_Otro26
with
  ZIPI_titulo "El monstruo",
  ZIPI_ejecutar [;
       print "^El monstruo se va moviendo aleatoriamente por el complejo. Tienes que evitarlo. Si te ";
       print "^lo encuentras, sal corriendo de esa habitaci�n, o empezar� a seguirte. Si te sigue, ";
       print "^no dejes de moverte (no hagas otra cosa en tu turno, o te matar�). El detector de ";
       print "^movimiento te advertir� de su presencia, as� que no te debe resultar dif�cil ";
       print "^esquivarlo. No intentes dispararle, o luchar con �l. Tan s�lo ev�talo. ";
  ];
ZIPI_Otro ZIPI_Otro27
with
  ZIPI_titulo "Rescatando a Jason",
  ZIPI_ejecutar [;
       print "^Si sigues el rastro de sangre en el suelo llegar�s hasta Jason, que se encuentra ";
       print "^atrapado en una vaina viscosa. Pero para ganar tiempo, vamos a ir antes al ";
       print "^laboratorio. Sur, este, sur, sur, oeste, abajo, este y sur. En el laboratorio, ";
       print "^examina las estanter�as y coge el bistur� l�ser. Ahora ve a la enfermer�a a recoger ";
       print "^la jeringa de adrenalina (luego la necesitar�s). Norte, norte y este. En la ";
       print "^enfermer�a, examina todos los cajones, abre el caj�n y saca la jeringa. Oeste, sur, ";
       print "^oeste, abajo, este, arriba y este. Llegas a la sala este de ventilaci�n. En un hueco ";
       print "^abierto en el techo la vaina viscosa donde se encuentra Jason. Corta la vaina con el ";
       print "^bistur� l�ser y saca a Jason. En unos 7 u 8 turnos, Jason caer� al suelo ";
       print "^inconsciente. En ese momento, cl�vale la inyecci�n de adrenalina y se recuperar�. ";
  ];
ZIPI_Otro ZIPI_Otro28
with
  ZIPI_titulo "Investigando",
  ZIPI_ejecutar [;
       print "^Si ahora intentaras salir por la puerta del complejo, comprobar�as que el monstruo la ";
       print "^ha sellado, as� que tienes que buscar otra salida. Desde la sala donde encontraste a ";
       print "^Jason, vete al oeste, abajo, oeste, arriba, oeste y sur. Llegar�s a la sala de ";
       print "^seguridad. All� ver�s una consola de control con una pantalla y un teclado. Si pulsas ";
       print "^el bot�n ~Reproducir~ ver�s las grabaciones de las c�maras de seguridad de la oficina ";
       print "^y el laboratorio. Descubrir�s que, en la oficina, hay una caja fuerte detr�s de un ";
       print "^cuadro. La combinaci�n es 111582. En la grabaci�n de seguridad del laboratorio ";
       print "^comprobar�s que el monstruo era un esp�cimen en estudio que luego escap�, sembrando ";
       print "^caos y muerte. Hay que hacer estallar todo esto. ";
  ];
ZIPI_Otro ZIPI_Otro29
with
  ZIPI_titulo "El contenido de la caja fuerte",
  ZIPI_ejecutar [;
       print "^Desde la sala de seguridad, si seguimos los cables llegar�s a la oficina y al ";
       print "^laboratorio. Ahora s�lo nos interesa la oficina, as� que vete al norte, este, ";
       print "^arriba, oeste, norte y oeste. Ya en la oficina, quita el cuadro y ver�s la caja ";
       print "^fuerte. Teclea la combinaci�n 111582 y abre la caja fuerte, donde encontrar�s una ";
       print "^tarjeta y un holocubo. Recoge ambas cosas y dir�gete al aula, donde proyectar�s ";
       print "^el interior del holocubo. Este, norte, este, este y este, y estar�s en el aula. ";
       print "^Coloca el holocubo en el proyector, enci�ndelo y examina la pantalla. As� ";
       print "^aprender�s c�mo activar el protocolo de emergencia. �Cuidado! En ese momento, el ";
       print "^monstruo ir� a ti (por aquello de darle emoci�n a la cosa), as� que tendr�s que ";
       print "^ser r�pido. Otra cosa que puedes hacer es, sencillamente, no examinar la pantalla ";
       print "^(toda la informaci�n que necesitas est� aqu�). ";
  ];
ZIPI_Otro ZIPI_Otro30
with
  ZIPI_titulo "La zona de emergencia",
  ZIPI_ejecutar [;
       print "^Desde el aula vete al oeste, sur, sur, oeste y abajo. Mete la tarjeta en la ranura y ";
       print "^entra por la puerta. Estar�s en el pasillo de emergencia. Cierra la puerta por ";
       print "^dentro, pero antes comprueba que Jason est� contigo y que el monstruo se queda fuera. ";
       print "^Vete al este y dile a Jason que se quede all�. Vete al oeste y de nuevo al oeste. ";
       print "^As�, estar�is cada uno en una sala de emergencia y delante de un bot�n. Dile a Jason ";
       print "^que pulse el bot�n, e inmediatamente despu�s pulsa t� el que tienes delante. Se ";
       print "^activar� la autodestrucci�n. Tienes diez minutos para escapar (hay tiempo de sobra si ";
       print "^no te demoras). ";
  ];
ZIPI_Otro ZIPI_Otro31
with
  ZIPI_titulo "La huida final",
  ZIPI_ejecutar [;
       print "^Dile a Jason que te siga para que te d� el encuentro. Este, abre la puerta y sal. ";
       print "^Baja y vete al oeste. All� estar� el ascensor de emergencia. Estar� abierto porque ";
       print "^hemos activado la autodestrucci�n. Entra en el ascensor (aseg�rate de que Jason est� ";
       print "^contigo, y sigui�ndote) y lograr�s salir (por los pelos) del complejo. Saldr�is al ";
       print "^exterior, en la localidad donde encontraste al robot al comienzo de la aventura. ";
       print "^Norte, pide a Madre que abra la compuerta de la nave, y entra. Y prep�rate... ";
       print "^^";
       print "******** FIN ******** ";
       print "^^";
  ];


[ ZIPI_Intro;
  print "Despl�zate con las flechas del cursor. Pulsa ", (s_in) "Enter", " para seleccionar, ", (s_in) "P", " para continuar, o ", (s_in) "Q", " para salir.";
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
