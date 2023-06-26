#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "bitmap.h" //lib for converting to bmp


int vrednost_konvergence(float a, float b)
{
    // funkcija vrne 80 ce konvergira proti r1 = 1 + 0 I, 160 ce konvergira proti -1/2 + sqrt(3)/2i in 240 ce konvergira proti -1/2 -sqrt(3)
    float complex x_0 = a + b * I;
    // printf("%lf | %lf \n", creal(x_0), cimag(x_0));
    float complex x_1 = x_0 - ((cpow(x_0, 3) - 1) / (3 * cpow(x_0, 2)));
    // printf("%f | %f\n", creal(x_1), cimag(x_1));
    int stevilo_iteracij = 0;
    // printf("%d\n", stevilo_iteracij);
    while (1)
    {
        x_0 = x_1;
        x_1 = x_0 - ((cpow(x_0, 3) - 1) / (3 * cpow(x_0, 2)));

        // switch ne deluje na int type ??
        if (fabs(creal(x_1) + 0.5) < 0.00001 && fabs((cimag(x_1) + 0.5 * sqrt(3))) < 0.00001)
            return 160;

        if (fabs(creal(x_1) + 0.5) < 0.00001 && fabs((cimag(x_1) - 0.5 * sqrt(3))) < 0.00001)
            return 240;

        if (fabs(creal(x_1) - 1) < 0.00001 && fabs(cimag(x_1)) < 0.00001)
            return 80;

        if (stevilo_iteracij >= 50)
        {
            break;
        }

        stevilo_iteracij++;
    }
    return 0;
}

unsigned char bitna_slika[1000][1000];
int main()
{

    // int *arrayPtr;

    // int x_int = 0;
    for (int i = -500; i < 500; i++)
    {
        for (int j = -500; j < 500; j++)
        {
            // resi enacbo in zapisi v tabelo 1000x1000
            int konver_proti = vrednost_konvergence((float)i, (float)j);
            bitna_slika[i + 500][j + 500] = (char)konver_proti;
        }
    }
    // int x = vrednost_konvergence(-1.0, 1.0);
    //  printf("%i", x);
    shraniBMP(bitna_slika, 1000, 1000, "skica_initial.bmp");
    return 0;
}