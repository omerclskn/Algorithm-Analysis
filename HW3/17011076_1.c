#include <stdio.h>
#include <stdlib.h>

float fakt(int k){  
      int i, f=1;		// Olas�l�k hesaplamak i�in gerekli faktoriyel fonksiyonu
      
      for(i=2;i<=k;i++)
      	f = f*i;
      
      return f;      
}

float calculate(float prob, int size){
	int length = size/2;
	float matrix[length+2][length+1];
	int i,j;
	
	for(i=0;i<length+2;i++){		// Kodun bu k�sm�n�n gerekli b�t�n a��klamalar� detay ve �rnekleriyle raporda a��klanm��t�r.
		for(j=0;j<length+1;j++){
			if(i==0 && j==0)
				matrix[i][j] = 1;
			else if(j==0){
				matrix[i][j] = matrix[i-1][j] * (prob);
			}
			else if(i==0){
				matrix[i][j] = matrix[i][j-1] * (1-prob);
			}
			else{
				matrix[i][j] = (matrix[i][0]*matrix[0][j]) * ( fakt(i+j-1) / ( fakt(i-1)*fakt(j) )  );
				matrix[i][j] += matrix[i][j-1];
			}
		}
	}
	
	printf("\nMatris:\n");	// Matrisin g�sterilmesi
	for(i=0;i<length+2;i++){
		for(j=0;j<length+1;j++){
			printf("%.6f  ",matrix[i][j]);
		} 
		printf("\n");
		}
	
	return matrix[length+1][length];	// Dinamik programlama sonucu olu�an ve arad���m�z degerin son h�creden return edilmesi
}

int main(){
	float prob;	// A tak�m�n�n kazanma olas�l�g�
	int size;	// Toplam mac say�s� ( serisi )
	
	printf("A takiminin kazanma olasiligini giriniz: ");
	scanf("%f",&prob);
	
	printf("Toplam mac sayisini giriniz: ");
	scanf("%d",&size);
	
	if(size%2==0){	// Cift say� girilmesi durumunda beraberlik olabileceginden program sonlan�r.
		printf("Lutfen tek sayi giriniz");
		return 0;
	}
	
	float result = calculate(prob,size);	// Dinamik programlama sonucu elde edilen deger result degiskenine at�l�r ve ekranda gosterilir.
	printf("\nA takiminin kazanma olasiligi: %f",result);
}
