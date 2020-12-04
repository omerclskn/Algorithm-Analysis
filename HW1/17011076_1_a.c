#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){
	int n; // Dizi eleman say�s�
	int i,j; // D�ng�ler i�in gerekli de�i�ken
	int tmp1,tmp2; // Arad���m�z elemanlar�n indisini tutan de�i�kenler
	
	clock_t start,end; // Program�n �al��ma s�resinin hesab� i�in olu�turulan de�i�kenler
	
	printf("Dizi eleman sayisini giriniz: ");
	scanf("%d",&n);
	
	int dizi[n];
	
	for(i=0;i<n;i++){
	printf(" %d. elemanin degerini giriniz: ",i);
	scanf("%d",&dizi[i]);	
	}
	
	int fark = 9999; // Program�n �al��abilmesi ve ilk fark� bulabilmesi i�in fark de�i�kenine b�y�k bir de�er at�yoruz.
	
	start = clock(); // Sayac�n ba�lat�lmas�.
	
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){ 
			if(fark > abs(dizi[i]-dizi[j])){ // E�er fark de�erimiz kontrol etti�imiz elemanlar�n fark�ndan b�y�kse bu elemanlar�n yerini tutuyoruz ve fark de�erimizi g�ncelliyoruz.
				tmp1 = i;
				tmp2 = j;
				fark = abs(dizi[i]-dizi[j]);
			}
		}
	}
	
	end = clock(); // Sayac�n Biti�i.
	
		printf("\n%d ve %d indexindeki elemanlar arasindaki minimum fark: %d",tmp1,tmp2,fark);
		printf("\nRunning Time: %f ms",(double)(end-start)/CLOCKS_PER_SEC);
}
