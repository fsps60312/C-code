#include<cstdio>
#include<utility>
using namespace std;
const int INF=2147483647;
inline void getmin(int &a,const int b){if(b<a)a=b;}
inline void getmax(int &a,const int b){if(b>a)a=b;}
template<class Type>
class LinkedList//1 indexed
{
	private:
		int LEFT[100001],*RIGHT[100001],*BEGIN,*END;
		Type DATA[100001];
		int SIZE;
	public:
		void Clear(){BEGIN=END=DATA,SIZE=0;}
		void PushBack(const Type &v){*END=v,RIGHT[END-DATA]=END-DATA+1,LEFT[END-DATA+1]=END-DATA,END++,SIZE++;}
		Type *Begin()const{return BEGIN;}
		Type *End()const{return END;}
		Type *Right(Type* i)const{return DATA+RIGHT[i-DATA];}
		Type *Left(Type* i)const{return DATA+LEFT[i-DATA];}
		int Size()const{return SIZE;}
};
int N,M,T[100000],J[100000],I[100000];
int Solve()
{
	static LinkedList<int>timeline;
	if(true)
	{
		static int sot[100001],next[100000],nsz,vals[100000];
		nsz=0;
		for(int i=1;i<=M;i++)sot[i]=-1;
		for(int i=0;i<M;i++)
		{
			vals[nsz]=i;
			next[nsz]=sot[T[i]];
			sot[T[i]]=nsz;
			nsz++;
		}
		timeline.Clear();
		for(int i=1;i<=M;i++)
		{
			for(int cur=sot[i];cur!=-1;cur=next[cur])timeline.PushBack(vals[cur]);
		}
	}
	for(int *i=timeline.Begin(),*j;i!=timeline.End();i=j)
	{
		j=timeline.Right(i);
		if(T[*i]==T[*j])
		{
			if(I[*i]!=I[*j])return false;
		}
	}
	static vector<int>left[100001],right[100001],vals[100001];
	for(int i=1;i<=M;i++)left[i].clear(),right[i].clear(),vals[i].clear();
	for(int *it=timeline.Begin();it!=timeline.End();it=timeline.Right(it))
	{
		const int sz=left[*it].size();
		vals[*it].push_back(T[*it]);
		left[*it].push_back(sz-1);
		right[*it].push_back(sz+1);
	}
	for(int *it=timeline.Begin();it!=timeline.End();it=timeline.Right(it))
	{
		
	}
	static int enter[100002],leave[100002];
	for(int i=1;i<=M+1;i++)enter[i]=leave[i]=0;
	for(int i=1;i<=N;i++)if(mn[i]!=INF)enter[mn[i]]++,leave[mx[i]+1]++;
	int certain=0,canleave=0,uncertain=0,leaved=0;
	for(int i=0,j=1;i<counts_size;i++)
	{
		const int cf=counts_first[i],cs=counts_second[i];
		for(;j<=cf;j++)
		{
			const int v=(enter[j]<uncertain?enter[j]:uncertain);
			uncertain-=v,certain+=v,enter[j]-=v;
			certain+=enter[j];
			certain-=leave[j],canleave+=leave[j];
		}
		while(certain+canleave+uncertain<cs)uncertain++;
		while(certain+canleave+uncertain>cs)
		{
			if(canleave)canleave--,leaved++;
			else
			{
				if(!uncertain)return false;
				uncertain--,leaved++;
			}
		}
	}
	return certain+uncertain+canleave+leaved<=N;
}
inline int readchar() {
    const int n = 1048576;
    static char buf[n];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, n, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline void ReadInt(int &v)
{
	const int zero='0',nine='9';
	int c=readchar();
	while(c<zero||c>nine)c=readchar();
	v=0;
	while(c>=zero&&c<=nine)v=v*10+(c-zero),c=readchar();
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;
	ReadInt(testcount);
	while(testcount--)
	{
		ReadInt(N),ReadInt(M);
		for(int i=0;i<M;i++)ReadInt(T[i]),ReadInt(J[i]),ReadInt(I[i]);
		int l=0,r=M;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",r);
	}
	return 0;
}
