#include<bits/stdc++.h>
using namespace std;
//AB->BA
//+A.freq*B.len
//-B.freq*A.len
//B.freq*A.len>A.freq*B.len
//
int N,LOC;
struct Song
{
	int idx,len;
	double freq;
	bool operator<(const Song &s)const{return freq*s.len>s.freq*len;}
}SONG[1<<16];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			Song &s=SONG[i];
			scanf("%d%d%lf",&s.idx,&s.len,&s.freq);
		}
		sort(SONG,SONG+N);
//		for(int i=0;i<N;i++)printf(" %d",SONG[i].idx);puts("");
		scanf("%d",&LOC);
		printf("%d\n",SONG[--LOC].idx);
	}
	return 0;
}
/*
5
1      10     45.5
2      5      20 
30     20     10 
400    50     35 
15     17     89.9
3
*/
