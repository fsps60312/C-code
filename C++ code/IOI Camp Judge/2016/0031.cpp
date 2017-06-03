#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
char S[100001];
int N,Z[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		Z[0]=0;
		for(int i=1,mx=0;;i++)
		{
			if(!S[i]){N=i;break;}
			if(mx+Z[mx]>=i)Z[i]=min(mx+Z[mx]-i,Z[i-mx]);
			else Z[i]=0;
			while(S[i+Z[i]]==S[Z[i]])Z[i]++;
			if(i+Z[i]>=mx+Z[mx])mx=i; 
		}
//		for(int i=0;S[i];i++)printf("%d ",Z[i]);puts("");
		int len;
		for(len=1;len<N;len++)if(N%len==0)
		{
			bool found=true;
			for(int i=1;i*len<N;i++)if(Z[i*len]<len){found=false;break;}
			if(found)break;
		}
		printf("%d\n",len);
	}
	return 0;
}
