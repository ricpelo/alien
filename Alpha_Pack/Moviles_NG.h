! -
! MOVILES. Una librería que proporciona movimiento aleatorio,
! dirigido e "inteligente" para PNJs, creada a partir de la
! librería PNJMóvil de Zak. Se trata de una versión avanzada,
! y más completa especialmente adaptada para su uso con la
! librería de autómatas.
!
! PNJMovil fue creada y modificada por:
!
!  Version 8.01, written by Neil Brown          neil@highmount.demon.co.uk
!                   and Alan Trewartha      alan@alant.demon.co.uk
!  Adaptación para InformatE de Zak McKraken spinf@geocities.com
!  8 Abril 1999
!
! Móviles fue creada a partir de la anterior por Mel Hython meliton@arrakis.es
! en Agosto del 2000
!
! Pequeñas variantes y correcciones, (c) 2008 Ricardo Pérez (Alpha Aventuras)
!
! -

System_file;

#ifndef WORDSIZE;       ! Para compatibilidad con Inform 6.15
Constant WORDSIZE = 2;
Constant TARGET_ZCODE;
#endif;

!Message "!! Compilando la ampliacion Moviles !!";

!
! Propiedades y atributos necesarios
!
Ifndef en_ruta;
Attribute en_ruta;
Endif;
Ifndef pnj_abrir;
Property pnj_abrir;
Endif;

!
! Maxima profundidad de busqueda
!
Ifndef max_longitud_camino;
Global max_longitud_camino = 10;
Endif;

!
! Tabla para guardar los móviles evitando el objectloop y los
! deamons para moverlos
!
Ifndef maximoNumeroMoviles;
Constant maximoNumeroMoviles = 100; ! Maximo número de móviles
Endif;

!
! Tabla que contiene los moviles
!
Array tablaMoviles table maximoNumeroMoviles;    ! (c) Alpha
Global indiceMoviles = 0;

!
! TIPOS DE MOVIMIENTOS VALIDOS EN MOVILES
!
!  ALEATORIO   - Camino en cualquier dirección cada turno, 
!                puede proporcionarse un % de que se mueva
!                por defecto este % es del 20%. Se puede 
!                indicar un tipo de ruta válida y una zona
!                de movimiento válidos.
!
!  POR_META    - El PNJ se encamina hacia una localización
!                determinada, usando una ruta y una zona válida
!  
!  NINGUNO     - El PNJ permanece detenido
!
!  PREFIJADO   - Se proporciona un camino FIJO por el que el 
!                PNJ debe caminar
!
!  NO_CAMBIAR  - Valor que simplemente lo deja en el mismo estado
!                de movimiento, facilita la creación de librerías
!                con cambio de estado de movimiento por eventos
!
!  PERSEGUIR   - El PNJ intenta alcanzar un objeto, si este objeto
!                pasa a estar en un no-Lugar o fuera de la zona
!                válida el PNJ se llama a pnj_bloqueado y por
!                defecto se para a esperar. Cada vez que se alcanza
!                el objetivo se llama a pnj_ha_llegado
!
!  HUIR        - El PNJ sale corriendo en una dirección al azar
!                cuando está presente el motivo de su huída
!
Constant   MOVIMIENTO_ALEATORIO = 0; ! Los tipos de movimiento
Constant    MOVIMIENTO_POR_META = 1; ! Llegar a un lugar
Constant     MOVIMIENTO_NINGUNO = 2; ! No moverse
Constant   MOVIMIENTO_PREFIJADO = 3; ! Una ruta dada
Constant  MOVIMIENTO_NO_CAMBIAR = 4; ! No cambiar el estado de movimiento
Constant   MOVIMIENTO_PERSEGUIR = 5; ! Intenta llegar hasta un objeto
Constant        MOVIMIENTO_HUIR = 6; ! Intenta alejarse de un objeto

!
! CLASES DE RUTAS VÁLIDAS
!
!  CUALQUIERA   - Todas las conexiones son válidas
!  SIN_CERROJOS - Sólo las puertas NO cerradas con llave
!  ABIERTO   - Sólo puertas NO cerradas
!  SIN_PUERTAS  - Sólo caminos SIN puertas
!
Constant   CAMINO_CUALQUIERA = $$00000000; ! Los tipos de camino para MOVIMIENTO_POR_METAs
Constant CAMINO_SIN_CERROJOS = $$00001000; ! En principio pueden
Constant      CAMINO_ABIERTO = $$00010000; ! combinarse
Constant  CAMINO_SIN_PUERTAS = $$00100000;


