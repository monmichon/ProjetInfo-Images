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
int width2 = width, height2 = height;


int main()
{
	srand(time(NULL));

	Piaf p(x0, height/2, 0, m);  //cr�e un piaf (cercle de rayon r, de masse m, plac� en (x0,height/2) etde couleur rouge)
	Obstacle obs[N]; //liste de tout les obstacles

	int n = 0; //n est le nombre d'obstacles cr��s
	int compteur = 0;
	double u = 0, v = 0, h = 0; //u, v, h variables al�atoires pour g�n�ration obstacles, grav variable al�atoire pour changement gravit�
	bool b = false, c = false, booleen = false, but = false; //booleens utiles pour la suite (m�moire)
	Timer t;

	Color* fond;
	loadColorImage(srcPath("fond.jpg"), fond, width2, height2);
	openWindow(width2,height2, "FlaPonts Bird");

	
	putColorImage(IntPoint2(0, 0), fond, width2, height2); //affichage du fond  

	p.afficher();

	ifstream score(srcPath("savegame.txt"));
	int best;
	score.close();

	Bouton bouton("START", width2 / 4 + 10, height2 / 3, 240,70,RED,YELLOW,50);

	bouton.afficher();
	while (!but)
	{
		but = bouton.test();
	}
	bouton.clic();
	milliSleep(50);

	t.reset();

	while (true) 
	{
		while (!b && !c)
		{ //tant que l'oiseau ne s'est ni crash� dans un tuyau (b vrai) ni dans une paroi (c vrai)

			ifstream score(srcPath("savegame.txt")); //on met � jour le meilleur score
			score >> best;
			score.close();

			t.reset(); //on remet le chrono � 0


			if (n == 0 || obs[n - 1].getx() < width2 - 600) //on cr�e un obstacle si le dernier est suffisament avanc� (dans le tiers gauche). Le rand() sert � ne pas avoir une distnce constante entre deux obstacles
			{
				n++;
				obs[n - 1].setx(width2 + 50 * double(rand()) / RAND_MAX);
				obs[n - 1].sety(double(rand()) / RAND_MAX*(height2 - 200));
				u = double(rand()) / RAND_MAX;
				v = double(rand()) / RAND_MAX;
				h = 135 + 15 * sqrt(-2 * log(u))*cos(2 * M_PI*v);//loi gaussienne pour l'epaisseur (pour �viter qu'il y ait trop de trucs large, mais un peu quand m�me
				if (h < 120)
					obs[n - 1].seth(120); 
				else
					obs[n - 1].seth(h);
			}


			noRefreshBegin();////////////////////////////////////////////////////// PARTIE AFFICHAGE

			putColorImage(IntPoint2(0, 0), fond, width2, height2);

			if (Clavier())
			{
				if (p.getvy() > 0)
					p.saut(jump);
				else
					p.saut(jump - p.getvy());
			}

			p.bouger();
			p.afficher();


			if (!obs[0].cadre())
			{//si l'obstacle sort de la fen�tre, on le sort de la liste et on d�cale tout
				for (int i = 0; i < n; i++)
					obs[i] = obs[i + 1];
				n--;
				booleen = false;
			}

			if ((obs[0].getx() + obs[0].getl() < x0) && !booleen)
			{ //si on passse un obstacle (forc�ment le premier de la liste) alors on incr�mente le compteur
				compteur++;
				booleen = true; //le bool�en est l� pour dire que l'obstacle � gauche du piaf a d�j� �t� compt�
			}

			for (int i = 0; i < n; i++)
			{
				obs[i].bouger(-vx);
				if (obs[i].cadre()) //on affiche l'obstacle i  si il est dans la fen�tre
					obs[i].afficher();
			}

			drawString(5, 60, to_string(compteur), Color(255, 100, 0), 45, 0, false, true);
			drawString(12, 60 + 50, to_string(best), Color(255, 100, 0), 30, 0, false, true);
			noRefreshEnd();////////////////////////////////////////FIN PARTIE AFFICHAGE

			c = !((p.gety() > 0) && (p.gety() < height2 - p.geth()));
			for (int i = 0; i < 3; i++) //Jamais plus de trois obstacles pass�s par p et toujours dans l'�cran, pas besoin de tout tester
				b = b || obs[i].test(p);

			if (300 * dt - 1000 * t.lap()>0)  //pour �viter que �a freeze si la boucle met trop de temps � s'executer
				milliSleep(300 * dt - 1000 * t.lap()); //on essaie d'�tre le plus r�gulier possible


			if (compteur > best)
			{ //on modifie le meilleur score en temps r�el
				ofstream score(srcPath("savegame.txt"));
				score << compteur;
				score.close();
			}
		}


		fillRect(IntPoint2(0, 0), width2, height2, RED);
		milliSleep(100);
		fillRect(IntPoint2(0, 0), width2, height2, YELLOW);
		milliSleep(100);
		fillRect(IntPoint2(0, 0), width2, height2, RED);
		milliSleep(100);
		fillRect(IntPoint2(0, 0), width2, height2, YELLOW);
		milliSleep(100);

		but = false;
		bouton.setText("REJOUER");
		bouton.setw(width2 / 2+45);
		bouton.afficher();

		while (!but)
		{
			but = bouton.test();
		}

		bouton.clic();
		compteur = 0;
		p.reset(x0, height2 / 2);
		b = false;
		c = false;
		for (int i = 0; i < n; i++)
			obs[i] = obs[i + 1];
		n--;
		booleen = false;
		milliSleep(50);

	}//fin boucle jeu
	Imagine::endGraphics();
	return 0;
}

