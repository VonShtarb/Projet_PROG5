#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

void print_header( Elf64_Ehdr elfulu);

Elf64_Ehdr readheader(char* name_file);
Elf64_Shdr load_elf_sec(FILE *file,int sec,  Elf64_Ehdr converted_file );
int main_readheader(char* name_file );
