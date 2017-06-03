#include<cstdio>
#include<algorithm>
using namespace std;
#define F(i,n) for(int i=0;i<n;i++)
const int mv=(int)5e2,me=(int)2e4;
struct se{int v,w,c;}E[me];
int cv,ce;
int d[mv];
void bellman_ford(){
	F(i,cv-1)
		F(j,ce){se&e=E[j];
			d[e.w]=min(d[e.w],d[e.v]+e.c);}
}
bool negative_infinity(int v){
	int t=d[v];
	bellman_ford();
	return t>d[v];
}
int main(){
	scanf("%i%i",&cv,&ce);
	F(i,ce){se&e=E[i];
		scanf("%i%i%i",&e.v,&e.w,&e.c);
		e.v--,e.w--;
	}
	fill(d,d+cv,(int)1e9);
	d[0]=0;
	bellman_ford();
	if(d[cv-1]==(int)1e9||negative_infinity(cv-1))
		puts("QAQ");
	else
		printf("%i\n",d[cv-1]);
	return 0;
}
/*
這個code有錯，測資在這:
10 5
9 7 -501
2 5 -5535
7 1 -370
4 8 249
3 10 -3626
*/
