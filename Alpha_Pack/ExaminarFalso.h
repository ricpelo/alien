!
! ExaminarFalso.h
!
! Copyright (c) 2012 Ricardo Pérez López (Alpha Aventuras)
!

! This program is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation, either version 3 of the License, or
! (at your option) any later version.
!
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
!
! You should have received a copy of the GNU General Public License
! along with this program.  If not, see <http://www.gnu.org/licenses/>.

!
! Permite usar simplemente el nombre de un objeto como sinónimo de
! 'EXAMINAR OBJETO' (copiado de Transilvania Corruption, de Alien Soft,
! y mejorado por mí para dar soporte a objetos decorado).
!
! USO: Incluir detrás de Decorado_NG para soportar objetos decorado.
!


System_file;


#ifdef UnknownVerb;
Message " __________________________________________________________ ";
Message "|                                                          |";
Message "|           * ExaminarFalso: I M P O R T A N T E *         |";
Mensaje "|           ======================================         |";
Message "|  Usando rutina UnknownVerb() proporcionada por el juego  |";
Message "|      NO OLVIDES USAR EN ESA RUTINA EL RESULTADO DE:      |";
Message "|      ExaminarFalso: ExaminarFalso.EF_UnknownVerb(x)      |";
Message "|__________________________________________________________|";
#endif; ! UnknownVerb


#ifndef UnknownVerb;
[ UnknownVerb x;
  return ExaminarFalso.EF_UnknownVerb(x);
];
#endif; ! UnknownVerb


Object ExaminarFalso
  with
    objetoVerboDesconocido 0,
    EF_UnknownVerb [x obj;
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

