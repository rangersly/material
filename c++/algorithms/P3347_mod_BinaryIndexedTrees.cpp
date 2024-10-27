//Copyright(c) 2024 e0x1a&ly. All right reserved.
#include<iostream>
#include<vector>

using namespace std;

void init(vector<int> &a)
{
	for(int i=1; i < a.size(); i++)
	{
		int lowbit=(i & -i)>>1;
		while(lowbit)
		{
			a[i]+=a[i-lowbit];
			lowbit=lowbit>>1;
		}
	}
}
void add(int x,int k,vector<int> &a)
{
	for(; x < a.size(); x+=(x & -x)) a[x]+=k;
}
int ask(int x,vector<int> &a)
{
	int ans=0;
	while(x) { ans+=a[x];x-=(x & -x);}
	return ans;
}


int main()
{
	//data init
	int n,m,temp;
	vector<int>a;a.push_back(0);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	{
		scanf("%d",&temp);
		a.push_back(temp);
	}
	init(a);


	while(m--)	//在线操作
	{
		int x,y;
		scanf("%d%d%d",&temp,&x,&y);
		if(temp==1)
			add(x,y,a);
		else printf("%d\n",ask(y,a)-ask(x-1,a));
	}

	return 0;
}
