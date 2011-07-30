! Grafdemo.h
!
!  Rutinas para mostrar automáticamente un gráfico al cambiar de
!  localidad o al examinar un objeto.
!
! (c) 2000 Zak McKracken 
!
! Son rutinas de alto nivel que realizan llamadas a SIX para el manejo
! de los gráficos, por lo que sirven tanto para juegos .z6 como para
! juegos Glulx (los detalles específicos de cada máquina se manejan
! desde SIX, y no desde este fichero).

Global NumGrafPrevia;   ! Gráfico mostrado la última vez que se llamó
                        ! a PintarGraficoLocalidad
Global MarcoPintado=0;  ! ¿Se ha pintado ya el marco de la imagen?
Global AnchoPrevio=0;   ! Ancho que tenía la pantalla la última vez
                        ! que se llamó a PintarGraficoLocalidad
                        ! (piensese que el jugador puede cambiar el
                        ! tamaño de la ventana del intérprete)


! PintaMarco dibuja la banderola sobre la cual aparecen los gráficos
! de cada localidad. La banderola está almacenada en el gráfico
! Marco_jpg. Además, el resto de la ventana se rellena con un patrón
! que se obtiene de Fondo_jpg
!
! El parámetro "forzar" fuerza a que se repinte
!
[ PintaMarco forzar ag;

    ag=AnchoDeVentanaGrafica();
    if (forzar||(AnchoPrevio==0)||(AnchoPrevio~=ag))
    {
	! Si la ventana ha cambiado de tamaño, hay que volver a pintar
	! el fondo y el marco, para que quede centrado en las nuevas
	! dimensiones.
	AnchoPrevio=ag;
	PatronFondoGraficos(Fondo_jpg);
    	PintarGraficoCentrado(Marco_jpg);
	MarcoPintado=0;
    }

    if (MarcoPintado==0)
    {
    	PintarGraficoCentrado(Marco_jpg);
    	MarcoPintado=1;
    }
];


! La siguiente función decide qué gráfico es el adecuado para esa
! localidad, y lo pinta centrado sobre la banderola anterior.
!
! Solo lo pinta si detecta que el gráfico ha cambiado, o si el
! parametro "forzar" vale true.
!
[ PintarGraficoLocalidad forzar
    n;

    ! Si estamos a oscuras, el gráfico a dibujar es Oscuridad_png
    ! Si no, lo sacamos de la propiedad numgrafico de la localidad
    ! actual (y si esta propiedad no existe, usamos el gráfico
    ! Sin_Imagen_jpg
    !
    if (localizacion==laoscuridad) n=Oscuridad_jpg;
    else if (localizacion provides numgrafico) n=localizacion.numgrafico;
    else n=Sin_Imagen_jpg;
    if (forzar||(n~=NumGrafPrevia))
    {
	NumGrafPrevia=n;
	PintaMarco(forzar);
	PintarGraficoCentrado(n);
	rtrue;
    }
    rfalse;
];


! La rutina TrasElPrompt se ejecuta siempre despues de que la librería
! haya impreso el prompt ">", es un buen momento para repintar el
! gráfico de la localidad.
!
[ TrasElPrompt;
    PintarGraficoLocalidad();
];


! Lo siguiente es un punto de entrada de SIX. Debe ocuparse de
! repintar el gráfico de la localidad:
!
[ RepintarGraficos;
    PintarGraficoLocalidad(true);
];



! Cambiamos la rutina ExaminarSub por otra que además dé la
! descripción, muestre el gráfico del objeto (es decir, cuando el
! jugador ponga EX OBJETO, saldrá una imagen de éste, además de su
! descripción. La imagen se toma de la propiedad numgrafico del
! objeto, si tiene una).
!
! La rutina se ha escrito "copiando y pegando" la que venía en
! Acciones.h, y añadiéndole simplemente las lineas señaladas
!
Replace ExaminarSub;
[ ExaminarSub i;
    if (localizacion==laoscuridad) return M__L(##Examinar,1);

 ! -----AÑADIDO
    if (uno provides numgrafico)
	PintarGraficoEnLinea(uno.numgrafico, imagealign_inlineup);
    ! puedes cambiar el tipo de alineación, si prefieres.
 ! -----FIN DE AÑADIDO

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

!================================================================
! FIN DE Grafdemo.h

