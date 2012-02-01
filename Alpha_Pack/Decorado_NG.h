! Decorados.h (c) 2000 Zak McKracken
! V2.0 biplataforma
!
!
!  Se define la clase decorado.
!
!  Los objetos de esta clase son en realidad varios objetos del juego,
!  recogidos en un solo objeto del codigo.
!
!  Se entiende que son objetos minimalistas, con los que apenas se
!  puede interactuar, salvo examinarlos.
!
!  Un objeto de la clase decorado, no puede tener nombre_corto ni
!  descripcion, ya que en realidad representa a muchos objetos
!  diferentes. Lo que tiene en cambio es la propiedad describir, que
!  contiene una lista con la siguiente estructura:
!
!  with describir
!    'palabra' "descripcion" GENERO
!    'palabra2' "descripcion2" GENERO2
!    etc.
!    ,
!
! Ejemplo:
!
! Object decorado_celda Celda
! class decorado
! with  describir
!        'pared' "Paredes lugubres y frias" G_FEMENINO
!        'paredes' "Paredes lugubres y frias" G_FEMENINO+G_PLURAL
! ;
!
!
!  Observa que los elementos de la lista no llevan comas separando. Ni
!  siquiera al final de cada linea. Solo al final de todos los
!  elementos, habra que poner una coma (si vas a seguir definiendo
!  propiedades o atributos), o directamente punto y coma (si has
!  terminado la definicion del objeto).
!
! Como funciona:
!
!  Cuando el jugador intente cualquier accion usando como sustantivo
!  'pared', por ejemplo, y el objeto decorado_celda esta a su alcance
!  (el jugador esta dentro de la celda), este objeto se dara por
!  referenciado, y asi se lo notificara al parser, actualizando ademas
!   los siguientes campos del objeto decorado_celda:
!
!   cantidad  -> Toma el valor de la palabra usada por el jugador
!               ('pared')
!   descripcion -> Toma el valor de la cadena que sigue a 'pared', en
!              la propiedad describir es decir "Paredes lugubres y
!              frias"
!   genero -> Toma el genero asociado con esa entrada, es decir
!             G_FEMENINO
!
!  Despues deja que el parser continue. La libreria, poco despues,
!  llamara al objeto  decorado_celda, a su rutina antes, para
!  informarle de la accion que se pretende hacer con el. La rutina
!  proporcionada en esta clase, por defecto "deja pasar" la
!  accion Examinar, pero impide cualquier otra con el mensaje "Dejalo,
!  solo es decorado".
!
!  Si la accion es examinar, la libreria llevara a cabo su accion
!  estandar, y por tanto poco despues imprimira la descripcion de ese
!  objeto, que toma del campo descripcion y que ya contiene la cadena
!  correcta.
!
!  Puedes sobreescribir la rutina antes en los objetos que derive de
!  esta clase, y emitir mensajes genericos a tu gusto, del
!  estilo de:
!
!    "Deja ", (el) self, " en paz. No ", (es) self, " mas que decorado.";
!
!  Y el nombre que saldra sera en cada caso el de la palabra que haya
!  usado el jugador, por ejemplo:
!
!  > EMPUJA PAREDES
!  Deja las paredes en paz, no son mas que decorado.
!
!  Incluso, si quisieras particularizar para un objeto concreto,
!  podrias examinar la propiedad cantidad, que te dira que palabra ha
!  usado el jugador. Por ejemplo:
!
!  Empujar: if (self.cantidad=='techo') "No llegas.",
!           "Deja ", (el) self, " en paz.";
!
!
!  LIMITACIONES: si el nombre corto tiene mas de nueve letras, cuando
!  sea impreso sera truncado, por ejemplo:
!  > EMPUJA INSTALACION
!  Deja la instalaci en paz.
!
!  Puede evitarse redefiniendo habilmente la rutina nombre_corto en el
!  objeto derivado de la clase, y cambiandolo por algo como:
!
!     if (self.cantidad=='instalacion') print "instalacion";
!     else print (address) self.cantidad;
!     rtrue;
!
!  Pero evidentemente habria que particularizarlo para cada caso.
!

! Para compatibilidad con Inform 6.15 InformATE 6/7
#ifndef WORDSIZE;
Constant WORDSIZE=2;
Constant TARGET_ZCODE;
#endif;

System_file;

Message "Incluyendo módulo de objetos de decorados, por Zak";

!
! Rutina que ejecuta rutinas si las encuentra
!
Ifndef VR;
[ VR valor;

!print "[VR: ", valor, " --> ", ZRegion( valor ), " ]^";

 if ( ZRegion( valor ) == 2 )
  return valor();
 else
  return valor;
];
EndIf;

