#include <stdio.h>

int main(void){
	
	FILE* ifp = stdin;
	
	int n,l,i,a,b,j,kase=1;
	while(1){
		fscanf(ifp,"%d%d",&n,&l);
		if(n+l == 0) break;
		int G[n][n];
		int E[n];
		int max = 0;
		printf("Page #%d:\n",kase++);
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				G[i][j] = 0;	
			}
			E[i] = 0;
		}
		for(i = 0; i < l; i++){
			fscanf(ifp, "%d%d",&a,&b);
			G[a-1][b-1] = 1;
			G[b-1][a-1] = 1;
			E[a-1]++;
			E[b-1]++;
			if(E[a-1] > max)
				max = E[a-1];
			if(E[b-1] > max)
				max = E[b-1];
		}
		//If the number of edges connecting to any node is more than 3, its impossible
		if(max > 2){
			printf("No, I can't color it.\n\n");	
		}
		//Simple BFS, the only way its possible is if the graph is a simple cycle or
		//connected line.
		else{
			int V[n];
			for(i = 0; i < n; i++)
				V[i] = 0;
			int can = 1;
			while(1){
				int d = -1;
				for(i = 0; i < n; i++){
					if(!V[i]){
						d = i;
						break;
					}
				}
				if(d == -1)
					break;
				
				int Q[n], C[n];
				for(i = 0; i < n; i++)
					C[i] = 0;
				int s = 0, e = 0;
				Q[e++] = d;
				V[d] = 1;
				
				while(s != e){
					int v = Q[s++];
					for(i = 0; i < n; i++){
						if(G[v][i] && !V[i]){
							V[i] = 1;
							Q[e++] = i;
							
							if(C[v] == 0){ //If the node is our start, color the first edge with a red
								C[v] = 1;
								C[i] = 1;
							}
							else if(C[i] == 0){//If the node we are connecting to has no colored edges, color it with the opposite color
								C[i] = 3 - C[v];
								C[v] = 3;
							}
							else if(C[i] == C[v]){//The two nodes have same colored edges connected to them
								C[i] = 3;
								C[v] = 3;
							}
							else{//Edge cannot be either color, so it is impossible
								can = 0;
								s = e;
								break;
							}
						}
						if(G[v][i]){
							if(C[i]+C[v] == 3){
								can = 0;
								s = e;
								break;
							}
						}
					}
				}
				
				if(!can)
					break;
				
			}
			if(can)
				printf("Yes, I can color it.\n\n");
			else
				printf("No, I can't color it.\n\n");
		}
	}
	return 0;
}
