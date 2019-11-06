#ifndef C_STACK_QUEUE_H
#define C_STACK_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------自定义类型区------------------//
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
    u8 (*push)(struct __SQ_Classt *t, const Classt *e);
    u8 (*enqueue)(struct __SQ_Classt *t, const Classt *e);
    u8 (*dequeue)(struct __SQ_Classt *t);
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
u8 SQ_pushSQ_Classt(struct __SQ_Classt *t, const Classt *e);
u8 SQ_enqueueSQ_Classt(struct __SQ_Classt *t, const Classt *e);
u8 SQ_dequeueSQ_Classt(struct __SQ_Classt *t);
void SQ_cleanSQ_Classt(struct __SQ_Classt *t);
void SQ_showSQ_Classt(struct __SQ_Classt *t);

#endif
