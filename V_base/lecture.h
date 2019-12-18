#ifndef _LECTURE_H_

#define _LECTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "type_liste_symb.h"

// Recupere le header
Elf32_Ehdr load_header(char* name);
// Recupere la table des symboles
Elf32_Sym load_symb(char* filename, int offset);
//Partie 1.4
void load_tablesymbole(char* file,Elf32_Ehdr header, Elf32_Shdr section[], liste_elf32_sym* list_symb);
// Recupere une section
Elf32_Shdr load_section(char* filename, int offset);
// Recupere la table des sections
void load_tablesection(char* filename, Elf32_Ehdr header, Elf32_Shdr sectionheaders[]);
// Recupere la table de String
char* load_stringtable(char* name_file,int offset);
#endif