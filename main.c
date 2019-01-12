#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

	int codProd;
	char denumire[50];
	char um[10];
	int cantitate;
	int pretUnitar;

}produs;

void readProcess(char* numeFis, produs *p, int *n) {

	FILE *pf = fopen(numeFis, "r");

	if (pf == NULL) {
		printf("Couldn't open File");
		exit(1);
	}

	*n = 0;
	

	while (1) {
		if (fscanf(pf, "%s", p[*n].denumire) != 1) {
			break;
		}

		p[*n].denumire[strlen(p[*n].denumire)] = '\0';


		int x, iter = 0;
		char ch;
		

		
		
			do {
				fseek(pf, 3, SEEK_CUR);
				fscanf(pf, "%d%c", &x, &ch);

				switch (iter)
				{
				case 0:
					p[*n].codProd = x;
					iter++;
					fseek(pf, 3, SEEK_CUR);
					fscanf(pf, "%s", p[*n].um);
					p[*n].um[strlen(p[*n].um)] = '\0';
					break;
				case 1:
					p[*n].cantitate = x;
					iter++;
					break;
				case 2:
					p[*n].pretUnitar = x;
					iter++;
					break;
				default:
					break;
				}
								
			} while (ch != '.');
			
		(*n)++;
		iter = 0;
	}
	
	fclose(pf);
}

void writeFile(char* numeFis, produs* p, int n) {
	FILE *pf = fopen(numeFis, "w");
	// 0 9 7 5 8 5 4 
	// 0 1 2 3 4 5 6
	
	int ord[11];
	int aux;

	for (int i = 0; i < n; i++) {
		ord[i] = i;
	}

	for (int i = 0; i < n/2; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (p[ord[j]].codProd > p[ord[j + 1]].codProd) {
				aux = ord[j];
				ord[j] = ord[j + 1];
				ord[j + 1] = aux;				
			}
		}
	}

	for (int i = 0; i < n; i++) {
		fprintf(pf, "%s          %d           %s           %d              %d\n", p[ord[i]].denumire, p[ord[i]].codProd,
			p[ord[i]].um, p[ord[i]].cantitate, p[ord[i]].pretUnitar);
	}
	fflush(pf);
	fclose(pf);
	for (int i = 0; i < n; i++) {
		printf("%s          %d           %s           %d              %d\n", p[ord[i]].denumire, p[ord[i]].codProd,
			p[ord[i]].um, p[ord[i]].cantitate, p[ord[i]].pretUnitar);
	}

}

int main(int argc, char *argv[]) {

	produs p[100];
	int n;

	readProcess("produse.txt", p, &n);

	writeFile("PSortat.txt", p, n);

	system("pause");

	return 0;
}