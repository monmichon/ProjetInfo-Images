#include<iostream>
using namespace std;
#include<Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Common.h>
#include "Classes.h"
#include "Fonctions.h"

Bouton::Bouton(std::string s1, std::string s2, int X, int Y)
{
	loadColorImage(stringSrcPath(s1), I1, w, h);
	loadColorImage(stringSrcPath(s2), I2, w, h);
	x = X;
	y = Y;
}

Bouton::~Bouton(){
	delete[] I1;
	delete[] I2;
}

void Bouton::afficher(){
	putColorImage(IntPoint2(x, y), I1, w, h);
}

void Bouton::clic(){
	afficher();
	putColorImage(IntPoint2(x, y), I2, w, h);
	milliSleep(150);
	putColorImage(IntPoint2(x, y), I1, w, h);
	milliSleep(20);
}

bool Bouton::test(int X, int Y){
	return(X > x && X<x + w && Y>y && Y < y + h);
}

void Bouton::setImage(std::string S1, std::string S2){
	loadColorImage(stringSrcPath(S1), I1, w, h);
	loadColorImage(stringSrcPath(S2), I2, w, h);
}