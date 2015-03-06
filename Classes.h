#pragma once


const double dt = 0.05; //pas temporel
const double g = 98*dt;//pesanteur
const double vo = -500*dt; //vitesse obstacle;
const double lim = 140;//vitesse limite de l'oiseau
const int N = 10;
const int width = 600, height = 800;

class Piaf{
	double x, y;//position
	double vx,vy;//vitesse
	double m; //masse
	int w,h;//dimensions piaf
	Color* I0;
	Color* I1;
	Color* I2;
	Color* I3;
	Color* I4;
	Color* I5;
	Color* I6;

	int pos;

	void setpos(int X, int Y);
	void setv(double vX, double vY);
public:
	Piaf(double x,double y,double vx, double m);
	int getw();
	int geth();
	double getx();
	double gety();
	double getvx();
	double getvy();
	void saut(double dy);
	void bouger();
	void afficher();
	void effacer();
	void reset(int X, int Y);
};

class Obstacle{
	int x,y, l, h,t; //x est le coin du bas, l la largeur, h la hauteur du trou dans le tube;
	Color* I1;
	Color* I2;
public:
	Obstacle();
	void afficher();
	void effacer();
	void bouger(double vx);
	bool test(Piaf p);
	void setx(double X);
	void sety(double Y);
	void seth(double H);
	bool cadre();
	double getx();
	int getl();
};

class Bouton{
	int x, y, w, h,t;
	Color c1, c2;
	std::string s1, s2; //si texte à afficher
	Color* I1;//si image à afficher
	Color* I2;
	bool b; //indique si bouton image ou texte
public:
	Bouton(std::string s, int x, int y, int w, int h, Color c1, Color c2, int t);
	Bouton(std::string s1, std::string s2, int x, int y);
	void afficher();
	void text();
	void setw(int W);
	void setText(std::string S);
	void clic();
	bool test();
};

class Piece{
	int x, y, w, h, type;
	Color* I;
public:
	Piece(int x, int y, int type);
	~Piece();
	void bouger(int vx);
	void afficher();
	bool test(Piaf p);
	void setxy(int X, int Y);
	bool cadre();
};