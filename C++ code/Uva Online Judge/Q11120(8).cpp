#include<cstdio>
#include<vector>
#include<cassert>
#include<queue>
using namespace std;
int N;
queue<int>BUFFER;
struct Deq
{
	vector<int>s;
	int l,r;
	void clear(){s.clear();l=0,r=-1;}
	void push_back(const int v){s.push_back(v);r++;while(!empty()&&front()==0)pop_front();}
	void pop_front(){l++;}
	int front()const{return s[l];}
	bool empty()const{return r<l;}
	bool Subtractable(const vector<int>&a)const
	{
		assert(empty()||front());
		if(r-(int)a.size()+1!=l)return l<r-(int)a.size()+1;
		for(int i=(int)a.size()-1;i>=0;i--)if(s[r-i]!=a[i])return s[r-i]>a[i];
		return true;
	}
	void Sub(const vector<int>&a)
	{
		for(int i=(int)a.size()-1;i>=0;i--)s[r-i]-=a[i];
		for(int i=r;i>=l;i--)if(s[i]<0)
		{
			assert(i>l);
			s[i-1]--,s[i]+=10,assert(s[i]>=0);
		}
		while(!empty()&&front()==0)pop_front();
	}
//	void Print(){for(int i=l;i<=r;i++)putchar('0'+s[i]);puts("");}
}DEQ;
int Pop(){const int ans=BUFFER.front();BUFFER.pop();return ans;}
void ExpandBUFFER(){BUFFER.push(0),BUFFER.push(0);}
void Extract(){assert(BUFFER.size()>=2);DEQ.push_back(Pop()),DEQ.push_back(Pop());ExpandBUFFER();}
void BuildBUFFER()
{
	vector<int>tmp;
	while(N)tmp.push_back(N%10),N/=10;
	while(!BUFFER.empty())BUFFER.pop();
	for(int i=tmp.size()-1;i>=0;i--)BUFFER.push(tmp[i]);
	ExpandBUFFER();
}
vector<int>ADD;
void Plus(vector<int>&ans,const int b)
{
	if(ans.empty())ans.push_back(b);
	else ans[0]+=b;
	for(int i=0;i<ans.size()&&ans[i]>=10;i++)
	{
		if(i+1==ans.size())ans.push_back(0);
		ans[i+1]+=ans[i]/10,ans[i]%=10;
	}
}
vector<int>&PlusMul(const vector<int>&a,const int b)
{
	static vector<int>ans;
	if(b==0){ans.clear();return ans;}
	ans=a;
	if(ans.empty())ans.push_back(0);
	ans[0]+=b;
	for(int i=0;i<ans.size();i++)ans[i]*=b;
	for(int i=0;i<ans.size();i++)if(ans[i]>=10)
	{
		if(i+1==ans.size())ans.push_back(0);
		ans[i+1]+=ans[i]/10,ans[i]%=10;
	}
	return ans;
}
bool FindAns(const vector<int>&seq)
{
	if(seq.size()<3)return false;
	const int r=seq.size()-1;
	return seq[r]==seq[r-1]&&seq[r]==seq[r-2];
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		if(!N)
		{
			assert(scanf("%d",&N)==-1);
			break;
		}
		assert(N>=2&&N<1000000);
		printf("%d ",N);
		BuildBUFFER();
		vector<int>ans;
		DEQ.clear();
		ADD.clear();
		if(BUFFER.size()%2==1)DEQ.push_back(Pop());
		else Extract();
		assert(BUFFER.size()%2==0);
		for(;;)
		{
			int l=0,r=9;
			while(l<r)
			{
				const int mid=(l+r+1)/2;
				if(DEQ.Subtractable(PlusMul(ADD,mid)))l=mid;
				else r=mid-1;
			}
			assert(l==r&&r>=0&&r<=9&&DEQ.Subtractable(PlusMul(ADD,r)));
			DEQ.Sub(PlusMul(ADD,r));
			Plus(ADD,r*2);
			ADD.push_back(-1);
			for(int i=ADD.size()-1;i>0;i--)ADD[i]=ADD[i-1];
			ADD[0]=0;
			ans.push_back(r);
			if(FindAns(ans))
			{
				printf("%d %d\n",(int)ans.size()-3,ans[ans.size()-1]);
				break;
			}
			Extract();
		}
	}
	return 0;
}
