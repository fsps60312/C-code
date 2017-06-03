#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cassert>
using namespace std;
const double EPS=1e-9,INF=1e100;
struct Node
{
	Node *ch[2];
	int sz;
	double v,mx;
	Node(const double &_v):sz(1),v(_v),mx(v),ch{NULL,NULL}{}
};
int Sz(Node* &o){return o?o->sz:0;}
double Mx(Node* &o){return o?o->mx:-INF;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->mx=max(o->v,max(Mx(o->ch[0]),Mx(o->ch[1])));
}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
void PushBack(Node* &o,const double &v)
{
	if(!o){o=new Node(v);return;}
	PushBack(o->ch[1],v);
	Maintain(o);
	Rotate(o);
}
void PopFront(Node* &o)
{
	if(!o->ch[0]){o=o->ch[1];return;}
	PopFront(o->ch[0]);
	Maintain(o);
	Rotate(o);
}
struct Matrix
{
	double s[2][2];
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)
		{
			double &v=ans.s[i][j]=0.0;
			for(int k=0;k<2;k++)v+=s[i][k]*a.s[k][j];
		}
		return ans;
	}
	bool ReachINF(const double &v)const{return v<-INF||v>INF;}
	bool ReachINF()const{return ReachINF(s[0][0])||ReachINF(s[0][1])||ReachINF(s[1][0])||ReachINF(s[1][1]);}
	void Print()
	{
		printf("%.4f %.4f\n%.4f %.4f\n\n",s[0][0],s[0][1],s[1][0],s[1][1]);
	}
}M;
int T;
double A,B;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf%lf%lf%lf",&M.s[0][0],&M.s[0][1],&M.s[1][0],&M.s[1][1]);
		scanf("%lf%lf",&A,&B);
		M.s[0][1]*=-1.0;
//		M.s[0][0]+=1.0,M.s[1][1]+=1.0;
		bool found=false;
		Node *na=NULL,*nb=NULL;
		for(int cnt=0;!M.ReachINF()&&cnt<1000000;M=M*M,cnt++)
		{
			const double a=A*M.s[0][0]+B*M.s[0][1],b=A*M.s[1][0]+B*M.s[1][1];
			M.Print();
			printf("a=%.4f,b=%.4f\n",a,b);
			PushBack(na,fabs(a)),PushBack(nb,fabs(b));
			assert(Sz(na)==Sz(nb));
			if(Sz(na)>1000)PopFront(na),PopFront(nb);
			if(a<-1e75||a>1e75||b<-1e75||b>1e75)
			{
				if(a>1e50&&b>1e50)puts("Both hares and foxes will overgrow.");
				else if(a>1e50&&b<-1e50)puts("Hares will overgrow while foxes will die out.");
				else if(a<-1e50&&b>1e50)puts("Hares will die out while foxes will overgrow.");
				else if(a<-1e50&&b<-1e50)puts("Both hares and foxes will die out.");
				else assert(0);
				found=true;
				break;
			}
			else if(Mx(na)<EPS&&Mx(nb)<EPS)
			{
				puts("Ecological balance will develop.");
				found=true;
				break;
			}
		}
		if(M.ReachINF())printf("ReachINF%.4f\n",INF);
		if(!found)puts("Chaos will develop.");
	}
	return 0;
}
