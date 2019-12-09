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
      void dibujarObjeto(float radio, float _ESCALA, float _STAY_X, float _STAY_Y, float _STAY_Z, float _ROTATION, float _X, float _Y, float _Z);

      // Dibuja cada objeto
      void escalar();
      void transladar();
      void rotar();

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

      float STAY_X, STAY_Y, STAY_Z;
      float ESCALA;
      float ROTATION;
      float X,Y,Z;
      float points[5][3]={{0,0,10},{10,0,10},{10,0,0},{0,0,0},{5.0,10.0,5.0}};

};

#endif // OBJETOS_H
