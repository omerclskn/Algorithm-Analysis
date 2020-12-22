#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define m 500

typedef struct sozluk{ // Ýcinde kelimenin degeri, keyi ve onerilen kelimeyi tutan structure
    int key;		
    char value[50];
    char oneri[50];
}ht;

int FindKey(char buffer[50], ht table[m]){ // Horner metodu kullanýlarak kelime degerinin key hesaplanmasý
    int word_length = strlen(buffer);	// kelimenin uzunluðu
    int key=0,i=0;
    
        for(i=0;i<word_length;i++)		// Horner Metodu ile key hesaplanmasý
        	key += buffer[i]*pow(3,i);
    return key;
}

int doubleHash(ht data,int i){	// Double hashing yöntemiyle adres hesaplanmasý
	int h1 = data.key % m;
    int h2 = 1 + (data.key%(m-1));
    int a = (h1 + i*h2) % m;
    return a;
}

int InsertToHash(ht data,ht table[m]){	// Double hashing kullanýlarak key deðerinin hash tablosuna yerlestirilmesi
    int i=0;
    int adr = doubleHash(data,i);
    
    while((table[adr].key!=-1) && (i < m)){	// Tabloda boþluk bulunana kadar yeni adres hesaplanýr
		i++;
        adr = doubleHash(data,i);	
    }
    	if(table[adr].key == -1){	// Adresteki yer boþ ise yerleþtirilme iþlemi, eðer error table ise onerilen kelime de yerleþtirilir.
    		table[adr].key=data.key;
        	strcpy(table[adr].value,data.value);
        	strcpy(table[adr].oneri,data.oneri);
        	return adr;
		}
     		printf("Kelime Eklenemedi: %s\n",data.value);
     		return -1;
}

void readfile(ht table[m]){
	int i, adr;
	FILE* sozluk;
    sozluk = fopen("smallDictionary.txt","r");	// Okunacak dosya
        for(i=0;i<m;i++){
            table[i].key=-1;	// Hash Tablosunun tamamýnýn keylerine -1 atanýr.
            }
        if (sozluk == NULL){
            printf("Dosya acilamadi.");
                }
		else{
            printf("Hash Tablosu smallDictionary.txt dosyasindan basariyla olusturuldu\n");
            char buffer[50];
            while (fscanf(sozluk, "%s", buffer) > 0){	// hash dosyasýnýn kelime kelime okunmasý - smallDictionary.txt
            	
                ht data;			// Kelimenin structure a keyi ile beraber eklenmesi
                data.key=FindKey(buffer,table);
                strcpy(data.value,buffer);
                adr=InsertToHash(data,table);
                    }
                }           
    fclose(sozluk);
}

int SearchToHash(ht data,ht table[m]){
    int i=0;	// Aranan kelimenin double hashing algoritmasý ile bulunmasý
    int adr = doubleHash(data,i);
    
	while((i < m)){		// Eðer tabloda bulunursa adres dondurulur yoksa 0 dondurulur
		if(strcmp(table[adr].value,data.value)==0){
        return adr;
    	}	
		i++;
        adr = doubleHash(data,i);
    }
        return 0;
}

int distance (char * word1, int len1, char * word2, int len2){	// Ýki kelimenin uzaklýgýnýn karsýlastýrýlmasý
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {	// Ýlk satýr ve ilk sütun doldurulur
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {	// Kelimelerin matriste karþýlýk gelen harflerine göre minimum uzaklýk hesplanýr 
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];	// Copy ise sol üstten cost olmadan tasýnýr.
            }
            else {
                int deleted;
                int insert;
                int substitute;
                int minimum;

                deleted = matrix[i-1][j] + 1; 		// Delete ise soldan saða 1 arttýrýlarak tasýnýr
                insert = matrix[i][j-1] + 1;		// Ýnsert ise yukarýdan aþaðýya 1 arttýrýlarak tasýnýr
                substitute = matrix[i-1][j-1] + 1;  // Change ise sol üstten 1 arttýrýlarak tasýnýr.
                minimum = deleted;		// En kucuk olan alýnacagý icin minimum degerine delete atýlýr ve diger degerlerle karsýlastýrýlýr
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;	// En son bulunan minimum degeri tabloya yazýlýr
            }
        }
    }
    return matrix[len1][len2];	// Bulunan distance degeri son hücrede olusur ve bu deger dondurulur.
}

