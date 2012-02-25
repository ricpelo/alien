!----------------------------------------------------------------------------
!
! RASTROS: Librería para el tratamiento de rastros en el juego. Permite
!          definir localizaciones sobre las que se quedan marcados rastros
!          de tal forma que se pueden ver en las descripciones o no, se
!          pueden examinar, se pueden seguir (o los pueden seguir los PNJs)
!          y se van desvaneciendo a un ritmo modificable, tanto por la 
!          naturaleza del rastro como del lugar.
!
! AUTOR:   Mel Hython  
! FECHA:  Diciembre 2000
! VERSION:   1.0
! PARA:   Ser usada sobre InformATE en su version 6-10
! URLs:   http://www.arrakis.es/~meliton/
!         http://www.geocities.com/TimesSquare/Fortress/9939/
!         http://www.geocities.com/jsjlogin/equipate/
! USO:    'Include "Rastros"' tras el 'Include "Gramatica"'.
!
!----------------------------------------------------------------------------

Ifndef WORDSIZE;
Constant WORDSIZE = 2;
EndIf;

!
! Parámetros Globales de la librería
!
Ifndef tasaDisipacion;
Global tasaDisipacion = 1;  ! Cantidad de 'intensidad' borrada 
                             ! a los rastros en cada turno
Endif;

Ifndef maximoNumeroConRastro;
Constant maximoNumeroConRastro = 100; ! Maximo número de sitios con rastros
Endif;

!
! Tabla de valores válidos
!
Ifndef nivelPerceptible;
Constant nivelPerceptible = 2;
Endif;

Ifndef nivelCasiInvisible;
Constant nivelCasiInvisible = 5;
Endif;

Ifndef nivelViejo;
Constant nivelViejo = 8;
Endif;

Ifndef nivelReciente;
Constant nivelReciente = 11;
Endif;

Ifndef nivelClaro;
Constant nivelClaro = 14;
Endif;

!
! Tabla que contiene los lugares con rastro
!
Array tablaConRastro table maximoNumeroConRastro;
Global indiceConRastro = 0;

