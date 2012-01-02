typedef struct {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        } color;
typedef color palette_data[256];
typedef struct {
                 int size;
                 palette_data  data;
               } palette;

palette *ReadBlorbPalette(char *f);
palette *ReadPNGPalette(char *f);
int AddEntry(palette *p, unsigned char r, unsigned char g, unsigned char b);
int EditEntry(palette *p, int n, unsigned char r, unsigned char g, unsigned char b);
int SaveBlorbPalette(palette *p, char *f);
int MergePalette(palette *dest, palette *src);
palette *ReadPaletteFromFile(FILE *Pal, int s);
void SortPalette(palette *p);
