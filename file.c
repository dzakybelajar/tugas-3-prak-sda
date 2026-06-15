#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct array
{
    char KTM[15];
    char nama[30];
    array *next;
} array;

array *hash_table[101];

void buat_node(char KTM, char nama){
    array *newnode = (array*) malloc(sizeof(array));
    strcpy(newnode->KTM,KTM);
    strcpy(newnode->nama,nama);
    int idx = fungsi_hash(newnode->KTM);
    newnode->next = hash_table[idx];
    hash_table[idx] = idx;
}

int fungsi_hash(char KTM[15]){
    int idx;

    return idx;
}

void baca_file(){
    FILE *file = fopen("Data_Latih.txt",'r');

    if (file == NULL)
    { printf("file tidak ditemukan!\n"); return; }
    else if (fgetc(file) == EOF)
    { printf("file tidaka ada isi!\n"); return; }
    
    char KTM[15];
    char nama[30];
    while (fscanf(file,"%[^,],%[^\n]",KTM,nama) == 2)
    { buat_node(KTM,nama); }
}

void hapus_node(){
    
}

void menu_utama(){
    char KTM[15];
    int pilihan;
    do
    {
        pilihan = 0;
        printf("==== MENU UTAMA ====\n");
        printf("1.verifikasi e-KTM\n");
        printf("2.keluar\n");
        printf("pilihan: ");
        scanf("%d",&pilihan);
        while(getchar() != "\n");

        switch (pilihan)
        {
        case 1:
            printf("masukkan kode e-KTM: ");
            fgets(KTM,15,stdin);
            fungsi_hash(KTM);
            break;
        case 2:
            hapus_node();
            printf("terima kasih!\n");
            return;
        default:
        printf("input tidak valid!\n");
        }
    } while (pilihan == 0);
}

int main(){
    baca_file();
    menu_utama();
}