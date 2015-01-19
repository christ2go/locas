#include <stdio.h>
int add(int a[4],int b[4])
{
	// ARRAY : 0 0 0 0
	//         0 1 2 3
	//         8 4 2 1
	int carry = 0;
	for(int i = 3;i>=0;i--)
	{
		int res = a[i]+b[i]+carry;
		carry = 0;
		if(res == 0)
		{
			a[i] = 0;	
		}
		if(res == 1)
		{
			a[i] = 1;
		} 
		if(res == 2)
		{
			a[i] = 0;
			carry = 1;
		}
		if(res == 3)
		{
			a[i] = 1;
			carry = 1;
		}
	}
	return carry;
}

int addc(int a[4],int b[4],int carry)
{
	for(int i = 3;i>=0;i--)
	{
		int res = a[i]+b[i]+carry;

		carry = 0;
		if(res == 0)
		{
			a[i] = 0;	
		}
		if(res == 1)
		{
			a[i] = 1;
		} 
		if(res == 2)
		{
			a[i] = 0;
			carry = 1;
		}
		if(res == 3)
		{
			a[i] = 1;
			carry = 1;
		}
	}
	return carry;
}
