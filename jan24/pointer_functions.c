void no_change(int a)
{
    a = 2;
}

void yes_change(int *a)
{
    *a = 2;
}

int main()
{
    int x = 5;
    no_change(x);
    yes_change(&x);
    return 0;
}