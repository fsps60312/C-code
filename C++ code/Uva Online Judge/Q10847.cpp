#include<cstdio>
#include<cstdlib>
#include<stack>
#define LL long long
using namespace std;
int n,T,sum;
char in[2000];
LL test;
struct nodetype
{
	int s;
	nodetype* ch[2];
	int getvalue()
	{
		if(s>=0) return ((1LL<<s)&test)!=0;
		if(s==-1) return ch[0]->getvalue()^1;
		return ch[0]->getvalue()==ch[1]->getvalue();
	}
};
nodetype node[2000];
int vis[1230];
int main()
{
	freopen("in.txt","r",stdin);
	//printf("%d %d %d %d\n",'A','Z','a','z');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",in);
		for(int i='A';i<=(int)'Z';i++) vis[i]=-1;
		for(int i='a';i<=(int)'z';i++) vis[i]=-1;
		//printf("\nvis:%d %d %d\n",vis['a'],vis['z'],vis['Z']);
		n=-1,sum=0;
		stack<int> st;
		bool valid=true;
		while(in[++n])
		{
			switch(in[n])
			{
				case'-':
				{
					if(st.size())
					{
						int a=st.top();st.pop();
						node[n].s=-1;
						node[n].ch[0]=&node[a];
						st.push(n);
					}
					else valid=false;
				}break;
				case'=':
				{
					if(st.size()>=2)
					{
						int a=st.top();st.pop();int b=st.top();st.pop();
						node[n].s=-2;
						node[n].ch[0]=&node[a];
						node[n].ch[1]=&node[b];
						st.push(n);
					}
					else valid=false;
				}break;
				default:
				{
					int c=in[n];
					if(vis[c]==-1)
					{
						vis[c]=sum++;//printf("%d ",vis[c]);
					}
					node[n].s=vis[c];
					st.push(n);
				}break;
			}
		}
		if(!valid||st.size()!=1)printf("incorrect\n");
		else
		{
			bool tautology=true;
			//printf("%d\n",sum);
			for(test=0;test<(1LL<<(sum+1));test++)
			{
				if(!node[n-1].getvalue())
				{
					tautology=false;
					break;
				}
			}
			if(tautology)printf("tautology\n");
			else printf("formula\n");
		}
	}
	return 0;
}
