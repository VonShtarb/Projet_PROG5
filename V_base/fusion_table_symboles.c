#include "fusion_table_symboles.h"

/*
return :
  0 if the symbol is define in table_symb
  1 if the symbol is present but not define
  -1 if the symbol doesn't exist
*/
int is_define_in_table(char * name_symb, Elf32_Shdr table_symb, char * stringtable){
  Elf32_Sym symbcurr;
  for(int i=0,i<sizeof(table_symb)/sizeof(Elf32_Sym);i++){
    get_symbol(table_symb, i, &symbcurr);
    char * symbname = stringtable + symbcurr.st_name;
    if(strcmp(symbname, name_symb)==0){
      if (i==0)
        return 1;
      else
        return 0;
    }
  }
  return -1;
}

//code de test
int main(int argc, char *argv[]){
//load symbols tables
  char * file1 = "./Examples_loader/example1.o";
  char * file2 = "./Examples_loader/example1.o";
  Elf32_Ehdr header1 = load_header(file1);
  Elf32_Ehdr header2 = load_header(file2);
  Elf32_Shdr sections1[], sections2[];
  liste_elf32_sym * list_symb1, list_symb2;
  load_tablesection(file1, header1, sections1[]);
  load_tablesection(file2, header2, sections2[]);
  load_tablesymbole(file1, header1, sections1[], list_symb1);
  load_tablesymbole(file2, header2, sections2[], list_symb2);
  int offset1 = ((header1.e_shnum*header1.e_shentsize)+header1.e_shoff);
  int offset2 = ((header2.e_shnum*header2.e_shentsize)+header2.e_shoff);
  char * stringtable1 = load_stringtable(file1, offset1);
  char * stringtable2 = load_stringtable(file2, offset2);

  //Boolean table for test
  int traiter[sizeof(list_symb2)/sizeof(Elf32_Sym)];
  for (int i=0; i < sizeof(list_symb2)/sizeof(Elf32_Sym);i++){
    traiter[i]=0;
  }
  //travel into the fabulous world of table symb 1
  for (int i=0; i < sizeof(list_symb1)/sizeof(Elf32_Sym);i++){
    Elf32_Sym symb1;
    get_symbol(liste_symb1, i, &symb1);
    char * symbname = stringtable1 + symb1.st_name;
    switch(is_define_in_table(symbname, list_symb2, stringtable2)){
      //symb defini dans 2
      case 0:
        //Erreur
        printf("you fool");
        return EXIT_FAILURE;
      //symb present but not define dans 2
      case 1:
          //nv entrée
          //ecrire table chaine
          //maj tab
          break;
      //symb not present in 2
      case -1:
          //nv entrée
         //ecrire table chaine
          break;
        //
    }
  }
}
