#include<iostream>
using namespace std;
#include<Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Common.h>
#include "Classes.h"
#include "Fonctions.h"

Bouton::Bouton(string S, int X, int Y, int W, int H, Color C1, Color C2,int T){
	s1 = S;
	x = (width-W)/2;
	y = Y;
	w = W;
	h = H;
	c1 = C1;
	c2 = C2;
	t = T;
	b = false;
	
}
Bouton::Bouton(std::string s1, std::string s2, int X, int Y)
{
	loadColorImage(stringSrcPath(s1) , I1, w, h);
	loadColorImage(stringSrcPath(s2), I2, w, h);
	x = X;
	y = Y;
	b = true;
}

Bouton::~Bouton(){
	delete[] I1;
	delete[] I2;
}

void Bouton::afficher(){
	if (!b)
		drawString(IntPoint2(x, y), s1, c1, t);
	else
		putColorImage(IntPoint2(x, y), I1, w, h);
}

void Bouton::clic(){
	afficher();
	if (!b){
		drawString(IntPoint2(x, y), s1, c2, t);
		milliSleep(150);
		drawString(IntPoint2(x, y), s1, c1, t);
		milliSleep(30);
	}
	else
	{
		putColorImage(IntPoint2(x, y), I2, w, h);
		milliSleep(150);
		putColorImage(IntPoint2(x, y), I1, w, h);
		milliSleep(30);
	}
}
bool Bouton::test(){
	int X=0, Y=0;
	getMouse(X, Y);
	return(X > x && X<x + w && Y>y && Y<y+h);
}

bool Bouton::test(int X, int Y){
	return(X > x && X<x + w && Y>y && Y<y + h);
}

void Bouton::setw(int W){
	w = W;
	x = (width - w) / 2;
}

void Bouton::setText(std::string S){
	s1 = S;
}

void Bouton::setImage(std::string S1, std::string S2){
	loadColorImage(stringSrcPath(S1), I1, w, h);
	loadColorImage(stringSrcPath(S2), I2, w, h);
}