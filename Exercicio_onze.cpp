#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


void display(void);
void init (void);
void desenhaTabuleiro();

float varx = -0.8;
float vary = -0.8;


void init (void)
{

   glClearColor (0.0, 0.0, 0.0, 0.0);
   

   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_CULL_FACE); 
   
   
}


void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //glLoadIdentity(); // Inicializa com matriz identidade

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30, 1.333, 0, 0);
   //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);



   desenhaTabuleiro();

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();   

   //gluLookAt (0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); visão em 2D
   gluLookAt (0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
   
   
    
   glPushMatrix();

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   glColor3f(1.0, 0.0, 0.0);
      glTranslatef(varx, vary,  0.0);
      glutSolidCube(0.4);

   glPopMatrix();


     



   glutSwapBuffers ();
   glutPostRedisplay();

   
}

void specialKeys(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_UP:
         if(vary > 0.8)
         {
            vary = 0.8;            
         }else
         {
            vary = vary + 0.4;
         }
         
      break;

      case GLUT_KEY_RIGHT:
         if(varx > 0.8)
         {
            varx = 0.8;
            
         }else
         {
            varx = varx + 0.4;
         }
         
      break;

      case GLUT_KEY_DOWN:
         if(vary - 0.4 < -0.8)
         {
            vary = -0.8;
            
         }else
         {
            vary = vary - 0.4;
         }
         
      break;

      case GLUT_KEY_LEFT:
         if(varx - 0.4 < -0.8)
         {
            varx = -0.8;
            
         }else
         {
            varx = varx - 0.4;   
         }
         
      break;

   }
   glutPostRedisplay();

}
   


int main(int argc, char** argv)
{
   
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (640, 480);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Tabuleiro 3D");
   init ();   
   glutDisplayFunc(display);
   glutSpecialFunc( specialKeys );
   glutMainLoop();

   return 0;
}



void desenhaTabuleiro()
{

 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 for(float i = -1;i < 1; i = i + 0.4)
 {
   for(float j = -1;j < 1; j = j + 0.4)
   {

      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
      
         glVertex2f (i,j);
         glVertex2f (i+0.4,j);
         glVertex2f (i+0.4,j+0.4);
         glVertex2f (i,j+0.4);

      glEnd();
   }

  }    

}


   