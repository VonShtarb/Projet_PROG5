#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

Elf64_Ehdr load_elf(char *file){

  Elf64_Ehdr converted_file;
  FILE *f = fopen(file,"rb");
  if(f) {
    int n = fread(&converted_file, 1, sizeof(converted_file), f);
    printf("%d octets lu\n", n);
    }
  printf("%x,%x,%x,%x\n",converted_file.e_ident[0],converted_file.e_ident[1],converted_file.e_ident[2],converted_file.e_ident[3]);
  fclose(f);
  return converted_file;

  }

Elf64_Shdr load_elf_sec(char *file,int sec){

  Elf64_Ehdr converted_file = load_elf(file);
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

int main(){
  char * fic = "ARM_runner_example";
  load_elf_sec(fic,1);
  return 0;
}
