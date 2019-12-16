
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int n;
  int taille_max;
  Elf64_Sym* tab;
} liste_elf64_sym;

/* Constructeurs */

/* Creer une liste vide */
void creer_liste(liste_elf64_sym * p,int taille);

/* Operations d'acces */

/* Retourne vrai ssi p est vide */
int est_vide(liste_elf64_sym p);

/* Renvoie le nombre d'elements dans la liste */
int taille(liste_elf64_sym p);

/* lit l'element a l'indice ind*/
/*Return 0 si ca s est bien passe et le symbole sera dans le 3eme argument
  Return 1 si il y a eu une erreur*/
int get_symbol(liste_elf64_sym p, int ind, Elf64_Sym* elem);

/* Operations de modification */

/* Vider la liste p */
void vider(liste_elf64_sym * p);

/* ajouter a la liste un Elf64_Sym x */
int ajouter(liste_elf64_sym * p, Elf64_Sym x);

/* Supprimer l'Elf64_Sym en haut de la liste */
int supprimer(liste_elf64_sym * p);

/* Free la structure */
void free_liste(liste_elf64_sym * p);