#ifndef _FUSION_H_

#define _FUSION_H_
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "lecture.h"
#include "gestion_endian.h"

/*
return max value between i1 and i2
*/
int max(int i1, int i2);
/*
return -1 if the section name doesn't exist in the elf file name_file
else return the index of name in name_file
*/
int search_same_name(char * name, char * name_file);
/*
hey! got any grapes?
*/
int main(int argc, char *argv[]);
/*
merge two files(s1 and s2) sections into res
return a new offset
*/
int cont_sect(FILE* res, char* s1, char* s2, int v1, int v2, int offset, Elf32_Shdr sectheader1[], Elf32_Shdr sectheader2[], Elf32_Ehdr header);
/*
update offset to section name in header
*/
void change_indstringtable(char* name_file ,Elf32_Ehdr header, Elf32_Shdr sectheader1[],  int v1);
/*
  Add a section in res
*/
int put_sect(FILE* res, char* source, int offset, Elf32_Shdr sectheader[], Elf32_Ehdr header, int v);
/*
Update the header in res
*/
void write_new_header(FILE* res, Elf32_Ehdr new_header);
/*
I'm calling out from Scatland
I'm calling out from Scatman's world
If you wanna break free you better listen to me
You got to learn how to see in your fantasy
*/
int main_fus(int argc, char *argv[]);

#endif
