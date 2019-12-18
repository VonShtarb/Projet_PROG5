#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "mains.h"
#include "lecture.h"
#include "affichage.h"
#include "gestion_endian.h"

// Cas -A
//1.1
int main_load_header(char* name_file ){
    Elf32_Ehdr res, res_b;
    res=load_header(name_file);
    res_b = res;
    //passsage big -> little
    swap_header(&res_b);
    print_header(res_b);
    return 0;
}
// Cas -B
//1.2
int main_read_section_table(char* name_file){
    Elf32_Ehdr header = load_header(name_file);
    swap_header(&header);
    int offset = ((header.e_shstrndx*header.e_shentsize)+header.e_shoff);
    char * stringtable = load_stringtable(name_file, offset);
    Elf32_Shdr sectionheaders[header.e_shnum]; 
    load_tablesection(name_file, header, sectionheaders);
    for (int k = 0; k<header.e_shnum;k++){
        swap_header_section(&(sectionheaders[k]));
    }
    print_section_table(sectionheaders, header.e_shnum, stringtable);
    return 0;
}
//Cas -C
//1.3
int main_section(char* name_file, char* val){
  FILE *f;
  f= fopen(name_file,"rb");
  if( f == NULL){
    printf("erreur, le premier argument n'est pas un fichier\n");
    return -1;
    }
  if(val == NULL){
    printf("erreur, il manque le deuxieme argument\n");
    return -2;
    }
  int index,n;
  Elf32_Ehdr header = load_header(name_file);
  swap_header(&header);
  Elf32_Shdr elf_sections[header.e_shnum];
  load_tablesection(name_file,header,elf_sections);
  for (int k = 0; k<header.e_shnum;k++){
  	swap_header_section(&(elf_sections[k]));
  }
  int offset = ((header.e_shstrndx*header.e_shentsize)+header.e_shoff);
  char * nameSec = load_stringtable(name_file,offset);
  

  if(sscanf(val, "%d", &index)==1){
    if(index<=header.e_shnum && index>=0){
       n = print_section(elf_sections[index], f, nameSec);
       if(n == -1){
          printf("erreur, le premier argument n'est pas un fichier\n");
          return -1;
      }
     }
     else{
      printf("erreur, section non trouvée\n");
	  return -3;
	}
  }
  else{
    int i = 0;
    int test =-1;
    char * name;
    while(test!=0 && i<header.e_shnum){
       name = nameSec+elf_sections[i].sh_name;
      if(strcmp(val,name)==0){
        test=0;index=i;
      }
      i++;
    }
      if(test==0){
        n = print_section(elf_sections[index], f, nameSec);
        if(n){}
      }
    else {
      printf("erreur, section non trouvée\n");
      return -3;  
    }
  }


fclose(f);
  return 0;
}
//Cas -D
//1.4
int main_table_symbole(char* name_file){
    Elf32_Ehdr header = load_header(name_file);
    swap_header(&header);
    int offset = (((header.e_shnum - 1)*header.e_shentsize)+header.e_shoff);
    char * stringtable = load_stringtable(name_file, offset);
    //creation liste symb
    liste_elf32_sym liste_symb;
    creer_liste(&(liste_symb), 5);
    Elf32_Shdr sectionheaders[header.e_shnum]; 
    load_tablesection(name_file, header, sectionheaders);
        for (int k = 0; k<header.e_shnum;k++){
        swap_header_section(&(sectionheaders[k]));
    }
    load_tablesymbole(name_file,header, sectionheaders, &liste_symb);

    for (int k = 0; k<liste_symb.n;k++){
        swap_header_symb(&(liste_symb.tab[k]));
    }

    print_tablesymbol(liste_symb,stringtable);
    return 0;
}
