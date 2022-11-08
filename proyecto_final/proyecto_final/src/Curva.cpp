#include "../include/Vertex.hpp"
#include "../include/Line.hpp"
#include "../include/Bezier.hpp"
#include "../include/Curva.hpp"
#include "../include/Transf.hpp"
#include <cstdlib>
#include <ctime>
#include <armadillo>

using namespace std;

Curva::Curva(double V1x, double V1y, double V1z, double V2x, double V2y, double V2z)
{
    Vec1x = V1x;
    Vec1y = V1y;
    Vec1z = V1z;
    Vec2x = V2x;
    Vec2y = V2y;
    Vec2z = V2z;
}

vector<Vertex> Curva::set_curva()
{
    Vertex V1(Vec1x, Vec1y, Vec1z);
    Vertex V2(Vec2x, Vec2y, Vec2z);
    double t = 1.0;

    Vertex P1 = V1;
    Line l;
    Vertex P2 = l.line_t(V1, V2, t);
    Vertex P3(P2.get_x() * t, P2.get_y(), P2.get_z());
    Vertex P4(P2.get_x() * (2 * t), 0, P2.get_z());

    Bezier bz(P1, P2, P3, P4);
    return (bz.curva());
}

arma::Mat<double> Curva::set_tranf(double escala, vector<Vertex> curva, int poscurv, Transf Tr)
{
    arma::Mat<double> S = Tr.S(escala, escala, escala);
    arma::Mat<double> T1 = Tr.T(curva[poscurv].get_x(),
                                 curva[poscurv].get_y(),
                                 curva[poscurv].get_z());
    return(T1*S);
}