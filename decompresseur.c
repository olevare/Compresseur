#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tabindex[256][257]; //cr�ation du tableau a 2 dimension dont la ligne 0 comprendra le caract�re et en dessous le code du caract�re

void initindex(char *argv1) //initialise l'index
{
    FILE *fc;
    int i; //indice ligne
    int j; //indice colonne
    int k=0;
    char c;
    for(i=0; i<256; i++) //boucle pour initialiser le tableau avec des valeurs connue et ne pas tomber sur des valeurs al�atoire
        for(j=0; j<257; j++)
            tabindex[i][j]='*';
    fc=fopen(argv1,"r");
    while(c != '.') //boucle qui sert a passer le nombre de caract�re qui se trouve au s�but du fichier
        c=fgetc(fc);
    j=0;
    while(k<5) //boucle qui v�rifie qu'il n'a pas rencontrer les 3 points et donc la fin de l'index
    {
        i=0;
        c=fgetc(fc);
        if(c=='.') //si il rencontre un point il le stoke dans une variable
            k++;
        else
            k=0; //sinon reinitialise la variable
        tabindex[i][j]=c;
        printf("\n le code du caractere %c est: ",c);
        while((c=fgetc(fc)) != '.') //boucle qui copie le code du caract�re sous le caract�re dans le tableau
        {
            i++;
            tabindex[i][j]=c;
            printf("%c",c);
        }
        k++;
        j++;
    }
    fclose(fc);
}

int calculNbCaract(char *argv1) //calcule le nombre de caract�re
{
    FILE *fc;
    int n=0;
    int k=0;
    int t;
    int i=0;
    int j=0;
    int l=0;
    char c;
    fc=fopen(argv1,"r");
    while((c = fgetc(fc)) != '.')//calcule en nombre de caractere le nombre de caratere (si 457 caract�re alors nombre de caract�re egal 3)
        n++;
    fseek(fc, SEEK_SET, 0);
    while((c = fgetc(fc)) != '.')//boucle qui calcule le nombre de caractere (obtient la valeur 457)
    {
        t=c;
        t=t-48;
        i=l;
        i++;
        l=i;
        j=1;
        for(i; i<n; i++)
            j=j*10;
        k=k+(t*j);//k=nombre de caract�re
    }
    return k;
}

void buffer(char *argv1) //creer le buffer pour ensuite redecompresser le fichier
{
    FILE *fc;
    FILE *fb;
    char c;
    int i=0;
    int n;
    fc=fopen(argv1,"r");
    while(c != EOF) //boucle qui permet de se mettre a la fin de l'index
    {
        c=fgetc(fc);
        if(c=='.') //si c est un point incr�mente la variable
        {
            i++;
            if(i == 5) //si i egal 3 alors on a atteint la fin de l'index
                c=EOF;
        }
        if(c != '.') //si c diff�rent d'un point reinitialise la variable
            i=0;
    }
    c=fgetc(fc); //passe un caractere qui est le retour a la ligne
    fb=fopen("buffer2.txt","a+");
    while((c=fgetc(fc)) != EOF)//creer le buffer
    {
        n=c; //r�cup�re la valeur du caract�re
        if(n==2)
            n=255;
        if(n<0)
            n=256+n;
        i=128;
        while(n != 2000) //boucle qui permet de decomposer la valeur du caract�re en fonction des puissance de 2
        {
            if((n-i) >= 0)
            {
                fprintf(fb,"1");
                n=n-i;
            }
            else
                fprintf(fb,"0");
            if(i == 1)
                n=2000;
            i=i/2;
        }
    }
    fclose(fc);
    fclose(fb);
}

void decompresser(int NbCaract, char *argv2)
{
    FILE *fb;
    FILE *fd;
    int n=20;
    int i=0;
    int a; //indice ligne
    int b; //indice colonne
    int k=0;
    char c;
    char *tabbuffer;
    fb=fopen("buffer2.txt","r");
    tabbuffer=malloc(n*sizeof(char));
    while((c=fgetc(fb)) != EOF)//creer le tableau du buffer
    {
        tabbuffer[i]=c; //copie le buffer dans le tableau
        if(i == (n-1)) //si on atteint la fin du tableau on l'agrandi
        {
            n=n+20;
            tabbuffer=realloc(tabbuffer,n);
        }
        i++;
    }
    fclose(fb);
    remove("decompresser.txt");
    fd = fopen(argv2,"a+");
    i=0;
    n=0;
    while(NbCaract>0)//boucle qui decompresse le fichier tant qu'il n'a pas atteint le nombre de caract�re du fichier de base
    {
        a=1;
        b=0;
        c='+'; //variable d'entrer et de sortie de boucle
        i=0;
        while(c != '-')
        {
            while(tabindex[a][b] == tabbuffer[n+i]) //boucle qui compare le buffer a une colonne de la table d'index
            {
                i++;
                a++;
            }
            if(tabindex[a][b] == '*') //quand l'index est diff�rent regarde si c'est parce que c'est la fin ou si c'est pas le bon caract�re
            {
                fprintf(fd,"%c",tabindex[0][b]);
                n=n+i;
                c='-';
            }
            else //sinon reinitialise les valeurs et passe a la colonne de caract�re suivante
            {
                a=1;
                b++;
                i=0;
            }
        }
        NbCaract--; //decremente le nombre de caract�re du fichier de depart
    }
    fclose(fd);
    remove("buffer2.txt");
    free(tabbuffer);
}

void calculeTaille(char *argv2)
{
    FILE *fd;
    fd=fopen(argv2,"r");
    fseek(fd, 0, SEEK_END);
    int taille1=ftell(fd);
    printf("\n \n La taille du fichier decompresse est : %d\n",taille1);
    fclose(fd);
}

int main(int argc, char *argv[])
{
    int NbCaract;
    int ttableau;
    initindex(argv[1]);
    NbCaract = calculNbCaract(argv[1]);
    buffer(argv[1]);
    decompresser(NbCaract, argv[2]);
    calculeTaille(argv[2]);
    return 0;
}
