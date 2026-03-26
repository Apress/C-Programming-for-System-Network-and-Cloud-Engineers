#include<stdio.h>
void sum(void *a, void *b, int type)
{
	if (type==1)
	{
		int r=*(int*)a+*(int*)b;
		printf("Sum: %d\n",r);

	}
	if (type==2)
	{
		float r = *(float*)a+*(float*)b;
		printf("Sum: %f\n",r);
	}
}



void mul(void *a, void *b, int type)
{
        if (type==1)
        {
                int r=*(int*)a * *(int*)b;
                printf("MUL: %d\n",r);

        }
        if (type==2)
        {
                float r = *(float*)a * *(float*)b;
                printf("MUL: %f\n",r);
        }
}

void div(void *a, void *b, int type)
{
        if (type==1)
        {
                int r=*(int*)a / *(int*)b;
                printf("DIVISON: %f\n",r);

        }
        if (type==2)
        {
                float r = *(float*)a / *(float*)b;
                printf("DIVISON: %f\n",r);
        }
}


void CommonInteface(int op, int type, void *a, void *b)
{
	void (*arithOp)(void *,void *, int);
	if (op==1)
	{
        	arithOp=sum;
        	(*arithOp)(a,b,type);
	}
	if (op==2)
	{
        	arithOp=mul;
        	(*arithOp)(a,b,type);
	}
	if (op==3)
	{
        	arithOp=div;
        	(*arithOp)(a,b,type);
	}

}

int main()
{
	int a=1,b=2;
	float c=1.2,d=2.2;
	sum(&a,&b,1);
	sum(&c,&d,2);
	
	mul(&a,&b,1);
	mul(&c,&d,2);

	div(&a,&b,1);
	div(&c,&d,2);
	CommonInteface(1,1,&a,&b);
	CommonInteface(1,2,&c,&d);

	CommonInteface(2,1,&a,&b);
	CommonInteface(2,2,&c,&d);


	CommonInteface(3,1,&a,&b);
	CommonInteface(3,2,&c,&d);

	void (*arithOp)(void *,void *, int);
	arithOp=sum;
	(*arithOp)(&a,&b,1);
	(*arithOp)(&c,&d,2);
	arithOp=mul;
	(*arithOp)(&a,&b,1);
	(*arithOp)(&c,&d,2);
	arithOp=div;
	(*arithOp)(&a,&b,1);
	(*arithOp)(&c,&d,2);

}
