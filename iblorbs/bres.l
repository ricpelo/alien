%option caseless
%option yylineno
%option noyywrap
%{
/* Bres: The Blorb Resource Compiler
/* V .4b by L. Ross Raszewski
/* Copyright 2000 by L. Ross Raszewski, but freely distributable.
*/

#include <stdio.h>
#include <string.h>
#include "short.h"   // For ShortProgramName
/* The version and boilerplate messages.  The string is formatted
/* with the assumption  that it will be printed with the program name,
/* compile date, and version string
*/
#define VERSION ".4b"
#define BOILER "%s: Blorb Resource Compiler (%s)\nVersion %s by L. Ross Raszewski\n"

// The 6 types of recognized blorb types
#define pic 0
#define sound 1
#define exec 2
#define copy 3
#define author 4
#define note 5
#define release 6
#define palette 7
#define resolution 8
#define palettehi 9
#define palettetru 10
#define ifhd 11
#define ifmd 12
// Default File Extensions
#define BLC_EXT ".blc"
#define INF_EXT ".bli"
#define RES_EXT ".res"

// Output file for BLC
FILE *Blurb;
// Output file for Inform
FILE *InfFile;

/* The name of the program -- on unix systems this should be identical to
/* argv[0].  DJGPP rewrites argv[0] to the cannonical file name, so
/* this is where we undo all that.
*/

char *MyName;

// The type of the current directive
int type=0;
// Buffer for inform identifier
char Ident_Buffer[128];
/* Number to be associated with a resource.  I start pictures and sounds at
/* 3 to ensure that they map to reachable z-machine resources (Sounds 1 and 2
/* in inform are considered to be "beeps")
*/
int ChType[] = { -1, -1, -1, 0, 0, 0, 1, 2, 2, 0, 0, 2, 2 };
int ResNum[] = { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,0,0};
char *StrN[] = { "0", "1", "2" };
// Function Prototypes
char *GuessForm(char *File, int type);
void CreateEntry(int type, char *Ident, char *Text);

// The Blorb names of recognized chunks, in the order given above.
char *BlbName[] = { "Pict", "Snd", "Exec", "(c)", "AUTH", "ANNO", "RelN",
                    "Plte", "Reso", "Plte", "Plte", "IFhd", "IFmd" };

// Guess table for mapping extensions to chunk types
char *Ext2Form[] = { "jpg",   "JPEG",
                     "jpeg",  "JPEG",
                     "jpe",   "JPEG",
                     "jfif",  "JPEG",
                     "png",   "PNG",
                     "aif",   "FORM",
                     "aiff",  "FORM",
                     "mod",   "MOD",
                     "z3",    "ZCOD",
                     "z4",    "ZCOD",
                     "z5",    "ZCOD",
                     "z6",    "ZCOD",
                     "z7",    "ZCOD",
                     "z8",    "ZCOD",
                     "dat",   "ZCOD",
                     "ulx",   "GLUL",
                     "ogg",   "OGGV"
                    
               };
#define KNOWN_EXT 17
char fpflag=0;
%}

%s START GETID GETSTR GETSTR2 GETINT

%%
<START>PICTURE                          type=pic; BEGIN GETID;
<START>SOUND                            type=sound; BEGIN GETID;
<START>CODE                             type=exec; BEGIN GETSTR;
<START>COPYRIGHT                        type=copy; BEGIN GETSTR;
<START>AUTHOR                           type=author; BEGIN GETSTR;
<START>NOTE                             type=note; BEGIN GETSTR;
<START>RELEASE                          type=release; BEGIN GETINT;
<START>PALETTE                          type=palette; BEGIN GETSTR;
<START>HEADER                          type=ifhd; BEGIN GETSTR;
<START>METADATA                        type=ifmd; BEGIN GETSTR;
<START>FRONTISPIECE                          type=pic; fpflag=1; BEGIN GETSTR;
<START>HIGHCOLOR                        type=palettehi; CreateEntry(type,Ident_Buffer,"\x10");
<START>TRUECOLOR                        type=palettetru; CreateEntry(type,Ident_Buffer,"\x20");
<START>RESOLUTION                       type=resolution; BEGIN GETSTR;
<START>[ \t\n]+
<START>![^\n]*
<GETINT>[0-9]+[ \t]*\n                  CreateEntry(type,Ident_Buffer,yytext); BEGIN START;
<GETINT>[ \t]+
<GETID>[ \t]+
<GETID>[a-z_][A-Z0-9_]*                 strcpy(Ident_Buffer,yytext); BEGIN GETSTR;
<GETSTR>[ \t]+                          BEGIN GETSTR2;
<GETSTR2>[^\n]+                         CreateEntry(type,Ident_Buffer,yytext); BEGIN START;
%%

