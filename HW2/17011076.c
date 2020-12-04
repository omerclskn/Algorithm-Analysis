#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define m 997

typedef struct sozluk{ // Ýcinde kelimenin degeri, keyi ve icinde oldugu dokuman bilgisini tutan structure
    int key;		
    char value[50];
    char dokuman[100];
}v;

int FindKey(char buffer[50], int secim,v table[m]){ // Horner metodu kullanýlarak kelime degerinin key hesaplanmasý
    int word_length = strlen(buffer);	// kelimenin uzunluðu
    int key=0,i=0;
    
    strlwr(buffer);
        
        if(secim==0){		// Ekleme yapýlýrken ayný deðer var ise -1 deðeri dondurulur.
        	for(i=0;i<m;i++){
    	if(strcmp(buffer,table[i].value)==0){
    		return -1;
				}
			}
		}
        for(i=0;i<word_length;i++)		// Horner Metodu ile key hesaplanmasý
        	key += buffer[i]*pow(3,i);
    return key;
}

int InsertToHash(v data,v table[m]){	// Double hashing kullanýlarak key deðerinin hash tablosuna yerlestirilmesi
    int i=0;
    
    int h1 = data.key % m;
    int h2 = 1 + (data.key%(m-1));
    int a = (h1 + i*h2) % m;
    
    while((table[a].key!=-1) && (i < m)){
		i++;
        h1 = data.key % m;
   		h2 = 1 + (data.key%(m-1));
    	a = (h1 + i*h2) % m;	
    }
    	if(table[a].key == -1){	// Adresteki yer boþ ise yerleþtirilme iþlemi
    		table[a].key=data.key;
        	strcpy(table[a].value,data.value);
        	return a;
		}
     		printf("Kelime Eklenemedi: %s\n",data.value);
     		return -1;
}

void SearchToHash(v data, char aranan[50],v table[m]){
    int i=0, flag=0;
								// Aranan kelimenin hashing algoritmasý ile bulunmasý
    int h1 = data.key % m;
   	int h2 = 1 + (data.key%(m-1));
    int a = (h1 + i*h2) % m;
    
	while((i < m) && (flag==0)){		// Eðer tabloda bulunursa adým sayýsý ve dokumaný yazdýrýlýr ardýndan dongu sonlandýrýlýr bulunamadý ise i arttýrýlarak devam edilir.
		if(strcmp(table[a].value,data.value)==0){
        printf("Aranan Kelimenin Bulundugu Dokuman: ");
        puts(table[a].dokuman);
        printf("%d Adimda Bulundu\n", i+1);
        flag=1;
        break;
    	}	
    	
		i++;
        h1 = data.key % m;
   		h2 = 1 + (data.key%(m-1));
    	a = (h1 + i*h2) % m;
    }
	if(flag==0)
        printf("Kelime Bulunamadi\n");
}

