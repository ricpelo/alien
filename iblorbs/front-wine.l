%option caseless
%{
/* Front: The Inform-Blorb Frontend
/* V .2b by L. Ross Raszewski
/* Copyright 2000 by L. Ross Raszewski, but freely distributable.
*/

#include <stdio.h>
#include <string.h>

// The three programs front calls.
char *Inform="inform-wine";
char *Bres="bres";
char *Blc="blc";
char **setv;  // The variable to be set

%}
%s START GETL GETL2
%%
<START>INFORM                   setv=&Inform; BEGIN GETL;
<START>BRES                     setv=&Bres; BEGIN GETL;
<START>BLC                      setv=&Blc; BEGIN GETL;
<START>[ \n\t]+
<GETL>[ \t]*                    BEGIN GETL2;
<GETL2>[^\n]+                   *setv=strdup(yytext);
%%

main(int argc, char **argv)
{
 char cmdbuf[1024];
 int status;
 int i;
 char res[128], h[128], blc[128], blb[128];
 // Print an error-usage message
 if (argc<2) { printf("Frontend: usage: Usage is:\n\
        front name-root [inform-options]\n");
        exit(1);
        }
 // Generate the names for the resource, inform, blc, and blorb files
 strcpy(res,argv[1]);
 strcpy(h,argv[1]);
 strcpy(blc,argv[1]);
 strcpy(blb,argv[1]);
 strcat(res,".res");
 strcat(h,".bli");
 strcat(blc,".blc");
 strcat(blb,".blb");
 BEGIN START;
 // Check infb.rc for overrides
 yyin=fopen("infb.rc","r");
 if (yyin) yylex();
 
 // Build the command line to bres
 strcpy(cmdbuf,Bres);
 strcat(cmdbuf," ");
 strcat(cmdbuf,res);
 strcat(cmdbuf," ");
 strcat(cmdbuf,blc);
 strcat(cmdbuf," ");
 strcat(cmdbuf,h);
 // Tell the user what we're doing
 printf("Running: %s\n",cmdbuf);
 // And do it.
 if (status=system(cmdbuf)) exit(status);

 // Build the command line to inform
 strcpy(cmdbuf,Inform);
 for(i=2;i<argc;i++)
 { strcat(cmdbuf," ");
   if (argv[i][0] == '$')
      strcat(cmdbuf, "\\");
   strcat(cmdbuf,argv[i]);
 }
 // And run it
 printf("Running: %s\n",cmdbuf);
 if (status=system(cmdbuf)) exit(status);

 /* Build the command line to blc (we do this now in case the user wanted
 /* To put the compiled program in the blorb)
 */
 strcpy(cmdbuf,Blc);
 strcat(cmdbuf," ");
 strcat(cmdbuf,blc);
 strcat(cmdbuf," ");
 strcat(cmdbuf,blb);
 printf("Running: %s\n",cmdbuf);
 return(system(cmdbuf));

 // Ditch the blc control file.
 unlink(blc);
}

