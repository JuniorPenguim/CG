#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
char var;

void desenhaEixos()
{
      glBegin(GL_LINES);
      glColor3f (1.0, 1.0, 1.0);
      glVertex3f(-10.0, 0.0, 0.0);
      glVertex3f( 360.0, 0.0, 0.0);
      glVertex3f(0.0, -10.0, 0.0);
      glVertex3f(0.0,  10.0, 0.0);
   glEnd();

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1920, 1080);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercicio 2");
   init ();
   printf("Pressione as teclas 'a', 's' e 'd' para alternar entre as formas da senoidal. \n");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);

   printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}




void display(void)
{

   switch(var)
   {
      case 'a':

      // Limpar todos os pixels
      glClear (GL_COLOR_BUFFER_BIT);

      desenhaEixos();

      for(float x = 0; x < 360; x = x + 60)
      {  
         //desenho do gráfico senoidal dividido em 6 partes
         glBegin(GL_LINE_STRIP);

            float y = sin(x*((3.1415)/180));        
            glColor3f(0.0, 1.0, 0.0);
            glVertex2f(x, y);
            glVertex2f((x+60),sin((x+60)*((3.1415)/180)));         
         
         glEnd();      

      glutSwapBuffers ();
      
      }

      break;

      case 'b':

      // Limpar todos os pixels
      glClear (GL_COLOR_BUFFER_BIT);

      desenhaEixos();   

      // desenho do grafico senoidal dividido em 12 partes
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

      break;

      case 'c':

      // Limpar todos os pixels
      glClear (GL_COLOR_BUFFER_BIT);

      desenhaEixos();
      
      //desenho gráfico senoidal dividido emm 180 partes
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

      break;

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
         
         var = 'a';
         glutPostRedisplay();


         break;

      case 'S':
      case 's':      
        
         var = 'b';
         glutPostRedisplay();

         
      break;

      case 'D':
      case 'd':         
         
         var = 'c';
         glutPostRedisplay();

      break;

     
      case 27:
        exit(0);
      break;

   }
}
