#ifndef FACE_H
#define FACE_H
#pragma once
	
#include <vector>
#include "Vertex.hpp"

using namespace std;

class Face  
{
	private:
	    vector<unsigned int> vertex_ind;
		float A, B, C, D;
	public:
	    //vector<unsigned int> vertex_ind;
		Face(vector<unsigned int> vertex_ind);
		void print();
		vector<unsigned int> get_fverts();
		void calculate_plane_eq(Vertex V1, Vertex V2, Vertex V3);
		arma::frowvec3 get_normal();
};
#endif