#ifndef C_STACK_QUEUE_H
#define C_STACK_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------自定义类型区------------------//
#ifndef PRINTF_ENABLE
#define PRINTF_ENABLE 1
#endif

#if PRINTF_ENABLE == 1
#define VPRINTF(ftm, ...) printf(ftm, ##__VA_ARGS__)
#else
#define VPRINTF(ftm, ...)
#endif
#if 1

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long long u64;

#endif //当#if 0 时自定义类型区关闭

#ifndef FALSE
#define FALSE 0u
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#ifndef _INC_STDLIB

extern void *memcpy(void *des, void *src, u64 size);
extern void *malloc(u64 size);
extern void free(void *p);
extern int rand(void);

#endif //如果没有include stdlib.h 文件 那么需要实现以上几个函数

#ifndef _INC_STRING

void *memset(void *des, int v, u64 size);

#endif //如果没有include string.h 文件 那么需要实现以上几个函数

//----------------------------膨胀宏定义区域-----------------------------------//

#define _SQ_TYPEDEF(T, TName)                                               \
    typedef struct __SQ_##TName                                             \
    {                                                                       \
        T *data;                                                            \
        u32 (*getSize)(const struct __SQ_##TName *t);                       \
        T(*top)                                                             \
        (const struct __SQ_##TName *t);                                     \
        T(*button)                                                          \
        (const struct __SQ_##TName *t);                                     \
        u8 (*pop)(struct __SQ_##TName * t);                                 \
        u8 (*push)(struct __SQ_##TName * t, const T e);                     \
        u8 (*enqueue)(struct __SQ_##TName * t, const T e);                  \
        u8 (*dequeue)(struct __SQ_##TName * t);                             \
        u8 (*enqueueArray)(struct __SQ_##TName * t, const T *e, u32 lengh); \
        u8 (*pushArray)(struct __SQ_##TName * t, const T *e, u32 lengh);    \
        u8 (*resize)(struct __SQ_##TName * t, u32 newsize);                 \
        void (*clean)(struct __SQ_##TName * t);                             \
        void (*show)(struct __SQ_##TName * t);                              \
        void (*toString)(const T *e);                                       \
        void (*deleteSub)(T * e);                                           \
        u32 realSize;                                                       \
        u32 top_index;                                                      \
        u32 button_index;                                                   \
    } SQ_##TName;

#define _SQ_NEW(T, TName, ToString, DeleteSub)          \
    SQ_##TName *SQ_newSQ_##TName(void)                  \
    {                                                   \
        SQ_##TName *ret = NULL;                         \
        ret = (SQ_##TName *)malloc(sizeof(SQ_##TName)); \
        if (ret == NULL)                                \
            return NULL;                                \
        memset(ret, 0, sizeof(SQ_##TName));             \
        ret->data = NULL;                               \
        ret->button_index = 0;                          \
        ret->realSize = 0;                              \
        ret->top_index = 0;                             \
        ret->getSize = _SQ_getSizeSQ_##TName;           \
        ret->resize = _SQ_resizeSQ_##TName;             \
        ret->top = _SQ_topSQ_##TName;                   \
        ret->button = _SQ_buttonSQ_##TName;             \
        ret->pop = _SQ_popSQ_##TName;                   \
        ret->push = _SQ_pushSQ_##TName;                 \
        ret->enqueue = _SQ_enqueueSQ_##TName;           \
        ret->pushArray = _SQ_pushArraySQ_##TName;       \
        ret->enqueueArray = _SQ_enqueueArraySQ_##TName; \
        ret->dequeue = _SQ_dequeueSQ_##TName;           \
        ret->show = _SQ_showSQ_##TName;                 \
        ret->clean = _SQ_cleanSQ_##TName;               \
        ret->toString = ToString;                       \
        ret->deleteSub = DeleteSub;                     \
        return ret;                                     \
    }

#define _SQ_DELETE(T, TName)                                           \
    void SQ_deleteSQ_##TName(SQ_##TName *t)                            \
    {                                                                  \
        if (t == NULL)                                                 \
            return;                                                    \
        if ((t->top_index != t->button_index) && t->deleteSub != NULL) \
        {                                                              \
            for (u32 i = t->button_index; i < t->top_index; i++)       \
            {                                                          \
                t->deleteSub(t->data + i);                             \
            }                                                          \
        }                                                              \
        free(t->data);                                                 \
        free(t);                                                       \
    }

#define _SQ_GETSIZE(T, TName)                             \
    static u32 _SQ_getSizeSQ_##TName(const SQ_##TName *t) \
    {                                                     \
        if (t == NULL)                                    \
            return -1u;                                   \
        else                                              \
            return (t->top_index) - (t->button_index);    \
    }

#define _SQ_RESIZE(T, TName)                                                                                             \
    static u8 _SQ_resizeSQ_##TName(SQ_##TName *t, u32 newsize)                                                           \
    {                                                                                                                    \
        if (t == NULL || ((t->top_index) - (t->button_index)) >= newsize)                                                \
            return FALSE;                                                                                                \
        T *tempdata = malloc(sizeof(T) * newsize);                                                                       \
        if (tempdata == NULL)                                                                                            \
            return FALSE;                                                                                                \
        if (t->top_index > t->button_index)                                                                              \
        {                                                                                                                \
            if (t->top_index > t->realSize)                                                                              \
            {                                                                                                            \
                memcpy(tempdata, t->data + t->button_index, sizeof(T) * ((t->realSize) - (t->button_index)));            \
                memcpy(tempdata + (t->realSize) - (t->button_index), t->data, sizeof(T) * (t->top_index % t->realSize)); \
            }                                                                                                            \
            else                                                                                                         \
            {                                                                                                            \
                memcpy(tempdata, t->data + (t->button_index), sizeof(T) * ((t->top_index) - (t->button_index)));         \
            }                                                                                                            \
            t->top_index -= t->button_index;                                                                             \
            t->button_index = 0;                                                                                         \
        }                                                                                                                \
        memset(tempdata + t->top_index, 0, (newsize - t->top_index) * sizeof(T));                                        \
        free(t->data);                                                                                                   \
        t->data = tempdata;                                                                                              \
        t->realSize = newsize;                                                                                           \
        return TRUE;                                                                                                     \
    }

#define _SQ_TOP(T, TName)                                     \
    static T _SQ_topSQ_##TName(const struct __SQ_##TName *t)  \
    {                                                         \
        if (t == NULL || t->button_index == t->top_index)     \
            return t->data[0];                                \
        else                                                  \
            return t->data[(t->top_index - 1) % t->realSize]; \
    }

#define _SQ_BUTTON(T, TName)                                    \
    static T _SQ_buttonSQ_##TName(const struct __SQ_##TName *t) \
    {                                                           \
        if (t == NULL || t->button_index == t->top_index)       \
            return t->data[0];                                  \
        else                                                    \
            return t->data[t->button_index];                    \
    }

#define _SQ_POP(T, TName)                                             \
    static u8 _SQ_popSQ_##TName(struct __SQ_##TName *t)               \
    {                                                                 \
        if (t == NULL || t->button_index >= t->top_index)             \
            return FALSE;                                             \
        if (t->deleteSub != NULL)                                     \
            t->deleteSub(&t->data[(t->top_index - 1) % t->realSize]); \
        t->top_index--;                                               \
        return TRUE;                                                  \
    }

#define _SQ_PUSH(T, TName)                                          \
    static u8 _SQ_pushSQ_##TName(struct __SQ_##TName *t, const T e) \
    {                                                               \
        return t->enqueue(t, e);                                    \
    }

#define _SQ_ENQUEUE(T, TName)                                          \
    static u8 _SQ_enqueueSQ_##TName(struct __SQ_##TName *t, const T e) \
    {                                                                  \
        if (t == NULL)                                                 \
            return FALSE;                                              \
        if ((t->top_index - t->button_index) >= t->realSize)           \
            if (t->resize(t, (t->realSize) * 3 / 2 + 2) == FALSE)      \
                return FALSE;                                          \
        t->data[t->top_index % t->realSize] = e;                       \
        t->top_index++;                                                \
        return TRUE;                                                   \
    }

#define _SQ_DEQUEUE(T, TName)                               \
    static u8 _SQ_dequeueSQ_##TName(struct __SQ_##TName *t) \
    {                                                       \
        if (t == NULL || t->top_index <= t->button_index)   \
            return FALSE;                                   \
        if (t->deleteSub != NULL)                           \
            t->deleteSub(&t->data[t->button_index]);        \
        t->button_index++;                                  \
        t->button_index %= (t->realSize);                   \
        return TRUE;                                        \
    }

#define _SQ_SHOW(T, TName)                                                                                  \
    static void _SQ_showSQ_##TName(struct __SQ_##TName *t)                                                  \
    {                                                                                                       \
        if (t == NULL)                                                                                      \
            return;                                                                                         \
        VPRINTF("this stackQue: size = %u , realsize = %u\n", t->top_index - t->button_index, t->realSize); \
        if (t->toString != NULL)                                                                            \
            for (u32 i = t->button_index; i < t->top_index; i++)                                            \
            {                                                                                               \
                VPRINTF("stackQue[%d] = \n\t", i - t->button_index);                                        \
                t->toString(&t->data[i % t->realSize]);                                                     \
                VPRINTF("\n");                                                                              \
            }                                                                                               \
    }

#define _SQ_CLEAN(T, TName)                                      \
    static void _SQ_cleanSQ_##TName(struct __SQ_##TName *t)      \
    {                                                            \
        if (t == NULL || t->top_index <= t->button_index)        \
            return;                                              \
        if (t->deleteSub != NULL)                                \
            for (u32 i = t->button_index; i < t->top_index; i++) \
                t->deleteSub(&t->data[i % t->realSize]);         \
        memset(t->data, 0, sizeof(T) * t->realSize);             \
        t->top_index = t->button_index = 0;                      \
    }

#define _SQ_ENQUEUEARRAY(T, TName)                                                      \
    static u8 _SQ_enqueueArraySQ_##TName(struct __SQ_##TName *t, const T *e, u32 lengh) \
    {                                                                                   \
        if (t == NULL)                                                                  \
            return FALSE;                                                               \
        if ((t->top_index - t->button_index + lengh) >= t->realSize)                    \
            if (t->resize(t, (t->realSize) * 3 / 2 + lengh) == FALSE)                   \
                return FALSE;                                                           \
        for (u32 i = 0; i < lengh; i++)                                                 \
        {                                                                               \
            t->data[t->top_index % t->realSize] = e[i];                                \
            t->top_index++;                                                             \
        }                                                                               \
        return TRUE;                                                                    \
    }

#define _SQ_PUSHARRAY(T, TName)                                                      \
    static u8 _SQ_pushArraySQ_##TName(struct __SQ_##TName *t, const T *e, u32 lengh) \
    {                                                                                \
        return _SQ_enqueueArraySQ_##TName(t, e, lengh);                              \
    }

#define SQ_Define(T, TName)                    \
    _SQ_TYPEDEF(T, TName)                      \
    extern SQ_##TName *SQ_newSQ_##TName(void); \
    extern void SQ_deleteSQ_##TName(SQ_##TName *t)

#define SQ_Declare(T, TName, ToString, DeleteSub) \
    _SQ_GETSIZE(T, TName)                         \
    _SQ_RESIZE(T, TName)                          \
    _SQ_TOP(T, TName)                             \
    _SQ_BUTTON(T, TName)                          \
    _SQ_PUSH(T, TName)                            \
    _SQ_POP(T, TName)                             \
    _SQ_ENQUEUE(T, TName)                         \
    _SQ_DEQUEUE(T, TName)                         \
    _SQ_SHOW(T, TName)                            \
    _SQ_CLEAN(T, TName)                           \
    _SQ_DELETE(T, TName)                          \
    _SQ_ENQUEUEARRAY(T, TName)                    \
    _SQ_PUSHARRAY(T, TName)                       \
    _SQ_NEW(T, TName, ToString, DeleteSub)        \
    static u8 _SQ_pushArraySQ_##TName(struct __SQ_##TName *t, const T *e, u32 lengh)

//----------------------------测试函数声明区域----------------------------------//
typedef struct
{
    unsigned short x;
    unsigned short y;
} Point_t;

typedef Point_t Classt;

typedef struct __SQ_Classt
{
    u32 realSize;
    u32 top_index;
    u32 button_index;
    Classt *data;
    u32 (*getSize)(const struct __SQ_Classt *t);
    Classt (*top)(const struct __SQ_Classt *t);
    Classt (*button)(const struct __SQ_Classt *t);
    u8 (*pop)(struct __SQ_Classt *t);
    u8 (*push)(struct __SQ_Classt *t, const Classt e);
    u8 (*enqueue)(struct __SQ_Classt *t, const Classt e);
    u8 (*enqueueArray)(struct __SQ_Classt *t, const Classt *e, u32 lengh);
    u8 (*pushArray)(struct __SQ_Classt *t, const Classt *e, u32 lengh);
    u8 (*dequeue)(struct __SQ_Classt *t);
    u8 (*resize)(struct __SQ_Classt *t, u32 newsize);
    void (*clean)(struct __SQ_Classt *t);
    void (*show)(struct __SQ_Classt *t);
    void (*toString)(const Classt *e);
    void (*deleteSub)(Classt *e);
} SQ_Classt;

SQ_Classt *SQ_newSQ_Classt(void);
void SQ_deleteSQ_Classt(SQ_Classt *t);
u32 SQ_getSizeSQ_Classt(const SQ_Classt *t);
u8 SQ_resizeSQ_Classt(SQ_Classt *t, u32 newsize);
Classt SQ_topSQ_Classt(const struct __SQ_Classt *t);
Classt SQ_buttonSQ_Classt(const struct __SQ_Classt *t);
u8 SQ_popSQ_Classt(struct __SQ_Classt *t);
u8 SQ_pushSQ_Classt(struct __SQ_Classt *t, const Classt e);
u8 SQ_enqueueSQ_Classt(struct __SQ_Classt *t, const Classt e);
u8 SQ_dequeueSQ_Classt(struct __SQ_Classt *t);
void SQ_cleanSQ_Classt(struct __SQ_Classt *t);
void SQ_showSQ_Classt(struct __SQ_Classt *t);
u8 SQ_pushArraySQ_Classt(struct __SQ_Classt *t, Classt *array, u32 lengh);

#endif
