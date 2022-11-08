#ifndef ONJECT_H
#define OBJECT_H
#pragma once

#include <string>
#include <vector>
#include "Vertex.hpp"
#include "Face.hpp"

using namespace std;

class Object 
{
    private:
        vector<string> splitSingle (const string &s, char delim);
        vector<Face> faces;
        vector<Vertex> vertices;
    protected:
        Object(string file);
        void print();
        vector<Face> get_faces();
        vector<Vertex> get_vertices();
         
};
#endif