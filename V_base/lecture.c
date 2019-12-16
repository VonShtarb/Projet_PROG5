#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>

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


Elf64_Ehdr readheader(char* name){
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


Elf64_Shdr load_elf_sec(char *file,int sec){

  Elf64_Ehdr converted_file = readheader(file);
  Elf64_Shdr elf_session;
  FILE *f = fopen(file,"rb");
  if(f) {
    fseek(f, converted_file.e_shoff, SEEK_SET);
    int n = fread(&elf_session, 1, sizeof(elf_session), f);
     for(int i=0; i<sec; i++){
       fseek(f, elf_session.sh_size, SEEK_CUR);
       n = fread(&elf_session, 1, sizeof(elf_session), f);
     }
    printf("%d octets lu\n", n);
    }
  printf("%d\n", elf_session.sh_name);
  return elf_session;
}

int main_section(char* name_file){
  load_elf_sec(name_file,1);
  return 0;
}
int main_readheader(char* name_file ){
    Elf64_Ehdr res;
    res=readheader(name_file);
    print_header(res);
    return 0;
}

Elf64_Shdr read_section_table(char* filename, int offset){
    FILE* file;
    file=fopen(filename, "rb");
    Elf64_Shdr sectionheader;
    if (file){
        int res;
        res=fseek(file, offset, SEEK_SET);
        res=fread(&sectionheader, 1, sizeof(sectionheader), file);
        res++;
    }
    fclose(file);
    return sectionheader; 
}

void get_section_table(char* filename, Elf64_Ehdr header, Elf64_Shdr sectionheaders[]){
    int offset = header.e_shoff;
    int sectionsize = header.e_shentsize;

    for(int i=0; i<header.e_shnum;i++){
        Elf64_Shdr sectionheader = read_section_table(filename, offset);
        sectionheaders[i]=sectionheader;
        offset+=sectionsize;
    }
    return;
}

void print_section_table(Elf64_Shdr sectionheaders[], int size, char* stringtable){
    Elf64_Shdr header;
    char* name;
    printf("No.\ttaille\ttype\t\tpermissions\tdecalage\tnom\n");
    for(int i=0;i<size;i++){
        header = sectionheaders[i];
        printf("[%d]\t", i);    // No. section
		//printf("%s\t", get_name(header.sh_name));   // nom section
        printf("%lx\t", header.sh_size);    // taille section
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
                printf("SHT_REL\t");
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
        printf("%lx\t\t", header.sh_offset); // decalage/debut
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

char * get_string_table(char *filename, int offset){
    FILE* file;
    file=fopen(filename, "rb");

    int res;
    Elf64_Shdr header;
    char * stringtable;

    res = fseek(file, offset, SEEK_SET);
    res = fread(&header, 1, sizeof(header), file);
    stringtable = malloc(header.sh_size);
    res = fseek(file, header.sh_offset, SEEK_SET);
    res = fread(stringtable, 1, header.sh_size, file);

    res+=0;
    fclose(file);
    return stringtable;
}

int main_read_section_table(char* filename){
    Elf64_Ehdr header = readheader(filename);
    int offset = ((header.e_shstrndx*header.e_shentsize)+header.e_shoff);
    char * stringtable = get_string_table(filename, offset);
    Elf64_Shdr sectionheaders[header.e_shnum]; 
    get_section_table(filename, header, sectionheaders);
    print_section_table(sectionheaders, header.e_shnum, stringtable);
    return 0;
}

int main(){
    main_read_section_table("debug.o");
    return 0;
}