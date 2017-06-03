#include<cstdio>
#include<cstdlib>
#include<stack>
#define LL long long
using namespace std;
int n,T,sum;
char in[2000];
LL test;
int abs(int a){return a>=0?a:-a;}
struct nodetype
{
	int s;
	nodetype* ch[2];
};
nodetype node[2000];
int main()
{
	freopen("in.txt","r",stdin);
	//printf("%d %d %d %d\n",'A','Z','a','z');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",in);
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
						node[n].s=-node[a].s;
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
						if(node[a].s==0||node[b].s==0) node[n].s=0;
						else if(abs(node[a].s)!=abs(node[b].s)) node[n].s=0;
						else if(node[a].s==node[b].s) node[n].s=1;
						else node[n].s=-1;
						//printf("%d\n",node[n].s);
						node[n].ch[0]=&node[a];
						node[n].ch[1]=&node[b];
						st.push(n);
					}
					else valid=false;
				}break;
				default:
				{
					node[n].s=in[n];
					st.push(n);
				}break;
			}
		}
		if(!valid||st.size()!=1)printf("incorrect\n");
		else
		{
			printf("%s\n",in);
			for(int i=0;i<n;i++) printf(" %d",node[i].s);printf("\n");
			if(node[n-1].s==1) printf("tautology\n");
			else printf("formula\n");
		}
	}
	return 0;
}
