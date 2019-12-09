#include "Objetos.h"

Objetos::Objetos()
{
  CONO=false;
  ESFERA=false;
  CUBO=false;
  PIRAMIDE=false;
  SKYBOX=false;
}

Objetos::Objetos(Textura * _textura, int objeto)
{
  CONO=false;
  ESFERA=false;
  CUBO=false;
  PIRAMIDE=false;
  SKYBOX=false;
  textura = _textura;
  setObjeto(objeto);

}

Objetos::~Objetos()
{
    //dtor
}

void Objetos::setObjeto(int objeto)
{
  if (objeto==1)
  {
    CONO=true;
  }
  else if (objeto==2)
  {
    ESFERA=true;
  }
  else if (objeto==3)
  {
    CUBO=true;
  }
  else if (objeto==4) {
    PIRAMIDE=true;
  }
  else if (objeto==5) {
    SKYBOX=true;
  }
}

void Objetos::dibujarObjeto(float radio) {
  if (CONO==true)
  {
    dibujaCono(radio);
  }
  else if (ESFERA==true)
  {
    dibujaEsfera(radio);
  }
  else if (CUBO==true)
  {
    dibujaCubo(radio);
  }
  else if (PIRAMIDE==true) {
    dibujaPiramide(radio);
  }
  else if (SKYBOX==true) {
    dibujarSkyBox(radio);
  }
}

void Objetos::dibujaCono(float radio)
{
  glPushMatrix();
    glRotatef(90.0, 1.0f, 0.0f, 0.0f);
    glColor3ub(121, 85, 72);
    //glutWireCone(radio,30,200,200);
    glutSolidCone(radio,30,30,30);
  glPopMatrix();
}

void Objetos::dibujaEsfera(float radio)
{
  glPushMatrix();
    glColor3ub(98, 101, 103);
    glutWireSphere(radio,200,200);
  glPopMatrix();
}

void Objetos::dibujaCubo(float radio)
{
  glPushMatrix();
    glColor3f(0.953, 0.624, 0.094);
    glutWireCube(50.0);
  glPopMatrix();
}

void Objetos::dibujaPiramide(float radio)
{
  glPushMatrix();
    glColor3f(0.953, 0.624, 0.094);
    glutWireSphere(20.0f,40,40);
  glPopMatrix();

  glPushMatrix();
  //glScalef(escala,escala,escala);
  int i;

  //activa la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura->texture[1]);
  glColor3ub(255, 255, 255);

     //se dibuja la punta
     for(i=0;i<3;i++){
        glBegin(GL_TRIANGLES);
           glTexCoord2f(0.5f,0.0f);
           glVertex3f(points[4][0],points[4][1],points[4][2]);
           glTexCoord2f(0.0f,1.0f);
           glVertex3f(points[i][0],points[i][1],points[i][2]);
           glTexCoord2f(1.0f,1.0f);
           glVertex3f(points[i+1][0],points[i+1][1],points[i+1][2]);
        glEnd();
        }

         glBegin(GL_TRIANGLES);
               glTexCoord2f(0.5f,0.0f);
               glVertex3f(points[4][0],points[4][1],points[4][2]);
               glTexCoord2f(0.0f,1.0f);
               glVertex3f(points[3][0],points[3][1],points[3][2]);
               glTexCoord2f(1.0f,1.0f);
               glVertex3f(points[0][0],points[0][1],points[0][2]);
         glEnd();


  glBegin(GL_QUADS);
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(points[0][0],points[0][1],points[0][2]);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(points[1][0],points[1][1],points[1][2]);
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(points[2][0],points[2][1],points[2][2]);
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(points[3][0],points[3][1],points[3][2]);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void Objetos::dibujarSkyBox(float radio)
{

  glPushMatrix();

    glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textura->texture[3]);
      glColor3ub(255, 255, 255);
      // Cuadro Frontal
      glBegin(GL_QUADS);
         glTexCoord2f(0.0f,1.0f);
         glVertex3f(radio,radio,radio);
         glTexCoord2f(1.0f,1.0f);
         glVertex3f(-radio,radio,radio);
         glTexCoord2f(1.0f,0.0f);
         glVertex3f(-radio,-radio,radio);
         glTexCoord2f(0.0f,0.0f);
         glVertex3f(radio,-radio,radio);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, textura->texture[5]);
      glColor3ub(255, 255, 255);
      // Cuadro Izquierda
      glBegin(GL_QUADS);
         glTexCoord2f(0.0f,1.0f);
         glVertex3f(-radio,radio,radio);
         glTexCoord2f(1.0f,1.0f);
         glVertex3f(-radio,radio,-radio);
         glTexCoord2f(1.0f,0.0f);
         glVertex3f(-radio,-radio,-radio);
         glTexCoord2f(0.0f,0.0f);
         glVertex3f(-radio,-radio,radio);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, textura->texture[4]);
      glColor3ub(255, 255, 255);
      // Cuadro Derecha
      glBegin(GL_QUADS);
         glTexCoord2f(0.0f,1.0f);
         glVertex3f(radio,radio,-radio);
         glTexCoord2f(1.0f,1.0f);
         glVertex3f(radio,radio,radio);
         glTexCoord2f(1.0f,0.0f);
         glVertex3f(radio,-radio,radio);
         glTexCoord2f(0.0f,0.0f);
         glVertex3f(radio,-radio,-radio);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, textura->texture[6]);
      glColor3ub(255, 255, 255);
      // Cuadro back
      glBegin(GL_QUADS);
         glTexCoord2f(0.0f,1.0f);
         glVertex3f(-radio,radio,-radio);
         glTexCoord2f(1.0f,1.0f);
         glVertex3f(radio,radio,-radio);
         glTexCoord2f(1.0f,0.0f);
         glVertex3f(radio,-radio,-radio);
         glTexCoord2f(0.0f,0.0f);
         glVertex3f(-radio,-radio,-radio);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, textura->texture[7]);
      glColor3ub(255, 255, 255);
      // Cuadro up
      glBegin(GL_QUADS);
         glTexCoord2f(0.0f,1.0f);
         glVertex3f(radio,radio,radio);
         glTexCoord2f(1.0f,1.0f);
         glVertex3f(-radio,radio,radio);
         glTexCoord2f(1.0f,0.0f);
         glVertex3f(-radio,radio,-radio);
         glTexCoord2f(0.0f,0.0f);
         glVertex3f(radio,radio,-radio);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, textura->texture[8]);
      glColor3ub(255, 255, 255);
      // Cuadro down
      glBegin(GL_QUADS);
         glTexCoord2f(0.0f,1.0f);
         glVertex3f(radio,-radio,radio);
         glTexCoord2f(1.0f,1.0f);
         glVertex3f(-radio,-radio,radio);
         glTexCoord2f(1.0f,0.0f);
         glVertex3f(-radio,-radio,-radio);
         glTexCoord2f(0.0f,0.0f);
         glVertex3f(radio,-radio,-radio);
      glEnd();

    glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}
