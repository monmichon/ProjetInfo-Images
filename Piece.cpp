#include<iostream>
using namespace std;
#include<Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Common.h>
#include "Classes.h"
#include "Fonctions.h"
 

Piece::Piece(int X, int Y, int TYPE){
	x = X;
	y = Y;
	type = TYPE;
	loadColorImage(srcPath("Piece.jpg"), I, w, h);
	b = false;
}

Piece::~Piece(){
	delete[] I;
}

void Piece::afficher(){
	putColorImage(IntPoint2(x, y), I, w, h);
}

void Piece::bouger(int vx){
	x += vx*dt;
}

bool Piece::test(Piaf p){
	int W = p.getw();
	int H = p.geth();
	IntPoint2 p_centre(p.getx() + W / 2, p.gety() + H / 2);
	return((p_centre.x()>x-5) && (p_centre.x()<x+w+5) && (p_centre.y()>y-5) && (p_centre.y()<y+h+5));
}

void Piece::setxy(int X, int Y){
	x = X;
	y = Y;
}

bool Piece::cadre(){
		if ((x + w) < 0)
			return false;
		else 
			return true;
}

bool Piece::existe(){
	return b;
}

void Piece::existence(bool booleen){
	b = booleen;
}