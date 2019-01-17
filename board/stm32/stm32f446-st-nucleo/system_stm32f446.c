volatile unsigned long * CPACR = (volatile unsigned long *)0xE000ED88;

void SystemInit(void)
{
	/* 开启FPU */
	*CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
 
 
}


int main()
{

	return 0;
}
