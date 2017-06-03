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
		if(R[r]==-1||Expand(R[r]))
		{
			R[r]=l;
			L[l]=r;
			return true;
		}
	}
	return false;
}
int Solve()
{
	for(int i=0;i<V;i++)L[i]=-1;
	for(int i=0;i<C;i++)R[i]=-1;
	int ans=0;
	for(int l=0;l<V;l++)
	{
		if(L[l]!=-1)continue;
		for(int r:LE[l])if(R[r]==-1){R[r]=l,L[l]=r;ans++;break;}
	}
	for(int l=0;l<V;l++)
	{
		if(L[l]!=-1)continue;
		for(int i=0;i<V;i++)VIS[i]=false;
		if(Expand(l))ans++,changed=true;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
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
				bool ok=true;
				for(int k=0;k<26;k++)if(DICT[i][k]<CHAL[j][k]){ok=false;break;}
				if(!ok)continue;
				LE[i].push_back(j);
				RE[j].push_back(i);
//				printf("(%d,%d)\n",i,j);
			}
		}
		printf("%d\n",Solve());
	}
	return 0;
}
