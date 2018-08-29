/*
  Name:        quad_transform.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Edited:	   Bruno José Dembogurski
  Update:      10/07/2018
  Date:        16/09/2004
  Description: Transformations using of OpenGL commands
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float desiredFPS = 10;
float varx = 0;
float vary = 0;
float dirx = 1.0f;
float diry = 1.0f;
float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
float var_angle = 0;
float dir_angle = 1.0f;
float var_scale = 1.0;
float dir_scale = 1.0;
int enableMenu = 0;


void display(void);
void init (void);
void desenhaEixos();
void idle();
void showMenu();
void mouse(int button, int state, int x, int y);


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

        
    if((varx == xtrans) && (vary == ytrans) && (var_angle == angle) && ((var_scale == scale)))
    {
    	if(enableMenu) showMenu();
    }
    

    
	if(varx != xtrans)
    {
         if((xtrans <= 0) && (xtrans < varx))
         {            
            varx-=dirx*1.0;
         }
         if((xtrans <= 0) && (xtrans > varx))
         {
         	varx+=dirx*1.0;
         }
         if ((xtrans >= 0) && (xtrans > varx))
         {
            varx+=dirx*1.0;
         }
         if((xtrans >= 0) && (xtrans < varx))
         {
         	varx-=dirx*1.0;
         }

    } 
    
    if(vary != ytrans)
    {
         if((ytrans <= 0) && (ytrans < vary))
         {            
            vary-=diry*1.0;
         }
         if((ytrans <= 0) && (ytrans > vary))
         {
         	vary+=diry*1.0;
         }
         if ((ytrans >= 0) && (ytrans > vary))
         {
            vary+=diry*1.0;
         }
         if((ytrans >= 0) && (ytrans < vary))
         {
         	vary-=diry*1.0;
         }

    } 


    
    if(var_angle > angle)
    {
    	var_angle-=dir_angle*1.0;    	
    }
    if(var_angle < angle)
    {
    	var_angle+=dir_angle*1.0;
    }

    if(var_scale > scale)
    {
    	var_scale-=dir_scale*1.0;
    }
    if(var_scale < scale)
    {
    	var_scale+=dir_scale*1.0;
    }
   

   

    /* Update tLast for next time, using static local variable */



    tLast = t;

    glutPostRedisplay();

}


// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      enableMenu = 1;
}

void showMenu()
{
   int op;
   system("cls");
   printf("\n=== MENU ===");
   printf("\n1 - Translacao");
   printf("\n2 - Rotacao");
   printf("\n3 - Escala");
   printf("\n4 - Sair");
   printf("\nOpcao: ");

   scanf("%d", &op);
   switch(op)
   {
      case 1:
         printf("\n\nInforme o vetor de translacao (entre -100.0 e 100.0)");
         printf("\nX : ");
         scanf("%f", &xtrans);
         printf("Y : ");
         scanf("%f", &ytrans);
         
      break;
      case 2:
         printf("\n\nInforme o angulo de rotacao (em graus): ");
         scanf("%f", &angle);
      break;
      case 3:
         printf("\n\nInforme o fator de escala: ");
         scanf("%f", &scale);
      break;
      case 4:
         exit(1);
      break;
      default:
         printf("\n\nOpcao invalida\n\n");
      break;
   }



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

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);

   
   glPushMatrix();
      glTranslatef(varx, vary, 0.0);
      glRotatef(var_angle, 0.0, 0.0, 1.0);
      glScalef(var_scale, var_scale, var_scale);
      glutWireCube(10);
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
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (300, 300);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   glutMouseFunc( mouse );
   glutIdleFunc( idle);
   init ();
   printf("Posicione as janelas e clique na janela do OpenGL para habilitar o menu.\n");
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}
