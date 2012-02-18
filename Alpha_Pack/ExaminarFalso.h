!
! ExaminarFalso.h
!
! Permite usar simplemente el nombre de un objeto como sinónimo de
! 'examinar objeto' (copiado de Transilvania Corruption, de Alien Soft,
! y mejorado por mí para dar soporte a objetos decorado):
!


System_file;

#ifdef UnknownVerb;
  Message "[ExaminarFalso: Usando rutina VerboDesconocido() proporcionada por el juego]";
  Message "[ExaminarFalso: IMPORTANTE: NO OLVIDES USAR EN ESA RUTINA EL RESULTADO DE...]";
  Message "[ExaminarFalso: ExaminarFalso.EF_VerboDesconocido(x) ]";
#endif; ! VerboDesconocido

#ifndef UnknownVerb;
  [ UnknownVerb x;
    return ExaminarFalso.EF_VerboDesconocido(x);
  ];
#endif; ! VerboDesconocido

Object ExaminarFalso
  with
    objetoVerboDesconocido 0,
    EF_VerboDesconocido [x obj;
      objectloop (obj ofclass Object && TestScope(obj)) {
#ifdef Decorado;
        if (obj ofclass Decorado && obj.buscar_nombre(x)) {
          jump PalabraEncontrada;
        } else
#endif;
          if (obj ~= player) {
            if (WordInProperty(x, obj, name) ||
              WordInProperty(x, obj, name_m) ||
              WordInProperty(x, obj, name_f) ||
              WordInProperty(x, obj, name_mp) ||
              WordInProperty(x, obj, name_fp)) {
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
  noun = ExaminarFalso.objetoVerboDesconocido;
  PronounNotice(noun);
  <<Examine noun>>;
];

