#include <Imagine/Graphics.h>
using namespace Imagine;
#include<iostream>
using namespace std;
#include <cmath>
#include "Classes.h"

#include "Fonctions.h"

const double x0 = width / 3, m = 35, r = 13, jump = 190*m*dt, pas_vitesse =dt;
double vx = 1400 * dt;
int main(){
	srand(time(NULL));
	Piaf p(x0, height/2, 0, m);  //crée un piaf (cercle de rayon r, de masse m, placé en (x0,height/2) etde couleur rouge)
	Obstacle obs[N]; //liste de tout les obstacles
	int n = 0; //n est le nombre d'obstacles créés
	int compteur = 0;
	openWindow(width,height, "FlaPonts Bird");
	bool b = false, c = false;
	Timer t;
	double u = 0, v = 0, h = 0;
	//p.afficher();
	Color* fond;
	int fondw, fondh;
	loadColorImage(srcPath("fond.jpg"), fond, fondw, fondh);
	putColorImage(IntPoint2(0, 0), fond, fondw, fondh); //affichage du fond  
	while (!b && !c){
		//vx += pas_vitesse;
		
		t.reset();
		if (n == 0||obs[n-1].getx()<width-600) //on crée un obstacle si le dernier est suffisament avancé (dans le tiers gauche). Le rand() sert à ne pas avoir une distnce constante entre deux obstacles
		{
			n++;
			obs[n-1].setx(width+50*double(rand())/RAND_MAX);
			obs[n-1].sety(double(rand()) / RAND_MAX*(height-200)); 
			u = double(rand()) / RAND_MAX;
			v = double(rand()) / RAND_MAX;
			h = 130 + 20 * sqrt(-2 * log(u))*cos(2 * M_PI*v);
			if (h < 100)
				obs[n - 1].seth(93); //loi gaussienne pour l'epaisseur (pour éviter qu'il y ait trop de trucs large, mais un peu quand même
			else
				obs[n - 1].seth(h);
		}


		noRefreshBegin();////////////////////////////////////////////////////// PARTIE AFFICHAGE
		putColorImage(IntPoint2(0, 0), fond, fondw, fondh);
		//p.effacer();
		if (Clavier()){
			if (p.getvy() > 0)
				p.saut(jump);
			else
				p.saut(jump - p.getvy());
		}
		p.bouger();
		p.afficher();
		for (int i = 0; i < n; i++)
		{
			//obs[i].effacer();
			obs[i].bouger(-vx);
			if (obs[i].cadre()) //on affiche l'obstacle i  si il est dans la fenêtre
				obs[i].afficher();
			else{ //sinon on l'efface de la liste et on décale l'ensemble 
				for (int i = 0; i < n; i++)
					obs[i] = obs[i + 1];
				n--;
				compteur++;
			}
		}
		
		drawString(width / 2 - 10, height / 4, to_string(compteur), RED, 30);

		noRefreshEnd();////////////////////////////////////////FIN PARTIE AFFICHAGE

		c = !((p.gety() > 0) && (p.gety()<height-p.geth()));
		for (int i = 0; i < 3; i++) //Jamais plus de trois obstacles passés par p et toujours dans l'écran, pas besoin de tout tester
			b = b||obs[i].test(p);
		if (350 * dt - 1000 * t.lap()>0)  //pour éviter que ça freeze si la boucle met trop de temps à s'executer
			milliSleep(350 * dt - 1000 * t.lap()); //on essaie d'être le plus régulier possible

	}
	cout << "PERDU" << endl;
	endGraphics();
	return 0;
}

