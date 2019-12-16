#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

void print_header( Elf64_Ehdr elfulu);

Elf64_Ehdr readheader(FILE* f);
Elf64_Shdr load_elf_sec(char *file,int sec);
int main_readheader(char* name_file );
void getheaders(char* filename, Elf64_Ehdr header, Elf64_Shdr sectionheader[]);
Elf64_Shdr read_section_table(char* filename, int offset);
void get_section_table(char* filename, Elf64_Ehdr header, Elf64_Shdr sectionheaders[]);
void print_section_table(Elf64_Shdr sectionheaders[], int size);
int main_read_section_table(char* filename);
