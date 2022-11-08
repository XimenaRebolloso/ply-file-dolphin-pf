#include "../include/Delfin.hpp"
#include "../include/Transf.hpp"
#include "../include/Curva.hpp"
#include <iostream>
#include <vector>
#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

using namespace std;

Delfin::Delfin(string file, float r, float g, float b, float ka, float kd): Object(file)
{
    this->matrix = arma::eye(4, 4);
    this->r = r;
    this->g = g;
    this->b = b;
    this->ka = ka;
    this->kd = kd;
}

void Delfin::set_transf(arma::Mat<double> transf)
{
    this->matrix = transf;
}

void Delfin::dibuja(float Ia, float Ip, arma::frowvec3 F)
{
    vector<Face> objeto_faces = this->get_faces();
    vector<Vertex> objeto_vertices = this->get_vertices();

    glBegin(GL_TRIANGLES);
    for (Face f : objeto_faces)
    {
        arma::frowvec3 N = f.get_normal();
        arma::frowvec3 V = {objeto_vertices[f.get_fverts()[0]].get_x(),
                            objeto_vertices[f.get_fverts()[0]].get_y(),
                            objeto_vertices[f.get_fverts()[0]].get_z(),
                           };
        
        arma::frowvec3 L = F - V;
        L = arma::normalise(L);

        float costheta = arma::dot(N,L);

        float I = (Ia * this->ka) + (Ip * this->kd * costheta) ; 

        float rn = this-> r * I;
        float gn = this-> g * I;
        float bn = this-> b * I;

        glColor3f(rn, gn, bn);
        // Recorrer los vértices de la cara
        for (long v_ind : f.get_fverts())
        {
            // Dibujar el objeto....
            arma::Col<double> vp = this->matrix * objeto_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
}
