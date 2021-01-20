#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// NOT CSV DOSYASINDAK� BO� H�CRELER�N YER�NE 0 DE�ER� YAZIP O �EK�LDE OKUMA YAPTIM AMA� HOCA BU �EK�LDE YAPILAN ��Z�M�N UYGUN OLDU�UNU S�YLED�.

float average(int n, int **A, int **B, int index_a, int index_b){
	int i;
	float sum=0;		// NU ve U okuyucular�n�n ortak okuduklar� kitaba g�re ortalamalar�
	int count=0;
	for(i=0;i<n;i++){
		if(A[index_a][i]!=0  && B[index_b][i]!=0){
			sum += A[index_a][i];
			count++;
		}
	}
	sum /= count;
	return sum;
}

float averageself(int n, int **A, int index){
	int i;
	float sum=0;	// Okuyucunun kendi okudu�u kitaplara g�re ortalamas�
	for(i=0;i<n;i++)
		sum += A[index][i];
		
	return (sum/n);
}

float pearson(int **X, int **Y, int n, int index_x, int index_y) {
  	int i=0;
  	
  	float var_x = 0;
  	float var_y = 0;
  	float cov = 0;
  	float ort_x = average(n,X,Y,index_x,index_y);	// ilgili U kullan�c�s�n�n NU kullan�c�s�yla okudu�u ortak kitaplara g�re ortalamas�
  	float ort_y = average(n,Y,X,index_y,index_x);	// ilgili NU kullan�c�s�n�n U kullan�c�s�yla okudu�u ortak kitaplara g�re ortalamas�
  	
  	
    while(i<n){
    	if(Y[index_y][i]!=0 && X[index_x][i]!=0)	// �kisinin de kitab� okumas� gerekli
    		cov += ((X[index_x][i]-ort_x) * (Y[index_y][i]-ort_y));
    	i++;	
	}
    	
    for(i=0;i<n;i++){
		if(Y[index_y][i]!=0 && X[index_x][i]!=0)	// Variance hesaplamas�
  			var_x += (pow((X[index_x][i]-ort_x),2));
	  }	
	  
    for(i=0;i<n;i++){
		if(Y[index_y][i]!=0 && X[index_x][i]!=0)	// Variance hesaplamas�
  			var_y += (pow((Y[index_y][i]-ort_y),2));
	  }
	  
    float p_corr = cov / (sqrt(var_x) * sqrt(var_y));	// sim form�l�n�n sonucunun hesaplanmas�
    return p_corr; 
}
 
float offer_book(float **sim, int **X, int **Y, int index_n, int book, int k, int book_size){
	int i,j;
	float ust=0, alt=0;
	int index_x=0;
	
	for(j=0;j<k;j++){	// pred form�l�n�n pay k�sm�n�n hesaplanmas�, sim hesaplan�rken zaten en benzerlerin deger ve indexlerini sim matrisinde tutmustuk
		index_x = (int)sim[index_n][j+k];	// o y�zden degerleri direkt matristen cekebiliyoruz.
		ust +=  sim[index_n][j] * ( X[index_x][book] - averageself(book_size,X,index_x) );
	}
	
	for(j=0;j<k;j++){	// pred form�l�n�n payda k�sm�n�n hesaplanmas�
		alt += sim[index_n][j];
	}
	
	float sonuc = averageself(book_size,Y,index_n) + ust/alt;	// pred form�l�n�n sonucunun hesaplanmas�
	return sonuc;
}

void sim_kont(float sonuc, float **sim, int index, int indexofsonuc, int k){
	int i,j;
	int flag = 0;
	
	for(i=0;i<k;i++){
		if(sim[index][i] == -2 && flag == 0){	// benzerlik degerlerini ve bu degerlerin hangi okuyucuya ait oldu�u(index) degerlerinin matris bosken kars�last�rma
			sim[index][i] = sonuc;				// yapmadan direkt atanmas�
			sim[index][i+k] = indexofsonuc;
			flag = 1;
		}
	}
	
	if(flag == 0){	// ilk atamalar gerceklestiyse en benzerler aras�ndaki minimum de�er bulunur ve eger yeni benzerlik oran�m�z minimumdan b�y�k ise �st�ne yaz�l�r
		float min = sim[index][0];
		int min_index = 0;
	for(i=1;i<k;i++){
		if(min > sim[index][i]){
			min = sim[index][i];
			min_index = i;
		}
	}
	
	if(min < sonuc){
		sim[index][min_index] = sonuc;
		sim[index][min_index+k] = indexofsonuc;
		}
	}
}

void readbooks(char **books, int book_size){
	char buffer[2048];
	char *record, *line;
	int i=0, j=0;
	
	FILE *fstream = fopen("RecomendationDataSet.csv","r");	// Dosyan�n ac�lmas�
	if(fstream == NULL){
		printf("Dosya acilamadi");	
		exit(0);
	}
	line=fgets(buffer,sizeof(buffer),fstream); // �lk sat�rdan kitap isimleri al�n�r
		
		record = strtok(line,";");
		record = strtok(NULL,";");
		
		for(j=0;j<book_size;j++){
			books[j] = record;
			if(j == book_size-2)    record=strtok(NULL,"\n");
            else record = strtok(NULL,";");
	}
	fclose(fstream);
}

