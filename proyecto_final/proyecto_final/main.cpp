#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "include/Object.hpp"
#include "include/Transf.hpp"
#include "include/Delfin.hpp"
#include "include/Bezier.hpp"
#include "include/Line.hpp"
#include "include/Curva.hpp"
#include "include/Sol.hpp"

using namespace std;

int main(void)
{
    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};

    GLFWwindow *window;
    int camc = 0;
    int modec = 2;

    if (!glfwInit())
    {
        cout << stderr << "Fallo al inicializar GLFW." << endl;
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Proyecto: Delfines saltando", NULL, NULL);
    if (window == NULL)
    {
        cout << stderr << "Fallo al abrir la ventana de GLFW." << endl;
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

    //  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

    //  Proyección en perspectiva
    //  glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // d1 = delfin1

    Delfin delfin1 = Delfin("models/delfinv7.ply", 0.0, 0.0, 1.0, 0.9, 0.8);
    Delfin delfin2 = Delfin("models/delfinv7.ply", 0.0, 0.0, 1.0, 0.5, 0.5);
    Sol sol = Sol("models/sol.ply", 0.5, 0.5, 0.0, 1.0, 1.0);

    //-0.75, 0.0, 0.0, 0.0, 0.75, 0.0
    Curva curvd1 = Curva(-0.70, -.75, 0.0, 0.0, 0.75, 0.0);
    vector<Vertex> curvaDelf1 = curvd1.set_curva();

    //-0.5, 0.0, -0.5, 0.0, 0.5, 0.0
    Curva curvd2 = Curva(-0.5, 0.0, -0.5, 0.0, 0.5, 0.0);
    vector<Vertex> curvaDelf2 = curvd2.set_curva();

    Transf Tr1 = Transf();
    Transf Tr2 = Transf();
    Transf TSol = Transf();

    int pos_curvad1 = 0;
    int pos_curvad2 = 0;

    int tecla = 0;

    float Ia = 0.9;
    arma::frowvec F = {0.0, 10.0, 0};
    float Ip = 0.8;

    do
    {
        tecla = glfwGetKey(window, GLFW_KEY_SPACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2],
                  camera[0], camera[1], camera[2],
                  0.0, 1.0, 0.0);
        if (tecla == GLFW_PRESS)
        {
            switch (modec)
            {
            case 1:
            {
                arma::frowvec temp = {10.0, 0.0, -10.0};
                eye = temp;
                modec = 2;
                break;
            }
            case 2:
            {
                arma::frowvec temp = {0.0, 0.0, 10.0};
                eye = temp;
                modec = 1;
                break;
            }
            }
        }
        if (camc < 8)
        {
            camc++;
        }
        // Dibujar el primer delfin
        arma::Mat<double> Transfd1 = curvd1.set_tranf(0.05, curvaDelf1, pos_curvad1, Tr1);
        if (pos_curvad1 < curvaDelf1.size() - 1)
        {
            pos_curvad1++;
        }
        delfin1.set_transf(Transfd1);
        delfin1.dibuja(Ia, Ip, F);

        sleep(1);
        // Fin dibujado el primer delfin

        // Dibujando el segundo delfin
        arma::Mat<double> Transfd2 = curvd2.set_tranf(0.05, curvaDelf2, pos_curvad2, Tr2);
        if (pos_curvad2 < curvaDelf2.size() - 1)
        {
            pos_curvad2++;
        }
        delfin2.set_transf(Transfd2);
        delfin2.dibuja(Ia, Ip, F);
        // fin dibujando el segundo delfin

        // Dibujando sol
        arma::Mat<double> S = TSol.S(0.4, 0.4, 0.4);
        arma::Mat<double> T = TSol.T(0.7, 0.7, 0.0);
        sol.set_transf(T * S);
        sol.dibuja(Ia, Ip, F);
        // fin dibujando el sol

        glfwSwapBuffers(window);
        glfwPollEvents();
        // cout << "El delfin " << endl;
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}