!
! Definición de la clase básica Lugar por 
! si no está definida
!
Ifndef Lugar;
class Lugar
  with number;
EndIf;


class Movil
  with
    tipo_de_movimiento MOVIMIENTO_ALEATORIO, ! Por defecto aleatoriamente
    capricho 20,                             ! Probabilidad de moverse en un turno
    ! Las direcciones (calculadas) que el pnj tomará
    pnj_dirs 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0,
    nombre_precamino 0,                      ! El nombre del array con el camino prefijado
    longitud_precamino 0,                    ! La longitud de ese array
    estado_pnj 0,                            ! Posición en el array de direcciones
    objetivo_pnj,                            ! El destino deseado o del que huir
    sentido,                                 ! Sentido del movimiento (c) Alpha
    lugar_objetivo,                          ! Sitio a donde va (c) Alpha
    condicion_movimiento [; rtrue; ],        ! Se mueve si la condición es true (c) Alpha
    perseguido,                              ! El perseguido
    tipoRuta,                                ! Ruta valida para este PNJ
    pnj_bloqueado [; 
      if (self.tipo_de_movimiento ~= MOVIMIENTO_PERSEGUIR)
        PNJ_Ruta(self, MOVIMIENTO_ALEATORIO); 
    ],
    ! También se podría esperar a que el camino se
    ! desbloquee, o mejor aún, buscar una ruta
    ! alternativa 
    pnj_sibloqueado 0,                       ! No se usa, puede usarla el programador
    ! ¿Qué ocurre cuando el PNJ llega a su meta?
    pnj_ha_llegado [; 
#ifdef DEBUG;
      if (parser_trace > 1)
        print "[pnj_ha_llegado por defecto]^";
#endif; 
      if (self.tipo_de_movimiento ~= MOVIMIENTO_PERSEGUIR)
        PNJ_Ruta(self, MOVIMIENTO_ALEATORIO); 
    ],
    ! Gancho de estado para 'Puertas.h'
