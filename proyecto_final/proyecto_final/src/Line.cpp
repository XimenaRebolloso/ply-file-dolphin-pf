#include "../include/Line.hpp"

Line::Line()
{
    
}

Vertex Line::line_t(Vertex v1, Vertex v2, double t)
{
    float x = v1.get_x() + t * (v2.get_x() - v1.get_x());
    float y = v1.get_y() + t * (v2.get_y() - v1.get_y());
    float z = v1.get_z() + t * (v2.get_z() - v1.get_z());
    return(Vertex(x,y,z));
}