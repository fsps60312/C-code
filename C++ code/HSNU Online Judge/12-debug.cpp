#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#define M 30001
#define N 10001
#define F(n) Fi(i,n)
#define Fi(i,n) Fl(i,0,n)
#define Fl(i,l,n) for(int i=l;i<n;i++)
using namespace std;
struct MP{
    int x,t,d,tag;
}D[N*2];
inline bool operator<(MP a,MP b){
    return a.x<b.x;
}
struct tp{
    int x,tag;
}BST[4*M];
int query(int l,int r,int a,int b,int id,int x){
    //if(x==0)cout<<l<<' '<<r<<' '<<BST[id].tag<<endl;
    if(l>b||r<a)return BST[id].tag? r-l+1:BST[id].x;
    if(a<=l&&r<=b)return (BST[id].tag+=x)? r-l+1:BST[id].x;
    BST[id].x=query(l,(l+r)/2,a,b,id*2,x)+query((l+r)/2+1,r,a,b,id*2+1,x);
    return BST[id].tag? r-l+1:BST[id].x;
}
int main(int argc,char *argv[])
{
    ios_base::sync_with_stdio(false);
    int n;
    cin>>n;
    F(n){
        cin>>D[i*2].x>>D[i*2].t>>D[i*2+1].x>>D[i*2].d;
        D[i*2+1].t=D[i*2].t;
        D[i*2+1].d=D[i*2].d;
        D[i*2].tag=-(D[i*2+1].tag=-1);
    }
    sort(D,D+n*2);
    int sum=0,cu=0,now=0;
    F(n*2){
        sum+=(D[i].x-now)*cu;
        now=D[i].x;
        cu=query(0,M-1,D[i].t,D[i].d-1,1,D[i].tag);
        //cout<<"DD "<<i<<' '<<sum<<' '<<cu<<endl;
    }
    cout<<sum<<endl;
    return 0;
}
