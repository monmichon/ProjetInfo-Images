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
}
Piaf::Piaf(double X, double Y, double vX, double M){
	setpos(X, Y);
	setv(vX, 0);
	loadColorImage(srcPath("oiseau.jpg"), I, w, h);
	m = M;
}
void Piaf::afficher(){
	putColorImage(IntPoint2(x, y), I, w, h);
}

void Piaf::effacer()
{
	putColorImage(IntPoint2(x, y), I, w, h);
}

void Piaf::reset(int X, int Y){
	setpos(X,Y);
	setv(vx, 0);
}