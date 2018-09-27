#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


float rotationX = 25.0, rotationY = 0.0;
int   last_x, last_y;
int width = 640, height = 300;
void desenhaTabuleiro();
float varx = -0.8;
float vary = -0.8;

int distOrigem = 2;

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
   glColorMaterial(GL_FRONT, GL_DIFFUSE);

   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
}


void desenhaTabuleiro()
{

 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 for(float i = -1;i < 0.6; i = i + 0.4)
 {
   for(float j = -1;j < 0.6; j = j + 0.4)
   {

      glPushMatrix();

         glRotatef(-45, 1, 0, 0);
         
         glBegin(GL_POLYGON);
         
            glVertex3f (i,j,0);
            glVertex3f (i+0.4,j,0);
            glVertex3f (i+0.4,j+0.4,0);
            glVertex3f (i,j+0.4,0);

         glEnd();

      glPopMatrix();
   }

  }    

}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

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
      glutSolidCube(0.4);
   glPopMatrix();

   glutSwapBuffers();
}

void idle ()
{
   glutPostRedisplay();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
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
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc( specialKeys );
   glutMouseFunc( mouse );
   glutMotionFunc( motion );
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