void CreateEntry(int type, char *Ident, char *Text)
/* CreateEntry writes the BLC control file and Inform source file based on
/* the lexer's input:
/*  type: The type of the chunk, as defined above
/*  Ident: The inform identifier (unsused for non-resources)
/*  Text: The actual text of the BLC entry
/*        (For resources, this is a filename.  For other resoruces, this is
/*         the literal text of the chunk
*/
{
  char *Form; char *Res;
  char ff=fpflag;
  fpflag=0;
  /* Pict, Sound, and Exec are "resource types", so we need to know
  /* both a file type and a usage.  We use the value in the type table
  /* for the usage, and try to determine the file type from the extension.
  */
  if (ChType[type]==-1) {
        Form=GuessForm(Text,type);
        Res=BlbName[type];
        // Write the constant declaration to the Inform source file.
        if (type!=exec) /* Exec is a special case; it's a resource with no
                        /* associated Inform name
                        */
        fprintf(InfFile,"Constant %s %d;\t!Blorb %s:%s\n",
                Ident,ResNum[type],BlbName[type],Text);
        if (ff)
        fprintf(InfFile,"Constant FRONTISPIECE_ib %d;\t!Blorb %s:%s\n",
                ResNum[type],BlbName[type],Text);

        }
  /* For non-resource types, the type is stored in the BlbName table,
  /* and we use "0" as the resource usage (This will flag to BLC that
  /* the chunk is not a resource, and needs not be indexed with them)
  */
  else { Form=BlbName[type];
         Res=StrN[ChType[type]];
       }
  // Write the chunk data to the BLC control file.
  fprintf(Blurb, "%s %d %s %s\n",
                 Res,
                 ResNum[type],
                 Form,
                 Text
         );
  if (ff)
  fprintf(Blurb, "3 0 Fspc %d\n",
                ResNum[type]
         );

  /* Bump up the resource number. This is not really important for
  /* non-resources, but it does ensure that each blorb chunk will
  /* have a unique identifier in the BLC control file.
  */
  ResNum[type]++;
}

char *GuessForm(char *File, int type)
/* GuessForm tries to guess a chunk type based on the name of the file
/*  File: The file name
/*  type: The resource type of the file
/* Returns: the literal blorb chunk type of the file.
*/
{
 /* Isolate the extension as the part of the strign following the last
 /* full stop.
 */
 char *Ext=strrchr(File,'.');
 static char *Form;
 Form=NULL;
 //Don't even bother if there wasn't a full stop in the name
 if (Ext)
 {
  int i;
  Ext++; // Wind past the period
  // Search the known extensions table for a blorb type
  for(i=0;i<KNOWN_EXT*2;i+=2)
   if (strncmp(Ext2Form[i],Ext,strlen(Ext2Form[i]))==0) break;
  /* This is, "if there was a match, the form type is the corresponding
  /* entry in the table."
  */
  if (i<KNOWN_EXT*2)
   Form=Ext2Form[i+1];
 }
 // If one wasn't found, or the last block was skipped
 if (!Form)
 {
  // Default types for known resources.
  if (type==pic) Form="PNG";
  else if (type==sound) Form="FORM";
  else Form="ZCOD";
  // Warn the user that this is only a guess.
  printf("%s: Warning: %d: Can't determine the type of file \"%s\".\n\
\tGuessing \"%s\".\n",MyName,yylineno, File, Form);
 }
 return Form;
}


main(int argc, char **argv)
{
  char BlurbName[128];
  char InfName[128];
  char InName[128];
  char *nameroot;
  // Strip off the path and .exe for DJGPP builds
  MyName=ShortProgramName(argv[0]);
  // Print the boilerplate
  printf(BOILER,MyName,__DATE__,VERSION);
  // Print error usage.
  if (argc<2)
  {
   printf("%s: Error: usage: usage must be one of:\n"
" %s base                To use base%s, base%s, and base%s\n"
" %s in.res base         To use in.res, base%s, and base%s\n"
" %s in.res b.blu c.h    To use in.res, b.blu and c.h\n",
 MyName,MyName, RES_EXT,BLC_EXT, INF_EXT, MyName, BLC_EXT, INF_EXT,MyName);
   exit(1);
   }
  // One argument was given: generate all three names based on the argument
  if (argc==2)
  {
   nameroot=argv[1];
   strcpy(InName,nameroot);
   strcat(InName,RES_EXT);
  }
  /* If two or three arguments are given, the input name is the literal 
  /* first argument.
  */
  else {
        nameroot=argv[2];
        strcpy(InName,argv[1]);
       }
  // If three arguments were given, use the literal arguments for output
  if (argc==4)
  {
   strcpy(BlurbName,argv[2]);
   strcpy(InfName,argv[3]);
  }
  else
  // If one or two arguments were given, generate the output file names
  {
   strcpy(BlurbName,nameroot);
   strcpy(InfName,nameroot);
   strcat(InfName,INF_EXT);
   strcat(BlurbName,BLC_EXT);
  }
  // Open the input file as the lexer input
  yyin=fopen(InName,"r");
  // Open the blc control file and inform file for output
  Blurb=fopen(BlurbName,"w");
  InfFile=fopen(InfName,"w");
  // Abort if any of the files didn't open.
  if (!yyin)
  {
   printf("%s: Error: (before compilation): Cannot open input file \"%s\"\n",
           MyName,InName);
   exit(1);
  }
  if (!Blurb)
  {
   printf("%s: Error: (before compilation): Cannot open output file \"%s\"\n",
           MyName,BlurbName);
   exit(1);
  }
  if (!InfFile)
  {
   printf("%s: Error: (before compilation): Cannot open output file \"%s\"\n",
           MyName,InfName);
   exit(1);
  }

  // Print a comment header for the blorb file
  fprintf(InfFile,"! Blorb Resource Definitions File\n"
"! Generated automatically by %s.\n"
"! Do not edit!\n"
"! Include this file in your inform source with \"Include \"%s\";\"\n\n"
"Message \"Including %s resource declarations generated on %d-%d-%d\";\n\n",
  MyName, InfName,MyName,1,1,1);

  // Fire up the lexer
  BEGIN START;
  yylex();
  // Close the files
  fclose(yyin);
  fclose(Blurb);
  fclose(InfFile);
  // And delete MyName
  free(MyName);
 return(0);

}