int offerword(char aranan[50], ht table[m], ht errtable[m], ht data, int distsize, char sentence[200]){
	int i,count=0,dist;
	int index[50];
	
	printf("\n%s is not in the dictionary - distance = %d icin aranacak \nDid you mean : ",aranan,distsize); // Sozluk Tablosunda bulunamayan deger aranacak distance degeri ile birlikte kullanýcýya söylenir
        for(i=0;i<m;i++){
			if(table[i].key != -1){
				dist=distance(aranan,strlen(aranan),table[i].value,strlen(table[i].value)); // Sozluk tablosunda bulunan her kelimenin aranan deger ile uzaklýgý bulunur
					if(dist == distsize){
						printf("%s - ",table[i].value); // Eger bulunan uzaklýk bizim aradýgýmýz 1 veya 2 degerine esit ise kullanýcýya onerilir
						index[count++] = i;	// index dizisine bu adresin degeri yazýlýr 
						}
					}
				}
		if(count==0)
			return 0;	// Eger aradýgýmýz uzaklýkta bir kelime yok ise count artmayacaktýr ve bu durumda 0 degeri dondurulecektir
			
		printf("?");
		
		int flag=0;
		char temp[50];
		
		while(flag==0){
			printf("\nChoose: ");	// Kullanýcýdan oneri olarak girebilecegi kelimelerden birini secmesi beklenir
			scanf("%s",temp);		// Kullanýcýnýn yazdýgý oneri
		
		for(i=0;i<count;i++){	// Kullanýcýnýn yazdýgý oneri, distance tarafýndan bulunan onerilenlerle karsýlastýrýlýr eger esit ise dongu sonlandýrýlýr fakat hatalý bir oneride bulunur ise tekrardan secmesi istenir
			if( strcmp(table[index[i]].value,temp)==0 ){
				flag=1;
				break;
			}	
		}
		if(flag==0)
			printf("Hatali kelime sectiniz lutfen tekrar deneyin\n");
		}
		
		strcpy(data.oneri,temp);	// Dogru oneri secilir ise bu oneri error table a structure nesnesinin onerisi olarak eklenir
		InsertToHash(data,errtable);
		strcat(sentence,data.oneri);	// En son gosterilecek dogru cumleye bu onerilen kelime eklenir
		strcat(sentence," ");
		
		return 1;		
}

void Menu_Yazdir(){			// Menu Yazdýran fonksiyon
	printf("\n0 - EXIT\n");
	printf("1 - Kelime/Cumle Girisi\n");
	printf("2 - Dictionary_HashTable Goruntule\n");
	printf("3 - Error_HashTable Goruntule\n");	
}

