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
int main_readheader(char* name_file );
void getheaders(char* filename, Elf64_Ehdr header, Elf64_Shdr sectionheader[]);
//Lecture d'un unique header de section
Elf64_Shdr read_section_table(char* filename, int offset);
//remplis un tableau avec la table des headers de sections
void get_section_table(char* filename, Elf64_Ehdr header, Elf64_Shdr sectionheaders[]);
//Fonction d'affichage de la table des headers de sections
void print_section_table(Elf64_Shdr sectionheaders[], int size);
int main_read_section_table(char* filename);
