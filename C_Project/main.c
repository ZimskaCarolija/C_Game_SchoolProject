//Aleksa Velimirovic NRT 136 21


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Boja_CRNA "\x1b[30m"
#define Boja_CRVENA "\x1b[31m"
#define Boja_ZUTA "\x1b[33m"
#define Boja_PLAVA "\x1b[34m"
#define Boja_BELA "\x1b[37m"
#define Bold_Boja "\e[1;36m"
struct Mapa
{
    int nivo;
    char naziv[20];
};
void PopuniMapu(struct Mapa mapa[]);//Popunjava niz structure mape
char** Ucitaj(int red,int kol ,FILE *fptr);//popunjava 2d niz sa karakterima iz datoteke ova funkcija vraca 2d niz kji jue dinamicki alociran
int X, Y,a=1,Kolona,Redovi,n=4, ima = 1;//N predstavlja broj mapa , X-Y predstavljaju poziciju igraca KOlone i Redovi predstavljaju velicinu 2d niza 
char pom[81];//pomocna promenjiva
struct Mapa mape[4];//niza strukture tipa mapa u kojom se cuvaju podaci o maoi
void Ispisi(char **niz, int Red, int Kolona);//ispisuje 2d niza
char** Kretanje(char** niz,int Red,int Kolona);//u funkciji uzima char i po tom charu gleda dal mis dodiruje zid i ako ne onda se pomera mis pomeranjem menja niz

