#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//yeah


void display(void);
void init (void);
void idle();
void DesenhaEixos();
void specialkeyboard(int key, int x, int y);

float desiredFPS = 30;
float varx = 0.2;
float vary = 6.2;
float dirx = 1.0f;
float diry = -1.0f;
float tempy = 4.65;
char aj;

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

   
   if(aj == 'u')
   {  

      diry = 1.0f;
          
      
      vary+=diry*0.1;
      

      //diry = -1.0f;
      tempy = 6.2;
      

      aj = 'v';
      

   }  


   if(varx <= 0.2 || varx >= 6.2) dirx *= -1;

   varx+=dirx*0.02;

   if(vary <= 0.2)
   {
      diry *= -1;
      
   } 

   if((diry > 0) && (vary >= tempy))
   {
        diry *= -1;
        tempy = (tempy * 0.75);
        
   }


   vary = vary + diry*0.1;
   
   
    
    

    

    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();

}

void specialkeyboard(int key, int x, int y)
{
      switch(key)
      {

         case GLUT_KEY_UP:

            aj = 'u';

            
         break;             

      }


}

void keyboardPress(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:
      exit(0);
    break;

    case '-':
      desiredFPS = desiredFPS - 5;
      if(desiredFPS <= 10) desiredFPS = 10;
    break;

    case '+':
      desiredFPS = desiredFPS + 5;
      if(desiredFPS >= 60) desiredFPS = 60;          
    break;
    
  }
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (640, 640);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("boucing ball");
   glutSpecialFunc(specialkeyboard);
   glutKeyboardFunc( keyboardPress );
   glutIdleFunc( idle);
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   

   return 0;
}

void DesenhaEixos()
{

   glBegin(GL_LINES);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f(-6.4, 0.0, 0.0);
      glVertex3f(6.4, 0.0, 0.0);
      glVertex3f(0.0, -6.4, 0.0);
      glVertex3f(0.0,  6.4, 0.0);
   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //glLoadIdentity(); // Inicializa com matriz identidade

   DesenhaEixos();

   glPushMatrix();

   glColor3f(1.0, 0.0, 0.0);
   glTranslatef(varx, vary, 0.0);
   glutSolidSphere(0.1, 50, 50);
 
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
   glOrtho(-0.1, 6.4, -0.1, 6.4, -6.4, 6.4);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}