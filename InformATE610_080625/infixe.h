! infixe.h
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
! Conversión (c) Zak 2000
!
! PARCHES:
!
!  El operador '.' (evaluar propiedad de objeto) y ',' (en las listas
!  de parámetros a funciones) no eran comprendidos. Se ha modificado
!  para que cuando se detectan estos operadores sean sustituidos por
!  el operador '?' y '!' respectivamente. Estos operadores no existen
!  realmente en inform, pero el resto de infix ha sido modificado para
!  que los evalúe como si fueran '.' y ',', por lo que el usuario no
!  nota nada.
!
!  La rutina InfixMatchPrule ha sido modificada para que entienda
!  correctamente un nombre de atributo o propiedad, cuando este está
!  "aliasado". En el original, un atributo o propiedad con alias nunca
!  era comprendido. En la versión actual es comprendido sólo si se usa
!  el primero de sus alias (así, se entiende "femenino", pero no
!  "femenina" que sería su segundo alias, o entiende "name", pero no
!  "nombre" "imperativo" "irrelevante", etc que son todos ellos alias
!  de "name"). Aún necesitaría más retoques para que pudiera
!  comprender todos los alias.
!
!
! ----------------------------------------------------------------------------
!  INFIX:  Support for the optional library extension "Infix".
!
!  Supplied for use with Inform 6                         Serial number 000629
!                                                                 Release 6/10
!  (c) Graham Nelson 1999
!      but freely usable (see manuals)
! ----------------------------------------------------------------------------
System_file;
#Ifdef DEBUG;

Constant INFIXTT_NUMBER 0;
Constant INFIXTT_ARRAY 1;
Constant INFIXTT_ROUTINE 2;
Constant INFIXTT_CONSTANT 3;
Constant INFIXTT_DWORD 4;
Constant INFIXTT_ACTION 5;
Constant INFIXTT_ATTRIBUTE 6;
Constant INFIXTT_PROPERTY 7;
Constant INFIXTT_GLOBAL 8;
Constant INFIXTT_NAMEDOBJECT 9;
Constant INFIXTT_SYSFUN 10;
Constant INFIXTT_STATICSTRING 11;
Constant INFIXTT_LOGICAL 12;

Global infix_term_type;
Global infix_data1;
Global infix_data2;
Global infix_lvalue;
Global infix_parsed_lvalue;
Array infix_tolowercase -> 256;
Array infix_text -> 128;


