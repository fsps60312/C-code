#include<cstdio>
#include<cstdlib>
#include<stack>
using namespace std;
char S[10001];
int T,n;
struct nodetype
{
	int ch[2];
	int depth,index;
	char s;
	void set(int a)
	{
		index=a;
		ch[0]=ch[1]=-1;
		s=S[a];
	}
	void set(int a,int b,int c)
	{
		index=a;
		s=S[a];
		ch[0]=b,ch[1]=c;
	}
	bool operator<(nodetype a)
	{
		if(depth!=a.depth) return depth>a.depth;
		return index>a.index;
	}
};
nodetype node[10000],tmp[10000];
void setdepth(int a,int b)
{
	node[a].depth=b;
	if(node[a].ch[0]!=-1)
	{
		setdepth(node[a].ch[0],b+1);
		setdepth(node[a].ch[1],b+1);
	}
}
bool islower(char a){return a>='a'&&a<='z';};
void rangedepth(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangedepth(a,mid);
	rangedepth(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&node[c]<node[d])) tmp[i]=node[c++];
		else tmp[i]=node[d++];
	}
	for(int i=a;i<=b;i++) node[i]=tmp[i];
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		n=-1;
		stack<int> now;
		while(S[++n])
		{
			if(islower(S[n]))
			{
				node[n].set(n);
				now.push(n);
			}
			else
			{
				int a=now.top();now.pop();
				int b=now.top();now.pop();
				node[n].set(n,b,a);
				now.push(n);
			}
		}
		setdepth(n-1,0);
		rangedepth(0,n-1);
		for(int i=0;i<n;i++) printf("%c",node[i].s);printf("\n");
	}
	return 0;
}
