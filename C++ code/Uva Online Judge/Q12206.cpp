#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int x=97;
char S[40001];
int m,n,pos,rank[40001],t1[40001];
unsigned long long hash[40001],H[40001],X[40001];
bool cmp(const int& a,const int& b)
{
	if(hash[a]!=hash[b])return hash[a]<hash[b];
	return a<b;
}
/*void msort(int a,int b)
{
	//printf("%d %d\n",a,b);
	if(a>=b)return;
	int mid=(a+b)/2;
	msort(a,mid);
	msort(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&cmp(rank[c],rank[d])))t1[i]=rank[c++];
		else t1[i]=rank[d++];
	}
	for(int i=a;i<=b;i++)rank[i]=t1[i];
}*/
bool possible(int L)
{
	for(int i=0;i<n-L;i++)
	{
		rank[i]=i;
		hash[i]=H[i+L]-(i>0?H[i-1]:0)*X[L+1];
	}
	//printf("a\n");
	sort(rank,rank+n-L,cmp);
	//for(int i=0;i<n-L;i++)printf("rank:%d\t%llu\n",rank[i],hash[rank[i]]);
	//printf("b\n");
	pos=-1;int ans=0;
	for(int i=0;i<n-L;i++)
	{
		if(i==0||hash[rank[i-1]]!=hash[rank[i]])ans=0;
		if(++ans>=m){pos=max(pos,rank[i]);/*printf("pos:%d\n",rank[i]);*/}
	}
	return pos>=0;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(scanf("%d",&m)==1&&m)
	{
		scanf("%s",&S);
		n=-1;while(S[++n]);
		if(!possible(0))
		{
			printf("none\n");
			continue;
		}
		H[0]=S[0],X[0]=1;
		for(int i=1;i<n;i++)H[i]=H[i-1]*x+S[i],X[i]=X[i-1]*x;
		int r=1,l=n;
		while(r<l)
		{
			int mid=(r+l)/2;
			//printf("mid=%d\n",mid);
			if(possible(mid))r=mid+1;
			else l=mid;
		}
		possible(r-1);
		printf("%d %d\n",r,pos);
	}
	return 0;
}