int main()
{	
	v table[m];			// hashtable
	int loadfactor=0;	// loadfactor baslanhngi0pp*0c degeri
    int i, secim=0,adr;	// yapýlacak islem icin secim, donguler icin i ve double hashing isleminden sonra donecek olan adres
	char dosya[50];		// okunacak dosya
	int flag=1,flag2=1;	// loadfactor kontrolleri icin gerekli degiskenler
	
	FILE* sozluk;
    sozluk = fopen("17011076.txt","r");
        for(i=0;i<m;i++){
            table[i].key=-1;
            }
        if (sozluk == NULL){
            printf("Dosya acilamadi.");
                return 0;
                }
		else{
            printf("Hash Dosyasi 17011076.txt olarak basariyla acildi\n");
            char buffer[50];
            while (fscanf(sozluk, "%s", buffer) > 0){	// hash dosyasýnýn kelime kelime okunmasý - sozluk.txt
            	
            	if(strcmp(buffer,"loadfactor")==0){		// Eger sozluk.txt dosyasýnda loadfactor degeri varsa okunacak
					fscanf(sozluk, "%d", &loadfactor);
					continue;
				}
                v data;			// Kelimenin structure a keyi ile beraber eklenmesi
                data.key=FindKey(buffer,0,table);
                strcpy(data.value,buffer);
                adr=InsertToHash(data,table);
                char temp[50];
				fscanf(sozluk, "%s", temp);		// Dokuman bilgisinin okunmasý
                strcpy(table[adr].dokuman,temp);
                    }
                }           
    fclose(sozluk);
    
    printf("LoadFactor: %f\n",(float)loadfactor/m);
    while(secim==0 || secim==1){
	
	printf("\nDokuman eklemek icin 0, kelime aramak icin 1 e basiniz: ");
	scanf("%d",&secim);
	
	if(secim==0){
	printf("Dokuman dosyasinin adini giriniz: ");
	scanf("%s",dosya);
	
	FILE* dokuman;
	dokuman = fopen(dosya, "r");
        if (dosya == NULL){
            printf("Dosya acilamadi.");
            return 0;
			}
		else{
            printf("Dosya acildi.\n\n");
            char buffer2[50];
        	while (fscanf(dokuman, "%s", buffer2) > 0 && flag==1){
                v data;
                	if(FindKey(buffer2,0,table)!=-1){		// Dokumandan kelime eklenmesi eger tabloda zaten var ise bu islemin yapýlmasýna gerek yok
                        data.key=FindKey(buffer2,0,table);
                   		strcpy(data.value,buffer2);
                   		int a = InsertToHash(data,table);
                   		strcpy(table[a].dokuman,dosya);
                   		if(a!=-1)
						   loadfactor++;
					}
					else{		// Zaten var olan bir kelime ekleniyor ise dokuman bilgisinin alýnmasý
						strlwr(buffer2);
						for(i=0;i<m;i++){
							if(strcmp(table[i].value,buffer2)==0 && strcmp(table[i].dokuman,dosya)!=0){
								strcat(table[i].dokuman,dosya);
									}
								}
							}
					if(((float)loadfactor/m) > 0.8 && flag2==1){
							printf("--- Uyari: LoadFactor 0.8 esigini gecti ---\n");
							flag2=0;
							}
					else if((float)loadfactor/m==1){
						printf("--- Uyari: LoadFactor 1 oldu Ekleme Durduruldu ---\n\n");
						flag=0;
							}
                    	}
                    	
            if(flag==0){
                    while (fscanf(dokuman, "%s", buffer2) > 0){
                    	printf("Kelime Yazdirilamadi: %s - Loadfactor=1\n",buffer2);
							}
                		}
					}      
            fclose(dokuman);
            
            FILE *fp=fopen("17011076.txt","w");		// Hash tablosuna alýnan degerlerin 17011076.txt dosyasýna yazýlmasý
            	for(i=0;i<m;i++){
                	if(table[i].key!=-1){
                		fprintf(fp,"%s %s\n",table[i].value,table[i].dokuman);
						}
            		} 
			fprintf(fp,"%s %d","loadfactor",loadfactor);	// Loadfactor 17011076.txt dosyasýna yazdýrýlýr.
            fclose(fp);
            printf("Loadfactor: %f\n",(float)loadfactor/m);	// Loadfactor degerinin m degerine bolunerek yazdýrýlmasý int deger oldugu icin basina float koyduk.
                			
        	printf("Hash Tablosu Basariyla Olusturuldu.\n");
}	
	if(secim==1){
		char aranan[50];			// Aranan kelimenin key degerinin ve kendisinin tabloda aramak uzerine structure yapýsýna eklenmesi
            printf("\nAranacak kelimeyi giriniz:");
            scanf("%s",aranan);
            v data;
            data.key=FindKey(aranan,1,table);
            strcpy(data.value,aranan);
            SearchToHash(data,aranan,table);
				}
			}
    		return 0;
		}
