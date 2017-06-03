#include"game.h"
#include<bits/stdc++.h>
using namespace std;
int C[1000];
inline int hasEdge(int u,int v){return --C[max(u,v)]?0:1;}
void initialize(int n){for(int i=0;i<n;i++)C[i]=i;}
