#include "../include/Transf.hpp"
#include "../include/Vertex.hpp"

#define PI 3.14159265

Transf::Transf()
{
    
}

arma::Mat<double> Transf::T(double dx, double dy, double dz)
{
    arma::Mat<double> t = {{1, 0, 0, dx},
                           {0, 1, 0, dy},
                           {0, 0, 1, dz},
                           {0, 0, 0, 1}};
    return(t);
}
arma::Mat<double> Transf::S(double sx, double sy, double sz)
{
    arma::Mat<double> s = {{sx, 0, 0, 0},
                           {0, sy, 0, 0},
                           {0, 0, sz, 0},
                           {0, 0, 0, 1}};
    return(s);
}
arma::Mat<double> Transf::Rx(double theta)
{
    double ct = cos(theta * PI / 180);
    double st = sin(theta * PI / 180);

    arma::Mat<double> rx = {{1, 0, 0, 0},
                           {0, ct, -st, 0},
                           {0, st, ct, 0},
                           {0, 0, 0, 1}};
    return(rx);

}
arma::Mat<double> Transf::Ry(double theta)
{
    double ct = cos(theta * PI / 180);
    double st = sin(theta * PI / 180);

    arma::Mat<double> ry = {{ct, 0, st, 0},
                           {0, 1, 0, 0},
                           {-st, 0, ct, 0},
                           {0, 0, 0, 1}};
    return(ry);
}
arma::Mat<double> Transf::Rz(double theta)
{
    double ct = cos(theta * PI / 180);
    double st = sin(theta * PI / 180);

    arma::Mat<double> rz = {{ct, -st, 0, 0},
                           {st, ct, 0, 0},
                           {0, 0, 1, 0},
                           {0, 0, 0, 1}};
    return(rz);

}

arma::Mat<double> Transf::Rp1p2(Vertex P1, Vertex P2, double theta)
{
    //Paso 1
    arma::Mat<double> T = this->T(-P1.get_x(), -P1.get_y(), - P1.get_z());

    //Paso 2
    float z2p = P2.get_z() - P1.get_z();
    float x2p = P2.get_x() - P1.get_x();
    double D1 = sqrt(pow(z2p,2) + pow(x2p,2));
    arma::Mat<double> Ry = {{z2p/D1, 0, -x2p/D1, 0},
                            {0, 1, 0, 0},
                            {x2p/D1, 0, z2p/D1, 0},
                            {0, 0, 0, 1}};

    //Paso 3
    float y2p = P2.get_y() - P1.get_y();
    double D2 = sqrt(pow(x2p,2) + pow(y2p,2) + pow(z2p,2));

    arma::Mat<double> Rx = {{1, 0, 0, 0},
                            {0, D1/D2, -y2p/D2, 0},
                            {0, y2p/D2, D1/D2, 0},
                            {0, 0, 0, 1}};

    //Paso 4
    arma::Mat<double> Rz = this->Rz(theta);

    //Paso 5
    arma::Mat<double> iRx = arma::inv(Rx);

    //PAso 6
    arma::Mat<double> iRy = arma::inv(Ry);

    //Paso 7
    arma::Mat<double> iT = arma::inv(T);

    return(iT*iRy*iRx*Rz*Rx*Ry*T);

}
