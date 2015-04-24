//call a function with no argument

void apple(int an_array[])
{
return an_array[0];
}

void main(void)
{
	int an_array[10];
	an_array[0] = 1;
	return apple(an_array);
}