!
! CLASE DECORADO
!
! El algoritmo es el siguiente: se permiten varias palabras seguidas (o separadas por las
! partículas el, la, los, las, de o del), siempre que dichas palabras sean sinónimas. Se
! permite que una misma palabra sea sinónima de dos o más palabras distintas, lo cual se
! usaría sobre todo para crear adjetivos. Ejemplo:
!
! sinonimos
!   'grande' 'mesa'    -1
!   'grande' 'ventana' -1,
! describir
!   'mesa'    "Una mesa muy bonita."          G_FEMENINO
!   'ventana' "Una ventana abierta al mundo." G_FEMENINO
!
! Este ejemplo crea dos elementos en el decorado: la mesa y la ventana. Ambas tienen como
! sinónimo la palabra 'grande' (que en realidad aquí actuaría como adjetivo de ambas).
! Se puede usar EX MESA, EX MESA GRANDE, EX VENTANA, EX VENTANA GRANDE... pero NO puede
! usarse EX MESA VENTANA o EX VENTANA MESA, ya que 'mesa' y 'ventana' no son sinónimos
! (si A es sinónimo de B y de C, eso no significa que B y C también lo sean). Aunque
! parece que no tiene demasiado sentido, sí es práctico para el caso de que el sinónimo
! sea un adjetivo (como el 'mesa' de este caso).
! Si el jugador escribe EX GRANDE, el algoritmo se decidirá por el primero que encuentre
! en la lista de sinónimos (en este caso, la mesa).
!
Class Decorado
  with
    descripcion 0,
    cantidad 0,
    describir 0,
    genero 0,
    sinonimos 0,
    nombre_corto [;
      print (address) self.cantidad;
      rtrue;
    ],
    parse_nombre [ i n w c r f m j p;
      self.descripcion = 0;
      n = (self.#describir) / (3 * WORDSIZE);

      if (w == 'el' or 'la' or 'los' or 'las')
        w = SiguientePalabra();

      c = r = 0;
      p = null;

      while (true) {
        w = SiguientePalabraParar(); if (w == -1) return c;

        if (w == 'de' or 'del') {
          w = SiguientePalabraParar(); if (w == -1) return c;
          r++;
        }

        if (w == 'el' or 'la' or 'los' or 'las') {
          w = SiguientePalabraParar(); if (w == -1) return c;
          r++;
        }

        f = false;

        for (i = 0 : i < n : i++) {
          if ((self.&describir)-->(i * 3) == w) {
            if (p == null) {
              p = w;
            } else {
              if (p ~= w) {
                return c;
              }
            }
            f = true;
            if (self.descripcion == 0) {
              self.descripcion = VR((self.&describir)-->(i * 3 + 1));
              self.cantidad = w;
              self.genero = (self.&describir)-->(i * 3 + 2);
            }
            c++;
            if (r > 0) {
              c = c + r;
              r = 0;
            }            
          }
        }

        if ((~~f) && self.sinonimos ~= 0) {
          m = (self.#sinonimos) / (3 * WORDSIZE);
          for (j = 0 : j < m : j++) {
.synonymContinue;
            if ((self.&sinonimos)-->(j * 3) == w) {
              f = false;
              for (i = 0 : i < n : i++) {
                if ((self.&describir)-->(i * 3) == (self.&sinonimos)-->(j * 3 + 1)) {
                  if (p == null) {
                    p = (self.&describir)-->(i * 3);
                  } else {
                    if (p ~= (self.&describir)-->(i * 3)) {
                      j++;
                      jump synonymContinue;
                    }
                  }
                  if (self.descripcion == 0) {
                    self.descripcion = VR((self.&describir)-->(i * 3 + 1));
                    self.cantidad = (self.&describir)-->(i * 3);
                    self.genero = (self.&sinonimos)-->(j * 3 + 2);
                    if (self.genero == -1) {
                      self.genero = (self.&describir)-->(i * 3 + 2);
                    }
                  }
                  f = true;
                  break;
                }
              }
              if (f) {
                c++;
                if (r > 0) {
                  c = c + r;
                  r = 0;
                }
                break;
              } else {
                return c;
              }
            }
          }
        }
      }
    ],
    antes [;
      Examinar: rfalse;
      Coger:    "No puedes hacerlo, ya que está", (n) self, " fij", (o) self,
                " en su sitio.";
      Empujar:  print_ret (_El) self, " no parece que pueda", (n) self,
                " ser empujad", (o) self, ".";
      Oler:     "No parece que huela", (n) self, " a nada especial.";
      Escuchar: "No produce", (n) self, " ningún sonido.";
      BuscarEn: "No hay nada que buscar en eso.";
      Tocar:    "No notas nada especial al tacto.";
      default:  "No hay ninguna razón para hacer eso.";
    ],
  has
    escenario oculto;

