#include<Imagine/Graphics.h>
using namespace Imagine;
#include "Classes.h"

void Piaf::setpos(int X, int Y){
	x = X;
	y = Y;
}
void Piaf::setv(double vX, double vY){
	vx = vX;
	vy = vY;
}
int Piaf::getw(){
	return w;
}
int Piaf::geth(){
	return h;
}
double Piaf::getx(){
	return x;
}
double Piaf::gety(){
	return y;
}
double Piaf::getvx(){
	return vx;
}
double Piaf::getvy(){
	return vy;
}
void Piaf::saut(double dy){
	vy += -dy;
}
void Piaf::bouger(){
	vy =(abs(vy)>lim)?vy/(abs(vy))*lim:(vy+ m*g*dt);
	x += vx*dt;
	y += vy*dt;
	if (vy < -lim/2)
		pos = 0;
	else if (vy<0)
		pos = 1;
	else if (vy < lim / 4)
		pos = 2;
	else if (vy < lim / 2)
		pos = 3;
	else if (vy < 3 * lim / 4)
		pos = 4;
	else if (vy < lim)
		pos = 5;
	else 
		pos = 6;
}

Piaf::Piaf(double X, double Y, double vX, double M){
	setpos(X, Y);
	setv(vX, 0);
	loadColorImage(srcPath("Oiseau0.jpg"), I0, w, h);
	loadColorImage(srcPath("Oiseau1.jpg"), I1, w, h);
	loadColorImage(srcPath("Oiseau2.jpg"), I2, w, h);
	loadColorImage(srcPath("Oiseau3.jpg"), I3, w, h);
	loadColorImage(srcPath("Oiseau4.jpg"), I4, w, h);
	loadColorImage(srcPath("Oiseau5.jpg"), I5, w, h);
	loadColorImage(srcPath("Oiseau6.jpg"), I6, w, h);
	m = M;
	pos = 1;
}
void Piaf::afficher(){
	if (pos==0)
		putColorImage(IntPoint2(x, y), I0, w, h);
	if (pos==1)
		putColorImage(IntPoint2(x, y), I1, w, h);
	if (pos==2)
		putColorImage(IntPoint2(x, y), I2, w, h);
	if (pos == 3)
		putColorImage(IntPoint2(x, y), I3, w, h);
	if (pos == 4)
		putColorImage(IntPoint2(x, y), I4, w, h);
	if (pos == 5)
		putColorImage(IntPoint2(x, y), I5, w, h);
	if (pos == 6)
		putColorImage(IntPoint2(x, y), I6, w, h);
}

void Piaf::effacer()
{
	putColorImage(IntPoint2(x, y), I1, w, h);
}

void Piaf::reset(int X, int Y){
	setpos(X,Y);
	setv(vx, 0);
}