#include<cstdio>
#include<vector>
#define min(x,y) (x<y?x:y)
const int INF=2147483647;
int Z,N,F[1000000],C[1000000];
struct Deq
{
	vector<int>val,idx;
	void clear(){val.clear(),idx.clear();}
	int Sz(){return val.size();}
	bool empty(){return Sz()==0;}
	void push_back(const int &v,const int &i){val.push_back(v),idx.push_back(i);}
	void pop_back(){val.pop_back(),idx.pop_back();}
	int &backv(){return val[val.size()-1];}
	int &backi(){return idx[idx.size()-1];}
}DEQ;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&Z);
	while(Z--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&F[i]);
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		int ans=0;
		DEQ.clear();
		DEQ.push_back(INF,-1);
		for(int i=0;i<N;i++)
		{
			while(!DEQ.empty()&&C[i]<DEQ.frontv())DEQ.pop_front();
			while(!DEQ.empty()&&F[i]>=DEQ.backv())
			{
				int low=DEQ.backv(),l=DEQ.backi();
				DEQ.pop_back();
				ans+=(min(F[i],DEQ.backv())-low)*(i-l);
				if(DEQ.backv()>F[i])break;
			}
			DEQ.push_back(F[i],i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