[ InfixPrintAttribute x; print (string) #attribute_names_array-->x; ];
[ InfixPrintProperty x; print (property) x; ];
[ InfixPrintGlobal x; print (string) #global_names_array-->x; ];
[ InfixPrintAction x;
  print (string) #action_names_array-->(x-#lowest_action_number);
];
[ InfixPrintRoutine x;
  print (string) #routine_names_array-->(x-#lowest_routine_number);
];
[ InfixPrintConstant x;
  print (string) #constant_names_array-->(x-#lowest_constant_number);
];
[ InfixPrintArray x;
  print (string) #array_names_array-->(x-#lowest_array_number);
];
[ InfixPrintFakeAction x;
  print (string) #fake_action_names_array-->(x-#lowest_fake_action_number);
];
[ InfixPrintPA x n;
  for (n=#lowest_routine_number:n<=#highest_routine_number:n++)
  {   if (x == Symb__Tab(INFIXTT_ROUTINE, n))
      {   print (InfixPrintRoutine) n; return;
      }
  }
  print "Routine(", x, ")";
];

[ InfixMatchPrule PrintingRule range1 range2 wa wl t i i2 it2 itlc j k plus;
  itlc = infix_tolowercase;
  if (itlc->255 == 0)
  {   for (j=0:j<256:j++) itlc->j = j;
      itlc->'A' = 'a';      itlc->'B' = 'b';
      itlc->'C' = 'c';      itlc->'D' = 'd';
      itlc->'E' = 'e';      itlc->'F' = 'f';
      itlc->'G' = 'g';      itlc->'H' = 'h';
      itlc->'I' = 'i';      itlc->'J' = 'j';
      itlc->'K' = 'k';      itlc->'L' = 'l';
      itlc->'M' = 'm';      itlc->'N' = 'n';
      itlc->'O' = 'o';      itlc->'P' = 'p';
      itlc->'Q' = 'q';      itlc->'R' = 'r';
      itlc->'S' = 's';      itlc->'T' = 't';
      itlc->'U' = 'u';      itlc->'V' = 'v';
      itlc->'W' = 'w';      itlc->'X' = 'x';
      itlc->'Y' = 'y';      itlc->'Z' = 'z';
  }
  switch(PrintingRule)
  {   InfixPrintAttribute:
          if (wa->0 == '~') { wl--; wa++; plus = 100; } ! A tilde
          t = #attribute_names_array;
      InfixPrintProperty: t = #property_names_array;
      InfixPrintAction: t = #action_names_array;
      InfixPrintFakeAction: t = #fake_action_names_array;
      InfixPrintGlobal: t = #global_names_array;
      InfixPrintRoutine: t = #routine_names_array;
      InfixPrintAction: t = #constant_names_array;
      InfixPrintArray: t = #array_names_array;
  }

  i2 = range2-range1; it2 = infix_text+2;
  for (i=0: i<=i2: i++)
  {   infix_text-->0 = 62; @output_stream 3 infix_text;
      if (t) print (string) t-->i; else PrintingRule(i+range1);
      @output_stream -3;
      k = infix_text-->0;
      if (printingrule==infixprintattribute or infixprintproperty) {
 	  for (j=2:j<k+2:j++)
	      if (infix_text->j=='/') break;
	  k=j-2;
      }
      if (k ~= wl) jump XL;
      if (itlc->(it2->0) ~= wa->0) jump XL;
      for (j=1:j<k:j++)
          if (itlc->(it2->j) ~= wa->j) jump XL;
      numero_interpretado = i + range1 + plus; rtrue;
      .XL;
  }
  rfalse;
];

[ InfixActionToken;
  if (InfixMatchPrule(InfixPrintAction,
      #lowest_action_number, #highest_action_number,
      DireccionDePalabra(np), LongitudDePalabra(np)))
  {   np++; infix_lvalue = numero_interpretado; return 0;
  }
  if (InfixMatchPrule(InfixPrintFakeAction,
      #lowest_fake_action_number, #highest_fake_action_number,
      DireccionDePalabra(np), LongitudDePalabra(np)))
  {   np++; infix_lvalue = numero_interpretado; return 0;
  }
  return -1;
];

[ InfixRvalueTerm n w i initial_wn wa wl sign base digit dcount;

  initial_wn = np;

  infix_parsed_lvalue = -1;
  infix_term_type = INFIXTT_NUMBER;

  w = SiguientePalabraParar();
  if (w == -1) return -1;

  wa = DireccionDePalabra(np-1);
  wl = LongitudDePalabra(np-1);
  if (wa->0 == '-' or '$' or '0' or '1' or '2' or '3' or '4'
               or '5' or '6' or '7' or '8' or '9')
  {   ! Parse decimal, hex or binary cantidad

      sign = 1; base = 10; dcount = 0;
      if (wa->0 == '-') { sign = -1; wl--; wa++; }
      else
      {   if (wa->0 == '$') { base = 16; wl--; wa++; }
          if (wa->0 == '$') { base = 2; wl--; wa++; }
      }
      if (wl == 0) return -1;
      n = 0;
      while (wl > 0)
      {   if (wa->0 >= 'a') digit = wa->0 - 'a' + 10;
          else digit = wa->0 - '0';
          dcount++;
          switch(base)
          {   2: if (dcount == 17) return -1;
             10: if (dcount == 6) return -1;
                 if (dcount == 5)
                 {   if (n > 3276) return -1;
                     if (n == 3276)
                     {   if (sign == 1 && digit > 7) return -1;
                         if (sign == -1 && digit > 8) return -1;
                     }
                 }
             16: if (dcount == 5) return -1;
          }
          if (digit >= 0 && digit < base) n = base*n + digit;
          else return -1;
          wl--; wa++;
      }
      numero_interpretado = n*sign; return 1;
  }

! Parse character constant 'a'

  if (wl == 3 && wa->0==''' && wa->2==''')
  {   numero_interpretado = wa->1; return 1;
  }

! ##Action, 'dword'

  switch(w)
  {   '##': infix_term_type = INFIXTT_ACTION;
            w = SiguientePalabraParar(); if (w == -1) return -1;
            np--;
            if (InfixActionToken() == 0) return 1;
            return -1;
      '^^': infix_term_type = INFIXTT_DWORD;
            w = SiguientePalabraParar(); if (w == -1) return -1;
            numero_interpretado = w; return 1;
  }

! Test for attribute, property, class nombre, variable nombre, array nombre,
! routine nombre, constant nombre

  np--;
  if ((wa->0 >= 'a' && wa->0 <= 'z')
      || (wa->0 >= 'A' && wa->0 <= 'Z')
      || wa->0 == '_')
  {

  infix_term_type = INFIXTT_ATTRIBUTE;
  if (InfixMatchPrule(InfixPrintAttribute,
      #lowest_attribute_number, #highest_attribute_number, wa, wl))
  {   np++; return 1; }

  infix_term_type = INFIXTT_PROPERTY;
  if (InfixMatchPrule(InfixPrintProperty,
      #lowest_property_number, #highest_property_number, wa, wl))
  {   np++; return 1; }

  infix_term_type = INFIXTT_GLOBAL;
  if (InfixMatchPrule(InfixPrintGlobal,
      #lowest_global_number, #highest_global_number, wa, wl))
  {   infix_parsed_lvalue = numero_interpretado-16;
      numero_interpretado = #globals_array-->infix_parsed_lvalue;
      np++; return 1;
  }

  infix_term_type = INFIXTT_ARRAY;
  if (InfixMatchPrule(InfixPrintArray,
      #lowest_array_number, #highest_array_number, wa, wl))
  {   infix_parsed_lvalue = numero_interpretado;
      numero_interpretado = Symb__Tab(INFIXTT_ARRAY,numero_interpretado);
      infix_data1 = temp__global3;
      infix_data2 = temp__global2;
      np++; return 1;
  }

  infix_term_type = INFIXTT_ROUTINE;
  if (InfixMatchPrule(InfixPrintRoutine,
      #lowest_routine_number, #highest_routine_number, wa, wl))
  {   infix_parsed_lvalue = numero_interpretado;
      numero_interpretado = Symb__Tab(INFIXTT_ROUTINE,numero_interpretado);
      infix_data1 = temp__global3;
      infix_data2 = temp__global2;
      np++; return 1;
  }

  infix_term_type = INFIXTT_CONSTANT;
  if (InfixMatchPrule(InfixPrintConstant,
      #lowest_constant_number, #highest_constant_number, wa, wl))
  {   infix_parsed_lvalue = numero_interpretado;
      numero_interpretado = Symb__Tab(INFIXTT_CONSTANT,numero_interpretado);
      infix_data1 = temp__global3;
      infix_data2 = temp__global2;
      np++; return 1;
  }

  switch(w)
  {   'parent', 'child', 'children',
      'random', 'metaclass', 'sibling': numero_interpretado = w;
          infix_parsed_lvalue = INFIXTT_SYSFUN;
          np++; return 1;
  }
  }

  infix_term_type = INFIXTT_NAMEDOBJECT;

  np = initial_wn; i = InterpretarToken(TT_ALCANCE, InfixBigScope);

  if (i == RPG_REPARSE) return i;
  if (i > RPG_MULTIPLE)
  {   print "(", (name) i, " (", i, "))^";
      numero_interpretado = i; return 1;
  }
  return -1;
];
[ InfixBigScope x;
  if (estadio_alcance == 1) return false;  ! No multiples here
  if (estadio_alcance == 2)
  {   objectloop (x ofclass Object) PonerAlAlcance(x);
      return true; ! That's the whole scope
  }
  print "; No puedo interpretar este término.^";
];

[ InfixCheckLineSpaced wa wl i force altered;
  for (i = 1 : i <= parse->1 : i++)
  {   wa = DireccionDePalabra(i);
      wl = LongitudDePalabra(i);
      if (wl > 3 && wa->0==''' && wa->(wl-1)==''')
      {   wa->(wl-1) = ' ';
          if (wa->(wl-2) == '/' && wa->(wl-3) == '/')
          {   wa->(wl-2) = ' ';
              wa->(wl-3) = ' ';
          }
          LTI_Insert(wa-buffer, ''');
          LTI_Insert(wa-buffer + 2, ' ');
          altered = true; break;
      }
  }
  for (i = 2 : i < buffer->1 + 2: i++)
  {   force = false;
      if (buffer->i=='-' && buffer->(i+1)=='-' && buffer->(i+2)=='>')
          force = true;
      if (force)
      {   if (i>2 && buffer->(i-1)~=' ')
          {   LTI_Insert(i++, ' '); altered = true;
          }
          if (buffer->(i+3)~=' ')
          {   LTI_Insert(i+3, ' '); i++; altered = true;
          }
          i = i + 2; continue;
      }

      if (buffer->i==':' && buffer->(i+1)==':') force = true;
      if (buffer->i=='-' && buffer->(i+1)=='>') force = true;
      if (buffer->i=='.' && buffer->(i+1)=='&')
      {   buffer->i = ']'; force = true;
      }
      if (buffer->i=='.' && buffer->(i+1)=='#')
      {   buffer->i = ']'; force = true;
      }
      if (buffer->i==']' && buffer->(i+1)=='&') force = true;
      if (buffer->i==']' && buffer->(i+1)=='#') force = true;
      if (buffer->i=='+' && buffer->(i+1)=='+') force = true;
      if (buffer->i=='-' && buffer->(i+1)=='-') force = true;
      if (buffer->i=='&' && buffer->(i+1)=='&') force = true;
      if (buffer->i=='|' && buffer->(i+1)=='|') force = true;
      if (buffer->i=='~' && buffer->(i+1)=='~') force = true;

      if (buffer->i=='=' && buffer->(i+1)=='=') force = true;
      if (buffer->i=='~' && buffer->(i+1)=='=') force = true;
      if (buffer->i=='>' && buffer->(i+1)=='=') force = true;
      if (buffer->i=='<' && buffer->(i+1)=='=') force = true;
      if (buffer->i=='#' && buffer->(i+1)=='#') force = true;

      if (force)
      {   if (i>2 && buffer->(i-1)~=' ')
          {   LTI_Insert(i++, ' '); altered = true;
          }
          if (buffer->(i+2)~=' ')
          {   LTI_Insert(i+2, ' '); i++; altered = true;
          }
          i = i + 1; continue;
      }

      if (buffer->i=='+') force = true;
      if (buffer->i=='-') force = true;
      if (buffer->i=='*') force = true;
      if (buffer->i=='/') force = true;
      if (buffer->i=='%') force = true;
      if (buffer->i=='(') force = true;
      if (buffer->i==')') force = true;
      if (buffer->i=='<' && buffer->(i-1)~=';') force = true;
      if (buffer->i=='>') force = true;
      if (buffer->i==',') { buffer->i='!'; force = true;}
      if (buffer->i=='.') { buffer->i='?'; force = true;}
      if (buffer->i=='&') force = true;
      if (buffer->i=='|') force = true;
      if (buffer->i=='~') force = true;
      if (buffer->i=='=') force = true;
      if (force)
      {   if (i>2 && buffer->(i-1)~=' ')
          {   LTI_Insert(i++, ' '); altered = true;
          }
          if (buffer->(i+1)~=' ')
          {   LTI_Insert(i+1, ' '); i++; altered = true;
          }
      }
  }
!  print "|";
  for (i = 2 : i < buffer->1 + 2: i++)
!    print (char) buffer->i;
      if (buffer->i == '~') { buffer->i = '['; altered = true; }
!      print "|";
  return altered;
];

Array InfixRV_rvals --> 32;
Array InfixRV_lvals --> 32;
Array InfixRV_op --> 32;
Array InfixRV_lop --> 32;
Array InfixRV_rop --> 32;
Array InfixRV_types --> 32;
Array InfixRV_commas --> 32;

[ InfixRvalue acc w i n flag base expecting_term max maxi lop rop lvalside
              a b sysfun_f;

  if (InfixCheckLineSpaced()) return RPG_REPARSE;

!  w = np; for (i=0: i<10: i++) { np = w; InfixRvalueTerm(); print i, "^"; }
!  np = w;

  expecting_term = true; base = 0;
  do
  {   w = SiguientePalabraParar();
      if (expecting_term)
      {   switch(w)
          {   '-//':
                  InfixRV_rvals-->n = 'unary-'; InfixRV_types-->n = base + 8;
              '[//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 6;
              '[[':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 2;
              '++':
                  InfixRV_rvals-->n = 'pre++'; InfixRV_types-->n = base + 9;
              '--':
                  InfixRV_rvals-->n = 'pre--'; InfixRV_types-->n = base + 9;
              '(//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = -3; base=base+100;
              ')//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = -3; base=base-100;
                  if (base < 0) { np--; flag = true; }
              -1: flag = true;
              default:
                  np--;
                  if (InfixRValueTerm() == 1)
                  {   InfixRV_rvals-->n = numero_interpretado;
                      InfixRV_lvals-->n = infix_parsed_lvalue;
                      InfixRV_types-->n = -1;
                      expecting_term = false;
                  }
                  else flag = true;
          }
      }
      else
      {   expecting_term = true;
          switch(w)
          {   '!//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base;
              '=//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 1;
              '&&', '||':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 2;
              '==', '[=', '>//', '>=', '<//', '<=', 'has', 'hasnt',
              'in', 'notin', 'ofclass', 'provides':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 3;
              'or':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 4;
              '+//', '-//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 5;
              '*//', '@{2f}//', '%//', '&//', '|//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 6;
              '->', '-->':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 7;
              ']&', ']#':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 10;
              '?//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 12;
              '::':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = base + 13;
              '(//':
                  InfixRV_rvals-->n = '(rcall';
                  InfixRV_types-->n = base + 11; base = base + 100;
              ')//':
                  InfixRV_rvals-->n = w; InfixRV_types-->n = -3;
                  base = base - 100;
                  if (base < 0) { np--; flag = true; }
                  expecting_term = false;
              '++':
                  InfixRV_rvals-->n = 'post++'; InfixRV_types-->n = base + 9;
                  expecting_term = false;
              '--':
                  InfixRV_rvals-->n = 'post--'; InfixRV_types-->n = base + 9;
                  expecting_term = false;
              default:
                  flag = true;
          }
      }
      n++;
  } until (flag || n==32);
  if (base > 0) return -1;
  n--; if (n == 0) return -1;
  np--;

  for (i=0: i<n: i++)
  {   acc = 0; if (InfixRV_types-->i ~= -3) acc = InfixRV_rvals-->i;
      InfixRV_op-->i = acc;
  }

  for (::)
  {
!      for (i=0: i<n: i++)
!      {   if (InfixRV_types-->i == -1) print InfixRV_rvals-->i, " ";
!          else if (InfixRV_types-->i == -3) print " # ";
!          else if (InfixRV_types-->i == -2) print " ## ";
!          else print (address) InfixRV_rvals-->i, "_", InfixRV_types-->i, " ";
!      }
!      new_line;

      max = -2;
      for (i=0:i<n:i++) if (InfixRV_types-->i > max)
                        { max = InfixRV_types-->i; maxi = i; }
      if (max == -1) { numero_interpretado = InfixRV_rvals-->maxi; return 1; }

      lop = maxi-1; rop = maxi+1;
      while (lop>=0 && InfixRV_types-->lop < -1) lop--;
      while (rop<n && InfixRV_types-->rop < -1) rop++;
      if (lop>=0) InfixRV_lop-->maxi = InfixRV_rvals-->lop;
      if (rop<n) InfixRV_rop-->maxi = InfixRV_rvals-->rop;
      flag = false;
    infix_term_type = INFIXTT_NUMBER;
    switch(InfixRV_rvals-->maxi)
    { '!//':     acc = (InfixRV_rvals-->rop);
      '=//', 'pre++', 'post++', 'pre--', 'post--':
                 lvalside = lop;
                 switch(InfixRV_rvals-->maxi)
                 {   '=//': acc = (InfixRV_rvals-->rop);
                     'pre++': acc = (InfixRV_rvals-->rop) + 1; lvalside = rop;
                     'pre--': acc = (InfixRV_rvals-->rop) - 1; lvalside = rop;
                     'post++': acc = (InfixRV_rvals-->lop) + 1;
                     'post--': acc = (InfixRV_rvals-->lop) - 1;
                 }
                 switch (InfixRV_op-->lvalside)
                 {   '?//':
                       (InfixRV_lop-->lvalside).(InfixRV_rop-->lvalside) = acc;
                     '->':
                       (InfixRV_lop-->lvalside)->(InfixRV_rop-->lvalside) = acc;
                     '-->':
                       (InfixRV_lop-->lvalside)-->(InfixRV_rop-->lvalside) =
 acc;
                     default:
                         w = InfixRV_lvals-->lvalside; if (w == -1) return -1;
                         @storew #globals_array w acc;
                 }
                 switch(InfixRV_rvals-->maxi)
                 {   'post++': acc--;
                     'post--': acc++;
                 }
      '(rcall':  sysfun_f = false;
                 switch (InfixRV_op-->lop)
                 {   '?//': a = InfixRV_lop-->lop; b = InfixRV_rop-->lop;
                     default:
                         a = InfixRV_rvals-->lop; b = call;
                         if (InfixRV_lvals-->lop == INFIXTT_SYSFUN)
                             sysfun_f = true;
                 }
                 w = 0;
                 i = maxi + 1; base = 100;
                 if (InfixRV_types-->i == -1 && InfixRV_rvals-->i == ')//')
                 {   if (sysfun_f) return -1;
                     acc = a.b();
                 }
                 else
                 {   while (base > 0)
                     {   if (InfixRV_types-->i == -3 && InfixRV_rvals-->i ==
 ')//')
                             base = base - 100;
                         if (InfixRV_types-->i == -3 && InfixRV_rvals-->i ==
 '(//')
                             base = base + 100;
                         if (InfixRV_op-->i=='(rcall') base = base + 100;
                         if (base == 100 && InfixRV_op-->i == '!//')
                         {   InfixRV_commas-->(w++) = i;
!                             print "Comma found at ", i, "^";
                         }
                         i++;
                     }
!                     print "Num args = ", w + 1, "^";
!                     for (i = 0 : i < w : i++)
!                       print "arg: ", InfixRV_lop-->(InfixRV_commas-->i), "^";
!                     print "arg: ", InfixRV_rvals-->rop, "^";
                     switch(w+1)
                     {   1: if (sysfun_f)
                            {   b = InfixRV_rvals-->rop;
                                infix_term_type = INFIXTT_NAMEDOBJECT;
                                switch(a)
                                {   'metaclass': acc = metaclass(b);
                                    'parent': acc = parent(b);
                                    'child': acc = child(b);
                                    'children': acc = children(b);
                                         infix_term_type = INFIXTT_NUMBER;
                                    'random': acc = random(b);
                                         infix_term_type = INFIXTT_NUMBER;
                                    'sibling': acc = sibling(b);
                                }
                            }
                            else
                                acc = a.b(InfixRV_rvals-->rop);
                         2: if (sysfun_f) return -1;
                            acc = a.b(InfixRV_lop-->(InfixRV_commas-->0),
                                      InfixRV_rvals-->rop);
                         3: if (sysfun_f) return -1;
                            acc = a.b(InfixRV_lop-->(InfixRV_commas-->0),
                                      InfixRV_lop-->(InfixRV_commas-->1),
                                      InfixRV_rvals-->rop);
                         4: if (sysfun_f) return -1;
                            acc = a.b(InfixRV_lop-->(InfixRV_commas-->0),
                                      InfixRV_lop-->(InfixRV_commas-->1),
                                      InfixRV_lop-->(InfixRV_commas-->2),
                                      InfixRV_rvals-->rop);
                         5: if (sysfun_f) return -1;
                            acc = a.b(InfixRV_lop-->(InfixRV_commas-->0),
                                      InfixRV_lop-->(InfixRV_commas-->1),
                                      InfixRV_lop-->(InfixRV_commas-->2),
                                      InfixRV_lop-->(InfixRV_commas-->3),
                                      InfixRV_rvals-->rop);
                         default: return -1;
                     }
                 }
      '+//':     acc = (InfixRV_rvals-->lop) + (InfixRV_rvals-->rop);
      '-//':     acc = (InfixRV_rvals-->lop) - (InfixRV_rvals-->rop);
      '*//':     acc = (InfixRV_rvals-->lop) * (InfixRV_rvals-->rop);
      '@{2f}//': acc = (InfixRV_rvals-->lop) / (InfixRV_rvals-->rop);
      '%//':     acc = (InfixRV_rvals-->lop) % (InfixRV_rvals-->rop);
      '?//':     acc = (InfixRV_rvals-->lop) . (InfixRV_rvals-->rop);
      '->':      acc = (InfixRV_rvals-->lop) -> (InfixRV_rvals-->rop);
      '-->':     acc = (InfixRV_rvals-->lop) --> (InfixRV_rvals-->rop);
      ']&':      acc = (InfixRV_rvals-->lop) .& (InfixRV_rvals-->rop);
      ']#':      acc = (InfixRV_rvals-->lop) .# (InfixRV_rvals-->rop);
      '::':      acc = (InfixRV_rvals-->lop) :: (InfixRV_rvals-->rop);
      '&//':     acc = (InfixRV_rvals-->lop) & (InfixRV_rvals-->rop);
      '|//':     acc = (InfixRV_rvals-->lop) | (InfixRV_rvals-->rop);
      '&&':      acc = (InfixRV_rvals-->lop) && (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '||':      acc = (InfixRV_rvals-->lop) || (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '<//':     acc = (InfixRV_rvals-->lop) < (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '<=':      acc = (InfixRV_rvals-->lop) <= (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '>//':     acc = (InfixRV_rvals-->lop) > (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '>=':      acc = (InfixRV_rvals-->lop) >= (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '==':      acc = (InfixRV_rvals-->lop) == (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '[=':  acc = (InfixRV_rvals-->lop) ~= (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      'has':     acc = (InfixRV_rvals-->lop) has (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      'hasnt':   acc = (InfixRV_rvals-->lop) hasnt (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      'in':      acc = (InfixRV_rvals-->lop) in (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      'notin':   acc = (InfixRV_rvals-->lop) notin (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      'provides': acc = (InfixRV_rvals-->lop) provides (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      'ofclass': acc = (InfixRV_rvals-->lop) ofclass (InfixRV_rvals-->rop);
                 infix_term_type = INFIXTT_LOGICAL;
      '[[':      acc = ~~ (InfixRV_rvals-->rop); flag = true;
      '[//':     acc = ~ (InfixRV_rvals-->rop); flag = true;
      'unary-':  acc = - (InfixRV_rvals-->rop); flag = true;
    }
      InfixRV_rvals-->maxi = acc;
      InfixRV_types-->maxi = -1;
      if (rop < n) InfixRV_types-->rop = -2;
      if (flag==false && lop >= 0) InfixRV_types-->lop = -2;
  }
];

! ------------------------------------------------------------------------

[ InfixWelcomeSub;
    print "; Bienvenido al depurador ~Infix~ (1/990428) que te permite
	usar los siguientes verbos de depuración:^^
	~; <expresion>~: evalúa esa expresión, que puede ser cualquier
	expresión válida de Inform. Por ejemplo, ~;localizacion~
	imprimirá el valor de la variable ~localizacion~, ~; 3*5+1~
	imprimirá 16, ~; children(caja de madera)~ te dirá cuántos
	elementos contiene. (Puedes referirte a los objetos tanto por
	su nombre dentro del código fuente, como ~obj_n~, o
	escribiendo el nombre bajo el que normalmente los reconocería el parser,
	como ~lado norte~: el efecto es el mismo.)^
	Se permite cualquier expresión, excepto las que contengan
	cadenas de texto (comillas dobles). Pero puedes enviar
	mensajes a los objetos, llamar a rutinas o asignar valores a
	las variables, propiedades y elementos de los arrays.
	^   ~; puntuacion++~ es una forma de progresar en el mundo.
	^   ~; banderafin = true~ es una forma de salirse de él.
	^   ~; PararDaemon(enanito odioso)~ evitará que el enano te
	moleste.^
	También se permiten condiciones, como ~; puntuacion>20~, en
	cuyo caso el resultado es 1 (si true) o 0 (si false).^^";
    print "~;examina <algo>~ o ~;x <algo>~ o ~;ex <algo>~ te da todo
	tipo de detalles sobre ese algo. Por ejemplo, ~;x ##Coger~
	describe la acción Coger, ~;x Class~ la clase Class, ~;x
	'deja'~ la palabra de diccionario ~deja~ y lo mismo para
	números, rutinas, arrays y por supuesto objetos. El comando
	~;xo~ examina algo como un objeto, así por ejemplo ~;x
	localizacion~ te da detalles sobre la variable ~localizacion~,
	mientras que ~;xo localizacion~ te los da sobre el objeto a
	que se refiere.^^";
    print "~;give~, ~;remove~ and ~;move~ funcionan igual que los
	comandos Inform del mismo nombre.^^";
    print "~;<~ causa una acción,  por ejemplo ~;< Comer queso~.^^";
    print "~;watch~ o ~;w~ o ~;observa~ o ~;o~ activa un ~watch~
	para actividades varias. Pon simplemente ~;w~ para más
	información.^^";
    print "~;inventario~ o ~;i~ muestra los objetos, variables,
	etc. del juego.^";
];
[ InfixEvalSub;
  InfixExamineP(true);
];
[ InfixActionSub;
  print "; <", (InfixPrintAction) infix_lvalue;
  if (uno) print " (", (the) uno, ")";
  if (otro) print " (", (the) otro, ")";
  print ">^";
  if (otro) <<(infix_lvalue) uno otro>>;
  if (uno) <<(infix_lvalue) uno>>;
  <<(infix_lvalue)>>;
];
[ InfixGiveSub f;
  print "; give (", (the) uno, ") ";
  if (otro<0) { otro = ~otro; f=true; }
  if (otro < 0 || otro>=48) "<Atributo inexistente>";
  if (f) print "@@126";
  print (DepurarAtributo) otro;
  if (f) @clear_attr uno otro;
  else @set_attr uno otro;
];
[ InfixMoveSub;
  print "; move (", (the) uno, ") to (", (the) otro, ")";
  move uno to otro;
];
[ InfixRemoveSub;
  print "; remove (", (the) uno, ")";
  remove uno;
];
[ InfixHex x y;
      y = (x & $7f00) / $100;
      if (x<0) y=y+$80;
      x = x & $ff;
      print (Infixhexdigit) y/$10, (Infixhexdigit) y,
            (Infixhexdigit) x/$10, (Infixhexdigit) x;
];
[ Infixhexdigit x;
  x = x % $10; if (x<10) print x; else print (char) 'a'+x-10;
];
[ InfixExamineOSub;
  infix_data1 = metaclass(uno);
  infix_term_type = INFIXTT_CONSTANT;
  InfixExamineP(false);
];
[ InfixExamineSSub;
  infix_term_type = INFIXTT_STATICSTRING;
  InfixExamineP(false);
];
[ InfixExamineSub;
  InfixExamineP(false);
];
[ InfixExamineP brief x a b w flag lines;
  switch(infix_term_type)
  {   INFIXTT_NUMBER:
          if (brief) "; == ", uno;
          print "; El número ", uno, " == $", (InfixHex) uno;
          if (uno >= 32 && uno < 127) print " == '", (char) uno, "'";
          new_line;
      INFIXTT_NAMEDOBJECT:
          print "~", (name) uno, "~ (", uno, ")^"; if (brief) return;
          <<MostrarObjeto uno>>;
      INFIXTT_CONSTANT:
          if (brief) "; == ", uno;
          switch(infix_data1 & 15)
          {   nothing:
                  print "; Constante ", (InfixPrintConstant) infix_parsed_lvalue,
                  " == ", uno, "^";
              Object: <<MostrarObjeto uno>>;
              Class: print "Clase ", (name) uno, "^";
                  objectloop (a ofclass uno)
                  {   if (flag) print ", "; else print "Contiene: ";
                      print (name) a, " (", a, ")"; flag=true;
                  }
                  if (flag==false) "No hay objetos derivados de esta clase";
          }
          new_line;
      INFIXTT_ATTRIBUTE:
          if (brief) "; == ", uno;
          if (uno>=48 || uno<0) "; Atributo inexistente";
          print "; Atributo ", (InfixPrintAttribute) uno,
              " (con el número ", uno, ")^";
          objectloop (x has uno)
          {   if (flag) print ", ";
              else print "Tienen el atributo ~", (InfixPrintAttribute) uno, "~: ";
              print (name) x, " (", x, ")"; flag = true;
          }
          if (flag == false) "Ningún objeto tiene el atributo ~", (InfixPrintAttribute) uno, "~";
          new_line;
      INFIXTT_PROPERTY:
          if (brief) "; == ", uno;
          print "; Propiedad ", (property) uno, " (con el número ", uno, ")^";
          objectloop (x provides uno)
          {   if (flag) print ", "; else print "Los siguientes objetos usan
		  (~provide~) esta propiedad: ";
              print (name) x, " (", x, ")"; flag = true;
          }
          if (flag == false) "Que no es ~provided~ por ningún objeto";
          new_line;
      INFIXTT_DWORD:
          if (brief) "; == ", uno;
          if (uno == 0) "; Esta palabra no está en el diccionario del juego";
          a = uno->#dict_par1;
          print "; Palabra de Diccionario '", (address) uno;
          if (a & 4) print "//p";
          print "' (address ", uno, ")";
          if (a)
          {   print ": ";
              if (a & 2) print "meta ";
              if (a & 1) print "verbo   ";
              if (a & 8) print "preposicion   ";
              if (a & 128) print "nombre ";
              if (a & 4) print "plural ";
          }
          new_line;
          if (a & 1) <<MostrarVerbo uno>>;
      INFIXTT_ROUTINE:
          if (brief) "; == ", uno;
          print "; Rutina ", (InfixPrintRoutine) infix_parsed_lvalue,
              " (número ", infix_parsed_lvalue, ",
              dirección empaquetada ", uno, ")^";
      INFIXTT_GLOBAL:
          if (brief) "; == ", uno;
          print "; Variable Global ", (InfixPrintGlobal) infix_parsed_lvalue,
              " == ", uno, "^";
      INFIXTT_ARRAY:
          if (brief) "; == ", uno;
          print "; Array ", (InfixPrintArray) infix_parsed_lvalue, " ";
          infix_data1 = infix_data1 % 16;
          switch(infix_data1)
          {   0: print "->"; a=0;
              1: print "-->"; a=0;
              2: print "string"; a=1;
              3: print "table"; a=1;
          }
          print " ", infix_data2, "^; == "; b=infix_data2; if (x) b++;
          for (w=b-1:w>=a:w--)
              if (infix_data1 == 0 or 2) { if (uno->w) break; }
              else { if (uno-->w) break; }
          if (b-1-w <= 5) w=b-1;
          for (:x<=w:x++)
              if (infix_data1 == 0 or 2) print uno->x, " ";
              else print uno-->x, " ";
          if (w<a) print "(", b-a, " elementos a cero)";
          else if (w<b-1) print "(y siguen ", b-1-w, " elementos a cero)";
          new_line;
      INFIXTT_ACTION:
          if (brief) "; == ", uno;
          if (uno >= #lowest_fake_action_number
              && uno <= #highest_fake_action_number)
             "; Acción falsa ", (InfixPrintFakeAction) uno,
              " (con el número ", uno, ")^No es generada por ninguna
		 línea de gramática";
          print "; Acción ", (InfixPrintAction) uno,
              " (con el número ", uno, ")^";
          w = 0-->4;
          for (b=0:b<(0-->4 + 5)-->0:b++)
          {   w = 0-->4 + 7 + b*9;
              if ((w->#dict_par1) & 1)
              {   a = (0-->7)-->($ff-(w->#dict_par2));
                  lines = a->0; a++;
                  for (:lines > 0:lines--)
                  {   a = DesempaquetarLineaGramatica(a);
                      if (accion_que_seria == uno)
                      {   print "'", (address) w, "' "; DepurarLineaGramatica();
                          new_line;
                          flag = true;
                      }
                  }
              }
          }
          if (flag == 0) "No es generada por ninguna línea de gramática";
      INFIXTT_SYSFUN:
          if (brief) "; == ", uno;
         "; Función de librería ~", (address) infix_parsed_lvalue, "~
	  no ha sido reescrita, y mantiene su definición estándar.";
      INFIXTT_STATICSTRING:
          if (brief) "; == ", uno;
          if (metaclass(uno) ~= String) "; ", uno, " no es una cadena.";
          print "~", (string) uno, "~^";
      INFIXTT_LOGICAL:
          if (uno==true) "; true"; if (uno==false) "; false";
          "; ", uno;
  }
];
[ InfixDescribeWatchSub x y z s flag aflag;
    print "; El verbo ~;watch~ o ~;observa~ te permite activar un
	~observador~ para cualquier rutina u objeto: por ejemplo
	~;watch PuntuacionSub~ o ~;watch espada de plata~. El
	observador imprimirá información cada vez que la rutina o el
	objeto sean accedidos. También puedes usar los comandos:
	^   ~;watch objetos~: observa todos los cambios en propiedades
	o atributos de cualquier objeto";
    if (debug_flag & 8) print " (on)"; else print " (off)";

    print ";^   ~;watch relojes~: observa los daemons y relojes
	activos en cada turno";
    if (debug_flag & 4) print " (on)"; else print " (off)";

    print ";^    ~;watch mensajes~: observa los mensajes enviados a
	cualquier objeto";
    if (debug_flag & 1) print " (on)"; else print " (off)";

    print ";^   ~;watch acciones~: observa la activación de cualquier acción";
    if (debug_flag & 2) print " (on)"; else print " (off)";

    print ".^~;watch~ puede abreviarse como ~;w~ o ~;o~ y puedes usar
	~off~ para dejar de observar algo: por ejemplo ~;w localizacion off~.^";
    aflag = debug_flag;
    objectloop (x has infix__watching) flag = true; aflag = aflag || flag;
    if (flag) print "Están siendo observados los siguientes objetos: ";
    flag = false;
    objectloop (x has infix__watching)
    {   if (flag) print ", "; flag = true;
      	print (name) x, " (", x, ")";
    }
    if (flag) new_line;
    s = (#highest_routine_number - #lowest_routine_number);
    if (s%8 == 0) s=s/8; else s=s/8+1;
    for (flag=false, x=0:x<s:x++) if (#routine_flags_array->x) flag = true;
    aflag = aflag || flag;
    if (flag) print "Están siendo observadas las siguientes rutinas: ";
    for (x=0, flag=false:x<s:x++)
    {   for (y=1,z=0:y<256:z++,y=y*2)
    {   if ((#routine_flags_array->x) & y)
    {   if (flag) print ", "; flag = true;
	print (InfixPrintRoutine)
	    #lowest_routine_number + x*8 + z;
    }
    }
    }
    if (flag) new_line;
    if (aflag == false) "En estos momentos nada está siendo observado.";
];
[ InfixWatchOnSub i j k l;
    if (uno == 0) return InfixDescribeWatchSub();
    if (infix_term_type == INFIXTT_ROUTINE)
    {   i = infix_parsed_lvalue/8;
      	for (j=0,k=1:j<infix_parsed_lvalue%8:j++) k=k*2;
      	l = #routine_flags_array->i;
      	l = l | k;
      	@storeb #routine_flags_array i l;
     	"; Observando la rutina ", (InfixPrintRoutine) infix_parsed_lvalue, ".";
    }
    if (metaclass(uno) == Object)
    {   give uno infix__watching;
     	"; Observando el objeto ~", (name) uno, "~ (", uno, ").";
    }
    InfixDescribeWatchSub();
];
[ InfixWatchOffSub i j k l;
  if (uno == 0) return InfixDescribeWatchSub();
  if (infix_term_type == INFIXTT_ROUTINE)
  {   i = infix_parsed_lvalue/8;
      for (j=0,k=1:j<infix_parsed_lvalue%8:j++) k=k*2;
      l = #routine_flags_array->i;
      l = l & (~k);
      @storeb #routine_flags_array i l;
     "; No se está observando ", (InfixPrintRoutine) infix_parsed_lvalue, ".";
  }
  if (metaclass(uno) == Object)
  {   @clear_attr uno infix__watching;
     "; No se está observando el objeto ~", (name) uno, "~ (", uno, ").";
  }
  InfixDescribeWatchSub();
];
[ InfixList from to tab filter i flag;
    print "^    ";
    for (i=from:i<=to:i++)
      	if (tab-->(i-from))
      	{   flag = true;
            if (tab == #array_names_array)
            {   Symb__Tab(INFIXTT_ARRAY, i);
              	flag = ~~(temp__global3 & 16);
            }
            if (tab == #routine_names_array)
            {   Symb__Tab(INFIXTT_ROUTINE,i);
              	flag = ~~(temp__global3 & 16);
            }
            if (tab == #constant_names_array)
            {   Symb__Tab(INFIXTT_CONSTANT,i);
              	flag = (~~(temp__global3 & 16)) && (temp__global3 % 16 == filter);
            }
            if (flag) print (string) tab-->(i-from), " ";
      	}
    new_line;
];
[ InfixInvSub i;

    print (string) Historia, (string) Titular;
    print "  ", (number) #highest_object_number - #lowest_object_number + 1,
      	" objetos;^";
    print "  objetos no de librería:";
    InfixList(#lowest_constant_number, #highest_constant_number,
      	      #constant_names_array, 2);
    print "  ", (number) #highest_class_number - #lowest_class_number + 1,
      	"  clases:^    ";
    for (i=#lowest_class_number:i<=#highest_class_number:i++)
      	print (name) #class_objects_array-->i, " ";
    new_line;
    print "  arrays no de librería:";
    InfixList(#lowest_array_number, #highest_array_number,
      	      #array_names_array);
    print "  rutinas no de librería:";
    InfixList(#lowest_routine_number, #highest_routine_number,
      	      #routine_names_array);
    print "  constantes no de librería:";
    InfixList(#lowest_constant_number, #highest_constant_number,
      	      #constant_names_array, 0);
    print "  propiedades (comunes):";
    InfixList(#lowest_property_number, 63, #property_names_array);
    print "  propiedades (individuales):";
    InfixList(64, #highest_property_number, #property_names_array + 126);
    print "  atributos:";
    InfixList(#lowest_attribute_number, #highest_attribute_number,
      	      #attribute_names_array);
    if (true) return;
    print "  variables globales:";
    InfixList(#lowest_global_number, #highest_global_number,
      	      #global_names_array);
    print "  acciones:";
    InfixList(#lowest_action_number, #highest_action_number,
      	      #action_names_array);
    print "  acciones falsas:";
    InfixList(#lowest_fake_action_number, #highest_fake_action_number,
      	      #fake_action_names_array);
];

Verb meta ";i" ";inv" ";inventario"
     * -> InfixInv;
Verb meta ";x" ";examina" ";ex"
     * InfixRvalue -> InfixExamine;
Verb meta ";xo" ";examinao" ";exo"
     * InfixRvalue -> InfixExamineO;
Verb meta ";xs" ";examinas" ";exs"
     * InfixRvalue -> InfixExamineS;
Verb meta ";<"
     * InfixActionToken -> InfixAction
     * InfixActionToken InfixRvalue -> InfixAction
     * InfixActionToken InfixRvalue InfixRvalue -> InfixAction;
Verb meta ";"
     * -> InfixWelcome
     * InfixRvalue -> InfixEval;
Verb meta ";give"
     * InfixRvalue InfixRvalue -> InfixGive;
Verb meta ";move"
     * InfixRvalue "to" InfixRvalue -> InfixMove;
Verb meta ";remove"
     * InfixRvalue -> InfixRemove;
Verb meta ";watch" ";w" ";observa" ";o"
    * 					-> InfixWatchOn
    * "relojes"/"daemons"/"timers" 	-> ActivarRelojes
    * "relojes"/"daemons"/"timers" "off" -> DesactivarRelojes
    * "actions"/"acciones"		-> ActivarAcciones
    * "actions"/"acciones" "off"	-> DesactivarAcciones
    * "messages"/"mensajes"		-> ActivarRutinas
    * "messages"/"mensajes" "off"	-> DesactivarRutinas
    * "objects"/"objetos"		-> CambiosOn
    * "objects"/"objetos" "off"		-> CambiosOff
    * InfixRvalueTerm 			-> InfixWatchOn
    * InfixRvalueTerm "off" 		-> InfixWatchOff;

#Endif; ! DEBUG

! ------------------------------------------------------------------------
