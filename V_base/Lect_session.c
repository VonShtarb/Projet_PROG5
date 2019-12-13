#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <lecture.h>
#include <string.h>

Elf64_Ehdr load_elf(FILE *f){

  Elf64_Ehdr converted_file;;
  if(f) {
    int n = fread(&converted_file, 1, sizeof(converted_file), f);
    printf("%d octets lu\n", n);
    }
  printf("%x,%x,%x,%x\n",converted_file.e_ident[0],converted_file.e_ident[1],converted_file.e_ident[2],converted_file.e_ident[3]);
  return converted_file;

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

int getSectionHeader(FILE *f, Elf64_Shdr section, char *sectionHeader) {
  fseek(f, section.sh_offset, SEEK_SET);
  int n;
  n = fread(sectionHeader, 1, section.sh_entsize, f);
  if(n == 0) {
    return -1;
  }
  return 0;
}

int printSection(Elf64_Shdr section, FILE *f, Elf64_Half headSize) {
// aler voir dans la string table
  char sectionHeader[section.sh_entsize];
  getSectionHeader(f, section, sectionHeader);
  //fseek(f, section.sh_offset, SEEK_SET);
  int len = strlen(sectionHeader);
  //char hexSH[100];
  // for (int i = 0, j = 0; i < len; ++i, j += 2){
  //   sprintf(hexSH + j, "%02x", sectionHeader[i] & 0xff);
  //   if (i%2==0){
  //     sprintf(hexSH +j, "%s", " ");
  //     j+=2;
  //   }
  // }
  // printf("%s, %s\n", hexSH, sectionHeader);

  char sectionString[section.sh_size];
  int n;
  if((n = fread(&sectionString, 1, section.sh_size, f)) == 0) {
    return -1;
  }
  len = strlen(sectionString);
  char hexSS[100];
  for (int i = 0, j = 0; i < len; ++i, j += 2){
    sprintf(hexSS + j, "%02x", sectionString[i] & 0xff);
    }
  printf("%s, %s", hexSS, sectionString);
  return 0;

}

int main(){
  char * fic = "./ARM_runner_example";
  FILE *f = fopen(fic,"rb");
  Elf64_Ehdr header = load_elf(f);
  Elf64_Shdr elf_session = load_elf_sec(f,1,header);
  int n = printSection(elf_session, f, header.e_shentsize);
  printf("%d", n);
  fclose(f);
  return 0;
}
