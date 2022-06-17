#include "header.h"



void kreirajZaposlenika(void) {

    FILE * fp = NULL;
    ZAPOSLENIK * zap = NULL;
    zap = (ZAPOSLENIK * ) calloc(1, sizeof(ZAPOSLENIK));
    if (zap == NULL) {
        perror("zauzimanje memorije");
        exit(EXIT_FAILURE);
    }
    fp = fopen("datoteka.bin", "ab");
    if (fp == NULL) {
        perror("datoteka");
        exit(EXIT_FAILURE);
    }
    int provjeraKor;
    int provjeraID1;
    int k = brojZap();
    printf("Upisite korisnicko ime: ");
    do {
        scanf("%s", zap->korisnickoIme);
        provjeraKor = provjeraKorisnika(k, zap -> korisnickoIme);
        if (provjeraKor == 1) {
            printf("Ovo korisnicko ime se vec koristi, pokusajte ponovo: ");
        }
    } while (provjeraKor != 0);
    char * sifra1;
    printf("Upisite sifru: ");
    getchar();
    sifra1 = sifra();
    strcpy(zap -> sifra, sifra1);
    printf("Upisite ime: ");
    scanf("%s",zap -> ime);
    
    if (zap -> ime[0] >= 97 && zap -> ime[0] <= 122) {
        zap -> ime[0] = (zap -> ime[0]) - 32;
    }
    printf("Upisite prezime: ");
    scanf("%s",zap -> prezime);
    if (zap -> prezime[0] >= 97 && zap -> prezime[0] <= 122) {
        zap -> prezime[0] = (zap -> prezime[0]) - 32;
    }
    printf("Upisite ID: ");
    do {
        scanf("%d", & zap -> ID);
        provjeraID1 = provjeraID(k, zap -> ID);
        if (provjeraID1 == 1) {
            printf("Ovaj ID je zauzet, pokusajte ponovo: ");
        }
    } while (provjeraID1 != 0);
    printf("Upisite placu: ");
    scanf("%f", & zap -> placa);
    fwrite(zap, sizeof(ZAPOSLENIK),1, fp);
    printf("Uspjesna registracija zaposlenika.\n");
    free(sifra1);
    free(zap);
    fclose(fp);

}





char * sifra(void) {
    const int max = 15;
    char * Sifra;
    Sifra = calloc(max + 1, sizeof(char));
    if (Sifra == NULL) {
        return 0;
    }
    char ch;
    int pozicija = 0;
    while (1) {
        ch = getch();
        if (ch == 10) {
            break;
        } else if (ch == 32 || ch == 9 || ch == 8) {
            continue;
        } else {
            if (pozicija < max) {
                Sifra[pozicija] = ch;
                pozicija++;
                printf("*");
            } else {
                printf("\nPreskocili ste maksimalan broj karaktera sifre koji iznosi:%d.", max);
                break;
            }
        }
    }
    Sifra[pozicija] = '\0';
    printf("\n");
    if (strlen(Sifra) == 0) {
        printf("\nNije unesena sifra.\n ");
    } else if (strlen(Sifra) < 6) {
        printf("Sifra mora biti barem 6 karaktera, pokusajte ponovo: ");
        free(Sifra);
        Sifra = sifra();
    } else {
        return Sifra;
    }

}





int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, & oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, & newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, & oldattr);
    return ch;
}




int brojZap(void) {

    FILE * fp = NULL;
    if((fp=fopen("datoteka.bin","rb"))==NULL){
            
    }else{
    int i=0;
    ZAPOSLENIK zap;
    while(fread(&zap, sizeof(ZAPOSLENIK), 1, fp)){
        i++;
    }
    fclose(fp);
    return i;
}
}






void ispisZap(int z) {
     FILE * fp = NULL;
    if (z == 0||(fp = fopen("datoteka.bin", "rb"))==NULL) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");

    } else {
        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("zauzimanje memorije");
            exit(EXIT_FAILURE);
        }
        fread(zaposlenici, sizeof(ZAPOSLENIK), z,fp);
         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {
            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
        free(zaposlenici);
        fclose(fp);
    }
}






