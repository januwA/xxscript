int f() {return 3; };

int main()
{
    int arr[] = {1, 2, f()};
    return arr[1];
}