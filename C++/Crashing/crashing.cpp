int main(int argc, char ** argv)
{
    int* toto = nullptr;
    *toto = 2; // Will crash (segfault)
    return 0;
}