#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ROZMIAR_BUFORA 2000
int BuforLiczb [ROZMIAR_BUFORA];

int OdczytZPliku(char	*NazwaPliku)
{
FILE*   file=NULL;
int     liczba,i=0;
int		WynikOdczytu;

	file = fopen(NazwaPliku,"r");
	if(file!=NULL) {
		do {
			WynikOdczytu=fscanf( file, "%u\n", &liczba );
			if((WynikOdczytu>0) && (WynikOdczytu!=EOF) ) {
				BuforLiczb[i++]=liczba;

				if(i>=ROZMIAR_BUFORA) {
	
					
					break;
				}
			}
		} while(WynikOdczytu!=EOF);
		fclose(file);
		return i;
	}
	else {
		
		return -1;
	}

}


int WprowadzanieLiczb()
{
int		WynikOdczytu;
int     i,liczba;
char    BufTekst [1000]; 
	i=0;
	printf("\nInput digits, input char to finish\n");
	do{
		scanf("%s",BufTekst);
		WynikOdczytu = sscanf(BufTekst, "%d", &liczba); 
		if(WynikOdczytu>0) BuforLiczb[i++]=liczba; 
		if(i>=ROZMIAR_BUFORA) break;

	}while(WynikOdczytu>0);
    return i;
}

int WprowadzanieNumeruFunkcji()
{
int		WynikOdczytu;
int     NrFunkcji;

	printf("\nInput function No. from 0 to 2 \n");
	do{
		WynikOdczytu = scanf("%d", &NrFunkcji);
		if( (NrFunkcji<0) || (NrFunkcji>2) ) printf("wrong number\n");
		else break;
	}while(1);
	return NrFunkcji;
}


int maksimum(int aktualnaWartosc, int poprzedniMax)
{
	return aktualnaWartosc > poprzedniMax ? aktualnaWartosc : poprzedniMax;
}

int minimum(int aktualnaWartosc, int poprzedniMin)
{
	return aktualnaWartosc < poprzedniMin ? aktualnaWartosc : poprzedniMin;
}

int suma(int aktualnaWartosc, int poprzedniaSuma)
{
	return poprzedniaSuma+aktualnaWartosc;
}



int(*FunkcjeAnalizy[3])(int,int)={maksimum, minimum, suma};



int forAll_by_funpointer(int *tablica, int liczbaElementow, int (*funkcja)(int,int))
{
int WynikFunkcji=0;
int i;
	if(liczbaElementow==0) return 0;
	WynikFunkcji=BuforLiczb[0]; 
	for(i=1; i<liczbaElementow; i++) {
		WynikFunkcji = funkcja( tablica[i], WynikFunkcji);
	}
	return WynikFunkcji;
}

int forAll_by_indexintab(int *tablica, int liczbaElementow, int nrFunkcji)
{
int WynikFunkcji;
int i;
	if(liczbaElementow==0) return 0;
	WynikFunkcji=BuforLiczb[0]; 
	for(i=1; i<liczbaElementow; i++) {
		WynikFunkcji = FunkcjeAnalizy[nrFunkcji]( tablica[i], WynikFunkcji);
	}
	return WynikFunkcji;
}

int forAll_by_textname(int *tablica, int liczbaElementow, char* TypFunkcji)
{
int WynikFunkcji=0;
	if(strcmp(TypFunkcji,"maximum")==0) {
		WynikFunkcji = forAll_by_funpointer(BuforLiczb, liczbaElementow, maksimum);
		printf("maximum = %d\n",WynikFunkcji);
	}
	else {
		if(strcmp(TypFunkcji,"minimum")==0) {
			WynikFunkcji = forAll_by_funpointer(BuforLiczb, liczbaElementow, minimum);
			printf("minimum = %d\n",WynikFunkcji);
		}
		else {
			if(strcmp(TypFunkcji,"sum")==0) {
				WynikFunkcji = forAll_by_funpointer(BuforLiczb, liczbaElementow, suma);
				printf("sum = %d\n",WynikFunkcji);
			}
			else printf("Nonexistent function\n");
		}
	}
	return WynikFunkcji;
}
void main_do_zadania5()

{
int i, n, v; 
int WynikFunkcji;
char test;

	n = WprowadzanieLiczb();
	do {
		v = WprowadzanieNumeruFunkcji();
		WynikFunkcji=BuforLiczb[0];
		for(i=1; i<n; i++) {
			WynikFunkcji = FunkcjeAnalizy[v]( BuforLiczb[i], WynikFunkcji);
		}
		printf("\nResult function No.  %d:  %d\n", v,WynikFunkcji);
		printf("\ncontinueć ? (Y - yes / N - no)  ");
	   

	}while((test=='T') || (test=='t'));



	do {
		v = WprowadzanieNumeruFunkcji();
		WynikFunkcji = forAll_by_indexintab(BuforLiczb, n, v);
		printf("\nFunction result %d:  %d\n", v, WynikFunkcji);
		printf("\ncontinue ? (Y - yes / N - no)  ");
	    

	}while((test=='T') || (test=='t'));



	printf("\n\nCalling by pointer\n\n");

	WynikFunkcji = forAll_by_funpointer(BuforLiczb, n, maksimum);
	printf("maximum = %d\n",WynikFunkcji);
	
	WynikFunkcji = forAll_by_funpointer(BuforLiczb, n, minimum);
	printf("minimum  = %d\n",WynikFunkcji);

	WynikFunkcji = forAll_by_funpointer(BuforLiczb, n, suma);
	printf("sum     = %d\n",WynikFunkcji);
	
}

void main(int argc, char* argv[])
{
char	*NazwaPliku=NULL;   
char	*TypFunkcji=NULL;  	
int     liczbaElementow,WynikFunkcji;   
char    Nazwa[1000]; 
	Nazwa[0]=0;      
	liczbaElementow=0;
    if(argc>1) {
		NazwaPliku=argv[1];
		liczbaElementow = OdczytZPliku(NazwaPliku);
	}
	if(liczbaElementow<=0) { 
		liczbaElementow = WprowadzanieLiczb();
	}
	 
	if(liczbaElementow) { 
		if(argc>2) {
			TypFunkcji=argv[2]; 
		}
		else {
			printf("Input function name < maximum, minimum, sum >  ");
			scanf("%s",Nazwa);
			TypFunkcji=Nazwa;
			printf("\n");
		}
		WynikFunkcji=forAll_by_textname(BuforLiczb, liczbaElementow, TypFunkcji);
	}
		
  
}