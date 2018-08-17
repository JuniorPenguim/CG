#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

void displayCheio(void);
void displayVazio(void);
void displayVazioCheio(void);
void displayPoligono(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (640, 640);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercicio 1 Test");
   init ();
   glutDisplayFunc(displayCheio);
   glutKeyboardFunc(keyboard);
   
   


   printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}



// É a rotina chamada automaticamente sempre que a
// janela ou parte dela precisa ser redesenhada
void displayCheio(void)
{


   // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   // Desenhar um triângulo vermelho
   glBegin(GL_TRIANGLES);

      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.5, 0.0, 0.0);
      glVertex3f (0.25, 0.5, 0.0);


   glEnd();

   
   glutSwapBuffers ();
}

void displayVazio(void)
{


   // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();


   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // Desenhar um triângulo vermelho
   glBegin(GL_TRIANGLES);

      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.5, 0.0, 0.0);
      glVertex3f (0.25, 0.5, 0.0);


   glEnd();

   
   glutSwapBuffers ();
}

void displayVazioCheio(void)
{


   // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   // Desenhar um triângulo vermelho cheio
   glBegin(GL_TRIANGLES);

      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (-0.5, 0.0, 0.0);
      glVertex3f (-0.25, -0.5, 0.0);


   glEnd();

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // Desenhar um triangulo vermelho vazio
   glBegin(GL_TRIANGLES);

      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.5, 0.0, 0.0);
      glVertex3f (0.25, 0.5, 0.0);


   glEnd();

   
   glutSwapBuffers ();
}

void displayPoligono(void)
{


   // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   // Desenhar um triângulo vermelho
   glBegin(GL_LINE_STRIP);


      glColor3f  (0.0, 0.0, 0.0);
      glVertex3f (-0.25, 0.5, 0.0);
      glVertex3f (-0.5, 0.0, 0.0);
      glVertex3f (-0.25, -0.5, 0.0);
      glVertex3f (0.25, -0.5, 0.0);
      glVertex3f (0.5, 0.0, 0.0);
      glVertex3f (0.25, 0.5, 0.0);
      


   glEnd();

   
   glutSwapBuffers ();
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (1.0, 1.0, 1.0, 1.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Inicializa com matriz identidade
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 'A':
      case 'a':
         
         glutDisplayFunc(displayCheio);
         glutIdleFunc(displayCheio);

         break;

      case 'S':
      case 's':

         
         glutDisplayFunc(displayVazio);
         glutIdleFunc(displayVazio);
         
      break;

      case 'D':
      case 'd':
         
         glutDisplayFunc(displayVazioCheio);
         glutIdleFunc(displayVazioCheio);
      break;

      case 'F':
      case 'f':
         
         glutDisplayFunc(displayPoligono);
         glutIdleFunc(displayPoligono);

      break;

      case 27:
        exit(0);
      break;


   }
}