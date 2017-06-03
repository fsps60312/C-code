#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int N;
struct Point{int x,y,ur,dl;Point(int x,int y):x(x),y(y){}};
vector<Point>P;
map<int,int>X,Y;
struct Bit
{
	int *v,sz;
	Bit(){}
	Bit(int sz):sz(sz),v(new int[sz+1])
	{for(int i=1;i<=sz;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void add(int i,int n)
	{
		while(i<=sz)
		{
			v[i]+=n;
			i+=lowbit(i);
		}
	}
	int query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=v[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BX,BY;
void buildBIT()
{
	BX=Bit(X.size()),BY=Bit(Y.size());
	for(int i=0;i<N;i++)
	{
		Point &p=P[i];
		p.x=X[p.x],p.y=Y[p.y];
		BX.add(p.x,1),BY.add(p.y,1);
	}
}
void init()
{
	P.clear(),X.clear(),Y.clear();
	for(int i=0,x,y;i<N;i++)
	{
		scanf("%d%d",&x,&y);
		P.push_back(Point(x,y));
		X[x]=Y[y]=0;
	}
	int idx=1;
	for(map<int,int>::iterator it=X.begin();it!=X.end();it++)it->second=idx++;
	idx=1;
	for(map<int,int>::iterator it=Y.begin();it!=Y.end();it++)it->second=idx++;
	buildBIT();
}
bool cmpx(Point a,Point b)
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y>b.y;
}
bool cmpy(Point a,Point b)
{
	if(a.y!=b.y)return a.y>b.y;
	return a.x<b.x;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		init();
		sort(P.begin(),P.end(),cmpy);//y¡õx¡÷ 
		for(int i=0,ynow,cnt=N;;)
		{
			ynow=P[i].y;
			while(i<P.size()&&P[i].y==ynow)
			{
				Point &p=P[i];
				BX.add(p.x,-1);
				cnt--;
				p.dl=BX.query(p.x-1);
				printf("DL(%d,%d):%d\n",p.x,p.y,p.dl);
				i++;
			}
			if(i==P.size())break;
		}
		int vmx=-1,it=-1;
		sort(P.begin(),P.end(),cmpx);//x¡÷y¡õ 
		for(int i=0,xnow,cnt=N,tmp,inow;;)
		{
			inow=i,xnow=P[i].x,tmp=2147483647;
			while(i<P.size()&&P[i].x==xnow)
			{
				Point &p=P[i];
				BY.add(p.y,-1);
				cnt--;
				p.ur=cnt-BY.query(p.y+1);
				getmin(tmp,p.ur+p.dl);
				i++;
			}
			if(tmp>vmx)vmx=tmp,it=inow;
			if(i==P.size())break;
		}
		printf("Stan: %d; Ollie:",vmx);
		vector<int> ans;
		for(int i=it;it<P.size()&&P[it].x==P[i].x;i++)
		{
			Point &p=P[i];
			ans.push_back(N-p.ur-p.dl);
		}
		sort(ans.begin(),ans.end());
		for(int i=0;i<ans.size();i++)printf(" %d",ans[i]);
		printf(";\n");
		printf("x=%d\n",P[it].x);
	}
	return 0;
}