main()
{
    FILE* fptr1;
    char** niz, pm;//pm je pomocna promenjiva
    int i=0,j=0;
    PopuniMapu(mape);//popunjava niz stucture tipa mapa
    printf("%s", Boja_PLAVA);
       
    printf("W,A,S,D za kretanje i - za izlaz cilj je mis P dodje do sira O * ako se mapa ne ucita lepo probajte da pritisnete enter \n");//opis kontrola
    while (ima)//vrti se cela igra
    {
           
        for (j = 0; j < n; j++)//ovaj for prelazi kroz sve nivoe
        {
      
            fptr1 = fopen(mape[j].naziv, "r");//otvaranje datoteke otvara iz niza mape datoteku za iscrtavanje mape za odredjeni nivo
            if (fptr1 == NULL)//provera greske
            {
                puts("Greska prilikok orvaranja datoteke");
                exit(1);
            };
            fgets(pom, 10, fptr1);//iz datoteke uzima 1 red i pretvaraga u int taj broj predstavlja redove
            if (!(Redovi = atoi(pom)))//provera greske
            {
                puts("Greska u citanju datoteke");
                exit(1);
            }

            fgets(pom, 10, fptr1);//iz datoteke uzima 2 red i pretvaraga  u int i taj broj [predstavlja kolone
            if (!(Kolona = atoi(pom)))//prikaz greske
            {
                puts("Greska u citanju datoteke");
                exit(1);
            }

            niz = Ucitaj(Redovi, Kolona, fptr1);//dinamicki alocira niz i popunjavaga podacima  iz tesktualnog file
            fclose(fptr1);//zatvara datoteku koja se koristila za ucitavanje
            Ispisi(niz, Redovi, Kolona);//ispisuje 2d niz na ekran
            a = 1;
            while (a)//ovaj while ce dq aradi dokle god igrac ne naidje na sir - O
            {

                niz = Kretanje(niz, Redovi, Kolona);//ova funckija se bavi pomeranjem igraca

                system("cls");//cisti ekran

                Ispisi(niz, Redovi, Kolona);//ispisuje niz 


            }


           
            for (int i = 0; i < Redovi; i++)//oslobadja se prostor 2d niza
                free(niz[i]);

        }
       printf("%s", Boja_ZUTA);//ispisuje se da se igra zavrsila
        printf("\n Uspesno ste pronasli sve sireve");
        printf("%s", Boja_BELA);
        printf("\n ako zelite da izadjete Unesite i ako zelite da natsavite unesite bilo sta drugo");
        scanf("%s", &pm);
        if (pm == 'i')//gleda dal se unelo i ako jeste porogram se zavrsava ako nije on se nastavlja
        exit(1);
    }
  
}
char** Ucitaj(int red, int kol, FILE *fptr)//funkcija koja ucitava niz iz tekstualne datoteke
{
    int i, j;
    char** niz,c;
    niz = (char**)malloc(red * sizeof(char*));  //dinamicki alocira 1 d niz
    for (i = 0; i < red; i++)
    {
        niz[i] = (char*)malloc(kol+1 * sizeof(char));//ovim svaki element niza postaje niz i tako se dinamicki napravio 2d niz
        if (niz[i] == NULL)//prikaz greske
        {
            puts("Greska pri dinamickoj dodeli memorije");
            exit(1);
        }
    }
   
    for (i = 0; i < red; i++)// popunjava se niz vrednostima
    {
        for (j = 0; j <= kol; j++)
        {
            if ((c = fgetc(fptr)) != EOF)
            {
                if (c == 'P')//provera pozicije igraca
                {
                    
                    Y = i;
                    X = j;
                   
                  
                }
                niz[i][j] = c;
               
            }
        }
    }
    return niz;
}
void Ispisi(char **niz, int Red, int Kolona)//ispisuje sadrzaj 
{
    int i, j;
    //dok ispisuje sdrzaj prverava karakterei u zavisnosti od karaktera menja boju teksta
    for (i = 0; i < Redovi; i++) {
        for (j = 0; j <= Kolona; j++) {
            if (niz[i][j] == '#')
        printf("%s", Boja_CRVENA);
            if(niz[i][j] == 'O')
                printf("%s", Boja_ZUTA);
            if (niz[i][j] == '.')
                printf("%s", Boja_CRNA);
            if (niz[i][j] == 'P')
                printf("%s", Boja_PLAVA);

            printf("%c", niz[i][j]);
        }
        
      
    }
    printf("%s", Boja_BELA);
   
}
char** Kretanje(char** niz, int Red, int Kolona)//kretanje 
{
    char st;
    int i = 0, j = 0;
    if (niz[Y][X] == 'O')//gleda dal je P na istoj poziviji kao O ako jeste nivo je predjen
    {
        puts("svaka cast nasli ste O");
        a = 0;

    }
    printf("\n");

    fflush(stdin);
    scanf("%c", &st);//cuva unos sa tastature i po tom unosu se gleda kretanje igraca


    if (st == 'a')//ide levo
    {
        if (niz[Y][X - 1] == 'O')
        {
            puts("svaka cast nasli ste O");
            a = 0;
        }
        if (niz[Y][X - 1] != '#')//proverava dal je levo niz
        {
            //zamenjuje pociciju igrqaca sa tackom koja oznacava prazno polje
            niz[Y][X] = '.';
            X = X - 1;
            niz[Y][X] = 'P';
        }
    }
    else if (st == 'd')//isto kao za a samo sto ide desno
    {
        if (niz[Y][X + 1] == 'O')
        {
            puts("svaka cast nasli ste O");
            a = 0;
        }
        if (niz[Y][X + 1] != '#')
        {
            niz[Y][X] = '.';
            X = X + 1;
            niz[Y][X] = 'P';
        }
    }
    else  if (st == 'w')//isto kao u predhodnim slucajevima smao sto ide gore
    {
        if (niz[Y - 1][X] == 'O')
        {
            puts("svaka cast nasli ste O");
            a = 0;
        }
        if (niz[Y - 1][X] != '#')
        {
            niz[Y][X] = '.';

            Y = Y - 1;
            niz[Y][X] = 'P';

        }
    }
    else if (st == 's')//ide dole
    {
        if (niz[Y + 1][X] == 'O')
        {
            puts("svaka cast nasli ste O");
            a = 0;
        }
        if (niz[Y + 1][X] != '#')
        {
            niz[Y][X] = '.';

            Y = Y + 1;
            niz[Y][X] = 'P';
        }

    }
    else if (st == 'i')//provera dal s eizlazi iz programa 
    {
        puts("IZasli ste");
        exit(1);
    }
    return niz;
}
void PopuniMapu(struct Mapa mapa[])//popujnava niz strucure tipa mapa sa podacima za mape
{
    mapa[0].nivo = 0;
    strcpy(mapa[0].naziv, "mapa1.txt");

     mapa[1].nivo = 1;
    strcpy(mapa[1].naziv, "mapa2.txt");

    mapa[2].nivo = 2;
    strcpy(mapa[2].naziv, "mapa4.txt");

    mapa[3].nivo = 3;
    strcpy(mapa[3].naziv, "mapa3.txt");
}
