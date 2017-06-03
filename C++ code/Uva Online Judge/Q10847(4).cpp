#include<cstdio>
#include<cstdlib>
#include<stack>
#define LL long long
using namespace std;
int n,T,sum;
char in[2000];
LL test;
int abs(int a){return a>=0?a:-a;}
int trans(char a){if(a<='Z')return a-'A';else return a-'a'+26;}
LL countbits(LL a)
{
	a=((a&0xaaaaaaaaaaaaaaaa)>>1)+(a&0x5555555555555555);
	a=((a&0xcccccccccccccccc)>>2)+(a&0x3333333333333333);
	a=((a&0xf0f0f0f0f0f0f0f0)>>4)+(a&0x0f0f0f0f0f0f0f0f);
	a=((a&0xff00ff00ff00ff00)>>8)+(a&0x00ff00ff00ff00ff);
	a=((a&0xffff0000ffff0000)>>16)+(a&0x0000ffff0000ffff);
	a=((a&0xffffffff00000000)>>32)+(a&0x00000000ffffffff);
	return a;
}
struct nodetype
{
	int s;
	LL infect;
	nodetype* ch[2];
	int getvalue()
	{
		if(ch[0])
		{
			if(ch[1]) return ch[0]->getvalue()*ch[1]->getvalue();
			else return -ch[0]->getvalue();
		}
		else return 1;
	}
};
nodetype node[2000];
int main()
{
	//freopen("in.txt","r",stdin);
	//printf("%d %d %d %d\n",'A','Z','a','z');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",in);
		n=-1,sum=0;
		stack<int> st;
		bool valid=true;
		while(in[++n]&&n<200)
		{
			switch(in[n])
			{
				case'-':
				{
					if(st.size()>=1)
					{
						int a=st.top();st.pop();
						node[n].s=-node[a].s;
						node[n].infect=node[a].infect;
						node[n].ch[0]=&node[a];
						node[n].ch[1]=NULL;
						st.push(n);
					}
					else valid=false;
				}break;
				case'=':
				{
					if(st.size()>=2)
					{
						int a=st.top();st.pop();int b=st.top();st.pop();
						/*if(node[a].s==0||node[b].s==0) node[n].s=0;
						else if(node[a].s==1) node[n].s=node[b].s;
						else if(node[b].s==1) node[n].s=node[a].s;
						else if(node[a].s==-1) node[n].s=-node[b].s;
						else if(node[b].s==-1) node[n].s=-node[a].s;
						else if(abs(node[a].s)!=abs(node[b].s)) node[n].s=0;
						else if(node[a].s==node[b].s) node[n].s=1;
						else node[n].s=-1;*/
						//printf("%d\n",node[n].s);
						node[n].ch[0]=&node[a];
						node[n].ch[1]=&node[b];
						node[n].infect=node[a].infect^node[b].infect;
						st.push(n);
					}
					else valid=false;
				}break;
				default:
				{
					node[n].s=in[n];
					node[n].infect=(1LL<<trans(in[n]));
					node[n].ch[0]=node[n].ch[1]=NULL;
					st.push(n);
				}break;
			}
		}
		if((n==200&&in[n])||!valid||st.size()!=1)printf("incorrect\n");
		else
		{
			//printf("%s\n",in);
			//for(int i=0;i<n;i++) printf(" %d",node[i].s);printf("\n");
			if(node[n-1].infect==0&&node[n-1].getvalue()==1) printf("tautology\n");
			else printf("formula\n");
		}
	}
	return 0;
}
