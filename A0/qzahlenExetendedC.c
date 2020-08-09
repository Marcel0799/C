#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int grenze = -1;
	
	if(argc == 2) {
		grenze = atoi(argv[1]);
	} else {
		printf("Bitte genau eine positive Zahl als Grenze eingeben");
	}
	
	for ( int a = 0; a <= grenze ; a++ ) {
		for(int b = 1 ; b <= grenze ; b++) {
			for(int c = 2 ; c <= grenze; c++) {
				if((c*c)+(b*b) == a && c != b) {
					printf("%d = (%d)² + (%d)²\n", a , b ,c );
					goto aLoop;
				}
			}
		}
		aLoop:;
	}
	
	return 0;
}
