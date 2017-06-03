#include<cstdio>
#include<vector>
#include<string>
using namespace std;
int V,C,DICT[500][26],CHAL[500][26];
vector<int>LE[500],RE[500];
int L[500],R[500];
bool VIS[500];
bool Expand(const int &l)
{
	if(L[l]!=-1||VIS[l])return false;
	VIS[l]=true;
	for(int r:LE[l])
	{
		if(R[r]==-1)
		{
			R[r]=l;
			L[l]=r;
			VIS[l]=false;
			return true;
		}
		else
		{
			for(int ll:RE[r])
			{
				if(Expand(ll))
				{
					R[r]=l;
					L[l]=r;
					VIS[l]=false;
					return true;
				}
			}
		}
	}
	VIS[l]=false;
	return false;
}
int Solve()
{
	for(int i=0;i<V;i++)L[i]=-1,VIS[i]=false;
	for(int i=0;i<C;i++)R[i]=-1;
	int ans=0;
	for(int l=0;l<V;l++)
	{
		if(L[l]!=-1)continue;
		for(int r:LE[l])if(R[r]==-1){R[r]=l,L[l]=r;ans++;break;}
	}
	for(bool changed=true;changed;)
	{
		changed=false;
		for(int l=0;l<V;l++)if(Expand(l))ans++,changed=true;
	}
	return ans;
}
int main()
{
	while(scanf("%d%d",&V,&C)==2)
	{
		for(int i=0;i<V;i++)
		{
			LE[i].clear();
			for(int j=0;j<26;j++)DICT[i][j]=0;
			static char tmp[31];
			scanf("%s",tmp);
			for(int j=0;tmp[j];j++)DICT[i][tmp[j]-'a']++;
		}
		for(int i=0;i<C;i++)
		{
			RE[i].clear();
			for(int j=0;j<26;j++)CHAL[i][j]=0;
			static char tmp[31];
			scanf("%s",tmp);
			for(int j=0;tmp[j];j++)CHAL[i][tmp[j]-'a']++;
		}
		for(int i=0;i<V;i++)
		{
			for(int j=0;j<C;j++)
			{
				bool ok=false;
				for(int k=0;k<26;k++)if(DICT[i][k]<CHAL[j][k]){ok=false;break;}
				if(!ok)continue;
				LE[i].push_back(j);
				RE[j].push_back(i);
			}
		}
		printf("%d\n",Solve());
	}
	return 0;
}
