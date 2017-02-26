#include<stdio.h>
#include<stdlib.h>

/*
* Programme de calcul de la division euclidienne étendu (essentiellement pour la cryptographie)
* Afin d'éviter de faire les calculs manuellement mais aussi pour éviter d'effectuer des calculs avec des très grand nombre
* Ce programme nous permet de générer la division d'euclide étendu.
*/

/*
* Structure de donnée du tableau de la division d'euclide
*/

typedef struct{
	int dividende;
	int diviseur;
	int nbEff;
	int n[20][4];
}euclide;

/*
* Fonction qui permet de permuter deux valeurs. 
* Ici elle nous servira à permuter j et k si k est plus grand que j car on ne peut pas diviser un petit nombre par avec un grand nombre
*/

void permute(int *j, int *k){
	int a = *j;
	*j=*k;
	*k=a;
}

/*
* On initialise la structure 
* D'abord on cherche à savoir le nombre de ligne qu'il nous faudra
* C'est-à-dire le nombre de fois que la division sera effectué
* Ensuite on initialise tout le tableau à 0 (jusqu'a la ligne limite du calcul et non 20)
* Et pour finir on initialise les deux premières lignes du tableau car c'est la seule ligne qu'on connait 
*/

void initialiseEuclide(euclide *p){
	int j=p->dividende, k=p->diviseur;
	for(p->nbEff=0; k!=0; p->nbEff++){
		j=j%k;
		permute(&j, &k);
	}
	for (int i=0; i<(p->nbEff)+1; i++){
		for(int m=0; m<4; m++)
			p->n[i][m]=0;
	}
	p->n[0][0] = p->dividende;
	p->n[0][1] = 1;
	p->n[0][2] = 0;
	p->n[0][3] = 0;
	p->n[1][0] = p->diviseur;
	p->n[1][1] = 0;
	p->n[1][2] = 1;
	p->n[1][3] = p->dividende/p->diviseur;
}

/*
* Cette fonction permet à l'utilisateur de saisir la dividende et le diviseur
* Tout d'abord tant que l'utilisateur n'a pas saisie un nombre positif pour la dividende et le division on répète la saisie
* Si l'utilisateur à saisie un diviseur plus grand que la dividende alors on permute les valeurs et on lui fait savoir que l'on a permuté
*/

void choixDivi(euclide *p){
	do{
		printf("Dividende?\n");
		scanf("%d", &p->dividende);
	}while(p->dividende<0);
	do{
		printf("Diviseur?\n");
		scanf("%d", &p->diviseur);
	}while(p->diviseur<0);
	if(p->diviseur>p->dividende)
		permute(&p->dividende, &p->diviseur);
}

/*
* Cette fonction va afficher le tableau d'euclide étendu tout en calculer case par case les valeurs des lignes suivantes
* La première colonne contient le reste de la division entre les deux cases aux dessus
* La deuxième colonne fait le calcul suivant : la différence entre les deux cases au dessus multiplié par le quotient de la ligne au dessus 
* La troisième colonne fait exactement la même chose que la deuxième mais sur la troisième colonne
* La quatrième colonne contient le quotient de la division entre la colonne 1 de la ligne du dessus et la colonne 1 de la ligne courante 
*/

void affichage(euclide *p){
	int i, j;
	printf("Rn\tUn\tVn\tQn\n");
	for (i=0; i<(p->nbEff)+1; i++){
		if (p->n[i][0]==0){
			p->n[i][0]=(p->n[i-2][0])%(p->n[i-1][0]);
			p->n[i][1]=p->n[i-2][1]-p->n[i-1][1]*p->n[i-1][3];
			p->n[i][2]=p->n[i-2][2]-p->n[i-1][2]*p->n[i-1][3];
			if (p->n[i][0]!=0)
				p->n[i][3]=(p->n[i-1][0])/(p->n[i][0]); 
		}
		for (j=0; j<4; j++)
			printf("%d\t", p->n[i][j]);
		printf("\n");		
	}
	
}

/*
* Main qui créer une structure de donnée euclide
* On demande les deux valeurs à l'utilisateur
* On initialise le tableau
* On affiche tout en calculant le tableau
*/

int main(){
	euclide p;
	choixDivi(&p);
	initialiseEuclide(&p);
	affichage(&p);
	return 0;
}