#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
template<class T>inline void getmin(T &a,const T &b){if(b<a)a=b;}
struct Point
{
	const static int D[6][2];
	int X,Y;
	Point(){}
	Point(const int _X,const int _Y):X(_X),Y(_Y){}
	int Direction(const Point &pre)const
	{
		for(int i=0;i<6;i++)if(X==pre.X+D[i][0]&&Y==pre.Y+D[i][1])return i;
		assert(0);return -1;
	}
	Point LeftTriangle(const Point &pre)const
	{
		switch(Direction(pre))
		{
			case 0:return Point(pre.X,pre.Y);
			case 1:return Point(pre.X+1,pre.Y);
			case 2:return Point(pre.X+1,pre.Y-1);
			case 3:return Point(pre.X,pre.Y-1);
			case 4:return Point(pre.X-1,pre.Y-1);
			case 5:return Point(pre.X-1,pre.Y);
			default:assert(0);return (*this);
		}
	}
	Point RigtTriangle(const Point &pre)const
	{
		switch(Direction(pre))
		{
			case 0:return Point(pre.X+1,pre.Y);
			case 1:return Point(pre.X+1,pre.Y-1);
			case 2:return Point(pre.X,pre.Y-1);
			case 3:return Point(pre.X-1,pre.Y-1);
			case 4:return Point(pre.X-1,pre.Y);
			case 5:return Point(pre.X,pre.Y);
			default:assert(0);return (*this);
		}
	}
	void Move(const int dis,Point &pre)
	{
		const int d=(Direction(pre)+dis+6)%6;
		pre=(*this);
		assert(0<=d&&d<6);
		X+=D[d][0],Y+=D[d][1];
	}
};
const int Point::D[6][2]={{1,1},{2,0},{1,-1},{-1,-1},{-2,0},{-1,1}};
bool operator<(const Point &a,const Point &b){return a.X<b.X||(a.X==b.X&&a.Y<b.Y);}
bool GetProblemType()
{
	static char s[2];scanf("%s",s);
	if(s[0]=='K')return true;
	if(s[0]=='N')return false;
	assert(0);return false;
}
vector<int>Format(const vector<int>&_s)
{
	vector<int>s=_s;
	int sum=0;
	for(int i=0;i<(int)s.size();i++)sum+=s[i];
	if(sum==-6)for(int i=0;i<(int)s.size();i++)s[i]*=-1;
	sum=0;
	for(int i=0;i<(int)s.size();i++)sum+=s[i];
	assert(sum==6);
	return s;
}
bool IsValid(const vector<int>&s)
{
//	for(int i=0;i<(int)s.size();i++)putchar('c'+s[i]);puts("");
	if(false)
	{
		for(int i=0;i<(int)s.size();i++)putchar('c'+s[i]);puts("");
		Point now=Point(1,1),pre=Point(0,0);
		for(int i=0;i<(int)s.size();i++)
		{
			const Point &p=now.RigtTriangle(pre);
			printf("(%d,%d)\n",p.X,p.Y);
			now.Move(s[i],pre);
			printf("now=(%d,%d)\n",now.X,now.Y);
		}puts("");
		exit(0);
	}
	if(true)
	{
		int sum=0;
		for(int i=0;i<(int)s.size();i++)sum+=s[i];
		assert(sum==6);
	}
	for(int i=0;i<(int)s.size();i++)if(s[i]<-2||2<s[i])return false;
	set<Point>vis;
	Point now=Point(1,1),pre=Point(0,0);
	for(int i=0;i<(int)s.size();i++)
	{
		if(vis.find(now.LeftTriangle(pre))!=vis.end())return false;
		vis.insert(now.RigtTriangle(pre));
		now.Move(s[i],pre);
	}
	assert(now.X==1&&now.Y==1);
//	for(int i=0;i<(int)s.size();i++)putchar('c'+s[i]);puts("");
	return true;
}
vector<int>LexicographicallySmallest(const vector<int>&_s)
{
	vector<int>s=_s;
	assert(IsValid(s));
	const int n=(int)s.size();
	vector<int>ans=s;
	for(int i=0;i<n-1;i++)rotate(s.begin(),s.begin()+1,s.end()),getmin(ans,s);
	reverse(s.begin(),s.end());
	for(int i=0;i<n;i++)getmin(ans,s),rotate(s.begin(),s.begin()+1,s.end());
	return ans;
}
vector<vector<int> >GenerateNext(const vector<int>&_s)
{
	vector<int>s=_s;
	assert(IsValid(s));
//	for(int i=0;i<(int)s.size();i++)putchar('c'+s[i]);puts("");
	vector<vector<int> >ans;
	const int n=(int)s.size();
	for(int i=0;i<n;i++)
	{
		vector<int>ta;
		if(s[0]-1>=-2&&s[1]-1>=-2)
		{
			ta.push_back(s[0]-1);
			ta.push_back(2);
			ta.push_back(s[1]-1);
			for(int j=2;j<n;j++)ta.push_back(s[j]);
		}
		else if(s[0]==-2&&s[1]==-2)
		{
			ta.push_back(3-((3-s[2])+1+(3-s[n-1])));
			for(int j=3;j<n-1;j++)ta.push_back(s[j]);
		}
		else if(s[0]==-2&&s[1]!=-2)
		{
			ta.push_back(s[n-1]-1);
			ta.push_back(s[1]-1);
			for(int j=2;j<n-1;j++)ta.push_back(s[j]);
		}
		else if(s[0]!=-2&&s[1]==-2)
		{
			ta.push_back(s[0]-1);
			ta.push_back(s[2]-1);
			for(int j=3;j<n;j++)ta.push_back(s[j]);
		}
		else assert(0);
		if(IsValid(ta))ans.push_back(ta);
		rotate(s.begin(),s.begin()+1,s.end());
	}
	return ans;
}
void Unique(vector<vector<int> >&s)
{
	for(int i=0;i<(int)s.size();i++)s[i]=LexicographicallySmallest(s[i]);
	sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
}
vector<vector<int> >Solve1()
{
	static char str[20];scanf("%s",str);
	vector<int>s;
	for(int i=0;str[i];i++)s.push_back(str[i]-'c');
//	IsValid(Format(s));assert(0);
	vector<vector<int> >ans=GenerateNext(Format(s));
	Unique(ans);
	return ans;
}
vector<vector<int> >Solve2()
{
	int n;scanf("%d",&n);
	vector<vector<int> >s[2];
	if(true)
	{
		vector<int>tmp;tmp.resize(3,2);
		s[0].push_back(tmp);
	}
	int d=0;
	for(int i=1;i<n;i++,d^=1)
	{
		s[d^1].clear();
		for(int j=0;j<(int)s[d].size();j++)
		{
			const vector<vector<int> >&ts=GenerateNext(Format(s[d][j]));
			for(int k=0;k<(int)ts.size();k++)s[d^1].push_back(ts[k]);
		}
		Unique(s[d^1]);
	}
	return s[d];
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		const vector<vector<int> >&ans=(GetProblemType()?Solve1():Solve2());
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			const vector<int>&s=ans[i];
			for(int j=0;j<(int)s.size();j++)putchar('c'+s[j]);
		}
		puts("");
	}
	return 0;
}
