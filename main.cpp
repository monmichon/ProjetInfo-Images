#include <Imagine/Graphics.h>
using namespace Imagine;
#include<iostream>
using namespace std;
#include <cmath>
#include "Classes.h"

#include "Fonctions.h"


int m = 35, x0 = width / 3;
int best;
const double jump = 190*m*dt, pas_vitesse =dt;
int vx = 1400 * dt; //vitesse de défilement des tuyaux
int width2 = width, height2 = height; //width et height sont des const définis dans Classes.h, et on a besoin de leurs équivalents en int pour les utiliser dans loadColorImage
int n = 0; //n est le nombre d'obstacles créés
int compteur = 0;
double u = 0, v = 0, h = 0; //u, v, h variables aléatoires pour génération obstacles, grav variable aléatoire pour changement gravité
bool b = false, c = false, booleen = false, but = false, quitter = false;//booleens utiles pour la suite (mémoire)

int X, Y; //Positions de la souris pour clics quand plusieurs boutons
int perso; // permet de choisir le personnage au dŽbut du jeu
int main()
{
	srand(time(NULL));

    Piece piece(3*width / 4, height / 2, 1); //Création d'une piece pour bonus
	Obstacle obs[N];						 //liste de tout les obstacles

	Timer t; //Définition d'un chrono pour contrôler temps d'éxécution de chaque boucle

	Color* fond;													//CHARGEMENT DU
	loadColorImage(srcPath("fond.jpg"), fond, width2, height2);     //FOND ET
	Window W1=openWindow(width2+20,height2+20, "FlaPonts Bird");				    //OUVERTURE FENETRE

	
	putColorImage(IntPoint2(0, 0), fond, width2, height2);//affichage du fond  //AFFICHAGE DE L'ECRAN
    

	Bouton bouton_start("bouton_start.jpg", "bouton_start_clic.jpg",width2 / 5-20, height2 / 3);			    	//DEFINITION
	Bouton bouton_rejouer("bouton_rejouer.jpg", "bouton_rejouer_clic.jpg", width2 / 5 - 20, height2 / 5+50);       //DES BOUTONS
	Bouton bouton_quitter("bouton_quitter.jpg", "bouton_quitter_clic.jpg", width2 / 5 - 20, height2/5+300);        //UTILES
	int h_bouton = height2 / 2-17, step = 120;
    Bouton bouton_flappy("oiseau_bouton.jpg","oiseau_bouton_clic.jpg",width2 / 2-20, h_bouton);
    Bouton bouton_mathias("m.jpg","m_clic.jpg",width2/2-20+step, h_bouton);
    Bouton bouton_thibaud("t.jpg","t_clic.jpg",width2 /2-10-step,h_bouton);
	Bouton bouton_fond("fond_bouton.jpg","fond_bouton.jpg",width2/5-20,h_bouton-17);
    
<<<<<<< HEAD
    drawString(10,height2/4,"choisissez",YELLOW,50);
    drawString(width2/2-40,height2/4,"votre",YELLOW,50);
    drawString(width2/2+30,height2/4,"perso",YELLOW,50);
=======
	bouton_start.afficher();
	bouton_fond.afficher();
>>>>>>> origin/master
    bouton_flappy.afficher();
    bouton_mathias.afficher();
    bouton_thibaud.afficher();
    
    while (!but)  
    {
        getMouse(X, Y);
        but =(bouton_mathias.test(X,Y)||bouton_thibaud.test(X,Y)||bouton_flappy.test(X,Y)||bouton_start.test(X,Y));
    }
    if(bouton_mathias.test(X,Y))
	{
        bouton_mathias.clic();
        perso=1;
    }
    else if(bouton_thibaud.test(X,Y))
	{
        bouton_thibaud.clic();
        perso=2;
    }
    else if(bouton_flappy.test(X,Y))
	{
        bouton_flappy.clic();
        perso=0;
    }
	else
	{
		bouton_start.clic();
		perso = 0;
	}
    but=false;
    
    putColorImage(IntPoint2(-1, -1), fond, width2, height2);        //affichage du fond 
    Piaf p(x0, height/2, 0, m, perso);                              //
    p.afficher();                                                   //affichage de l'oiseau
    
	t.reset(); //On lance le chrono

	do  //On entre dans la boucle d'éxécution (en sortir signifie quitter le jeu, voir while à la fin)
	{
		while (!b && !c) //Tant que l'oiseau ne s'est ni crashé dans un tuyau(b vrai) ni dans une paroi(c vrai)
		{

			t.reset();  //Remise à zero du chrono

			ifstream score(srcPath("savegame.txt")); //MISE A 
			score >> best;							 //JOUR 
			score.close();							 //MEILLEUR SCORE


			///////CREATION OBSTACLES ET PIECES
			if (n == 0 || obs[n - 1].getx() < width2 - 600) //on crée un obstacle si le dernier est suffisament avancé (dans le tiers gauche). Le rand() sert à ne pas avoir une distnce constante entre deux obstacles
			{
				n++;
				obs[n - 1].setx(width2 + 50 * double(rand()) / RAND_MAX);
				obs[n - 1].sety(double(rand()) / RAND_MAX*(height2 - 200));
				u = double(rand()) / RAND_MAX;
				v = double(rand()) / RAND_MAX;
				h = 145+15 * sqrt(-2 * log(u))*cos(2 * M_PI*v);//loi gaussienne pour l'epaisseur (pour éviter qu'il y ait trop de trucs large, mais un peu quand même
				if (h < 120)
					obs[n - 1].seth(120); 
				else
					obs[n - 1].seth(h);

				u = rand() % 7 ; //lorsqu'on crée un obstacle, il y a une chance sur 3 de créer une pièce située à une hauteur aléatoire
				if (u == 0){
					piece.existence(true);
					u = double(rand()) / RAND_MAX;
					piece.setxy(obs[n-1].getx()+300, 30 + (height - 150)*u);
				}
			}


			noRefreshBegin();////////////////////////////////////////////////////// PARTIE AFFICHAGE

			putColorImage(IntPoint2(0, 0), fond, width2, height2); //On affiche le fond, ce qui efface tout l'écran précédent

			///////DETECTION CLAVIER
			if (Clavier())
			{
				if (p.getvy() > 0)
					p.saut(jump);
				else
					p.saut(jump - p.getvy());
			}
			//////

			////////////GESTION MOUVEMENT DE L'ENSEMBLE DES OBJETS

			if (piece.existe() && piece.cadre())    //PIECE (si il y en a une)
			{
				piece.bouger(-vx);
				piece.afficher();
			}

			p.bouger();  //MOUVEMENT
			p.afficher();//OISEAU

			if (!obs[0].cadre()) //si l'obstacle sort de la fenêtre, on le sort de la liste et on décale tout
			{
				for (int i = 0; i < n; i++)
					obs[i] = obs[i + 1];
				n--;
				booleen = false;
			}

			if ((obs[0].getx() + obs[0].getl() < x0) && !booleen)//si on passe un obstacle (forcément le premier de la liste) alors on incrémente le compteur
			{ 
				compteur++;
				booleen = true; //le booléen est là pour dire que l'obstacle à gauche de l'oiseau a déjà été compté
			}

			for (int i = 0; i < n; i++)
			{
				obs[i].bouger(-vx);
				if (obs[i].cadre()) //on affiche l'obstacle i  si il est dans la fenêtre
					obs[i].afficher();
			}
			////////////////////////


			drawString(5, 60, to_string(compteur), Color(255, 100, 0), 45, 0, false, true);   //AFFICHAGE SCORE
			drawString(12, 60 + 50, to_string(best), Color(255, 100, 0), 30, 0, false, true); //ET MEILLEUR SCORE

			noRefreshEnd();
			///////////////////FIN PARTIE AFFICHAGE


			/////DETECTION COLLISIONS
			c = !((p.gety() > 0) && (p.gety() < height2 - p.geth())); //vrai si l'oiseau est hors cadre 

			b = obs[0].test(p); //Un seul obstacle dans l'écran (dans le format actuel)

			if (piece.test(p) && piece.existe())
			{ //si on passe sur une pièce, on la fait disparaître, et on donne un point au joueur
				piece.existence(false);
				compteur++;
			}
			///////////


			if (300 * dt - 1000 * t.lap()>0)  //pour éviter que ça freeze si la boucle met trop de temps à s'executer
				milliSleep(300 * dt - 1000 * t.lap()); //on essaie d'être le plus régulier possible


			if (compteur > best) //Si on bat le meilleur score, on le met constamment à jour
			{
				ofstream score(srcPath("savegame.txt")); //ECRITURE
				score << compteur;						 //MEILLEUR SCORE
				score.close();                           //DANS FICHIER TXT
			}
		}     

		but = false;

		bouton_rejouer.afficher();	   
		bouton_quitter.afficher();										 //  		                         
		while (!but)						                             // GESTION
		{                                                                //
			getMouse(X, Y);					                             // BOUTONS
			but = bouton_rejouer.test(X,Y)||bouton_quitter.test(X,Y);    // REJOUER
		}								                                 // ET QUITTER
		if (bouton_rejouer.test(X, Y))
		{
			bouton_rejouer.clic();
			compteur = 0;//on réinitialise tout pour rejouer
			p.reset(x0, height2 / 2);
			b = false;
			c = false;
			for (int i = 0; i < n; i++)
				obs[i] = obs[i + 1];
			n--;
			booleen = false;
			piece.existence(false);
		}
		else
		{
			bouton_quitter.clic();
			quitter = true;
			closeWindow(W1);
		}
	}while (!quitter);  //fin boucle jeu
	return 0;
}

