#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

// Affiche le header
void print_header( Elf64_Ehdr elfulu);
// Recupere le header
Elf64_Ehdr load_header(char* name);
// Recupere la table des section
Elf64_Shdr load_elf_sec(FILE *file, int sec, Elf64_Ehdr converted_file )
// Recupere la table des symboles
Elf64_Shdr load_symb(char *file, Elf64_Ehdr header);
int main_section(char* name_file, int nb);
int main_load_header(char* name_file );
