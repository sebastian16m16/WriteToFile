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

void readProcess(char* numeFis, produs* p, int *n) {

	FILE *pf = fopen(numeFis, 'r');

	if (pf == NULL) {
		printf("Couldn't open File");
		exit(1);
	}

	*n = 0;
	produs change;

	while (1) {
		if (fscanf(pf, "%s", p[*n].denumire) != 1) {
			break;
		}

		p[*n].denumire[strlen(p[*n].denumire) - 1] = '\0';


		int x, iter = 0;
		char ch1, ch2;

		
			do {
				fscanf(pf, "%d%c%c",&x, &ch1, &ch2);
				switch (iter)
				{
				case 0:
					p[*n].codProd = x;
					iter++;
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
				
			} while (ch2 != '.');
			
			
		iter = 0;
		*n++;
	}
	for (int i = 0; i < n-1; i++) {
		if (p[i].codProd > p[i + 1].codProd) {
			change = p[i];
			p[i] = p[i + 1];
			p[i + 1] = change;
		}
	}
	fclose(pf);
}

void writeFile(char* numeFis, produs* p, int n) {
	FILE *pf = fopen(numeFis, "w");

	for (int i = 0; i < n; i++) {
		fprintf(pf, "%s          %d           %s           %d              %d\n", p[i].denumire, p[i].codProd,
			p[i].um, p[i].cantitate, p[i].pretUnitar);
	}
	fclose(pf);

}

int main() {

	produs p[100];
	int n;

	readProcess("produse.txt", p, &n);
	writeFile("produseSortate.txt", p, n);

	system("pause");

	return 0;
}