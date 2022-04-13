#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int rahanNostaminen(int saldo);
void saldonTarkastelu(int saldo);
void tapahtumienTarkastelu(void);
void lueRoskat(void);

int main()
{
    int valinta;
    int saldo;
    char oikeapin[5];
    char pinsyote[5];
    char tilinro[10];
    FILE *filu;
    FILE *temp;
    int tulos = 1;


    do {
        printf("Anna tilin numero: ");
        fgets(tilinro, 10, stdin);

        if (tilinro[strlen(tilinro)-1] == '\n')
            tilinro[strlen(tilinro)-1] = '\0';
        else
            lueRoskat();

        strcat(tilinro, ".acc");

        if ((filu = fopen(tilinro, "r")) != NULL)
            {
            printf("Anna PIN-koodi: ");

            fgets(pinsyote, 5, stdin);

            if (pinsyote[strlen(pinsyote) - 1] == '\n')
                pinsyote[strlen(pinsyote) - 1] = '\0';
            else
                lueRoskat();


         fgets(oikeapin, 10, filu);

         do {
            if (oikeapin[strlen(oikeapin) - 1] == '\n')
               oikeapin[strlen(oikeapin) - 1] = '\0';

            if ((tulos = strcmp(oikeapin, pinsyote)) == 0)
                {
               fscanf(filu, "%d", &saldo);
                }
            else
               printf("Vaara PIN-koodi, yrita uudestaan\n");

            }
        while(tulos != 0);

            }
        else
        {
         printf("Tilia ei ole olemassa\n");
        }

   }
   while(tulos != 0);

    printf("Tama on paavalikko. Valitse toiminto.\n");
    printf("[1] Otto\n[2] Saldo\n[3] Tapahtumat\n[0] Lopeta\n");
    scanf("%d", &valinta);

    while(valinta >= 1)
    {
        switch(valinta)
        {
            case 1:
                saldo = rahanNostaminen(saldo);
                break;

            case 2:
                saldonTarkastelu(saldo);
                break;

            case 3:
                tapahtumienTarkastelu();
                break;

            default:
                printf("Virheellinen valinta, valitse uudestaan\n");
                break;
        }
        printf("\nTama on paavalikko. Valitse toiminto.\n");
        printf("[1] Otto\n[2] Saldo\n[3] Tapahtumat\n[0] Lopeta");
        scanf("%d", &valinta);
    }

    temp = fopen("temp.acc", "w");

    if(temp == NULL)
        printf("Virhe luodessa temp-tiedostoa");

    fprintf(temp, "%s\n%d", oikeapin, saldo);

    fclose(filu);
    fclose(temp);
    remove("12345.acc");
    rename("temp.acc", "12345.acc");

    fclose(filu);
    printf("Kiitos kaynnista, tervetuloa uudestaan\n");
    return 0;
}

int rahanNostaminen(int saldo)
{
    int summa;
    int temp = 0;

    printf("\nOtto\n");
    printf("Syota 0 palataksesi paavalikkoon\n");

    while(temp == 0)
    {
    printf("Valitse nostettava summa: ");
    scanf("%d", &summa);

    if(summa == 0)
        return saldo;

    if(summa < saldo && summa >= 20 && summa <= 1000 && (summa % 10 == 0) && summa != 30)
    {
        if(((summa % 50) % 20) == 0)
        {
            printf("Tililta nostettu %d euroa\n", summa);
            printf("%d x 50 euroa, %d x 20 euroa\n", (summa / 50), ((summa % 50)/20));
            saldo = saldo - summa;
            temp++;
        }

        if(((summa % 50) % 20) != 0)
        {
            printf("Tililta nostettu %d euroa\n", summa);
            printf("%d x 50 euroa, %d x 20 euroa\n", ((summa / 50) - 1), (((summa % 50) + 50)/20));
            saldo = saldo - summa;
            temp++;
        }


        printf("Paina ENTER jatkaaksesi\n");
        while(1)
            if (kbhit()) break;
    }

    else
        printf("Virheellinen summa, kokeile uudestaan\n");
    }

     return saldo;
}

void saldonTarkastelu(int saldo)
{
    printf("\nSaldo\n");
    printf("Tililla on %d euroa\n", saldo);
    printf("Paina ENTER jatkaaksesi\n");
    while(1)
        if (kbhit()) break;
}

void tapahtumienTarkastelu(void)
{
    printf("Tapahtumia ei ole, koska niita ei ole koodattu :(\n");
    printf("Paina Enter jatkaaksesi");
    while(1)
        if (kbhit()) break;
}

void lueRoskat(void)
{
   while(fgetc(stdin) != '\n');
}
