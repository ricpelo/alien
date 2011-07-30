! Decir.h --- Decir ambiguo
! Versión 2.0 Biplataforma
!
! 6/Mayo/1999     primera versión
! 17/Octubre/2000 versión biplataforma 
! (c) Zak McKraken
!
! NOTA: La versión biplataforma es 100% idéntica a la original.
! No se requieren modificaciones. No obstante, la publico como
! una "versión 2 biplataforma" para evitar dudas.
!
! Esta mini librería implementa la acción Decir que se generará cuando
! el jugador  ponga "DI LO QUE SEA", sin referirse a ninguna criatura
! en particular.
!
! Debe incluirse detrás de "Gramatica.h"
!
! El comando "DI ALGO" sin especificar a quién, generará la acción
! DECIR y dejará preparadas las variables consultar_desde y
! consultar_num_palabras (lo cual significa que es compatible con la
! librería ETemas). No será llamada la rutina antes de ningún objeto
! para esta acción, pero el programador puede capturarla en la rutina
! reaccionar_antes.  
!
! Si el programador no modifica su juego, (es decir, si no captura la
! acción Decir) simplemente por el hecho de incluir esta libreria 
! ya obtendrá el siguiente comportamiento:
!
! 1) Si el jugador pone "DI HOLA" en una habitación en la que sólo hay
! un PNJ (o un objeto hablable), se generará la acción Responder sobre
! ese objeto, lo mismo que si hubiera puesto "DI HOLA A MANOLO".
!
! 2) Si hay más de un PNJ u objeto hablable, aparece el mensaje
! "Hablas, pero nadie te hace caso. Quizás debas dirigirte a alguien
! en particular".
!
! 3) Si no hay nadie con quién hablar, aparece el mensaje "Aqui no hay
! nadie que pueda escucharte".
!
! Por otro lado, el programador puede capturar la acción Decir en
! la rutina antes de cualquier PNJ u objeto hablable, para hacer que
! "escuche" cuando el jugador habla cerca. (también puede escuchar lo
! que habla con otro PNJ si captura las acciones Responder, Preguntar
! y Hablar)
!
! Ejemplo (que usaría la librería ETemas):
!
! Object Manolo "Manolo"
! with nombre 'manolo'
!      reaccionar_antes [ tema;
!         Decir: tema=AveriguarTema(Temas);
!             switch(tema){
!               hola: "Manolo apenas levanta la vista ante tu
!                      saludo.";
!               tema_manolo: "Manolo te mira perplejo por un
!                      momento.";
!               adios: "Manolo te mira para comprobar que te vas.";
!               }
!         ],
!  has animado;
!
! Reaccionando antes a la acción Decir se capturan las frases
! "lanzadas al aire" por el jugador. Recordar que sin embargo, las
! frases dirigidas a alquien en concreto producen la acción Responder.
!
!

Global HayAlguien;    ! Contador de cuántos hablables hay en las cercanías
Global QuienHay;      ! Uno de ellos (el último encontrado)


! La siguiente rutina recibe un objeto y debe contarlo como hablable
! si es un personaje o un objeto hablable distinto del jugador.
[ EresAlguien obj;
    if (obj==jugador) return;
    if (obj has animado || obj has hablable) {
	QuienHay=obj;
	HayAlguien++;
    }
];


! Rutina por defecto para la acción Decir
! Se ejecuta si el programador no ha capturado esta acción en
! reaccionar_antes (o si ha retornado false tras capturarla).
!
! Averigua cuántos PNJ hay en la estancia y actúa de forma acorde.
!
[ DecirSub ;
    HayAlguien=0;
    BucleAlcance(EresAlguien);
    if (HayAlguien==1)
    {
	print "[", (al) QuienHay, "]^";
	<<Responder 0 QuienHay>>;
    }
    else if (HayAlguien>1)	
    	"Hablas pero nadie te hace caso. Quizás debas dirigirte a alguien
	en particular.";
    else "Aqui no hay nadie que pueda escucharte.";
];


! Esta rutina es usada por el parser para determinar dónde termina la
! frase que el jugador pone tras DI. La frase termina, bien con la
! última palabra, o bien con la última aparición de la preposición
! 'a', para distinguir DI HOLA de DI HOLA A MANOLO (esto implica
! también que la frase usada por el jugador no puede usar esta
! preposición, como p. ej: DI VETE A LA PORRA). Para este caso debe
! especificar con quién habla: DI VETE A LA PORRA A MANOLO
[ frase w ultima;
    consultar_desde = np;
    ultima=0;
    do {
	w=SiguientePalabraParar();
#Ifdef DEBUG;
        if (parser_trace > 6) {
           print "[frase: ";
           if (w~=0 or -1) print (address) w;
           else print "NULL";
           print "]^";
        } 
#Endif;
	if (w=='a//') ultima=np;
    } until (w==-1);
#Ifdef DEBUG;
    if (parser_trace > 6) print "[frase: ultima palabra de la frase=", ultima -1,"]^";
#Endif;
    if (ultima==0)
    	np--;
    else 
	np=ultima-1;
    consultar_num_palabras=np-consultar_desde;
#Ifdef DEBUG;
    if (parser_trace > 6) 
       print "[frase: contiene ", consultar_num_palabras," palabras]^";
#Endif;
    if (consultar_num_palabras==0) return -1;
    return 1;
];


! Nueva gramática del verbo "DI" (y sus sinónimos "GRITA" y "RESPONDE"
!
Extend 'di' replace
    * frase				-> Decir
    * 'a//' creature topic		-> Responder reverse
    * frase 'a//' creature		-> Responder;