!
! CLASE TipoRastro
!
!  Tipo de rastro que se puede dejar. El que haya clases
!  de rastros permite que un mismo objetivo pueda ser
!  rastreado, por ejemplo, mediante diversos sentidos
!
Ifndef TipoRastro;
Class TipoRastro
  with
    name 'rastro' 'rastros' 'olor',
    !
    ! Multiplicador de la pérdida de rastro por el tipo
    !
    multDisipacion 1,
    !
    ! Texto en el caso del plural
    !
    nombre_plural 0,
    !
    ! Indica si un rastro es oloroso en lugar de visual
    !
    esOloroso false,
    !
    ! Implementación de esta_en, para que aparezca el rastro
    ! en las localizaciones correctas
    !
    found_in [ number;
      !
      ! Sólo en sitios 'marcables'
      !
      if (location ofclass LugarConRastro) {
        !
        ! Si es oloroso está oculto
        !
        if (self.esOloroso)
          give self concealed;

        number = location.numeroClase(self, nivelPerceptible);

        if (number > 1)
          give self pluralname;
        else
          give self ~pluralname;

        if (number > 0)
          rtrue;
      }
 
      rfalse;
    ],
    !
    ! Si es oloroso debe unirse al olfateo
    !
    react_before [;
      Smell: 
        if ((self.esOloroso) && (noun == 0)) {
          ! Sólo se huele el rastro más oloroso de todos
          if (parent(self).rastroMasOloroso() == self) {
            <<Smell self>>;
          }
        }
    ],
    !
    ! Descripción del rastro
    !
    short_name [ padre number;
      padre = parent(self); 

      if (padre ofclass LugarConRastro) {
        number = padre.numeroClase(self, nivelPerceptible);
        if (number > 1) {
          give self pluralname;
          if (self.nombre_plural ~= 0)
            print (string) VR(self.nombre_plural);
          else
            print (object) self;
        } else {
          give self ~pluralname;
          print (object) self;
        }

        rtrue;
      }
    ],
    !
    ! Metodo de descripcion de la intensidad del rastro
    !
    describeIntensidad [ intensidad era_plural;
      ! print " ", intensidad, " ";
      if (self has pluralname) {
        give self ~pluralname;
        era_plural = 1;
      }
      if (intensidad < nivelCasiInvisible) {
        print " de forma casi imperceptible";
      } else if (intensidad < nivelViejo) {
        print " de forma difusa";
      } else if (intensidad < nivelReciente) {
        ! No se imprime nada en este caso
      } else if (intensidad < nivelClaro) {
        print " claramente";
      } else {
        print " muy claramente";
      }
      if (era_plural == 1) {
        give self pluralname;
      }
    ],
    !
    ! Metodo de descripcion del rastro
    !
    describeRastro [ origen direccion intensidad otra_direccion;
      if (otra_direccion == 0) {
        self.describeIntensidad(intensidad);
        print " ", (DirDada) direccion;
      } else {
        print " ", (del) direccion, " y se dirige";
        self.describeIntensidad(intensidad);
        print " ", (DirDada) otra_direccion;
      }

      if (origen.rastroReconocible(self)) {
        ! Rastro reconocible por el jugador
         print ". Parece ", (del) origen;
      }
    ],
    !
    ! Redefinición de varias acciones
    !
    before [ number padre contador oloroso;
      !
      ! Antes de todas las acciones recalcular el género
      !
      padre = parent(self);
      
      if ((padre) && (padre ofclass LugarConRastro))
        number = padre.numeroClase(self, nivelPerceptible);
      else
       number = 0;

      if (number > 1)
        give self pluralname;
      else
        give self ~pluralname;

      Take:
        "No se puede", (n) self, " coger.";

      Smell:
        !
        ! Si se trata de un rastro odorífero
        ! se pasa la pelota a la descripción
        !
        if (self.esOloroso)
          <<Examine self>>;
        else {
          ! Este no huele, pero ¿huele algo?
          oloroso = padre.rastroMasOloroso();
          if (oloroso ~= 0) {
            <<Smell oloroso>>;
          }
        }

      Examine:
        !
        ! Ver si realmente queda algo aún
        !
        if (number == 0)
          "El rastro es tan poco definido que no se puede saber de qué se trata
           o hacia dónde se dirige.";

        !
        ! Poner la descripcion básica si hay alguna
        !
        if (self.description ~= 0)
          PrintOrRun(self, description);

        !
        ! Describir la orientación usando el sistema del rastro
        !
        if (number > 1) {
          print "Realmente hay varios ";
          if (self.nombre_plural ~= 0)
            print (string) self.nombre_plural;
          else
            print (object) self;
          print ":^";

          for (contador = 0 : contador < 8 : contador++) {
            ! Miramos la 'intensidad' para buscar una que sea cero
            if ((padre.&rastros-->(2 + contador * 5) == self) &&
                (padre.&rastros-->(3 + contador * 5) >= nivelPerceptible)) {
              print "    ";
              if (self has pluralname) {
                give self ~pluralname;
                print "un", (o) self;
                give self pluralname;
              } else {
                print "un", (o) self;
              }
              self.describeRastro(padre.&rastros-->(0 + contador * 5),   ! origen
                                  padre.&rastros-->(1 + contador * 5),   ! direccion
                                  padre.&rastros-->(3 + contador * 5),   ! intensidad
                                  padre.&rastros-->(4 + contador * 5));  ! otra_direccion
              print "^";
            }
          }
        } else {
          ! Sólo se trata de un rastro pero hay que describirlo
          for (contador = 0 : contador < 8 : contador++) {
            ! Miramos la 'intensidad' para buscar una que sea cero
            if ((padre.&rastros-->(2 + contador * 5) == self) &&
                (padre.&rastros-->(3 + contador * 5) >= nivelPerceptible)) {
              if (padre.&rastros-->(4 + contador * 5) ~= 0)
                print "Proviene";
              else
                print "Se dirige";
              self.describeRastro(padre.&rastros-->(0 + contador * 5),   ! origen
                                  padre.&rastros-->(1 + contador * 5),   ! direccion
                                  padre.&rastros-->(3 + contador * 5),   ! intensidad
                                  padre.&rastros-->(4 + contador * 5));  ! otra_direccion
              print ".^";
            }
          }
        }

      rtrue;
    ],
  has static;
