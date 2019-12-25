#include "cstackqueue.h"
//#include "memwatch.h"
typedef struct
{
    char *name;
} Customer;

extern void tostring(const Customer *c);
void freecustomer(Customer *c);
SQ_Define(Customer, Customer);

SQ_Declare(Customer, Customer, tostring, freecustomer);

void tostring(const Customer *c)
{
    printf("customer name = %s \n", c->name);
}

void freecustomer(Customer *c)
{
    if (c != NULL)
        free(c->name);
}

void toStringPoint(const Point_t *p)
{
    printf("point {%d,%d}", p->x, p->y);
}

void cstackqueue_test(void)
{
#if 0
    SQ_Customer *cus = SQ_newSQ_Customer();
    char *nametab[] = {"bob", "tom", "kim", "foolDog", "stupid", "zhazha"};
    Customer c;
    for (size_t i = 0; i < (sizeof(nametab) / sizeof(nametab[0])); i++)
    {
        c.name = malloc(20);
        strcpy(c.name, nametab[i]);
        cus->enqueue(cus, c);
    }
    cus->show(cus);

    printf("the top name :%s\n", cus->top(cus).name);
    printf("the button name :%s\n", cus->button(cus).name);
    cus->pop(cus);

    printf("the top name :%s\n", cus->top(cus).name);
    printf("the button name :%s\n", cus->button(cus).name);
    cus->dequeue(cus);

    printf("the top name :%s\n", cus->top(cus).name);
    printf("the button name :%s\n", cus->button(cus).name);
    cus->pop(cus);

    SQ_deleteSQ_Customer(cus);
#endif
#if 1
    SQ_Classt *stack = SQ_newSQ_Classt();
    Point_t pox;
    pox.x = 1;
    pox.y = 1;
    for (u16 i = 1; i < 20; i++)
    {
        if (i & 0x01)
            pox.x = i;
        else
            pox.y = i;
        stack->enqueue(stack, pox);
    }
    stack->toString = toStringPoint;
    stack->show(stack);
    while (stack->getSize(stack) != 5)
    {
        Point_t t = stack->button(stack);
        toStringPoint(&t);
        stack->dequeue(stack);
        printf("\nstack size = %d\n", stack->getSize(stack));
    }
    pox.x = 255;
    pox.y = 255;
    stack->enqueue(stack, pox);

    pox.x = 128;
    pox.y = 128;
    stack->enqueue(stack, pox);

    pox.x = 0;
    pox.y = 0;
    pox = stack->top(stack);
    toStringPoint(&pox);

    printf("\n");

    stack->show(stack);
    stack->resize(stack, 10);

    while (stack->getSize(stack) != 0)
    {
        Point_t p = stack->top(stack);
        printf("top = {%d,%d} ,size = %d ,realzise = %d\n", p.x, p.y, stack->getSize(stack), stack->realSize);
        stack->pop(stack);
    }

    SQ_deleteSQ_Classt(stack);
#endif
}

SQ_Classt *SQ_newSQ_Classt(void)
{
    SQ_Classt *ret = NULL;
    ret = (SQ_Classt *)malloc(sizeof(SQ_Classt));
    if (ret == NULL)
        return NULL;
    memset(ret, 0, sizeof(SQ_Classt));
    ret->data = NULL;
    ret->button_index = 0;
    ret->realSize = 0;
    ret->top_index = 0;
    ret->getSize = SQ_getSizeSQ_Classt;
    ret->resize = SQ_resizeSQ_Classt;
    ret->top = SQ_topSQ_Classt;
    ret->button = SQ_buttonSQ_Classt;
    ret->pop = SQ_popSQ_Classt;
    ret->push = SQ_pushSQ_Classt;
    ret->enqueue = SQ_enqueueSQ_Classt;
    ret->dequeue = SQ_dequeueSQ_Classt;
    ret->show = SQ_showSQ_Classt;
    ret->clean = SQ_cleanSQ_Classt;
    ret->toString = NULL;
    ret->deleteSub = NULL;
    return ret;
}

