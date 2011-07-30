! Efectos.h
! (c) 2000 Zak McKracken
! 
! Efectos de sonido para la máquina Glulx
!
! Este módulo define dos canales de sonido y se ocupa de su
! inicialización y gestión, proporcionando rutinas de alto nivel para
! simplificar el acceso al sonido desde los juegos. El interfaz se
! gestiona a través de un objeto llamado EfectosSonoros; el
! programador debe usar llamadas a las propiedades de este objeto para
! activar y desactivar el sonido.
!

#ifndef TARGET_GLULX;
Message fatalerror "El modulo de efectos de sonido solo funciona para
 la maquina Glulx (compilar con opcion -G)"; 
#endif;

System_file;

Constant GG_CANAL_EFECTOS_ROCA 510;
Constant SONIDO_BUCLE_INFINITO -1;

Object EfectosSonoros
 with 	gg_canales 0 0 0 0 0 0 0 0, ! Uso interno
 	sonando_efecto 0 0 0 0 0 0 0 0,  
              ! Numero del sonido que debe sonar en cada canal
 	rep_efecto 0 0 0 0 0 0 0 0 0,     ! Loop de cada canal
	volumen_canal 0 0 0 0 0 0 0 0,    ! volumen de cada canal
        n_canales 2,
 	NoSonido false,     ! ¿Soporta sonido el intérprete?

	! La siguiente rutina debe ser llamada desde
	! IdentifyGlkObjects mediante:
	! EfectosSonoros.IdentifyGlk(fase);
   	IdentifyGlk [ fase id i;
    	    if (self.NoSonido) return;
    	    if (fase == 0) {
      		! Poner  a 0 las referencias a objetos glk
		for (i=0:i<self.n_canales:i++)
		    self.&gg_canales-->i = 0;
        	return;
    	    }
    	    if (fase == 1) {
		! Relacionado con ventanas, streams y ficheros
		! No hay nada qué hacer, aqui
        	return;
    	    }
    	    if (fase == 2) {
		! Inicialización de los objetos gg_ que apuntan a canales de
		! sonido
        	id = glk(240, 0, gg_arguments); ! schannel_iterate
        	while (id) {
		    for (i=0:i<self.n_canales:i++) 
		    {
			if (gg_arguments-->0==GG_CANAL_EFECTOS_ROCA+i)
			{
			    self.&gg_canales-->i = id;
			}
		    }
            	    id = glk(240, id, gg_arguments); ! schannel_iterate
        	}
		
        	! Ahora llamamos a ActualizarCanales, para que empiece a
		! sonar la música indicada por la propiedad sonand_efecto
		! No pienses que estas variables tienen que tener
		! el valor cero en este punto, pues puede ser que estemos aqui
		! porque el jugador acaba de hacer un comando LOAD, cargando
		! un estado previo del juego en el que habia sonidos activos
        	self.ActualizarCanales(true); ! (c) Alpha (el parámetro true)
    	    }
	],

	! La siguiente rutina debe ser llamada desde el Inicializar
	! del juego, mediante
	! EfectosSonoros.InicializarCanales();
	InicializarCanales [ num
	    i res;
    	    ! Averiguemos antes si el intérprete soporta sonido
    	    res=glk(4,8,0);  ! gestalt sound
    	    if (res==0) 
    	    {
		self.NoSonido = true;
		"[Tu intérprete no tiene soporte de sonido. No podrás escuchar
		los efectos sonoros.]^";
    	    }
	    if (num==0) num = 1;
	    self.n_canales=num;
	    for (i=0:i<self.n_canales:i++)
		self.&gg_canales-->i = glk(242, GG_CANAL_EFECTOS_ROCA+i);
	],

	! Para activar un efecto en el canal N (se desactivará el
	! efecto que estuviera sonando en él). Recibe como parámetro
	! el número de efecto y el número de repeticiones. Finalmente,
	! el número de canal. Si se omite el canal, se asume el 0. Si
	! se omiten "repeticiones" y "canal" se asume
	! "repeticiones=1", "canal=0"
 	ActivarEfecto [efecto rep canal;
    	    self.&sonando_efecto-->canal=efecto;
    	    if (rep) self.&rep_efecto-->canal=rep;
	    else self.&rep_efecto-->canal=1;
    	    return self.ActualizarCanal(canal);
	],
	! Apaga el sonido en el canal N. Si se omite N se toma 0
	DesactivarEfecto [canal;
	    self.&sonando_efecto-->canal = -1;
    	    return self.ActualizarCanal(canal);
	],
	! Apaga todo sonido
	DesactivarSonidos [ i;
	    for (i=0:i<self.n_canales:i++) self.DesactivarEfecto(i);
	    self.NoSonido = true;
	],
	! Reactiva el sonido
	ActivarSonidos [;
	    self.NoSonido=false;
	    self.InicializarCanales();
	],
	! Cambia el volumen de un canal
	Volumen [vol canal;
	    if (self.NoSonido) return;
	    if (self.&gg_canales-->canal)
	    {
		if (self.&sonando_efecto-->canal >= 0)
		{
		    self.&volumen_canal-->canal = vol;
		    return glk(251, self.&gg_canales-->canal, vol);
		    ! set_volume
		}
	    }
	],
	! Actualiza el canal dado de modo que ejecute el sonido
	! almacenado en la propiedad correspondiente. Si se omite el
	! canal se toma 0
	ActualizarCanal [canal;
	    
	    if (self.NoSonido) return;
	    if (self.&gg_canales-->canal)
	    {
	    	if (self.&sonando_efecto-->canal == -1) 
		    ! Parar el sonido de ese canal
		    return glk(250, self.&gg_canales-->canal);
	    	else 
		{
		    ! Fijar volumen para ese canal
		    self.Volumen(self.&volumen_canal-->canal, canal);
		    ! Poner a sonar ese canal
		    return glk(249, self.&gg_canales-->canal,
			       self.&sonando_efecto-->canal,
			       self.&rep_efecto-->canal, 0);
		}
	    }
	],
	! Actualiza todos los canales de sonido
	ActualizarCanales [ flag i;
	    for (i=0:i<self.n_canales:i++)
              if (flag && i == CANAL_FONDO or CANAL_DETECTOR)   ! (c) Alpha
		self.ActualizarCanal(i);
	];

#ifndef IdentifyGlkObject;
! La siguiente función es llamada por InformATE cada vez que el 
! juego es reiniciado o una partida es cargada del disco. Se
! trata de asignar a las variables gg_* que identifican a los
! objetos Glk los valores adecuados.
!
! Lee la "Guia Glulx para programadores de Inform" para
! detalles de qué debe hacer esta rutina
!
! En este caso particular, en el que no hay objetos Glk salvo los
! canales de sonido, todo resulta muy sencillo. Basta llamar a una
! rutina del objeto EfectosSonoros para que él se ocupe de inicializar
! todo
!
! Esta rutina se usará sólo en caso de que el programador no haya
! suministrado una propia. Si el programador escribe su propia
! IdentifyGlkObject debe ocuparse de llamar desde ella a
! EfectosSonoros.IdentifyGlk(fase)
!
[ IdentifyGlkObject fase tipo ref ROCA res;

    EfectosSonoros.IdentifyGlk(fase);

    ! Para evitar warnings de parámetros no utilizados
    tipo=tipo+ref+ROCA+res;
];
#endif;

		

    
