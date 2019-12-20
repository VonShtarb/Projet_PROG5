#include "fusion_table_symboles.h"

/*
return :
  the index if the symbol is define in table_symb
  -1 if the symbol doesn't exist
*/
int is_define_in_table(char * name_symb, liste_elf32_sym table_symb, char * stringtable){
  Elf32_Sym symbcurr;
  for(int i=0;i<sizeof(table_symb)/sizeof(Elf32_Sym);i++){
    get_symbol(table_symb, i, &symbcurr);
    char * symbname = stringtable + symbcurr.st_name;
    if(strcmp(symbname, name_symb)==0){
      return i;
    }
  }
  return -1;
}

/*
add a new entrie in file's strings table according to the offset
and return the stringtable with new string added
*/
char * write_in_string_table(char * file, char * nom) {
  Elf32_Ehdr header = load_header(file);
  int offset = ((header.e_shnum*header.e_shentsize)+header.e_shoff);
  char * stringtable = load_stringtable(file, offset);
  strcat(stringtable, nom);
  return stringtable;
}

//code de test
int main(int argc, char *argv[]){
//load symbols tables
  char * file1 = "./Examples_loader/example1.o";
  char * file2 = "./Examples_loader/example2.o";
  Elf32_Ehdr header1 = load_header(file1);
  Elf32_Ehdr header2 = load_header(file2);
  Elf32_Shdr sections1[header1.e_shnum], sections2[header2.e_shnum];
  Elf32_Shdr newSectionTable[256];
  liste_elf32_sym * list_symb1, * list_symb2;
  load_tablesection(file1, header1, sections1);
  load_tablesection(file2, header2, sections2);
  load_tablesymbole(file1, header1, sections1, list_symb1);
  load_tablesymbole(file2, header2, sections2, list_symb2);
  int offset1 = ((header1.e_shnum*header1.e_shentsize)+header1.e_shoff);
  int offset2 = ((  header2.e_shnum*header2.e_shentsize)+header2.e_shoff);
  char * stringtable1 = load_stringtable(file1, offset1);
  char * stringtable2 = load_stringtable(file2, offset2);
  char * stringtable3;
  //Boolean table for test
  int traiter[sizeof(list_symb2)/sizeof(Elf32_Sym)];
  for (int i=0; i < sizeof(list_symb2)/sizeof(Elf32_Sym);i++){
    traiter[i]=0;
  }
  //travel into the fabulous world of table symb 1
  for (int i=0; i < sizeof(list_symb1)/sizeof(Elf32_Sym);i++){
    Elf32_Sym symb1;
    get_symbol(*list_symb1, i, &symb1);
    char * symbname = stringtable1 + symb1.st_name;
    int indexTab2 = is_define_in_table(symbname, *list_symb2, stringtable2);
    switch(indexTab2){

      case -1:
        //nv entrée
        newSectionTable[i] = sections1[i];
        //ecrire table chaine
        write_in_string_table(stringtable3, symbname);
        //maj tab
        traiter[indexTab2]=1;
        break;

      // define in 1 and 2
      case 0:
        //Erreur
        printf("you fool");
        return EXIT_FAILURE;

      //symb not present in 2
      default:
      //nv entrée
      newSectionTable[i] = sections1[i];
      //ecrire table chaine
      write_in_string_table(stringtable3, symbname);
      break;

    }
  }
  //travel into the fabulous world of table symb 2
  for(int i = 0; i<sizeof(list_symb2)/sizeof(Elf32_Sym) ; i++) {
    if(traiter[i] == 0) {
      Elf32_Sym symb2;
      get_symbol(*list_symb2, i, &symb2);
      char * symbname = stringtable2 + symb2.st_name;
      newSectionTable[i] = sections2[i];
      write_in_string_table(stringtable3, symbname);
    }
  }
  printf("%s", stringtable3);

}
