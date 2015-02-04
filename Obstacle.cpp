#include<Imagine/Graphics.h>
using namespace Imagine;
#include "Classes.h"

Obstacle::Obstacle(){ //génère un obstacle hors de l'écran
	x = 2*width;
	h = 50;
	y = 350;
	int fondw, fondh;
	loadColorImage(srcPath("tuyau1.jpg"), I1, l,t);
	loadColorImage(srcPath("tuyau2.jpg"), I2, l, t);
	loadColorImage(srcPath("fond.jpg"), fond, fondw, fondh);
}
void Obstacle::afficher(){
	putColorImage(IntPoint2(x, y-t), I1,l,t);
	putColorImage(IntPoint2(x, y+h), I2, l, t);
}
void Obstacle:: effacer(){
	putColorImage(IntPoint2(x, y - t), I1, l, t);
	putColorImage(IntPoint2(x, y + h), I2, l, t);
	/*for (int i = -3; i < 3; i++){
		for (int j = 0; j < y; j++){
			drawPoint(IntPoint2(x + l-i,t-y+j), fond[x + l-i + (t-y+j)*l]);
		}
		for (int j = 0; j < t - y - h; j++){
			drawPoint(IntPoint2(x + l-i, y + h + j), fond[x + l-i + (y + h + j)*l]);
		}
	}*/
}
void Obstacle::bouger(double vx){
	x += vx*dt;
}

bool Obstacle::test(Piaf p){
	int W = p.getw();
	int H = p.geth();
	return((p.getx()< (x + l)) && (p.getx() > x-W)&& (p.gety()<y || p.gety()>y+h-H)); //si p est dans l'obstacle, on retourne true
}

void Obstacle::setx(double X){
	x = X;
}

void Obstacle::sety(double Y){
	y = Y;
}

void Obstacle::seth(double H){
	h = H;
}

bool Obstacle::cadre(){
	if ((x + l) < 0)
		return false;
	else return true;
}
double Obstacle::getx(){
	return x;
}