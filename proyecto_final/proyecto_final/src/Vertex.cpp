#include <iostream>
#include "../include/Vertex.hpp" 

using namespace std; 
	
Vertex::Vertex()
{
	//x = y = z = 0.0;
}

Vertex::Vertex(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vertex::get_x()
{
    return(this->x);
}

float Vertex::get_y()
{
    return(this->y);
}

float Vertex::get_z()
{
    return(this->z);
}

void Vertex::print()
{
    cout << this->x << " " << this->y << " " << this->z << endl;

}

//Representar una coordenada homogenea 
arma::Col<double> Vertex::homg()
{
    arma::Col<double> h = {this->x, this->y, this->z, 1};
    return(h);
}
