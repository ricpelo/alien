// CINFORM
// (C) Sarganar, Baltasar, Presi
// ANSI C Consultors: Baltasar, Presi


// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


#include <cstdio>
#include <cstdlib> //for exit() 
#include <cctype>
#include <cstring>

#include "lista.h"

#define IS_WE      0
#define ISNOT_WE   1
#define IS_DICT    2
#define IS_COMMENT 3
#define IS_STRING  4
#define IS_IDLE    5

#define SI   1
#define NO   0

using namespace std;

char token_state  = IS_IDLE;


long tokenise(long i_sel, char *source, char *text_in, char *traducible);
char *traducir(char * text_in);
void add_text (char *destiny, char *text_out);
void help(void);

long chIndex = 0;
long size_txt = 2048;//tamaÒo de text_in, que alberga los tokens a procesar
long file_length=0;
char **lista1;
char **lista2;
FILE *fptr,*dbgFile,*outFile;

// Compara dos cadenas sin importar mays/mins
int strcmpi2(char *s1, char *s2)
{
   for (; *s1 && *s2 && (toupper(*s1) == toupper(*s2)); ++s1, ++s2);
//   printf ("comparando..\n");
   return *s1 - *s2;
}

int main(int argc, char *argv[])
{
   FILE * File1;
   char ch;
   char traducible; // 1: el token es traducible: va a ser procesado
   char *text_out; // puntero a token traucido
   long new_t;
   char *file_in;// nombre del archivo de salida
   int len_f;
   
   char spa2eng = 1; // 1: spanish to english
                     // 0: english to spanish
                     
   printf ("\nCINFORM : Conversor InformATE! a Inform (y viceversa)\n");
   printf ("           by Sarganar - Release 701.4\n");
   printf ("           ANSI C consulter: Baltasar, Presi.\n");

   if (argc <2)
   {   help ();exit(1);}
   
   for (int g=0; g<argc; g++)
//     printf ("Argumento %d: %s\n",g,argv[g]);

   printf("Check option\n");
   // ej: sinform -outsp archivo.inf
   if (argc > 2){
      char *arg_lengua = argv[1];
      if ( strcmpi2(arg_lengua,"-outsp")==0 ){
            spa2eng = 0;
      }else if ( strcmpi2(arg_lengua,"-outeng")==0 ){
            spa2eng = 1;
      }else{
            help (); exit (1);
      } 
                  
   file_in = argv[2];
   len_f = strlen (argv[2]);
   }else {      
   file_in = argv[1];
   len_f = strlen (argv[1]);
   }// if (argc>2
   
   char file_out [len_f];// nombre del archivo de salida
   memset (file_out,0,len_f); 
   strcat(file_out,file_in);

   printf("Set extention output file\n");

   if ( spa2eng )
      strcat(file_out,".eng");// renombre del archivo de salida
   else
      strcat(file_out,".spa");// renombre del archivo de salida
   
   
   // carga de las listas de palabras, segun spa2eng para traducir
   //   hacia un lado o hacia el otro

   printf("Load words lists\n");
   // Preparar lista1 y lista2 para que apunten a las listas
   // adecuadas
   if ( spa2eng ) {
	lista1 = listaSPA;
	lista2 = listaENG;
   } else {
        lista2 = listaSPA;
        lista1 = listaENG;
   }

    printf("Open source file\n");

   //Apertura del archivo fuente para cargarlo en 'source[]'
   if ( (File1=fopen(file_in,  "rt" ))==NULL){
      printf ("Error al abrir archivo.\n");    
      exit(1);
   }   

   //Extraccion tamaÒo de archivo
   fseek( File1, 0, SEEK_END );
   file_length = ftell( File1 );
   fseek( File1, 0, SEEK_SET );

   //Apertura del archivo fuente para cargarlo en 'source[]'
   if ( (fptr = fopen (file_in, "r"))==NULL){
      perror ("Error");
      printf("\n");
      exit(1);
   }   

   char source [file_length]; //contendra el archivo de partida (fuente)
   char destiny [file_length];//contendra el archivo de llegada
   char text_in [size_txt];   //contendra los tokens parciales para procesar
  
   memset (source, 0, file_length);
   memset (destiny, 0, file_length);
   memset (text_in, 0, size_txt);

   printf("Open destiny file\n");
     
//   dbgFile=fopen("words_count.csv", "aw"); 
   outFile =fopen(file_out, "w"); //archivo out o de llegada ('traducido')
   
   printf("Load source file\n");
//carga del archivo de salida (fuente)
   while (!feof(fptr))
   {
     source [chIndex] = fgetc(fptr);
 //    fprintf(dbgFile,"%c",source [chchIndex]);
 //    printf("%c",source [chIndex]);

     chIndex++;
   }
   fclose (fptr);

   chIndex = chIndex -2; //fix true value (true size)
   
   printf ("Cantidad de bytes leidos: %d\n",chIndex);
   if ( spa2eng )
      printf ("\nInformATE! ---> Inform \n");
   else
      printf ("\nInform ---> InformATE!\n");
   
    printf ("\nProcesando...\n");
   
 /////////////////////////////////////////// 
 // Procesamiento (tokenizado y traduccion)  
 ///////////////////////////////////////////
   for (long t=0; t<chIndex ; t++)
   {
      new_t = tokenise (t, source, text_in, &traducible);
      t = new_t-1;
      if (traducible){
//        fprintf(dbgFile,"%s,1\n",text_in);
        text_out = traducir (text_in);
      }else{
        text_out = text_in;// no traducible
      }
      
      add_text(destiny, text_out);
//      printf("t = %d\n",t);     
  } // for
   
 fprintf(outFile,"%s",destiny);//volcar al disco
               
//   fclose (dbgFile);
   fclose (outFile);
   printf("\n  Proceso Finalizado.\n"); 
   printf("  Archivo traducido: %s\n\n",file_out);
   printf("  No se han traducido strings, palabras de diccionario ni lÌneas comentariadas.\n");
   if ( spa2eng ){
      printf("  Cambia los Include \"EParser\"   --> Include \"Parser\"\n");
      printf("             Include \"Acciones\"  --> Include \"Verblib\"\n");
      printf("             Include \"Gramatica\" --> Include \"SpanishG\"\n");
   }
//   ch = getche();
   return 1;
}


