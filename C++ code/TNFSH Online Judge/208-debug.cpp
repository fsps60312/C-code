#include<bits/stdc++.h>
using namespace std;
int n,m,k;
long long w[550][550],lx[550],ly[550],slack[550];
int left1[550];
bool s[550],t[550];
bool match(int i){
    //cout<<i<<lx[i]<<ly[1]<<w[i][1];
    s[i]=1;
    for(int j=1;j<=m;j++) if(lx[i]+ly[j]==w[i][j]&&!t[j]){
        t[j]=1;
        if(!left1[j]||match(left1[j])){
            left1[j]=i;
            return true;
        }
    }
    return false;
}

void update(){
    long long a=1<<30;
    for(int i=1;i<=m;i++) if(!t[i])
        for(int j=1;j<=n;j++) if(s[j])
            {a=min(a,lx[j]+ly[i]-w[j][i]);}
    for(int i=1;i<=m;i++) if(t[i]){ly[i]+=a;}
    for(int i=1;i<=n;i++) if(s[i]){lx[i]-=a;}
}

long long km(){
    for(int i=1;i<=m;i++) ly[i]=left1[i]=0;
    for(int i=1;i<=n;i++) lx[i]=0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            lx[i]=max(lx[i],w[i][j]);

    }

    for(int i=1;i<=n;i++){
            int k=0;
            //cout<<i;
            
        while(1){
            k++;
            for(int i=1;i<=n;i++) s[i]=0;
            for(int i=1;i<=m;i++) t[i]=0;
            if(match(i)){break;}
            else {update();}
            //cout<<endl;
          if(k>n+10)break;
        }
    }



    long long ans=0;
    for(int i=1;i<=n;i++) ans+=lx[i];
    for(int i=1;i<=m;i++) ans+=ly[i];
    return ans;
}




int main(){
	freopen("in.txt","r",stdin);
    int q;
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d",&n,&m,&k);
        if(n>m)m=n;
        memset(w,0,sizeof(w));
        while(k--){
            int a,b;
            long long c,d;
            scanf("%d%d%lld%lld",&a,&b,&c,&d);
            w[a][b]=c*8*9*5*7/d;

        }

        long long q=km(),p=1;
        if(q%2)p*=2;
        else q/=2;
        if(q%2)p*=2;
        else q/=2;
        if(q%2)p*=2;
        else q/=2;
        if(q%3)p*=3;
        else q/=3;
        if(q%3)p*=3;
        else q/=3;
        if(q%5)p*=5;
        else q/=5;
        if(q%7)p*=7;
        else q/=7;
        cout<<q<<" "<<p<<endl;

    }

}
