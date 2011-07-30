! Acciones.h
!================================================================
! Adaptación para InformATE! de la librería biplataforma 6/10
!----------------------------------------------------------------
!
! Número de Serie: 080625
!
! Esta adaptación ha sido realizada mediante un conversor automático
! y posteriores retoques manuales.
! Los comentarios permanecen en inglés, así como todas las variables y
! constantes añadidas para el soporte Glulx.
!
! Conversión (c) Zak 2000, 2001
!
! ----------------------------------------------------------------------------
!  VERBLIB:  Front end to standard verbs library.
!
!  Supplied for use with Inform 6                         Serial number 000629
!                                                                 Release 6/10
!  (c) Graham Nelson 1993, 1994, 1995, 1996, 1997, 1998, 1999
!      but freely usable (see manuals)
! ----------------------------------------------------------------------------

System_file;

Ifdef MODULE_MODE;
  Message fatalerror "*** La librería InformATE! no soporta el uso de
    módulos. Debes compilar sin la opción -M ***";
Endif; ! MODULE_MODE

Default LLEVAR_MAX       100;
Default PUNTUACION_MAX   0;
Default NUMERO_TAREAS    1;
Default PUNTOS_OBJETO    4;
Default PUNTOS_LUGAR     5;
Default OBJETO_SACO      0;
Default HAY_CURIOSIDADES 1;
Default HAY_TAREAS       1;

#Ifndef puntuacion_tareas;
  Constant MAKE__TS;
#Endif; ! puntuacion_tareas

#Ifdef MAKE__TS;
  Array puntuacion_tareas --> 0 0;
#Endif; ! MAKE__TS

Array tarea_hecha --> NUMERO_TAREAS;

#Ifndef MensajesLibreria;
  Object MensajesLibreria;
#Endif; ! MensajesLibreria;

#Ifndef NO_LUGARES;
  [ LugaresSub; Lugares1Sub(); ];
  [ ObjetosSub; Objetos1Sub(); ];
#Endif; ! NO_LUGARES

! ==================== Fin de Acciones.h ====================

! Inclusión aquí de accionm, no tiene sentido dejarlo como fichero
! aparte porque no se soporta la compilación por módulos

! accionm.h
!================================================================
! Adaptación para InformATE! de la librería biplataforma 6/10
!----------------------------------------------------------------
! Esta adaptación ha sido realizada mediante un conversor automático
! y posteriores retoques manuales.
! Los comentarios permanecen en inglés, así como todas las variables y
! constantes añadidas para el soporte Glulx.
!
! Conversión (c) Zak 2000, 2001
!
! ----------------------------------------------------------------------------
!  VERBLIBM:  Core of standard verbs library.
!
!  Supplied for use with Inform 6                         Serial number 000629
!                                                                 Release 6/10
!  (c) Graham Nelson 1993, 1994, 1995, 1996, 1997, 1998, 1999
!      but freely usable (see manuals)
! ----------------------------------------------------------------------------

! ----------------------------------------------------------------------------

[ Anuncio i;
  if (Historia ~= 0)
  {
  #Ifdef TARGET_ZCODE;
    #IfV5;
      style bold;
    #Endif; ! V5
    print (string) Historia;
    #IfV5;
      style roman;
    #Endif; ! V5
  #Ifnot; ! TARGET_GLULX;
    glk ($0086, 3); ! set header style
    print (string) Historia;
    glk ($0086, 0); ! set normal style
  #Endif; ! TARGET_
  }
  if (Titular ~= 0)
    print (string) Titular;
  #Ifdef TARGET_ZCODE;
    print "Revisión ", (0 --> 1) & $03ff, " / Número de serie ";
    for (i = 18: i < 24: i++)
      print (char) 0 -> i;
  #Ifnot; ! TARGET_GLULX;
    print "Revisión ";
    @aloads 52 0 i;
    print i;
    print " / Número de serie ";
    for (i = 0: i < 6: i++)
      print (char) 54 -> i;
  #Endif; ! TARGET_
  print " / Inform v"; inversion;
  print " Librería ", (string) RevisionLib, " ";
  #Ifdef STRICT_MODE;
    print "S";
  #Endif; ! STRICT_MODE
  #Ifdef INFIX;
    print "X";
  #Ifnot;
    #Ifdef DEBUG;
      print "D";
    #Endif; ! DEBUG
  #Endif; ! INFIX
  new_line;
];

[ VersionSub ix;
  Anuncio();
  #Ifdef TARGET_ZCODE;
    ix = 0; ! shut up compiler warning
    if (interprete_estandar > 0)
      print "Estándar del intérprete ",
        interprete_estandar / 256, ".", interprete_estandar % 256,
        " (", 0 -> $1e, (char) 0 -> $1f, ") / ";
    else
      print "Intérprete ", 0 -> $1e, " Versión ", (char) 0 -> $1f, " / ";
  #Ifnot; ! TARGET_GLULX;
    @gestalt 1 0 ix;
    print "Versión del intérprete ", ix / $10000, ".", (ix & $FF00) / $100,
      ".", ix & $FF, " / ";
    @gestalt 0 0 ix;
    print "VM ", ix / $10000, ".", (ix & $FF00) / $100,
      ".", ix & $FF, " / ";
  #Endif; ! TARGET_;
  print "Número de serie de la librería ", (string) NumSerieLib, "^";
  #Ifdef VersionIdioma;
    print (string) VersionIdioma, "^";
  #Endif; ! VersionIdioma
];

