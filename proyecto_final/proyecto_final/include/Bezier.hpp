#ifndef BEZIER_H
#define BEZIER_H

#pragma once


#include <vector>
#include "Vertex.hpp"

using namespace std;

class Bezier
{
public:
    Bezier(Vertex P1, Vertex P2, Vertex P3, Vertex P4);
    vector<Vertex> curva();
private:
    vector<Vertex> pcurva;
};

#endif