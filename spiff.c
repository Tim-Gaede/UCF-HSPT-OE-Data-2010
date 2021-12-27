#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permute(int Q[8], char W[8], int P[8][8], char D[][8], int level, int L);

int N;
int V[8];
int nf = 0;
int main(void){
	
	FILE* ifp = stdin;
	
	int C,i, kase = 1;
	while(1){
		fscanf(ifp,"%d",&N);
		if(N == 0) break;
		char dictionary[N][8];
		for(i = 0; i < N; i++){
			fscanf(ifp,"%s", dictionary[i]);
		}
		fscanf(ifp, "%d", &C);
		char words[C][8];
		for(i = 0; i < C; i++){
			fscanf(ifp,"%s", words[i]);
		} 
		
		int P[8][8];
		for(i = 0; i < 8; i++){
			P[i][0] = -1;
			V[i] = 0;
		}
		int Q[8];
		for(i = 0; i < C; i++){
			if(P[strlen(words[i])][0] == -1){
				nf = 0;
				permute(Q, words[i], P, dictionary, 0, strlen(words[i]));
				if(nf != 1){
					P[strlen(words[i])][0] = -1;
				}
			}
		}
		int j;
		printf("Message #%d:", (kase++));
		for(i = 0; i < C; i++){
			int  L = strlen(words[i]);
			printf(" ");
			for(j = 0; j < L; j++){
				printf("%c",words[i][P[L][j]]);
			}
		}
		printf("\n\n");
	}	
	return 0;
}

void permute(int Q[8], char W[8], int P[8][8], char D[N][8], int level, int L){
	if(level == L){
		int i;
		for(i = 0; i < N; i++){
			if(L == strlen(D[i])){
				int j,found = 1;
				for(j = 0; j < L; j++){
					if(D[i][j] != W[Q[j]]){
						found = 0;
						break;
					}
				}
				if(found){
					for(j = 0; j < L; j++){
						P[L][j] = Q[j];
					}
					nf++;
				}
			}
		}
	}
	else{
		int i;
		for(i = 0; i < L; i++){
			if(!V[i]){
				V[i] = 1;
				Q[level] = i;
				permute(Q,W,P,D,level+1,L);
				V[i] = 0;
			}
		}
	}
}
