#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noeud //cree la structure noeud
{
    int pere;
    int filsg;
    int filsd;
    float frequence;
};

struct noeud arbre[511]; //creation du tableau de noeud

void calfrequence(char *argv1, char *argv2) //algo qui calcule les frequences
{
    FILE *fd;
    FILE *fc;
    char c;
    int i;
    int n=0;
    int f=0;
    if((fd = fopen(argv1, "r")) != NULL) //vérifie si le fichier est vide
    {
        while((c = fgetc(fd)) != EOF) //parcourt le fichier texte
        {
            i=c;
            if(i<=0)
                i=256+i;
            arbre[i].frequence=arbre[i].frequence+1;
            n=n+1;
        }
        if(n<=1)
        {
            printf("Le fichier est vide ou ne possede qu'un seul caractere donc il ne sert a rien de le compresser");
            return 0;
        }
        fc=fopen(argv2,"a+");
        fprintf(fc,"%d",n);
        fclose(fc);
        printf("\n");
        fclose(fd);
    }
    else
        printf("fichier inaccessible \n"); //condition si le fichier est vide
    printf("FREQUENCE: \n \n");
    for(i=0; i<256; i++)
    {
        arbre[i].frequence=arbre[i].frequence/n; //calcule la frequence en fonction du nombre de caractère
        if(arbre[i].frequence >0)
            printf("Le caractere %c a une frequence de %f \n",i,arbre[i].frequence);
    }
    printf("\n \n");
}


void initarbre() //initialise le tableau de noeud
{
    int i;
    for(i=0; i<511; i++)
    {
        if(i<256)
        {
            arbre[i].pere=-1;
            arbre[i].filsg=-1;
            arbre[i].filsd=-1;
        }
        else
        {
            arbre[i].pere=-1;
            arbre[i].filsg=-1;
            arbre[i].filsd=-1;
            arbre[i].frequence=0;
        }
    }
}

void generarbre()
{
    int inoeudracine=256;
    float min1;
    float min2;
    int i;
    int j;
    int k;
    for(i=0; i<256; i++)
    {
        if((arbre[i].frequence)==1) //cas ou il n'y a que un seul caractère
        {
            arbre[inoeudracine].frequence=arbre[i].frequence;
            arbre[inoeudracine].filsg=i;
            arbre[i].pere=inoeudracine;
            return 0;
        }
    }
    do
    {
        min1=2;
        min2=2;
        for(i=0; i<511; i++) //recherche minimum 1
        {
            if(arbre[i].frequence != 0)
            {
                if(arbre[i].frequence<min1)
                {
                    min1=arbre[i].frequence;
                    j=i;
                }
            }
        }
        arbre[j].frequence=0; //change la valeur pour ne pas la reprendre
        for(i=0; i<511; i++) //recherche minimum 2
        {
            if(arbre[i].frequence != 0)
            {
                if(arbre[i].frequence<min2)
                {
                    min2=arbre[i].frequence;
                    k=i;
                }
            }
        }
        arbre[k].frequence=0; //change la valeur pour ne pas la reprendre
        if((min1 != 2) && (min2 != 2)) //si il y a deux minimums
        {
            arbre[inoeudracine].frequence=min1+min2;
            arbre[inoeudracine].filsg=j;
            arbre[inoeudracine].filsd=k;
            arbre[j].pere=inoeudracine;
            arbre[k].pere=inoeudracine;
            inoeudracine=inoeudracine+1;
        }
    }
    while((min1 != 2) && (min2 != 2));
    return 0;
}

void parcours(char *argv2)
{
    FILE *fc;
    int i;
    int j;
    int k;
    int e;
    int tab[200]; //tableau qui enregistre le caractère et le chemin de la racine a la feuille
    for(i=0; i<200; i++) //initialise le tableau
        tab[i]=-1;
    fc = fopen(argv2, "a+"); //créer un fichier texte contenant l'index
    printf("CODES: \n \n");
    for(i=0; i<256; i++)
    {
        e=1;
        if(arbre[i].pere != -1) //parcout les feuille voir si il possède un père
        {
            printf("Le caractere %c ou %d a pour chemin: ",i,i);
            tab[0]=i; //enregistre le caractère a la première case du tableau
            j=arbre[i].pere;
            k=i; //enregistre la feuille pour la comparer a son père et lui attribuer un chemin
            while((arbre[j].filsg != -1) && (j != -1)) //entre dans la boucle tant que le père possede un fils
            {
                if(arbre[j].filsg==k) //attribut le chemin 1 si c'est le fils gauche
                {
                    tab[e]=1;
                    e++;
                }
                if(arbre[j].filsd==k) //attribut le chemin 0 si c'est le fils droit
                {
                    tab[e]=0;
                    e++;
                }
                if(arbre[j].pere == -1) //si le père actuel n'a pas de père il m'es fin a la boucle
                    j=-1;
                k=j; //enregistre le père pour la comparer a son père et lui attribuer un chemin
                j=arbre[j].pere; //passe au père du père actuel
            }
            fprintf(fc,".%c",tab[0]); //écrit le caractère du chemin voulue dans le fichier
            j=199;
            while(j>0) //parcourt le tableau et écrit dans le fichier texte le chemin du caractère
            {
                if(tab[j] != -1)
                {
                    fprintf(fc,"%d",tab[j]);
                    printf("%d",tab[j]);
                }
                j--;
            }
            for(j=0; j<200; j++) //réinitialise le tableau
                tab[j]=-1;
            printf("\n");
        }
    }
    fprintf(fc,".....");
    printf("\n \n");
    fclose(fc);
}

