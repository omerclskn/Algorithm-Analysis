#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int n; // Matris olusturmak icin gerekli n sayýsý
	int i,j; // döngüler için kullanýlacak deðiþken
	int tmp=0; //her satýrdaki siyah sayýsýný bulabilmek için oluþturduðumuz deðiþken
	int **matris; // Matrisimiz
	
	printf("N degerini giriniz: ");
	scanf("%d",&n);
	
	int n2 = n; // Girilen n degerini kaybetmememiz için n2 deðiþkeninde bu deðeri tuttuk
	n = (2*n) + 3; // Toplam matris büyüklüðünü bu formül ile bulabiliyoruz
	int blackrow[n]; // Her satirdaki siyah sayýsýný tutan dizi 
	
	matris=(int **)malloc(n*sizeof(int*)); // Dinamik Matris Açýlýmý
 		for(i=0;i<n;i++)
  			matris[i]=(int *)malloc(n*sizeof(int));
  			
  	for(i=0;i<n;i++){ // Açýlan matrisin bütün deðerlerine 0 atýyoruz.
  		for(j=0;j<n;j++)
   			matris[i][j]=0;
	  	}
	  	// Matrisimiz 2 parçalý þekilde oluþturulacak ilk kýsým orta çizginin yukarýsý ikinci kýsým aþaðýsýný oluþturacak.
	  	
	 for(i=0;i<n/2;i++){ // Matrisin yarýsýný oluþturacaðýmýz için i deðerimiz matris buyuklugunun yarýsýna kadar gidecek.
	 	for(j=n/2-i;j<=n/2+i;j++) // Merkezden yukarý kýsmý yazdýracaðýz, n/2 orta çizgimiz oluyor, en sola n/2-i en saða ise n/2+i ile eriþebiliyoruz
	 		matris[i+1][j]=1; // ilk satýr boþ kalacaðý için i+1 deðerinden itibaren 1 yazdýrýyoruz
	 }
	 
	 for(i=0;i<n/2;i++){ // Matrisin kalan alt yarýsýný yazdýrýyoruz
	 	for(j=n/2-i;j<=n/2+i;j++) // Merkezden yukarý kýsmý yazdýracaðýz, n/2 orta çizgimiz oluyor, en sola n/2-i en saða ise n/2+i ile eriþebiliyoruz
	 		matris[2*n2+1-i][j]=1; // En alttan yukarý doðru ters yazdýracaðýmýz için (2*n2+1) ile bu noktaya eriþip i deðerimiz arttýkça yukarý merkeze yaklaþýyoruz.
	 }
	 
 	for(i=0;i<n;i++){ // Matrisi yazdýrýrken her 1 deðerini gordugumuzde tmp deðerini 1 arttýrýyoruz satýr bittiðinde bu deðeri blackrow dizimizdeki ilgili satýrla ayný deðere yazýyoruz.
  		for(j=0;j<n;j++){ // Ardýndan tmp deðerini sýfýrlayýp yeni satýrlarý da tutabilmesini saðlýyoruz.
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
 			
 		for(i=0;i<n;i++){ // Dizideki elemanlarý teker teker çekerek her satýrdaki siyah sayýsýný yazdýrýyoruz.
 			printf("%d. satir siyah nokta sayisi: %d\n",i+1,blackrow[i]);
		}
 				
 		printf("\nToplam siyah nokta sayisi: %d", (2*n2)*(n2+1)+1); // Toplam siyah sayýsýný bu formülle hesaplayabiliyoruz
	}
