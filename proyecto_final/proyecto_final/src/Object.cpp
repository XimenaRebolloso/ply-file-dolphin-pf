#include "../include/Object.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

Object::Object(string file)
{

    string line;

    vector<Vertex> vertices = {};
    vector<Face> faces = {};

    ifstream archivo(file);

    int nVertex, nFaces;

    // floats para los vertices
    float fx, fy, fz;

    // auxiliares para las caras y los vertices
    int auxV = 0;
    int auxF = 0;
    int auxnf = 0;

    // banderas para leer el archivo
    int band = 0, bandv = 0;

    // contadores
    int nv = 0, nf = 0, i;

    // indices de los vertices para las caras
    vector<unsigned int> indexVertex;
    unsigned int auxindV;

    while (getline(archivo, line))
    {
        vector<string> words = splitSingle(line, ' ');
        // cout << words[0] << endl;

        // Aqui se puede saber cuantos vertices tiene
        if (words[0] == "element" && words[1] == "vertex")
        {
            nVertex = stof(words[2]);
            // cout << nVertex << endl;
        }
        // Aqui se puede saber cuantas caras tiene
        if (words[0] == "element" && words[1] == "face")
        {
            nFaces = stof(words[2]);
            // cout << nFaces << endl;
        }
        if (line == "end_header")
        {
            band = 1;
        }
        // Aqui si la bandera esta levantada y la linea es diferente a end_header donde
        // empiezan despues los vertices y las caras.
        if (band == 1 && line != "end_header")
        {
            if (nv < nVertex)
            {
                // Vertices
                fx = stof(words[0]);
                fy = stof(words[1]);
                fz = stof(words[2]);
                // cout << fx << " " << fy << " " << fz << endl;
                Vertex v(fx, fy, fz);
                vertices.push_back(v);
                nv++;
            }
            // la bandera se levanta cuando se llega al final de los vertices
            bandv = 1;
        }

        if (bandv == 1 && ((stof(words[0])) == words.size() - 1))
        {
            // Este es el numero de caras (auxnf)
            auxnf = words.size();
            // Primer ciclo para ir de la primera cara a la ultima
            if (nf < nFaces)
            {
                //Segundo ciclo para ir sobre los elementos de las caras
                for (i = 0; i < auxnf; i++)
                {
                    auxindV = stof(words[i]);
                    //Se añaden a un vector de unsigned ints 
                    indexVertex.push_back(auxindV);
                }

                //Se crea la cara con el vector de unsigned ints
                Face f(indexVertex);
                f.calculate_plane_eq(vertices[indexVertex[0]],
                                     vertices[indexVertex[1]],
                                     vertices[indexVertex[2]]);
                faces.push_back(f);

                //Esta parte, se limpia el vector de los indicies para que se pueda volver a usar 
                //Después que durante bastante tiempo se estaban agregando todos los elementos al mismo 
                //vector y no se podia hacer las caras 
                indexVertex.clear();

                //Se pasa a la siguiente linea
                nf++;
            }
        }
    }
    this->vertices = vertices;
    this->faces = faces;
}

//Esto es todo, se espera que funcione bien.

//Funcion tokenizer, previamente se utilizaba una donde el delimitador era un string
//Ya que con los archivos .obj habia en ocasiones dos delimitadores entre los elementos que importaban 
vector<string> Object::splitSingle(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void Object::print()
{
    /*cout << "ply" << endl;
    cout << "format ascii 1.0" << endl;
    cout << "element vertex " << vertices.size() << endl;
    cout << "property float x" << endl;
    cout << "property float y" << endl;
    cout << "property float z" << endl;
    cout << "element face " << faces.size() << endl;
    cout << "property list uchar uint vertex_indices" << endl;
    cout << "end_header" << endl;
    for (Vertex v : this->vertices)
    {
        v.print();
    }*/
    for(Face f : this->faces)
    {
        f.print();
    }
}

vector<Face> Object::get_faces()
{
    return(this->faces);
}

vector<Vertex> Object::get_vertices()
{
    return(this->vertices);
}