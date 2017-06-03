#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9,PI=acos(-1.0);
void getmax(double &a,const double b){if(b>a)a=b;}
struct Tree
{
	double X,Y,D,H;
}S[100];
struct AngleRange
{
	double L,R;
	AngleRange(){}
	AngleRange(const double _L,const double _R):L(_L),R(_R){}
	AngleRange Offset(const double angle)const{return AngleRange(L+angle,R+angle);}
	bool operator<(const AngleRange &a)const{return L<a.L;}
};
double Amod(const double a)
{
	double ans=fmod(a,2.0*PI);
	if(ans<0.0)ans+=2.0*PI;
	return ans;
}
double Angle(const double x,const double y)
{
		 if(x>0.0&&y>=0.0)return atan2(y,x);
	else if(x<=0.0&&y>0.0)return atan2(-x,y)+0.5*PI;
	else if(x<0.0&&y<=0.0)return atan2(-y,-x)+1.0*PI;
	else if(x>=0.0&&y<0.0)return atan2(x,-y)+1.5*PI;
	else assert(0);
	return -1.0;
}
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
double Sq(const double x){return x*x;}
void GetFenceShadow(vector<AngleRange>&ans,const double dis,const double r,const double h,const double offset)
{
	const double lq=Hypot(r,h);
	if(lq<dis+EPS)return;
//	printf("dis=%.2f,r=%.2f,h=%.2f,offset=%.3f\n",dis,r,h,offset/PI*180);
	const double angle=acos(dis/lq)+atan(r/h);
//	printf("lq=%.3f,angle=%.3f\n",lq,angle/PI*180);
	if(h+EPS<dis)
	{
		const double bngle=-asin(dis/lq)+atan(r/h);
		assert(0.0<=bngle&&bngle<=angle);
		ans.push_back(AngleRange(-angle,-bngle).Offset(offset));
		ans.push_back(AngleRange(bngle,angle).Offset(offset));
	}
	else ans.push_back(AngleRange(-angle,angle).Offset(offset));
}
void GetTreeShadow(vector<AngleRange>&ans,const double dis,const double r2,const double r1,const double h1,const double offset)
{
	const double lq=Hypot(r1,h1);
	if(lq<dis-r2+EPS)return;
//	printf("dis=%.2f,r2=%.2f,r1=%.2f,h1=%.2f,offset=%.3f\n",dis,r2,r1,h1,offset/PI*180);
	double angle;
	if(lq>=sqrt(dis*dis-Sq(r1+r2)))angle=asin((r1+r2)/dis);
	else angle=acos((dis*dis+lq*lq-r2*r2)/(2.0*dis*lq));
//	printf("lq=%.3f,angle=%.3f\n",lq,angle/PI*180);
	if(h1+EPS<dis-r2)
	{
		const double bngle=asin((r2+h1)/dis);
		assert(0.0<=bngle&&bngle<=angle);
		ans.push_back(AngleRange(-angle,-bngle).Offset(offset));
		ans.push_back(AngleRange(bngle,angle).Offset(offset));
	}
	else ans.push_back(AngleRange(-angle,angle).Offset(offset));
}
bool EXIST[100];
double XMN,YMN,XMX,YMX;
int N;
bool CanCut(const int u)
{
	if(!EXIST[u])return false;
	vector<AngleRange>tmp;
	GetFenceShadow(tmp,XMX-S[u].X,0.5*S[u].D,S[u].H,0.0);
	GetFenceShadow(tmp,S[u].Y-YMN,0.5*S[u].D,S[u].H,0.5*PI);
	GetFenceShadow(tmp,S[u].X-XMN,0.5*S[u].D,S[u].H,1.0*PI);
	GetFenceShadow(tmp,YMX-S[u].Y,0.5*S[u].D,S[u].H,1.5*PI);
	for(int i=0;i<N;i++)if(i!=u&&EXIST[i])
	{
		GetTreeShadow(tmp,Hypot(S[i].X-S[u].X,S[i].Y-S[u].Y),0.5*S[i].D,0.5*S[u].D,S[u].H,Angle(S[i].X-S[u].X,S[i].Y-S[u].Y));
	}
	vector<AngleRange>segs;
	for(const AngleRange &a:tmp)
	{
		const double l=Amod(a.L),r=Amod(a.R);
		if(l<=r)segs.push_back(AngleRange(l,r));
		else segs.push_back(AngleRange(l,2.0*PI)),segs.push_back(AngleRange(0.0,r));
	}
	sort(segs.begin(),segs.end());
//	printf("u=%d\n",u);
//	for(const AngleRange &a:segs)printf("(%.3f,%.3f)\n",a.L/PI*180,a.R/PI*180);
	double r=0.0;
	for(const AngleRange &a:segs)
	{
		if(a.L<=r+EPS)getmax(r,a.R);
		else return true;
	}
	return r+EPS<2.0*PI;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf%lf%lf%d",&XMN,&YMN,&XMX,&YMX,&N)==5&&(XMN||YMN||XMX||YMX||N))
	{
		for(int i=0;i<N;i++){Tree &s=S[i];scanf("%lf%lf%lf%lf",&s.X,&s.Y,&s.D,&s.H);EXIST[i]=true;}
//		for(int i=0;i<N;i++)printf("CanCut(%d)=%d\n",i,CanCut(i));return 0;
		int ans=0;
		for(bool changed=true;changed;)
		{
			changed=false;
			for(int j=0;j<N;j++)if(CanCut(j))EXIST[j]=false,++ans,changed=true;
		}
		static int kase=0;
		printf("Forest %d\n%d tree(s) can be cut\n\n",++kase,ans);
	}
}
