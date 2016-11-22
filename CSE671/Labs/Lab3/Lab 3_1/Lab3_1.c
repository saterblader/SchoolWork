int a=1, b=2, c=3;
int proc1(int a, int b, int c)
{
	if (a > 0)
		return b-c;
	else
		return b+c;
}
int main()
{
	int w, x, y;
	w=proc1(a,b,c);
	switch (w)
	{
		case 0: x=3; break;
		case 1: x=4; break;
		case 2: x=7; break;
		default: x=9; break;
	}
	y=w+x;
	return 0;
}