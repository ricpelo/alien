/* short.c:
/* ShortProgramName turns a fully qualified file name (specifically, DJGPP
/* style argv[0] into the simple program name (strips directory and
/* extension)
/* Returns new memory, which must be freed by the program.
*/
#include <string.h>
#include <stdlib.h>
char *ShortProgramName(char *argv)
{
  char *MyName;
  MyName=strrchr(argv,'/');
  if (MyName) MyName++;
  else MyName=argv;
  MyName=strdup(MyName);
  if (strrchr(MyName,'.')) *(strrchr(MyName,'.'))=0;
  return MyName;
}
