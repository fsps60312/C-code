#include<cstdio>
#include<vector>
using namespace std;
int R,C,N,R_VIS[1001],C_VIS[1001];
vector<int> R_TO[1001],C_TO[1001],R_REC,C_REC,R_ANS,C_ANS;
void dfs(int u,int isr)
{
	if(isr)
	{
		if(R_VIS[u])return;
		R_VIS[u]=1;
		R_REC.push_back(u);
		for(int i=0;i<R_TO[u].size();i++)dfs(R_TO[u][i],0);
	}
	else
	{
		if(C_VIS[u])return;
		C_VIS[u]=1;
		C_REC.push_back(u);
		for(int i=0;i<C_TO[u].size();i++)dfs(C_TO[u][i],1);
	}
}
int min(int a,int b){return a<b?a:b;}
int TMP_msort[1001];
void msort(vector<int> &DA,int l,int r)
{
	if(l==r)return;
	int mid=(l+r)/2;
	msort(DA,l,mid);
	msort(DA,mid+1,r);
	int a=l,b=mid+1;
	for(int i=l;i<=r;i++)
	{
		if(b>r||(a<=mid&&DA[a]<DA[b]))TMP_msort[i]=DA[a++];
		else TMP_msort[i]=DA[b++];
	}
	for(int i=l;i<=r;i++)DA[i]=TMP_msort[i];
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%d%d%d",&R,&C,&N)==3&&(R||C||N))
	{
		for(int i=1;i<=R;i++)
		{
			R_TO[i].clear();
			R_VIS[i]=0;
		}
		for(int i=1;i<=C;i++)
		{
			C_TO[i].clear();
			C_VIS[i]=0;
		}
		for(int i=1;i<=N;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			R_TO[a].push_back(b);
			C_TO[b].push_back(a);
		}
		R_ANS.clear(),C_ANS.clear();
		for(int i=1;i<=R;i++)
		{
			if(!R_VIS[i])
			{
				R_REC.clear(),C_REC.clear();
				dfs(i,1);
				if(R_REC.size()>C_REC.size())
				{
					for(int j=0;j<C_REC.size();j++)C_ANS.push_back(C_REC[j]);
				}
				else
				{
					for(int j=0;j<R_REC.size();j++)R_ANS.push_back(R_REC[j]);
				}
			}
		}
		printf("%d",R_ANS.size()+C_ANS.size());
		if(R_ANS.size())msort(R_ANS,0,R_ANS.size()-1);
		if(C_ANS.size())msort(C_ANS,0,C_ANS.size()-1);
		for(int i=0;i<R_ANS.size();i++)printf(" r%d",R_ANS[i]);
		for(int i=0;i<C_ANS.size();i++)printf(" c%d",C_ANS[i]);
		printf("\n");
	}
	return 0;
}
