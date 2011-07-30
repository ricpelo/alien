! -
! PNJMovil v9. Una librería que proporciona movimiento aleatorio,
! dirigido e "inteligente" para PNJs.
!
! Versión 9.0  biplataforma Z/GLulx
! [Version 8.01, written by Neil Brown      neil@highmount.demon.co.uk
!                      and Alan Trewartha    alan@alant.demon.co.uk
! ]
!
! Adaptación para InformATE 6/10 biplataforma de Zak McKraken
! 18 de Octubre 2000
!
! Las funciones de esta librería son demasiado complejas para
! explicarlas aquí, por favor, consulta el breve manual que acompaña a
! este fichero (llamado "movilman.txt")
!
! También se acompaña una mini-demo que contiene algunos personajes
! móviles
! 
! Si tu programa usa la librería PERSEGUIR.H (cosa poco probable ya
! que no existe todavía en su versión InformatE), deberás incluir
! PNJMovil después de PERSEGUIR. Si no, pueden ocurrir errores
! -

#ifndef WORDSIZE;       ! Para compatibilidad con Inform 6.15
Constant WORDSIZE = 2;
Constant TARGET_ZCODE;
#endif;

System_file;

Message "!! Compilando la ampliacion PNJMovil !!";

Attribute en_ruta;
Property  pnj_abrir;
Property  accion_despues;
Property  accion_antes;
Property  capricho  alias  tiempo_restante;
Global    max_longitud_camino = 10;

Constant   MOVIMIENTO_ALEATORIO = 0; ! Los tipos de movimiento
Constant    MOVIMIENTO_POR_META = 1;
Constant     MOVIMIENTO_NINGUNO = 2;
Constant   MOVIMIENTO_PREFIJADO = 3;

Constant   CAMINO_CUALQUIERA = $$00000000; ! Los tipos de camino para
                                           ! MOVIMIENTO_POR_METAs
Constant CAMINO_SIN_CERROJOS = $$00001000; ! En principio pueden
Constant      CAMINO_ABIERTO = $$00010000; ! combinarse
Constant  CAMINO_SIN_PUERTAS = $$00100000;


Ifndef Lugar;
Class 	Lugar
 with 	cantidad;
EndIf;


