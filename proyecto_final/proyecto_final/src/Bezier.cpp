#include "../include/Bezier.hpp"
#include <armadillo>

Bezier::Bezier(Vertex P1, Vertex P2, Vertex P3, Vertex P4)
{
    this->pcurva = {};
    double dt = 0.1;
    // Curvas de Bezier
    arma::Mat<double> MB = {{-1, 3, -3, 1},
                        {3, -6, 3, 0},
                        {-3, 3, 0, 0},
                        {1, 0, 0 , 0}};

    arma::Mat<double> GB = {{P1.get_x(), P1.get_y(), P1.get_z()},
                            {P2.get_x(), P2.get_y(), P2.get_z()},
                            {P3.get_x(), P3.get_y(), P3.get_z()},
                            {P4.get_x(), P4.get_y(), P4.get_z()}};
    
    for (double t = 0.0; t <= 1.0+dt; t+=dt)
    {
        arma::Row<double> T = {pow(t,3), pow(t,2), t, 1};
        arma::Row<double> Qt = T * MB * GB; 
        this->pcurva.push_back(Vertex(Qt[0], Qt[1], Qt[2]));
        //cout << "t=" << t << "   " << T * MB * GB << endl;
    }

}

vector <Vertex> Bezier::curva()
{
    return(this->pcurva);
}

