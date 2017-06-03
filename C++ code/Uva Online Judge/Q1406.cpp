#include<cstdio>
#include<vector>
#include<algorithm>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
using namespace std;
typedef long long LL;
int N;
char LINE[2];
vector<int>S,V[16][2],A[16][2];
int getidx(int bit,int b,int add)
{
	int anb=(1<<bit)-1;
	vector<int>&v=V[bit][b];
	int l=0,r=v.size(),mid;
	while(r>l)
	{
		mid=(l+r)/2;
		if((v[mid]&anb)+(add&anb)<=anb)l=mid+1;
		else r=mid;
	}
	return l;
}
int main()
{
	while(scanf("%d",&N)==1&&N!=-1)
	{
		S.clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			S.push_back(v);
		}
		for(int i=0;i<16;i++)
		{
			vector<int>&v0=V[i][0],&v1=V[i][1],&a0=A[i][0],&a1=A[i][1];
			v0.clear(),v1.clear(),a0.clear(),a1.clear();
			for(int j=0;j<N;j++)
			{
				V[i][(S[j]&(1<<i))>>i].push_back(S[j]);
			}
			sort(v0.begin(),v0.end()),sort(v1.begin(),v1.end());
			a0.push_back(v0[0]),a1.push_back(v1[0]);
			for(int i=1;i<v0.size();i++)a0.push_back(a0[i-1]+v0[i]);
			for(int i=1;i<v1.size();i++)a1.push_back(a1[i-1]+v1[i]);
		}
		int add=0,tmp;
		LL ans=0LL;
		while(scanf("%s",&LINE)&&LINE[0]!='E')
		{
			if(LINE[0]=='C')
			{
				scanf("%d",&tmp);
				add+=tmp;
			}
			else if(LINE[0]=='Q')
			{
int prea=ans;
				scanf("%d",&tmp);
				int anb=(1<<tmp)-1;
				vector<int>&v0=V[tmp][0],&v1=V[tmp][1];
				int l=0,r=v0.size(),mid;
				while(r>l)
				{
					mid=(l+r)/2;
					if(v0[mid]+(add&anb)<=anb)l=mid+1;
					else r=mid;
				}
				ans+=v0.size()-l;
				l=0,r=v1.size(),mid;
				while(r>l)
				{
					mid=(l+r)/2;
					if(v1[mid]+(add&anb)<=anb)l=mid+1;
					else r=mid;
				}
				ans+=l;
printf("add%d\n",ans-prea);
			}
			else termin("Can't handle %s\n",LINE);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