void SQ_deleteSQ_Classt(SQ_Classt *t)
{
    if (t == NULL)
        return;
    if ((t->top_index != t->button_index) && t->deleteSub != NULL)
    {
        for (u32 i = t->button_index; i < t->top_index; i++)
        {
            t->deleteSub(t->data + i);
        }
    }
    free(t->data);
    free(t);
}
u32 SQ_getSizeSQ_Classt(const SQ_Classt *t)
{
    if (t == NULL)
        return -1u;
    else
        return (t->top_index) - (t->button_index);
}
u8 SQ_resizeSQ_Classt(SQ_Classt *t, u32 newsize)
{
    if (t == NULL || ((t->top_index) - (t->button_index)) >= newsize)
        return FALSE;
    Classt *tempdata = malloc(sizeof(Classt) * newsize);
    if (tempdata == NULL)
        return FALSE;
    if (t->top_index > t->button_index)
    {
        if (t->top_index > t->realSize)
        {
            memcpy(tempdata, t->data + t->button_index, sizeof(Classt) * ((t->realSize) - (t->button_index)));
            memcpy(tempdata + (t->realSize) - (t->button_index), t->data, t->top_index % t->realSize);
        }
        else
        {
            memcpy(tempdata, t->data + (t->button_index), sizeof(Classt) * ((t->top_index) - (t->button_index)));
        }
        t->top_index -= t->button_index;
        t->button_index = 0;
    }
    memset(tempdata + t->top_index, 0, (newsize - t->top_index) * sizeof(Classt));
    if (t->data != NULL)
        free(t->data);
    t->data = tempdata;
    t->realSize = newsize;
    return TRUE;
}

Classt SQ_topSQ_Classt(const struct __SQ_Classt *t)
{
    if (t == NULL || t->button_index == t->top_index)
        return t->data[0];
    else
        return t->data[(t->top_index - 1) % t->realSize];
}
Classt SQ_buttonSQ_Classt(const struct __SQ_Classt *t)
{
    if (t == NULL || t->button_index == t->top_index)
        return t->data[0];
    else
        return t->data[t->button_index];
}
u8 SQ_popSQ_Classt(struct __SQ_Classt *t)
{
    if (t == NULL || t->button_index >= t->top_index)
        return FALSE;
    if (t->deleteSub != NULL)
        t->deleteSub(&t->data[(t->top_index - 1) % t->realSize]);
    t->top_index--;
    return TRUE;
}
u8 SQ_pushSQ_Classt(struct __SQ_Classt *t, const Classt e)
{
    return t->enqueue(t, e);
}
u8 SQ_enqueueSQ_Classt(struct __SQ_Classt *t, const Classt e)
{
    if (t == NULL)
        return FALSE;
    if ((t->top_index - t->button_index) >= t->realSize)
        if (t->resize(t, (t->realSize) * 3 / 2 + 2) == FALSE)
            return FALSE;
    t->data[t->top_index % t->realSize] = e;
    t->top_index++;
    return TRUE;
}
u8 SQ_dequeueSQ_Classt(struct __SQ_Classt *t)
{
    if (t == NULL || t->top_index <= t->button_index)
        return FALSE;
    if (t->deleteSub != NULL)
        t->deleteSub(&t->data[t->button_index]);
    t->button_index++;
    t->button_index %= (t->realSize);
    return TRUE;
}
void SQ_showSQ_Classt(struct __SQ_Classt *t)
{
    if (t == NULL)
        return;
    VPRINTF("this stackQue: size = %u , realsize = %u\n", t->top_index - t->button_index, t->realSize);
    if (t->toString != NULL)
        for (u32 i = t->button_index; i < t->top_index; i++)
        {
            VPRINTF("stackQue[%d] = \n\t", i - t->button_index);
            t->toString(&t->data[i % t->realSize]);
            VPRINTF("\n");
        }
}
void SQ_cleanSQ_Classt(struct __SQ_Classt *t)
{
    if (t == NULL || t->top_index <= t->button_index)
        return;
    if (t->deleteSub != NULL)
        for (u32 i = t->button_index; i < t->top_index; i++)
            t->deleteSub(&t->data[i % t->realSize]);
    memset(t->data, 0, sizeof(Classt) * t->realSize);
    t->top_index = t->button_index = 0;
}
