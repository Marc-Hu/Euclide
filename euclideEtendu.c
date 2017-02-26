#include<stdio.h>
#include<stdlib.h>


typedef struct{
	int dividende;
	int diviseur;
	int nbEff;
	int n[20][4];
}euclide;

void permute(int *j, int *k){
	int a = *j;
	*j=*k;
	*k=a;
}

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
	printf("Rn\tUn\tVn\tQn\n");
}

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

void affichage(euclide *p){
	int i, j;
	printf("%d", p->nbEff);
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

int main(){
	euclide p;
	choixDivi(&p);
	initialiseEuclide(&p);
	affichage(&p);
	return 0;
}