Class 	PNJMovil
 with 	tipo_de_movimiento
       	    MOVIMIENTO_ALEATORIO, ! Por defecto se mueve aleatoriamente
       	capricho      20, ! Probabilidad de moverse en un turno
       	pnj_dirs 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0,
	! Las direcciones (calculadas) que el pnj tomará
       	nombre_precamino  0, ! El nombre del array con el camino prefijado
       	longitud_precamino  0, ! La longitud de ese array
       	estado_pnj     0, ! Posición en el array de direcciones
       	objetivo_pnj,      ! El destino deseado
       	pnj_bloqueado [; PNJ_Ruta(self,MOVIMIENTO_ALEATORIO); ],
	! También se podría esperar a que el camino se
	! desbloquee, o mejor aún, buscar una ruta
	! alternativa 
       	pnj_sibloqueado 0, ! No se usa, puede usarla el programador
       	pnj_ha_llegado [; PNJ_Ruta(self,MOVIMIENTO_ALEATORIO); ],
	! ¿Qué ocurre cuando el PNJ llega a su meta?
       	marcha "se marcha",
       	llega  "llega",
       	accion_seguir,   ! } Por si se usa PERSEGUIR.H
       	objeto_seguir,   ! } 
       	daemon [ i n k;
            if (EjecutarRutinas(self,accion_antes)) rtrue;
	    ! Si esta rutina retorna true, ya no tendrá
	    ! lugar el movimiento del PNJ en este turno
	    
            switch(self.tipo_de_movimiento) {
	     0, MOVIMIENTO_ALEATORIO: 
#ifdef DEBUG;
		if (parser_trace>1)
		    print "[MOVIMIENTO_ALEATORIO daemon ", (del) self ,"]^";
#endif;
                if (random(100)>=self.capricho) {
		    #ifdef DEBUG;
		    if (parser_trace>1) print "[",(The) self, " decide
			no moverse.]^";
		    #endif;
    		    rfalse;
		}
                objectloop (i in brujula)
    		    if (ConduceA(i,parent(self),CAMINO_CUALQUIERA))
    		    {  n++;
			#ifdef DEBUG;
			if (parser_trace>1)
	    		    print "[Alternativa ",n, ": ",(DirDada) i ,"]^";
#endif;
        	    }                
              	if (n==0) rfalse;
              	k=random(n); n=0;
#ifdef DEBUG;
		if (parser_trace>1)
		    print "[Elige ",k, "]^";
#endif;
              	objectloop (i in brujula)
              	{
		    if (ConduceA(i,parent(self),CAMINO_CUALQUIERA)) n++;
                    if (n==k)
                    {
			MoverPNJDir(self,i);
                   	break;
                    }
              	}
		
             1, MOVIMIENTO_POR_META : 
              	i=self.&pnj_dirs-->self.estado_pnj;
#ifdef DEBUG;
		if (parser_trace>1)
		    print "[MOVIMIENTO_POR_META daemon ",
			(del) self, " ", (DirDada) i,"]^";
#endif;
              	if (i==0  || MoverPNJDir(self,i))
		    ! Truco: la rutina solo se llama si i~=0
                    self.estado_pnj++;
              	if (parent(self)==self.objetivo_pnj)
                    self.pnj_ha_llegado();
              	
             2, MOVIMIENTO_NINGUNO : ! No se mueve
		#ifdef DEBUG;
		if (parser_trace>1)
		    print "[MOVIMIENTO_NINGUNO daemon ", (del) self, ".]^";
#endif;
		
	     3, MOVIMIENTO_PREFIJADO :
    		i=(self.nombre_precamino)-->self.estado_pnj;
		#ifdef DEBUG;
		if (parser_trace>1)
		    print "[MOVIMIENTO_PREFIJADO daemon ",
			(del) self," ", (DirDada) i, "]^";
#endif;
		if (i==0 ||MoverPNJDir(self,i)) 
		    ! Truco: la rutina solo se llama si i~=0
    		    self.estado_pnj++;
              	if (self.estado_pnj>=self.longitud_precamino)
                    self.pnj_ha_llegado();
            	
       	     default: "** Error PNJMovil: tipo_de_movimiento no válido
		para", (el) self, " **";
            }
        ];

     
