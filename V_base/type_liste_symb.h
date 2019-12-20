#ifndef _TYPE_LISTE_SYMB_H_

#define _TYPE_LISTE_SYMB_H_
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int n;
  int taille_max;
  Elf32_Sym* tab;
} liste_elf32_sym;

/* Constructeurs */

/* Creer une liste vide */
void creer_liste(liste_elf32_sym * p,int taille);

/* Operations d'acces */

/* Retourne vrai ssi p est vide */
int est_vide(liste_elf32_sym p);

/* Renvoie le nombre d'elements dans la liste */
int taille(liste_elf32_sym p);

/* lit l'element a l'indice ind*/
/*Return 0 si ca s est bien passe et le symbole sera dans le 3eme argument
  Return 1 si il y a eu une erreur*/
int get_symbol(liste_elf32_sym p, int ind, Elf32_Sym* elem);

/* Operations de modification */

/* Vider la liste p */
void vider(liste_elf32_sym * p);

/* ajouter a la liste un Elf32_Sym x */
int ajouter(liste_elf32_sym * p, Elf32_Sym x);

void re_alloc(liste_elf32_sym * p);

/* Supprimer l'Elf32_Sym en haut de la liste */
int supprimer(liste_elf32_sym * p);

/* Free la structure */
void free_liste(liste_elf32_sym * p);
#endif
