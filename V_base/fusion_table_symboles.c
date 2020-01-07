#include "fusion_table_symboles.h"

/*
return :
the index if the symbol is define in table_symb
-1 if the symbol doesn't exist
*/
int is_define_in_table(char * name_symb,Elf32_Half ndx, liste_elf32_sym table_symb, char  * stringtable){
  Elf32_Sym symbcurr;
  for(int i=0;i<taille(table_symb);i++){
    get_symbol(table_symb, i, &symbcurr);
    char * symbname = stringtable + symbcurr.st_name;
    if(strcmp(symbname, name_symb) == 0 && ndx == symbcurr.st_shndx){
      if(symbcurr.st_info == 0){
        return i;
      }
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

  swap_header(&header1);
  swap_header(&header2);

  int offset1 = ((header1.e_shstrndx*header1.e_shentsize)+header1.e_shoff);
  int offset2 = ((  header2.e_shstrndx*header2.e_shentsize)+header2.e_shoff);
  char * stringtable1 = load_stringtable(file1, offset1);
  char * stringtable2 = load_stringtable(file2, offset2);
  char * stringtable3 = (char *)malloc(sizeof(char *));

  Elf32_Shdr newSectionTable[256];

  liste_elf32_sym  list_symb1,  list_symb2;
  creer_liste(&list_symb1,5);
  creer_liste(&list_symb2,5);

  Elf32_Shdr sections1[header1.e_shnum], sections2[header2.e_shnum];
  printf(" header1.e_shnum %d\n header2.e_shnum %d\n", header1.e_shnum, header2.e_shnum);
  load_tablesection(file1, header1, sections1);

  for (int i = 0; i< header1.e_shnum;i++){
    swap_header_section(&sections1[i]);
    }
  load_tablesection(file2, header2, sections2);
  for (int i = 0; i< header2.e_shnum;i++){
    swap_header_section(&sections2[i]);
    }

  load_tablesymbole(file1, header1, sections1, &list_symb1);
  for (int k = 0; k<taille(list_symb1);k++){
    swap_header_symb(&(list_symb1.tab[k]));
  }
  load_tablesymbole(file2, header2, sections2, &list_symb2);
  for (int k = 0; k<taille(list_symb2);k++){
    swap_header_symb(&(list_symb2.tab[k]));
  }
  offset1 = load_offset_symb(header1, sections1,stringtable1);
	offset2 = load_offset_symb(header2, sections2,stringtable2);
	free(stringtable1);
	free(stringtable2);
	stringtable1 = load_stringtable(file1,offset1);
	stringtable2 = load_stringtable(file2,offset2);
  //Boolean table for test
  int traiter[taille(list_symb2)];
  printf("taillo %d\n", taille(list_symb2));
  for (int i=0; i < taille(list_symb2);i++){
    traiter[i]=0;
  }
  //travel into the fabulous world of table symb 1
  printf("taillo 2 : %d\n", taille(list_symb1));
  for (int i=1; i <  taille(list_symb1);i++){
    Elf32_Sym symb1;
    get_symbol(list_symb1, i, &symb1);
    char * symbname = stringtable1 + symb1.st_name;
    int indexTab2 = is_define_in_table(symbname,symb1.st_shndx, list_symb2, stringtable2);
//  printf("%d", indexTab2);
    switch(indexTab2){

      case -1:
      //nv entrée
      newSectionTable[i] = sections1[i];
      //ecrire table chaine
      stringtable3 = strncat(stringtable3, symbname, strlen(symbname));
      //write_in_string_table(stringtable3, symbname);
      //maj tab
      traiter[indexTab2]=1;
      break;

      // define in 1 and 2
      case 0:
      //Erreur
      printf("you fool\n");
      return EXIT_FAILURE;

      //symb not present in 2
      default:
      //nv entrée
      newSectionTable[i] = sections1[i];
      //ecrire table chaine
      //write_in_string_table(stringtable3, symbname);
      stringtable3 = strncat(stringtable3, symbname, strlen(symbname));
      break;

    }
  }
  //travel into the fabulous world of table symb 2
  for(int i = 0; i<taille(list_symb2) ; i++) {
    if(traiter[i] == 0) {
      Elf32_Sym symb2;
      get_symbol(list_symb2, i, &symb2);
      char * symbname = stringtable2 + symb2.st_name;
      newSectionTable[i] = sections2[i];
      stringtable3 = strncat(stringtable3, symbname, strlen(symbname));
      //write_in_string_table(stringtable3, symbname);
    }
  }
  printf("sttable : %s\n", stringtable3);

}
