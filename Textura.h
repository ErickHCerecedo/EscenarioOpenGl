#ifndef TEXTURA_H
#define TEXTURA_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include <GL/glext.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "FreeImage.h"

#define NTextures 9

class Textura
{
  public:
    Textura();
    virtual ~Textura();

    bool readImage();

    FreeImage_Initialise();

    GLuint texture[NTextures];
    //variables para manejo de texturas
    char *texturefiles[NTextures] = {
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/imagen1.bmp",         //0
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/imagen2.bmp",         //1
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/imagen3.bmp",         //2

      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/img/Midday_Front.png",//3
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/img/Midday_Right.png",//4
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/img/Midday_Left.png", //5
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/img/Midday_Back.png", //6
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/img/Midday_Up.png",   //7
      "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/img/Midday_Down.png", //8
    };

  protected:

  private:



};

#endif // TEXTURA_H
