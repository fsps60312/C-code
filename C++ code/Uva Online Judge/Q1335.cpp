#include<cstdio>
int N,R[100000];
void getmax(int &a,int b){if(b>a)a=b;}
int min(int a,int b){return a<b?a:b;}
bool fitans(int S)
{
	int nl=R[0],nr=0,pl,pr;
	for(int i=1;i<N;i++)
	{
		pr=nr,pl=nl;
		if(i&1)
		{
			nl=min(R[0]-pl,R[i]);
			nr=R[i]-nl;
		}
		else//take right
		{
			nr=min(S-R[0]-pr,R[i]);
			nl=R[i]-nr;
		}
	}
	return nl==0;
}
int solve(int MAX)
{
	if(N==1)return R[0];
	if(!(N&1))return MAX;
	int l=MAX,r=0;
	for(int i=0;i<N;i++)getmax(r,R[i]);
	r*=3;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(fitans(mid))r=mid;
		else l=mid+1;
	}
	return l;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		int MAX=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&R[i]);
			if(i>0)getmax(MAX,R[i-1]+R[i]);
		}
		getmax(MAX,R[N-1]+R[0]);
		printf("%d\n",solve(MAX));
	}
	return 0;
}
