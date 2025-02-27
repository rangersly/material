// Copyright (c) 2024 e0x1a.ly. All rights reserved.
#include<iostream>
using namespace std;
class Node
{
public:
	Node(){c_l=c_r=c_max=c_sum=c_lag=0;tl=NULL;tr=NULL;}

	void build(int *arr,int l,int r)
	{
		c_l=l;c_r=r;
		if(l==r) {c_max=arr[l];c_sum=arr[l];}
		else {
			tl=new Node;tr=new Node;
			tl->build(arr,l,(l+r)/2);
			tr->build(arr,(l+r)/2+1,r);
			c_max = tl->c_max > tr->c_max ? tl->c_max:tr->c_max;
			c_sum = tl->c_sum + tr->c_sum;
		}
	}	

	void print(int cnt=1)
	{
		printf("%5d---%5d---%5d\n",cnt,c_max,c_sum);
		if(c_l != c_r)
		{
			tl->print(cnt+1);
			tr->print(cnt+1);
		}
	}


	int ask_max(int l,int r)
	{
		if(c_l >= l && c_r <= r)
			return c_max;
		int t_max1=0,t_max2=0;
		if((c_l+c_r)/2 < r) t_max1=tr->ask_max(l,r);
		if((c_l+c_r)/2+1 > l) t_max2=tl->ask_max(l,r) ;
		return t_max1 > t_max2 ? t_max1 : t_max2;
	}

	int ask_sum(int l,int r)
	{
		if(c_l >= l && c_r <= r)
			return c_sum;
		int t_sum1=0,t_sum2=0;
		if((c_l+c_r)/2 < r) t_sum1=tr->ask_sum(l,r);
		if((c_l+c_r)/2+1 > l) t_sum2=tl->ask_sum(l,r) ;
		return t_sum1 + t_sum2;
	}

	void change(int x,int value)
	{
		if(c_l == x && c_r == x)
			c_max=c_sum=value;
		else {
			if((c_l+c_r)/2+1 >x) tl->change(x,value);
			else tr->change(x,value);
			c_max = tl->c_max > tr->c_max ? tl->c_max:tr->c_max;
			c_sum = tl->c_sum + tr->c_sum;
		}
	}
	
	void add(int l,int r,int value)
	{
		if(c_l >= l && c_r <= r)
		{
			if(c_l==c_r)
				c_sum=c_max+=value;
			else {
				c_lag+=value;
			}
		} else if(c_l != c_r){
			if(l <= (c_l+c_r)/2) tl->add(l,r,value);	
			if(r > (c_l+c_r)/2) tr->add(l,r,value);
			c_max = tl->c_max > tr->c_max ? tl->c_max:tr->c_max;
			c_sum = tl->c_sum + tr->c_sum;
		}
	}

private:
	int c_l,c_r,c_max,c_sum,c_lag;
	Node *tl,*tr;
};

int main()
{
	Node s;
	int *arr,n;
	cin>>n;
	arr=new int[n+1];arr[0]=n;
	for(int i=1;i<(n+1);i++)
		cin>>arr[i];
	s.build(arr,1,n);
	s.print();
	while(1)
	{	
		int x,y,v;
		cin>>n;
		if(!n)break;
		switch(n)
		{
			case 1: cin>>x>>y;s.change(x,y);break;
			case 2: cin>>x>>y;cout<<s.ask_max(x,y)<<endl;break;
			case 3: cin>>x>>y>>v;s.add(x,y,v);break;
			case 4: cin>>x>>y;cout<<s.ask_sum(x,y)<<endl;break;
		}
	}
	return 0;
}
