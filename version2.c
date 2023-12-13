
#define Nnour 4
#define N 31
#define Nf 5

/*#include<sabrina.h>*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


struct position{ //Definition du type position  
	int x; 
	int y;
};

struct fourmi{//Definition du type fourmi
    struct position pos;//position courante de la fourmi
    int retour;//0 lorsque la fourmi cherche de la nourriture et 1 sinon
    int prec;//mouvement précédent
};

 struct environment{//Definition du type environment
    struct fourmi Tabfourmis[Nf];
    struct position nourriture[Nnour];
    int tour;//nombre de déplacements total effectué par les fourmi de Tabfourmis[]
    int pheromones[N][N];
 };
 
 struct position nid={15,15};

 int case_bord(struct fourmi f){
    /*retourne 1 si la fourmi f est sur une case adjacente au bord et 0 sinon*/

return((f.pos.x==N-1)||(f.pos.x==0)||(f.pos.y==N-1)||(f.pos.y==0));

} 

int distance(struct position pos){
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


int Rand4Sauf2(int except1, int except2){
	
	int min= fmin(except1, except2);
	int  max = fmax(except1, except2);
	if((min<0)||(max>3)){
		printf("erreur");
		return 0;
	}
	int r=1+rand()%2;
	if(r>=max){
		return r+1;
	}
	if(r<=min){
		return r-1;
	}
	return r;
}
int switch_nourriture( int a){
            
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

   


struct environment init_v2(struct position nid){
	struct environment res;
	int i,tx,ty,j,t;
	res.tour=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
		res.pheromones[i][j]=0;
		}
	}
	for(i=0;i<Nf;i++){
		res.Tabfourmis[i].pos.x=nid.x;
		res.Tabfourmis[i].pos.y=nid.y;
	}
	for(i=0;i<Nnour;i++){//on place les Nnour nourritures
		t=1;//on réinitialise la variable t pour pouvoir entrer dans le while
		while(t){
			tx=1+rand()%(N-2);
			ty=1+rand()%(N-2);//on tire deux entiers aléatoires compris entre 1 et N-2 (pas de nourriture sur les bords)
			for(j=0;j<i;j++){	
				if((tx!=res.nourriture[j].x||ty!=res.nourriture[j].y)&&(tx!=nid.x||ty!=nid.y)){
				//on ne met pas 2 fois de la nourriture dans la même case, ni dans le nid
					res.nourriture[i].x=tx;
					res.nourriture[i].y=ty;
					printf("%d\n %d\n",tx,ty);	
					t=0;//la i-éme nourriture est trouvée
				}
			
			}
			if(i==0&&(res.nourriture[i].x!=nid.x||res.nourriture[i].y!=nid.y)){
			res.nourriture[0].x=tx;
			res.nourriture[0].y=ty;
			t=0;
			}	
		}
	}
	
	return res;
}



struct environment ne;

struct fourmi MoveNourriture(struct fourmi f){
	struct fourmi rf;
	int i=0, j, r, m=0, min;
	int p[4];
				p[0]=ne.pheromones[f.pos.x][f.pos.y+1];
				p[1]=ne.pheromones[f.pos.x][f.pos.y-1];
				p[2]=ne.pheromones[f.pos.x-1][f.pos.y];
				p[3]=ne.pheromones[f.pos.x+1][f.pos.y];
	min=p[0]+p[1];//On doit faire en sorte que min soit plus grand qu'au moins 2 des p[i]
	int pf=f.prec;
	int interdit=switch_nourriture(pf);
	while((i<4)&&(i!=interdit)){
		for(j=0;((j<i)&&(j!=interdit));j++){
			if(p[i]==p[j]){
				r=Rand4Sauf1(interdit);//on tire un nombre aléatoire r parmi { i}_{i!=interdit};
				switch(r){
					case 0:
						rf.pos.y=f.pos.y+1;
						break;
					case 1:
						rf.pos.y=f.pos.y-1;
						break;
					case 2:
						rf.pos.x=f.pos.x-1;
						break;
					default:
						rf.pos.x=f.pos.x+1;
						break;
				}
			i=5;
			}
			i++;
        	}
    }
	if(i!=5){
        	
        for(i=0; ((i<4)&&(i!=interdit)); i++){
            if(p[i]<=min){ //on doit faire en sorte que min soit plus grand quau moins 1 des p[i]
                m=i;}
			r=Rand4Sauf2(m,i);//on tire un nombre aléatoire r parmi { i}_{i!= m,interdit};
			switch(r){
					case 0:
						rf.pos.y=f.pos.y+1;
						break;
					case 1:
						rf.pos.y=f.pos.y-1;
						break;
					case 2:
						rf.pos.x=f.pos.x-1;
						break;
					default:
						rf.pos.x=f.pos.x+1;
						break;
				}
        }
	}
    if (case_bord(rf)){
            rf.pos=f.pos;
            pf=switch_nourriture(r);
            
	}  
	else{pf=r;}
	switch(r){
		case 0:
			rf.pos.y=f.pos.y+1;
			break;
		case 1:
			rf.pos.y=f.pos.y-1;
			break;
		case 2:
			rf.pos.x=f.pos.x-1;
			break;
		default:
			rf.pos.x=f.pos.x+1;
			break;
	}
	return rf;}