////////////////////////////////////////////////////////////////////////////////
// Funciones Auxiliares
//

long tokenise(long i_sel, char *source, char *text_in, char *traducible){
    // 'secciona' el texto en tokens que pueden ser:
    // IS_WE : is word element: palabra traducible (if, has, with, luz, etc)
    // el resto no se traducen, la idea es que pasan derecho al archivo de llegada:
    // IS_DICT: is dictonary word: palabra de diccionario 'verde' 'madera'(o frase dentro de un string)
    // IS_STRING: is string: es un string "El Protector^"
    // IS_COMMENT: is comment: es un comentario o ICL (empieza con !)
    // ISNOT_WE: particulas restantes (espacios, tabulaciones, ##, (), ];, etc)
     
    // se tiene en cuenta que quizas el token quede mas grande que text_in
    // en ese caso no se resetea token_state a IDLE y la proxima vez que 
    // entre aqui, se va directamente al switch, siguiendo con el 'resto'
    // del gran token. Solo para IS_STRING , ISNOT_WE y IS_COMMENT
    
    char ch;
    long count = 0;
    
    memset (text_in, 0, size_txt); //flush text_in
    
    ch = source [i_sel];
    
    if (token_state == IS_IDLE)
    {
        if ( isalnum(ch) != 0 || ch == '_' || strchr("·ÈÌÛ˙Ò—¸‹¡…Õ”⁄",ch)!= 0 )
                token_state = IS_WE;
        else if (ch == 39) // ' :palabras de diccionario
                token_state = IS_DICT;
        else if (ch == 34) // " :strings
                token_state = IS_STRING;
        else if (ch == '!') // comentario
                token_state = IS_COMMENT;
        else
                token_state = ISNOT_WE;
    }
    
    switch (token_state)
    {
      case IS_WE:
            while ( isalnum(ch) !=0 || ch=='_' || strchr("·ÈÌÛ˙Ò—¸‹¡…Õ”⁄",ch)!= 0){
               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
            }      
//            text_in [count] = 0;
            *traducible = SI;
            break;
      case IS_DICT:
               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
            while ( ch != 39 ){
               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
//               printf ("ch = %d \n",ch);
            }
               text_in [count] = ch;
               count++;
               i_sel++;
//               text_in [count] = 0;   
            *traducible = NO;   
//            printf ("text_in : %s\n",text_in);
            break;
      case IS_STRING:
               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
            while ( ch != 34 && count < size_txt){
               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
            }
               if (count < size_txt)
                   text_in [count] = ch;
//               count++;
               i_sel++;
//               text_in [count] = 0;   
            *traducible = NO;   
//            printf ("text_in : %s\n",text_in);
            break;
      case ISNOT_WE:
            while ( ch != 39 && ch != 34 && isalnum(ch) ==0 && ch!='_' && ch!='!' && i_sel <= chIndex && count < size_txt){

               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
            }
//            text_in [count] = 0;
            *traducible = NO;   
            break;
      case IS_COMMENT:
            while ( ch != 10 && i_sel <= chIndex && count < size_txt){
               text_in [count] = ch;
               count++;
               i_sel++;
               ch = source [i_sel];
            }
//            text_in [count] = 0;
            *traducible = NO;   
            break;
      default:
//            text_in [0] = 0;   
            
            break;
    } //case
// printf ("text_in : %s\n",text_in);

    if (count < size_txt)
        token_state = IS_IDLE;
 
    return i_sel; //retorna actual posicion en source[]
}

