#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void display(void);
void init (void);
void desenhaTabuleiro();
void idle();

float desiredFPS = 60;
float positx = -2.5;
float posity = -2.5;
float varx = -2.5;
float vary = -2.5;
float dirx = 1.0f;
float diry = 1.0f;

void idle()
{
    float t, desiredFrameTime, frameTime;
    static float tLast = 0.0;

    // Get elapsed time
    t = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
    t /= 1000.0;

    // Calculate frame time
    frameTime = t - tLast;
    // Calculate desired frame time
    desiredFrameTime = 1.0 / (float) (desiredFPS);

    // Check if the desired frame time was achieved. If not, skip animation.
    if( frameTime <= desiredFrameTime)
        return;

    /*
     *UPDATE ANIMATION VARIABLES
     */
    
    if(varx != positx)
    {
         if((positx <= 0) && (positx < varx))
         {            
            varx-=dirx*0.01;
         }
         if((positx <= 0) && (positx > varx))
         {
          varx+=dirx*0.01;
         }
         if ((positx >= 0) && (positx > varx))
         {
            varx+=dirx*0.01;
         }
         if((positx >= 0) && (positx < varx))
         {
          varx-=dirx*0.01;
         }

    } 
    
    if(vary != posity)
    {
         if((posity <= 0) && (posity < vary))
         {            
            vary-=diry*0.01;
         }
         if((posity <= 0) && (posity > vary))
         {
          vary+=diry*0.01;
         }
         if ((posity >= 0) && (posity > vary))
         {
            vary+=diry*0.01;
         }
         if((posity >= 0) && (posity < vary))
         {
            vary-=diry*0.01;
         }

    }    

    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();

}

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
   glutIdleFunc( idle);
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
   glTranslatef(varx, vary, 0.0);
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
