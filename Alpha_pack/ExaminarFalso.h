!
! ExaminarFalso.h
!
! Permite usar simplemente el nombre de un objeto como sinónimo de
! 'examinar objeto' (copiado de Transilvania Corruption, de Alien Soft,
! y mejorado por mí para dar soporte a objetos decorado):
!


System_file;

#ifdef VerboDesconocido;
  Message "[ExaminarFalso: Usando rutina VerboDesconocido() proporcionada por el juego]";
  Message "[ExaminarFalso: IMPORTANTE: NO OLVIDES USAR EN ESA RUTINA EL RESULTADO DE...]";
  Message "[ExaminarFalso: ExaminarFalso.EF_VerboDesconocido(x) ]";
#endif; ! VerboDesconocido

#ifndef VerboDesconocido;
  [ VerboDesconocido x;
    return ExaminarFalso.EF_VerboDesconocido(x);
  ];
#endif; ! VerboDesconocido

Object ExaminarFalso
  with
    objetoVerboDesconocido 0,
    EF_VerboDesconocido [x obj;
      objectloop (obj ofclass Object && PruebaDeAlcance(obj)) {
#ifdef Decorado;
        if (obj ofclass Decorado && obj.buscar_nombre(x)) {
          jump PalabraEncontrada;
        } else
#endif;
          if (obj ~= jugador) {
            if (PalabraEnPropiedad(x, obj, nombre) ||
              PalabraEnPropiedad(x, obj, nombre_m) ||
              PalabraEnPropiedad(x, obj, nombre_f) ||
              PalabraEnPropiedad(x, obj, nombre_mp) ||
              PalabraEnPropiedad(x, obj, nombre_fp)) {
            jump PalabraEncontrada;
          }
        }
      }
      rfalse;
    .PalabraEncontrada;
      self.objetoVerboDesconocido = obj;
      return 'examinar.falso';
    ];


Verb 'examinar.falso'
   *                   -> ExaminarFalso;


[ ExaminarFalsoSub;
  uno = ExaminarFalso.objetoVerboDesconocido;
  ActualizarPronombre(uno);
  <<Examinar uno>>;
];

