#include <stdio.h>

int main (void){

    int raio;
    int x1, y1;
    int i = 01;
    float aux = 0.0;

    printf("Valor do raio: ");
    scanf("%d", &raio);

    x1 = 0;
    y1 = raio;

    aux = (5.0 / 4) - raio;

    printf("(%d), (%d)\n", x1, y1);
    printf("");

    while (x1 < y1)
    {
        if(aux < 0)
        {
            x1 = x1 + 1;
            aux = aux + 2*x1 + 1;
        }
        else
        {
            x1 = x1 + 1;
            y1 = y1 - 1;
            aux = aux + 2*x1 + 1 - 2*y1;
        }
        
        printf(" %d - %f - (%d), (%d)\n", i, aux, x1, y1);
        i++;
    }
    return 0;
}

