#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

void print_header( Elf64_Ehdr elfulu);

Elf64_Ehdr readheader(FILE* f);
Elf64_Shdr load_elf_sec(char *file,int sec);
int main_readheader(char* name_file );