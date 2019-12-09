#ifndef OBJETOS_H
#define OBJETOS_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "../Textura.h"

#include <stdio.h>
#include "math.h"

class Objetos
{
    public:
      Objetos();
      Objetos(Textura*, int objeto);
      virtual ~Objetos();
      void setObjeto(int objeto);
      void dibujarObjeto(float radio);

      // Dibuja cada objeto
      void dibujaCono(float radio);
      void dibujaEsfera(float radio);
      void dibujaCubo(float radio);
      void dibujaPiramide(float radio);
      void dibujarSkyBox(float radio);

      // Textura
      Textura *textura;

    protected:

    private:
      // Lista de objetos
      bool CONO=false;
      bool ESFERA=false;
      bool CUBO=false;
      bool PIRAMIDE=false;
      bool SKYBOX=false;

      int STAY_X, STAY_Y, STAY_Z;
      int SIZE;
      float points[5][3]={{0,0,10},{10,0,10},{10,0,0},{0,0,0},{5.0,10.0,5.0}};

};

#endif // OBJETOS_H
