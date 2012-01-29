!===============================================================================
!  DREAMBYTES ADVENTURES: (IN)ICIALIZACION (UN)IFICADA DE (E)XTENSIONES EN GL(K)
!  Codigo Fuente
!===============================================================================
!
!  Archivo :  dainunek.h
!  Fecha   :  2009/01/03
!  Version :  3
!  Autor   :  Eliuk Blau
!  e-Mail  :  eliukblau (AT) gmail.com
!
!  Descripcion: Extension usada por DreamBytes Adventures para la programacion
!               de juegos de Ficcion Interactiva en Inform6, que proporciona
!               un objeto capaz de implementar y gestionar automaticamente
!               los siguientes Puntos de Entrada para Glk que proporciona
!               la libreria Inform: IdentifyGlkObject() y HandleGlkEvent().
!
!               Dainunek implementa un Objeto-Gestor dentro del cual las
!               distintas extensiones pueden colocar un objeto-hijo que
!               tenga codificado como una propiedad el codigo necesario
!               para cada uno de los Puntos de Entrada Glk soportados.
!
!               Dainunek implementa por si misma los dos Puntos de Entrada
!               mencionados al principio y mediante un 'objectloop' en los
!               objetos-hijos (que cada extension proveera segun lo requiera)
!               colocados dentro Objeto-Gestor de Dainunek ejecutara el codigo
!               para cada Punto de Entrada que estos objetos-hijos implementen.
!               Asi se produce un efecto en cadena: como resultado, el codigo
!               implementado en cada extension sera ejecutado por unas unicas
!               grandes rutinas de Punto de Entrada que ejecutaran el codigo
!               colectado de cada uno de los objetos-hijos dentro del
!               Objeto-Gestor de Dainunek.
!
!               De momento, Dainunek solo gestiona los Puntos de Entrada
!               IdentifyGlkObject() y HandleGlkEvent(); si se agregan a la
!               libreria Inform nuevos Puntos de Entrada Glk en el futuro, es
!               posible que Dainunek tambien los incluya dentro de su gestion.
!               Pero solo se incluiran si el propio funcionamiento de estos
!               puntos de entrada lo permite: por ejemplo, si son rutinas
!               simples con codigos que pueden ejecutarse en cualquier orden
!               y eso no afecta su comportamiento [este es uno de los motivos
!               por los que no se ha incluido la gestion del Punto de Entrada
!               InitGlkWindow(), ya que este puede retornar diferentes
!               valores que afectaran el comportamiento global de la rutina,
!               y ejecutar un cadena de rutinas para este punto de entrada
!               podria provocar comportamientos no deseados. Corregir esto
!               involucraria programar un monton de codigo que, en buenos
!               terminos, seria excesivo y exagerado. Lo mas simple es que el
!               propio programador implemente InitGlkWindow() y coloque los
!               diferentes codigos en el orden que prefiera. HandleGlkEvent(),
!               que si se gestiona por Dainunek, esta casi en limite: puede
!               retornar algunos valores que modifican el comportamiento del
!               codigo, pero que no son demasiado usados.
!
!               Dainunek esta programada exclusivamente para los fines
!               propios de las extensiones de DreamBytes Adventures en cuanto
!               a su inicializacion en Glk. Sin embargo, si algun programador
!               quiere crear una extension propia que sea compatible con las
!               Extensiones DA en cuanto a Glk, deberia usar Dainunek como
!               gestor de las inicializaciones de los puntos de entrada
!               que su extension utilice para funcionar correctamente.
!
!               Dainunek requiere para funcionar correctamente:
!                 - Compilador Inform v6.30 o superior
!                 - Libreria Inform 6/11
!
!               Si modificas la extension Dainunek, estare muy agradecido si
!               me mandas el codigo fuente por e-Mail.
!
!               If you modify the Dainunek extension, I would be grateful if
!               you send me the source code by e-Mail.
!
!               Copyright (c) 2008 Nicolas Merino Quezada (aka Eliuk Blau).
!
!               This program is free software: you can redistribute it and/or
!               modify it under the terms of the GNU Lesser General Public
!               License as published by the Free Software Foundation, either
!               version 3 of the License.
!
!               This program is distributed in the hope that it will be useful,
!               but WITHOUT ANY WARRANTY; without even the implied warranty of
!               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
!               GNU Lesser General Public License for more details.
!
!               You should have received a copy of the GNU Lesser General
!               Public License along with this program. If not, see
!               <http://www.gnu.org/licenses/>.
!
!===============================================================================
!
!  Log:
!  2009/01/03  Eliuk Blau - IMPORTANTE!! Nuevo Release: ** Dainunek v3 **
!                         - Se realizan muchas mejoras en el codigo, entre las
!                           que se destacan eliminacion de la clase 'Dainunek'
!                           reemplazandola por el Objeto-Gestor 'Dainunek' con
!                           el fin de evitar un 'objectloop' para todos los
!                           objetos del juego (en juegos con muchos objetos
!                           esto podia potencialmente ocasionar una lentitud).
!                           Ahora cada objeto que quiera implementar un Punto
!                           de Entrada Glk debe ser hijo del Objecto-Gestor,
!                           entonces el 'objectloop' se vuelve mas rapido
!                           ya que solo recorre los hijos del Objeto-Gestor.
!  2008/03/29  Eliuk Blau - CAPRICHOS!! Se reemplaza el concepto de "libreria"
!                           por el concepto de "extension". Se modifican todas
!                           las palabras del codigo fuente y la documentacion
!                           en consecuencia. NOTA: hasta antes de este cambio
!                           Dainunek se llamaba "Dainulik". (Observacion solo
!                           por motivos historicos.)
!                         - Se retocan algunos mensajes de informacion.
!                         - IMPORTANTE!! Debido a los cambios se libera
!                           una nueva version de Dainunek: v1/080329.
!  2008/03/15  Eliuk Blau - IMPORTANTE!! Se cambia la licencia de Dainunek.
!                           Ahora esta licenciada bajo los terminos de LGPLv3.
!  2007/08/06  Eliuk Blau - Release 1 de esta extension.
!  2007/08/05  Eliuk Blau - Se crea el archivo.
!
!-------------------------------------------------------------------------------

#ifndef _DAINUNEK_H_;  ! se ha incluido ya?

Message "[DAINUNEK: <(DA): (IN)icializacion (UN)ificada de (E)xtensiones en Gl(K)>]";
System_file; Constant _DAINUNEK_H_;

!===============================================================================
! COMPROBACIONES INICIALES
!-------------------------------------------------------------------------------
! ERROR: Se necesita el Compilador Inform v6.30 o superior
#ifndef VN_1630;
  Message "[DAINUNEK: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAINUNEK: -> Se necesita el Compilador Inform v6.30 o superior]";
  Message fatalerror "";
#endif; ! VN_1630

! ERROR: Se necesita la Libreria Inform 6/11 o superior
#ifndef LIBRARY_VERSION;
  Message "[DAINUNEK: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAINUNEK: -> Se necesita la Libreria Inform 6/11 o superior]";
  Message fatalerror "";
#endif;
#iftrue (LIBRARY_VERSION < 611);
  Message "[DAINUNEK: ERROR - No se puede compilar el codigo del juego]";
  Message "[DAINUNEK: -> Se necesita la Libreria Inform 6/11 o superior]";
  Message fatalerror "";
#endif; ! LIBRARY_VERSION

!-------------------------------------------------------------------------------
! ERROR SI SE ACTIVA COMPILACION PARA MAQUINA-Z
#ifdef TARGET_ZCODE;
  Message "[DAINUNEK: ERROR - Se esta generando codigo para la Maquina Z]";
  Message "[DAINUNEK: -> La extension solo funcionara en la Maquina Glulx]";
  Message fatalerror "";
#endif; ! TARGET_ZCODE

!-------------------------------------------------------------------------------
! programador no proporciona rutina IdentifyGlkObject() en codigo del juego
#ifndef IdentifyGlkObject;
  Message "[DAINUNEK: Auto-Implementando Punto de Entrada IdentifyGlkObject()]";
#endif;  ! IdentifyGlkObject

! programador no proporciona rutina HandleGlkEvent() en codigo del juego
#ifndef HandleGlkEvent;
  Message "[DAINUNEK: Auto-Implementando Punto de Entrada HandleGlkEvent()]";
#endif; ! HandleGlkEvent
!===============================================================================

!-------------------------------------------------------------------------------
! ESTAS CONSTANTES LE PERMITEN AL PROGRAMADOR DE LA EXTENSION QUE USARA DAINUNEK
! COMPROBAR SI ACASO ALGUNO DE LOS PUNTOS DE ENTRADA GLK YA HA SIDO IMPLEMENTADO
! POR EL PROPIO PROGRAMADOR DEL JUEGO O SI LO HA HECHO, EN SU DEFECTO, LA PROPIA
! DAINUNEK. LAS CONSTANTES SOLO EXISTEN PARA PERMITIR MOSTRAR MENSAJES DE AVISO
! APROPIADOS DURANTE LA COMPILACION. EL SIGUIENTE ESQUEMA MUESTRA COMO MONTAR
! DE MANERA CORRECTA ESTE TIPO DE MENSAJES DE COMPILACION (POR EJEMPLO):
!
! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
!
!  ! el programador proporciona rutina IdentifyGlkObject() en el codigo del juego
!  #ifdef IdentifyGlkObject;
!    #ifndef DAINUNEK_IGO; ! codigo segun Dainunek
!      Message "[EXTENSION: Usando rutina IdentifyGlkObject() proporcionada por el juego]";
!      Message "[EXTENSION: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A]";
!      Message "[EXTENSION: -> < EXT_IdentifyGlk(fase,tipo,ref,rock); >]";
!    #endif; ! DAINUNEK_IGO
!  #endif; ! IdentifyGlkObject
!
!  ! el programador proporciona rutina HandleGlkEvent() en el codigo del juego
!  #ifdef HandleGlkEvent;
!    #ifndef DAINUNEK_HGE; ! codigo segun Dainunek
!      Message "[EXTENSION: Usando rutina HandleGlkEvent() proporcionada por el juego]";
!      Message "[EXTENSION: -> IMPORTANTISIMO: NO OLVIDES LLAMAR EN ESA RUTINA A]";
!      Message "[EXTENSION: -> < EXT_HandleGlk(ev,contexto,abortres); >]";
!    #endif; ! DAINUNEK_HGE
!  #endif; ! HandleGlkEvent
!
! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
!
! EL ESQUEMA ANTERIOR DEBE ESCRIBIRSE **SIEMPRE ANTES** DE INCLUIR DAINUNEK EN
! EL CODIGO DE LA EXTENSION QUE LA USARA. DE OTRA MANERA LOS MENSAJES MOSTRADOS
! PUEDEN NO RESULTAR APROPIADOS EN ESTRUCTURACIONES DEL CODIGO MAS COMPLEJAS.
!-------------------------------------------------------------------------------

#ifndef IdentifyGlkObject; ! Para IdentifyGlkObject() declaramos esta constante
  Constant DAINUNEK_IGO;   ! especial para manejo de mensajes de compilacion.
  #ifndef DAINUNEK_OK;     ! Truquito para avisar que Dainunek va a gestionar
    Constant DAINUNEK_OK;  ! al menos uno de todos los Puntos de Entrada Glk.
  #endif; ! DAINUNEK_OK
#endif; ! IdentifyGlkObject

#ifndef HandleGlkEvent;    ! Para HandleGlkEvent() declaramos esta constante
  Constant DAINUNEK_HGE;   ! especial para manejo de mensajes de compilacion.
  #ifndef DAINUNEK_OK;     ! Truquito para avisar que Dainunek va a gestionar
    Constant DAINUNEK_OK;  ! al menos uno de todos los Puntos de Entrada Glk.
  #endif; ! DAINUNEK_OK
#endif; ! HandleGlkEvent

#ifndef DAINUNEK_OK;
  Message "[DAINUNEK: -> AVISO: No se gestionara ningun Punto de Entrada Glk!]";
#endif; ! DAINUNEK_OK

!===============================================================================

! LA VERSION DE LA EXTENSION DAINUNEK
Constant _DAINUNEK_VERSION_ = 3;

!===============================================================================
! IMPLEMENTACION AUTOMATICA DE PUNTOS DE ENTRADA GLK GESTIONADOS POR DAINUNEK
!-------------------------------------------------------------------------------
! SI EL PROGRAMADOR NO PROPORCIONA LA RUTINA -- IdentifyGlkObject() --
#ifdef DAINUNEK_IGO;
  [ IdentifyGlkObject fase tipo ref rock;
      return Dainunek.IdentifyGlk(fase,tipo,ref,rock);
  ];
#endif; ! DAINUNEK_IGO

! SI EL PROGRAMADOR NO PROPORCIONA LA RUTINA -- HandleGlkEvent() --
#ifdef DAINUNEK_HGE;
  [ HandleGlkEvent ev contexto abortres;
      return Dainunek.HandleGlk(ev,contexto,abortres);
  ];
#endif; ! DAINUNEK_HGE
!-------------------------------------------------------------------------------

!===============================================================================
! --- OBJETO-GESTOR DE DAINUNEK ---
! TODA EXTENSION QUE OCUPE DAINUNEK TIENE QUE IMPLEMENTAR UN OBJETO ESPECIAL
! QUE DEBE ESTAR DENTRO DEL OBJETO-GESTOR 'DAINUNEK'. EL OBJETO ESPECIAL DEBE
! CONTAR CON UNA PROPIEDAD IdentifyGlk(), HandleGlk() O AMBAS SI LA EXTENSION
! NECESITA USAR AMBOS PUNTOS DE ENTRADA GLK.
!
! EL SIGUIENTE ESQUEMA MUESTRA COMO CODIFICAR DE MANERA CORRECTA ESTE
! OBJETO CON EL CODIGO QUE SE EJECUTARA PARA CADA PUNTO DE ENTRADA GLK:
!
! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
!
!  ! PARA LA INICIALIZACION UNIFICADA DE EXTENSIONES (PUNTOS DE ENTRADA GLK)
!  Include "Dainunek";
!
!  ! ERROR: Se necesita la Extension Dainunek v3 o superior
!  #ifndef _DAINUNEK_VERSION_;
!    Message "[EXTENSION: ERROR - No se puede compilar el codigo del juego]";
!    Message "[EXTENSION: -> Se necesita la Extension Dainunek v3 o superior]";
!    Message fatalerror "";
!  #endif;
!  #iftrue (_DAINUNEK_VERSION_ < 3);
!    Message "[EXTENSION: ERROR - No se puede compilar el codigo del juego]";
!    Message "[EXTENSION: -> Se necesita la Extension Dainunek v3 o superior]";
!    Message fatalerror "";
!  #endif; ! _DAINUNEK_VERSION_
!
!  #ifdef DAINUNEK_OK;
!    Object NombreDeLaExtension_Glk Dainunek
!      with
!        IdentifyGlk [ fase tipo ref rock;
!          ! el codigo necesario en este punto de entrada, por ejemplo...
!          return EXT_IdentifyGlk(fase,tipo,ref,rock);
!        ],
!        HandleGlk [ ev contexto abortres;
!          ! el codigo necesario en este punto de entrada, por ejemplo...
!          return EXT_HandleGlk(ev,contexto,abortres);
!        ],
!    ;
!  #endif; ! DAINUNEK_OK
!
! - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
!
! EN EL OBJETO, EL PUNTO DE ENTRADA HandleGlk() PUEDE DEVOLVER ALGUN VALOR DE
! RETORNO, PUESTO QUE EN EL PUNTO DE ENTRADA REAL HandleGlkEvent() SE ACEPTAN
! LOS VALORES DE RETORNO ESPECIALES -1 Y 2, QUE PERMITEN HACER CAMBIOS EN EL
! COMPORTAMIENTO DE LA ENTRADA DE TEXTO (MAS INFORMACION AL RESPECTO EN LA
! 'GUIA PARA PROGRAMADORES DE GLULX INFORM', DE ANDREW PLOTKIN).
!
! DAINUNEK DEVOLVERA FINALEMENTE EN EL PUNTO DE ENTRADA REAL HandleGlkEvent()
! EL VALOR DE RETORNO ESPECIAL MAS ALTO (-1, 2) ENCONTRADO DURANTE LA
! EJECUCION DE LOS PUNTOS DE ENTRADA HandleGlk() EN LOS OBJETOS QUE CADA
! EXTENSION COLOQUE DENTRO DEL OBJETO-GESTOR 'DAINUNEK', O CERO SI ACASO
! NINGUNA RUTINA HandleGlk() DEVOLVIO ALGUNO DE ESTOS VALORES ESPECIALES.
!
! - PARA LA RUTINA IdentifyGlk() EL VALOR DE RETORNO NO ES IMPORTANTE.
! - SI UNA EXTENSION NO NECESITA DEVOLVER NADA EN HandleGlk() NO ES
!   OBLIGATORIO TENER QUE USAR UN 'return' COMO EN EL EJEMPLO.
!-------------------------------------------------------------------------------

#ifdef DAINUNEK_OK;
  Object Dainunek
    with
      IdentifyGlk [ fase tipo ref rock
        obj;
        objectloop (obj in self) {
          if (obj provides IdentifyGlk && obj.IdentifyGlk ofclass Routine) {
            obj.IdentifyGlk(fase, tipo, ref, rock);
          }
        }
      ],
      HandleGlk [ ev contexto abortres
        obj tmp aux;
        tmp = 0; aux = -99; ! AVISO: no cambiar estos valores!!
        objectloop (obj in self) {
          if (obj provides HandleGlk && obj.HandleGlk ofclass Routine) {
            tmp = obj.HandleGlk(ev, contexto, abortres);
            if (tmp == -1 or 2) {
              if (tmp > aux) { aux = tmp; }
            }
          }
        }
        if (aux == -99) { aux = 0; } ! AVISO: no borrar esta linea!!
        return aux;
      ],
  ;
#endif; ! DAINUNEK_OK

#endif; ! fin de _DAINUNEK_H_
