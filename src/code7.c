#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int** cout;
int var;

void creeCout(int nbSommets){
    int coutMin = 10;
    int coutMax = 40;
    int i, j, iseed, it;
    iseed = 1;
    cout = (int**) malloc(nbSommets*sizeof(int*));
    for (i=0; i<nbSommets; i++){
        cout[i] = (int*) malloc(nbSommets*sizeof(int));
        for (j=0; j<nbSommets; j++){
            if (i == j) cout[i][j] = coutMax+1;
            else {
                it = 16807 * (iseed % 127773) - 2836 * (iseed / 127773);
                if (it > 0)	iseed = it;
                else iseed = 2147483647 + it;
                cout[i][j] = coutMin + iseed % (coutMax-coutMin+1);
            }
        }
    }
}

int comp(const void* a, const void* b){
	int i1 = *(int*) a;
	int i2 = *(int*) b;
	return cout[var][i1] - cout[var][i2];
}

void printTab(int vus[], int nbVus){
    /*
     Postcondition : Affiche les valeurs de vus[0..nbVus-1] separees par un espace, suivies par un retour à la ligne
    */
    int i;
    for (i=0; i<nbVus; i++)
        printf("%d ",vus[i]);
    printf("\n");
}



int permut(int vus[], int nbVus, int nonVus[], int nbNonVus, int longueur, int pcc){
    if(nbNonVus>0){
		int l=cout[vus[nbVus-1]][nonVus[0]];
		int j;
		for(j=1; j<nbNonVus; j++){
			if(cout[vus[nbVus-1]][nonVus[j]]<l){
				l=cout[vus[nbVus-1]][nonVus[j]];
			}
		}
		int somme = l;
		int min, j1, j2;
		for(j1=0; j1<nbNonVus; j1++){
			min = INT_MAX;
			for(j2=0; j2<nbNonVus; j2++){
				if(j1!=j2){
					if(cout[nonVus[j1]][nonVus[j2]]<min){
						min = cout[nonVus[j1]][nonVus[j2]];
					}
				}
				if(cout[nonVus[j1]][0]<min){
					min = cout[nonVus[j1]][0];
				}
			}
			somme += min;
		}
		if(longueur+somme > pcc){
			return pcc;
		}
	}
	int k;
	int tmp[nbNonVus];
    for(k=0; k<nbNonVus; k++){
		tmp[k]=nonVus[k];
	}
	var = vus[nbVus-1];
	qsort(tmp, sizeof tmp / sizeof *tmp, sizeof *tmp, comp);
		
	nonVus = tmp;
	
    if(nbNonVus==0){
        longueur +=  cout[vus[nbVus-1]] [0];
        if(longueur<pcc){
			pcc=longueur;
		}
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
		int lo=longueur+cout[v[nbVus-1]][v[nbVus]];
		pcc=permut(v,nbVus+1,nV,nbNonVus-1,lo,pcc);
		nV[i]=nonVus[i];
	}
	return pcc;
}

int main(){
    int nbSommets, i, pcc;
    scanf("%d",&nbSommets);
    int vus[nbSommets];
    int nonVus[nbSommets-1];
    creeCout(nbSommets);
    for (i=0; i<nbSommets-1; i++)
        nonVus[i] = i+1;
    vus[0] = 0;
    pcc = permut(vus,1,nonVus,nbSommets-1,0,INT_MAX);
    printf("%d\n",pcc);
    return 0;
}