void login(int k) {
     FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.bin","rb"))==NULL) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");

    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("zauzimanje memorije");
            exit(EXIT_FAILURE);
        }
        fread(zaposlenici, sizeof(ZAPOSLENIK), k,fp);
        fclose(fp);
        char korisnik[15];
        printf("korisnicko ime: ");
        scanf("%s", korisnik);
        int provj = 0;
        int i = 0;
        do {
            if ((strcmp(korisnik, (zaposlenici + i) -> korisnickoIme)) == 0) {
                provj = 1;
                break;
            }
            i++;
        } while (k > i);
        int pokusaj = 0;
        char * sifra1;
        int oslobodenje=0;
        if (provj == 1) {
            printf("Korisnicko ime nadeno, upisite sifru, ");
            getchar();
            do {
                pokusaj++;
                printf("imate jos %d pokusaj/a: ", 5 - pokusaj);
                sifra1 = sifra();
                if (strcmp(sifra1, (zaposlenici + i) -> sifra) == 0) {
                    oslobodenje=1;
                    printf("Sifra tocna.\n");
                    free(sifra1);
                    free(zaposlenici);
                    int uvijet = 1;
                    while (uvijet) {
                        uvijet = izbornikZaposlenik(i);
                    }
                    break;
                }else{
                    free(sifra1);
                }
            } while (pokusaj < 4);

        } else {
            printf("Korisnicko ime nije nadeno! pokusajte ponovo upisat ");
            free(zaposlenici);
            login(k);
        }
        if ((oslobodenje==0)&&(pokusaj==4)) {
            free(zaposlenici);
            printf("Sifra netocna, vracam na izbornik.\n");
        }
    }
}





void promjenaSifre(int s, int z) {
    FILE * fp = NULL;
    fp = fopen("datoteka.bin", "rb");
    if (fp == NULL) {
        perror("greska u otvaranju");
        exit(EXIT_FAILURE);
    }
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("zauzimanje memorije");
        exit(EXIT_FAILURE);
     }
    fread(zaposlenici, sizeof(ZAPOSLENIK), z,fp);
    printf("Upisite novu sifru: ");
    char * novasifra;
    getchar();
    novasifra = sifra();
    strcpy((zaposlenici + s) -> sifra, novasifra);
    fclose(fp);
    fp = fopen("datoteka.bin", "wb");

    fwrite(zaposlenici, sizeof(ZAPOSLENIK),z, fp);  
    
    free(zaposlenici);
    fclose(fp);
    free(novasifra);
}


void stvoriBiljesku(char *ime){
    FILE *fp=NULL;
    fp=fopen(ime, "a");
    if (fp == NULL) {
            perror("greska u otvaranju");
            exit(EXIT_FAILURE);
        }
    char p;
    printf("\nUpisite biljesku: ");
    while((p=getchar())!=10){
        putc(p, fp);
    }
    fprintf(fp, "\n");
    
    fclose(fp);
    
}



void citajBiljesku(char *ime){
    FILE *fp=NULL;
    if((fp=fopen(ime,"r"))==NULL){
        printf("\nNema biljeske!\n");
    }else{
    fp=fopen(ime, "r");
    printf("\nVasa biljeska:\n");
    char p;
	while ((p = getc(fp)) != EOF) {
		printf("%c", p);
	}
    
    fclose(fp);
    }
}