void compresser(char *argv1, char *argv2)
{
    FILE *fc, *fd, *fb;
    int n=0;
    int i=0;
    int j=0;
    int k=0;
    int l=0;
    int m=1;
    int p=0;
    int r=0;
    char a='0';
    char b='1';
    char c;
    fc=fopen(argv2,"r");
    while((c = fgetc(fc)) != EOF) //boucle qui calcule la taille de l'index
        n=n+1;
    char tabindex[n]; //creer un tableau statique de l'index
    fseek(fc, SEEK_SET, 0);
    while((c = fgetc(fc)) != EOF) //boucle qui copie les elements de l'indexdans le tableau index
    {
        tabindex[i]=c;
        i++;
    }
    fclose(fc);
    fd=fopen(argv1,"r");
    fb=fopen("buffer.txt","a+");
    while((c = fgetc(fd)) != EOF) //boucle qui permet de creer le buffer dans un fichier texte
    {
        for(i=0; i<n; i++)
        {
            if((tabindex[i]==c) && (tabindex[i-1]=='.')) //cherche dans l'index le caractère du fichier
            {
                j=i;
                i=n; //permet de mettre fin a la boucle
            }
        }
        i=j;
        while((tabindex[i+1]==a) || (tabindex[i+1]==b)) //boucle qui copie le code du caractère
        {
            fprintf(fb,"%c",tabindex[i+1]); //copie le code du caractère dans un fichier texte
            i++;
            r++;
        }
    }
    fclose(fd);
    char tabcompresser[r];
    fseek(fb, SEEK_SET, 0);
    i=0;
    while((c = fgetc(fb)) != EOF) //boucle qui copie le buffer dans un tableau
    {
        tabcompresser[i]=c;
        i++;
    }
    fclose(fb);
    fc=fopen(argv2,"a+");
    fprintf(fc,"\n");
    for(i=0; i<r; i++) //boucle qui transforme le buffer en caractère pour en faire le fichier compresser
    {
        k++;
        if(k<=8) //calcule 8 par 8 les caractère du buffer pour obtenir un nombre et donc un caractère
        {
            if(tabcompresser[i]=='1') //si le caractère egal 1 alors calcul sinon passe au suivant
            {
                for(l=2; l<=k; l++)
                    m=m*2;
                p=p+(128/m);
                m=1;
            }
        }
        if((k>8) || (i==r-1)) //quand on a pris 8 caractère ou on atteint la fin du buffer
        {
            if(p==255)
                p=2;
            fprintf(fc,"%c",p); //copie dans le fichier texte le caractère
            p=0;
            k=1;
            if(tabcompresser[i]=='1')
            {
                for(l=2; l<=k; l++)
                    m=m*2;
                p=p+(128/m);
                m=1;
            }
        }
    }
    fclose(fc);
    remove("buffer.txt");
}

void calculeTaux(char *argv1, char *argv2)
{
    FILE *fd;
    FILE *fc;
    fd=fopen(argv1,"r");
    fc=fopen(argv2,"r");
    fseek(fd, 0, SEEK_END);
    int taille1=ftell(fd);
    fseek(fc, 0, SEEK_END);
    int taille2=ftell(fc);
    printf("La taille du fichier source est : %d\n",taille1);
    printf("La taille du fichier compresse est : %d\n",taille2);
    printf("Le ratio de compression est de %f\n\n\n", (float)taille2/taille1);
    fclose(fd);
    fclose(fc);
}


int main(int argc, char *argv[])
{
    calfrequence(argv[1], argv[2]);
    initarbre();
    generarbre();
    parcours(argv[2]);
    compresser(argv[1], argv[2]);
    calculeTaux(argv[1], argv[2]);
    return 0;
}
