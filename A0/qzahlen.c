#include <stdio.h>
int main(void) {
	for ( int a = 0; a < 100 ; a++ ) {
		for(int b = 1 ; b < 100 ; b++) {
			for(int c = 2 ; c<100; c++) {
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
