#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int *dizi,int first,int last){
    int i,j;
    int pivot; // Pivot eleman� tutacak saya� de�i�keni
    int tmp; // Yer de�i�tirme i�lemi i�in kullan�lacak de�i�ken
    pivot = first; // Pivota ilk eleman atiyoruz
   
    // E�er son eleman ilk elemandan b�y�kse, son eleman ilk elemandan b�y�k oldu�u s�rece ba�tan ve sondan pivottan b�y�k olan ve pivottan k���k olan bir eleman se�ip yer de�i�tiriyoruz
    if(last>first){
        pivot=first;
        i=first;
        j=last;
        while (i<j){
            while (dizi[i]<=dizi[pivot] && i<last && j>i){ // Ba�tan pivottan b�y�k olan bir eleman buluyoruz
                i++;
            }
            while (dizi[j]>=dizi[pivot] && j>=first && j>=i){ // Sondan pivottan k���k olan bir eleman buluyoruz
                j--;
            }
            if (j>i){ // Swap i�lemi yap�l�r
                tmp=dizi[i];
                dizi[i]=dizi[j];
                dizi[j]=tmp;
            }
        }
        // Yeniden pivot se�iyoruz ve b�l�nen ba�l� listenin di�er par�alar�n� tekrar quick sort fonksiyonuna g�nderiyoruz
        tmp=dizi[j];
        dizi[j]=dizi[pivot];
        dizi[pivot]=tmp;
        quickSort(dizi,first,j-1);
        quickSort(dizi,j+1,last);
    }
}

int main(){
	int i,j; // D�ng�ler i�in gerekli de�i�ken
	int tmp1,tmp2; // Arad���m�z elemanlar�n indisini tutan de�i�kenler
	clock_t start,end;  // Program�n �al��ma s�resinin hesab� i�in olu�turulan de�i�kenler
	
	int *dizi,n; // Dizimiz ve boyutunu tutacak n de�eri.
    printf("Dizinin boyutunu giriniz: "); 
	scanf("%d",&n);
	
    dizi=(int *)malloc(n*sizeof(int));
    
    for(i=0;i<n;i++){
        printf("Dizinin %d. elemani :",i);
		scanf("%d",&dizi[i]);
    }
    
	printf("\nDizinin siralanmamis durumu: ");
    for(i=0;i<n;i++){
        printf("%d ",dizi[i]);
    }
    // Diziyi s�ralay�nca indislerin yeri de�i�ece�i i�in dizinin s�ralanmam�� orjinal halini farkl� bir dizi a��p ona at�yoruz.
    int orjdizi[n];
	for(i=0;i<n;i++){
		orjdizi[i]=dizi[i];
	}	
	start = clock(); // Sayac�n ba�lat�lmas�.
	quickSort(dizi,0,n-1); // Dizinin quicksort ile s�ralanmasi. Fonksiyona diziyle beraber ilk ve son eleman indisi gonderiliyor.
	
    printf("\nDizinin siralanmis durumu: ");
    for(i=0;i<n;i++){
        printf("%d ",dizi[i]);
    }
	
	int fark = 9999; // Program�n �al��abilmesi ve ilk fark� bulabilmesi i�in fark de�i�kenine b�y�k bir de�er at�yoruz.
	
	for(i=0;i<n-1;i++){
		if(fark > dizi[i+1] - dizi[i]){ // E�er fark de�erimiz kontrol etti�imiz elemanlar�n fark�ndan b�y�kse bu elemanlar�n yerini tutuyoruz ve fark de�erimizi g�ncelliyoruz.
			tmp1 = i;
			tmp2 = i+1;
			fark = dizi[i+1]-dizi[i];
		}
	}
	// S�ralad���m�z dizide elemanlar�n yerleri de�i�ti�i i�in de�i�meden �nceki yerlerini bulup indisleri tutan tmp de�erlerimizi g�ncelliyoruz.
	for(i=0;i<n;i++){
		if(dizi[tmp1]==orjdizi[i]){
			tmp1=i;
			break;
			}
		}
		for(i=0;i<n;i++){
			if(dizi[tmp2]==orjdizi[i]){
				tmp2=i;
				break;
			}
		}
	
	end = clock(); // Sayac�n Biti�i.
	
		printf("\n\n%d ve %d indexindeki elemanlar arasindaki minimum fark: %d",tmp1,tmp2,fark);
		printf("\nRunning Time: %f ms",(double)(end-start)/CLOCKS_PER_SEC);
}
