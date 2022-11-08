#ifndef DELFIN_H
#define DELFIN_H
#pragma once

#include <string>
#include <vector>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "Object.hpp"
#include "Transf.hpp"

using namespace std;

class Delfin : public Object
{
    public:
	Delfin(string file, float r, float g, float b, float ka, float kd);
	void set_transf(arma::Mat<double> transf);
	void dibuja(float Ia, float Ip, arma::frowvec3 F);
	
	private: 
	arma::Mat<double> matrix;
	float r, g, b;
	float ka, kd;
};
#endif