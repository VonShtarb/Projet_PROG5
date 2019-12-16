
#include "type_liste_symb.h"

/* Créer une liste vide */
void creer_liste(liste_elf64_sym * p,int taille){
	p->n=0;
	p->taille_max = taille;
	p->tab = malloc(sizeof(Elf64_Sym) * taille);
}

/* Opérations d'accès */

/* Retourne vrai ssi p est vide */
int est_vide(liste_elf64_sym p){
	if (p.n==0){
		return 1;
	}
	return 0;
}	

/* Renvoie le nombre d'éléments dans la liste */
int taille(liste_elf64_sym p){
	return p.n;
}

/* lit l'element a l'indice ind*/
/*Return 0 si ca s est bien passe et le symbole sera dans le 3eme argument
  Return 1 si il y a eu une erreur*/
int get_symbol(liste_elf64_sym p, int ind, Elf64_Sym* elem){
	if (ind < p.n) {
		*elem = p.tab[ind];
		return 0;
	}
	else {
		elem = NULL;
		return 1;
	}
}

/* Opérations de modification */

/* Vider la liste p */
void vider(liste_elf64_sym * p){
	p->n=0;
}

/* Emlister un entier x */
/* Précondition : taille(p) < TAILLE_MAX */
int ajouter(liste_elf64_sym * p,Elf64_Sym x){
	if (p->n == p->taille_max) {
		return 1;
	}
	p->tab[p->n]=x;
	p->n++;
	return 0;
}

/* Supprimer l'entier en haut de la liste */
/* Précondition : p non vide */
int Supprimer(liste_elf64_sym * p, int ind){
	if (p->n == 0){
		return 1;
	}
	p->tab[ind] = p->tab[(p->n)-1];
	p->n--;
	return 0;
}

/* Free la structure */
void free_liste(liste_elf64_sym * p){
	free(p->tab);
	p->n=0;
}







