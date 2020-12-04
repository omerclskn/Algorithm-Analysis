#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int *dizi,int first,int last){
    int i,j;
    int pivot; // Pivot elemaný tutacak sayaç deðiþkeni
    int tmp; // Yer deðiþtirme iþlemi için kullanýlacak deðiþken
    pivot = first; // Pivota ilk eleman atiyoruz
   
    // Eðer son eleman ilk elemandan büyükse, son eleman ilk elemandan büyük olduðu sürece baþtan ve sondan pivottan büyük olan ve pivottan küçük olan bir eleman seçip yer deðiþtiriyoruz
    if(last>first){
        pivot=first;
        i=first;
        j=last;
        while (i<j){
            while (dizi[i]<=dizi[pivot] && i<last && j>i){ // Baþtan pivottan büyük olan bir eleman buluyoruz
                i++;
            }
            while (dizi[j]>=dizi[pivot] && j>=first && j>=i){ // Sondan pivottan küçük olan bir eleman buluyoruz
                j--;
            }
            if (j>i){ // Swap iþlemi yapýlýr
                tmp=dizi[i];
                dizi[i]=dizi[j];
                dizi[j]=tmp;
            }
        }
        // Yeniden pivot seçiyoruz ve bölünen baðlý listenin diðer parçalarýný tekrar quick sort fonksiyonuna gönderiyoruz
        tmp=dizi[j];
        dizi[j]=dizi[pivot];
        dizi[pivot]=tmp;
        quickSort(dizi,first,j-1);
        quickSort(dizi,j+1,last);
    }
}

int main(){
	int i,j; // Döngüler için gerekli deðiþken
	int tmp1,tmp2; // Aradýðýmýz elemanlarýn indisini tutan deðiþkenler
	clock_t start,end;  // Programýn Çalýþma süresinin hesabý için oluþturulan deðiþkenler
	
	int *dizi,n; // Dizimiz ve boyutunu tutacak n deðeri.
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
    // Diziyi sýralayýnca indislerin yeri deðiþeceði için dizinin sýralanmamýþ orjinal halini farklý bir dizi açýp ona atýyoruz.
    int orjdizi[n];
	for(i=0;i<n;i++){
		orjdizi[i]=dizi[i];
	}	
	start = clock(); // Sayacýn baþlatýlmasý.
	quickSort(dizi,0,n-1); // Dizinin quicksort ile sýralanmasi. Fonksiyona diziyle beraber ilk ve son eleman indisi gonderiliyor.
	
    printf("\nDizinin siralanmis durumu: ");
    for(i=0;i<n;i++){
        printf("%d ",dizi[i]);
    }
	
	int fark = 9999; // Programýn çalýþabilmesi ve ilk farký bulabilmesi için fark deðiþkenine büyük bir deðer atýyoruz.
	
	for(i=0;i<n-1;i++){
		if(fark > dizi[i+1] - dizi[i]){ // Eðer fark deðerimiz kontrol ettiðimiz elemanlarýn farkýndan büyükse bu elemanlarýn yerini tutuyoruz ve fark deðerimizi güncelliyoruz.
			tmp1 = i;
			tmp2 = i+1;
			fark = dizi[i+1]-dizi[i];
		}
	}
	// Sýraladýðýmýz dizide elemanlarýn yerleri deðiþtiði için deðiþmeden önceki yerlerini bulup indisleri tutan tmp deðerlerimizi güncelliyoruz.
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
	
	end = clock(); // Sayacýn Bitiþi.
	
		printf("\n\n%d ve %d indexindeki elemanlar arasindaki minimum fark: %d",tmp1,tmp2,fark);
		printf("\nRunning Time: %f ms",(double)(end-start)/CLOCKS_PER_SEC);
}
