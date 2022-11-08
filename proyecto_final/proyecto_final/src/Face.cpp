#include <iostream>
#include <vector>
#include <armadillo>
#include "../include/Face.hpp"
#include "../include/Vertex.hpp"

Face::Face(vector<unsigned int> vertex_ind)
{
    this->vertex_ind = vertex_ind;
}

void Face::print()
{
    /*for (int i = 0; i < vertex_ind.size(); i++)
    {
        cout << vertex_ind[i] << " ";
    }
    cout << endl;*/
    cout << "Equación del plano; ";
    cout << this->A << "x + ";
    cout << this->B << "y + ";
    cout << this->C << "z + ";
    cout << this->D << "= 0 " << endl;
    cout << endl;
}

vector<unsigned int> Face::get_fverts()
{
    return(this->vertex_ind);
}

void Face::calculate_plane_eq(Vertex V1, Vertex V2, Vertex V3)
{
    Vertex V2V1 = Vertex (V2.get_x()-V1.get_x(), V2.get_y()-V1.get_y(), V2.get_z()-V1.get_z());
    Vertex V3V1 = Vertex (V3.get_x()-V1.get_x(), V3.get_y()-V1.get_y(), V3.get_z()-V1.get_z());
    this->A = (V2V1.get_y()*V3V1.get_z()) - (V2V1.get_z()*V3V1.get_y());
    this->B = (V2V1.get_z()*V3V1.get_x()) - (V2V1.get_x()*V3V1.get_z());
    this->C = (V2V1.get_x()*V3V1.get_y()) - (V2V1.get_y()*V3V1.get_x());
    this->D = -((A*V1.get_x()) + (B*V1.get_y()) + (C*V1.get_z()));
}

arma::frowvec3 Face::get_normal()
{
    arma::frowvec3 N = {this->A, this->B, this->C};

    N = arma::normalise(N);
    return(N);
}