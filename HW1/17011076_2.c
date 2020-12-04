#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int n; // Matris olusturmak icin gerekli n say�s�
	int i,j; // d�ng�ler i�in kullan�lacak de�i�ken
	int tmp=0; //her sat�rdaki siyah say�s�n� bulabilmek i�in olu�turdu�umuz de�i�ken
	int **matris; // Matrisimiz
	
	printf("N degerini giriniz: ");
	scanf("%d",&n);
	
	int n2 = n; // Girilen n degerini kaybetmememiz i�in n2 de�i�keninde bu de�eri tuttuk
	n = (2*n) + 3; // Toplam matris b�y�kl���n� bu form�l ile bulabiliyoruz
	int blackrow[n]; // Her satirdaki siyah say�s�n� tutan dizi 
	
	matris=(int **)malloc(n*sizeof(int*)); // Dinamik Matris A��l�m�
 		for(i=0;i<n;i++)
  			matris[i]=(int *)malloc(n*sizeof(int));
  			
  	for(i=0;i<n;i++){ // A��lan matrisin b�t�n de�erlerine 0 at�yoruz.
  		for(j=0;j<n;j++)
   			matris[i][j]=0;
	  	}
	  	// Matrisimiz 2 par�al� �ekilde olu�turulacak ilk k�s�m orta �izginin yukar�s� ikinci k�s�m a�a��s�n� olu�turacak.
	  	
	 for(i=0;i<n/2;i++){ // Matrisin yar�s�n� olu�turaca��m�z i�in i de�erimiz matris buyuklugunun yar�s�na kadar gidecek.
	 	for(j=n/2-i;j<=n/2+i;j++) // Merkezden yukar� k�sm� yazd�raca��z, n/2 orta �izgimiz oluyor, en sola n/2-i en sa�a ise n/2+i ile eri�ebiliyoruz
	 		matris[i+1][j]=1; // ilk sat�r bo� kalaca�� i�in i+1 de�erinden itibaren 1 yazd�r�yoruz
	 }
	 
	 for(i=0;i<n/2;i++){ // Matrisin kalan alt yar�s�n� yazd�r�yoruz
	 	for(j=n/2-i;j<=n/2+i;j++) // Merkezden yukar� k�sm� yazd�raca��z, n/2 orta �izgimiz oluyor, en sola n/2-i en sa�a ise n/2+i ile eri�ebiliyoruz
	 		matris[2*n2+1-i][j]=1; // En alttan yukar� do�ru ters yazd�raca��m�z i�in (2*n2+1) ile bu noktaya eri�ip i de�erimiz artt�k�a yukar� merkeze yakla��yoruz.
	 }
	 
 	for(i=0;i<n;i++){ // Matrisi yazd�r�rken her 1 de�erini gordugumuzde tmp de�erini 1 artt�r�yoruz sat�r bitti�inde bu de�eri blackrow dizimizdeki ilgili sat�rla ayn� de�ere yaz�yoruz.
  		for(j=0;j<n;j++){ // Ard�ndan tmp de�erini s�f�rlay�p yeni sat�rlar� da tutabilmesini sa�l�yoruz.
  			printf("%d",matris[i][j]);
	  			if(matris[i][j]==1){
	  				tmp++;
					}
		  		}
		  	
		 	blackrow[i]=tmp;
			tmp=0;
  			printf("\n");
 		}
 			
 		printf("\n");
 			
 		for(i=0;i<n;i++){ // Dizideki elemanlar� teker teker �ekerek her sat�rdaki siyah say�s�n� yazd�r�yoruz.
 			printf("%d. satir siyah nokta sayisi: %d\n",i+1,blackrow[i]);
		}
 				
 		printf("\nToplam siyah nokta sayisi: %d", (2*n2)*(n2+1)+1); // Toplam siyah say�s�n� bu form�lle hesaplayabiliyoruz
	}
