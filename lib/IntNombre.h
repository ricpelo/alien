!#######################################################################################
! Parsenoun alternativo para infSP6 basado en el Intnombre.h de InformATE de Zak
! 27-Nov-20007 . Actualizacion by JaReL
!#######################################################################################
! Modo de empleo:
! incluir en el código de tu aventura lo siguiente:
!
!       Replace ParseNoun; 
!       Include "SpanishG";
!       Include "intnombre.h";
! Con esto habremos reemplazado la funcion Parsenoun por defecto proporcionada en SpanishG.h
!#######################################################################################
! El nuevo parsenoun permite elegir entre dos opciones:
!
! 0- Parseado admitiendo nombres y adjetivos, priorizando los primeros en caso de duda con otro objeto.
! Con este modelo serían válidas las expresiones:
! "EX MADERA", "EX MESA DE MADERA", "EX MESA".
! (Éste es el modelo por defecto, si deseas parsear siempre así, no necesitas utilizar este módulo)
!
! 1- Parseado admitiendo los adjetivos EXCLUSIVAMENTE cuando al menos un nomnbre del objeto ha sido detectado.
! Con este segundo modelo serían válidas la expresiones: 
! "EX MESA", "EX MESA DE MADERA"... pero NO "EX MADERA" (queriendo referirnos a la mesa de madera)
!
! AVISO: Este modelo segundo modelo inhabilita las respuestas breves las preguntas de desmabiguación
! del parser del tipo:
! ¿A cuál te refieres, al paraguas amarillo o al paraguas azul?
! Ya no podremos responder simplemente por los adjetivos "el amarillo" o "el azul",
! sino que tendremos que responder "el paraguas amarillo" o "el paraguas azul"
!
! Se pueden alternar los dos modelos durante el juego cambiando el valor de la variable parseado_estricto
! a los valores 0 o 1. 
! Desde el Prompt se puede cambiar con el comando "modoparsing".
!
! Si queremos utilizar el modo estricto de partida, escribiremos dentro de [ Initialise;
! parseado_estricto =1;
!
!
!
!#######################################################################################

Global parseado_estricto = 0; !valores:
				     ! parseado_estricto =0: admite nombres y adjetivos
				     ! parseado_estricto =1: admite adjetivos sólo si al menos hay un nombre también.

[ ParseNoun obj n m dudas seguir gen p aux;

    n=0;   ! numero de palabras reconocidas de momento
    m=0;   ! * numero de nombres reconocidos de momento    
    seguir=1;  ! seguir mirando palabras para ver si las siguientes
               ! se refieren a este mismo objeto

    aux=aux;
    #ifdef DEBUG;
    aux=debug_flag;
    debug_flag=0; ! Desactivar trazado de give (para no cansar con tanto 'nombreusado' cambiando continuamente)
    #endif;
!    #ifndef NI_BUILD_COUNT;
    give obj ~nombreusado; ! resetear nombreusado (quitar nombreusado)
    gen=5;    ! 1=masculino, 2=femenino,
              ! 3=masculino plural, 4= femenino plural
              ! 5=sin determinar


    while(seguir)
    {
    p=NextWord();
    if ((p=='de')&&(n==0)) return 0;
    
!     if (WordInProperty(p, obj, name))
!         ! Una palabra que se refiere al objeto
!     {
!         n++;        ! la contamos
!         n=n+dudas;        ! añadimos todos los "de" "la"...
!                 ! que estaban sin contar
!         dudas=0;        ! y resetamos el contador de "de"s
!         continue;        ! volvemos al while
!     }
    if (WordInProperty(p, obj, name_f))
        ! Una palabra que se refiere al objeto
    {
            if (p) dict_flags_of_noun = (p->#dict_par1) & $$01110100;
        if (gen==5) gen=G_FEMENINO;
            n++;        ! la contamos
		m++;        ! * contamos nombre
        n=n+dudas;        ! añadimos todos los "de" "la"...
                ! que estaban sin contar
        dudas=0;        ! y resetamos el contador de "de"s
!        print " --> es ahora femenino...." ; !infsp debug
        continue;        ! volvemos al while
    }
    if (WordInProperty(p, obj, name_mp))
        ! Una palabra que se refiere al objeto
    {
            if (p) dict_flags_of_noun = (p->#dict_par1) & $$01110100;
        if (gen==5) gen=G_MASCULINO+G_PLURAL;
            n++;        ! la contamos
		m++;        ! * contamos nombre
        n=n+dudas;        ! añadimos todos los "de" "la"...
                ! que estaban sin contar
        dudas=0;        ! y resetamos el contador de "de"s
        continue;        ! volvemos al while
    }
    if (WordInProperty(p, obj, name_fp))
    {
            if (p) dict_flags_of_noun = (p->#dict_par1) & $$01110100;
        if (gen==5) gen=G_FEMENINO+G_PLURAL;
            n++;        ! la contamos
		m++;        ! * contamos nombre
        n=n+dudas;        ! añadimos todos los "de" "la"...
                ! que estaban sin contar
        dudas=0;        ! y resetamos el contador de "de"s
        continue;        ! volvemos al while
    }
    ! [I7] se cambio de lugar este if para buscar el name_m (o name)
    ! en ultimo lugar, debido a una interferencia q provoca la asignacion 'automatica' de 
    ! plural en los objetos I7
    if (WordInProperty(p, obj, name_m))
        ! Una palabra que se refiere al objeto
    {
            if (p) dict_flags_of_noun = (p->#dict_par1) & $$01110100;
        if (gen==5) gen=G_MASCULINO;
            n++;        ! la contamos
		m++;        ! * contamos nombre
        n=n+dudas;        ! añadimos todos los "de" "la"...
                ! que estaban sin contar
        dudas=0;        ! y resetamos el contador de "de"s
!        print " --> es ahora masculino...." ; !infsp debug
        continue;        ! volvemos al while
    }
    if (WordInProperty(p, obj, adjectives))
    {
            if (p) dict_flags_of_noun = (p->#dict_par1) & $$01110100;
            n++;        ! la contamos
	
        n=n+dudas;        ! añadimos todos los "de" "la"...
                ! que estaban sin contar
        dudas=0;        ! y resetamos el contador de "de"s
        continue;        ! volvemos al while
    }
        
    ! Si la palabra no fue reconocida, miraremos si se trata
    ! de 'de' o un artículo. En este caso mantenemos la duda y
    ! seguimos mirando palabras, hasta que una de ellas encaje
    ! en este objeto, en cuyo caso se retornan todas las que se
    ! han leido, o bien se encuentre una que no encaja en cuyo
    ! caso se retorna las que se habían encontrado antes del "de"


    else if (p== 'el' or 'la' or 'los' or 'las' or 'de' )

    {
        dudas++; continue;
    }
        
    else seguir=0;   ! Si no fue reconocida, ni un articulo, ni "de"
             ! nos damos por vencidos
    }! while block
    
    if (obj provides gender)
        switch(gen)
        { ! Los casos del switch estaban mal.
          ! Bug corregido en 001030
          1: give obj ~female ~pluralname; !infsp fix for I7 compatibility (en I7 no se puede asignar el 0 a gender, de 1 para arriba, sí)
          2: give obj female ~pluralname;!print " FEMALE GIVEN "; !infsp debug
          3: give obj ~female pluralname;
          4: give obj female pluralname;
        }
    if (gen<5) give obj nombreusado;

    
#ifdef DEBUG;
    debug_flag=aux;
#endif;

! despreciamos el objeto si no ha sido referenciado al menos uno de sus nombres.
if(parseado_estricto>0)if(m==0)return 0; 

    return n;

];    

