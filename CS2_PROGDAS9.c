#include <stdio.h>
#include <string.h>

typedef enum {
    ANION,
    KATION
} UNSUR_TYPE;

typedef union {
    int excess;
    int missing;
} Elektron;

typedef struct {
    char simbol[3];
    int nomorAtom;
    int jumlahAtom;
    UNSUR_TYPE jenis;
    Elektron elektron;
} Unsur;

typedef struct {
    char nama[11];
    int jumlahAtom;
} Senyawa;

typedef struct {
    int n;
    int max;
} Subshell;

Subshell subshells[] = {
    {1, 2}, {2, 2}, {2, 6}, {3, 2}, {3, 6},
    {4, 2}, {3, 10}, {4, 6}, {5, 2}, {4, 10},
    {5, 6}, {6, 2}, {4, 14}, {5, 10}, {6, 6}
};

int hitungElektronValensi(int nomorAtom) {
    int total = 0;
    int max_n = 0;
    int valensi = 0;
    int i = 0;

    while (total < nomorAtom) {
        int sisa = nomorAtom - total;
        int muat = subshells[i].max < sisa ? subshells[i].max : sisa;
        total += muat;

        if (subshells[i].n > max_n) {
            max_n = subshells[i].n;
            valensi = muat;
        } else if (subshells[i].n == max_n) {
            valensi += muat;
        }

        i++;
    }

    return valensi;
}

void typeUnsurDanElektron(int elektronValensi, Unsur *unsurKe){
    if (elektronValensi < 4){
        unsurKe->jenis = KATION;
        unsurKe->elektron.excess = elektronValensi;
    }    
    else {
        unsurKe->jenis = ANION;
        unsurKe->elektron.missing = 8 - elektronValensi;
    }
}

void displayUnsur(Unsur unsurKe){
    if (unsurKe.jenis == 1){
        puts("--- Kation ---");
        printf("Simbol      : %s\n", unsurKe.simbol);
        printf("Nomor atom  : %d\n", unsurKe.nomorAtom);
        printf("Jumlah atom : %d\n", unsurKe.jumlahAtom);
        printf("Jenis       : KATION\n");
        printf("Excess      : %d\n", unsurKe.elektron.excess);
    } else {
        puts("--- Anion ---");
        printf("Simbol      : %s\n", unsurKe.simbol);
        printf("Nomor atom  : %d\n", unsurKe.nomorAtom);
        printf("Jumlah atom : %d\n", unsurKe.jumlahAtom);
        printf("Jenis       : ANION\n");
        printf("Missing     : %d\n", unsurKe.elektron.missing);
    }
}

int main(){
    Unsur unsur1, unsur2;
    printf("Masukkan simbol unsur pertama (maks 2 huruf): ");
    scanf("%s", unsur1.simbol);
    printf("Masukkan nomor atom unsur pertama: ");
    scanf("%d", &unsur1.nomorAtom);
    printf("Masukkan jumlah atom unsur pertama: ");
    scanf("%d", &unsur1.jumlahAtom);
    
    puts("");

    printf("Masukkan simbol unsur kedua (maks 2 huruf): ");
    scanf("%s", unsur2.simbol);
    printf("Masukkan nomor atom unsur kedua: ");
    scanf("%d", &unsur2.nomorAtom);
    printf("Masukkan jumlah atom unsur kedua: ");
    scanf("%d", &unsur2.jumlahAtom);

    puts("");

    int elektronValensi1 = hitungElektronValensi(unsur1.nomorAtom);
    int elektronValensi2 = hitungElektronValensi(unsur2.nomorAtom);

    typeUnsurDanElektron(elektronValensi1, &unsur1);
    typeUnsurDanElektron(elektronValensi2, &unsur2);

    if (unsur1.jenis == unsur2.jenis){
        puts("Senyawa gagal dibentuk! Unsur sama jenis");
    } else if ((unsur1.elektron.excess != unsur2.elektron.missing) || (unsur1.elektron.missing != unsur2.elektron.excess)){
        puts("Senyawa gagal dibentuk! Excess dan missing tidak cocok");
    } else {
        printf("=== Senyawa Berhasil Dibentuk ===\n");
        Senyawa s;
        char tempNama[11];
        strcpy(tempNama, unsur1.simbol);
        char tempChar[3];
        if (unsur1.jumlahAtom > 1){
            sprintf(tempChar, "%d", unsur1.jumlahAtom);
            strcat(tempNama, tempChar);
        }
        strcat(tempNama, unsur2.simbol);
        if (unsur2.jumlahAtom > 1){
            sprintf(tempChar, "%d", unsur2.jumlahAtom);
            strcat(tempNama, tempChar);
        }

        strcpy(s.nama, tempNama);
        s.jumlahAtom = unsur1.jumlahAtom + unsur2.jumlahAtom;
        printf("Nama senyawa : %s\n", s.nama);
        printf("Jumlah atom  : %d\n\n", s.jumlahAtom);
        displayUnsur(unsur1);
        displayUnsur(unsur2);
    }
    return 0;
}
