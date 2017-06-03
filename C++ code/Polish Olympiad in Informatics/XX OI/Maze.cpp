#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
struct Point
{
	int x,y;
	Point(){}
	Point(const int _x,const int _y):x(_x),y(_y){}
	Point Move(const int dx,const int dy)const{return Point(x+dx,y+dy);}
	bool operator==(const Point &p)const{return x==p.x&&y==p.y;}
};
struct ManyPoints
{
	Point UL,DR;
	int D1,D2;
	deque<Point>ps;
	ManyPoints(const Point &p,const int _d1,const int _d2):UL(p.Move(-1,-1)),DR(p.Move(1,1)),D1(((_d1+2)%4+4)%4),D2((_d2%4+4)%4){ps.push_back(p);}
//	ManyPoints(const int _d1,const int _d2):UL(Point(INF,INF)),DR(Point(-INF,-INF)),D1(((_d1+2)%4+4)%4),D2((_d2%4+4)%4){}
	void Move(const int dx,const int dy)
	{
		UL=UL.Move(dx,dy),DR=DR.Move(dx,dy);
		for(int i=0;i<(int)ps.size();i++)ps[i]=ps[i].Move(dx,dy);
	}
	Point Reflection(const Point &p,const int d)const
	{
		switch(d)
		{
			case 0:return Point(p.x,UL.y);
			case 1:return Point(DR.x,p.y);
			case 2:return Point(p.x,DR.y);
			case 3:return Point(UL.x,p.y);
			default:assert(0);return Point(-1,-1);
		}
	}
	Point Entry()const{return Reflection(ps.front(),D1);}
	Point Exit()const{return Reflection(ps.back(),D2);}
	int SpanX()const{return abs(Entry().x-Exit().x);}
	int SpanY()const{return abs(Entry().y-Exit().y);}
};
ManyPoints* Merge(ManyPoints *a,ManyPoints *b)
{
//	swap(a,b);
//	printf("%d %d\n",a->D2,b->D1);
	assert(abs(a->D2-b->D1)==2);
	const Point pa=a->Exit(),pb=b->Entry();
	if(a->ps.size()<b->ps.size())
	{
		a->Move(pb.x-pa.x,pb.y-pa.y);
		assert(a->Exit()==b->Entry());
		getmin(b->UL.x,a->UL.x),getmin(b->UL.y,a->UL.y);
		getmax(b->DR.x,a->DR.x),getmax(b->DR.y,a->DR.y);
		for(int i=(int)a->ps.size()-1;i>=0;i--)b->ps.push_front(a->ps[i]);
		b->D1=a->D1;
		delete a;
		return b;
	}
	else
	{
		b->Move(pa.x-pb.x,pa.y-pb.y);
		assert(a->Exit()==b->Entry());
		getmin(a->UL.x,b->UL.x),getmin(a->UL.y,b->UL.y);
		getmax(a->DR.x,b->DR.x),getmax(a->DR.y,b->DR.y);
		for(int i=0;i<(int)b->ps.size();i++)a->ps.push_back(b->ps[i]);
		a->D2=b->D2;
		delete b;
		return a;
	}
}
int N,D[100001];
struct QdTree
{
	int begin,end;
	QdTree *chs[3];
	QdTree(const int _begin,const int _end):begin(_begin),end(_end)
	{
		if(end-begin==1)return;
		vector<int>s;
		s.push_back(begin);
		s.push_back(begin+1);
		for(int i=begin+2;;i++)
		{
			assert(i<end);
			if(abs(D[i]-D[begin+1])==1&&abs(D[i]-D[end])==1){s.push_back(i);break;}
		}
		s.push_back(end);
		assert((int)s.size()==4);
		for(int i=0;i<3;i++)chs[i]=new QdTree(s[i],s[i+1]);
	}
	ManyPoints *Build()
	{
//		printf("(%d,%d)(%d,%d)\n",begin,end,D[begin],D[end]);
		if(end-begin==1)return new ManyPoints(Point(0,0),D[begin],D[end]);
		ManyPoints *s[3];
		for(int i=0;i<3;i++)
		{
			s[i]=chs[i]->Build();
			delete chs[i];
		}
		ManyPoints *ans=s[0];
		ans=Merge(ans,s[1]);
		ans=Merge(ans,s[2]);
		return ans;
	}
};
char S[100001];
void Solve()
{
	D[0]=0;
	for(int i=0;i<N;i++)
	{
			 if(S[i]=='P')D[i+1]=D[i]+1;
		else if(S[i]=='L')D[i+1]=D[i]-1;
		else assert(0);
	}
	bool flipped=false;
	if(D[N]==-4)
	{
		for(int i=0;i<N;i++)S[i]=(S[i]=='P'?'L':'P');
		for(int i=0;i<=N;i++)D[i]*=-1;
		flipped=true;
	}
	else//if(D[N]!=4)
	{
		puts("NIE");
		return;
	}
	QdTree **trees=new QdTree*[4];
	int pre=0,cur=0;
	for(int d=1;d<4;d++)
	{
		while(D[cur]!=d)cur++;
		assert(cur<N);
		trees[d-1]=new QdTree(pre,cur);
		pre=cur;
	}
	trees[3]=new QdTree(pre,N);
	ManyPoints **s=new ManyPoints*[4];
	for(int i=0;i<4;i++)
	{
		s[i]=trees[i]->Build();
		delete trees[i];
	}
	delete[]trees;
	int xmx=-INF,ymx=-INF;
	for(int i=0;i<4;i++)getmax(xmx,s[i]->SpanX()),getmax(ymx,s[i]->SpanY());
	s[0]->Move(-xmx-s[0]->Entry().x,-ymx-s[0]->Exit().y );
	s[1]->Move( xmx-s[1]->Exit().x ,-ymx-s[1]->Entry().y);
	s[2]->Move( xmx-s[2]->Entry().x, ymx-s[2]->Exit().y );
	s[3]->Move(-xmx-s[3]->Exit().x , ymx-s[3]->Entry().y);
	vector<Point>ans;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<(int)s[i]->ps.size();j++)ans.push_back(s[i]->ps[j]);
//		printf("(%d,%d)(%d,%d)\n",s[i]->Entry().x,s[i]->Entry().y,s[i]->Exit().x,s[i]->Exit().y);
		delete s[i];
	}
	delete[]s;
	assert((int)ans.size()==N);
	for(int i=0;i<N;i++)ans[i].y*=-1;
	if(flipped)for(int i=0;i<N;i++)ans[i].x*=-1;
	else reverse(ans.begin(),ans.end());
	for(int i=0;i<N;i++)printf("%d %d\n",ans[i].x,ans[i].y);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s",S);N=-1;while(S[++N]);
	Solve();
	return 0;
}