int main(){
	int i;				// Dongu degiskeni
	ht table[m];		// Sozluk Hash Table
	ht errtable[m];		// Error Hash Table
	char satir[200];	// Butun satýrý okuyacak char dizisi
	char *aranan;		// Aracak olan kelime
	int errorflag;		// Kelimenin sozlukte olup olmadýgýný tutacak olan degisken
	int distselect;		// Offerword fonksiyonundan 0 degeri donerse yani istenilen distance icin kelime onerilemezse bu durumu tutacak olan degisken
	int secim;			// Menu secimi icin kullanýlacak degisken
	char sentence[200];	// En son yazdýrýlacak dogru cumleyi tutan char dizisi
	
	for(i=0;i<m;i++){
            errtable[i].key=-1;	// Olusturulan Error Hash Table'ýn butun key degerlerine -1 verilir
            }
            
	readfile(table);	// dictionary file okunur ve tabloya eklenir
	
	Menu_Yazdir();
	printf("\n***Islem Yapmak Istediginiz Fonksiyonu Seciniz : ");
	scanf("%d", &secim);
	
	do{
		switch(secim){
			case 1:
				sentence[0]='\0';	// Her yeni cumle girisinde dogru cumlenin sýfýrlanmasý gerekli
				printf("\nCumle giriniz: ");
				fflush(stdin);	// Buffer da kalan degerlerin temizlenmesi ve gets fonksiyonunun duzgun calýsmasý icin gereken fonksiyon
				gets(satir);
				aranan = strtok(satir," ");	// Butun satýr okunur ve strtok fonksiyonu ile bosluklarla bölünür
			    int dist;
    
				while(aranan != NULL){	
			    	ht data;
			        data.key = FindKey(aranan,table);
			        strcpy(data.value,aranan);
			        errorflag = SearchToHash(data,table); // Aranacak olan kelimenin SearchToHash fonksiyonundan dondurdugu deger errorflag degiskenine atanýr
			        if(errorflag == 0){	// 0 ise sozluk tablosunda yoktur
			        		if(SearchToHash(data,errtable) == 0){	// Bu sefer errortable da aranýr burada da yok ise
								distselect = offerword(aranan,table,errtable,data,1,sentence);	// distance=1 icin kelimeler onerilir
								if(distselect == 0){	// Onerilecek kelime yok ise bu sefer distance=2 icin aranýr
									printf("%s kelimesine onerilecek Uygun Kelime distance=1 icin Bulunamadi",aranan);
									distselect = offerword(aranan,table,errtable,data,2,sentence);
										if(distselect == 0){	// Eger distance=2 icin de kelime onerilemediyse daha fazla distance icin aranmaz, kelime gecilerek kullanýcýya bilgi verilir
											printf("%s kelimesine onerilecek Uygun Kelime distance=2 icin Bulunamadi\n",aranan);
											printf("...Daha buyuk distance aranmayacak kelime geciliyor...\n");
										}	
								}
							}
							else{	// Error Table da aranan kelime onceden onerilip bulunduysa kullanýcýya gosterilir, adresi hesaplanarak dogru cumleye onerilen kelime eklenir
								int adrs = SearchToHash(data,errtable);
								printf("\n--- %s kelimesi duzeltilmis hali %s olarak error_table da bulundu\n",aranan,errtable[adrs].oneri);
								strcat(sentence,errtable[adrs].oneri);
								strcat(sentence," ");
							}
					}
					else{	// Kelime sozlukta var ise kullanýcýya bilgi verilir ve dogru cumleye eklenir
						printf("\n--- %s kelimesi sozlukte bulundu\n",aranan);
						strcat(sentence,aranan);
						strcat(sentence," ");
					}
			        aranan = strtok(NULL," "); // Bosluga kadar yeni kelime alýnýr.
					}
		printf("\nDuzeltilmis Cumle: %s\n\n",sentence); // Yapýlan islemler sonucu olusan dogru cümle ekrana yazdýrýlýr
		
		Menu_Yazdir();
		printf("\n***Islem Yapmak Istediginiz Fonksiyonu Seciniz : ");
		scanf("%d", &secim); // Kullanýcýya yapmak istedigi yeni islem sorulur.
	break;
		case 2:
			for(i=0;i<m;i++){	// Dictionary Tablosunun dolu olan degerleri gosterilir
				if(table[i].key!=-1)
					printf("%d - %s\n",i,table[i].value);
				}
			Menu_Yazdir();
			printf("\n***Islem Yapmak Istediginiz Fonksiyonu Seciniz : ");
			scanf("%d", &secim); // Kullanýcýya yapmak istedigi yeni islem sorulur.
	break;
		case 3:
			for(i=0;i<m;i++){	// Error Tablosunun dolu olan degerleri gosterilir
				if(errtable[i].key!=-1)
					printf("%d - %s - %s\n",i,errtable[i].value,errtable[i].oneri);
				}
			Menu_Yazdir();
			printf("\n***Islem Yapmak Istediginiz Fonksiyonu Seciniz : ");
			scanf("%d", &secim); // Kullanýcýya yapmak istedigi yeni islem sorulur.
			break;
	}
}while(secim == 1 || secim == 2 || secim == 3);
	printf("Program Sonlandi...");
}
