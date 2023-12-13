
#ifndef BIBLI
#define BIBLI
struct position {  //Definition du type position  
	int x; 
	int y;
};
struct fourmi{//Definition du type fourmi
    struct position pos;//position courante de la fourmi
    int retour;//0 lorsque la fourmi cherche de la nourriture et 1 sinon
    int prec;//mouvement précédent
};

int case_bord(struct fourmi );
int distance(struct pos);
void deplacement_r(int , struct pos, struct pos);
int Rand4Saud1(int );
int Rand4Sauf2(int, int );
int switch_nourriture(int );
#endif






   

