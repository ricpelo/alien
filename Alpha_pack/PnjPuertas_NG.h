!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!   PNJPUERTAS  Una libreria para InformATE complementaria a PNJMovil
!   para la codificación sencilla de puertas
!   utilizables por los PNJs.
!   Escrita por Jævius. <jaevius@teleline.es>
!
!   Basada en una traducción y adaptación de la
!   libreria DOORS de L. Ross Raszewski.<rraszews@skipjack.bluecrab.org>
!   
! La documentación sobre el uso de la librería se incluyen en el
! archivo adjunto PNJPuertas.txt, dado su extensión.


Property tras_abrir;
!Property additive pnj_abrir;
Constant DEJA_ALEATORIO = 0;
Constant DEJA_ABIERTO = 1;
Constant DEJA_CERRADO = 2;
Constant DEJA_CERRADO_CON = 3;
Constant NO_PUEDE_ABRIR = 4;


Class PnjPuerta
  with
    nombre_f 'puerta',
    nombre_fp 'puertas',
    interior 0,                     ! (c) Alpha
    exterior 0,                     ! (c) Alpha
    direcc_puerta [;
      if (parent(self) == self.ladoa)
        return self.dira;
      return self.dirb;
    ],
    puerta_a [;
      if (parent(self) == self.ladoa)
        return self.ladob;
      return self.ladoa;
    ],     
    ladoa 0,
    dira 0,
    ladob 0,
    dirb 0,
    esta_en 0 0,
    lado_cierre 0,
    bloqueada false,
    entra_o_sale [;
      if (self.interior == 0 || self.interior == parent(self)) {
        return "entra";
      } else {
        return "sale";
      }
    ],
    entrando_o_saliendo [;
      if (self.interior == 0 || self.interior == parent(self)) {
        return "entrando";
      } else {
        return "saliendo";
      }
    ],
    pnj_abrir [ quien res x;
      if (self has abierta)
        res = 0;
      else  
        if (quien.tras_abrir == NO_PUEDE_ABRIR) {
          if (PruebaDeAlcance(quien))
            print "^", (_El) quien, " quiere abrir ", (el) self, ", pero no puede.^";
          else
            if (PruebaDeAlcance(self))
              print "^Se oyen ruidos al otro lado de ", (el) self,
                    ", como si algo intentara abrirla.^";
          rfalse;
        } else
          if (self hasnt cerrojoechado)
            res = 7;
          else
            if (self provides con_llave) 
              if (self.con_llave in quien) 
                if (self.lado_cierre == 0 || quien in self.lado_cierre)
                  res = 1;
                else
                  res = 2;
              else
                if (self.lado_cierre == 0 || quien in self.lado_cierre)
                  res = 3;
                else
                  res = 4;
            else
              if (self.lado_cierre == 0 || quien in self.lado_cierre)
                res = 5;
              else
             res = 6;

    if (self.bloqueada)
      switch (res) {
     1: res = 8;
     5: res = 9;
     7: res = 10;
        }

!****** YA TENEMOS EN RES CODIFICADO EL RESULTADO DEL MOVIMIENTO DEL PNJ
! EN RELACION CON LA PUERTA. Los códigos son:
! 0.- Puerta abierta.- Pnj pasa sin problema
! 1.- Puerta cerrada con llave y PNJ tienen la llave.- pasa sin problema
! 2.-  "  " " " " " ,pero no hay cerradura a este lado.- no pasa
! 3.-  "  " " "  no tiene la llave. No pasa.
! 4.-  "  " " "   "  "  "   , además no hay cerradura aquí. No pasa.
! 5.-  Puerta cerrada con pestillo y está al alcance del PNJ.- Pasa.
! 6.-  "  " " Y NO está al alcance pnj. No pasa.
! 7.-  Puerta cerrada pero sin llave ni pestillo. Pasa.
! 8, 9 y 10 corresponden a 1, 5 y 7 (únicos casos en los que el
! pnj atravesaría la puerta abriendola), cuando ésta se ha bloqueado. No
! pasan.
!************* AHORA DESCRIBIMOS LA ACCION -SI SE VE EL PNJ O LA PUERTA...

      if (PruebaDeAlcance(quien)) {
        print "^";
        switch (res) {
          0: print (_El) quien, " ", (string) self.entra_o_sale(), " por ", (el) self, ".^";
        1: print (_El) quien, " abre con ", (un) self.con_llave, " ", (el) self,
                 " y ", (string) self.entra_o_sale(), " por ell", (o) self, ".^";
        2, 3, 4, 6: print (_El) quien, " intenta abrir ", (el) self, " pero parece cerrad",
                          (o) self, ".^";
        5: print (_El) quien, " abre ", (el) self, " accionando el pestillo, y ",
                 (string) self.entra_o_sale(), " por ell", (o) self, ".^";
        7: print (_El) quien, " abre ", (el) self, " y ", (string) self.entra_o_sale(), " por ell",
                 (o) self, ".^";
        8: print (_El) quien, " intenta abrir con ", (un) self.con_llave, " ", (el) self,
                 ", pero parece que algo la atranca.";
          9: print (_El) quien, " acciona el pestillo de ", (el) self, " pero algo impide que l",
                   (o)self, " abra.";
         10: print (_El) quien, " intenta abrir ", (el) self, " pero parece atascada con algo.^";
        }
      } else
        if (PruebaDeAlcance(self)) {
          print "^";
          switch (res) {
            0: print (_El) quien, " ", (string) self.entra_o_sale(), " por ", (el) self, ".^";
            1: print "Oyes abrirse una cerradura, y  ", (el) self, " se abre ",
                     (string) self.entrando_o_saliendo(), " ", (el) quien, ".^";
            2, 3, 4, 6, 8, 9, 10: print "Alguien intenta abrir ", (el) self, " sin conseguirlo.^";
            5: print "Oyes descorrer un pestillo, y ", (el) self, " se abre ",
                     (string) self.entrando_o_saliendo(), " ", (el) quien, ".^";
            7: print (_El) self, " se abre y ", (string) self.entra_o_sale(), " ", (el) quien,
                     " por ell", (o)self, ".^";
          }
        }

!*********************** ESTADO DE LA PUERTA TRAS ABRIRLA ******************************
! EN FUNCION DE LA PROPIEDAD TRAS_ABRIR DEL PNJMovil... 

    if (res == 0 && self hasnt abrible)
      rtrue;
 
    !si la puerta estaba abierta y no es abrible - no es necesario ejecutar codigo de cierre...
    !esto permite crear entradas como arcos, dinteles, etc, sin puerta propiamente dicha.

    x = 0;
    
    if (quien provides tras_abrir)
      x = quien.tras_abrir;

    if (x == DEJA_ALEATORIO)
      x = random(3);

    ! PRIMERO IMPRIMIMOS EL MENSAJE SI LA ACCION ES VISIBLE POR EL JUGADOR
 
    if (PruebaDeAlcance(self) || PruebaDeAlcance(quien)) {
      if (x == DEJA_CERRADO && res == 0 or 1 or 5 or 7)
        print (_El) quien, " cierra ", (el)self, ".^";

      if (x == DEJA_CERRADO_CON && res == 0 or 1 or 5 or 7) {
        print (_El)quien, " cierra ", (el)self;

        if (self.lado_cierre == parent(quien))
          print".^";
        else
          switch (res) {
            0, 7: if (self provides con_llave)
                    if (self.con_llave in quien) {
                      print " con llave.^";
                    } else
                      print".^";
                  else
                    if (self has cerrojo)
                      print " echándole el pestillo.^";
                    else
                      print ".^";
            1: print " con llave.^";
            5: print " echándole el pestillo.^";
          } !fin de switch

      } !fin de if (x == DEJA_CERRADO_CON...

    } !fin de if (PruebaDeAlcance....

!AHORA EJECUTAMOS EL RESULTADO DE TODO EL PROCESO **************************

    switch (res) {
      0: if (x == DEJA_CERRADO or DEJA_CERRADO_CON)
           give self ~abierta;
         if (x == DEJA_CERRADO_CON && self.lado_cierre ~= parent(quien))
           if (self provides con_llave)
             if (self.con_llave in quien)
               give self cerrojoechado;
             else
               rtrue;
           else
             if (self has cerrojo)
               give self cerrojoechado;
       rtrue;
      1, 5: if (x == DEJA_ABIERTO or DEJA_CERRADO)
              give self ~cerrojoechado;
            if (x == DEJA_ABIERTO)
              give self abierta;
            if (x == DEJA_CERRADO_CON && self.lado_cierre ~= 0)
              give self ~cerrojoechado;
            rtrue;
      7: if (x == DEJA_ABIERTO) give self abierta;
         if (x == DEJA_CERRADO_CON && self.lado_cierre ~= parent(quien))
         if (self provides con_llave)
           if (self.con_llave in quien)
             give self cerrojoechado;
           else
             rtrue;
         else
           if (self has cerrojo)
             give self cerrojoechado;
         rtrue;
      default:
        rfalse;
  }
  ],   
 antes [;
  Abrir, Cerrar: 
      if (self.bloqueada) {
        print "^Algo bloquea ", (el)self, " impidiendo que l", (o)self;
        if (accion == ##Abrir)
          " abras.";
        else
          " cierres.";
      }
    Abrir:
      if (self provides con_llave)
        rfalse;
      else
        if (self has cerrojo && self has cerrojoechado)
          "^Está cerrad", (o) self, " con un pestillo.^";
    
    ! Corrige un defecto de la libreria.- en puertas cerradas con pestillo, al intentar
    ! abrirlas te informaba que estaban cerradas con llave.
    ! (supongo que un problema de traduccion (...lock)

    EcharCerrojo, QuitarCerrojo:
      if (self.lado_cierre == 0 || self.lado_cierre == localizacion)
        rfalse;
      else {
        if (self provides con_llave)
          "No hay cerradura a este lado ", (del) self, ".";
          "No existe pestillo a este lado ", (del) self, ".";
      }

    !el lado_cierre afecta tanto a los Pnjs como al jugador
  
    Examinar:
      if (self provides descripcion)
        ImprimirOEjecutar(self, descripcion);
      else        print "^";
   
      if (self.lado_cierre == 0 || localizacion == self.lado_cierre)
        if (self provides con_llave)
          print (_El) self, " puede abrirse y cerrarse desde aquí con una llave.^";
        else
          if (self has cerrojo)
            print (_El) self, " puede abrirse y cerrarse desde aquí con un pestillo.^";
            
      if (self has abrible)
        if (self has abierta)
          "Ahora está abiert", (o) self, ".^";
        else
          "Está cerrad", (o) self, ".^";
      rtrue;    
    ],
  has
    puerta estatico;


[ IniciarPuertas o i j;
  objectloop (j ofclass PnjPuerta) { 
    objectloop (o in brujula) {
      i = o.direcc_puerta;
      if (j provides i) {
        j.ladoa = j.i;
        j.dirb = i;
      }
    }
    objectloop (o in brujula) {
      i = o.direcc_puerta;
      if ((j provides i) && (j.dirb ~= i)) {
        j.ladob = j.i;
        j.dira = i;
      }
    }
    j.&esta_en-->0 = j.ladoa;
    j.&esta_en-->1 = j.ladob;
  }
];

