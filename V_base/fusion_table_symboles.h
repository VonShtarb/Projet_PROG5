#ifndef _FUSION_TABLE_SYMB_H_

#define _FUSION_TABLE_SYMB_H_

/*
Load a symbol table of an elf file
*/
Elf32_Shdr load_table_sym(char * file_name);
/*
return :
  0 if the symbol is define in table_symb
  1 if the symbol is present but not define
  -1 if the symbol doesn't exist
*/
int is_define_in_table(char * name_symb, Elf32_Shdr table_symb);
/*
return a new symbol table with all symbols of table_symb1 and table_symb2
*/
Elf32_Shdr fusion_table_symb(Elf32_Shdr table_symb1, Elf32_Shdr table_symb2);
/*
add a new entrie in file's strings table according to the offset
and return a new offset for a next entrie
*/
int write_in_string_table(File * file, char * nom, int offset);
