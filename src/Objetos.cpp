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
    //activa la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura->texture[1]);
    glColor3ub(255, 255, 255);

      glRotatef(90.0, 1.0f, 0.0f, 0.0f);
      //glColor3ub(121, 85, 72);
      //glutWireCone(radio,30,200,200);
      glTexCoord2f(0.0f,0.0f);
      glTexCoord2f(0.0f,1.0f);
      glTexCoord2f(1.0f,0.0f);
      glTexCoord2f(1.0f,1.0f);
      glutSolidCone(radio,30,30,30);


    glDisable(GL_TEXTURE_2D);

  glPopMatrix();
}

void Objetos::dibujaEsfera(float radio)
{
  /*
  glPushMatrix();
    glColor3ub(98, 101, 103);
    glutWireSphere(radio,200,200);
  glPopMatrix();
  */
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textura->texture[1]);
  glColor3ub(255, 255, 255);

        int i=0;
        int j=0;
        //float radio=50;
        float teta;
        float phi;
        int ResolucionEsfera=20;
        float porcentajex=0;
        float FinalPhi=2*M_PI;
        float FinalTeta=(float)M_PI;
        float porcentajey=1;
        float incrementox=(float)(1/((float)2*ResolucionEsfera)); //1/20
             float incrementoy=(float)(-1/((float)ResolucionEsfera)); //1/10
        float increRad=(float)(M_PI/ResolucionEsfera);
             float Vertice1x,Vertice1y, Vertice1z=0;
             float Vertice2x,Vertice2y, Vertice2z=0;
             float Vertice3x,Vertice3y, Vertice3z=0;
             float Vertice4x,Vertice4y, Vertice4z=0;
             //-----------\/---------Construcción de la esfera poco a poco---------------
             if(FinalPhi<2*M_PI)FinalPhi+=increRad/50;/*FinalPhi=2*PI;*/
             if(FinalTeta<M_PI)FinalTeta+=increRad/100;/*FinalTeta=(float)PI;*/
             //-----------/\---------Construcción de la esfera poco a poco---------------
        for(teta=0;teta<FinalTeta;teta+=increRad){
                for(phi=0;phi<FinalPhi;phi+=increRad){
                                  //VERTICE 1
                    Vertice1z=(radio)*((float) sin(teta))*((float)cos(phi));
                    Vertice1x=(radio)*((float) sin(teta))*((float)sin(phi));
                    Vertice1y=(radio)*((float) cos(teta));
                                  //VERTICE 2
                    Vertice2z=(radio)*((float) sin(teta+increRad))*((float)cos(phi));
                    Vertice2x=(radio)*((float) sin(teta+increRad))*((float)sin(phi));
                    Vertice2y=(radio)*((float) cos(teta+increRad));
                                  //VERTICE 3
                   Vertice3z=(radio)*((float) sin(teta+increRad))*((float)cos(phi+increRad));
                   Vertice3x=(radio)*((float) sin(teta+increRad))*((float)sin(phi+increRad));
                   Vertice3y=(radio)*((float) cos(teta+increRad));
                                  //VERTICE 4
                    Vertice4z=(radio)*((float) sin(teta))*((float)cos(phi+increRad));
                    Vertice4x=(radio)*((float) sin(teta))*((float)sin(phi+increRad));
                    Vertice4y=(radio)*((float) cos(teta));

  glNormal3f((float)1.5*sin(teta)*sin(phi),(float)1.5*cos(teta),(float)1.5*sin(teta)*cos(phi));

  glBegin(GL_TRIANGLES);
          //TRIANGULO 1
  glTexCoord2f(porcentajex, porcentajey);glVertex3f(Vertice1x, Vertice1y,Vertice1z);
  glTexCoord2f(porcentajex,porcentajey+incrementoy);glVertex3f(Vertice2x, Vertice2y,Vertice2z);
  glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);glVertex3f(Vertice3x,Vertice3y,Vertice3z);
                                        //TRIANGULO
  glTexCoord2f(porcentajex, porcentajey);glVertex3f(Vertice1x, Vertice1y,Vertice1z);
  glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);glVertex3f(Vertice3x, Vertice3y,Vertice3z);
  glTexCoord2f(porcentajex+incrementox,porcentajey);glVertex3f(Vertice4x, Vertice4y,Vertice4z);

  glEnd();

  porcentajex+=incrementox;
  }
  porcentajey+=incrementoy;
  porcentajex=0;
  }

    glDisable(GL_TEXTURE_2D);
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
