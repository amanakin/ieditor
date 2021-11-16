
#include <TXLib.h>
                                                                                #define __slowpoke  txSleep (20),
double Hermite00 (double t) { return  2*t*t*t - 3*t*t + 1; }
double Hermite10 (double t) { return    t*t*t - 2*t*t + t; }
double Hermite01 (double t) { return -2*t*t*t + 3*t*t;     }
double Hermite11 (double t) { return    t*t*t -   t*t;     }

double CatmullRom (double* y, double dx, double t)
    {
    double m0 = (y[1] - y[-1]) / 2,           //                                  y[1]
           m1 = (y[2] - y[ 0]) / 2;           //        y[-1]               ,-----* .
                                              //        * .                .      |   .        y[2]
    double t2   = t*t,                        //        |   .        y[0] /       |      .  .  *
           t3   = t2 * t,                     //        |     . .  . *---+        |            |
           t3_2 = t3 * 2,                     //        |            |            |            |
           t2_3 = t2 * 3;                     //        |            |            |            |
                                              //        |            |            |            |
    double hermite00 =  t3_2 - t2_3 + 1;      //     ---+------------+------------+------------+---
    double hermite10 =  t3   - t2*2 + t;      //         <----dx---->|<====dx====>|<-----dx--->
    double hermite01 = -t3_2 + t2_3;          //                     t=0          t=1
    double hermite11 =  t3   - t2;

    return hermite00 * y[0] + hermite10 * m0 * dx +
           hermite01 * y[1] + hermite11 * m1 * dx;
    }

int main()
    {
    srand (time (NULL));

    txCreateWindow (800, 800);
    _getch();

    const int N = 50;

    double yy[N] = {};
    for (int i = 0; i < N; i++) yy[i] = (rand() % 1025 / 1024.0) * 2 - 1;

    double x0 = 0, dx = 1;

    txSetColor (TX_WHITE); txSetFillColor (TX_GRAY);

    for (int i = 1; i < N-2; __slowpoke i++)
    	{
    	for (double t = 0; t <= 1; t += 0.001)
    	    {
    	    double x = x0 + (i+t)*dx;
    	    double y = CatmullRom (yy+i, dx, t);
    	    txCircle (x*15 + 10, -y*100 + 400, 3);

    	    if (t == 0) txCircle (x*15 + 10, -y*100 + 400, 10);
    	    }
    	}
    getch();

    double xx[N] = {};
    for (int i = 0; i < N; i++) xx[i] = (rand() % 1025 / 1024.0) * 2 - 1;

    txSetColor (TX_LIGHTRED); txSetFillColor (TX_RED);

    for (int i = 1; i < N-2; __slowpoke i++)
    	{
    	for (double t = 0; t <= 1; t += 0.001)
    	    {
    	    double x = CatmullRom (&xx[i], 1, t);
    	    double y = CatmullRom (&yy[i], 1, t);
    	    txCircle (x*300 + 400, -y*300 + 400, 3);

    	    if (t == 0) txCircle (x*300 + 400, -y*300 + 400, 10);
    	    }
    	}
    getch();

    double zz[N] = {};
    for (int i = 0; i < N; i++) zz[i] = rand() % 1025 / 1024.0;

    double rr[N] = {};
    for (int i = 0; i < N; i++) rr[i] = rand() % 1025 / 1024.0;

    double gg[N] = {};
    for (int i = 0; i < N; i++) gg[i] = rand() % 1025 / 1024.0;

    double bb[N] = {};
    for (int i = 0; i < N; i++) bb[i] = rand() % 1025 / 1024.0;

    for (int i = 1; i < N-2; __slowpoke __slowpoke i++)
    	{
    	for (double t = 0; t <= 1; t += 0.01)
    	    {
    	    double x = CatmullRom (xx+i, 1, t);
    	    double y = CatmullRom (yy+i, 1, t);
    	    double z = CatmullRom (zz+i, 1, t);
    	    double r = CatmullRom (rr+i, 1, t);
    	    double g = CatmullRom (gg+i, 1, t);
    	    double b = CatmullRom (bb+i, 1, t);

    	    txColor     (r, g, b);
            txFillColor (r, g, b);
    	    txCircle (x*300 + 400, -y*300 + 400, z * 20 + 10);
    	    }
    	}
    getch();

    txBegin();
    while (!kbhit())
        {
        int K = N/3;
        for (int i = 0; i < K; i++) xx[i] += (rand() % 1025 / 1024.0 - 0.5) / 25;
        for (int i = 0; i < K; i++) yy[i] += (rand() % 1025 / 1024.0 - 0.5) / 25;
        for (int i = 0; i < K; i++) zz[i] += (rand() % 1025 / 1024.0 - 0.5) / 25;
        for (int i = 0; i < K; i++) rr[i] += (rand() % 1025 / 1024.0 - 0.5) / 25;
        for (int i = 0; i < K; i++) gg[i] += (rand() % 1025 / 1024.0 - 0.5) / 25;
        for (int i = 0; i < K; i++) bb[i] += (rand() % 1025 / 1024.0 - 0.5) / 25;

        txSetFillColor (0); // hehe
        txClear();

        for (int i = 1; i < K-2; i++)
        	{
        	for (double t = 0; t <= 1; t += 0.01)
        	    {
        	    double x = CatmullRom (xx+i, 1, t);
        	    double y = CatmullRom (yy+i, 1, t);
        	    double z = CatmullRom (zz+i, 1, t);
        	    double r = CatmullRom (rr+i, 1, t);
        	    double g = CatmullRom (gg+i, 1, t);
        	    double b = CatmullRom (bb+i, 1, t);

        	    txColor     (r, g, b);
                txFillColor (r, g, b);
        	    txCircle (x*300 + 400, -y*300 + 400, z * 30 + 10);
        	    }
        	}

   	    txColor (rr[K-1]/2, gg[K-1]/2, bb[K-1]/2);
   	    txCircle (xx[K-1]*300 + 400, -yy[K-1]*300 + 400+12, zz[K-1] * 30 + 10);

        txSetFillColor (TX_WHITE);
   	    txCircle   (xx[K-1]*300 + 400-10, -yy[K-1]*300 + 400-2, 5);
   	    txSetPixel (xx[K-1]*300 + 400-10, -yy[K-1]*300 + 400-2, 0);
   	    txCircle   (xx[K-1]*300 + 400+10, -yy[K-1]*300 + 400-2, 5);
   	    txSetPixel (xx[K-1]*300 + 400+10, -yy[K-1]*300 + 400-2, 0);
   	    txSetColor     (TX_LIGHTRED);
        txSetFillColor (TX_LIGHTRED);
   	    txCircle   (xx[K-1]*300 + 400, -yy[K-1]*300 + 400+20, 10);

        txSetColor (TX_WHITE);
        if (rand() % 10 == 0)
            txTextOut (xx[K-1]*300 + 400, -yy[K-1]*300 + 400+50, "ÙÀ ÓÊÓÑÈÒ!");

        txSleep (1);
        }
    txEnd();
    }

