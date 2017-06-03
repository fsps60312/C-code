#include<cstdio>
#include<map>
#include<string>
#include<vector>
using namespace std;
map<string,int>IDX;
char LINE[21];
vector<int>SZ;
vector<int>DJ;
int getIDX(char *name)
{
	if(IDX.find(name)==IDX.end())
	{
		int sz=IDX.size();
		IDX[name]=sz;
		SZ.push_back(1);
		DJ.push_back(sz);
	}
	return IDX[name];
}
int findDJ(int a)
{
	if(DJ[a]==a)return a;
	return DJ[a]=findDJ(DJ[a]);
}
int getsize(int &f1,int &f2)
{
	if(f1!=f2)
	{
		SZ[f1]+=SZ[f2];
		DJ[f2]=f1;
	}
	return SZ[f1];
}
int T,F;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		IDX.clear(),SZ.clear(),DJ.clear();
		scanf("%d",&F);
		while(F--)
		{
			scanf("%s",LINE);
			int f1=findDJ(getIDX(LINE));
			scanf("%s",LINE);
			int f2=findDJ(getIDX(LINE));
			printf("%d\n",getsize(f1,f2));
		}
	}
	return 0;
}
