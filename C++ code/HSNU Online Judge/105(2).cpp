#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int T,N,A,B,C;
vector<int>ET[5000];
LL GetF(const LL u){return A*u*u+B*u+C;}
LL Gcd(const LL a,const LL b){return b==0LL?a:Gcd(b,a%b);}
int DJ[5000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Merge(int a,int b)
{
	a=Find(a),b=Find(b);
	if(a==b)return false;
	DJ[a]=b;
	return true;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&N,&A,&B,&C);
		for(int i=0;i<N;i++)ET[i].clear(),DJ[i]=i;
		int ans=N;
		for(int i=0;i<N;i++)
		{
			for(int j=i+1;j<N;j++)if(Gcd(GetF(i),GetF(j))==1LL&&Merge(i,j))ans--;
		}
		printf("%d\n",ans);
	}
	return 0;
}
