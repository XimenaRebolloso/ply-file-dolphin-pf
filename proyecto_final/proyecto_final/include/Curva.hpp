#ifndef CURVA_H
#define CURVA_H

#pragma once

#include "Bezier.hpp"
#include "Vertex.hpp"
#include "Transf.hpp"
#include "Line.hpp"

using namespace std;

class Curva
{
    public:
    Curva(double V1x, double V1y, double V1z, double V2x, double V2y, double V2z);
    vector<Vertex> set_curva();
    arma::Mat<double> set_tranf(double escala, vector <Vertex> curva, int poscurv, Transf Tr);

    private:
    double Vec1x, Vec1y, Vec1z, Vec2x, Vec2y, Vec2z;

};
#endif