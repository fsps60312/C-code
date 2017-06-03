#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Deq
{
	int S[500000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Front(const int i)const{return S[L+i];}
	int Back(const int i)const{return S[R-i];}
	int Size()const{return R-L+1;}
}DEQ;
int N,H[500000],ANS[500000],SQ[500000];
double GetX(const int i1,const int i2)
{
	assert(i1<i2&&H[i1]<H[i2]);
	const double v=H[i2]-H[i1];
	const double i=i2-i1;
	//sqrt(x)=v+sqrt(x-i)
	//sqrt(x)-v=sqrt(x-i)
	//x+v^2-2v*sqrt(x)=x-i
	//x+v^2-x+i=2v*sqrt(x)
	//v^2+i=2v*sqrt(x)
	//v^4+2iv^2+i^2=4v^2x
	//x=(v^4+2iv^2+i^2)/(4v^2)
	const double ans=(v*v*v*v+2.0*i*v*v+i*i)/(4.0*v*v)+i1;
//	printf("%.9f %.9f\n",sqrt(ans)-v,sqrt(ans-i));
//	printf("%.9f %.9f\n",ans+v*v-2.0*v*sqrt(ans),ans-i);
//	printf("%.9f %.9f\n",sqrt(ans),v+sqrt(ans-i));
//	printf("%.9f %.9f\n",H[i1]+sqrt(ans-i1),H[i2]+sqrt(ans-i2));
//	assert(fabs((H[i1]+sqrt(ans-i1))-(H[i2]+sqrt(ans-i2)))<1e-9);
	return ans;
}
bool NeedPopBack(const int i)
{
	if(DEQ.Size()==0)return false;
	if(H[DEQ.Back(0)]+sqrt(i-DEQ.Back(0))<=H[i])return true;
	if(DEQ.Size()==1)return false;
	return GetX(DEQ.Back(1),DEQ.Back(0))>=GetX(DEQ.Back(0),i);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d",&H[i]),ANS[i]=H[i];
	for(int a=1;;++a)
	{
		const int mn_dis=(a-1)*(a-1)+1,mx_dis=a*a;
		if(mn_dis>=N)break;
		for(int i=mn_dis;i<=mx_dis&&i<N;i++)SQ[i]=a;
	}
	for(int type=0;type<2;type++)
	{
		DEQ.Clear();
		for(int i=1;i<N;++i)
		{
			if(!DEQ.Size())DEQ.PushBack(i-1);
			else if(H[i-1]>H[DEQ.Back(0)])
			{
				while(NeedPopBack(i-1))DEQ.PopBack();
				DEQ.PushBack(i-1);
			}
			while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))<=i)DEQ.PopFront();
			getmax(ANS[i],H[DEQ.Front(0)]+SQ[i-DEQ.Front(0)]);
		}
		reverse(H,H+N),reverse(ANS,ANS+N);
	}
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]-H[i]);
	return 0;
}
