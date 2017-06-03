#include<cstdio>
#include<cassert>
#include<algorithm>
#include<stack>
using namespace std;
bool IsDigit(const char c){return '0'<=c&&c<='9';}
struct DisjointSets
{
	int DATA[10000],COUNT[10000],SIZE[10000];
	void Clear(const int n){DATA[n]=n,COUNT[n]=SIZE[n]=1;}
	int Find(const int a){return DATA[a]==a?a:(DATA[a]=Find(DATA[a]));}
	void Merge(int a,int b,bool get_max)
	{
		assert((a=Find(a))!=(b=Find(b)));
		DATA[a]=b;
		if(get_max)COUNT[b]=max(COUNT[a],COUNT[b]);
		else COUNT[b]=min(COUNT[a]+SIZE[b],COUNT[b]+SIZE[a]);
		SIZE[b]+=SIZE[a];
	}
}DJ;
char S[1000001];
int RIGHT[1000001],LEFT[1000001];
int N;
int Dfs(const int l,const int r)
{
	if(S[l]=='(')
	{
		assert(S[r]==')'&&RIGHT[l]+1==LEFT[r]-1);
		const int a=Dfs(l+1,RIGHT[l]-1),b=Dfs(LEFT[r]+1,r-1);
		const char type=S[RIGHT[l]+1];
		assert(type=='J'||type=='U');
		DJ.Merge(a,b,type=='U');
		return a;
	}
	else
	{
		int ans=0;
		for(int i=l;;i++)
		{
			if(IsDigit(S[i]))ans=ans*10+(S[i]-'0');
			else{assert(i==r+1);break;}
		}
		while(ans>N)DJ.Clear(N++);
		return ans-1;
	}
}
int L;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		stack<int>stk;
		for(int &i=L=0;S[i];i++)switch(S[i])
		{
			case'(':stk.push(i);break;
			case')':RIGHT[stk.top()]=i,LEFT[i]=stk.top(),stk.pop();break;
			default:assert(S[i]=='J'||S[i]=='U'||IsDigit(S[i]));break;
		}
		assert(stk.empty());
		N=0;
		Dfs(0,L-1);
		for(int i=1;i<N;i++)assert(DJ.Find(i)==DJ.Find(0));
		printf("%d\n",DJ.COUNT[DJ.Find(0)]);
	}
	return 0;
}
