!
! ETEMAS   Otro enfoque para el parsing de Temas de conversacion
! Versión 2.0 biplataforma
!
!
!  Para uso con Inform 6.15 Librería 6/7E  (InformATE!)
!  o con Inform 6.21 Librería 6/10E (InformATE!)
!  (c) 1999-2000 Zak McKraken  (6/Mayo/1999, 17/Octubre/2000)
!
! USO:
!
!  1) Incluir este fichero en cualquier punto después del "Eparser.h"
!  2) Definir, (después de esta inclusión) tantos objetos "Temas-raiz"
!  como se quiera, por ejemplo:
!   Object TemasVoxPopuli;
!   Object TemasdeManolo;
!   Object Secretos;
!
!  3) Definir objetos dentro de los objetos anteriores, cada uno de
!  ellos con su propiedad 'nombre' que son las palabras que el jugador
!  puede usar para referirse a ese tema (no es necesario especificar
!  artículos o 'de').
!
!  Cada Tema puede tener activado el atributo "parsing_estricto" que
!  indica que a la hora de "encajar" ese tema, *todas* las palabras
!  escritas por el jugador deben encajar con palabras de la propiedad
!  'nombre', y en el mismo orden. También puede tener el atributo
!  "parsing_normal", según el cual su nombre se "parsea" como el de
!  cualquier otro objeto. Si no tiene activado ninguno de estos
!  atributos, el encaje se hará de forma más flexible: Cuantas más
!  palabras de las escritas por el jugador encajen con el nombre, mejor;
!  pero las que no encajen se ignoran sin más.
!
!  Por ejemplo:
!    Object tiempo_atmosferico "el tiempo" TemasVoxPopuli
!    with nombre 'buen' 'tiempo' 'llover' 'sol' 'calor' 'frio';
!
!    Object euro "el euro" TemasVoxPopuli
!    with nombre 'euro';
!
!  4) La propiedad vida de los PNJ, en el apartado de Responder,
!  Preguntar o Hablar deben llamar a la función AveriguarTema(),
!  pasándole como parámetro la colección de temas en la que buscar. El
!  valor retornado es el tema de conversación más probable a partir de
!  las palabras escritas por el jugador. Por ejemplo:
!
!     tema=AveriguarTema(TemasVoxPopuli);
!     switch(tema) {
!       tiempo_atmosferico: "Creo que va a llover";
!       euro: "Es la nueva moneda, creo.";
!       default: "No sé nada de eso";
!      }
!
!  Así, el juego admitirá:
!  > PREGUNTA A MANOLO SOBRE EL TIEMPO
!  > MANOLO, PARECE QUE HACE SOL
!  > PREGUNTA A MANOLO POR EL CAMBIO DEL EURO
!
! Estas preguntas sólo llevarán al tema "tiempo" y "euro" con el
! parsing flexible usado por defecto. Con el parsing normal, la
! primera sería comprendida (pues 'tiempo' está en la lista de
! palabras de un tema), pero las otras dos no (porque 'parece' y
! 'cambio' no están en la lista de palabras de ningun
! tema). Finalmente, con parsing_estricto no sería comprendida ninguna
! de las frases, pues aunque 'tiempo' está en la lista de palabras de
! un tema, no es su primera palabra. Con parsing estricto sólo sería
! comprendido:
!
!  > PREGUNTA A MANOLO SOBRE EL BUEN TIEMPO 
!  > PREGUNTA A MANOLO POR EL EURO
!

#ifndef WORDSIZE;      ! Para compatibilidad con Inform 6.15
Constant WORDSIZE= 2;
Constant TARGET_ZCODE;
#endif;

Attribute parsing_estricto alias hablable;
Attribute parsing_normal alias ausente;
! Uso alias de otros atributos existentes, para no definir nuevos ya
! que el número de atributos máximo de la máquina Z es limitado, y
! después de todo un Tema no necesita los atributos talkable ni absent.


! Simplemente cuenta cuántas palabras de las del topic encajan en el
! obj dado (las que no encajan se ignoran sin más, a diferencia de
! InterpretarNombre, que deja de contar tan pronto como llega a una
! palabra no reconocida)
[ FlexibleInterpretarNombre obj i w n;
#Ifdef DEBUG;
    if (parser_trace>=5) print "[ FlexibleInterpretarNombre: llamado
	para objeto ~",(_nombre_)obj, "~^  Tratando de encajar ",
	consultar_num_palabras, " palabras, empezando en la ",np,": ";
#Endif;
    for (i=0:i<consultar_num_palabras:i++)
    {
    	w=SiguientePalabraParar();
	if (PalabraEnPropiedad(w, obj, nombre)) n++;
    }
#Ifdef DEBUG;
    if (parser_trace>=5) print n, " palabras encajadas]^";
#Endif;
!    if (n<consultar_num_palabras) return 0;
    return n;
];

[ MoreStrictInterpretarNombre obj i w listanombres n_nombres;
    listanombres=obj.&nombre;
    n_nombres=(obj.#nombre)/WORDSIZE;
    if (n_nombres<consultar_num_palabras) return 0;
    for (i=0:i<consultar_num_palabras:i++)
    {
	w=SiguientePalabraParar();
	if (w~=listanombres-->i) return i;
    }
    return i;
];

       
	

[ AveriguarTema T i n k max tmax;
    max=0;  ! La mejor puntuación de momento
    tmax=0; ! El objeto correspondiente a esta puntuación
    k=np;
    objectloop (i in T) { !Buscar entre los temas dados
      	np=consultar_desde;  !Empezando por la primera palabra
	if (i provides parse_nombre) ! Si el tema tiene su propio
	                           ! parse_nombre, lo llamamos
	    n=ValorOEjecutar(parse_nombre);
	else
	    if (i has parsing_estricto) ! Si se solicita parsing estricto
	    n=MoreStrictInterpretarNombre(i);
	else
	    if (i hasnt parsing_normal) ! Si no se solicta el parser
		                        ! normal, se hace flexible
		n=FlexibleInterpretarNombre(i);
	else n=InterpretarNombre(i);
	! De lo contrario, el InterpretarNombre normal
	if (n>max) 
	{
	    max=n;                 ! Actualizar máximos
	    tmax=i;
	}
    }
#Ifdef DEBUG;
    if (parser_trace>=4) print "[ AveriguarTema ha detectado ~", (_nombre_)
	tmax, "~ (", tmax, ") como posible tema, con puntuación ",
	    max, " ]^";
#Endif;
    np=k;
    return(tmax);     ! Y retornar el mejor hallado
                      ! Observar que no hay intento de aclarar
                      ! ambigüedades si dos o más coincidieran en
                      ! puntuación 
];
