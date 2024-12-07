#include <stdio.h>


int main(){
	int M1[3][3]={{-3, 4, 5},{10, 0, -1}, {21, 4, 2}}, M2[3][3]={{34, 8, -5}, {21, 44, -10}, {32, 0, 3}}, M3[3][3];


	
	for(int l=0;l<3;l++){
		for(int c=0; c<3; c++){
			M3[l][c] = M1[l][c] + M2[l][c];
		}
	}
	
	for(int l=0;l<3;l++){
		for(int c=0; c<3; c++){
			printf("%d ", M3[l][c]);
		}
		printf("\n");
	}
	return 0;
}
