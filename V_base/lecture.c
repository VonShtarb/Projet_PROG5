#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

void print_header( Elf64_Ehdr elfulu){

    printf("ident:\t%c%c%c\n",elfulu.e_ident[1],elfulu.e_ident[2],elfulu.e_ident[3]);
    printf("ident class:\t");
    switch(elfulu.e_ident[4]){
        case 0:
            printf("0 - Invalid class\n");
            break;
        case 1:
            printf("1 - 32 bits obj\n");
            break;
        case 2:
            printf("2 - 64 bit obj\n");
            break;
        default:
            printf("\n");
    }
    printf("ident data:\t");
    switch(elfulu.e_ident[EI_DATA]){
        case 0:
            printf("0 - nvalid data encoding\n");
            break;
        case 1:
            printf("1 - Little endian (ex:FE CA)\n");
            break;
        case 2:
            printf("2 - Big endian (ex:CA FE)\n");
            break;
        default:
            printf("\n");
    }
    printf("ident version:\t%d\n", elfulu.e_ident[EI_VERSION]);
    printf("type:\t");
    switch(elfulu.e_type){
        case 0:
            printf("0 - No file type\n");
            break;
        case 1:
            printf("1 - Relocated file\n");
            break;
        case 2:
            printf("2 - Executable file\n");
            break;
        case 3:
            printf("3 - Shared object file\n");
            break;
        case 4:
            printf("4 - Core file\n");
            break;
        case 0xff00:
            printf("0xff00 - Processor specific\n");
            break;
        case 0xffff:
            printf("0xffff - Processor specific\n");
            break;
    }
    printf("machine:\t%hd\n",elfulu.e_machine);
    printf("version:\t");
    switch(elfulu.e_version){
        case 0:
            printf("0 - Invalid version\n");
            break;
        case 1:
            printf("1 - current version\n");
            break;
    }
    printf("entry:\t%ld\n",elfulu.e_entry);
    printf("phoff:\t%ld\n",elfulu.e_phoff);
    printf("shoff:\t%ld\n",elfulu.e_shoff);
    printf("flags:\t%hd\n",elfulu.e_flags);
    printf("ehsize:\t%hd\n",elfulu.e_ehsize);
    printf("phentsize:\t%hd\n",elfulu.e_phentsize);
    printf("phnum:\t%hd\n",elfulu.e_phnum);
    printf("shentsize:\t%hd\n",elfulu.e_shentsize);
    printf("shnum:\t%hd\n",elfulu.e_shnum);
    printf("shstrndx:\t%hd\n",elfulu.e_shstrndx);
}


Elf64_Ehdr load_header(char* name){
    FILE* f;
    Elf64_Ehdr header;
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

liste_elf64_sym load_symb(char *file, Elf64_Ehdr header, tableausection){
    int error;
    //creation liste symb
    liste_elf64_sym liste_symb;
    creer_liste(&liste_symb, header->e_shnum);
    // Pour chaque section s
    for (int i=0; i< header->e_shnum){
        // Si s.type = symb
        if (sections[i].sh_type == SHT_SYMTAB){
            // ajout dans liste
            int ajouter(&liste_symb,sections[i]);
        }
    }
    //retourn liste
    return liste_symb;
}

Elf64_Shdr load_elf_sec(FILE *file, int sec, Elf64_Ehdr converted_file ){
  Elf64_Shdr elf_session;
  if(file) {
    fseek(file, converted_file.e_shoff, SEEK_SET);
    int n = fread(&elf_session, 1, sizeof(elf_session), file);
     for(int i=0; i<sec; i++){
       n = fread(&elf_session, 1, sizeof(elf_session), file);
     }
    printf("%d octets lu\n", n);
    }
  return elf_session;
}

int main_section(char* name_file, int nb){
  load_elf_sec(name_file,nb);
  return 0;
}
int main_load_header(char* name_file ){

    Elf64_Ehdr res;
    res=load_header(name_file);
    print_header(res);
    return 0;
}
