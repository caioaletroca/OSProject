#define low16(address) (unsigned short)((address) & 0xFFFF)
#define high16(address) (unsigned short)(((address) >> 16) & 0xFFFF)

void memcpy(char *source, char *dest, int nbytes);