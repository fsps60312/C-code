#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
void BuildFail(const char *str,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1;str[i];i++)
	{
		int &f=fail[i+1]=fail[i];
		while(f&&str[f]!=str[i])f=fail[f];
		if(str[f]==str[i])f++;
	}
}
int N,FAIL[500001],LEFT[500002],RIGHT[500002];
char S[500001];
vector<int>ET[500001];
void RemoveNode(const int _loc,int &max_len)
{
//	printf("remove %d\n",_loc);
	const int loc=_loc+1;
	getmax(max_len,RIGHT[loc]-LEFT[loc]);
	RIGHT[LEFT[loc]]=RIGHT[loc],LEFT[RIGHT[loc]]=LEFT[loc];
}
void RemoveNodes(const int u,int &max_len)
{
	RemoveNode(u,max_len);
	for(int i=0;i<(int)ET[u].size();i++)RemoveNodes(ET[u][i],max_len);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s",S);
	N=-1;while(S[++N]);
	BuildFail(S,FAIL);
	for(int i=0;i<=N;i++)ET[i].clear();
	for(int i=1;i<=N;i++)ET[FAIL[i]].push_back(i);
	vector<int>valid_prefixes;
	for(int cur=N;cur;cur=FAIL[cur])valid_prefixes.push_back(cur);
	valid_prefixes.push_back(0);
	for(int i=0;i<=N;i++)LEFT[i+1]=i,RIGHT[i]=i+1;
	int ans=N,max_len=1;
	for(int i=(int)valid_prefixes.size()-1;i>0;i--)
	{
		const int root=valid_prefixes[i],exclude=valid_prefixes[i-1];
//		printf("root=%d,max_len=%d\n",root,max_len);
		if(root>=max_len){ans=root;break;}
		for(int j=0;j<(int)ET[root].size();j++)if(ET[root][j]!=exclude)RemoveNodes(ET[root][j],max_len);
	}
	printf("%d\n",ans);
	return 0;
}
