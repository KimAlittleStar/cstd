#include "cvector.h"

V_Declare_Vector(int, int_t);

void printInt(const int *i)
{
    printf("%d ", *i);
}

void cvt_demotest(void)
{
    VCT_int_t *a = VCT_newVCT_int_t();
    a->toString = printInt;
    a->size = 10;
    a->data = NULL;
    a->reSize(a, 4);
    a->append(a, 1);
    a->append(a, 2);
    a->show(a);
}
