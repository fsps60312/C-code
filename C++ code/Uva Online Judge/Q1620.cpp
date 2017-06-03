#include<cstdio>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
int T,N;
int S[500];
void Show()
{
	for(int i=0;i<N;i++)printf(" %d",S[i]);puts("");
}
void Swap(int &a,int &b)
{
	static int tmp;
	tmp=a,a=b,b=tmp;
}
void Rotate(int idx)
{
	Swap(S[idx],S[idx+3]);
	Swap(S[idx+1],S[idx+2]);
	Show();
}
bool RotateToFit(int v)
{
	int idx=0;
	for(;idx<N;idx++)if(S[idx]==v)break;
	if(idx>=N)termin("can't find %d\n",v);
	if(idx==v)return true;
	while(idx-v>=3)
	{
		idx-=3;
		Rotate(idx);
	}
	if(idx==v)return true;
	if(v+4>=N)return false;
	while(idx-v<3)
	{
		Rotate(idx-1);
		idx++;
	}
	Rotate(v);
	return true;
}
bool solve()
{
	for(int i=0;i<N;i++)if(!RotateToFit(i))return false;
	return true;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=1;i<N;i++)
		{
			if(S[i]==1)
			{
				static int tmp[500];
				for(int j=0;j<N;j++)tmp[j]=S[(i+j)%N];
				for(int j=0;j<N;j++)S[i]=tmp[i];
				break;
			}
		}
		for(int i=0;i<N;i++)S[i]--;
		printf(solve()?"possible\n":"impossible\n");
	}
	return 0;
}
