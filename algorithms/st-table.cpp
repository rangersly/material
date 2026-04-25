#include<bits/stdc++.h>
using namespace std;

int f[100001][30],n,m;

void init(int n)//计算区间预处理
{
	for(int i = 1;1<<i <= n;i++)
		for(int j = 1;(j+(1<<i)-1) <= n;j++)
			//f[j][i] = max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
			{int k=i-1;f[j][i] = f[j][k]>f[j+(1<<(k))][k] ? f[j][k] : f[j+(1<<(k))][k];}
}
inline int query(int L,int R)//查询
{
	int s = log2(R-L+1);
	//return max(f[L][s],f[R-(1<<s)+1][s]);
	return f[L][s]>f[R-(1<<s)+1][s] ? f[L][s] : f[R-(1<<s)+1][s];
}
inline int read()//快读int
{
	int data=0;bool n=false;char ch;
	while(1){if((ch=getchar())==EOF)return -1;if(!isdigit(ch)){if(n==true)break;else continue;}n=true;data=data*10+(int)(ch-48);}
	return data;
}
int main()
{
	cin>>n>>m;
	for(int i = 1;i <= n;i++)f[i][0]=read();//读入数据
	init(n);
	int L,R;
	while(m--)
	{
		L=read();R=read();
		printf("%d\n",query(L,R));
	}
	return 0;
}
