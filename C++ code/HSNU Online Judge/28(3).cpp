#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int N,K,P,ORD[500000],INQ[100001];
int NXI[500001],PRE[100001];
struct MyPriQueue
{
	vector<int>time,drive;
	void Clear(){time.clear(),drive.clear();time.push_back(-1),drive.push_back(-1);}
	int Sz(){return time.size()-1;}
	void Swap(int a,int b)
	{
		swap(INQ[drive[a]],INQ[drive[b]]);
		swap(time[a],time[b]);
		swap(drive[a],drive[b]);
	}
	void Sink(int idx)
	{
		if(idx*2+1<=Sz()&&time[idx*2]>time[idx]&&time[idx*2+1]>time[idx])
		{
			if(time[idx*2]>time[idx*2+1]){Swap(idx,idx*2);Sink(idx*2);}
			else{Swap(idx,idx*2+1);Sink(idx*2+1);}
		}
		else if(idx*2<=Sz()&&time[idx*2]>time[idx]){Swap(idx,idx*2);Sink(idx*2);}
		else if(idx*2+1<=Sz()&&time[idx*2+1]>time[idx]){Swap(idx,idx*2+1);Sink(idx*2+1);}
	}
	void Delete(int idx)
	{//idx=1;
		Swap(idx,Sz());
		INQ[drive[Sz()]]=0;
		time.pop_back(),drive.pop_back();
		Sink(idx);
	}
	void Pop(){Delete(1);}
	void Float(int idx)
	{
		while(idx/2&&time[idx]>time[idx/2])
		{
			Swap(idx/2,idx);
			idx/=2;
		}
	}
	void Push(int d,int nxi)
	{
		time.push_back(nxi),drive.push_back(d);
		INQ[d]=Sz();
		Float(Sz());
	}
	void Check()
	{
		for(int i=2;i<=Sz();i++)
		{
			if(time[i]>time[i/2])
			{
				printf("time[%d]=%d > time[%d]=%d\n",i,time[i],i/2,time[i/2]);
				printf("Sz()=%d\n",Sz());
				assert(0);
			}
		}
	}
}PQ;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&P);
	PQ.Clear();
	for(int i=1;i<=N;i++)
	{
		PRE[i]=500000;
		INQ[i]=0;
	}
	for(int i=0;i<P;i++)
	{
		scanf("%d",&ORD[i]);
		NXI[PRE[ORD[i]]]=i;
		PRE[ORD[i]]=i;
		NXI[i]=P+1;
	}
//	for(int i=0;i<P;i++)printf(" %d",NXI[i]);puts("");
	int ans=0;
	for(int i=0;i<P;i++)
	{
		if(INQ[ORD[i]])
		{
//printf("Update %d\n",ORD[i]);
			PQ.Delete(INQ[ORD[i]]);
//			assert(!INQ[ORD[i]]);
		}
		if(PQ.Sz()==K)
		{
//printf("Remove %d\n",PQ.drive[1]);
			PQ.Pop();
			ans++;
		}
//printf("Insert %d\n",ORD[i]);
		PQ.Push(ORD[i],NXI[i]);
		PQ.Check();
	}
	printf("%d\n",ans);
	return 0;
}
