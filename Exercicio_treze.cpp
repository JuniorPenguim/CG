/*
  Name:        iluminacao_atenuacao.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Edited:	   Bruno José Dembogurski
  Update:        10/07/2018
  Date:        23/06/2008
  Description: Atenuação em fontes de luz em opengl.  O fator de atenuação
               segue a seguinte fórmula

attenuation factor =        1
                    -------------------
                    kc + kl*d + kq*d^2
onde
d = distancia entre o vertice e a fonte de luz
kc = GL_CONSTANT_ATTENUATION	(default 1.0f)
kl = GL_LINEAR_ATTENUATION		(default 0.0f)
kq = GL_QUADRATIC_ATTENUATION (default 0.0f)
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int width  = 700;
int height = 700;

int anguloRotacao = 0;
float kc = 0.1f;
float kl = 0.04f;
float kq = 0.0005f;
bool vermelho = true;
bool verde = true;
bool azul = true;
bool attenuationOn = true;

// Material da base
GLfloat base_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
GLfloat base_difusa[]    = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_especular[] = { 0.8, 0.0, 0.0, 1.0 };
GLfloat base_emissao[]   = { 1.0, 1.0, 1.0, 1.0 };
GLfloat base_brilho[]    = { 128.0 };

// Material do teapot
GLfloat object_ambient[]   = { 0.25725, 0.1995, 0.0745, 1.0 };
GLfloat object_difusa[]    = { 0.80164, 0.60648, 0.22648, 1.0 };
GLfloat object_especular[] = { 0.828281, 0.555802, 0.366065, 1.0 };
GLfloat object_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat object_brilho[]    = { 160.0 };

// Define parametros da luz vermelha
GLfloat cor_luz_vermelha[]			= { 1.0f, 0.0f, 0.0f, 1.0};
GLfloat cor_luz_amb_vermelha[]	= { 0.02, 0.02, 0.02, 0.02};
GLfloat posicao_luz_vermelha[]	= { 0.0, 10.0, 10.0, 1.0};
GLfloat cor_fonte_luz_vermelha[]	= { 1.0, 0.0, 0.0, 1.0};
GLfloat cor_emissao_vermelha[]	= { 0.2, 0.2, 0.0, 1.0 };

// Define parametros da luz verde
GLfloat cor_luz_verde[]			= { 0.0f, 1.0f, 0.0f, 1.0};
GLfloat cor_luz_amb_verde[]	= { 0.02, 0.02, 0.02, 0.02};
GLfloat posicao_luz_verde[]	= { -10.0, 10.0, 0.0, 1.0};
GLfloat cor_fonte_luz_verde[]	= { 0.0, 1.0, 0.0, 1.0};
GLfloat cor_emissao_verde[]	= { 0.2, 0.2, 0.0, 1.0 };

// Define parametros da luz azul
GLfloat cor_luz_azul[]			= { 0.0f, 0.0f, 1.0f, 1.0};
GLfloat cor_luz_amb_azul[]	= { 0.02, 0.02, 0.02, 0.02};
GLfloat posicao_luz_azul[]	= { 10.0, 10.0, 0.0, 1.0};
GLfloat cor_fonte_luz_azul[]	= { 0.0, 0.0, 1.0, 1.0};
GLfloat cor_emissao_azul[]	= { 0.2, 0.2, 0.0, 1.0 };

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
   glEnable(GL_LIGHTING);                 // Habilita luz
   glEnable(GL_LIGHT0);                   // habilita luz 0
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);

   // Define parametros da luz 0
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb_vermelha);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz_vermelha);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz_vermelha);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz_vermelha);

   // Define parametros da luz 1
   glLightfv(GL_LIGHT1, GL_AMBIENT, cor_luz_amb_verde);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz_verde);
   glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz_verde);
   glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz_verde);

   // Define parametros da luz 2
   glLightfv(GL_LIGHT2, GL_AMBIENT, cor_luz_amb_azul);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, cor_luz_azul);
   glLightfv(GL_LIGHT2, GL_SPECULAR, cor_luz_azul);
   glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz_azul);

   printf("\nMenu");
   printf("\n====\n\n");
   printf("Keyboard:\n");
   printf("  'a' para ligar/desligar o efeito de atenuação.\n");
   printf("  'o' e 'p' para rotacionar o bule.\n");
   printf("  Direcionais do teclado movem a luz vermelha em X e Y.\n");
   printf("  'PageUp' e 'PageDown' movem a luz vermelha em Z.\n");
   printf("  'e', 's', 'd', 'f' movem a luz verde em X e Y.\n");
   printf("  'r' e 'g' movem a luz verde em Z.\n");
   printf("  'u', 'h', 'j', 'k' movem a luz azul em X e Y.\n");
   printf("  'i' e 'l' movem a luz azul em Z.\n");
   printf("  'b' para ligar/deligar luz vermelha.\n");
   printf("  'n' para ligar/deligar luz verde.\n");
   printf("  'm' para ligar/deligar luz azul.\n");
   printf("Pressione ESC para sair.\n");
}

void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
					  GLfloat *brilho, GLfloat *emissao )
{
   // Define os parametros da superficie a ser iluminada

   glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
   glMaterialfv(GL_FRONT, GL_EMISSION, emissao);

}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(85.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (0.0, 15.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   // Posiciona esfera que representa a fonte de luz 0 no mundo
   glPushMatrix();
      glTranslatef(posicao_luz_vermelha[0],posicao_luz_vermelha[1],posicao_luz_vermelha[2]);
      glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz_vermelha);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_fonte_luz_vermelha);
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao_vermelha);
      glutSolidSphere(0.2,30,30);

      glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
      glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
      glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

   glPopMatrix();




   // Posiciona esfera que representa a fonte de luz 1 no mundo
   glPushMatrix();
      glTranslatef(posicao_luz_verde[0],posicao_luz_verde[1],posicao_luz_verde[2]);
      glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz_verde);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_fonte_luz_verde);
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao_verde);
      glutSolidSphere(0.2,30,30);

      glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, kc);
      glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, kl);
      glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, kq);

   glPopMatrix();




   // Posiciona esfera que representa a fonte de luz 2 no mundo
   glPushMatrix();
      glTranslatef(posicao_luz_azul[0],posicao_luz_azul[1],posicao_luz_azul[2]);
      glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz_azul);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_fonte_luz_azul);
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao_azul);
      glutSolidSphere(0.2,30,30);

      glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, kc);
      glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, kl);
      glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, kq);

   glPopMatrix();



    //Draw lines
    glLineWidth(5);

      glBegin(GL_LINES);

          // linha horizontal da frente
      glVertex3f(-10.0f, 10.0f, 10.0);
      glVertex3f(10.0f, 10.0f, 10.0);


     // linha horizontal da direita
      glVertex3f(10.0f, 10.0f, 10.0);
      glVertex3f(10.0f, 10.0f, -10.0);


      // linha horizontal da esquerda
      glVertex3f(-10.0f, 10.0f, 10.0);
      glVertex3f(-10.0f, 10.0f, -10.0);


      // linha vertifical frontal da direita
      glVertex3f(10.0f, 10.0f, 10.0);
      glVertex3f(10.0f, -2.5f, 10.0);

      // linha vertifical frontal da esquerda
      glVertex3f(-10.0f, 10.0f, 10.0);
      glVertex3f(-10.0f, -2.5f, 10.0);


      // linhas vertifical traseira da direita
      glVertex3f(10.0f, 10.0f, -10.0);
      glVertex3f(10.0f, -2.5f, -10.0);


      // linhas vertifical traseira da esquerda
      glVertex3f(-10.0f, 10.0f, -10.0);
      glVertex3f(-10.0f, -2.5f, -10.0);

      glEnd();


   // Draw objects
    glPushMatrix();
        setMaterial(object_ambient,object_difusa,object_especular,object_brilho,object_emissao);
        glRotatef(anguloRotacao, 0.0, 1.0, 0.0);
        glutSolidTeapot(7.0);
    glPopMatrix();

	glPushMatrix();

        setMaterial(base_ambient,base_difusa,base_especular,base_brilho,base_emissao);

        glBegin(GL_POLYGON);
          glNormal3f(0.0f, 1.0f, 0.0f);
          glVertex3f(-10.0f, -2.5f, -10.0);
          glVertex3f( 10.0f, -2.5f, -10.0);
          glVertex3f( 10.0f, -2.5f,  10.0);
          glVertex3f(-10.0f, -2.5f,  10.0);

        glEnd();
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

void special(int key, int x, int y)
{
   switch (key)
   {
      case GLUT_KEY_LEFT:

         if(((posicao_luz_vermelha[1] == 10)) && ((posicao_luz_vermelha[2] == 10)))
         {
            if (posicao_luz_vermelha[0] - 0.2 > -10.0)
            posicao_luz_vermelha[0] = posicao_luz_vermelha[0] - 0.2;
         else
            posicao_luz_vermelha[0] = -10.0;

         }
      break;

      case GLUT_KEY_RIGHT:

         if(((posicao_luz_vermelha[1] == -2.5) || ((posicao_luz_vermelha[1] == 10))) && ((posicao_luz_vermelha[2] == 10) || (posicao_luz_vermelha[2] == -10)))
         {
            if (posicao_luz_vermelha[0] + 0.2 < 10.0)
            posicao_luz_vermelha[0] = posicao_luz_vermelha[0] + 0.2;

         else
            posicao_luz_vermelha[0] = 10.0;
         }

      break;

      case GLUT_KEY_UP:
          if(((posicao_luz_vermelha[0] == -10) || ((posicao_luz_vermelha[0] == 10))) && ((posicao_luz_vermelha[2] == 10) || (posicao_luz_vermelha[2] == -10)))
            {
            if(posicao_luz_vermelha[1] + 0.2 < 10.0)
                posicao_luz_vermelha[1] = posicao_luz_vermelha[1] + 0.2;
            else
                posicao_luz_vermelha[1] = 10.0;
            }

      break;

      case GLUT_KEY_DOWN:
          if(((posicao_luz_vermelha[0] == -10) || ((posicao_luz_vermelha[0] == 10))) && ((posicao_luz_vermelha[2] == 10) || (posicao_luz_vermelha[2] == -10)))
          {
            if(posicao_luz_vermelha[1] - 0.2 > -2.5)
            posicao_luz_vermelha[1] = posicao_luz_vermelha[1] - 0.2;
          else
            posicao_luz_vermelha[1] = -2.5;
          }

      break;

      case GLUT_KEY_PAGE_DOWN:
          if(((posicao_luz_vermelha[0] == -10) || ((posicao_luz_vermelha[0] == 10))) && ((posicao_luz_vermelha[1] == 10) || (posicao_luz_vermelha[1] == -2.5)))
          {
            if(posicao_luz_vermelha[2] + 0.2 < 10.0)
            posicao_luz_vermelha[2] = posicao_luz_vermelha[2] + 0.2;
          else
             posicao_luz_vermelha[2] = 10.0;
          }

      break;

      case GLUT_KEY_PAGE_UP:
          if(((posicao_luz_vermelha[0] == -10) || ((posicao_luz_vermelha[0] == 10))) && ((posicao_luz_vermelha[1] == 10) || (posicao_luz_vermelha[1] == -2.5)))
          {
            if(posicao_luz_vermelha[2] - 0.2 > -10.0)
            posicao_luz_vermelha[2] = posicao_luz_vermelha[2] - 0.2;
          else
            posicao_luz_vermelha[2] = -10.0;
          }

      break;
   }
   glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (tolower(key))
   {
       case 's':
             if(((posicao_luz_verde[1] == 10)) && ((posicao_luz_verde[2] == 10)))
             {
                if (posicao_luz_verde[0] - 0.2 > -10.0)
                posicao_luz_verde[0] = posicao_luz_verde[0] - 0.2;
             else
                posicao_luz_verde[0] = -10.0;
             }
            break;

      case 'f':
            if(((posicao_luz_verde[1] == -2.5) || ((posicao_luz_verde[1] == 10))) && ((posicao_luz_verde[2] == 10) || (posicao_luz_verde[2] == -10)))
             {
                if (posicao_luz_verde[0] + 0.2 < 10.0)
                posicao_luz_verde[0] = posicao_luz_verde[0] + 0.2;

             else
                posicao_luz_verde[0] = 10.0;
             }
            break;

      case 'e':
          if(((posicao_luz_verde[0] == -10) || ((posicao_luz_verde[0] == 10))) && ((posicao_luz_verde[2] == 10) || (posicao_luz_verde[2] == -10)))
            {
            if(posicao_luz_verde[1] + 0.2 < 10.0)
                posicao_luz_verde[1] = posicao_luz_verde[1] + 0.2;
            else
                posicao_luz_verde[1] = 10.0;
            }
            break;

      case 'd':
          if(((posicao_luz_verde[0] == -10) || ((posicao_luz_verde[0] == 10))) && ((posicao_luz_verde[2] == 10) || (posicao_luz_verde[2] == -10)))
          {
            if(posicao_luz_verde[1] - 0.2 > -2.5)
            posicao_luz_verde[1] = posicao_luz_verde[1] - 0.2;
          else
            posicao_luz_verde[1] = -2.5;
          }
            break;

      case 'r':
          if(((posicao_luz_verde[0] == -10) || ((posicao_luz_verde[0] == 10))) && ((posicao_luz_verde[1] == 10) || (posicao_luz_verde[1] == -2.5)))
          {
            if(posicao_luz_verde[2] + 0.2 < 10.0)
            posicao_luz_verde[2] = posicao_luz_verde[2] + 0.2;
          else
             posicao_luz_verde[2] = 10.0;
          }

          break;

      case 'g':
          if(((posicao_luz_verde[0] == -10) || ((posicao_luz_verde[0] == 10))) && ((posicao_luz_verde[1] == 10) || (posicao_luz_verde[1] == -2.5)))
          {
            if(posicao_luz_verde[2] - 0.2 > -10.0)
            posicao_luz_verde[2] = posicao_luz_verde[2] - 0.2;
          else
            posicao_luz_verde[2] = -10.0;
          }

          break;

      case 'h':

         if(((posicao_luz_azul[1] == 10)) && ((posicao_luz_azul[2] == 10)))
         {
            if (posicao_luz_azul[0] - 0.2 > -10.0)
            posicao_luz_azul[0] = posicao_luz_azul[0] - 0.2;
         else
            posicao_luz_azul[0] = -10.0;

         }
         break;

      case 'k':

         if(((posicao_luz_azul[1] == -2.5) || ((posicao_luz_azul[1] == 10))) && ((posicao_luz_azul[2] == 10) || (posicao_luz_azul[2] == -10)))
         {
            if (posicao_luz_azul[0] + 0.2 < 10.0)
            posicao_luz_azul[0] = posicao_luz_azul[0] + 0.2;

         else
            posicao_luz_azul[0] = 10.0;
         }

         break;

      case 'u':
          if(((posicao_luz_azul[0] == -10) || ((posicao_luz_azul[0] == 10))) && ((posicao_luz_azul[2] == 10) || (posicao_luz_azul[2] == -10)))
            {
            if(posicao_luz_azul[1] + 0.2 < 10.0)
                posicao_luz_azul[1] = posicao_luz_azul[1] + 0.2;
            else
                posicao_luz_azul[1] = 10.0;
            }

          break;

      case 'j':
          if(((posicao_luz_azul[0] == -10) || ((posicao_luz_azul[0] == 10))) && ((posicao_luz_azul[2] == 10) || (posicao_luz_azul[2] == -10)))
          {
            if(posicao_luz_azul[1] - 0.2 > -2.5)
            posicao_luz_azul[1] = posicao_luz_azul[1] - 0.2;
          else
            posicao_luz_azul[1] = -2.5;
          }

          break;

      case 'i':
          if(((posicao_luz_azul[0] == -10) || ((posicao_luz_azul[0] == 10))) && ((posicao_luz_azul[1] == 10) || (posicao_luz_azul[1] == -2.5)))
          {
            if(posicao_luz_azul[2] + 0.2 < 10.0)
            posicao_luz_azul[2] = posicao_luz_azul[2] + 0.2;
          else
             posicao_luz_azul[2] = 10.0;
          }

          break;

      case 'l':
          if(((posicao_luz_azul[0] == -10) || ((posicao_luz_azul[0] == 10))) && ((posicao_luz_azul[1] == 10) || (posicao_luz_azul[1] == -2.5)))
          {
            if(posicao_luz_azul[2] - 0.2 > -10.0)
            posicao_luz_azul[2] = posicao_luz_azul[2] - 0.2;
          else
            posicao_luz_azul[2] = -10.0;
          }

          break;

      case 'o':
         anguloRotacao = (anguloRotacao + 1) % 360;
         break;
      case 'p':
         anguloRotacao = (anguloRotacao - 1) % 360;
         break;
      case 'b':
         vermelho = !vermelho;
         break;
      case 'n':
         verde = !verde;
         break;
      case 'm':
         azul = !azul;
         break;
      case 'a':
      attenuationOn = !attenuationOn;
      if(attenuationOn)
      {
         kc = 0.1f;
         kl = 0.04f;
         kq = 0.0005f;
         printf("AttenuationOn\n");
      }
      else
      {	// default values
         kc = 1.0f;
         kl = 0.0f;
         kq = 0.0f;
         printf("AttenuationOff\n");
      }
      break;
      case 27:	   exit(0);
      break;
   }
   if (vermelho)
     glEnable(GL_LIGHT0);
   else
     glDisable(GL_LIGHT0);

   if (verde)
     glEnable(GL_LIGHT1);
   else
     glDisable(GL_LIGHT1);

   if (azul)
     glEnable(GL_LIGHT2);
   else
     glDisable(GL_LIGHT2);

   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (width, height);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
