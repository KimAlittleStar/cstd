#include "cstackqueue.h"

void cstackqueue_test(void)
{
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
    if (t != NULL && (t->top_index != t->button_index) && t->deleteSub != NULL)
    {
        for (u32 i = t->button_index; i < t->top_index; i++)
        {
            t->deleteSub(t->data + i);
        }
    }
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
        ///< @bug 当在queue中出现top指针在 button指针后面的时候,将会出现bug;
        memcpy(tempdata, t->data + (t->button_index), sizeof(Classt) * ((t->top_index) - (t->button_index)));
        t->top_index -= t->button_index;
        t->button_index = 0;
    }
    memset(tempdata + t->top_index, 0, (newsize - t->top_index) * sizeof(Classt));
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
    t->data[t->top_index] = e;
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
