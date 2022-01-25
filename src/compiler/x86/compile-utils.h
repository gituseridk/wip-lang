#ifndef X86_COMPILE_UTILS_H
#define X86_COMPILE_UTILS_H

#include <stdio.h>

#define L(...) fprintf(out_stream, __VA_ARGS__);\
               fprintf(out_stream, "\n");

#define FORBID_ADDRESS_AS_RESULT if (address) {\
                                   char err[100]; \
                                   sprintf(err, "address as result is not implemented for \"%s\" expression", self->name); \
                                   throwSourceError(err, self->token); \
                                 }

void copyNBytes(char *address_reg, unsigned size, FILE *out_stream);
void addIntToRegX86(char *reg, int value, FILE *out_stream);

#endif
