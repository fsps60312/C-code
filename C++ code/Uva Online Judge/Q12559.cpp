#include<cstdio>
#include<map>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
const int PI=acos(-1.0);
int T,W,H;
char MAT[100][100];
map<int,int>CNT[100][100];
void Insert(int h,int w,int r)
{
	map<int,int>&m=CNT[h][w];
	if(m.find(r)==m.end())m[r]=1;
	else m[r]++;
}
inline int hypot(int a,int b){return a*a+b*b;}
inline int sqrt(int v)
{
	static int l,r,mid;
	l=1,r=v;
	while(l<r)
	{
		mid=(l+r+1)/2;
		if(mid*mid>v)r=mid-1;
		else l=mid;
	}
	return l;
}
inline void Update(int h,int w,int r)
{
	if(r<25)return;
	static int v;
	v=sqrt(r);
	
	Insert(h,w,v++);
	if(v*v<r)Insert(h,w,v);
}
struct Ans
{
	int w,h,r;
	double ratio;
	Ans(){}
	Ans(int w,int h,int r,int cnt):w(w),h(h),r(r),ratio((double)cnt/r){}
	bool operator<(const Ans &a)const{return ratio>a.ratio;}
};
bool cmp(Ans a,Ans b)
{
	if(a.r!=b.r)return a.r<b.r;
	if(a.w!=b.w)return a.w<b.w;
	return a.h<b.h;
}
vector<Ans>ANS;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&W,&H);
		for(int h=0;h<H;h++)
		{
			for(int w=0;w<W;w++)
			{
				CNT[h][w].clear();
				char &v=MAT[h][w];
				do
				{
					scanf("%c",&v);
				}while(v!='0'&&v!='1');
			}
		}
		static int h0,w0,h1,w1,r;
		for(h0=0;h0<H;h0++)
		{
			for(w0=0;w0<W;w0++)
			{
				if(MAT[h0][w0]=='0')continue;
				for(h1=0;h1<H;h1++)
				{
					for(w1=0;w1<W;w1++)
					{
						r=hypot(w1-w0,h1-h0);
						Update(h1,w1,r);
					}
				}
			}
		}
		ANS.clear();
		for(int h=0;h<H;h++)
		{
			for(int w=0;w<W;w++)
			{
				map<int,int>&m=CNT[h][w];
				for(map<int,int>::iterator it=m.begin();it!=m.end();it++)ANS.push_back(Ans(w,h,it->first,it->second));
			}
		}
		sort(ANS.begin(),ANS.end());
		int idx=1;
		while(idx<5&&ANS[idx].ratio>1.5*PI)idx++;
		static int kase=1;
		printf("Case %d: %d",kase++,idx);
		sort(ANS.begin(),ANS.begin()+idx,cmp);
		for(int i=0;i<idx;i++)printf(" (%d,%d,%d)",ANS[i].r,ANS[i].w,ANS[i].h);
		puts("");
	}
	return 0;
}
