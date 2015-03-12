#pragma once


const double dt = 0.05; //pas temporel
const double g = 98*dt;//pesanteur
const double vo = -500*dt; //vitesse obstacle;
const double lim = 140;//vitesse limite de l'oiseau
const int N = 3;
const int width = 600, height = 800;

class Piaf{
	double x, y;//position
	double vy;//vitesse
	double m; //masse
	int w,h;//dimensions image
	Color* I0; //Toutes les images pour affichage rotation
	Color* I1;
	Color* I2;
	Color* I3;
	Color* I4;
	Color* I5;
	Color* I6;

	int pos;//repère pour savoir quelle image afficher parmi les 7
    int perso; // choix du personnage

	void setpos(int X, int Y);
	void setv(double vY);
public:
	
	Piaf(double x,double y, double m, int perso);
	int getw();
	int geth();
	double getx();
	double gety();
	double getvy();
	void saut(double dy);
	void bouger();
	void afficher();
	void reset(int X, int Y);
};

class Obstacle{
	int x,y, l, h,t; //x est le coin du bas, l la largeur, h la hauteur du trou dans le tube. 
					 //t sert à savoir quelle portion du tube complet tronquer 
					 //(l'image a une hauteur fixe, on adapte la taille du tube en en affichant une partie en dehors).

	Color* I1;  //tube du haut et tube du bas
	Color* I2;
public:
	Obstacle();
	void afficher();
	void bouger(double vx);
	bool test(Piaf* p);
	void setx(double X);
	void sety(double Y);
	void seth(double H);
	bool cadre();
	double getx();
	int getl();
};

class Bouton{
	int x, y, w, h;
	std::string s1, s2; //chemins images
	Color* I1;
	Color* I2;
public:
	Bouton( std::string s1,  std::string s2, int x, int y);  //ructeur si Bouton image (deuxième image utile pour effet "clic")
	~Bouton();
	void afficher();
	void clic();
	bool test(int X,  int Y);
	void setImage(std::string S1, std::string S2);
};

class Piece{
	int x, y, w, h;
	bool b;
	Color* I;
public:
	Piece(int x, int y);
	~Piece();
	void bouger(int vx);
	void afficher();
	bool test(Piaf* p);
	void setxy(int X, int Y);
	bool cadre();
	bool existe();
	void existence(bool booleen);
};