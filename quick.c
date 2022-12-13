static double da[] = {3.0,1.3,0.4,78,13.2,-1.1,6.0,-3.2,-12};

int cmp(const void *a, const void *b)
{
    const double *aa = a;
    const double *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

void swap(void * val1P, void * val2P, int size){
    void *e = malloc(size);
    if(val1P == val2P) return;
    memcpy(e, val1P, size);
    memcpy(val1P, val2P, size);
    memcpy(val2P, e, size);
    free(e);
}

int partition(void *base, int n, int size){
    void *pivot = base;
    int pivotPos = 0;
    swap(base, base+n/2*size, size);
    for(int i=1; i<n; i++){
        if(cmp(base+i*size, base)<0){
            swap(base+(++pivotPos)*size, base+i*size, size);
        }
    }
    swap(pivot, base+pivotPos*size, size);
    return pivotPos;
}


void upo_quick_sort(void *base, int n, int size)
{
    printf("\nOK %d", n);
    if(n == 1) return;
    int q = partition(base, n, size);
    int n1 = q;
    int n2 = n-q-1;
    upo_quick_sort(base, n1, size);
    upo_quick_sort(base+(n1+2)*size, n2, size);
}

int main(){
  upo_quick_sort(&da, 9, 8);
  
  return 0;
}