!   tras_abrir 0,                            (c) Alpha, para que funcione PnjPuertas
    marcha "se marcha",
    llega [ dir;
      print "^", (The) self, " ";
      if (self.tipo_de_movimiento == MOVIMIENTO_PERSEGUIR) {
        if (self.perseguido == player) {
          print "te sigue";
        } else {
          print "sigue ", (al) self.perseguido;
        }
      } else {
        print "llega";
      }
      if (dir ~= NULL) {
        print " desde ", (the) dir;
        print ".^";
      }
    ],
    zonaValida Lugar,                        ! Cualquier 'Lugar' es válido por defecto
    seHaMovido false,                        ! Indica si hace hecho algún movimiento este turno
    accion_antes [; rfalse; ],
    accion_despues [; return; ],
    movimiento [ i n k;
      if (RunRoutines(self, accion_antes))
        rtrue;
        
      ! Si esta rutina retorna true, ya no tendrá lugar el movimiento del PNJ en este turno
      self.seHaMovido = false;
     
      switch (self.tipo_de_movimiento) {
        0, MOVIMIENTO_ALEATORIO, 6, MOVIMIENTO_HUIR: 
#ifdef DEBUG;
          if (parser_trace > 1) {
            if (self.tipo_de_movimiento == MOVIMIENTO_ALEATORIO)
              print "[MOVIMIENTO_ALEATORIO movimiento ", (del) self , "]^";
            else
              print "[MOVIMIENTO_HUIR movimiento para ", (the) self , "]^";
          }
#endif;
          if ((self.tipo_de_movimiento == MOVIMIENTO_ALEATORIO) &&
              (random(100) >= self.capricho)) {
#ifdef DEBUG;
            if (parser_trace > 1)
              print "[", (The) self, " decide no moverse.]^";
#endif;
            rfalse;
          }
      
          if ((self.tipo_de_movimiento == MOVIMIENTO_HUIR) &&
              (parent(self.objetivo_pnj) ~= parent(self))) {
#ifdef DEBUG;
            if (parser_trace > 1)
              print "[", (The) self, " no huye ", (del) self.objetivo_pnj, " porque no está",
                    (n) self.objetivo_pnj, " presente", (s) self.objetivo_pnj, ".]^";
#endif;
            rfalse;
          }
      
          objectloop (i in compass)
            if (ConduceA(i, parent(self), self.tipoRuta, self.zonaValida)) {
              n++;
#ifdef DEBUG;
              if (parser_trace > 1)
                print "[Alternativa ", n, ": ", (DirDada) i , "]^";

#endif;
            }
            
          if (n == 0)
            rfalse;
            
          k = random(n);
          n = 0;

#ifdef DEBUG;
          if (parser_trace > 1)
            print "[Elige ", k, "]^";
#endif;
          objectloop (i in compass) {
            if (ConduceA(i, parent(self), self.tipoRuta, self.zonaValida))
              n++;
            if (n == k) {
              MoverPNJDir(self, i);
              break;
            }
          }

        1, MOVIMIENTO_POR_META, 5, MOVIMIENTO_PERSEGUIR: 
          if (self.tipo_de_movimiento == MOVIMIENTO_PERSEGUIR) {
            if (parent(self) == parent(self.perseguido))
              rfalse;

!            if (parent(self.perseguido) ~= self.objetivo_pnj) {     (c) Alpha - 080810
              if (PNJ_Ruta(self, MOVIMIENTO_POR_META, parent(self.perseguido), self.tipoRuta,
                           self.zonaValida)) {
                self.tipo_de_movimiento = MOVIMIENTO_PERSEGUIR;
              } else {
                self.tipo_de_movimiento = MOVIMIENTO_PERSEGUIR;
                self.objetivo_pnj = 0;
                self.pnj_bloqueado();
                rfalse;
              }
!            }                                                       (c) Alpha - 080810
         }
      
          i = (self.&pnj_dirs)-->(self.estado_pnj);
#ifdef DEBUG;
          if (parser_trace > 1) {
            if (self.tipo_de_movimiento == MOVIMIENTO_POR_META)
              print "[MOVIMIENTO_POR_META movimiento ", (del) self, " ", (DirDada) i, "]^";
           else
              print "[MOVIMIENTO_PERSEGUIR movimiento ", (del) self, " ", (DirDada) i, "]^";
          }
#endif;
          if (i == 0 || MoverPNJDir(self, i))
            ! Truco: la rutina solo se llama si i ~= 0
            self.estado_pnj++;
  
          if (parent(self) == self.objetivo_pnj)
            self.pnj_ha_llegado();
  
        2, MOVIMIENTO_NINGUNO, 4, MOVIMIENTO_NO_CAMBIAR: ! No se mueve
#ifdef DEBUG;
          if (parser_trace > 1)
            print "[MOVIMIENTO_NINGUNO movimiento ", (del) self, ".]^";
#endif;

        3, MOVIMIENTO_PREFIJADO:
          i = (self.nombre_precamino)-->self.estado_pnj;
#ifdef DEBUG;
          if (parser_trace > 1)
            print "[MOVIMIENTO_PREFIJADO movimiento ", (del) self, " ", (DirDada) i, "]^";
#endif;
          if (i == 0 || MoverPNJDir(self, i))
            ! Truco: la rutina solo se llama si i ~= 0
            self.estado_pnj++;
            
          if (self.estado_pnj >= self.longitud_precamino)
            self.pnj_ha_llegado();

        default:
          "** Error Movil: tipo_de_movimiento no válido para", (the) self, " **";
      }
    ];