void readusers(int **user_u, int **user_n, int size_u, int book_size){
	char buffer[2048];
	char *record, *line;
	int i=0, j=0;
	
	FILE *fstream = fopen("RecomendationDataSet.csv","r");	// Dosyan�n ac�lmas�
	if(fstream == NULL){
		printf("Dosya acilamadi");	
		exit(0);
	}
	line=fgets(buffer,sizeof(buffer),fstream); 
	
	for(i=0;i<size_u;i++){	// csv dosyas�nda h�cre de�erleri ; ile ayr�ld���ndan strtok ile ilk �nce U okuyucular�n�n kitaplara verdi�i puanlar matrise al�n�r
		line=fgets(buffer,sizeof(buffer),fstream);
			record = strtok(line,";");	// ilk de�er okuyucu ad�n� icerdigiden atlan�r.
			record = strtok(NULL,";");
			
		for(j=0;j<book_size;j++){
			user_u[i][j] = atoi(record);
			if(j == book_size-2)    record=strtok(NULL,"\n");
            else record = strtok(NULL,";");
		}
	}
		i=0;
	while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){		// U okuyucular� okunmas� bittiginde bir sonraki sat�rdan okunacak sat�rlar bitene kadar NU okuyuclar�n�n puanlar� matrise al�n�r
		record = strtok(line,";");
		record = strtok(NULL,";");
			
		for(j=0;j<book_size;j++){
			user_n[i][j] = atoi(record);
			if(j == book_size-2)    record=strtok(NULL,"\n");
            else record = strtok(NULL,";");
		}
		i++;
	}
	fclose(fstream);
}

int main(){
	int i,j,k,n_user;
	int size_u, size_n, book_size;
	float sonuc;
	
	printf("\n USER sayisini giriniz: ");
	scanf("%d",&size_u);
	
	printf(" NEWUSER sayisini giriniz: ");
	scanf("%d",&size_n);
	
	printf(" Kitap Sayisini giriniz: ");
	scanf("%d",&book_size);
	char *books[book_size];
	
	printf("\n K Giriniz:");
	scanf("%d",&k);
	
	int **user_u;
	user_u = (int**)malloc(sizeof(int*)*size_u);	
		for(i=0;i<size_u;i++)
			user_u[i] = (int*)malloc(sizeof(int)*book_size);
			
	int **user_n;
	user_n = (int**)malloc(sizeof(int*)*size_n);	
		for(i=0;i<size_n;i++)
			user_n[i] = (int*)malloc(sizeof(int)*book_size);
	
	readusers(user_u,user_n,size_u,book_size);
	readbooks(books,book_size);
	
	printf(" Oneri Yapilacak Kullanici Sayisi NU:");
	scanf("%d",&n_user);
	
	float **sim = (float**)malloc(sizeof(float*)*size_n);	// Sim matrisi k de�erine ba�l� olarak en y�ksek benzerlik oranlar�n� ve bu oranlar�n elde edildi�i indexleri tutacak
	for(i=0;i<size_n;i++)
		sim[i] = (float*)malloc(sizeof(float)*(2*k));
	
	for(i=0;i<size_n;i++){
		for(j=0;j<k;j++){
			sim[i][j] = -2;
			sim[i][j+k] = 0;
		}
	}
	
	for(i=0;i<size_n;i++){	
		for(j=0;j<size_u;j++){
			sonuc = pearson(user_u,user_n,book_size,j,i);	// Her bir NewUser kullan�c�s�n�n U kullan�c�l�na benzerlik oranlar�n�n hesaplanmas�
			sim_kont(sonuc,sim,i,j,k);						// Ard�ndan bu degerlerin ilgili fonksiyona g�nderilerek en y�ksek de�erlilerin bulunmas�
		}
	}
	
		printf("\n NU:%d icin en benzerler:\n",n_user);
		for(j=k;j<(2*k);j++){
			printf("\t U:%.0f -> %.3f\n",sim[n_user-1][j]+1,sim[n_user-1][j-k]);	// �stenilen NU kullan�c�s�n�n k girdisine ba�l� olarak en y�ksek benzerlikli
		}																			// U kullan�c�lar�n�n listelenmesi
		
	printf("\n NU:%d icin Tahmini Begenme Degerleri: \n",n_user);
	
	float offer;			// Her bir pred de�erini tutacak de�i�ken
	int offer_index;		// Tutulan pred de�erinin hangi kitaba ait oldu�unu tutacak de�i�ken
	float offer_temp = -1;	// Bir �nceki pred de�eriyle kar��la�t�rabilmek i�in tutulan temp de�er ilk ad�mda �al��abilmesi i�in -1 de�eri verildi
	
		for(j=0;j<book_size;j++){
			if(user_n[n_user-1][j] == 0){	// �stenilen NU kullan�c�s�n�n okumad��� kitaplara g�re tahmin olu�turulacak
				offer = offer_book(sim,user_u,user_n,n_user-1,j,k,book_size);	// Tahmin de�erinin hesaplanmas�
						printf("\t %s -> %.4f\n",books[j],offer);
					if(offer > offer_temp){	// E�er �neri de�eri �nceki �neri de�erinden b�y�kse bu de�er �nerilen kitap olacak
						offer_index = j;	// �nerilecek kitab�n indexi tutulur
						offer_temp = offer; // Di�er de�erlerle kar��la�t�rabilmek i�in �neri de�eri offer_temp de�i�keninde tutulur
					}
				}
			}
		
		printf("\n NU:%d icin onerilen kitap\n\t--- %s ---\n",n_user,books[offer_index]);	// �stenilen kullan�c�ya �nerilecek kitab�n g�r�nt�lenmesi
	
	free(sim);
	return 0;
}
