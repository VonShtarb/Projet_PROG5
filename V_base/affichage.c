
#include "affichage.h"

/****************************PRINTS**********************************/
//1.1
void print_header( Elf32_Ehdr header){ 
    printf("ident:\t%c%c%c\n",header.e_ident[1],header.e_ident[2],header.e_ident[3]);
    printf("ident class:\t");
    switch(header.e_ident[4]){
        case 0:
            printf("0 - Invalid class\n");
            break;
        case 1:
            printf("1 - 32 bits obj\n");
            break;
        case 2:
            printf("2 - 32 bit obj\n");
            break;
        default: 
            printf("\n");
    }
    printf("ident data:\t");
    switch(header.e_ident[EI_DATA]){
        case 0:
            printf("0 - invalid data encoding\n");
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
    printf("ident version:\t%d\n", header.e_ident[EI_VERSION]);
    printf("type:\t");
    switch(header.e_type){
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
    printf("machine:\t%hd\n",header.e_machine);
    printf("version:\t");
    switch(header.e_version){
        case 0:
            printf("0 - Invalid version\n");
            break;
        case 1:
            printf("1 - current version\n");
            break;     
    }
    printf("entry:\t%d\n",header.e_entry);
    printf("phoff:\t%d\n",header.e_phoff);
    printf("shoff:\t%d\n",header.e_shoff);
    printf("flags:\t0x%x\n",header.e_flags);
    printf("ehsize:\t%hd\n",header.e_ehsize);
    printf("phentsize:\t%hd\n",header.e_phentsize);
    printf("phnum:\t%hd\n",header.e_phnum);
    printf("shentsize:\t%hd\n",header.e_shentsize);
    printf("shnum:\t%hd\n",header.e_shnum);
    printf("shstrndx:\t%hd\n",header.e_shstrndx);
}
//1.2
void print_section_table(Elf32_Shdr sectionheaders[], int size, char* stringtable){
    Elf32_Shdr header;
    char* name;
    printf("No.\ttaille\ttype\t\tpermissions\tdecalage\tnom\n");
    for(int i=0;i<size;i++){
        header = sectionheaders[i];
        printf("[%d]\t", i);    // No. section
		//printf("%s\t", get_name(header.sh_name));   // nom section
        printf("%x\t", header.sh_size);    // taille section
        switch(header.sh_type){     // type de section
            case 0:
                printf("SHT_NULL\t");
                break;
            case 1:
                printf("SHT_PROGBITS\t");
                break;
            case 2:
                printf("SHT_SYMTAB\t");
                break;
            case 3:
                printf("SHT_STRTAB\t");
                break;
            case 4:
                printf("SHT_RELA\t");
                break;
            case 5:
                printf("SHT_HASH\t");
                break;
            case 6:
                printf("SHT_DYNAMIC\t");
                break;
            case 7:
                printf("SHT_NOTE\t");
                break;
            case 8:
                printf("SHT_NOBITS\t");
                break;
            case 9:
                printf("SHT_REL\t\t");
                break;
            case 10:
                printf("SHT_SHLIB\t");
                break;
            case 11:
                printf("SHT_DYNSYM\t");
                break;
            case 0x70000000:
                printf("SHT_LOPROC\t");
                break;
            case 0x7fffffff:
                printf("SHT_HIPROC\t");
                break;
            case 0x80000000:
                printf("SHT_LOUSER\t");
                break;
            case 0xffffffff:
                printf("SHT_HIUSER\t");
                break;
            
            default:
                    printf("0x%x\t", header.sh_type);    // taille section

        }
        //printf("%ld\t", header.sh_flags); // informations d'allocation (adresse ?)
        switch(header.sh_flags){
            case 0x0ff00000:
                printf("SHF_MASKOS\t\t");
            case 0xf0000000:
                printf("SHF_MASKPROC\t\t");
            case 0x40000000:
                printf("SHF_ORDERED\t\t");
            case 0x80000000:
                printf("SHF_EXCLUDE\t\t");
            default:
                printf(" ");
                char strflags[50] = "";
                int flags = header.sh_flags;
                if(flags-1024>=0){
                    strcat(strflags, "T");
                    flags = flags - 1024;
                }
                if(flags-512>=0){
                    strcat(strflags,"G");
                    flags = flags - 512;
                }
                if(flags-256>=0){
                    strcat(strflags, "O ");
                    flags = flags - 256;
                }
                if(flags-128>=0){
                    strcat(strflags, "L");
                    flags = flags - 128;
                }
                if(flags-64>=0){
                    strcat(strflags, "I");
                    flags = flags - 64;
                }
                if(flags-32>=0){
                    strcat(strflags, "S");
                    flags = flags - 32;
                }
                if(flags-16>=0){
                    strcat(strflags, "M");
                    flags = flags - 16;
                }
                if(flags-4>=0){
                    strcat(strflags, "X");
                    flags = flags - 4;
                }
                if(flags-2>=0){
                    strcat(strflags, "A");
                    flags = flags - 2;
                }
                if(flags-1>=0){
                    strcat(strflags, "W");
                    flags = flags - 1;
                }
                printf("%s\t\t", strflags);
        }
        printf("%x\t\t", header.sh_offset); // decalage/debut
        name = stringtable + header.sh_name;
        printf("%s\t", name);
        printf("\n");
        
    }
    printf("DETAILS :\n");
    printf("T : SHF_TLS\t\tG : SHF_GROUP\t\tO : SHF_OS_NONCONFORMING\n");
    printf("L : SHF_LINK_ORDER\tI : SHF_INFO_LINK\tS : SHF_STRINGS\n");
    printf("M : SHF_MERGE\t\tX : SHF_EXECINSTR\tA : SHF_ALLOC\n");
    printf("W : SHF_WRITE\n");
}

//1.3
 int print_section(Elf32_Shdr section, FILE *f, char * nameSec) {
  fseek(f, section.sh_offset, SEEK_SET);
  char sectionString[section.sh_size];
  for (int i = 0; i<section.sh_size; i++){
    if(fscanf(f, "%c", &(sectionString[i])) == 0) {
      printf("Erreur lecture fichier");
      return -1;
    }
  }
  printf("\nVidange hexadécimale de la section << %s >> :\n",nameSec+section.sh_name);
    for (int y=0;y<section.sh_size;y+=16){
      //affichage de la ligne d'adresse
    printf("0x%.8x ",section.sh_addr+y);

    //affichage version hexa
    for(int i=0;i<16;i++){
      if(i%4==0)
        printf(" ");
      if(i+y<section.sh_size){
        if(sectionString[i+y]=='\x0'){
          printf("00");
        }
        else if(sectionString[i+y]>>16=='\xff')
          printf("%x",(sectionString[i+y])&(0xff) );
        else
          printf("%x",sectionString[i+y]);
        }
      else
        printf("  ");

   }
     printf("\t");
    //affichage version string
   for(int z=0;z<16;z++){
     if(z+y<section.sh_size){
     if(sectionString[z+y]<32){
       printf(".");
     }
     else
      printf("%c",sectionString[z+y]);
   }
 }
   printf("\n");
  }
  printf("\n");
  return 0;

}
/*
  fseek(f, section.sh_offset, SEEK_SET);
  //fseek(f, section.sh_entsize, SEEK_SET);
  char sectionString[section.sh_size];
  int n;
  if((n = fread(&sectionString, 1, section.sh_size, f)) == 0) {
    return -1;
  }
  for (int i = 0; i<section.sh_size; i++){
    if((n = fscanf(f, "%c", &(sectionString[i])) == 0))
      return -1;
  }

  printf("\nVidange hexadécimale de la section << %s >> :\n",nameSec+section.sh_name);
    for (int y=0;y<section.sh_size;y+=16){
      //affichage de la ligne d'adresse
    printf("0x%.8x ",section.sh_addr+y);

    //affichage version hexa
    for(int i=0;i<16;i++){
      if(i%4==0)
        printf(" ");
      if(i+y<section.sh_size){
        if(sectionString[i+y]=='\x0'){
          printf("00");
        }
        else if(sectionString[i+y]>>16=='\xff')
          printf("%x",(sectionString[i+y])&(0xff) );
        else
          printf("%x",sectionString[i+y]);
        }
      else
        printf("  ");

   }
     printf("    ");
    //affichage version string
   for(int z=0;z<16;z++){
      printf("%c",sectionString[z+y]);
   }
   printf("\n");
  }
  printf("\n");
  return 0;

}*/

//1.4
void print_tablesymbol(liste_elf32_sym listesymb,char* stringtable){
    Elf32_Sym symbol;
    char* name;
    int error;
        printf("number\t");
        printf("name\t");
        printf("value\t");
        printf("size\t");
        printf("lien\t");
        printf("shndx\t");
        printf("type\t");
        printf("\n");
    for (int i =0; i<taille((listesymb)); i++){
               
        error=get_symbol(listesymb, i, &(symbol));
        if(error==0){
            printf("%d\t", i);
            name = stringtable + (symbol.st_name );
            printf("%s\t",name);
            printf("0x%x\t",symbol.st_value);
            printf("%d\t",symbol.st_size);

            //Vis
             switch(ELF32_ST_BIND(symbol.st_info)){
                case 0:
                    printf("local\t");
                    break;
                case 1:
                    printf("global\t");
                    break;
                case 2:
                    printf("weak\t");
                    break;
                case 13:
                    printf("loproc\t");
                    break;
                case 15:
                    printf("hiproc\t");
                    break;
                default:
                    printf("%d\t", ELF32_ST_BIND(symbol.st_info));
                    break;
            }
            //printf("\tshndx:\t");
            switch(symbol.st_shndx){
                case 0:
                    printf("undef\t");
                    break;
                case 0xff00:
                    printf("loreserve or loproc\t");
                    break;
                case 0xff1f:
                    printf("hiproc\t");
                    break;
                case 0xfff1:
                    printf("abs\t");
                    break;
                case 0xfff2:
                    printf("commun\t");
                    break;
                case 0xffff:
                    printf("hireserve\t");
                    break;
                default:
                    printf("%d\t", symbol.st_shndx);
                    break;
            }
            
            //printf("\tinfo:\t");
            switch(ELF32_ST_TYPE(symbol.st_info)){
                case 0:
                    printf("notype\t");
                    break;
                case 1:
                    printf("object\t");
                    break;
                case 2:
                    printf("func\t");
                    break;
                case 3:
                    printf("section\t");
                    break;
                case 4:
                    printf("file\t");
                    break;
                case 13:
                    printf("loproc\t");
                    break;
                case 15:
                    printf("hiproc\t");
                    break;
                default:
                    printf("%d\t", ELF32_ST_TYPE(symbol.st_info));
                    break;
            }
            printf("\n");
        }else{
            printf("Erreor on symbol table");
        }
    }

}
