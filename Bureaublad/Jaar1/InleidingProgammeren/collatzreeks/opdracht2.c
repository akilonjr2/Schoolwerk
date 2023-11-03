/*
 * Naam Björn Smitt
 * UvAnetID : 14663600
 * Studie : BSc Informatica
 *
 * opdracht_2.c:
 * − Deze opdracht bevat alle onderdelen, met uitzondering van de bonus-
 * opdracht, die gevraagd werden als onderdeel van opdracht 2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

int(c) = 2;
int(getal) = 0;
int (stoptijd) = 0;
int (stoptijd2) = 0;
int(volgend_getal) = 0;
int(grootste) = 0;
int(grootste_stop) = 0;
int(grootste_getal) = 0;
int(timer) = 0;
int(tijdelijke_stoptijd) = 0;
int (detect) = 0;
int(begingetal) = 0;

int collatz_opvolger(int getal) 
{
    //standaard formule    
    if (getal%2 == 0) 
    {
        getal= getal / 2;

    }
   
    else 
    {
        getal = 3 * getal + 1;
    }
    
    return getal;

}

int collatz_stoptijd(int getal) 
{

    if (getal == 4)
    {
        getal = getal / 2;
        stoptijd += 1;
    }

    while (getal != 4)
    {
        collatz_opvolger(getal);
    }

    printf("Resultaten collatz_stoptijd: \n");
    printf("De stoptijd is %d \n", stoptijd);
    return stoptijd;
}

int collatz_grootste(int getal) 
{

    grootste = getal;
    
    while (getal != 1) 
    {
        if (getal >= grootste) 
        {
            grootste = getal;
        }        
        
        collatz_opvolger(getal);
    }

    printf("Resultaten collatz_grootste: \n");
    printf("Het grootste getal is %d \n", grootste);
    return grootste;
}

int collatz_langste_tussen(int a, int b) 
{

    getal = a;
    timer = a;
    
    
    while (timer <= b) 
    {

        while (getal != 1) 
        {
            collatz_opvolger(getal);

            if (getal > grootste) 
            {
                grootste = getal;
            }            
        }
    
        //+1 sinds de code stopt bij het getal 1 en telt de laatste stoptijd
        //niet mee, is de stoptijd 1 van het echte resultaat af. Sinds
        //het altijd zo is, wordt opgelost met op +1 bij de stoptijd.
        
        stoptijd += 1;

        if (grootste_stop <= stoptijd) 
        {
            grootste_stop = stoptijd;
        }

        stoptijd = 0;
        getal = a;
        timer = timer + 1;
        a +=1;
        getal = a;

    }

    printf("Resultaten collatz_langste_tussen: \n");
    printf("Het grootste getal is %d \n", grootste);
    printf("De langste stoptijd is %d \n", grootste_stop);
    return grootste;
    return grootste_stop;
}

int collatz_grootste_tussen(int a, int b) 
{

    getal = a;
    timer = a;
    
    while (timer <= b) 
    {

        while (getal != 1) 
        {

            if (getal%2 == 0) 
            {
                getal = (getal / 2);
                stoptijd += 1;

            }
            
            else 
            {
                getal = (3 * getal) + 1;
                stoptijd +=1;
            }

            if (getal > grootste) 
            {
                grootste = getal;
                tijdelijke_stoptijd = true;
            }
        }

        if (tijdelijke_stoptijd == true)
        {
            grootste_stop = stoptijd;
            printf("%d\n", grootste_stop );
        }
        
        tijdelijke_stoptijd = false;
        stoptijd += 1; //Dezelfde oplossing als bij vorige functie.
        stoptijd = 0;
        getal = a;
        timer = timer + 1;
        a +=1;
        getal = a;

    }
    
    printf("Resultaten collatz_grootste_tussen: \n");
    printf("Het grootste getal is %d \n", grootste);
    printf("De stoptijd die daarbij hoort is %d \n", grootste_stop);
    return grootste;
    return stoptijd;
}

void collatz_maximum(void) 
{

    detect = 0;

    while (detect != 1) 
    {

        getal = c;
        begingetal = getal;
       
        while (getal != 1)
        {

            if (getal%2 == 0) 
            {
                getal = (getal / 2);
            }       
            
            else 
            {
                
                if (getal >= 715827882) 
                {
                    
                    printf("Resultaten Collatz_maximum: \n");
                    printf("Er heeft een overflow plaatsgevonden \n");
                    printf("Dit ontstond bij de reeks met het \n");
                    printf("begingetal %d \n", begingetal);
                    detect = 1;
                    return;

                }
                
                getal = (3 * getal) + 1;
            }
        }
        
        begingetal = 0;
        c += 1;
    }
}

void collatz_maximum_verlengd(void) 
{
    // Implementeer en documenteer deze functie
}

#ifndef COMPILE_MAIN
int main(int argc, char **argv)
{
    // Check of genoeg argumenten van het juiste type aangeleverd zijn.
    if (argc != 3 || !isdigit(*argv[1]) || !isdigit(*argv[2])) 
    {
        return EXIT_FAILURE;
    }

    // Converteer string argumenten naar integers.
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    // Check of de conditie a < b geldt en of a en b positieve getallen zijn.
    if (a >= b || a <= 0 || b <= 0) 
    {
        return EXIT_FAILURE;
    }
    
    getal = a;
    collatz_opvolger(getal);
    
    // Roep de collatz_langste_tussen en collatz_grootste_tussen functies aan.
    collatz_langste_tussen(a, b);
    collatz_grootste_tussen(a, b);

    // Roept de funcite collatz_maximum aan.
    collatz_maximum();
    // collatz_maximum_verlengd();

    return EXIT_SUCCESS;
}
#endif

