#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
char var;

void display(void);
void init (void);
void desenhaEixos();
void keyboard(unsigned char key, int x, int y);
void specialkeyboard(int key, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Quad Transform com teclas");
   init ();
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialkeyboard);
   printf("Pressione 'R' para rotacionar no sentido anti-horário e 'r' no sentido horário.\n");
   printf("Pressione '+' para aumentar a escala e '-' para diminuir.\n");
   printf("Utilize as teclas direcionais para movimentar o cubo.\n");
   printf("Pressione ESC para sair.\n");
   glutDisplayFunc(display);
   glutMainLoop();
   

   return 0;
}

void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void specialkeyboard(int key, int x, int y)
{
      switch(key)
      {

         case GLUT_KEY_UP:

            ytrans = ytrans + 5;
            glutPostRedisplay();
         break;

         case GLUT_KEY_DOWN:

            ytrans = ytrans - 5;
            glutPostRedisplay();
         break;

         case GLUT_KEY_LEFT:

            xtrans = xtrans - 5;
            glutPostRedisplay();
         break;

         case GLUT_KEY_RIGHT:

            xtrans = xtrans + 5;
            glutPostRedisplay();
         break;         

      }

}


void keyboard(unsigned char key, int x, int y)
{

   switch(key)
   {

      case '+':
         
         scale = scale * 2;
         glutPostRedisplay();            
         
      break;

      case '-':

         scale = scale / 2;   
         glutPostRedisplay();         

      break;

      case 'r':

         angle--;
         glutPostRedisplay();         

      break;

      case 'R':

         angle++;
         glutPostRedisplay();         

      break;

      case 27:

         exit(0);

      break;

   }

}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);

   glPushMatrix();
      glTranslatef(xtrans, ytrans, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glScalef(scale, scale, scale);
      glutWireCube(10);
   glPopMatrix();   

   glutSwapBuffers ();
      
}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
