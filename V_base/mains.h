#ifndef _MAINS_H_

#define _MAINS_H_

#include "type_liste_symb.h"
//1.1
int main_load_header(char* name_file );
//1.2
int main_read_section_table(char* name_file);
//1.3
int main_section(char* name_file, char* val);
//1.4
int main_table_symbole(char* name_file);

#endif