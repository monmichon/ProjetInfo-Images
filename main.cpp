#include <Imagine/Graphics.h>
using namespace Imagine;
#include<iostream>
using namespace std;
#include <cmath>
#include "Classes.h"

#include "Fonctions.h"

double m = 35, x0 = width / 3;
const double  r = 13, jump = 190*m*dt, pas_vitesse =dt;
double vx = 1400 * dt;


int main(){


	srand(time(NULL));
	Piaf p(x0, height/2, 0, m);  //crée un piaf (cercle de rayon r, de masse m, placé en (x0,height/2) etde couleur rouge)
	Obstacle obs[N]; //liste de tout les obstacles
	int n = 0; //n est le nombre d'obstacles créés
	int compteur = 0;
	openWindow(width,height, "FlaPonts Bird");
	bool b = false, c = false, booleen = false; //booleens utiles pour la suite (mémoire)
	Timer t;
	double u = 0, v = 0, h = 0; //u, v, h variables aléatoires pour génération obstacles, grav variable aléatoire pour changement gravité
	Color* fond;
	int fondw, fondh;
	loadColorImage(srcPath("fond.jpg"), fond, fondw, fondh);
	putColorImage(IntPoint2(0, 0), fond, fondw, fondh); //affichage du fond  

	int x,y; //inutiles, simplement pour utiliser getMouse à la fin:
	ifstream score(srcPath("savegame.txt"));
	int best;
	score.close();
	while (true)
	{
		while (!b && !c)
		{ //tant que l'oiseau ne s'est ni crashé dans un tuyau (b vrai) ni dans une paroi (c vrai)

			ifstream score(srcPath("savegame.txt")); //on met à jour le meilleur score
			score >> best;
			score.close();

			t.reset(); //on remet le chrono à 0


			if (n == 0 || obs[n - 1].getx() < width - 600) //on crée un obstacle si le dernier est suffisament avancé (dans le tiers gauche). Le rand() sert à ne pas avoir une distnce constante entre deux obstacles
			{
				n++;
				obs[n - 1].setx(width + 50 * double(rand()) / RAND_MAX);
				obs[n - 1].sety(double(rand()) / RAND_MAX*(height - 200));
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

			if (Clavier()){
				if (p.getvy() > 0)
					p.saut(jump);
				else
					p.saut(jump - p.getvy());
			}

			p.bouger();
			p.afficher();


			if (!obs[0].cadre()){//si l'obstacle sort de la fenêtre, on le sort de la liste et on décale tout
				for (int i = 0; i < n; i++)
					obs[i] = obs[i + 1];
				n--;
				booleen = false;
			}

			if ((obs[0].getx() + obs[0].getl() < x0) && !booleen){ //si on passse un obstacle (forcément le premier de la liste) alors on incrémente le compteur
				compteur++;
				booleen = true; //le booléen est là pour dire que l'obstacle à gauche du piaf a déjà été compté
			}

			for (int i = 0; i < n; i++)
			{
				obs[i].bouger(-vx);
				if (obs[i].cadre()) //on affiche l'obstacle i  si il est dans la fenêtre
					obs[i].afficher();
			}

			drawString(5, 60, to_string(compteur), Color(255, 100, 0), 45, 0, false, true);
			drawString(12, 60 + 50, to_string(best), Color(255, 100, 0), 30, 0, false, true);
			noRefreshEnd();////////////////////////////////////////FIN PARTIE AFFICHAGE

			c = !((p.gety() > 0) && (p.gety() < height - p.geth()));
			for (int i = 0; i < 3; i++) //Jamais plus de trois obstacles passés par p et toujours dans l'écran, pas besoin de tout tester
				b = b || obs[i].test(p);
			if (300 * dt - 1000 * t.lap()>0)  //pour éviter que ça freeze si la boucle met trop de temps à s'executer
				milliSleep(300 * dt - 1000 * t.lap()); //on essaie d'être le plus régulier possible


			if (compteur > best){
				ofstream score(srcPath("savegame.txt"));
				score << compteur;
				score.close();
			}

		}
		drawString(width / 4, height / 3, "REJOUER", RED, 50);
		getMouse(x, y);
		if (x > width / 4 && x<3 * width / 4 && y<height / 3 && y > height / 3 - 50){
			drawString(width / 4, height / 3, "REJOUER", Color(255,255,0), 50);
			milliSleep(150);
			drawString(width / 4, height / 3, "REJOUER", RED, 50);
			compteur = 0;
			p.reset(x0, height / 2);
			b = false;
			c = false;
			for (int i = 0; i < n; i++)
				obs[i] = obs[i + 1];
			n--;
			booleen = false;
			milliSleep(50);
		}
	}

	Imagine::endGraphics();
	return 0;
}