[ PNJ_Ruta
    pnj tipo_movimiento LugarObjetivo tipo_ruta pasos i j k encontrado;
    
!    if (metaclass(tipo_movimiento)==Object && tipo_movimiento ofclass Lugar)
!    {   tipo_ruta=LugarObjetivo;
!      	LugarObjetivo=tipo_movimiento;
!      	tipo_movimiento=MOVIMIENTO_POR_META;
! To stay compatible with old code
!    }
#ifdef DEBUG;
    if (parser_trace>1)
    {print "[PNJ_Ruta pone ", (al) self," ";
 	switch (tipo_movimiento)
     	{
	 MOVIMIENTO_NINGUNO: print "MOVIMIENTO_NINGUNO";
   	 MOVIMIENTO_ALEATORIO: print "MOVIMIENTO_ALEATORIO";
   	 MOVIMIENTO_PREFIJADO: print "MOVIMIENTO_PREFIJADO";
    	 MOVIMIENTO_POR_META: print "MOVIMIENTO_POR_META";
       	 default: print "**UNDEFINED**";
 	}
 	print "]^";
    }
#endif;
    if (tipo_movimiento==MOVIMIENTO_NINGUNO)
    {
	pnj.tipo_de_movimiento=MOVIMIENTO_NINGUNO;
    	rtrue;
    }
    
    if (tipo_movimiento==MOVIMIENTO_ALEATORIO)
    {
	pnj.tipo_de_movimiento=MOVIMIENTO_ALEATORIO;
     	if (LugarObjetivo~=0)
            pnj.capricho=LugarObjetivo;
     	rtrue;
    }
    
    if (tipo_movimiento==MOVIMIENTO_PREFIJADO)
     	return PNJpreruta(pnj,LugarObjetivo,tipo_ruta);
    
    if (tipo_movimiento~=MOVIMIENTO_POR_META)
     	rfalse;
    
    ! Sólo se pueden calcular rutas desde un lugar de la clase Lugar a
    ! otro de la misma clase, así que...
    if (~~(parent(pnj) ofclass Lugar) || parent(pnj)==LugarObjetivo)
      	rfalse;
    objectloop (i ofclass Lugar)
    {
	i.cantidad=0;         
     	give i ~en_ruta;      ! Resetear todos los lugares
    }
    ! Algoritmo: partiendo del lugar inicial, numeramos cada lugar por
    ! el que pasamos con el número de pasos necesario para alcanzarlo,
    ! hasta que alcancemos el lugar objetivo
    parent(pnj).cantidad=1;
    give parent(pnj) en_ruta;
    for (pasos=1: pasos<max_longitud_camino:pasos++)
    {
	objectloop (i has en_ruta)
    	{
	    if (i.cantidad==pasos)
    	    {
		objectloop (j in Brujula)
    		{
		    k=ConduceA(j,i,tipo_ruta);
		    if (k ofclass Lugar)
		    {
			give k en_ruta;
            		if (k.cantidad==0)
            		{
			    k.cantidad=pasos+1;
#ifdef DEBUG;
			    if (parser_trace>1)
		    		print "[",(name) k, " es ", pasos+1, "]^";
#endif;
	    		}
    	    		if (k==LugarObjetivo)  encontrado=true;
		    }
		    if (encontrado) break;
    		}
    	    }
      	    if (encontrado) break;    
    	}
    	if (encontrado) break;
    }
    if (encontrado==false) rfalse; ! hemos alcanzado la máxima longitud
    
    objectloop(i has en_ruta)
    	if (i.cantidad>pasos && i~=LugarObjetivo)
    	{
	    i.cantidad=0;        ! Los lugares que están a igual distancia
      	    give i ~en_ruta;   ! que el objetivo, no son interesantes
    	}
    
    pnj.estado_pnj=0;
    pnj.tipo_de_movimiento=MOVIMIENTO_POR_META;
    pnj.objetivo_pnj=LugarObjetivo;
    pnj.longitud_precamino=pasos;
    
#ifdef DEBUG;
    if (parser_trace>1)
	print "[Encontrado un camino de ",pasos,
	    " pasos. Recorriendolo hacia atrás desde ...^",
	    (name) LugarObjetivo;
#endif;
    
    for ( :pasos>0:pasos--)  ! Retroceder paso a paso
    {
	encontrado=false;   ! buscando un lugar interesante que lleve
	! hasta el lugar interesante que estaba en 'paso+1' 
    	objectloop(i has en_ruta)  
    	{
	    if (i.cantidad==pasos)
      	    {
		objectloop (j in Brujula)
        	{
		    k=ConduceA(j,i,tipo_ruta);
            	    if (k has en_ruta && k.cantidad==pasos+1)
			encontrado=true;
            	    if (encontrado) break;
        	}
      	    }
      	    if (encontrado) break;
    	}
	
#ifdef DEBUG;
	if (parser_trace>1)
	    print " está...^", (DirDada) j, " ", (del) i, ", el cual";
#endif;

    	pnj.&pnj_dirs-->(k.cantidad-2)=j;  
    	objectloop(k has en_ruta)  ! Otros lugares con el mismo número
 	                           ! no son interesantes
      	    if (k.cantidad==pasos && i~=k)
      	    {
		k.cantidad=0;
        	give k ~en_ruta;
      	    }
    }
    
#ifdef DEBUG;
    if (parser_trace>1)
	print " es el punto de partida!]^";
#endif;
    
    rtrue;
];



[ PNJpreruta pnj array_ruta longitud_ruta fakevar;
  fakevar=fakevar;            ! por si se le llama pasandole un lugar
  if (pnj ofclass PNJMovil)
  { pnj.estado_pnj=0;
    pnj.tipo_de_movimiento=MOVIMIENTO_PREFIJADO;
    pnj.nombre_precamino=array_ruta;
    pnj.longitud_precamino=longitud_ruta;
  }
  else
  { "*** PNJMovil Error: PNJpreruta ha sido llamado para el objeto
      no-PNJMovil '",
     (el) pnj, "' ***";
  }
];



