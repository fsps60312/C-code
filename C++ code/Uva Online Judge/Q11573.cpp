#include<cstdio>
#include<vector>
#include<set>
#include<queue>
using namespace std;
char LAKE[1000][1000];
int DJ[1000000],VIS[1000000],N,R,C;
int findDJ(int a){return DJ[a]==a?a:(DJ[a]=findDJ(DJ[a]));}
vector<set<int> >TO;
void Reindex()
{
	static vector<int>change;
	change.clear();
	N=0;
	for(int i=0;i<R*C;i++)
	{
		int v=findDJ(i);
		if(VIS[v]==-1)VIS[v]=N++,change.push_back(v);
	}
	for(int i=0;i<R*C;i++)DJ[i]=VIS[DJ[i]];
	for(int i=0;i<change.size();i++)VIS[change[i]]=-1;
}
void BuildTO()
{
	static int d[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
	TO.resize(N);
	for(int i=0;i<N;i++)TO[i].clear(); 
	for(int r=0,x,y,i1,i2;r<R;r++)
	{
		for(int c=0;c<C;c++)
		{
			for(int i=0;i<8;i++)
			{
				y=r+d[i][0],x=c+d[i][1];
				if(y<0||x<0||y>=R||x>=C)continue;
				i1=DJ[r*C+c],i2=DJ[y*C+x];
				if(i1!=i2)TO[i1].insert(i2),TO[i2].insert(i1);
			}
		}
	}
}
int Dis(int s,int t)
{
	static queue<pair<int,int> >q;
	static vector<int>change;
	change.clear();
	q=queue<pair<int,int> >();
	q.push(make_pair(s,0));
	for(;;)
	{
		pair<int,int>p=q.front();q.pop();
		if(VIS[p.first]==0)continue;
		VIS[p.first]=0;change.push_back(p.first);
		if(p.first==t)
		{
			for(int i=0;i<change.size();i++)VIS[change[i]]=-1;
			return p.second;
		}
		for(set<int>::iterator it=TO[p.first].begin();it!=TO[p.first].end();it++)
		{
			q.push(make_pair(*it,p.second+1));
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<1000000;i++)VIS[i]=-1;
	while(scanf("%d%d",&R,&C)==2)
	{
		for(int i=0;i<R*C;i++)DJ[i]=i;
		for(int r=0,x,y;r<R;r++)
		{
			for(int c=0;c<C;c++)
			{
				char &v=LAKE[r][c];
				do{scanf("%c",&v);}while(v>'7'||v<'0');
				if(v>='7'||v<='1')y=r-1;
				else if(v>='3'&&v<='5')y=r+1;
				else y=r;
				if(v>='1'&&v<='3')x=c+1;
				else if(v>='5'&&v<='7')x=c-1;
				else x=c;
				if(x<0||y<0||x>=C||y>=R)continue;
				DJ[findDJ(y*C+x)]=findDJ(r*C+c);
			}
		}
		puts("a");
		Reindex();
		puts("b");
		BuildTO();
		puts("c");
		static int Q;
		scanf("%d",&Q);
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)printf("%d",DJ[i*C+j]);
			puts("");
		}
		while(Q--)
		{
			static int r1,c1,r2,c2;
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			printf("%d\n",Dis(DJ[r1*C+c1],DJ[r2*C+c2]));
		}
	}
	return 0;
}
