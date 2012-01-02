/* Blorb Merge
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "short.h"
char Merge_Mode=0;
/* The version and boilerplate messages.  The string is formatted
/* with the assumption  that it will be printed with the program name,
/* compile date, and version string
*/
#define VERSION ".1b"
#define BOILER "%s: Blorb Merge (%s)\nVersion %s by L. Ross Raszewski\n"
// Maximum number of chunks we'll allow
// The program name.  DJGPP munges this, so we rebuild it here
char *MyName;

void write_int(FILE *f, unsigned int v)
// Write_int writes an integer to a file in blorb format 
{
  unsigned char v1=v&0xFF,
    v2=(v>>8)&0xFF,
    v3=(v>>16)&0xFF,
    v4=(v>>24)&0xFF;
  
  fwrite(&v4,1,1,f);
  fwrite(&v3,1,1,f);
  fwrite(&v2,1,1,f);
  fwrite(&v1,1,1,f);
}

unsigned int read_int(unsigned char *from)
{
 unsigned int l;
 
 l = ((unsigned int) from[0]) << 24;
 l |= ((unsigned int) from[1]) << 16;
 l |= ((unsigned int) from[2]) << 8;
 l |= ((unsigned int) from[3]);
 return l;
}
unsigned int ReadChunk(FILE *from, void **to)
// ReadChunk reads one entry from a blorb and loads a chunk from it
{
 unsigned int l;
 unsigned char v[4];
 unsigned long pp;
 pp=ftell(from);
 fseek(from,4,SEEK_CUR);
 fread(v,4,1,from);
 l=read_int(v);
 fseek(from,pp,SEEK_SET);
 l+=8;
 if (l%2) l++;
 *to=malloc(l);
 fread(*to,l,1,from);
 return l;
}

/*
  1. Read both RIdx chunks
  2. Compose new RIdx
  3. For each chunk in the new RIdx, write it to the chunk file.
  4. Scan both files to build 'other chunks' index
  5. For each other chunk, if it is in the other chunks index, add it to
     the chunk file.
  6. Write the IFRS and RIdx to the outfile
  7. Copy the chunk file into the outfile
*/

typedef struct {
  char use[4];
  char res[4];
  unsigned int offset;
  FILE *f;
} RIdx;
typedef struct idx_t
 {
  char type[4];
  int len;
  void *data;
  char deleted;
  struct idx_t *next;
 } INdx;


INdx *buildINdx(FILE *from, RIdx *idx, int n)
{
 char type[4];
 char buf[4];
 int pos, skip, len, i;
 INdx *head=NULL;
 fseek(from,24+(12*n),SEEK_SET);
 while(!feof(from) && !ferror(from))
 {
 skip=0;
 pos=ftell(from);
 if (feof(from)) break;
 for(i=0;i<n;i++) if (pos==idx[i].offset) skip=1;
 fread(type,1,4,from);
 if (feof(from)) break;
 if (skip==0)
  {
   INdx *t=(INdx *) malloc(sizeof(INdx));
   
   t->next=head;
   head=t;
   fseek(from,pos,SEEK_SET);
   t->len=ReadChunk(from,&(t->data));
   t->deleted=0;
   memcpy(t->type,type,4); 
  }
  else
  {
   fread(buf,1,4,from);
   len=read_int(buf);
   if (len %2) len++;
   fseek(from,len,SEEK_CUR);
  }
 }
 rewind(from);
 return head;
}

INdx *mergeINdx(INdx *i1, INdx *i2)
{
 INdx *p=i1;
 INdx *pp;
 while(p->next) p=p->next;
 p->next=i2;
 p=i1;
 while(p)
 {
  for(pp=p->next;pp&&(p->deleted==0);pp=pp->next)
   if (pp->deleted==0 && memcmp(p->type,pp->type,4)==0)
   {
    char c=0;
    if (Merge_Mode==0)
    {
     char buf[256];
     char buf2[256];
     if (p->len<(256+8)) {
                          memcpy(buf,p->data+8,p->len-8);
                          buf[p->len-8]=0;
                         }
     else {
                          memcpy(buf,p->data+8,255);
                          buf[255]=0;
                          }
     if (pp->len<(256+8)) {
                          memcpy(buf2,pp->data+8,pp->len-8);
                          buf2[pp->len-8]=0;
                         }
     else {
                          memcpy(buf2,pp->data+8,255);
                          buf2[255]=0;
     }
     printf("Duplicate chunk found. Type: %c%c%c%c.\n"
            "Contents (1): %s\n"
            "Contents (2): %s\n"
            "Which would you like to use? [1/2] ",
            p->type[0],
            p->type[1],
            p->type[2],
            p->type[3],
            buf, buf2
            );
     while(c!='1' && c!='2') c=getc(stdin);
    }
    if (Merge_Mode==1 || c=='1')
     pp->deleted=0;
    else if (Merge_Mode==-1 || c=='2')
     p->deleted=1;
    }
    p=p->next;
   }
 
 p=i1;
 while(p && p->deleted) p=p->next;
 for(pp=i1;pp!=p;pp=i2)
 { i2=pp->next;
   free(pp->data);
   free(pp);
 }
 if (p) pp=p->next;
 i2=p;
 while(pp)
 {
  if (pp->deleted)
  {
   i2->next=pp->next;
   free(pp->data);
   free(pp);
   pp=i2->next;
  }
  else
  {
   i2=pp;
   pp=pp->next;
  }
 }
 return p;
}


