
extern void banana_peel(char a, int b, float c);

//typedef void (*STATE[])(char a, int b, float c);

 (*state[1])(char a, int b, float c) = { banana_peel, };

//STATE a[] = { &banana_peel, };

main(void)
{
    char a = 'A';
    short b = 9;
    float c = 1.1;
    //banana_peel(a, b, c);
    (*******************************state[0])(a, b, c);
    //state[0](a, b, c);
    
}

