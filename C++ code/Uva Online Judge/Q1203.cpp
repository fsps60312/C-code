#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
char in[1000];
struct pairtype
{
	int x,y,z;
	bool operator<(pairtype a)const
	{
		if(x!=a.x) return x>a.x;
		return y>a.y;
	}
};
priority_queue<pairtype> p;
pairtype newpair(int a,int b,int d){pairtype c;c.x=a,c.y=b,c.z=d;return c;}
int main()
{
	int a,b;
	while(scanf("%s",in)==1)
	{
		if(in[0]=='#')
		{
			scanf("%d",&a);
			for(int i=0;i<a;i++)
			{
				pairtype j=p.top();p.pop();
				printf("%d\n",j.y);
				j.x+=j.z;
				p.push(j);
			}
			break;
		}
		scanf("%d%d",&a,&b);
		p.push(newpair(b,a,b));
	}
	return 0;
}