[ ErrorDeEjecucion n p1 p2;
  #Ifdef DEBUG;
    print "** Error de librería ", n, " (", p1, ",", p2, ") **^** ";
    switch (n)
    {
      1:
        print "preposición no encontrada (esto no debería ocurrir)";
      2:
        print "El valor de la propiedad no es rutina ni cadena: ~",
          (property) p2, "~ de ~", (name) p1, "~ (", p1, ")";
      3:
        print "La entrada en la lista de la propiedad no es rutina ni
          cadena: ~", (property) p2, "~ list of ~", (name) p1, "~ (", p1, ")";
      4:
        print "Hay demasiados relojes/daemons activos simultáneamente. El
          límite es la constante de la librería MAX_RELOJES (actualmente ",
          MAX_RELOJES, "). Debes incrementarla";
      5:
        print "El objeto ~", (name) p1, "~ no tiene la propiedad
          ~tiempo_restante~";
      7:
        print "El objeto ~", (name) p1, "~ sólo puede usarse como un
          jugador si tiene la propiedad ~cantidad~";
      8:
        print "Se ha intentado acceder a una entrada de un table array vacío";
      9:
        print p1, " no es un número válido para una propiedad de dirección";
      10:
        print "El objeto-jugador está fuera del árbol de objetos";
      11:
        print "El lugar ~", p1, "~ no tiene propiedad ~descripcion~";
      12:
        print "Se ha intentado fijar un pronombre inexistente con
          FijarPronombre";
      13:
        print "Un token tipo 'topic' sólo puede ir seguido por una
          preposición";
      default:
        print "(no explicado)";
    }
    " **";
  #Ifnot;
    "** Error de librería ", n, " (", p1, ", ", p2, ") **";
  #Endif;
];

! ----------------------------------------------------------------------------
!  La rutina EscribirListaDesde, un listador de objetos flexible que tiene en
!  cuenta los plurales, información del inventario, varios formatos y otras
!  cosas. Es utilizada por la librería en toda parte que quiera listar
!  cualquier cosa.
!
!  Si no hubiese objetos para listar, no imprimiría nada y devolvería falso;
!  si no, devolvería verdadero.
!
!  o es el objeto, y el estilo es un mapa de bits, cuyos bits vienen dados
!  por:
! ----------------------------------------------------------------------------

Constant NUEVALINEA_BIT  1;     ! Nueva línea tras cada entrada
Constant INDENTAR_BIT    2;     ! Indentar cada entrada por profundidad
Constant INFOTOTAL_BIT   4;     ! Info completa del inventario tras cada entrada
Constant ESPANOL_BIT     8;     ! Estilo de oración española, con comas e y
Constant RECURSIVO_BIT   16;    ! Recurse downwards with usual rules
Constant SIEMPRE_BIT     32;    ! Always recurse downwards
Constant BREVE_BIT       64;    ! More terse English style
Constant INFOPARCIAL_BIT 128;   ! Sólo info breve del inventario tras la entrada
Constant DEFINIDO_BIT    256;   ! Usar el articulo definido en la lista
Constant BANDERAUX_BIT   512;   ! At top level (only), only list objects
                                ! which have the "banderaux" attribute
Constant HAY_BIT         1024;  ! Print " is" or " are" antes list
Constant OCULTAR_BIT     2048;  ! Omitir objetos con "oculto" o "escenario":
                                ! if BANDERAUX_BIT also set, then does _not_
                                ! apply at top level, but does lower down
Constant SINARTICULO_BIT 4096;  ! No imprimir articulos, ni in ni definidos

[ SiguienteElemento o odepth;
  for (::)
  {
    o = sibling (o);
    if (o == 0)
      return 0;
    if (valor_lj ~=0 && o.listar_juntos ~= valor_lj)
      continue;
    if (estilo_ac & BANDERAUX_BIT ~= 0 && odepth == 0 && o hasnt banderaux)
      continue;
    if (estilo_ac & OCULTAR_BIT ~= 0 && (o has oculto || o has escenario))
      continue;
    return o;
  }
];

[ DeboBajarRecursivo o;
  if (estilo_ac & SIEMPRE_BIT ~= 0)
    rtrue;
  if (estilo_ac & RECURSIVO_BIT == 0)
    rfalse;
  if (o has transparente || o has soporte ||
     (o has recipiente && o has abierto))
    rtrue;
  rfalse;
];

[ ListarIguales o1 o2;
  if (child (o1) ~= 0 && DeboBajarRecursivo (o1) ~= 0)
    rfalse;
  if (child (o2) ~= 0 && DeboBajarRecursivo (o2) ~= 0)
    rfalse;

  if (estilo_ac & (INFOTOTAL_BIT + INFOPARCIAL_BIT) ~= 0)
  {
    if ((o1 hasnt puesto && o2 has puesto) ||
       (o2 hasnt puesto && o1 has puesto))
      rfalse;
    if ((o1 hasnt luz && o2 has luz) || (o2 hasnt luz && o1 has luz))
      rfalse;

    if (o1 has recipiente)                          ! Añadido en [020524]
    {                                               ! para evitar que dos
      if (o2 hasnt recipiente)                      ! recipientes plurales
        rfalse;                                     ! idénticos sean listados
      if ((o1 has abierto && o2 hasnt abierto)      ! juntos si no tienen
         || (o2 has abierto && o1 hasnt abierto))   ! ambos el mismo valor
        rfalse;                                     ! del atributo abierto,
    }                                               ! pues antes se mostraba
    else                                            ! la información de este
      if (o2 has recipiente)                        ! atributo de uno de ellos
        rfalse;                                     ! como válida para ambos.
  }

  return Identicos (o1,o2);
];

[ OrdenarJuntos obj value;
!  print "Sorting together possessions of ",
!         (object) obj, " by value ", value, "^";
!  for (x=child(obj):x~=0:x=sibling(x))
!      print (the) x, " no: ", x, " lt: ", x.listar_juntos, "^";
  while (child(obj)~=0)
  {   if (child(obj).listar_juntos~=value) move child(obj) to obj_afuera;
      else move child(obj) to obj_adentro;
  }
  while (child(obj_adentro)~=0)
      move child(obj_adentro) to obj;
  while (child(obj_afuera)~=0)
      move child(obj_afuera) to obj;
];

[ OrdenarLista obj i k l;
!  print "^^Sorting out list from ", (name) obj, "^  ";
!  for (i=child(localizacion):i~=0:i=sibling(i))
!      print (name) i, " --> ";
!  new_line;
 .AP_SOL;
  for (i=obj:i~=0:i=sibling(i))
  {   k=i.listar_juntos;
      if (k~=0)
      {   ! print "Scanning ", (name) i, " with lt=", k, "^";
          for (i=sibling(i):i~=0 && i.listar_juntos==k:) i=sibling(i);
              if (i==0) rfalse;
          !print "First not in block is ", (name) i,
          ! " with lt=", i.listar_juntos, "^";
          for (l=sibling(i):l~=0:l=sibling(l))
              if (l.listar_juntos==k)
              {   OrdenarJuntos(parent(obj), k);
!  print "^^After ST:^  ";
!  for (i=child(localizacion):i~=0:i=sibling(i))
!      print (name) i, " --> ";
!  new_line;
                  obj = child(parent(obj));
                  jump AP_SOL;
              }
      }
  }
];

#Ifdef TARGET_ZCODE;

[ Imprimir__Espacios n;  ! To avoid a bug occurring in Inform 6.01 to 6.10
  if (n==0) return; spaces n; ];

#Ifnot; ! TARGET_GLULX;

[ Imprimir__Espacios n;
  while (n > 0) {
    @streamchar ' ';
    n = n - 1;
  }
];

#Endif; ! TARGET_

[ EscribirListaDesde o style depth;
  if (o==child(parent(o)))
  {   OrdenarLista(o); o=child(parent(o)); }
  estilo_ac=style;
  indentacion_eld=0; EscribeListaR(o,depth);
  rtrue;
];

[ EscribeListaR o depth stack_pointer  classes_p sizes_p i j k k2 l m n q senc
 mr;

  if (depth>0 && o==child(parent(o)))
  {   OrdenarLista(o); o=child(parent(o)); }
  for (::)
  {
      if (o==0) rfalse;
      if (estilo_ac & BANDERAUX_BIT ~= 0 && depth==0 && o hasnt banderaux)
      {   o = sibling(o); continue; }
      if (estilo_ac & OCULTAR_BIT ~= 0
          && (o has oculto || o has escenario))
      {   o=sibling(o); continue; }
      break;
  }

  classes_p = encajan_clases + stack_pointer;
  sizes_p   = lista_encajan + stack_pointer;

  for (i=o,j=0:i~=0 && (j+stack_pointer)<128:i=SiguienteElemento(i,depth),j++)
  {   classes_p->j=0;
      if (i.plural~=0) k++;
  }

  if (estilo_ac & HAY_BIT ~= 0)
  {   if (j==1 && o hasnt nombreplural)
          print (string) HAY__TX; else print (string) HAYP__TX;
      if (estilo_ac & NUEVALINEA_BIT ~= 0) print ":^"; else print (char) ' ';
      estilo_ac = estilo_ac - HAY_BIT;
  }

  stack_pointer = stack_pointer+j+1;

  if (k<2) jump EconomyVersion;   ! It takes two to plural
  n=1;
  for (i=o,k=0:k<j:i=SiguienteElemento(i,depth),k++)
      if (classes_p->k==0)
      {   classes_p->k=n; sizes_p->n=1;
          for (l=SiguienteElemento(i,depth), m=k+1:l~=0 && m<j:
               l=SiguienteElemento(l,depth), m++)
              if (classes_p->m==0 && i.plural~=0 && l.plural~=0)
              {   if (ListarIguales(i,l)==1)
                  {   sizes_p->n = sizes_p->n + 1;
                      classes_p->m = n;
                  }
              }
          n++;
      }
  n--;

  for (i=1, j=o, k=0: i<=n: i++, senc++)
  {   while (((classes_p->k) ~= i)
             && ((classes_p->k) ~= -i)) { k++; j=SiguienteElemento(j,depth); }
      m=sizes_p->i;
      if (j==0) mr = 0;
      else
      {   if (j.listar_juntos~=0 or valor_lj
              && ZRegion(j.listar_juntos)==2 or 3
              && j.listar_juntos==mr) senc--;
          mr=j.listar_juntos;
      }
  }
  senc--;

  for (i=1, j=o, k=0, mr=0: senc>=0: i++, senc--)
  {   while (((classes_p->k) ~= i)
             && ((classes_p->k) ~= -i)) { k++; j=SiguienteElemento(j,depth); }
      if (j.listar_juntos~=0 or valor_lj)
      {   if (j.listar_juntos==mr) { senc++; jump Omit_FL2; }
          k2=SiguienteElemento(j,depth);
          if (k2==0 || k2.listar_juntos~=j.listar_juntos) jump Omit_WL2;
          k2=ZRegion(j.listar_juntos);
          if (k2==2 or 3)
          {   q=j; tamanio_listando=1; l=k; m=i;
              while (m<n && q.listar_juntos==j.listar_juntos)
              {   m++;
                  while (((classes_p->l) ~= m)
                         && ((classes_p->l) ~= -m))
                  {   l++; q=SiguienteElemento(q,depth); }
                  if (q.listar_juntos==j.listar_juntos) tamanio_listando++;
              }
!              print " [", tamanio_listando, "] ";
              if (tamanio_listando==1) jump Omit_WL2;
              if (estilo_ac & INDENTAR_BIT ~= 0)
                  Imprimir__Espacios(2*(depth+indentacion_eld));
              if (k2==3)
              {   q=0; for (l=0:l<tamanio_listando:l++) q=q+sizes_p->(l+i);
                  EnglishNumber(q); print " ";
                  print (string) j.listar_juntos;
                  if (estilo_ac & ESPANOL_BIT ~= 0) print " (";
                  if (estilo_ac & INDENTAR_BIT ~= 0) print ":^";
              }
              q=estilo_ac;
              if (k2~=3)
              {   etapa_inventario=1;
                  parser_uno=j; parser_dos=depth+indentacion_eld;
                  if (EjecutarRutinas(j,listar_juntos)==1) jump Omit__Sublist2;
              }

#Ifdef TARGET_ZCODE;
              @push valor_lj; @push listando_junto; @push tamanio_listando;
#Ifnot; ! TARGET_GLULX;
              @copy valor_lj sp;
              @copy listando_junto sp;
              @copy tamanio_listando sp;
#Endif; ! TARGET_;
              valor_lj=j.listar_juntos; listando_junto=j; indentacion_eld++;
              EscribeListaR(j,depth,stack_pointer); indentacion_eld--;
#Ifdef TARGET_ZCODE;
              @pull tamanio_listando; @pull listando_junto; @pull valor_lj;
#Ifnot; ! TARGET_GLULX;
              @copy sp tamanio_listando;
              @copy sp listando_junto;
              @copy sp valor_lj;
#Endif; ! TARGET_;

              if (k2==3)
              {   if (q & ESPANOL_BIT ~= 0) print ")";
              }
              else
              {   etapa_inventario=2;
                  parser_uno=j; parser_dos=depth+indentacion_eld;
                  EjecutarRutinas(j,listar_juntos);
              }
             .Omit__Sublist2;
              if (q & NUEVALINEA_BIT ~= 0 && estilo_ac & NUEVALINEA_BIT == 0)
                  new_line;
              estilo_ac=q;
              mr=j.listar_juntos;
              jump Omit_EL2;
          }
      }

     .Omit_WL2;
      if (EscribeAntesElemento(j,depth,-senc)==1) jump Omit_FL2;
      if (sizes_p->i == 1)
      {   if (estilo_ac & SINARTICULO_BIT ~= 0) print (name) j;
          else
          {   if (estilo_ac & DEFINIDO_BIT ~= 0) print (el) j;
	      else print (un) j;
          }
      }
      else
      {   if (estilo_ac & DEFINIDO_BIT ~= 0)
              PonerArticuloDelante(j, 1, sizes_p->i);
          print (number) sizes_p->i, " ";
          ImprimirOEjecutar(j,plural,1);
      }
      if (sizes_p->i > 1 && j hasnt nombreplural)    ! Añadido para evitar el
      {                                              ! bug de concordancia de
        give j nombreplural;                         ! número al mostrar info
        EscribeTrasElemento(j,depth,stack_pointer);  ! sobre objetos plurales
        give j ~nombreplural;                        ! idénticos. Como en:
      }                                              ! "Puedes ver dos cajas
      else                                           ! (que está cerrada)."
        EscribeTrasElemento(j,depth,stack_pointer);

     .Omit_EL2;
      if (estilo_ac & ESPANOL_BIT ~= 0)
      {   if (senc==1) print (string) Y__TX;
          if (senc>1) print ", ";
      }
     .Omit_FL2;
  }
  rtrue;

  .EconomyVersion;

  n=j;

  for (i=1, j=o: i<=n: j=SiguienteElemento(j,depth), i++, senc++)
  {   if (j.listar_juntos~=0 or valor_lj
          && ZRegion(j.listar_juntos)==2 or 3
          && j.listar_juntos==mr) senc--;
      mr=j.listar_juntos;
  }

  for (i=1, j=o, mr=0: i<=senc: j=SiguienteElemento(j,depth), i++)
  {   if (j.listar_juntos~=0 or valor_lj)
      {   if (j.listar_juntos==mr) { i--; jump Omit_FL; }
          k=SiguienteElemento(j,depth);
          if (k==0 || k.listar_juntos~=j.listar_juntos) jump Omit_WL;
          k=ZRegion(j.listar_juntos);
          if (k==2 or 3)
          {   if (estilo_ac & INDENTAR_BIT ~= 0)
                  Imprimir__Espacios(2*(depth+indentacion_eld));
              if (k==3)
              {   q=j; l=0;
                  do
                  {   q=SiguienteElemento(q,depth); l++;
                  } until (q==0 || q.listar_juntos~=j.listar_juntos);
                  EnglishNumber(l); print " ";
                  print (string) j.listar_juntos;
                  if (estilo_ac & ESPANOL_BIT ~= 0) print " (";
                  if (estilo_ac & INDENTAR_BIT ~= 0) print ":^";
              }
              q=estilo_ac;
              if (k~=3)
              {   etapa_inventario=1;
                  parser_uno=j; parser_dos=depth+indentacion_eld;
                  if (EjecutarRutinas(j,listar_juntos)==1) jump Omit__Sublist;
              }

#Ifdef TARGET_ZCODE;
              @push valor_lj; @push listando_junto; @push tamanio_listando;
#Ifnot; ! TARGET_GLULX;
              @copy valor_lj sp;
              @copy listando_junto sp;
              @copy tamanio_listando sp;
#Endif; ! TARGET_;
              valor_lj=j.listar_juntos; listando_junto=j; indentacion_eld++;
              EscribeListaR(j,depth,stack_pointer); indentacion_eld--;
#Ifdef TARGET_ZCODE;
              @pull tamanio_listando; @pull listando_junto; @pull valor_lj;
#Ifnot; ! TARGET_GLULX;
              @copy sp tamanio_listando;
              @copy sp listando_junto;
              @copy sp valor_lj;
#Endif; ! TARGET_;

              if (k==3)
              {   if (q & ESPANOL_BIT ~= 0) print ")";
              }
              else
              {   etapa_inventario=2;
                  parser_uno=j; parser_dos=depth+indentacion_eld;
                  EjecutarRutinas(j,listar_juntos);
              }
             .Omit__Sublist;
              if (q & NUEVALINEA_BIT ~= 0 && estilo_ac & NUEVALINEA_BIT == 0)
 new_line;
              estilo_ac=q;
              mr=j.listar_juntos;
              jump Omit_EL;
          }
      }
     .Omit_WL;
      if (EscribeAntesElemento(j,depth,i-senc)==1) jump Omit_FL;
      if (estilo_ac & SINARTICULO_BIT ~= 0) print (name) j;
      else
      {   if (estilo_ac & DEFINIDO_BIT ~= 0) print (el) j;
          else print (un) j;
      }
      EscribeTrasElemento(j,depth,stack_pointer);

     .Omit_EL;
      if (estilo_ac & ESPANOL_BIT ~= 0)
      {   if (i==senc-1) print (string) Y__TX;
          if (i<senc-1) print ", ";
      }
     .Omit_FL;
  }
];

[ EscribeAntesElemento o depth sentencepos  flag;
  if (estilo_ac & INDENTAR_BIT)
 Imprimir__Espacios(2*(depth+indentacion_eld));

  if (estilo_ac & INFOTOTAL_BIT ~= 0)
  {   if (o.listarse~=0)
      {   etapa_inventario=1;
          flag=ImprimirOEjecutar(o,listarse,1);
          if (flag==1)
          {   if (estilo_ac & ESPANOL_BIT)
              {   if (sentencepos == -1) print (string) Y__TX;
                  if (sentencepos < -1) print ", ";
              }
              if (estilo_ac & NUEVALINEA_BIT) new_line;
          }
      }
  }
  return flag;
];

[ EscribeTrasElemento o depth stack_p  flag flag2 flag3 p combo;

  if (estilo_ac & INFOPARCIAL_BIT) {
      combo = 0;
      if (o has luz && localizacion hasnt luz) combo = combo + 1;
      if (o has recipiente && o hasnt abierto) combo = combo + 2;
      if ((o has recipiente && (o has abierto || o has transparente))
          && (child(o)==0))                    combo = combo + 4;
      if (combo) M__L (##ListaMiscelanea, combo, o);
  }  ! Fin del procesamiento de INFOPARCIAL_BIT

  if (estilo_ac & INFOTOTAL_BIT) {
      if (o.listarse ~= 0)
      {   etapa_inventario=2;
          if (EjecutarRutinas(o,listarse)~=0)
          {   if (estilo_ac & NUEVALINEA_BIT ~= 0) new_line;
              rtrue;
          }
      }
      if (o has luz && o has puesto)
      {    M__L(##ListaMiscelanea, 8, o); flag2=1; }
      else
      {   if (o has luz) {  M__L(##ListaMiscelanea, 9, o); flag2=1; }
          if (o has puesto)  {  M__L(##ListaMiscelanea, 10, o); flag2=1; }
      }
      if (o has recipiente)
          if (o has abrible)
          {   if (flag2==1) print (string) Y__TX;
              else M__L(##ListaMiscelanea, 11, o);
              if (o has abierto)
                  if (child (o)) M__L (##ListaMiscelanea, 12, o);
                  else           M__L (##ListaMiscelanea, 13, o);
              else
                  if (o has cerrojo && o has cerrojoechado)
                      M__L(##ListaMiscelanea, 15, o);
                  else M__L(##ListaMiscelanea, 14, o);
              flag2=1;
          }
          else
              if (child(o)==0 && o has transparente)
                  if (flag2==1) M__L(##ListaMiscelanea, 16, o);
                  else M__L(##ListaMiscelanea, 17, o);
      if (flag2==1) print ")";
  }

  if (estilo_ac & OCULTAR_BIT == 0)
  {   flag3 = children(o);
      flag2 = child(o);
  }
  else
  {   flag3 = 0;
      objectloop (p in o)
          if (p hasnt oculto && p hasnt escenario) { flag3++; flag2 = p; }
  }

  if (estilo_ac & SIEMPRE_BIT ~= 0 && flag3>0)
  {   if (estilo_ac & ESPANOL_BIT ~= 0) M__L(##ListaMiscelanea, 18, o);
      flag=1;
  }

  if (estilo_ac & RECURSIVO_BIT ~= 0 && flag3>0) {
      if (o has soporte) {
          if (estilo_ac & ESPANOL_BIT) {
              if (estilo_ac & BREVE_BIT)
                   M__L(##ListaMiscelanea, 19, o);
              else M__L(##ListaMiscelanea, 20, o);
              if (o has animado) print (string) QUIEN__TX;
              else print (string) ELCUAL__TX;
          }
          flag=1;
      }
      if (o has recipiente && (o has abierto || o has transparente)) {
          if (estilo_ac & ESPANOL_BIT) {
              if (estilo_ac & BREVE_BIT)
                   M__L(##ListaMiscelanea, 21, o);
              else M__L(##ListaMiscelanea, 22, o);
              if (o has animado) print (string) QUIEN__TX;
              else print (string) ELCUAL__TX;
          }
          flag=1;
      }
  }

  if (flag==1 && (estilo_ac & ESPANOL_BIT))
      if (flag3 > 1 || flag2 has nombreplural)
           print (string) HAYP2__TX;
      else print (string) HAY2__TX;

  if (estilo_ac & NUEVALINEA_BIT) new_line;

  if (flag==1)
  {   o = child(o);
#Ifdef TARGET_ZCODE;
      @push valor_lj; @push listando_junto; @push tamanio_listando;
#Ifnot; ! TARGET_GLULX;
      @copy valor_lj sp;
      @copy listando_junto sp;
      @copy tamanio_listando sp;
#Endif; ! TARGET_;
      valor_lj = 0; listando_junto = 0; tamanio_listando = 0;
      EscribeListaR(o, depth+1, stack_p);
#Ifdef TARGET_ZCODE;
      @pull tamanio_listando; @pull listando_junto; @pull valor_lj;
#Ifnot; ! TARGET_GLULX;
      @copy sp tamanio_listando;
      @copy sp listando_junto;
      @copy sp valor_lj;
#Endif; ! TARGET_;
      if (estilo_ac & BREVE_BIT) print ")";
  }
];

! ----------------------------------------------------------------------------
!  Much better menus can be created using the optional library extension
!  "menus.h".  These are provided for compatibility with previous practice:
! ----------------------------------------------------------------------------

[ LowKey_Menu menu_choices EntryR ChoiceR lines main_title i j;
  anidacion_menu++;
 .LKRD;
  elemento_menu=0;
  lines=indirect(EntryR);
  main_title=nombre_elemento;

  print "--- "; print (string) main_title; print " ---^^";

  if (menu_choices ofclass Routine) menu_choices.call();
  else print (string) menu_choices;

  for (::)
  {   M__L(##Miscelanea, 52, lines);
      print "> ";

#Ifdef TARGET_ZCODE;
      #IfV3; read buffer parse;
      #Ifnot; read buffer parse DibujarLineaEstado;
      #Endif;
      j = parse->1; ! number of words
#Ifnot; ! TARGET_GLULX;
      KeyboardPrimitive(buffer, parse);
      j = parse-->0; ! cantidad of words
#Endif; ! TARGET_

      i=parse-->1;
      if (j==0 || (i==TERMINAR1__WD or TERMINAR2__WD))
      {   anidacion_menu--; if (anidacion_menu>0) rfalse;
          if (banderafin==0) <<Mirar>>;
          rfalse;
      }
      i=IntentarNumero(1);
      if (i==0) jump LKRD;
      if (i<1 || i>lines) continue;
      elemento_menu=i;
      j=indirect(ChoiceR);
      if (j==2) jump LKRD;
      if (j==3) rfalse;
  }
];

#Ifdef TARGET_ZCODE;

#IfV3;
[ DoMenu menu_choices EntryR ChoiceR;
  LowKey_Menu(menu_choices,EntryR,ChoiceR);
];
#Endif;

#IfV5;
[ DoMenu menu_choices EntryR ChoiceR
         lines main_title main_wid cl i j oldcl pkey;

  if (bandera_guapo==0)
      return LowKey_Menu(menu_choices,EntryR,ChoiceR);

  anidacion_menu++;
  elemento_menu=0;
  lines=indirect(EntryR);
  main_title=nombre_elemento; main_wid=ancho_elemento;
  cl=7;

  .ReDisplay;
      oldcl=0;
      @erase_window $ffff;
      i=lines+7;
      @split_window i;
      i = 0->33;
      if (i==0) i=80;
      @set_window 1;
      @set_cursor 1 1;
      style reverse;
      spaces(i); j=i/2-main_wid;
      @set_cursor 1 j;
      print (string) main_title;
      @set_cursor 2 1; spaces(i);
      @set_cursor 2 2; print (string) TECLASIG__TX;
      j=i-12; @set_cursor 2 j; print (string) TECLAANT__TX;
      @set_cursor 3 1; spaces(i);
      @set_cursor 3 2; print (string) RKEY__TX;
      j=i-17; @set_cursor 3 j;
      if (anidacion_menu==1) print (string) QKEY1__TX;
                      else print (string) QKEY2__TX;
      style roman;
      @set_cursor 5 2; font off;

      if (menu_choices ofclass String) print (string) menu_choices;
      else menu_choices.call();

      for (::)
      {   if (cl ~= oldcl)
          {   if (oldcl>0) { @set_cursor oldcl 4; print " "; }
              @set_cursor cl 4; print ">";
          }
          oldcl=cl;
          @read_char 1 -> pkey;
          if (pkey==TECLASIG1__KY or TECLASIG2__KY or 130)
          {   cl++; if (cl==7+lines) cl=7; continue;
          }
          if (pkey==TECLAANT1__KY or TECLAANT2__KY or 129)
          {   cl--; if (cl==6)  cl=6+lines; continue;
          }
          if (pkey==QKEY1__KY or QKEY2__KY or 27 or 131) break;
          if (pkey==10 or 13 or 132)
          {   @set_window 0; font on;
              new_line; new_line; new_line;

              elemento_menu=cl-6;
              EntryR.call();

              @erase_window $ffff;
              @split_window 1;
              i = 0->33; if (i == 0) i = 80;
              @set_window 1; @set_cursor 1 1; style reverse; spaces(i);
              j=i/2-ancho_elemento;
              @set_cursor 1 j;
              print (string) nombre_elemento;
              style roman; @set_window 0; new_line;

              i = ChoiceR.call();
              if (i==2) jump ReDisplay;
              if (i==3) break;

              M__L(##Miscelanea, 53);
              @read_char 1 -> pkey; jump ReDisplay;
          }
      }

      anidacion_menu--; if (anidacion_menu>0) rfalse;
      font on; @set_cursor 1 1;
      @erase_window $ffff; @set_window 0;
      new_line; new_line; new_line;
      if (banderafin==0) <<Mirar>>;
];
#Endif;

#Ifnot; ! TARGET_GLULX

[ DoMenu menu_choices EntryR ChoiceR
    winwid winhgt lines main_title main_wid cl i oldcl pkey;

  if (bandera_guapo==0 || gg_statuswin==0)
    return LowKey_Menu(menu_choices, EntryR, ChoiceR);

  anidacion_menu++;
  elemento_menu=0;
  lines=indirect(EntryR);
  main_title=nombre_elemento;
  main_wid=ancho_elemento;

  cl = 0;

  ! If we printed "hit arrow keys" here, it would be appropriate to
  ! check for the availability of Glk input keys. But we actually
  ! print "hit N/P/Q". So it's reasonable to silently accept Glk
  ! arrow key codes as secondary options.

  .ReDisplay;
    glk($002A, gg_statuswin); ! window_clear
    glk($002A, gg_mainwin); ! window_clear
    glk($002F, gg_statuswin); ! set_window
    StatusLineHeight(lines+7);
    glk($0025, gg_statuswin, gg_arguments, gg_arguments+4); ! window_get_size
    winwid = gg_arguments-->0;
    winhgt = gg_arguments-->1;
    glk($0086, 4); ! set subheader style
    glk($002B, gg_statuswin, winwid/2-main_wid, 0); ! window_move_cursor
    print (string) main_title;
    glk($002B, gg_statuswin, 1, 1); ! window_move_cursor
    print (string) TECLASIG__TX;
    glk($002B, gg_statuswin, winwid-13, 1); ! window_move_cursor
    print (string) TECLAANT__TX;
    glk($002B, gg_statuswin, 1, 2); ! window_move_cursor
    print (string) RKEY__TX;
    glk($002B, gg_statuswin, winwid-18, 2); ! window_move_cursor
    if (anidacion_menu==1)
      print (string) QKEY1__TX;
    else
      print (string) QKEY2__TX;
    glk($0086, 0); ! set normal style

    glk($002B, gg_statuswin, 1, 4); ! window_move_cursor
    if (menu_choices ofclass String)
      print (string) menu_choices;
    else
      menu_choices.call();

    oldcl = -1;

    for (::) {
      if (cl ~= oldcl) {
        if (cl < 0 || cl >= lines)
          cl = 0;
        if (oldcl >= 0) {
          glk($002B, gg_statuswin, 3, oldcl+6);
          print (char) ' ';
        }
        oldcl = cl;
        glk($002B, gg_statuswin, 3, oldcl+6);
        print (char) '>';
      }
      pkey = KeyCharPrimitive(gg_statuswin, true);
      if (pkey == $80000000)
        jump ReDisplay;
      if (pkey==TECLASIG1__KY or TECLASIG2__KY or $fffffffb) {
        cl++;
        if (cl >= lines)
          cl = 0;
        continue;
      }
      if (pkey==TECLAANT1__KY or TECLAANT2__KY or $fffffffc) {
        cl--;
        if (cl < 0)
          cl = lines-1;
        continue;
      }
      if (pkey==QKEY1__KY or QKEY2__KY or $fffffff8 or $fffffffe)
        break;
      if (pkey==$fffffffa or $fffffffd) {
        glk($002F, gg_mainwin); ! set_window
        new_line; new_line; new_line;
        elemento_menu = cl+1;
        EntryR.call();

        glk($002A, gg_statuswin); ! window_clear
        glk($002A, gg_mainwin); ! window_clear
        glk($002F, gg_statuswin); ! set_window
        StatusLineHeight(1);
        glk($0025, gg_statuswin, gg_arguments, gg_arguments+4); ! window_get_size
        winwid = gg_arguments-->0;
        winhgt = gg_arguments-->1;
        glk($0086, 4); ! set subheader style
        glk($002B, gg_statuswin, winwid/2-ancho_elemento, 0); ! window_move_cursor
        print (string) nombre_elemento;
        glk($0086, 0); ! set normal style

        glk($002F, gg_mainwin); ! set_window
        new_line;
        i = ChoiceR.call();
        if (i==2) jump ReDisplay;
        if (i==3) break;
        M__L(##Miscelanea, 53);
        pkey = KeyCharPrimitive(gg_mainwin, 1);
        jump ReDisplay;
      }
    }

  ! done with this menu...
  anidacion_menu--;
  if (anidacion_menu>0) rfalse;
  glk($002F, gg_mainwin); ! set_window
  glk($002A, gg_mainwin); ! window_clear
  new_line; new_line; new_line;
  if (banderafin==0) <<Mirar>>;
];

#Endif; ! TARGET_

! ----------------------------------------------------------------------------
!   A cunning routine (which could have been a daemon, but isn't, for the
!   sake of efficiency) to move objects which could be in many rooms about
!   so that the jugador never catches one not in place
! ----------------------------------------------------------------------------

[ MoverObjetosFlotantes i k l m address flag;
  objectloop (i)
  {   address=i.&esta_en;
      if (address~=0 && i hasnt ausente)
      {   if (ZRegion(address-->0)==2)
          {   if (i.esta_en() ~= 0) move i to localizacion; else remove i;
          }
          else
          {   k=i.#esta_en;
              for (l=0: l<k/WORDSIZE: l++)
              {   m=address-->l;
                  if (m==localizacion || m in localizacion)
                  {   if (i notin localizacion) move i to localizacion;
                      flag = true;
                  }
              }
              if (flag == false) { if (parent(i)) remove i; }
          }
      }
  }
];

! ----------------------------------------------------------------------------
!   Two little routines for moving the jugador safely.
! ----------------------------------------------------------------------------

[ JugadorA newplace flag;
  move jugador to newplace;
  while (parent(newplace)~=0) newplace=parent(newplace);
  localizacion=newplace;
  localizacion_real=localizacion; MoverObjetosFlotantes();
  AjustarLuz(1);
  if (flag==0) <Mirar>;
  if (flag==1) { AnotarLlegada(); PuntuacionLlegada(); }
  if (flag==2) MirarSub(1);
];

[ MoverJugador direc; <Ir direc>; <Mirar>; ];

! ----------------------------------------------------------------------------
!   The handy SiONo routine, and some "meta" verbs
! ----------------------------------------------------------------------------

[ SiONo i;
  for (::)
  {
#Ifdef TARGET_ZCODE;
      bufferaux->0=2;
      parseaux->0=1;
      if (localizacion == nothing || parent(jugador) == nothing)
        read bufferaux parseaux;
      else read bufferaux parseaux DibujarLineaEstado;
#Ifnot; ! TARGET_GLULX;
      KeyboardPrimitive(bufferaux, parseaux);
#Endif; ! TARGET_
      QuitarAcentos(bufferaux, parseaux);      ! [030305]
      i=parseaux-->1;
      if (i==SI1__WD or SI2__WD or SI3__WD) rtrue;
      if (i==NO1__WD or NO2__WD or NO3__WD) rfalse;
      M__L(##Finalizar,1); print "> ";
  }
];

#Ifdef TARGET_ZCODE;

[ FinalizarSub; M__L(##Finalizar,2); if (SiONo()~=0) quit; ];

[ ReiniciarSub; M__L(##Reiniciar,1);
  if (SiONo()~=0) { @restart; M__L(##Reiniciar,2); }
];

[ RestaurarSub;
  restore Rmaybe;
  return M__L(##Restaurar,1);
  .RMaybe; M__L(##Restaurar,2);
];

[ SalvarSub flag;
  #IfV5;
  @save -> flag;
  switch (flag) {
      0: M__L(##Salvar,1);
      1: M__L(##Salvar,2);
      2: M__L(##Restaurar,2);
  }
  #Ifnot;
  save Smaybe;
  return M__L(##Salvar,1);
  .SMaybe; M__L(##Salvar,2);
  #Endif;
];

[ VerificarSub;
  @verify ?Vmaybe;
  jump Vwrong;
  .Vmaybe; return M__L(##Verificar,1);
  .Vwrong;
  M__L(##Verificar,2);
];

[ ActivarTranscripcionSub;
  modo_transcripcion = ((0-->8) & 1);
  if (modo_transcripcion) return M__L(##ActivarTranscripcion,1);
  @output_stream 2;
  if (((0-->8) & 1) == 0) return M__L(##ActivarTranscripcion,3);
  M__L(##ActivarTranscripcion,2); VersionSub();
  modo_transcripcion = true;
];

[ DesactivarTranscripcionSub;
  modo_transcripcion = ((0-->8) & 1);
  if (modo_transcripcion == false) return M__L(##DesactivarTranscripcion,1);
  M__L(##DesactivarTranscripcion,2);
  @output_stream -2;
  if ((0-->8) & 1) return M__L(##DesactivarTranscripcion,3);
  modo_transcripcion = false;
];

#Ifnot; ! TARGET_GLULX;

[ FinalizarSub;
  M__L(##Finalizar,2);
  if (SiONo() ~= 0)
    quit;
];

[ ReiniciarSub;
  M__L(##Reiniciar,1);
  if (SiONo()~=0) {
    @restart;
    M__L(##Reiniciar,2);
  }
];

[ RestaurarSub res fref;
  fref = glk($0062, $01, $02, 0); ! fileref_create_by_prompt
  if (fref == 0)
    jump RFailed;
  gg_savestr = glk($0042, fref, $02, GG_SAVESTR_ROCK); ! stream_open_file
  glk($0063, fref); ! fileref_destroy
  if (gg_savestr == 0)
    jump RFailed;

  @restore gg_savestr res;

  glk($0044, gg_savestr, 0); ! stream_close
  gg_savestr = 0;

.RFailed;
  M__L(##Restaurar,1);
];

[ SalvarSub res fref;
  fref = glk($0062, $01, $01, 0); ! fileref_create_by_prompt
  if (fref == 0)
    jump SFailed;
  gg_savestr = glk($0042, fref, $01, GG_SAVESTR_ROCK); ! stream_open_file
  glk($0063, fref); ! fileref_destroy
  if (gg_savestr == 0)
    jump SFailed;

  @save gg_savestr res;

  if (res == -1) {
    ! The jugador actually just typed "restore". We're going to print
    !  M__L(##Restaurar,2); the Z-Code Inform library does this correctly
    ! now. But first, we have to recover all the Glk objects; the values
    ! in our global variables are all wrong.
    GGRecoverObjects();
    glk($0044, gg_savestr, 0); ! stream_close
    gg_savestr = 0;
    return M__L(##Restaurar,2);
  }

  glk($0044, gg_savestr, 0); ! stream_close
  gg_savestr = 0;

  if (res == 0)
    return M__L(##Salvar,2);

.SFailed;
  M__L(##Salvar,1);
];

[ VerificarSub res;
  @verify res;
  if (res == 0)
    return M__L(##Verificar,1);
  M__L(##Verificar,2);
];

[ ActivarTranscripcionSub;
  if (gg_scriptstr ~= 0)
    return M__L(##ActivarTranscripcion,1);

  if (gg_scriptfref == 0) {
    ! fileref_create_by_prompt
    gg_scriptfref = glk($0062, $102, $05, GG_SCRIPTFREF_ROCK);
    if (gg_scriptfref == 0)
      jump S1Failed;
  }
  ! stream_open_file
  gg_scriptstr = glk($0042, gg_scriptfref, $05, GG_SCRIPTSTR_ROCK);
  if (gg_scriptstr == 0)
    jump S1Failed;

  glk($002D, gg_mainwin, gg_scriptstr); ! window_set_echo_stream
  M__L(##ActivarTranscripcion,2);
  VersionSub();
  return;

.S1Failed;
  M__L(##ActivarTranscripcion,3);
];

[ DesactivarTranscripcionSub;
  if (gg_scriptstr == 0)
    return M__L(##DesactivarTranscripcion,1);

  M__L(##DesactivarTranscripcion,2);
  glk($0044, gg_scriptstr, 0); ! stream_close
  gg_scriptstr = 0;
];

#Endif; ! TARGET_;

#Ifndef NO_PUNTUACION;
  [ ActivarNotificacionSub;
    modo_notificar = 1;
    M__L (##ActivarNotificacion);
  ];

  [ DesactivarNotificacionSub;
    modo_notificar = 0;
    M__L (##DesactivarNotificacion);
  ];
#Endif; ! NO_PUNTUACION

#Ifndef NO_LUGARES;
  [ Lugares1Sub i j k;
    M__L (##Lugares);
    objectloop (i has visitado)
      j++;

    objectloop (i has visitado)
    {
      print (name) i;
      k++;
      if (k == j)
        ".";
      if (k == j - 1)
        print (string) Y__TX;
      else
        print ", ";
    }
  ];

  [ Objetos1Sub i j f;
    M__L (##Objetos, 1);
    objectloop (i has movido)
    {
      f = 1;
      print (the) i;
      j = parent (i);

      if (j)
      {
        if (j == jugador)
        {
          if (i has puesto)
            M__L (##Objetos, 3, i);
          else
            M__L (##Objetos, 4, i);
          jump Obj__Ptd;
        }

        if (j has animado)
        {
          M__L (##Objetos, 5, j);
          jump Obj__Ptd;
        }
        if (j has visitado)
        {
          M__L (##Objetos, 6, j);
          jump Obj__Ptd;
         }
        if (j has recipiente)
        {
          M__L (##Objetos, 8, j);
          jump Obj__Ptd;
        }
        if (j has soporte)
        {
          M__L (##Objetos, 9, j);
          jump Obj__Ptd;
        }
        if (j has entrable)
        {
          M__L (##Objetos, 7, j);
          jump Obj__Ptd;
        }
      }

      M__L (##Objetos, 10, i);
      .Obj__Ptd;
        new_line;
    }
    if (f == 0)
      M__L (##Objetos, 2);
  ];
#Endif; ! NO_LUGARES

! ----------------------------------------------------------------------------
!   El sistema de puntuación
! ----------------------------------------------------------------------------

#Ifndef NO_PUNTUACION;
  [ PuntuacionSub;
    M__L(##Puntuacion);
    ImprimirRango();
  ];
#Endif; ! NO_PUNTUACION

[ Conseguido num;
  if (tarea_hecha->num==0)
  {   tarea_hecha->num=1;
      puntuacion = puntuacion + puntuacion_tareas->num;
  }
];

[ ImpNumAlin m n;
  print "  ";
  n=m;
  if (n<0)    { n=-m; n=n*10; }
  if (n<10)   { print "   "; jump Panuml; }
  if (n<100)  { print "  ";  jump Panuml; }
  if (n<1000) { print " "; }
.Panuml;
  print m, " ";
];

#Ifndef NO_PUNTUACION;
  [ PuntuacionTotalSub i;
    PuntuacionSub();
    if (puntuacion == 0 || HAY_TAREAS == 1)
      rfalse;
    new_line;
    M__L (##PuntuacionTotal, 1);

    for (i = 0: i < NUMERO_TAREAS: i++)
      if (tarea_hecha->i == 1)
      {
        ImpNumAlin (puntuacion_tareas->i);
        ImprimirTareas(i);
      }

    if (puntos_cosas ~= 0)
    {
      ImpNumAlin (puntos_cosas);
      M__L (##PuntuacionTotal, 2);
    }
    if (puntos_sitios ~= 0)
    {
      ImpNumAlin (puntos_sitios);
      M__L (##PuntuacionTotal, 3);
    }
    new_line;
    ImpNumAlin (puntuacion);
    M__L (##PuntuacionTotal, 4);
  ];
#Endif; ! NO_PUNTUACION

! ----------------------------------------------------------------------------
!   Real verbs start here: Inventory
! ----------------------------------------------------------------------------

[ InvAnchoSub;
  estilo_inventario = ESPANOL_BIT + RECURSIVO_BIT + INFOTOTAL_BIT;
  <Inv>;
];

[ InvAltoSub;
  estilo_inventario = NUEVALINEA_BIT + RECURSIVO_BIT + INDENTAR_BIT +
                      INFOTOTAL_BIT;
  <Inv>;
];

[ InvSub x;
  if (child(jugador)==0) return M__L(##Inv,1);
  if (estilo_inventario==0) return InvAltoSub();

  M__L(##Inv,2);
  if (estilo_inventario & NUEVALINEA_BIT ~= 0) print ":^"; else print " ";

  EscribirListaDesde(child(jugador), estilo_inventario, 1);
  if (estilo_inventario & ESPANOL_BIT ~= 0) print ".^";

#Ifndef PRONOMBRES_AMANO;
  objectloop(x in jugador) ActualizarPronombre(x);
#Endif;
  x = 0; ! To prevent a "not used" error
  RutinasDespues();
];

! ----------------------------------------------------------------------------
!   The object tree and determining the possibility of moves
! ----------------------------------------------------------------------------

[ AntepasadoComun o1 o2 i j;
  !  Find the nearest object indirectly containing o1 and o2,
  !  or return 0 if there is no common ancestor.

  i = o1;
  while (i ~= 0)
  {
      j = o2;
      while (j ~= 0)
      {   if (j == i) return i;
          j = parent(j);
      }
      i = parent(i);
  }
  return 0;
];

[ ContieneIndirectamente o1 o2;
  !  Does o1 indirectly contain o2?  (Same as testing if their common
  !  ancestor is o1.)

  while (o2~=0)
  {   if (o1==o2) rtrue;
      o2=parent(o2);
  }
  rfalse;
];

[ ObjetoEnAlcancePorAlgo item i j k l m;
  i = item;
  while (parent(i) ~= 0) i=parent(i);
  objectloop (j .& suma_al_alcance)
  {   l = j.&suma_al_alcance;
      k = (j.#suma_al_alcance)/WORDSIZE;
      if (l-->0 ofclass Routine) continue;
      for (m=0:m<k:m++)
          if (l-->m == i)
              return j;
  }
  rfalse;
];

[ ObjetoEsIntocable item flag1 flag2 ancestor i;

  ! Determine if there's any barrier preventing the jugador from moving
  ! things to "item".  Return false if no barrier; otherwise print a
  ! suitable message and return true.
  ! If flag1 is set, do not print any message.
  ! If flag2 is set, also apply Take/Remove restrictions.

  ! If the item has been added to scope by something, it's first necessary
  ! for that something to be touchable.

  i = ObjetoEnAlcancePorAlgo(item);
  if (i ~= 0)
  {   if (ObjetoEsIntocable(i)) return;
      ! An item immediately added to scope
  }

  ancestor = AntepasadoComun(jugador, item);

  ! First, a barrier between the jugador and the ancestor.  The jugador
  ! can only be in a sequence of entrable objects, and only closed
  ! containers form a barrier.

  if (jugador ~= ancestor)
  {   i = parent(jugador);
      while (i~=ancestor)
      {   if (i has recipiente && i hasnt abierto)
          {   if (flag1) rtrue;
              return M__L(##Coger,9,i);
          }
          i = parent(i);
      }
  }

  ! Second, a barrier between the item and the ancestor.  The item can
  ! be carried by someone, part of a piece of machinery, in or on top
  ! of something and so on.

  if (item ~= ancestor)
  {   i = parent(item);
      while (i~=ancestor)
      {   if (flag2 && i hasnt recipiente && i hasnt soporte)
          {   if (i has animado)
              {   if (flag1) rtrue;
                  return M__L(##Coger,6,i);
              }
              if (i has transparente)
              {   if (flag1) rtrue;
                  return M__L(##Coger,7,i);
              }
              if (flag1) rtrue;
              return M__L(##Coger,8,item);
          }
          if (i has recipiente && i hasnt abierto)
          {   if (flag1) rtrue;
              return M__L(##Coger,9,i);
          }
          i = parent(i);
      }
  }
  rfalse;
];

[ IntentarCogerObjeto item     ancestor after_recipient i j k;
  ! Try to transfer the given item to the jugador: return false
  ! if successful, true if unsuccessful, printing a suitable message
  ! in the latter case.

  ! People cannot ordinarily be taken.
  if (item == jugador) return M__L(##Coger,2);
  if (item has animado) return M__L(##Coger,3,item);

  ancestor = AntepasadoComun(jugador, item);

  if (ancestor == 0)
  {   i = ObjetoEnAlcancePorAlgo(item);
      if (i ~= 0) ancestor = AntepasadoComun(jugador, i);
  }

  ! Are jugador and item in totally different places?

  if (ancestor == 0) return M__L(##Coger,8,item);

  ! Is the jugador indirectly inside the item?
  if (ancestor == item) return M__L(##Coger,4,item);

  ! Does the jugador already directly contain the item?
  if (item in jugador) return M__L(##Coger,5,item);

  ! Can the jugador touch the item, or is there (e.g.) a closed recipiente
  ! in the way?
  if (ObjetoEsIntocable(item,false,true)) return;

  ! The item is now known to be accessible.

  ! Consult the immediate possessor of the item, if it's in a recipiente
  ! which the jugador is not in.

  i=parent(item);
  if (i ~= ancestor && (i has recipiente || i has soporte))
  {   after_recipient=i;
      k=accion; accion=##DejarSalir;
      if (EjecutarRutinas(i,antes)~=0) { accion=k; rtrue; }
      accion=k;
  }

  if (item has escenario) return M__L(##Coger,10,item);
  if (item has estatico)  return M__L(##Coger,11,item);

  ! The item is now known to be available for taking.  Is the jugador
  ! carrying too much?  If so, possibly juggle items into the rucksack
  ! to make room.

  k=0; objectloop (j in jugador) if (j hasnt puesto) k++;

  if (k >= ValorOEjecutar(jugador,capacidad))
  {   if (OBJETO_SACO~=0)
      {   if (parent(OBJETO_SACO)~=jugador)
              return M__L(##Coger,12);
          j=0;
          objectloop (k in jugador)
              if (k~=OBJETO_SACO && k hasnt puesto && k hasnt luz) j=k;

          if (j~=0)
          {   M__L(##Coger,13,j);
              tate_callao = 1; <Meter j OBJETO_SACO>; tate_callao = 0;
              if (j notin OBJETO_SACO) rtrue;
          }
          else return M__L(##Coger,12);
      }
      else return M__L(##Coger,12);
  }

  ! Transfer the item.

  move item to jugador;

  ! Send "despues" message to the object letting go of the item, if any.

  if (after_recipient~=0)
  {   k=accion; accion=##DejarSalir;
      if (EjecutarRutinas(after_recipient,despues)~=0) { accion=k; rtrue; }
      accion=k;
  }
  rfalse;
];

! ----------------------------------------------------------------------------
!   Object movement verbs
! ----------------------------------------------------------------------------

[ CogerSub;
  if (amodo_noposeido==0 || uno notin jugador)
      if (IntentarCogerObjeto(uno)) rtrue;
  if (RutinasDespues()==1) rtrue;
  modo_noposeido=amodo_noposeido;
  if (tate_callao==1) rtrue;
  M__L(##Coger,1,uno); ! [001115] Añadido "uno"
];

[ SacarSub i;
  i=parent(uno);
  if (i has recipiente && i hasnt abierto) return M__L(##Sacar,1,uno);
  if (i~=otro) return M__L(##Sacar,2,uno);
  if ((i has animado) && (i hasnt recipiente)) return M__L(##Coger,6,i);
  if (IntentarCogerObjeto(uno)) rtrue;
  accion=##Sacar; if (RutinasDespues()==1) rtrue;
  accion=##Coger;   if (RutinasDespues()==1) rtrue;

  if (tate_callao==1) rtrue;
  return M__L(##Sacar,3,uno);
];

[ DejarSub;
  if (uno == jugador) return M__L(##PonerSobre, 4);
  if (uno in parent(jugador)) return M__L(##Dejar,1,uno);
  if (uno notin jugador) return M__L(##Dejar,2,uno);
  if (uno has puesto)
  {   M__L(##Dejar,3,uno);
      <Desvestir uno>;
      if (uno has puesto && uno in jugador) rtrue;
  }
  move uno to parent(jugador);
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  return M__L(##Dejar,4,uno);
];

[ PonerSobreSub ancestor;
  accion_recibir=##PonerSobre;
  if (otro == obj_abajo || jugador in otro) <<Dejar uno>>;
  if (parent(uno)~=jugador) return M__L(##PonerSobre,1,uno);

  ancestor = AntepasadoComun(uno, otro);
  if (ancestor == uno) return M__L(##PonerSobre,2,uno);
  if (ObjetoEsIntocable(otro)) return;

  if (otro ~= ancestor)
  {   accion=##Recibir;
      if (EjecutarRutinas(otro,antes)~=0) { accion=##PonerSobre; return; }
      accion=##PonerSobre;
  }
  if (otro hasnt soporte) return M__L(##PonerSobre,3,otro);
  if (ancestor == jugador) return M__L(##PonerSobre,4);
  if (uno has puesto)
  {   M__L(##PonerSobre,5,uno); <Desvestir uno>; if (uno has puesto) return;
  }

  if (children(otro)>=ValorOEjecutar(otro,capacidad))
      return M__L(##PonerSobre,6,otro);

  move uno to otro;

  if (RutinasDespues()==1) return;

  if (otro ~= ancestor)
  {   accion=##Recibir;
      if (EjecutarRutinas(otro,despues)~=0) { accion=##PonerSobre; return; }
      accion=##PonerSobre;
  }
  if (tate_callao==1) return;
  if (banderamulti==1) return M__L(##PonerSobre,7);
  M__L(##PonerSobre,8,uno);
];

[ MeterSub ancestor;
  accion_recibir = ##Meter;
  if (otro==obj_abajo || jugador in otro) <<Dejar uno>>;
  if (parent(uno)~=jugador) return M__L(##Meter,1,uno);

  ancestor = AntepasadoComun(uno, otro);
  if (ancestor == uno) return M__L(##Meter, 5, uno);
  if (ObjetoEsIntocable(otro)) return;

  if (otro ~= ancestor)
  {   accion=##Recibir;
      if (EjecutarRutinas(otro,antes)~=0) { accion=##Meter; rtrue; }
      accion=##Meter;
      if (otro has recipiente && otro hasnt abierto)
          return M__L(##Meter,3,otro);
  }
  if (otro hasnt recipiente) return M__L(##Meter,2,otro);

  if (uno has puesto)
  {   M__L(##Meter,6,uno); <Desvestir uno>; if (uno has puesto) return;
  }

  if (children(otro) >= ValorOEjecutar(otro,capacidad))
      return M__L(##Meter,7,otro);

  move uno to otro;

  if (RutinasDespues()==1) rtrue;

  if (otro ~= ancestor)
  {   accion=##Recibir;
      if (EjecutarRutinas(otro,despues)~=0) { accion=##Meter; rtrue; }
      accion=##Meter;
  }
  if (tate_callao==1) rtrue;
  if (banderamulti==1) return M__L(##Meter,8,uno);
  M__L(##Meter,9,uno);
];

! ----------------------------------------------------------------------------
!   Empties and transfers are routed through the actions above
! ----------------------------------------------------------------------------

[ TransferirSub;
  if (uno notin jugador && IntentarCogerObjeto(uno)) return;
  if (otro has soporte) <<PonerSobre uno otro>>;
  if (otro == obj_abajo) <<Dejar uno>>;
  <<Meter uno otro>>;
];

[ VaciarSub;
  otro=obj_abajo; VaciarEnSub();
];

[ VaciarEnSub i j k flag;
  if (uno == otro) return M__L(##VaciarEn,4);
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt recipiente) return M__L(##VaciarEn,1,uno);
  if (uno hasnt abierto) return M__L(##VaciarEn,2,uno);
  if (otro~=obj_abajo)
  {   if (otro hasnt soporte)
      {   if (otro hasnt recipiente) return M__L(##VaciarEn,1,otro);
          if (otro hasnt abierto) return M__L(##VaciarEn,2,otro);
      }
  }
  i=child(uno); k = children(uno);
  if (i==0) return M__L(##VaciarEn,3,uno);
  while (i~=0)
  {   j=sibling(i);
      flag = 0;
      if (ObjetoEsIntocable(uno)) flag = 1;
      if (uno hasnt recipiente) flag = 1;
      if (uno hasnt abierto) flag = 1;
      if (otro~=obj_abajo)
      {   if (otro hasnt soporte)
          {   if (otro hasnt recipiente) flag = 1;
              if (otro hasnt abierto) flag = 1;
          }
      }
      if (k-- == 0) flag = 1;
      if (flag) break;
      if (tate_callao == 0) print (name) i, ": ";
      <Transferir i otro>;
      i=j;
  }
];

! ----------------------------------------------------------------------------
!   Gifts
! ----------------------------------------------------------------------------

[ DarSub;
  if (parent(uno)~=jugador) return M__L(##Dar,1,uno);
  if (otro==jugador)  return M__L(##Dar,2,uno);
  if (EjecutarVida(otro,##Dar)~=0) rfalse;
  M__L(##Dar,3,otro);
];

[ GiveRSub; <Dar otro uno>; ];

[ MostrarSub;
  if (parent(uno)~=jugador) return M__L(##Mostrar,1,uno);
  if (otro==jugador) <<Examinar uno>>;
  if (EjecutarVida(otro,##Mostrar)~=0) rfalse;
  M__L(##Mostrar,2,otro);
];

[ ShowRSub; <Mostrar otro uno>; ];

! ----------------------------------------------------------------------------
!   Travelling around verbs
! ----------------------------------------------------------------------------

[ MeterseSub ancestor j k l;
    if (uno in Brujula) <<Ir uno>>;
    ! Corrección del comportamiento para que funcione como se explica en
    ! DocumentATE. Gracias a 'Presi' por detectar el bug
    if (uno has puerta) {
        if ((palabra_verbo == 'baja' && uno.direcc_puerta == arriba)  ! [030305]
            ||
            (palabra_verbo == 'sube' && uno.direcc_puerta == abajo))  ! [071030]
            return M__L(##Meterse,2,uno);
    	k=0; l=uno.direcc_puerta;
    	if (ZRegion(l)==2) l=EjecutarRutinas(uno,direcc_puerta);
    	objectloop (j in Brujula) {
      	    if (j.direcc_puerta == l) k=j;
    	}
    	if (k) <<Ir k>>;
    	"[***Error de programación, la puerta '", (name) uno, "' no tiene
	    propiedad direcc_puerta***]^";
    }

    ! Cambiadas las referencias a la acción Entrar por Meterse
    ! Gracias a 'Presi' por detectar el bug
    if (jugador in uno) return M__L(##Meterse,1,uno);
    if (uno hasnt entrable) return M__L(##Meterse,2,uno);
    if (uno has recipiente && uno hasnt abierto) return M__L(##Meterse,3,uno);

    if (parent(jugador) ~= parent(uno))
    {   ancestor = AntepasadoComun(jugador, uno);
      	if (ancestor == jugador or 0) return M__L(##Meterse,4,uno);
      	while (jugador notin ancestor)
      	{   j = parent(jugador);
            k = tate_callao;
            if (parent(j) ~= ancestor || uno ~= ancestor)
            {   M__L(##Meterse,6,j);
              	tate_callao = 1;
            }
            <Salir>;
            tate_callao = k;
            if (jugador in j) return;
      	}
      	if (jugador in uno) return;
      	if (uno notin ancestor)
      	{   j = parent(uno);
            while (parent(j) ~= ancestor) j = parent(j);
            M__L(##Meterse,7,j);
            k = tate_callao; tate_callao = 1;
            <Meterse j>;
            tate_callao = k;
            if (jugador notin j) return;
            <<Meterse uno>>;
      	}
    }

    move jugador to uno;
    if (RutinasDespues()==1) rtrue;
    if (tate_callao==1) rtrue;
    M__L(##Meterse,5,uno);

    ! Reajuste de pronombres
    #Ifndef PRONOMBRES_AMANO;
      LocalPronom (uno);
    #Endif;

    Local(uno);
];

[ SalirseSub;
  if (parent(jugador)==uno) <<Salir>>;
  M__L(##Salirse,1,uno);
];

[ SalirSub p;
  p=parent(jugador);
  if (p==localizacion || (localizacion==LaOscuridad && p==localizacion_real))
  {   if ((localizacion.afuera~=0)
          || (localizacion == LaOscuridad && localizacion_real.afuera ~= 0))
        <<Ir obj_afuera>>;
      return M__L(##Salir,1);
  }
  if (p has recipiente && p hasnt abierto)
      return M__L(##Salir,2,p);

  move jugador to parent(p);

  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Salir,3,p); MirarSub(1);
];

[ IrAmbiguoSub; M__L(##IrAmbiguo); ];

[ EntrarSub;
  <<Ir obj_adentro>>;
];

[ IrSub i j k df movewith thedir old_loc;

  if (otro ~= 0 && otro notin Brujula
      && ObjetoEsIntocable(otro)) return;

  old_loc = localizacion;
  movewith=0;
  i=parent(jugador);
  if ((localizacion ~= LaOscuridad && i ~= localizacion) ||
      (localizacion == LaOscuridad && i ~= localizacion_real))
  {   j=localizacion;
      if (localizacion == LaOscuridad) localizacion = localizacion_real;
      k=EjecutarRutinas(i,antes); if (k~=3) localizacion=j;
      if (k==1)
      {   movewith=i; i=parent(i);
      }
      else
      {   if (k==0) M__L(##Ir,1,i);
          rtrue;
      }
  }

  thedir=uno.direcc_puerta;
  if (ZRegion(thedir)==2) thedir=EjecutarRutinas(uno,direcc_puerta);

  j=i.thedir; k=ZRegion(j);
  if (k==3) { print (string) j; new_line; rfalse; }
  if (k==2) { j=EjecutarRutinas(i,thedir);
              if (j==1) rtrue;
            }

  if (k==0 || j==0)
  {   if (i.no_puedes_ir ~= 0) return ImprimirOEjecutar(i, no_puedes_ir);
      else return M__L(##Ir, 2);
  }

  if (j has puerta)
  {   if (j has oculto) return M__L(##Ir,2);
      if (j hasnt abierto)
      {   if (uno==obj_arriba) return M__L(##Ir,3,j);
          if (uno==obj_abajo) return M__L(##Ir,4,j);
          return M__L(##Ir,5,j);
      }
      k=EjecutarRutinas(j,puerta_a);
      if (k==0) return M__L(##Ir,6,j);
      if (k==1) rtrue;
      j = k;
  }
  if (movewith==0) move jugador to j; else move movewith to j;

  localizacion=j; MoverObjetosFlotantes();
  df=HayLuz(j);
  if (df~=0) { localizacion=j; localizacion_real=j; banderaluz=1; }
  else
  {   if (old_loc == LaOscuridad)
      {   CaminarAOscuras();
          if (banderafin~=0) rtrue;
      }
      localizacion_real=j;
      localizacion = LaOscuridad; banderaluz = 0;
  }
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  MirarSub(1);
];

! ----------------------------------------------------------------------------
!   Describing the world.  DecirQueHaySobre(object) does just that (producing
!   no text if nothing except possibly "escenario" and "oculto" items are).
!   Local(object) runs through the "tail end" of a Look-style room
!   descripcion for the contents of the object, printing up suitable
!   descriptions as it goes.
! ----------------------------------------------------------------------------

[ DecirQueHaySobre descon j f;
  if (descon==parent(jugador)) rfalse;
  objectloop (j in descon)
      if (j hasnt oculto && j hasnt escenario) f=1;
  if (f==0) rfalse;
  M__L(##Mirar, 4, descon); rtrue;
];

[ NoSoportaAlJugador o i;
  i=parent(jugador);
  while (i~=0 && i~=techo_de_visibilidad)
  {   if (i==o) rfalse;
      i = parent(i);
      if (i~=0 && i hasnt soporte) rtrue;
  }
  rtrue;
];

! Parte de la rutina Local que reajusta los pronombres
[ LocalPronom descin o;
  objectloop (o in descin)
    if (o hasnt oculto && NoSoportaAlJugador(o))
      ActualizarPronombre(o);
];

[ Local descin text1 text2 o k p j f2 flag;

  objectloop (o in descin) give o ~banderaux;

  k=0;
  objectloop (o in descin)
      if (o hasnt oculto && NoSoportaAlJugador(o))
      {
         if (o hasnt escenario)
         {   give o banderaux; k++;
             p=inicial; f2=0;
             if ((o has puerta || o has recipiente)
                 && o has abierto && o provides si_abierto)
             {   p = si_abierto; f2 = 1; jump Prop_Chosen; }
             if ((o has puerta || o has recipiente)
                 && o hasnt abierto && o provides si_cerrado)
             {   p = si_cerrado; f2 = 1; jump Prop_Chosen; }
             if (o has conmutable
                 && o has encendido && o provides si_encendido)
             {   p = si_encendido; f2 = 1; jump Prop_Chosen; }
             if (o has conmutable
                 && o hasnt encendido && o provides si_apagado)
             {   p = si_apagado; f2 = 1; }

             .Prop_Chosen;

             if (o hasnt movido || o.describir~=NULL || f2==1)
             {   if (o.describir~=NULL && EjecutarRutinas(o,describir)~=0)
                 {   flag=1;
                     give o ~banderaux; k--;
                 }
                 else
                 {   j=o.p;
                     if (j~=0)
                     {   new_line;
                         ImprimirOEjecutar(o,p);
                         flag=1;
                         give o ~banderaux; k--;
                         if (o has soporte && child(o)~=0) DecirQueHaySobre(o);
                     }
                 }
             }
         }
         else
             if (o has soporte && child(o)~=0) DecirQueHaySobre(o);
      }

  if (k==0) return 0;

  if (text1~=0)
  {   new_line;
      if (flag==1) text1=text2;
      print (string) text1, " ";
      EscribirListaDesde(child(descin),
          ESPANOL_BIT + RECURSIVO_BIT + INFOPARCIAL_BIT + BREVE_BIT +
          OCULTAR_BIT + BANDERAUX_BIT);
      return k;
  }

  if (flag==1) M__L(##Mirar,5,descin); else M__L(##Mirar,6,descin);
];

! ----------------------------------------------------------------------------
!   Looking.  MirarSub(1) is allowed to abbreviate long descriptions, but
!     MirarSub(0) (which is what happens when the Look accion is generated)
!     isn't.  (Except that these are over-ridden by the jugador-set modomirar.)
! ----------------------------------------------------------------------------

[ ModoM1Sub; modomirar=1; print (string) Historia; M__L(##ModoM1); ];  ! Brief

[ ModoM2Sub; modomirar=2; print (string) Historia; M__L(##ModoM2); ];  ! Verbose

[ ModoM3Sub; modomirar=3; print (string) Historia; M__L(##ModoM3); ];  ! Superbrief

[ AnotarLlegada descin;
  if (localizacion == LaOscuridad) { ultimadesc = LaOscuridad; return; }
  if (localizacion~=ultimadesc)
  {   if (localizacion.inicial~=0) ImprimirOEjecutar(localizacion, inicial);
      descin = localizacion;
      LugarNuevo();
      ultimadesc = descin;
  }
];

[ PuntuacionLlegada;
  if (localizacion hasnt visitado)
  {
    give localizacion visitado;
    if (localizacion has valepuntos)
    {
      puntuacion = puntuacion + PUNTOS_LUGAR;
      puntos_sitios = puntos_sitios + PUNTOS_LUGAR;
    }
  }
];

[ FindVisibilityLevels visibility_levels;
  visibility_levels = 1;
  techo_de_visibilidad = parent(jugador);
  while ((parent(techo_de_visibilidad) ~= 0)
         && (techo_de_visibilidad hasnt recipiente
             || techo_de_visibilidad has abierto
             || techo_de_visibilidad has transparente))
  {   techo_de_visibilidad = parent(techo_de_visibilidad);
      visibility_levels++;
  }
  return visibility_levels;
];

[ MirarSub allow_abbrev  visibility_levels i j k;
  if (parent(jugador)==0) return ErrorDeEjecucion(10);

  .MovedByInitial;
  if (localizacion == LaOscuridad)
  {   techo_de_visibilidad = LaOscuridad;
      AnotarLlegada();
  }
  else
  {   visibility_levels = FindVisibilityLevels();
      if (techo_de_visibilidad == localizacion)
      {   AnotarLlegada();
          if (techo_de_visibilidad ~= localizacion) jump MovedByInitial;
      }
  }

  !   Printing the top line: e.g.
  !   Octagonal Room (on the table) (as Frodo)

  new_line;
#Ifdef TARGET_ZCODE;
  style bold;
#Ifnot; ! TARGET_GLULX;
  glk($0086, 4); ! set subheader style
#Endif; ! TARGET_
  if (visibility_levels == 0) print (name) LaOscuridad;
  else
  {   if (techo_de_visibilidad ~= localizacion) print (The) techo_de_visibilidad;
      else print (name) techo_de_visibilidad;
  }
#Ifdef TARGET_ZCODE;
  style roman;
#Ifnot; ! TARGET_GLULX;
  glk($0086, 0); ! set normal style
#Endif; ! TARGET_

  for (j=1, i=parent(jugador):j<visibility_levels:j++, i=parent(i))
      if (i has soporte) M__L(##Mirar,1,i);
                      else M__L(##Mirar,2,i);

  if (bandera_imprime_jugador==1) M__L(##Mirar,3,jugador);
  new_line;

   ! Reajuste de pronombres
   #Ifndef PRONOMBRES_AMANO;
     if (visibility_levels == 0)
       LocalPronom (LaOscuridad);
     else {
       for (j = visibility_levels: j > 0: j--) {
         for (i = jugador, k = 0: k < j: k++)
           i = parent (i);
         LocalPronom(i);
       }
     }
   #Endif;

  !   The room descripcion (if visible)

  if (modomirar<3 && techo_de_visibilidad==localizacion)
  {   if ((allow_abbrev~=1) || (modomirar==2) || (localizacion hasnt visitado))
      {   if (localizacion.describir~=NULL) EjecutarRutinas(localizacion,describir);
          else
          {   if (localizacion.descripcion==0) ErrorDeEjecucion(11,localizacion);
              else ImprimirOEjecutar(localizacion,descripcion);
          }
      }
  }

  if (visibility_levels == 0) Local (LaOscuridad);
  else
  {   for (i=jugador, j=visibility_levels: j>0: j--, i=parent(i))
          give i banderaux;

      for (j=visibility_levels: j>0: j--)
      {   for (i=jugador, k=0: k<j: k++) i=parent(i);
          if (i.descripcion_dentro~=0)
          {   new_line; ImprimirOEjecutar(i,descripcion_dentro); }
          Local(i);
      }
  }

  RutinaMirar();
  PuntuacionLlegada();

  accion=##Mirar;
  if (RutinasDespues()==1) rtrue;
];

[ ExaminarSub i;
  if (localizacion == LaOscuridad) return M__L (##Examinar, 1);
  i=uno.descripcion;
  if (i==0)
  {   if (uno has recipiente) <<BuscarEn uno>>;
      if (uno has conmutable) { M__L(##Examinar,3,uno); rfalse; }
      return M__L(##Examinar,2,uno);
  }
  ImprimirOEjecutar(uno, descripcion);
  if (uno has conmutable) M__L(##Examinar,3,uno);
  if (RutinasDespues()==1) rtrue;
];

[ MirarDebajoSub;
  if (localizacion == LaOscuridad) return M__L (##MirarDebajo, 1);
  M__L(##MirarDebajo,2);
];

[ BuscarEnSub i f;
  if (localizacion == LaOscuridad) return M__L (##BuscarEn, 1, uno);
  if (ObjetoEsIntocable(uno)) return;
  objectloop (i in uno) if (i hasnt oculto && i hasnt escenario) f=1;
  if (uno has soporte)
  {   if (f==0) return M__L(##BuscarEn,2,uno);
      return M__L(##BuscarEn,3,uno);
  }
  if (uno hasnt recipiente) return M__L(##BuscarEn,4,uno);
  if (uno hasnt transparente && uno hasnt abierto)
      return M__L(##BuscarEn,5,uno);
  if (RutinasDespues()==1) rtrue;

  i=children(uno);
  if (f==0) return M__L(##BuscarEn,6,uno);
  M__L(##BuscarEn,7,uno);
];

! ----------------------------------------------------------------------------
!   Verbs which change the state of objects without moving them
! ----------------------------------------------------------------------------

[ QuitarCerrojoSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt cerrojo) return M__L(##QuitarCerrojo,1,uno);
  if (uno hasnt cerrojoechado)   return M__L(##QuitarCerrojo,2,uno);
  if (uno.con_llave~=otro) return M__L(##QuitarCerrojo,3,otro);
  give uno ~cerrojoechado;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##QuitarCerrojo,4,uno);
];

[ EcharCerrojoSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt cerrojo) return M__L(##EcharCerrojo,1,uno);
  if (uno has cerrojoechado)     return M__L(##EcharCerrojo,2,uno);
  if (uno has abierto)       return M__L(##EcharCerrojo,3,uno);
  if (uno.con_llave~=otro) return M__L(##EcharCerrojo,4,otro);
  give uno cerrojoechado;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##EcharCerrojo,5,uno);
];

[ EncenderSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt conmutable) return M__L(##Encender,1,uno);
  if (uno has encendido) return M__L(##Encender,2,uno);
  give uno encendido;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Encender,3,uno);
];

[ ApagarSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt conmutable) return M__L(##Apagar,1,uno);
  if (uno hasnt encendido) return M__L(##Apagar,2,uno);
  give uno ~encendido;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Apagar,3,uno);
];

[ AbrirSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt abrible) return M__L(##Abrir,1,uno);
  if (uno has cerrojoechado)     return M__L(##Abrir,2,uno);
  if (uno has abierto)       return M__L(##Abrir,3,uno);
  give uno abierto;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  if (uno has recipiente && uno hasnt transparente && child(uno)~=0
      && ContieneIndirectamente(uno,jugador)==0)
      return M__L(##Abrir,4,uno);
  M__L(##Abrir,5,uno);
];

[ CerrarSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt abrible) return M__L(##Cerrar,1,uno);
  if (uno hasnt abierto)     return M__L(##Cerrar,2,uno);
  give uno ~abierto;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Cerrar,3,uno);
];

[ DesvestirSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt puesto) return M__L(##Desvestir,1,uno);
  give uno ~puesto;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Desvestir,2,uno);
];

[ QuitarSub;
    if (otro) <<Sacar uno otro>>;
    if (uno in jugador) <<Desvestir uno>>;
    <<Coger uno>>;
];


[ VestirSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt prenda)  return M__L(##Vestir,1,uno);
  if (parent(uno)~=jugador) return M__L(##Vestir,2,uno);
  if (uno has puesto)        return M__L(##Vestir,3,uno);
  give uno puesto;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Vestir,4,uno);
];

[ ComerSub;
  if (ObjetoEsIntocable(uno)) return;
  if (uno hasnt comestible) return M__L(##Comer,1,uno);
  if (uno has puesto)
  {   M__L(##Dejar,3,uno);
      <Desvestir uno>;
      if (uno has puesto && uno in jugador) rtrue;
  }
  remove uno;
  if (RutinasDespues()==1) rtrue;
  if (tate_callao==1) rtrue;
  M__L(##Comer,2,uno);
];

! ----------------------------------------------------------------------------
!   Verbs which are really just stubs (anything which happens for these
!   actions must happen in antes rules)
! ----------------------------------------------------------------------------

[ PermitirEmpujarDir i;
  if (parent (otro) ~= Brujula)        return M__L (##EmpujarDir, 2, uno);
  if (otro == obj_arriba or obj_abajo) return M__L (##EmpujarDir, 3, uno);
  RutinasDespues(); i = uno; move i to jugador;
  <Ir otro>;
  if (localizacion == LaOscuridad) move i to localizacion_real;
  else                             move i to localizacion;
];

[ ResponderSub;
  if (otro ~= 0 && EjecutarVida (otro, ##Responder) ~= 0) rfalse;
  M__L (##Responder, 1, uno);
];

[ PreguntarSub;
  if (EjecutarVida (uno, ##Preguntar) ~= 0) rfalse;
  M__L (##Preguntar, 1, uno);
];

[ PedirSub;
  if (uno == jugador) <<Inv>>;
  M__L (##Orden, 1, uno);
];

[ AtacarSub;
  if (ObjetoEsIntocable (uno)) return;
  if (uno has animado && EjecutarVida (uno, ##Atacar) ~= 0) rfalse;
  M__L (##Atacar, 1, uno);
];

[ SoplarSub; M__L (##Soplar, 1, uno); ];

[ QuemarSub; M__L (##Quemar, 1, uno); ];

[ ComprarSub; M__L (##Comprar, 1, uno); ];

[ TreparSub; M__L (##Trepar, 1, uno); ];

[ ConsultarSub; M__L (##Consultar, 1, uno); ];

[ CortarSub; M__L (##Cortar, 1, uno); ];

[ ExcavarSub; M__L (##Excavar, 1, uno); ];

[ BeberSub; M__L (##Beber, 1, uno); ];

[ LlenarSub; M__L (##Llenar, 1, uno); ];

[ SaltarSub; M__L (##Saltar, 1, uno); ];

[ SaltarSobreSub; M__L (##SaltarSobre, 1, uno); ];

[ BesarSub;
  if (ObjetoEsIntocable (uno)) return;
  if (EjecutarVida (uno, ##Besar) ~= 0) rfalse;
  if (uno == jugador) return M__L (##Tocar, 3, uno);
  M__L (##Besar, 1, uno);
];

[ EscucharSub; M__L (##Escuchar, 1, uno); ];

[ SosoSub; M__L (##Soso, 1, uno); ];

[ NoSub; M__L (##No); ];

[ RezarSub; M__L (##Rezar, 1, uno); ];

[ TirarSub;
  if (ObjetoEsIntocable (uno)) return;
  if (uno has estatico)  return M__L (##Tirar, 1, uno);
  if (uno has escenario) return M__L (##Tirar, 2, uno);
  if (uno has animado)   return M__L (##Tirar, 4, uno);
  M__L (##Tirar, 3, uno);
];

[ EmpujarSub;
  if (ObjetoEsIntocable (uno)) return;
  if (uno has estatico)  return M__L (##Empujar, 1,uno);
  if (uno has escenario) return M__L (##Empujar, 2,uno);
  if (uno has animado)   return M__L (##Empujar, 4, uno);
  M__L (##Empujar, 3, uno);
];

[ EmpujarDirSub; M__L (##EmpujarDir, 1, uno); ];

[ FrotarSub; M__L (##Frotar, 1, uno); ];

[ FijarSub; M__L (##Fijar, 1, uno); ];

[ PonerASub; M__L (##PonerA, 1, uno); ];

[ CantarSub; M__L (##Cantar, 1, uno); ];

[ DormirSub; M__L (##Dormir, 1, uno); ];

[ OlerSub; M__L (##Oler, 1, uno); ];

[ LoSientoSub; M__L (##LoSiento, 1, uno); ];

[ RetorcerSub;
  if (ObjetoEsIntocable (uno)) return;
  if (uno has animado) return M__L (##Retorcer, 1, uno);
  M__L (##Retorcer, 2, uno);
];

[ TacosSub; M__L (##Tacos, 1, uno); ];

[ NadarSub; M__L (##Nadar, 1, uno); ];

[ ColumpiarSub; M__L (##Columpiar, 1, uno); ];

[ ProbarSub; M__L (##Probar, 1, uno); ];

[ HablarSub;
  if (uno == jugador) return M__L (##Hablar, 1, uno);
  if (EjecutarVida (uno, ##Hablar) ~= 0) rfalse;
  M__L (##Hablar, 2, uno);
];

[ PensarSub; M__L (##Pensar, 1, uno); ];

[ LanzarSub;
  if (ObjetoEsIntocable (uno)) return;
  if (otro > 1) {
      accion = ##RecibirLanzamiento;
      if (EjecutarRutinas (otro, antes) ~= 0) { accion = ##Lanzar; rtrue; }
      accion = ##Lanzar;
  }
  if (uno has puesto) {
      M__L (##Dejar, 3, uno);
      <Desvestir uno>;
      if (uno has puesto && uno in jugador) rtrue;
  }
  if (otro hasnt animado) return M__L (##Lanzar, 1);
  if (EjecutarVida (otro, ##Lanzar) ~= 0) rfalse;
  M__L (##Lanzar, 2, uno);
];

[ AtarSub; M__L (##Atar, 1, uno); ];

[ TocarSub;
  if (uno == jugador)  return M__L (##Tocar, 3, uno);
  if (ObjetoEsIntocable (uno)) return;
  if (uno has animado) return M__L (##Tocar, 1, uno);
  M__L (##Tocar, 2, uno);
];

[ GirarSub;
  if (ObjetoEsIntocable (uno)) return;
  if (uno has estatico)   return M__L (##Girar, 1, uno);
  if (uno has escenario)  return M__L (##Girar, 2, uno);
  if (uno has animado)    return M__L (##Girar, 4, uno);
  M__L (##Girar, 3, uno);
];

[ EsperarSub;
  if (RutinasDespues() == 1) rtrue;
  M__L (##Esperar, 1, uno);
];

[ DespertarseSub; M__L (##Despertarse, 1, uno); ];

[ DespertarOtroSub;
  if (ObjetoEsIntocable (uno)) return;
  if (EjecutarVida (uno, ##DespertarOtro) ~= 0) rfalse;
  M__L (##DespertarOtro, 1, uno);
];

[ AgitarSub;
  if (parent(uno) ~= jugador) return M__L (##Agitar, 1, uno);
  M__L (##Agitar, 2, uno); ];

[ GesticularSub; M__L (##Gesticular, 1, uno); ];

[ SiSub; M__L (##Si); ];

! ----------------------------------------------------------------------------
!   Debugging verbs
! ----------------------------------------------------------------------------

#Ifdef DEBUG;

[ ActivarTrazaSub; parser_trace=1; "[Traza activada.]"; ];

[ NivelTrazaSub;
  parser_trace=uno;
  print "[Nivel de traza ", parser_trace, ".]^";
];

[ DesactivarTrazaSub; parser_trace=0; "[Traza desactivada.]"; ];

[ ActivarRutinasSub;  debug_flag=debug_flag | 1;
    "[Listado de mensajes activado.]"; ];

[ DesactivarRutinasSub; debug_flag=debug_flag & 14;
    "[Listado de mensajes desactivado.]"; ];

[ ActivarAccionesSub;  debug_flag=debug_flag | 2;
    "[Listado de acciones activado.]"; ];

[ DesactivarAccionesSub; debug_flag=debug_flag & 13;
    "[Listado de acciones desactivado.]"; ];

[ ActivarRelojesSub;  debug_flag=debug_flag | 4;
    "[Listado de relojes activado.]"; ];

[ DesactivarRelojesSub; debug_flag=debug_flag & 11;
    "[Listado de relojes desactivado.]"; ];

#Ifdef VN_1610;

[ CambiosOnSub;  debug_flag=debug_flag | 8;
    "[Listado de cambios activado.]"; ];

[ CambiosOffSub; debug_flag=debug_flag & 7;
    "[Listado de cambios desactivado.]"; ];

#Ifnot;

[ CambiosOnSub;
    "[El listado de cambios sólo está disponible con Inform 6.2 o superior]";
];

[ CambiosOffSub;
    "[El listado de cambios sólo está disponible con Inform 6.2 o superior]";
];

#Endif; ! VN_1610

#Ifdef TARGET_ZCODE;

[ ActivarComandosSub;
  @output_stream 4; xcommsdir=1; "[Grabación de comandos activada.]"; ];
[ DesactivarComandosSub;
  if (xcommsdir==1) @output_stream -4;
  xcommsdir=0;
  "[Grabación de comandos desactivada.]"; ];
[ LeerComandosSub;
  @input_stream 1; xcommsdir=2; "[Reproduciendo comandos.]"; ];
[ PredecibleSub i; i=random(-100);
  "[El generador de números aleatorios es ahora predecible.]"; ];
#Ifnot; ! TARGET_GLULX;
[ ActivarComandosSub fref;
  if (gg_commandstr ~= 0) {
    if (gg_command_reading)
      "[La reproducción de comandos está activa.]";
    "[La grabación de comandos ya estaba activa.]";
  }
  ! fileref_create_by_prompt
  fref = glk($0062, $103, $01, 0);
  if (fref == 0)
    "[La grabación de comandos ha fracasado.]";
  gg_command_reading = false;
  ! stream_open_file
  gg_commandstr = glk($0042, fref, $01, GG_COMMANDWSTR_ROCK);
  glk($0063, fref); ! fileref_destroy
  if (gg_commandstr == 0)
    "[La grabación de comandos ha fracasado.]";
  "[Grabacion de comandos activada.]";
];
[ DesactivarComandosSub;
  if (gg_commandstr == 0)
    "[La grabación de comandos ya estaba desactivada.]";
  if (gg_command_reading)
    "[La reproducción de comandos está activa.]";
  glk($0044, gg_commandstr, 0); ! stream_close
  gg_commandstr = 0;
  gg_command_reading = false;
  "[Grabación de comandos desactivada.]";
];
[ LeerComandosSub fref;
  if (gg_commandstr ~= 0) {
    if (gg_command_reading)
      "[La reproducción de comandos ya estaba activada.]";
    "[La grabación de comandos está activa.]";
  }
  ! fileref_create_by_prompt
  fref = glk($0062, $103, $02, 0);
  if (fref == 0)
    "[La grabación de comandos ha fracasado.]";
  gg_command_reading = true;
  ! stream_open_file
  gg_commandstr = glk($0042, fref, $02, GG_COMMANDRSTR_ROCK);
  glk($0063, fref); ! fileref_destroy
  if (gg_commandstr == 0)
    "[La grabación de comandos ha fracasado.]";
  "[Grabación de comandos activada.]";
];
[ PredecibleSub;
  @setrandom 100;
  "[El generador de números aleatorios es ahora predecible.]";
];
#Endif; ! TARGET_;

[ XCompruebaMover obj dest;
  if ((obj<=LibreriaInform) || (obj == MensajesLibreria) || (obj in 1))
     "[No puedo mover ", (name) obj, ": es un objeto de librería.]";
  while (dest ~= 0)
  {   if (dest == obj)
          "[No puedo mover ", (name) obj, ": se contendría a sí mismo.]";
      dest = parent(dest);
  }
  rfalse;
];

[ XRobarSub;
  if (XCompruebaMover(uno,jugador)) return;
  move uno to jugador; give uno movido ~oculto;
  "[XRobado.]"; ];

[ XMoverSub;
  if (XCompruebaMover(uno,otro)) return;
  move uno to otro; "[XMovido.]"; ];

[ XObj obj f;
  if (parent(obj) == 0) print (name) obj; else print (un) obj;
  print " (", obj, ") ";
  if (f==1 && parent(obj) ~= 0)
      print "(en ", (name) parent(obj), " ", parent(obj), ")";
  new_line;
  if (child(obj)==0) rtrue;
  if (obj == Class)
      EscribirListaDesde(child(obj),
      NUEVALINEA_BIT + INDENTAR_BIT + SIEMPRE_BIT + SINARTICULO_BIT, 1);
  else
      EscribirListaDesde(child(obj),
      NUEVALINEA_BIT + INDENTAR_BIT + SIEMPRE_BIT + INFOTOTAL_BIT, 1);
];

[ XArbolSub i;
  if (uno==0)
  {   objectloop(i)
      if (i ofclass Object && parent(i)==0) XObj(i);
  }
  else XObj(uno,1);
];

[ XIrASub;
  if (~~(uno ofclass Object) || (parent(uno)~=0)) "[No es un lugar seguro.]";
  JugadorA(uno);
];

[ IrDondeSub x; x=uno; while (parent(x)~=0) x=parent(x); JugadorA(x); ];

[ Print_ScL obj; print_ret ++x_cuenta_ambito, ": ", (un) obj, " (", obj, ")"; ];

[ AlcanceSub; x_cuenta_ambito=0; BucleAlcance(Print_ScL, uno);
  if (x_cuenta_ambito==0) "No hay nada al alcance.";
];

#Ifdef TARGET_GLULX;

[ GlkListSub id val;
  id = glk($0020, 0, gg_arguments); ! window_iterate
  while (id) {
    print "Window ", id, " (", gg_arguments-->0, "): ";
    val = glk($0028, id); ! window_get_type
    switch (val) {
      1: print "par";
      2: print "vacía";
      3: print "buffer de texto";
      4: print "rejilla de texto";
      5: print "gráfica";
      default: print "desconocida";
    }
    val = glk($0029, id); ! window_get_parent
    if (val) print ", el padre es la ventana ", val;
    else print ", sin padre (raíz)";
    val = glk($002C, id); ! window_get_stream
    print ", stream ", val;
    val = glk($002E, id); ! window_get_echo_stream
    if (val) print ", stream de eco ", val;
    print "^";
    id = glk($0020, id, gg_arguments); ! window_iterate
  }
  id = glk($0040, 0, gg_arguments); ! stream_iterate
  while (id) {
    print "Stream ", id, " (", gg_arguments-->0, ")^";
    id = glk($0040, id, gg_arguments); ! stream_iterate
  }
  id = glk($0064, 0, gg_arguments); ! fileref_iterate
  while (id) {
    print "Fileref ", id, " (", gg_arguments-->0, ")^";
    id = glk($0064, id, gg_arguments); ! fileref_iterate
  }
  val = glk($0004, 8, 0); ! gestalt, Sound
  if (val) {
    id = glk($00F0, 0, gg_arguments); ! schannel_iterate
    while (id) {
      print "Soundchannel ", id, " (", gg_arguments-->0, ")^";
      id = glk($00F0, id, gg_arguments); ! schannel_iterate
    }
  }
];
#Endif; ! TARGET_;

#Endif; ! DEBUG

! ----------------------------------------------------------------------------
!   Finally: the mechanism for library text (the text is in the language defn)
! ----------------------------------------------------------------------------

[ M__L act n x1 s;
  s=sw__var; sw__var=act; if (n==0) n=1;
  M___L(n,x1);
  sw__var=s;
];

[ M___L n x1 s;
  s=accion;
  ml_n=n; ml_o=x1;
  accion=sw__var;
  if (EjecutarRutinas(MensajesLibreria,antes)~=0) { accion=s; rfalse; }
  accion=s;

  MLIdioma(n, x1);
];

! ==============================================================================
