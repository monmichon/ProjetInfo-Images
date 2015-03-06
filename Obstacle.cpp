#include<Imagine/Graphics.h>
using namespace Imagine;
#include "Classes.h"


Obstacle::Obstacle(){ //génère un obstacle hors de l'écran
	x = 2*width;
	h = 50;
	y = 350;
	loadColorImage(srcPath("tuyau1.jpg"), I1, l,t);
	loadColorImage(srcPath("tuyau2.jpg"), I2, l, t);
}

void Obstacle::afficher(){
	putColorImage(IntPoint2(x, y-t), I1,l,t);
	putColorImage(IntPoint2(x, y+h), I2, l, t);
}
void Obstacle:: effacer(){
	putColorImage(IntPoint2(x, y - t), I1, l, t);
	putColorImage(IntPoint2(x, y + h), I2, l, t);
}
void Obstacle::bouger(double vx){
	x += vx*dt;
}

bool Obstacle::test(Piaf p){
	int W = p.getw();
	int H = p.geth();
	return((p.getx()< (x + l-5)) && (p.getx() > x-W+5)&& (p.gety()<y-5 || p.gety()>y+h-H+5)); //si p est dans l'obstacle, on retourne true
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
int Obstacle::getl(){
	return l;
}