struct fourmi MoveRetour(struct fourmi f){
    struct fourmi rf;
    int d[4];
    int i=0, j, r, m=0, max=0;//on doit faire en sorte que max soit inférieur à au moins des d[i]
    int pf=f.prec;
	for(i=0; i<4; i++){
	switch(r){
		case 0:
			rf.pos.y=f.pos.y+1;
			break;
		case 1:
			rf.pos.y=f.pos.y-1;
			break;
		case 2:
			rf.pos.x=f.pos.x-1;
			break;
		default:
			rf.pos.x=f.pos.x+1;
			break;
	}
	d[i]=distance(rf.pos);
	rf=f;}
   
    int interdit=switch_nourriture(pf);
    while((i<4)&&(i!=interdit)){
        for(j=0;((j<i)&&(j!=interdit));j++){
            if(d[i]==d[j]){
            r=Rand4Sauf1(interdit);//on tire un nombre aléatoire r parmi { i}_{i!=interdit};
		i=5;
}
i++;
        }
    }
    if(i!=5){
     
        for(i=0; ((i<4)&&(i!=interdit)); i++){
            if(d[i]>=max){
                m=i;}
		r=Rand4Sauf2(m,interdit);//on tire un nombre aléatoire r parmi { i}_{i!= m,interdit}
		switch(r){
		case 0:
			rf.pos.y=f.pos.y+1;
			break;
		case 1:
			rf.pos.y=f.pos.y-1;
			break;
		case 2:
			rf.pos.x=f.pos.x-1;
			break;
		default:
			rf.pos.x=f.pos.x+1;
			break;
	}
		}
	}
    if (case_bord(rf)){
            rf.pos=f.pos;
            pf=switch_nourriture(r);
            
	}

    
	else{pf=r;}/*a confirmer*/
	return rf;}




struct environment evolve(struct environment e){
	struct position nid={N/2,N/2};
	int t=1;
	int fx, fy;
	int temp;
	int i,j;
	struct environment ne=init_v2(nid);
    for(i=0;i<Nf;i++){
    	temp=ne.tour;
    	while(t){//tant que la fourmi n'a pas trouvÃ© de nourriture on recommence
    			fx=ne.Tabfourmis[i].pos.x;
    			fy=ne.Tabfourmis[i].pos.y;
    			
	    	ne.Tabfourmis[i]=MoveNourriture(ne.Tabfourmis[i]);//la fourmi cherche la nourriture
			ne.pheromones[fx][fy]++;
			ne.tour++;//on rÃ©alise un  tour de plus
	        for(j=0;j<=Nnour;j++){
	            if (fx==ne.nourriture[j].x&&fy==ne.nourriture[j].y){//nourriture trouvÃ©e
	            	printf("la fourmi %d\n a trouvÃ© une nourriture en case: ", i);
	            	printf("%d\t%d\n",fx, fy);
	            	printf("nombre de tours nÃ©cÃ©ssaires pour que la fourmi %d\n trouve la nourriture au tour: ", i);
	            	temp=ne.tour-temp;
	            	printf("%d\n", temp);//on affiche le nombre de tours nÃ©cÃ©ssaires pour trouver la nourriture
	            	ne.nourriture[j].x=32;//la fourmi i a pris la nourriture, donc on l'enlève
	            	ne.nourriture[j].y=32;
	            	ne.Tabfourmis[i].retour=1;
	            	t=0;
					break;}
			}
	
	}
		while(fx==nid.x&&fy==nid.y){
			ne.Tabfourmis[i]=MoveRetour(ne.Tabfourmis[i]);
			fx=ne.Tabfourmis[i].pos.x;
    		fy=ne.Tabfourmis[i].pos.y;
			ne.pheromones[fx][fy]++;
			ne.tour++;
	
		}
		temp=ne.tour-temp;
		printf("la fourmi %d\t est rentré au nid en %d\t tour",i,temp);
    }
    return ne;  }
    
    

void EnregPosFourmi(struct fourmi f){
	FILE *output = fopen("nom.txt", "a");
	fprintf(output,"%d\t%d\n",f.pos.x,f.pos.y);
	fclose(output);
}
int main(){
	srand(time(NULL)));
	FILE *output2 = fopen("nom.txt2", "a");
	struct environment e,ne;
	int i, j;
	int phero[N][N];
	while(1){
		ne=evolve(e);	
	
		for(i=0;i<N;i++){
			for(j=0; j<N; j++){
				phero[i][j]=phero[i][j]+ne.pheromones[i][j];
				fprintf(output2,"%d\t%d\t%d\n",i,j,phero[i][j]);
				if(phero[i][j]>=32000){
				fclose(output2);
				return 0;}
			}
		}
	}
}
