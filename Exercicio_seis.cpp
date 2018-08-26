#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//yeah


void display(void);
void init (void);
void desenhaTabuleiro();

float positx = -2.5;
float posity = -2.5;

void mouse(int button, int state, int x, int y)
{

   y = 150 - y; 
   x = x - 150;
   

   if(button == GLUT_LEFT_BUTTON)
   {
         if(state == GLUT_DOWN)
      {
         printf("\nBotao esquerdo pressionado na posicao [%d, %d].", x*2, y*2);
         positx = floor((float)((x*2.0)/100.0)) + 0.5;
         posity = floor((float)((y*2.0)/100.0)) + 0.5;
         printf("\n%f , %f", positx, posity);

         
      }

   }


}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("tabuleiro");
   glutMouseFunc( mouse );
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   

   return 0;
}


void desenhaTabuleiro()
{
 for(int i = -3;i <= 3; i++ )
 {
   for(int j = -3;j <= 3; j++ )
   {

      glBegin(GL_POLYGON);
      if((i%2) == 0)
      {

         if((j%2) == 0)
         {
            glColor3f (1, 1, 1);
         }else
         {

            glColor3f (0, 0, 0);
         }

      }
      else
      {
         if((j%2) == 0)
         { 
            glColor3f (0, 0, 0);
         }else
         {
            glColor3f (1, 1, 1);
         }

      }

         glVertex2f (i,j);
         glVertex2f (i+1,j);
         glVertex2f (i+1,j+1);
         glVertex2f (i,j+1);
      glEnd();
   }

  }    

}


void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //glLoadIdentity(); // Inicializa com matriz identidade

   desenhaTabuleiro();

   glPushMatrix();

   glColor3f(1.0, 0.0, 0.0);
   glTranslatef(positx, posity, 0.0);
   glutSolidSphere(0.5, 50, 50);
 
   glPopMatrix();
     

   glutSwapBuffers ();
   glutPostRedisplay();

   
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