[ PNJ_Ruta pnj tipo_movimiento LugarObjetivo tipo_ruta zona
  pasos i j k encontrado claseVal;

  !
  ! Si es no cambiar no hacemos nada
  !
  if (tipo_movimiento == MOVIMIENTO_NO_CAMBIAR) {
    rtrue;
  } 
    
  !
  ! Copiamos los valores necesarios
  !
  pnj.tipoRuta = tipo_ruta;
  pnj.lugar_objetivo = LugarObjetivo;                     ! (c) Alpha
  
  if (tipo_movimiento == MOVIMIENTO_PERSEGUIR) {
    pnj.perseguido = LugarObjetivo;
    LugarObjetivo = parent(pnj.perseguido);
    pnj.lugar_objetivo = LugarObjetivo;
    pnj.zonaValida = zona;
    pnj.tipo_de_movimiento = MOVIMIENTO_PERSEGUIR;        ! (c) Alpha
  }

#ifdef DEBUG;
  if (parser_trace > 1) {
   print "[PNJ_Ruta pone ", (al) pnj, " ";
   
   switch (tipo_movimiento) {
     MOVIMIENTO_NINGUNO:    print "MOVIMIENTO_NINGUNO";
     MOVIMIENTO_ALEATORIO:  print "MOVIMIENTO_ALEATORIO";
     MOVIMIENTO_PREFIJADO:  print "MOVIMIENTO_PREFIJADO";
     MOVIMIENTO_POR_META:   print "MOVIMIENTO_POR_META";
     MOVIMIENTO_NO_CAMBIAR: print "MOVIMIENTO_NO_CAMBIAR";
     MOVIMIENTO_PERSEGUIR:  print "MOVIMIENTO_DE_PERSECUCION HACIA ", (the) pnj.perseguido;
     MOVIMIENTO_HUIR:       print "MOVIMIENTO_DE_HUIDA";
     default:               print "**UNDEFINED**";
   }
   print "]^";
  }
#endif;

  pnj.zonaValida = zona;
    
  if (tipo_movimiento == MOVIMIENTO_NINGUNO) {
    pnj.tipo_de_movimiento = MOVIMIENTO_NINGUNO;
    rtrue;
  }
    
  if (tipo_movimiento == MOVIMIENTO_ALEATORIO) {
    pnj.tipo_de_movimiento = MOVIMIENTO_ALEATORIO;
    
!    if (LugarObjetivo ~= 0)
!      pnj.capricho = LugarObjetivo;                       ! ¿¿¿ Esto está bien ??? (c) Alpha

    rtrue;
  }
    
  if (tipo_movimiento == MOVIMIENTO_HUIR) {
    pnj.tipo_de_movimiento = MOVIMIENTO_HUIR;
    
    if (LugarObjetivo ~= 0)
      pnj.objetivo_pnj = LugarObjetivo;

    rtrue;
  }
    
  if (tipo_movimiento == MOVIMIENTO_PREFIJADO)
    return PNJpreruta(pnj, LugarObjetivo, tipo_ruta);
    
  if ((tipo_movimiento ~= MOVIMIENTO_POR_META) && (tipo_movimiento ~= MOVIMIENTO_PERSEGUIR))
    rfalse;
    
  ! Sólo se pueden calcular rutas desde un lugar de la clase Lugar a
  ! otro de la misma clase, así que...
  if (zona == 0)
    claseVal = Lugar;
  else
    claseVal = zona;

  ! Paréntesis que encierran cada término del ||, (c) Alpha
  if ((~~(parent(pnj) ofclass claseVal)) || (parent(pnj) == LugarObjetivo))
    rfalse;
    
  objectloop (i ofclass claseVal) {
    i.number = 0;         
    give i ~en_ruta;      ! Resetear todos los lugares
  }

  ! Algoritmo: partiendo del lugar inicial, numeramos cada lugar por
  ! el que pasamos con el número de pasos necesario para alcanzarlo,
  ! hasta que alcancemos el lugar objetivo

  parent(pnj).number = 1;
  give parent(pnj) en_ruta;

  for (pasos = 1 : pasos < max_longitud_camino : pasos++) {
    objectloop (i has en_ruta) {
      if (i.number == pasos) {
        objectloop (j in compass) {
          k = ConduceA(j, i, tipo_ruta, claseVal);
          if (k ofclass Lugar) {
            give k en_ruta;
            if (k.number == 0) {
              k.number = pasos + 1;
#ifdef DEBUG;
              if (parser_trace > 1)
                print "[", (name) k, " es ", pasos + 1, "]^";
#endif;
            }
            if (k == LugarObjetivo) {
              encontrado = true;
              pnj.sentido = IntercambiarDireccion(j);     ! (c) Alpha
            }
          }
          if (encontrado)
            break;
        }
      }
      if (encontrado)
        break;    
    }
    if (encontrado)
      break;
  }
    
  pnj.tipo_de_movimiento = tipo_movimiento;

#ifdef DEBUG;
  if (parser_trace > 1)
    print "[Puesto ", (the) pnj, " en estado de movimiento ", pnj.tipo_de_movimiento, "]^";
#endif;

  pnj.objetivo_pnj = LugarObjetivo;
    
  if (encontrado == false) {
    pnj.longitud_precamino = 0;       ! si no lo encuentra: camino tiene longitud 0, (c) Alpha
    rfalse;                                               ! hemos alcanzado la máxima longitud
  }
    
  objectloop (i has en_ruta)
    if (i.number > pasos && i ~= LugarObjetivo) {
      i.number = 0;                                ! Los lugares que están a igual distancia
      give i ~en_ruta;                                  ! que el objetivo, no son interesantes
    }
    
  pnj.estado_pnj = 0;
  pnj.longitud_precamino = pasos;
    
#ifdef DEBUG;
  if (parser_trace > 1)
    print "[Encontrado un camino de ", pasos, " pasos. Recorriendolo hacia atrás desde ...^",
          (name) LugarObjetivo;
#endif;

  for ( : pasos > 0 : pasos--)  {                         ! Retroceder paso a paso
    encontrado = false;                                   ! buscando un lugar interesante que lleve
                                                ! hasta el lugar interesante que estaba en 'paso+1' 
    objectloop (i has en_ruta) {
      if (i.number == pasos) {
        objectloop (j in compass) {
          k = ConduceA(j, i, tipo_ruta, claseVal);
          if (k)
            if (k has en_ruta && k.number == pasos + 1)
              encontrado = true;
            if (encontrado)
              break;
        }
      }
      if (encontrado)
        break;
    }
 
#ifdef DEBUG;
    if (parser_trace > 1)
      print " está...^", (DirDada) j, " ", (del) i, ", el cual";
#endif;
 
    pnj.&pnj_dirs-->(k.number - 2) = j;  
    objectloop (k has en_ruta)                            ! Otros lugares con el mismo número
      if (k.number == pasos && i ~= k) {                ! no son interesantes
        k.number = 0;
        give k ~en_ruta;
      }
  }
    
#ifdef DEBUG;
  if (parser_trace > 1)
    print " es el punto de partida!]^";
#endif;

  rtrue;
];


