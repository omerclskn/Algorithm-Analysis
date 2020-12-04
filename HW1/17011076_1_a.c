#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){
	int n; // Dizi eleman sayýsý
	int i,j; // Döngüler için gerekli deðiþken
	int tmp1,tmp2; // Aradýðýmýz elemanlarýn indisini tutan deðiþkenler
	
	clock_t start,end; // Programýn Çalýþma süresinin hesabý için oluþturulan deðiþkenler
	
	printf("Dizi eleman sayisini giriniz: ");
	scanf("%d",&n);
	
	int dizi[n];
	
	for(i=0;i<n;i++){
	printf(" %d. elemanin degerini giriniz: ",i);
	scanf("%d",&dizi[i]);	
	}
	
	int fark = 9999; // Programýn çalýþabilmesi ve ilk farký bulabilmesi için fark deðiþkenine büyük bir deðer atýyoruz.
	
	start = clock(); // Sayacýn baþlatýlmasý.
	
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){ 
			if(fark > abs(dizi[i]-dizi[j])){ // Eðer fark deðerimiz kontrol ettiðimiz elemanlarýn farkýndan büyükse bu elemanlarýn yerini tutuyoruz ve fark deðerimizi güncelliyoruz.
				tmp1 = i;
				tmp2 = j;
				fark = abs(dizi[i]-dizi[j]);
			}
		}
	}
	
	end = clock(); // Sayacýn Bitiþi.
	
		printf("\n%d ve %d indexindeki elemanlar arasindaki minimum fark: %d",tmp1,tmp2,fark);
		printf("\nRunning Time: %f ms",(double)(end-start)/CLOCKS_PER_SEC);
}
