#include<bits/stdc++.h>
using namespace std;
int N,S[250000];
struct Pair
{
	int v,cnt;
};
vector<Pair>P;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N*N;i++)scanf("%d",&S[i]);
		sort(S,S+N*N,greater<int>());
		P.clear();
		for(int i=0,j=0,k;i<N;i++)
		{
			Pair p;p.v=S[j],p.cnt=0;
			for(k=j;S[k]==S[j];k++)p.cnt++;
			j=k;
			P.push_back(p);
		}
		vector<int>ans;
		for(int cnt=0,p=0;cnt<N;)
		{
			int now=0;
			vector<int>tmp;
			for(int i=0;i<p;i++)
			{
				if(P[i].v%P[p].v==0)now+=P[i].cnt,tmp.push_back(P[i].v);
			}
			int v=P[p].cnt-now*2;
			for(int i=0;i<tmp.size();i++)
			{
				for(int j=0;j<tmp.size();j++)
				{
					if(gcd(tmp[i],tmp[j])==P[p].v)v--;
				}
			}
			int a=sqrt(v)+0.5;
			assert(a*a==v);
			for(int i=0;i<a;i++)ans.push_back(P[p].v);
//			printf("(%d,%d)\n",P[p].v,a);
			cnt+=a;
			p++;
		}
		printf("%d",ans[0]);
		for(int i=1;i<N;i++)printf(" %d",ans[i]);puts("");
	}
	return 0;
}