[ PNJpreruta pnj array_ruta longitud_ruta fakevar;
  fakevar = fakevar;                                      ! por si se le llama pasandole un lugar

  if (pnj ofclass Movil) {
    pnj.estado_pnj = 0;
    pnj.tipo_de_movimiento = MOVIMIENTO_PREFIJADO;
    pnj.nombre_precamino = array_ruta;
    pnj.longitud_precamino = longitud_ruta;
  } else {
    "*** Movil Error: PNJpreruta ha sido llamado para el objeto no-Movil '", (the) pnj, "' ***";
  }
];


[ ConduceA direccion estelugar tipo_ruta zona_valida
  k tmp tmp2 zona;
  
  !    print "-ConduceA: ", (name) direccion, ":";
  if (~~(estelugar provides direccion.door_dir)) {
    ! print "NO HAY^";
    return 0;
  }
  
  k = estelugar.(direccion.door_dir);
  
  if (ZRegion(k) == 2) {
    ! print "Rutina que devuelve ";
    k = k();
  }
  
  if (ZRegion(k) ~= 1) {
    ! print " no se puede pasar^";
    return 0;
  }
    
  if (k)
    if (k has door) {
      ! print " una puerta ";
      if (tipo_ruta & CAMINO_SIN_PUERTAS)
        return 0;
      if ((tipo_ruta & CAMINO_ABIERTO) && k hasnt open) {
        ! print "cerrada^";
        return 0;
      }
      if ((tipo_ruta & CAMINO_SIN_CERROJOS) && k has locked) {
        ! print "cerrada con llave^";
        return 0;
      }
      tmp = parent(k);
      move k to estelugar;
      tmp2 = k.door_to();
      if (tmp ~= 0)
        move k to tmp;
      else
        remove k;
      k = tmp2;
      ! print " que lleva a ";
    }

  ! print (name) k;
  if (zona_valida == 0)
    zona = Lugar;
  else
    zona = zona_valida;

  if (~~(k ofclass zona)) {
    ! print " que no es un lugar válido.^";
    return 0;
  }
  
  ! print ".^";
  return k;
];


