#include "lib1896.h"
int C[1500];
int hasEdge(int	u,int v){return ++C[u>v?u:v]==(u>v?u:v);}
void initialize(int n){for(int i=0;i<n;i++)C[i]=0;}
