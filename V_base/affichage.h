#ifndef _AFFICHAGE_H_

#define _AFFICHAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "type_liste_symb.h"
#include "lecture.h"

void print_header( Elf32_Ehdr header);
void print_section_table(Elf32_Shdr sectionheaders[], int size, char* stringtable);
int print_section(Elf32_Shdr section, FILE *f, char * nameSec);
void print_tablesymbol(liste_elf32_sym listesymb,char* stringtable);

#endif
