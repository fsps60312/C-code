#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int N,K,P,ORD[500000],INQ[100001];
queue<int>NXI[100001];
struct MyPriQueue
{
	vector<int>time,drive;
	MyPriQueue(){time.push_back(-1),drive.push_back(-1);}
	int Sz(){return time.size()-1;}
	void Expand(int idx){while(time.size()<=idx)time.push_back(-1),drive.push_back(-1);}
	void Swap(const int &a,const int &b)
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
	{
		Swap(idx,Sz());
		INQ[drive[Sz()]]=0;
		time.pop_back(),drive.pop_back();
		if(idx<=Sz())Sink(idx);
	}
	void Pop(){Delete(1);}
	void Float(int idx)
	{
		if(idx/2&&time[idx]>time[idx/2])
		{
			Swap(idx/2,idx);
			Float(idx/2);
		}
	}
	void Push(int d,int nxi)
	{
		time.push_back(nxi),drive.push_back(d);
		INQ[d]=Sz();
		Float(Sz());
	}
}PQ;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&P);
	for(int i=0;i<P;i++)
	{
		scanf("%d",&ORD[i]);
		NXI[ORD[i]].push(i);
	}
	for(int i=1;i<=N;i++)
	{
		NXI[i].push(P+1);
		INQ[i]=false;
	}
	int ans=0;
	for(int i=0;i<P;i++)
	{
		NXI[ORD[i]].pop();
		if(INQ[ORD[i]])PQ.Delete(INQ[ORD[i]]);
		if(PQ.Sz()==K){PQ.Pop();ans++;}
		PQ.Push(ORD[i],NXI[ORD[i]].front());
	}
	printf("%d\n",ans);
	return 0;
}
