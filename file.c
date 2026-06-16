#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct array
{
    char KTM[15];
    char nama[30];
    struct array *next;
} array;

array *hash_table[101] = {NULL};
int collision = 0;
int idx_terisi = 0;
float score = 0;

int fungsi_hash(char KTM[]){

    int unsigned long hash = 37;
    int idx = 0;

    for(int i = 0; KTM[i] != "/0"; i++){
       int nilai_ascii = KTM[i];
       
       hash = (hash << 5 ) ^ nilai_ascii;
       hash = hash +(nilai_ascii * idx * 11);

       idx++;
    }


    return hash % 101;
}

void buat_node(char KTM[], char nama[]){
    array *newnode = (array*) malloc(sizeof(array));
    strcpy(newnode->KTM,KTM);
    strcpy(newnode->nama,nama);
    int idx = fungsi_hash(newnode->KTM);
    if (hash_table[idx] == NULL) { idx_terisi++;}
    else { collision++; }
    newnode->next = hash_table[idx];
    hash_table[idx] = newnode;
}

void baca_file(){
    FILE *file = fopen("Data_Latih.txt","r");

    if (file == NULL)
    { printf("file tidak ditemukan!\n"); return; }
    else if (fgetc(file) == EOF)
    { printf("file tidak ada isi!"); return;};
    rewind(file);

    char KTM[15];
    char nama[30];
    while (fscanf(file,"%[^,],%[^\n]\n",KTM,nama) == 2)
    { buat_node(KTM,nama); }
}

void hapus_node(){
    for (int i = 0; i < 101; i++)
    {
        array *temp = hash_table[i];
        while (temp != NULL)
        { 
            hash_table[i] = temp->next;
            free(temp);
            temp = hash_table[i];
        }
    }
}

void menu_utama(){
    char KTM[15];
    int idx = 0;
    int pilihan;
    do
    {
        pilihan = 0;
        printf("==== MENU UTAMA ====\n");
        printf("1.verifikasi e-KTM\n");
        printf("2.output data:\n");
        printf("3.keluar\n");
        printf("pilihan: ");
        scanf("%d",&pilihan);
        while(getchar() != '\n');

        switch (pilihan)
        {
        case 1:
            printf("masukkan kode e-KTM: ");
            fgets(KTM,15,stdin);
            KTM[strcspn(KTM,"\n")] = 0;
            idx = fungsi_hash(KTM);
            array *temp = hash_table[idx];
            if (temp == NULL)
            { printf("kode e-KTM tidak ditemukan!\n\n"); }
            while (temp != NULL)
            {
                if (strcmp(temp->KTM,KTM) == 0)
                { 
                    printf("kode e-KTM: %s\n",temp->KTM);
                    printf("nama: %s\n\n",temp->nama); 
                    break; 
                }
                else if (temp->next == NULL)
                { printf("kode e-KTM tidak ditemukan!\n\n"); }
                temp = temp->next;
            }
            break;
        case 2:
            score = ((float)idx_terisi / 101.0) * (1.0 - ((float)abs(collision - 399) / 500.0)) * 100.0;
            printf("\n==================================\n");
            printf("     BUKTI OUTPUT PERFORMANCE     \n");
            printf("==================================\n");
            printf("Total Tabrakan (Collision): %d\n",collision);
            printf("Jumlah Indeks Laci Terisi: %d dari 101 slot\n",idx_terisi);
            printf("Nilai Score: %.3f%% \n",score);
            printf("==================================\n\n");
            break;
        case 3:
            hapus_node();
            printf("terima kasih!\n");
            return;
        default:
            printf("input tidak valid!\n\n");
        }
    } while (pilihan != 3);
}

int main(){
    baca_file();
    menu_utama();
}