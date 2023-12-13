#define Nnour 4 //nombre de nourritures
#define N 31 //taille de la grille
#define Nf 5 //nombre de fourmis


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


struct position {  //Definition du type position  
	int x; 
	int y;
};

struct fourmi{//Definition du type fourmi
    struct position pos;//position courante de la fourmi
    int retour;//0 lorsque la fourmi cherche de la nourriture et 1 sinon
    int prec;//mouvement précédent
};


 struct position nid={15,15};

 int case_bord(struct fourmi f){//retourne 1 si la fourmi f est sur une case adjacente au bord de la grille de taille N*N et 0 sinon.

return((f.pos.x==N-1)||(f.pos.x==0)||(f.pos.y==N-1)||(f.pos.y==0));

} 


int distance(struct position pos){//retourne la distance euclidienne entre pos et nid
	return floor(sqrt((pos.x-nid.x)*(pos.x-nid.x)+(pos.y-nid.y)*(pos.y-nid.y)));
}
 



int Rand4Sauf1(int except){//tirage d'un entier aléatoire entre 0 et 4 sauf except
	if((except<0)||(except>3)){	
		printf("erreur");
	}
	int r=rand()%3;
	if(r>=except){
		r++;
	}
	return r;
}


int Rand4Sauf2(int except1, int except2){//tirage d'un entier aléatoire entre 0 et 4 sauf except1 et except2
	
	int min= fmin(except1, except2);
	printf("min %d\n", min);
	int  max = fmax(except1, except2);
	printf("max %d\n", max);
	if((min<0)||(max>3)){
		printf("erreur");
		return 0;
	}
	int r=1+rand()%2;
	printf("r %d\n", r);
	if(r>=max){
		return r+1;
	}
	if(r<=min){
		return r-1;
	}
	return r;
}
int switch_nourriture( int a){//renvoie un entier selon la règle suivante: (0,1,2,3)->(1,0,3,2)
            
            switch(a){
         case 0:
              return 1;
            case 1:
           	return 0;
            case 2:
               return 3;
            default:
          return 2;
      }
    }

   


int main(){
	return 0;
}