//////////////////////////////////////////////////////////////////
// *traducir(char * text_in)
// devuelve la palabra traducida segun una consulta con las listas.
//     *text_in : token a traducir
//    Si no se encuentra token en la lista, lo devuelve.
//    La comparacion de cadenas no tiene en cuenta mayusculas/minusculas.
char *traducir(char * text_in){
    
    for (int q=0; *lista1[q] != 0 ;q++){
        if ( strcmpi2(text_in,lista1[q])==0 ){ // palabra traducible?
//                printf ("%s --> %s \n",text_in,lista2[q]);
                return lista2[q];
        }
    }    
//    printf ("no traducible --> %s \n",text_in);
           
    return text_in; // palabra no traducible
}

//////////////////////////////////////////////
//  add_text (char *destiny, char *text_out)
//     Concatena strings.
//    *text_out : texto a agregar
//    *destiny : strings al que se la va agragndo texto
//    Si el tamaÒo de destiny se supera, vuelca todo el contenido al disco,
// limpia destiny y sigue.
void add_text (char *destiny, char *text_out){

      if ( (strlen (text_out)+strlen (destiny))<file_length ){
            strcat(destiny,text_out);
      }else{//superada la capacidad de 'destiny', volcar lo que tiene al disco
        fprintf(outFile,"%s",destiny);
//         printf ("text_out : %s\n",destiny);
         memset (destiny, 0, file_length);
         strcat(destiny,text_out);
         printf ("superada la capacidad de 'destiny'\n");
      }

}

void help (){
            printf ("\n   Para usar SINFORM debes tipear 'SINFORM  [-outsp/-outeng] archivo'\n");
            printf ("\n        -outsp : Traduce inform --> informATE!\n");
            printf ("\n        -outeng: Traduce informATE! --> inform\n\n");
            printf ("\n        no poner parametro-idioma se entiende como -outeng.\n");


}
