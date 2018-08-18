#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void display_6(void);
void display_12(void);
void display_180(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1920, 1080);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercicio 2 Test");
   init ();
   glutDisplayFunc(display_6);
   glutKeyboardFunc(keyboard);
   
   


	printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}



// É a rotina chamada automaticamente sempre que a
// janela ou parte dela precisa ser redesenhada
void display_6(void)
{


   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT);

   // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(360.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();
   

      
   for(float x = 0; x < 360; x = x + 60)
   {
      glBegin(GL_LINE_STRIP);

         float y = sin(x*((3.1415)/180));        
         glColor3f(0.0, 1.0, 0.0);
         glVertex2f(x, y);
         glVertex2f((x+60),sin((x+60)*((3.1415)/180)));

         
         
         glEnd();

      

      glutSwapBuffers ();
      
   }

  

}

void display_12(void)
{


   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT);

   // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(360.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();
   

      
   for(float x = 0; x < 360; x = x + 30)
   {
      glBegin(GL_LINE_STRIP);

         float y = sin(x*((3.1415)/180));        
         glColor3f(0.0, 1.0, 0.0);
         glVertex2f(x, y);
         glVertex2f((x+30),sin((x+30)*((3.1415)/180)));

         
         
         glEnd();

      

      glutSwapBuffers ();
      
   }

  

}

void display_180(void)
{


   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT);

   // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(360.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();
   

      
   for(float x = 0; x < 360; x = x + 2)
   {
      glBegin(GL_LINE_STRIP);

         float y = sin(x*((3.1415)/180));        
         glColor3f(0.0, 1.0, 0.0);
         glVertex2f(x, y);
         glVertex2f((x+2),sin((x+2)*((3.1415)/180)));        
         

      glEnd();

      

      glutSwapBuffers ();
      
   }

  

}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Inicializa com matriz identidade
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 'A':
      case 'a':
         
         //glutDisplayFunc(display_6);
         glutIdleFunc(display_6);

         break;

      case 'S':
      case 's':

         
         //glutDisplayFunc(display_12);
         glutIdleFunc(display_12);
         
      break;

      case 'D':
      case 'd':
         
         //glutDisplayFunc(display_180);
         glutIdleFunc(display_180);
      break;

     
      case 27:
        exit(0);
      break;


   }
}
