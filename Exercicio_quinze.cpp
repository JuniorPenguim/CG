#include <stdio.h>



int main (void){

    int x1, x2;
    int y1, y2;
    int aux;
    int varx, vary; //delta x e delta y
    int iX , iY;

    printf("Valores de x1 e y1: \n");
    scanf("%d %d", &x1, &y1);
    printf("Valores de x2 e y2: \n");
    scanf("%d %d", &x2, &y2);
    printf("");

    varx = x2-x1;
    vary = y2-y1;

    iY = 2*vary;
    iX = 2*varx;

    
    printf("(%d), (%d)\n", x1,y1);

    aux = iY - varx;

    while( x1<x2 )
    {
        if(aux < 0)
        {
            aux = aux + iY;
            x1 = x1 + 1;
        }
        else
        {
            aux = aux + iY - iX;
            x1 = x1 + 1;
            y1 = y1 + 1;
        }
        printf("(%d), (%d)\n", x1,y1);
    }
    return 0;
}

