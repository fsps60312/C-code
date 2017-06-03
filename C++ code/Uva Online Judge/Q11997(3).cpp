#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int k;
int s1[750],s2[750],tmp[750];
void ranges1(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	ranges1(a,mid);
	ranges1(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&s1[c]<s1[d])) tmp[i]=s1[c++];
		else tmp[i]=s1[d++];
	}
	for(int i=a;i<=b;i++) s1[i]=tmp[i];
}
void ranges2(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	ranges2(a,mid);
	ranges2(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&s2[c]<s2[d])) tmp[i]=s2[c++];
		else tmp[i]=s2[d++];
	}
	for(int i=a;i<=b;i++) s2[i]=tmp[i];
}
struct pairtype
{
	int x,y;
	bool operator>(pairtype a){return x<a.x;}
	bool operator<(pairtype a){return x>a.x;} 
};
struct heap
{
	vector<pairtype> v;
	void swap(int a,int b){pairtype c=v[a];v[a]=v[b];v[b]=c;}
	void push(int a,int b)
	{
		int d=v.size();
		pairtype c;c.x=a,c.y=b;
		v.push_back(c);
		while(d&&v[d]>v[d>>1])
		{
			swap(d,d>>1);
			d>>=1;
		}
	}
	pairtype top(){return v[0];}
	void pop()
	{
		swap(0,v.size()-1);
		v.pop_back();
		int b=-1,c=0;
		while(c!=b)
		{
			b=c;
			if((b<<1)<v.size()&&v[c]<v[b<<1]) c=(b<<1);
			if((b<<1)+1<v.size()&&v[c]<v[(b<<1)+1]) c=(b<<1)+1;
			swap(b,c);
		}
	}
};
void merge()
{
	heap a;
	for(int i=0;i<k;i++) a.push(s1[i]+s2[0],0);
	for(int i=0;i<k;i++)
	{
		pairtype j=a.top();a.pop();
		if(j.y+1<k) a.push(j.x-s2[j.y]+s2[j.y+1],j.y+1);
		s1[i]=j.x;
	}
}
int main()
{
	while(scanf("%d",&k)==1)
	{
		for(int i=0;i<k;i++) scanf("%d",&s1[i]);
		ranges1(0,k-1);
		//for(int i=0;i<k;i++)printf(" %d",s1[i]);printf("\n");
		for(int i=1;i<k;i++)
		{
			for(int j=0;j<k;j++) scanf("%d",&s2[j]);
			ranges2(0,k-1);
			//for(int j=0;j<k;j++)printf(" %d",s2[j]);printf("\n");
			merge();
		}
		printf("%d",s1[0]);for(int i=1;i<k;i++) printf(" %d",s1[i]);printf("\n");
	}
	return 0;
}
