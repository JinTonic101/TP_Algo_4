#include <stdio.h>
#include <stdlib.h>

void printSolution(int vus[], int nbVus){
    /*
     Postcondition : Affiche les valeurs de vus[0..nbVus-1] séparées par un espace, suivies par un retour à la ligne
    */
    int i;
    for (i=0; i<nbVus; i++) {
        printf("%d ",vus[i]);
	}
    printf("\n");
}

void permut(int vus[], int nbVus, int nonVus[], int nbNonVus){
    /*
    Entree :
     - vus[0..nbVus-1] = sommets visités
     - nonVus[0..nbNonVus-1] = sommets non visités
    Précondition : nbVus > 0 et vus[0] = 0 (le tour commence toujours par le sommet 0)
    Postcondition : Affiche tous les tours commençant par vus[0..nbVus-1] et se terminant par les sommets de nonVus[0..nbNonVus-1] (dans tous les ordres possibles)
     */
    if (nbNonVus==0){  
		printSolution(vus,nbVus);
	}
	int v[nbVus+1], nV[nbNonVus];
	int i;
	for(i=0;i<nbVus;i++){
		v[i]=vus[i];
	}
	for(i=0;i<nbNonVus;i++){
		nV[i]=nonVus[i];
	}
	for(i=0; i<nbNonVus; i++){
		v[nbVus]=nonVus[i];
		nV[i]=nonVus[nbNonVus-1];
		permut(v,nbVus+1,nV,nbNonVus-1);
		nV[i]=nonVus[i];
	}
}

int main(){
    int nbSommets, i;
    scanf("%d", &nbSommets);
    int vus[nbSommets], nonVus[nbSommets-1];
    vus[0] = 0;
    for (i=0; i<nbSommets-1; i++) {
        nonVus[i] = i+1;
	}
    permut(vus,1,nonVus,nbSommets-1);
    return 0;
}
