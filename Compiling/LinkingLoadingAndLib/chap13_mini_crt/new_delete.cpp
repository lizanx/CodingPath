extern "C"
{
    void *malloc(unsigned int);
    void free(void *);
}

void *operator new(unsigned int size)
{
    return malloc(size);
}

void operator delete(void *ptr)
{
    free(ptr);
}

void *operator new[](unsigned int size)
{
    return malloc(size);
}

void operator delete[](void *ptr)
{
    free(ptr);
}
