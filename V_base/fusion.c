#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "lecture.h"
#include "gestion_endian.h"

// retourne l'index de la section name ou -1 si elle n'existe pas
int search_same_name(char * name, char * name_file){
    Elf32_Ehdr header = load_header(name_file);
    swap_header(&header);
      Elf32_Shdr elf_sections[header.e_shnum];
    load_tablesection(name_file,header,elf_sections);
    for (int k = 0; k<header.e_shnum;k++){
        swap_header_section(&(elf_sections[k]));
    }
    int offset = ((header.e_shstrndx*header.e_shentsize)+header.e_shoff);
      char * nameSec = load_stringtable(name_file,offset);

    int index, i = 0;
    int test =-1;
    char * nameTemp;
    while(test!=0 && i<header.e_shnum){
        nameTemp = nameSec+elf_sections[i].sh_name;
        if(strcmp(name,nameTemp)==0){
            test=0;index=i;
        }
        i++;
        }
    if(test==0){
        return index;
    }
    else{
        return -1;
    }
}

//code de test
int main(int argc, char *argv[]){
  int n = search_same_name(".debug_line","./Examples_loader/example1.o");
  printf("index : %d\n", n);
  return 0;
}