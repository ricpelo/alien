!-------------------------------------------------------------------------
! Versión 1.00 Marzo de 2001
!-------------------------------------------------------------------------
! Motivación:
!-------------------------------------------------------------------------
! Estas son unas sencillas clases que me permiten olvidarme de
! como es la sintaxis de Inform para arrays/vectores.
!-------------------------------------------------------------------------
! Uso:
!-------------------------------------------------------------------------
! vector naturales
! private
!     elementos 1 2 3 4 5 6 7 8 9 10
! ;
! print naturales.elemento(2);
! naturales.longitud();
! naturales.escribe(2,99); ! en C++ es: naturales.escribe[2] = 99;
!
! array m2por2
! private elementos 1 2
!                   3 4,
!         dimx 2,
!         dimy 2
! ;
!-------------------------------------------------------------------------

System_file;

! Clase base abstracta ----Collection-------------------------------------

class coleccion
private
      elementos 0,
with
      elemento [;
          return 0;
      ],
      longitud [;
          return self.#elementos/WORDSIZE;
      ],
      escribe [;
          return;
      ]
;

! Clase ----Vector-------------------------------------------------------

class vector
class coleccion,
 with
      elemento [i;
         if (i<self.longitud() 
          || i>=0)
          return self.&elementos-->i;
         else
          return 0;
      ],
      escribe [ i x;
         if (i<self.longitud()
          && i>=0) 
          self.&elementos-->i = x;
      ]
;

! Clase ----Array---------------------------------------------------------

class array
class coleccion
 private
      dimx 0,
      dimy 0,
 with
      elemento [x y;
          if (x>=0 
           && x<self.dev_dimx()
           && y>=0
           && y<self.dev_dimy())
              return (self.&elementos-->((x*self.dev_dimy()) + y));
          else return 0;
      ],
      escribe [ x y v;
          if (x>=0 
           && x<self.dev_dimx()
           && y>=0
           && y<self.dev_dimy())
              return (self.&elementos-->((x*self.dev_dimy()) + y) = v);
          else return 0;
      ],
      dev_dimx [; return self.dimx; ],
      dev_dimy [; return self.dimy; ]
;
      
! Clase ----Coleccion---------------------------------------------------------

class asociativo      
class coleccion
private
       parelem 0,
with
       busca [x i;
         for(i=0:i<self.longitud():i++)
              if (self.&elementos-->i == x)
                  break;
         if (i==self.longitud())
              return -1;
         else return i;
       ],
       elemento [x i;
         if ((i=self.busca(x))>-1)
            return self.&parelem-->i;
         else
            return -1;
       ],
       escribe [x y i;
         if ((i=self.busca(x))>-1)
            self.&parelem-->i = y;
       ],
       modifica [x y i;
         if ((i=self.busca(x))>-1)
            self.&elementos-->i = y;
       ]
;