Endif;

!
! CLASE ObjetoRastreable
!
!  Definición de los objetos que dejan rastros tras de sí
!  en los lugares en los que quedan rastros
!
Ifndef ObjetoRastreable;
class ObjetoRastreable
 with
   !
   ! Rastros que va 'dejando' tras de sí, cada
   ! grupo de ceros representa un rastro posible
   ! en grupos de tres valores:
   !
   ! - Tipo de rastro: de clase TipoRastro
   ! - Intensidad por defecto
   ! - ¿Reconoce el jugador este rastro?
   !
   ! NO DEBE HABER TIPOS REPETIDOS EN ESTE ARRAY.
   !
   ! Este array puede ser redefinido por otro 
   ! de cualquier longitud múltiplo de 3
   !
   rastrosDejados 0 0 0,
   !
   ! Función que dado un tipo busca la intensidad
   ! por defecto correspondiente
   !
   dameIntensidadClase [ tipo contador entradas;
     ! Numero de elementos
     entradas = (self.#rastrosDejados) / WORDSIZE;
    
     ! Numero de tripletes
     entradas = entradas / 3;
    
     ! Recorremos y buscamos clase
     for (contador = 0 : contador < entradas : contador++) {
       if ((self.&rastrosDejados-->(0 + contador * 3)) == tipo) {
         return self.&rastrosDejados-->(1 + contador * 3);
       }
     }

     ! No encontrado retornamos '0'
     return 0;
   ], 
   !
   ! Función que dado un tipo determina si
   ! el rastro de esa clase de este objeto
   ! es reconocible o no por el jugador
   !
   rastroReconocible [ tipo contador entradas;
     ! Numero de elementos
     entradas = (self.#rastrosDejados) / WORDSIZE;

     ! Numero de tripletes
     entradas = entradas / 3;
    
     ! Recorremos y buscamos clase
     for (contador = 0 : contador < entradas : contador++) {
       if ((self.&rastrosDejados-->(0 + contador * 3)) == tipo) {
         return self.&rastrosDejados-->(2 + contador * 3);
       }
     }

     ! No encontrado retornamos false
     rfalse;
   ], 
   !
   ! Función que cambia de estado un rastro
   !
   cambiaRastro [ tipo reconocible intensidad contador entradas;
     ! Numero de elementos
     entradas = (self.#rastrosDejados) / WORDSIZE;

     ! Numero de tripletes
     entradas = entradas / 3;
    
     ! Recorremos y buscamos clase
     for (contador = 0 : contador < entradas : contador++) {
       if ((self.&rastrosDejados-->(0 + contador * 3)) == tipo) {
         self.&rastrosDejados-->(2 + contador * 3) = reconocible;
         if (intensidad ~= 0)
           self.&rastrosDejados-->(1 + contador * 3) = intensidad;
         break;
       }
     }
   ], 
   !
   ! Función que marca UN rastro o todos los rastros
   !
   !  Si se le llama con tipo igual a cero (o sin
   !   dicho parámetro) marcará TODOS los rastros
   !   incluídos en self.rastrosDejados con la intensidad
   !   por defecto. 
   !
   !   Si se le llama con un tipo distinto de cero
   !   pero sin intensidad se busca la por defecto
   !   y se usa esta.
   !
   dejaRastros [ direccion tipo intensidad otra_direccion padre entradas contador;
     padre = parent(self);

     ! Si no es marcable nada de nada
     if (~~(padre ofclass LugarConRastro))
       rfalse;

     if (tipo ~= 0) {
       ! Se genera un sólo rastro
       if (intensidad == 0)
         intensidad = self.dameIntensidadClase(tipo);

       parent(self).marcaRastro(self, tipo, direccion, intensidad, otra_direccion);
     } else {
       ! Generar TODOS los rastros
 
       ! Numero de elementos
       entradas = (self.#rastrosDejados) / WORDSIZE;
    
       ! Numero de tripletes
       entradas = entradas / 3;
    
       ! Recorremos y buscamos clase
       for (contador = 0 : contador < entradas : contador++) {
         !
         ! Marcamos cada clase con su intensidad por defecto
         !
         parent(self).marcaRastro(self, 
                                  self.&rastrosDejados-->(0 + contador * 3),
                                  direccion,
                                  self.&rastrosDejados-->(1 + contador * 3),
                                  otra_direccion);
       }
     }
   ];
Endif;
  

!
! CLASE LugarConRastro
!
!  Definición de la clase de localidades en las que se pueden
!  marcar los rastros. Incluyen todo el código necesario para
!  modificar correctamente las descripciones, etc...
!
Ifndef LugarConRastro;
class LugarConRastro
  with
    !
    ! Variables que modifican el comportamiento de los rastros
    !
    multGeneral 1, ! Multiplicador de la velocidad de desaparción
    !
    ! Rastros: un máximo de 8 rastros simultáneos por habitación
    !
    numRastrosActivos 0,
    rastros 0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0,
    !
    ! Función que permite marcar rastros
    !
    marcaRastro [ origen tipo direccion intensidad otra_direccion contador;
      ! Si algunos de los parámetros no ha sido
      ! especificado no hacemos nada (otra_direccion es opcional)
      if ((origen == 0) || (direccion == 0) ||
          (tipo == 0) || (intensidad == 0))
        rfalse;

      ! Si alguno de los parámetros no es del tipo
      ! adecuado nos salimos
      if ((~~(origen ofclass ObjetoRastreable)) ||
          (~~(tipo ofclass TipoRastro)) ||
!         (~~(direccion in brujula)) ||            (c) Alpha
          (intensidad <= 0))
        rfalse;

      ! Buscamos un 'hueco' donde acomodar el rastro
      for (contador = 0 : contador < 8 : contador++) {
        ! Miramos la 'intensidad' para buscar una que sea cero
        if (self.&rastros-->(3 + contador * 5) <= 0) {
          self.&rastros-->(0 + contador * 5) = origen;
          self.&rastros-->(2 + contador * 5) = tipo;
          self.&rastros-->(1 + contador * 5) = direccion;
          self.&rastros-->(3 + contador * 5) = intensidad;
          self.&rastros-->(4 + contador * 5) = otra_direccion;
          self.numRastrosActivos++;
          break;
        }
      }

      rtrue;
    ],
    !
    ! Función que reduce la intensidad de los rastros
    !
    disipaRastros [ factor contador aRestar valor tipo quedan;
      !
      ! Para acelerar un poco
      !
      quedan = self.numRastrosActivos;
      !
      ! el parámetro factor es un mecanismo
      ! adicional para que el programador
      ! pueda cambiar el disipador. El disipador
      ! por defecto siempre pasará 1
      !
      aRestar = tasaDisipacion * factor;

      ! Calculamos el valor a restar considerando 
      ! modificadores del tipo y de la localidad
      aRestar = aRestar * self.multGeneral;

      for (contador = 0 : contador < 8 : contador++) {
        ! Ver si queda alguno
        if (quedan == 0)
          break;

        ! Miramos la 'intensidad' para buscar una que no sea cero
        valor =  self.&rastros-->(3 + contador * 5);
        if (valor > 0) {
          tipo = self.&rastros-->(2 + contador * 5);
          valor = valor - aRestar * tipo.multDisipacion;
          if (valor < 0)
            valor = 0;

          self.&rastros-->(3 + contador * 5) = valor;

          if (valor == 0)
            self.numRastrosActivos--;

          quedan--;
        }
      }
    ],
    !
    ! Numero de rastros presentes de una clase determinada
    !
    numeroClase [ clase min_intensidad contador _clase total _intensidad;

      if (self.numRastrosActivos == 0)
        return 0;

      total = 0;

      for (contador = 0 : contador < 8 : contador++) {
        _clase = self.&rastros-->(2 + contador * 5);
        _intensidad = self.&rastros-->(3 + contador * 5);

        if ((clase == _clase) && (_intensidad > min_intensidad))
          total++;
      }

      return total;
    ],
    !
    ! Localiza el rastro odorífero MAS intenso
    !
    rastroMasOloroso [ contador _clase mayor _intensidad encontrado;

      if (self.numRastrosActivos == 0)
        return 0;

      mayor = 0;
      encontrado = 0;

      for (contador = 0 : contador < 8 : contador++) {
        _clase = self.&rastros-->(2 + contador * 5);
        _intensidad = self.&rastros-->(3 + contador * 5);

        if (_clase ofclass TipoRastro) {
          if (_clase.esOloroso) {
            if (_intensidad > mayor) {
              mayor = _intensidad;
              encontrado = _clase;
            }
          }
        }
      }

      return encontrado;
    ];
Endif;


!
! Motor de reducción de rastros
!
Ifndef DisipadorDeRastros;
Object DisipadorDeRastros
  with
    daemon [ lugar indLugar i;
      !
      ! Reducción de todos los rastros del juego
      !
      for (indLugar = 1 : indLugar <= indiceConRastro : indLugar ++) {
        ! Multiplicador normal '1'
        lugar = tablaConRastro-->indLugar;
        if (lugar.numRastrosActivos > 0)
          lugar.disipaRastros(1);
      }

      !
      ! Correción del número de cada rastro 'presente'
      !
      if (location ofclass LugarConRastro) {
        objectloop(i in location) {
          if (i ofclass TipoRastro) {
            i.found_in();
          }
        }
      }
    ];
Endif;

!
! Rutina de inicio de los rastros
!
[ IniciarRastros lugar;
  objectloop(lugar ofclass LugarConRastro) {
    if (indiceConRastro < maximoNumeroConRastro) {
      indiceConRastro++;
      tablaConRastro-->indiceConRastro = lugar;
    } else {
      print "ERROR: superado el límite de lugares con rastros; ",
             (name)lugar, " no será tratado como tal.";
    }
  }

  StartDaemon(DisipadorDeRastros);
];

!
! Rutina que ejecuta rutinas si las encuentra
!
#ifndef VR;
[ VR valor;
! print "[VR: ", valor, " --> ", ZRegion(valor), " ]^";
  if (ZRegion(valor) == 2) return valor();
  else                     return valor;
];
#endif;

!
! Rutina de decir direcciones
!
#ifndef DirDada;
[ DirDada i;
  switch (i) {
    n_obj:   print "hacia el norte";
    s_obj:   print "hacia el sur";
    e_obj:   print "hacia el este";
    w_obj:   print "hacia el oeste";
    ne_obj:  print "hacia el noreste";
    nw_obj:  print "hacia el noroeste";
    se_obj:  print "hacia el sureste";
    sw_obj:  print "hacia el suroeste";
    u_obj:   print "hacia arriba";
    d_obj:   print "hacia abajo";
    in_obj:  print "hacia el interior";
    out_obj: print "hacia el exterior";
    default: print "hacia ", (the) i;           ! (c) Alpha
  }
];
#endif;