[ MoverPNJDir amover direccion
  i j p mensaje;
    
  ! Un sólo movimiento por turno
  if (amover.seHaMovido)
    rfalse;
    
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
    
  j = p.(direccion.door_dir);

  if (ZRegion(j) == 2)
    j = j();

  if (j)
    if (j has door) {
      ! pnj_abrir retorna: 2 para atravesar la puerta normalmente
      !                    1 para atravesar la puerta pero impedir
      !                    que se imprima el texto de
      !                    "marchar/llegar"
      !                    0 para impedir al PNJ que use esa puerta
      if (j provides pnj_abrir) {
        mensaje = j.pnj_abrir(amover);
        
        if (mensaje == false) {
          amover.pnj_bloqueado();
#ifdef DEBUG;
          if (parser_trace > 1)
            print "[MoverPNJDir bloqueado: ", (the) j, "'s pnj_abrir retornó falso]^";
#endif;
          rfalse;
        }
      } else if (j hasnt open) {
        amover.pnj_bloqueado();
#ifdef DEBUG;
        if (parser_trace > 1)
          print "[MoverPNJDir bloqueado: ", (the) j, " está cerrad", (o)j, " y no tiene pnj_abrir]^";
#endif;
        rfalse;
      }
    }
    
  MoverPNJ(amover, i, ##Go, direccion);
    
  if (p == location && mensaje == 2) {
    if (ZRegion(self.marcha) == 3)  ! Imprimir el texto
      print "^", (The) self, " ", (string) self.marcha, " ", (DirDada) direccion, ".^";
    else
      self.marcha(direccion);
  }
    
  if (parent(self) == location && mensaje == 2) {
    direccion = NULL;
    
    objectloop (i in compass)
      if (ConduceA(i, location, CAMINO_CUALQUIERA) == p)
        direccion = i;
 
    if (ZRegion(self.llega) == 3) {
      print "^", (The) self, " ", (string) self.llega;
      if (direccion ~= NULL) print " desde ", (the) direccion;
        print ".^";
    } else
      self.llega(direccion);
  }
    
  if (self provides accion_despues)
    self.accion_despues();
    
  amover.seHaMovido = true;
  rtrue;
];


! (c) Alpha:

[ IntercambiarDireccion d;
  switch (d) {
    n_obj: return s_obj;
    s_obj: return n_obj;
    e_obj: return w_obj;
    w_obj: return e_obj;
    nw_obj: return se_obj;
    ne_obj: return sw_obj;
    sw_obj: return ne_obj;
    se_obj: return nw_obj;
    u_obj: return d_obj;
    d_obj: return u_obj;
    in_obj: return out_obj;
    out_obj: return in_obj;
  }
];


Ifndef MoverPNJ; ! Proporciona un MoverPNJ mínimo si no se ha incluido PERSEGUIR.h
[ MoverPNJ amover dest actn objn;
  move amover to dest;
  actn = actn;
  objn = objn;
];
Endif;


Ifndef DirDada;
[ DirDada i;
  switch(i) {
    n_obj:       print "hacia el norte";
    s_obj:       print "hacia el sur";
    e_obj:       print "hacia el este";
    w_obj:       print "hacia el oeste";
    ne_obj:      print "hacia el noreste";
    nw_obj:      print "hacia el noroeste";
    se_obj:      print "hacia el sureste";
    sw_obj:      print "hacia el suroeste";
    u_obj:  print "hacia arriba";
    d_obj:   print "hacia abajo";
    in_obj: print "al interior";
    out_obj:  print "afuera";
    default:     print "hacia ", (the) i;
  }
];
Endif;


!
! Objeto que mueve a los móviles
!
Object MovedorDeMoviles
  with
    daemon [ mov indMov;
      for (indMov = 1 : indMov <= indiceMoviles : indMov++) {
        mov = tablaMoviles-->indMov; 
        ! print (object) mov, mov, " va a moverse^";
        if (mov.condicion_movimiento()) mov.movimiento();
      }
    ];


[ IniciarMoviles mov; 
  objectloop (mov ofclass Movil) {
    if (indiceMoviles < maximoNumeroMoviles) {
      indiceMoviles++;
      tablaMoviles-->indiceMoviles = mov;
    } else {
      print "ERROR: superado el límite de moviles, ", (name)mov, " no será tratado como tal.";
    }
  }
    
  StartDaemon(MovedorDeMoviles);
];
