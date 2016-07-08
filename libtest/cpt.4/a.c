/* a.c */

extern int shared;
int aaaa;

int main()
{
    int a = 100;
    swap(&a, &shared);
}