[ ConduceA direccion estelugar tipo_ruta k tmp tmp2;
!    print "-ConduceA: ", (name) direccion, ":";
    if (~~(estelugar provides direccion.direcc_puerta))
    {
!	print "NO HAY^";
	return 0;
    }
    k=estelugar.(direccion.direcc_puerta);
    if (ZRegion(k)==2)
    {
!	print "Rutina que devuelve ";
	k=k();
    }
    if (ZRegion(k)~=1) 
    {
!	print " no se puede pasar^";
	return 0;
    }
    
    if (k has puerta)
    {
!	print " una puerta ";
       	if (tipo_ruta & CAMINO_SIN_PUERTAS) return 0;
       	if ((tipo_ruta & CAMINO_ABIERTO) && k hasnt abierto)
	{
!	    print "cerrada^";
	    return 0;
	}
       	if ((tipo_ruta & CAMINO_SIN_CERROJOS) && k has cerrojoechado)
	{
!	    print "cerrada con llave^";
	    return 0;
	}
       	tmp=parent(k);
       	move k to estelugar;
       	tmp2=k.puerta_a();
       	if (tmp) move k to tmp;
       	k=tmp2;
!	print " que lleva a ";
    }
    
!    print (name) k;
    if (~~(k ofclass Lugar))
    {
!	print " que no es un lugar válido.^";
	return 0;
    }
!    print ".^";
    return k;
];



[ MoverPNJDir amover direccion
  i j p mensaje;
  
  mensaje = 2;
  p = parent(amover);
  i = ConduceA(direccion, p, CAMINO_CUALQUIERA);

  if (i == 0) {
    amover.pnj_bloqueado();
#ifdef DEBUG;
    if (parser_trace > 1)
      print "[MoverPNJDir bloqueado: la dirección no lleva a ningún sitio]^";
#endif;
    rfalse;
  }
    
  j = p.(direccion.direcc_puerta);
  
  if (ZRegion(j) == 2)
    j = j();
    
  if (j has puerta) {
    ! pnj_abrir retorna: 2 para atravesar la puerta normalmente
    !                    1 para atravesar la puerta pero impedir
    !                    que se imprima el texto de
    !                    "marchar/llegar"
    !                    0 para impedir al PNJ que use esa puerta
    if (j provides pnj_abrir) {
      mensaje = j.pnj_abrir(self);

      if (mensaje == false) {
        amover.pnj_bloqueado();
#ifdef DEBUG;
        if (parser_trace > 1)
          print "[MoverPNJDir bloqueado: ", (el) j, "'s pnj_abrir retornó falso]^";
#endif;
        rfalse;
      }
    }	else
      if (j hasnt abierto) {
        amover.pnj_bloqueado();
#ifdef DEBUG;
		    if (parser_trace > 1)
          print "[MoverPNJDir bloqueado: ", (el) j, " está cerrad", (o)j, " y no tiene pnj_abrir]^";
#endif;
        rfalse;
      }
  }
    
  MoverPNJ(amover, i, ##Ir, direccion);
    
  if (p == localizacion && mensaje == 2) {
    if (ZRegion(self.marcha) == 3)  ! Imprimir el texto
      print "^", (The) self, " ", (string) self.marcha, " ", (DirDada) direccion, ".^";
    else
      self.marcha(direccion);
  }
    
  if (parent(self) == localizacion && mensaje == 2) {
    direccion = NULL;
    
    objectloop (i in brujula)
      if (ConduceA(i, localizacion, CAMINO_CUALQUIERA) == p)
        direccion = i;

    if (ZRegion(self.llega) == 3) {
      print "^", (The) self, " ", (string) self.llega;
      
      if (direccion ~= NULL)
        print " desde ",(el) direccion;
        
      print ".^";
    } else
      self.llega(direccion);
  }
    
  if (self provides accion_despues)
    self.accion_despues();

  rtrue;
];



Ifndef MoverPNJ; ! Proporciona un MoverPNJ mínimo si no se ha incluido
                 ! PERSEGUIR.h
[ MoverPNJ amover dest actn objn;
  move amover to dest;
  actn=actn;
  objn=objn;
];
Endif;



[ DirDada i;
    switch(i)
    {
     obj_n: print "hacia el norte";
     obj_s: print "hacia el sur";
     obj_e: print "hacia el este";
     obj_o: print "hacia el oeste";
     obj_ne: print "hacia el noreste";
     obj_no: print "hacia el noroeste";
     obj_se: print "hacia el sureste";
     obj_so: print "hacia el suroeste";
     obj_arriba: print "hacia arriba";
     obj_abajo: print "hacia abajo";
     obj_adentro: print "al interior";
     obj_afuera: print "afuera";
    }
];

