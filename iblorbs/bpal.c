#include <stdio.h>
#include "bpal.h"
palette *ReadBlorbPalette(char *f)
{
  palette *p=NULL;
  FILE *Pal=fopen(f,"rb");
  if (Pal)
  {
   int t;
   fseek(Pal,0,SEEK_END);
   t=ftell(Pal);
   fseek(Pal,0,SEEK_SET);
   p=ReadPaletteFromFile(Pal,t);
   fclose(Pal);
  }
  return p;
}
palette *ReadPNGPalette(char *f)
{
 palette *p=NULL;
 FILE *Pal=fopen(f,"rb");
 int i; char type[4];
 if (!Pal) return NULL;
 fseek(Pal,8,SEEK_SET);
 fread(&i,4,1,Pal);
 i=ntohl(i);
 fread(type,4,1,Pal);
//  printf("Chunk %c%c%c%c, length %d\n",type[0],type[1],type[2],type[3],i);
 while (!(type[0]=='P' &&
          type[1]=='L' &&
          type[2]=='T' &&
          type[3]=='E') && !feof(Pal))
 {
  fseek(Pal,i+4,SEEK_CUR);
  fread(&i,4,1,Pal);
  i=ntohl(i);
  fread(type,4,1,Pal);
//  printf("Chunk %c%c%c%c, length %d\n",type[0],type[1],type[2],type[3],i);
 }
 if (!feof(Pal))
  p=ReadPaletteFromFile(Pal,i);
 fclose(Pal);
 return p;

}

  
palette *ReadPaletteFromFile(FILE *Pal, int s)
{
   char buffer[256*3];
   palette *p;
   int i,j;
// printf("Reading a palette of size %d (%d entries)\n",s,s/3);
   p=(palette *)malloc(sizeof(palette));
   fread(buffer, 1, s, Pal);
   p->size=s/3;
   for(i=0,j=0;i<s;i+=3,j++)
    {
     p->data[j].red=buffer[i];
     p->data[j].green=buffer[i+1];
     p->data[j].blue=buffer[i+2];
    }
 return p;
}

int AddEntry(palette *p, unsigned char r, unsigned char g, unsigned char b)
{
 if (p->size==256) return 0;
 p->data[p->size].red=r;
 p->data[p->size].green=g;
 p->data[p->size].blue=b;
 p->size++;
 return 1;
}
int EditEntry(palette *p, int n, unsigned char r, unsigned char g, unsigned char b)
{
 if (n>=p->size) return 0;
 p->data[n].red=r;
 p->data[n].green=g;
 p->data[n].blue=b;
 return 1;
}
int SaveBlorbPalette(palette *p, char *f)
{
 FILE *Pal=fopen(f,"wb");
 char Buffer[256*3];
 int i,j=0;
 if (!Pal) return 0;
 for(i=0;i<p->size;i++)
 {
  Buffer[j++]=p->data[i].red;
  Buffer[j++]=p->data[i].green;
  Buffer[j++]=p->data[i].blue;
 }
 fwrite(Buffer,1,j,Pal);
 fclose(Pal);
 return 1;
}
int MergePalette(palette *dest, palette *src)
{
 int j;
 for(j=0; dest->size<256 && j<src->size;j++)
 {
  int k;
  for (k=0;k<dest->size;k++)
   if (dest->data[k].red==src->data[j].red &&
       dest->data[k].green==src->data[j].green &&
       dest->data[k].blue==src->data[j].blue
      ) break;
  if (k<dest->size) continue;
  dest->data[k]=src->data[j];
  dest->size++;
 }
 return src->size-j;
}
int DeleteEntry(palette *p, int n)
{
 int i;
 if (n>=p->size) return 0;
 for(i=n;i<(p->size-1);i++)
  p->data[i]=p->data[i+1];
 p->size--;
 return 1;
}
int colorcmp(const color *a, const color *b)
{
 if (a->red==b->red)
  if (a->green==b->green)
   if (a->blue==b->blue)
    return 0;
   else return a->blue-b->blue;
  else return a->green-b->green;
 else return a->red-b->red;
}
void SortPalette(palette *p)
{
 qsort(p->data,p->size,sizeof(color),colorcmp);
}