int ReadRIdx(FILE *from, RIdx **arr)
{
 void *chnk;
 RIdx *indx;
 int i,n,l;
 fseek(from,12,SEEK_SET);
 i=ReadChunk(from,&chnk);
 if (memcmp(chnk,"RIdx",4)) { printf("Error: RIdx chunk not found!\n"); exit(1); }
 n=read_int(chnk+8);
 indx=(RIdx *)malloc(sizeof(RIdx)*n);
 for(i=0,l=12;i<n;i++,l+=12)
 {
  unsigned char buf[4];
  memcpy(indx[i].use,chnk+l,4);
  memcpy(indx[i].res,chnk+l+4,4);
  memcpy(buf,chnk+l+8,4);
  indx[i].offset=read_int(buf);
  indx[i].f=from;
 }
 *arr=indx;
 free(chnk);
 return n;
}

int BuildRIdx(FILE *f1, FILE *f2, RIdx **out, INdx **idx)
{
 RIdx *i1;
 RIdx *i2;
 RIdx *indx;
 char *mask1;
 char *mask2;
 int l1, l2, l, i,j;
 INdx *a,*b;
 printf("Reading the first RIdx chunk...\n");
 l1=ReadRIdx(f1,&i1);
 printf("Reading the second RIdx chunk...\n");
 l2=ReadRIdx(f2,&i2);
 printf("Indexing other chunks in the first file...\n");
 a=buildINdx(f1,i1,l1);
 printf("Indexing other chunks in the second file...\n");
 b=buildINdx(f2,i2,l2);
 printf("Merging the index of other chunks...\n");
 *idx=mergeINdx(a,b);
 mask1=(char *)malloc(l1);
 mask2=(char *)malloc(l2);
 printf("Merging the RIdx chunks...\n");
 for(i=0;i<l2;i++) mask2[i]=1;
  for(i=0;i<l1;i++) mask1[i]=1;
 l=0;
 for(i=0;i<l1;i++)
 {
  for(j=0;j<l2;j++)
  if (memcmp(i1[i].res,i2[j].res,4)==0 && memcmp(i1[i].use,i2[j].use,4)==0)
  {
   char c=0;
   if (Merge_Mode==0)
   {
    printf("Duplicate resource found. Type: %c%c%c%c. Number: %d.\n"
           "Which would you like to use? (1=first file, 2=second file) ",
           i1[i].use[0],
           i1[i].use[1],
           i1[i].use[2],
           i1[i].use[3],
           read_int(i1[i].res));
   while(c!='1' && c!='2') c=getc(stdin);
   }
   if (Merge_Mode==1 || c=='1')
    mask2[j]=0;
   else if (Merge_Mode==-1 || c=='2')
    mask1[1]=0;
   }
  if (mask1[i]) l++;
  }
  for(i=0;i<l2;i++) if (mask2[i]) l++;
  indx=(RIdx *)malloc(sizeof(RIdx)*l);
 
  for(j=0,i=0;i<l1;i++)
   if (mask1[i]) indx[j++]=i1[i];
  for(i=0;i<l2;i++)
   if (mask2[i]) indx[j++]=i2[i];
  *out=indx;
  free(mask1);
  free(mask2);
  free(i1);
  free(i2);
  return j;
}

void writeResources(RIdx *indx, int n, FILE *out)
{
 int i;
 void *chunk;
 int l;
 fseek(out,24+(12*n),SEEK_SET);
 for(i=0;i<n;i++)
 {
  fseek(indx[i].f,indx[i].offset,SEEK_SET);
  l=ReadChunk(indx[i].f,&chunk);
  indx[i].offset=ftell(out);
  fwrite(chunk,1,l,out);
  free(chunk);
 }
}
void writeRIdx(FILE *out, RIdx *indx, int n)
{
  int i;
  fseek(out,12,SEEK_SET);
  fwrite("RIdx",1,4,out);
  write_int(out,4+(12*n));
  write_int(out,n);
  for(i=0;i<n;i++)
  {
   fwrite(indx[i].use,1,4,out);
   fwrite(indx[i].res,1,4,out);
   write_int(out,indx[i].offset);
  }
}
void mergeFiles(FILE *f1, FILE *f2, FILE *out)
{
 RIdx *ridx;
 INdx *indx;
 int n;

 n=BuildRIdx(f1,f2,&ridx,&indx);
printf("Writing the resource chunks...\n");
 writeResources(ridx,n,out);
printf("Writing the RIdx chunk...\n");
 writeRIdx(out,ridx,n);
 fseek(out,0,SEEK_END);
printf("Writing the other chunks...\n");
 while(indx)
 {
  INdx *ii=indx;
  fwrite(indx->data,indx->len,1,out);
  free(indx->data);
  indx=indx->next;
  free(ii);
 }
 n=ftell(out);
 fseek(out,0,SEEK_SET);
 fwrite("FORM",1,4,out);
 write_int(out, n-8);
 fwrite("IFRS",1,4,out);
}

main(int argc, char **argv)
{
 FILE *f1, *f2, *f3;
 int a=0;
  MyName=ShortProgramName(argv[0]);
 printf(BOILER,MyName,__DATE__,VERSION);
 if (argc < 4) { printf("Usage is %s [-1/2] infile1 infile2 outfile\n",MyName); exit(1); }
 if (argv[1][0]=='-' && argv[1][1]=='1')
 { a=1; Merge_Mode=1; } 
 else if (argv[1][0]=='-' && argv[1][1]=='2')
 { a=1; Merge_Mode=-1; } 
 f1=fopen(argv[1+a],"rb");
 f2=fopen(argv[2+a],"rb");
 f3=fopen(argv[3+a],"wb");
 mergeFiles(f1,f2,f3);
}





