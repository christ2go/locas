// "AND" funktion der alu

void and(int a[4],int b[4])
{
	for(int i = 0;i<4;i++)
		if((a[i] == 1)&&(b[i] == 1)){a[i] = 1;}else{a[i] = 0;}
}
