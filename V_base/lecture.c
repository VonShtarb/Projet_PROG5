#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "lecture.h"
#include "gestion_endian.h"

/************************* LOAD**********************/
//Partie 1.1
Elf32_Ehdr load_header(char* name){
    FILE* f;    
    Elf32_Ehdr header;
    f=fopen(name, "rb");
    if (f== NULL){
        printf("Erreur ouverture fichier\n");
        exit(0);
    }
    size_t res;
    res=fread(&header, 1, sizeof(header), f);
    fclose(f);
    if (res==0){}
    return header;
}

//Partie 1.2
Elf32_Shdr load_section(char* filename, int offset){
    FILE* file;
    file=fopen(filename, "rb");
    Elf32_Shdr sectionheader;
    if (file){
        int res;
        res=fseek(file, offset, SEEK_SET);
        res=fread(&sectionheader, 1, sizeof(sectionheader), file);
        res++;
    }
    fclose(file);
    return sectionheader; 
}
//Partie 1.2
void load_tablesection(char* filename, Elf32_Ehdr header, Elf32_Shdr sectionheaders[] ){
    int offset = header.e_shoff;
    int sectionsize = header.e_shentsize;
    for(int i=0; i<header.e_shnum;i++){
        Elf32_Shdr sectionheader = load_section(filename, offset);
        sectionheaders[i]=sectionheader;
        offset+=sectionsize;
    }
    return;
}
// Partie 1.2
char * load_stringtable(char *name_file, int offset){

    FILE* file = fopen(name_file,"rb");
    int res;
    Elf32_Shdr header;
    header  = load_section(name_file,offset);
    swap_header_section(&header);
    char * stringtable;
    stringtable = malloc(header.sh_size);
    res = fseek(file, header.sh_offset, SEEK_SET);
    res = fread(stringtable, 1, header.sh_size, file);
    res+=0;
    fclose(file);
    return stringtable;
}

//1.3
int load_section_header(FILE *f, Elf32_Shdr section, char *sectionHeader) {
  fseek(f, section.sh_offset, SEEK_SET);
  int n;
  n = fread(sectionHeader, 1, section.sh_entsize, f);
  if(n == 0) {
    return -1;
  }
  return 0;
}

//Partie 1.4
Elf32_Sym load_symb(char* filename, int offset){
    Elf32_Sym symb; 
    FILE* file; 
    file=fopen(filename, "rb");
    if (file){ 
        int res; 
        res=fseek(file, offset, SEEK_SET);
        res=fread(&symb, 1, sizeof(symb), file);
        res++;
    }
    fclose(file);
    return symb;
}
//Partie 1.4
void load_tablesymbole(char* file,Elf32_Ehdr header, Elf32_Shdr section[], liste_elf32_sym* list_symb){
    int errore=-1;
    int offs;
    Elf32_Sym symbole;
    for (int i=0; i<header.e_shnum; i++){
        if (section[i].sh_type==2){
            offs = section[i].sh_offset;
            while (offs <section[i].sh_offset+ section[i].sh_size){
                symbole=load_symb(file, offs); 
                offs = sizeof(symbole) + offs;
                errore=ajouter(list_symb, symbole);  
                if(errore){}
            }
        }
    }
}