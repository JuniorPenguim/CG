#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


void display(void);
void init (void);
void desenhaTabuleiro();
void idle();

float rotationX = 25.0, rotationY = 0.0;
int   last_x, last_y;
int width = 640, height = 480;

float desiredFPS = 30;
int varx = -80;
int vary = -80;
float dirx = 1.0;
float diry = 1.0;
int positx = -80;
int posity = -80;

int distOrigem = 200;



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
         varx = varx + dirx * 1;
     }

     if(vary != posity)
     {
         vary = vary + diry * 1;
     }
    
   

    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();

}

void init (void)
{

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);   

   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_CULL_FACE); 
   
   
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void display(void)
{

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 400.0);
   //glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0); // visão em 2D

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, distOrigem, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f (1, 1, 1);
   desenhaTabuleiro();
   glColor3f (1, 0, 0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   
   glPushMatrix();
      glRotatef(-45, 1, 0, 0);
      glTranslatef(varx, vary,  0.0);
      glutSolidCube(40);
   glPopMatrix();

   glutSwapBuffers();

   
}

void keyboard (unsigned char key, int x, int y)
{
   switch (tolower(key))
   {
      case '+' :
         distOrigem--;
         if(distOrigem<2) distOrigem=2;
      break;
      case '-' :
         distOrigem++;
         if(distOrigem>5) distOrigem=5;
      break;
      case 27:
         exit(0);
      break;
   }
}

void specialKeys(int key, int x, int y)
{
   switch(key)
   {
      case GLUT_KEY_UP:
         if(posity + 40 < 100)
         {  
            diry = 1;
            posity = posity + 40;
         }
         
      break;

      case GLUT_KEY_RIGHT:

         if(positx + 40 < 100)
         {  
            dirx = 1;                  
            positx = positx + 40;    
            
         }
         
      break;

      case GLUT_KEY_DOWN:
         if(posity - 40 > -100 )
         {
            diry = -1;
            posity = posity - 40;
         }
         
      break;

      case GLUT_KEY_LEFT:
         if(positx - 40 > -100)
         {  
            dirx = -1;
            positx = positx - 40;
         }
         
      break;

   }
   glutPostRedisplay();

}
   

// Motion callback
void motion(int x, int y )
{
   rotationX += (float) (y - last_y);
   rotationY += (float) (x - last_x);

   last_x = x;
   last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
   {
      last_x = x;
      last_y = y;
   }
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glutSpecialFunc( specialKeys );
   glutIdleFunc(idle);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);   
   glutMouseFunc( mouse );
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);   
   glutMainLoop();
   return 0;
}



void desenhaTabuleiro()
{

 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 for(float i = -100;i < 100; i = i + 40)
 {
   for(float j = -100;j < 100 ; j = j + 40)
   {

      glPushMatrix();

         glRotatef(-45, 1, 0, 0);

         glBegin(GL_POLYGON);
         
            glVertex2f (i,j);
            glVertex2f (i+40,j);
            glVertex2f (i+40,j+40);
            glVertex2f (i,j+40);

         glEnd();

      glPopMatrix();
   }

  }    

}