void obirisiZaposlenika(int z) {
   FILE * fp = NULL;

    if ((fp = fopen("datoteka.bin", "rb"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");
    }else{
        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("zauzimanje memorije");
            exit(EXIT_FAILURE);

        }
         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
         fread(zaposlenici, sizeof(ZAPOSLENIK), z,fp);
        for (int i = 0; i < z; i++) {
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
        fclose(fp);
        printf("\nUnesite ID zaposlenika koji zelite obrisat: ");
        int zapID;
        int provjera=0;
        do{
        scanf("%d", &zapID);
        for(int i=0; i<z; i++){
        if((zaposlenici+i)->ID==zapID){
            provjera=1;
            break;
        }
        }
        if(provjera==1){
            break;
        }
        printf("\nNe postoji zaposlenik s tim ID-om, pokusajte ponovo: ");
        }while(1);
        fp = fopen("datoteka.bin", "wb");
        for (int i = 0; i < z; i++) {
            if (zapID == (zaposlenici+i)->ID) {
                continue;
            }
                fwrite((zaposlenici+i), sizeof(ZAPOSLENIK),1, fp); 
        }
        printf("\nZaposlenik uspjesno obrisan!\n");
        fclose(fp);
        free(zaposlenici);
    }
}





void sortirajPlacaVeca(int z) {
    FILE * fp = NULL;

    if ((fp = fopen("datoteka.bin", "rb"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n");
    }else{
        
    int i, j;
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("zauzimanje memorije");
        exit(EXIT_FAILURE);
    }
        fread(zaposlenici, sizeof(ZAPOSLENIK), z,fp);

    fclose(fp);

zaposlenici=sortVeca(z, zaposlenici);

         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {

            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
    free(zaposlenici);

}
}


ZAPOSLENIK *sortVeca(int z, ZAPOSLENIK *zaposlenici){
    int i, j;
    int min = -1;
    for (i = 0; i < z - 1; i++) {
        min = i;
        for (j = i + 1; j < z; j++) {
            if ((zaposlenici + j) -> placa > (zaposlenici + min) -> placa) {
                min = j;
            }
        }
        zamjena((zaposlenici + i), (zaposlenici + min));
    }
    return zaposlenici;
}


void sortirajPlacaManja(int z) {
    FILE * fp = NULL;

    if ((fp = fopen("datoteka.bin", "rb"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n");
    }else{
        int i, j;
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("greska");
        exit(EXIT_FAILURE);
    }

        fread(zaposlenici, sizeof(ZAPOSLENIK), z,fp);


    fclose(fp);

zaposlenici=sortManja(z, zaposlenici);

         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {
            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
    free(zaposlenici);

}
}

ZAPOSLENIK *sortManja(int z, ZAPOSLENIK *zaposlenici){
    int i, j;
    int min = -1;
    for (i = 0; i < z - 1; i++) {
        min = i;
        for (j = i + 1; j < z; j++) {
            if ((zaposlenici + j) -> placa < (zaposlenici + min) -> placa) {
                min = j;
            }
        }
        zamjena((zaposlenici + i), (zaposlenici + min));
    }
    return zaposlenici;
}




void sortirajIme(int z) {
    FILE * fp = NULL;

    if ((fp = fopen("datoteka.bin", "rb"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n");
    }else{
    int i,j;
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("zauzimanje memorije");
        exit(EXIT_FAILURE);
    }
    fread(zaposlenici, sizeof(ZAPOSLENIK), z,fp);
        
    fclose(fp);

    zaposlenici=sortIme(z, zaposlenici);

         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {
            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
    free(zaposlenici);
}
}


ZAPOSLENIK *sortIme(int z, ZAPOSLENIK *zaposlenici){
    int i, j;
    int min = -1;
    for (i = 0; i < z - 1; i++) {
        min = i;
        for (j = i + 1; j < z; j++) {
            if ((zaposlenici + j) -> ime[0] < (zaposlenici + min) -> ime[0]) {
                min = j;
            }
        }
        zamjena((zaposlenici + i), (zaposlenici + min));
    }
    return zaposlenici;
}




void zamjena(ZAPOSLENIK * veci, ZAPOSLENIK * manji) {
    ZAPOSLENIK temp;
    temp = * manji;
    * manji = * veci;
    * veci = temp;
}




void trazenjeID(int k){
         FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.bin","rb"))==NULL) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");

    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("zauzimanje memorije");
            exit(EXIT_FAILURE);
        }
        int trazeniID;
        printf("\nUpisite ID koji trazite: ");
        scanf("%d", &trazeniID);
        int provjera=0;
        int i;
        fread(zaposlenici, sizeof(ZAPOSLENIK), k,fp);
        for (i = 0; i < k; i++) {
            if(trazeniID==(zaposlenici+i)->ID){
                provjera=1;
                break;
            }
        }
        fclose(fp);
        if(provjera==1){

            printf("\nZaposlenik naden!\n\nIme:%s\nPrezime:%s\nID:%d\nPlaca:%.2f\n\n",(zaposlenici+i)->ime, (zaposlenici+i)->prezime, (zaposlenici+i)->ID, (zaposlenici+i)->placa);
        }
        else{
            printf("\nTrazeni ID nije naden!\n");
        }
      free(zaposlenici);
        
    }
}




int provjeraKorisnika(int k, char *korisnik){
             FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.bin","rb"))==NULL) {
    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("zauzimanje memorije");
            exit(EXIT_FAILURE);
        }
        int provjera=0;
        fread(zaposlenici, sizeof(ZAPOSLENIK), k,fp);
        for (int i = 0; i < k; i++) {

            if ((strcmp(korisnik, (zaposlenici + i) -> korisnickoIme)) == 0) {
                provjera = 1;
                break;
            }
                
            }
            fclose(fp);
            free(zaposlenici);
            return provjera;
        }
    
}




int provjeraID(int k, int ID){
             FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.bin","rb"))==NULL) {
    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("zauzimanje memorije");
            exit(EXIT_FAILURE);
        }
        int provjera=0;
        fread(zaposlenici, sizeof(ZAPOSLENIK), k,fp);
        for (int i = 0; i < k; i++) {
            if (ID==(zaposlenici+i)->ID) {
                provjera = 1;
                break;
            }
            }
            fclose(fp);
            free(zaposlenici);
            return provjera;
        }
}
