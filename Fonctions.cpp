#include<iostream>
using namespace std;
#include<Imagine/Graphics.h>
using namespace Imagine;
#include "Classes.h"
#include "Fonctions.h"
#include <Imagine/Common.h>

bool Clavier() {
    Event e;
    getEvent(0.5, e);
    return(e.type == EVT_KEY_ON);
}
