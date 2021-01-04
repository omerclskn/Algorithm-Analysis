#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void printMatrix(int **matrix, char *colors[8], int n, int i, int secim);

void shift_right(int **matrix, int n, int row){
	int i;
	int temp = matrix[row][n-1];
    for(i=n-1;i>0;i--){		// satir sa�a kayd�r�l�r
        matrix[row][i]=matrix[row][i-1];
    }
    matrix[row][0]=temp;
}

bool col_control(int **matrix, int row, int col){
	int i,j;
	
	for(i=0;i<row;i++){	// Matrisin belirtilen sat�r�n�n �st�ndeki b�t�n s�tunlar�n ayn� olup olmad���n�n kontrol� 
			if(matrix[row][col]==matrix[i][col])
				return true;
	}
	return false;
}

int total_shift_calculator(int n){
	int i, sum=0;		// Toplam olabilecek maksimum shift say�s� hesaplan�r
	for(i=1;i<n;i++)
		sum += pow(n,i);
	return sum;
}

void solveMatrix(int **matrix, char *colors[8], int n, int row, int total_shift, int secim){
	int col = 0;
	int shift_count = 0;
	bool flag = true;
	
	if(total_shift >= total_shift_calculator(n)){	// Maks shift say�s� ge�ilirse program sonlan�r
		printf("\n--------Sonuc Yok-----------");
		exit(0);
	}
	
	while( col<n && flag){	// s�tun ve satir icin olabilecek maksimum shift say�s� kontrol�
		if( col_control(matrix,row,col)){
			if(shift_count < n){	// E�er shift say�s� n de�erini ge�erse farkl� sat�r denenecek
				shift_count++;
				col = 0;
				shift_right(matrix,n,row);
			}
			else flag = false;
		}
		else col++;	// E�le�me olmad�ysa s�tunda ilerlenecek.
	}
	total_shift += shift_count;	// T�m sat�rlar i�in toplam shift say�s� tutuldu
	if(!flag){
		if(row != 1){	// �lk sat�rda de�il ise ve shift say�s� as�ld�ysa bir �stteki sat�r shift edilerek tekrar kontrol edilir.
			shift_right(matrix,n,row-1);
			return solveMatrix(matrix,colors,n,row-1,total_shift,secim);	
		}
		else{	// �lk sat�ra kadar gelindiyse sonuc yoktur
			printf("\n--------Sonuc Yok-----------");
			exit(0);	
		}
	}
	else{
		if(row != n-1){	// Son sat�rda de�il isek tamamlanan sat�r�n alt�na ge�ilir ve secim 1 ise tamamlanan sat�r ekrana bast�r�l�r.
			if(secim==1) printMatrix(matrix,colors,n,row+1,secim);
			return solveMatrix(matrix,colors,n,row+1,total_shift,secim);
		}
		else return;
	}
}

void printMatrix(int **matrix, char *colors[8], int n, int i, int secim){	
	int row,col;		// Matris ekrana yaz�l�r, eger secim 1 ise tamamlanan sat�r�n bilgisi de g�sterilir.
	if(secim==1 && i != 0){
		printf("\n%d. Satir Tamamlandi:\n",i);
	}
	for (row = 0; row < n; row++) {
		for (col = 0; col < n; col++)
			printf("%s ", colors[matrix[row][col]]);
		printf("\n");
	}
} 
  
void get_Matrix(int **matrix, char *colors[8], int n){
	
	int i,j,k,z;
	char get_color[10];
	char selected_colors[n][10];
	int flag = 0;
	char temp[10];
	int flag2 = 0;
	
	for(i=0;i<n;i++){	// Kullan�c�dan girilen rengin renk dizisinde olup olmamas�na g�re al�m�
		printf("Sectiginiz %d. Rengi Giriniz: ",i+1);
		scanf("%s",temp);
		flag2 = 0;
		for(j=0;j<8;j++){
			if(strcmp(temp,colors[j])==0){
				flag2 = 1;
			}
		}
		
		if(flag2==1){
			strcpy(selected_colors[i],temp);
			}
		else{
			printf("Lutfen dogru renk giriniz\n");
			i--;
		}	
	}
	
	printf("\n---Renk Matrisi---:\n");
	for(i=0;i<n;i++){	// // Kullan�c�dan girilen rengin se�ilen renk dizisinde olup olmamas�na g�re al�m�
		for(j=0;j<n;j++){
			printf("Matris %d. Satir %d. Sutun Rengi Giriniz: ",i+1,j+1);
			scanf("%s",get_color);
			flag = 0;				
			for(z=0;z<n;z++){
				if(strcmp(get_color,selected_colors[z])==0){
					flag = 1;
				}
			}

			if(flag == 1){
				for(k=0;k<8;k++){
					if(strcmp(get_color,colors[k])==0){
						matrix[i][j] = k;
						break;
					}
				}
			}
			else{
				printf("Lutfen Sectiginiz Renklerden Birini Giriniz...\n");
				j--;
			} 			
		}
	}
}

int main(){
	
	int n,i,secim;
	
	char *colors[8] = {"kirmizi","yesil","sari","mavi","siyah","mor","beyaz","lacivert"};
	printf("Secebileceginiz Renkler: kirmizi, yesil, sari , mavi , siyah , mor , beyaz , lacivert\n\n");
	printf("N Degerini Giriniz (3 <= N <= 8): ");	
	scanf("%d",&n);
	
	if(n<3 || n>8){
		printf("Hatali deger girdiniz, program sonlanacak...");
		return 0;
	}
	printf("Sadece Sonuc Goruntulemek icin 0, Asamali Cikti Almak icin 1 giriniz\nSecim: ");
	scanf("%d",&secim);
	
	if(secim!=0 && secim!=1){
		printf("Hatali deger girdiniz, program sonlanacak...");
		return 0;
	}
	
	int **matrix;
	matrix = (int**)malloc(sizeof(int*)*n);	
	for(i=0;i<n;i++)
		matrix[i] = (int*)malloc(sizeof(int)*n);
	
	int total_shift = 0;
	get_Matrix(matrix,colors,n);
	printf("\nOlusan Matrisiniz:\n");
	printMatrix(matrix,colors,n,0,secim);
	printf("\n");
	solveMatrix(matrix,colors,n,1,total_shift,secim);
		printf("\nSonuc: \n");
	printMatrix(matrix,colors,n,0,secim);
	
}
