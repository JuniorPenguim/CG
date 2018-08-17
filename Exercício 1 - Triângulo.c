#include <stdio.h>
#include <GL/glut.h>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (250, 250);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Exercicio 1 Test");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);

	printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}

// É a rotina chamada automaticamente sempre que a
// janela ou parte dela precisa ser redesenhada
void display(void)
{
   // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT);

    // Desenhar a linha x do eixo
    glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(-0.5, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);

   glEnd();

   // Desenhar a linha y do eixo
   glBegin(GL_LINES);

      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, -0.5, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

   glEnd();

   // Desenhar um triângulo vermelho
   glBegin(GL_TRIANGLES);

      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (0.0, 0.0, 0.0);
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
      case GLUT_KEY_LEFT:
         exit(0);
      break;
   }
}
