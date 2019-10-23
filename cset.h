#ifndef CSET_H
#define CSET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------宏定义配置区-----------------------//
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

//-----------------------------函数实现区------------------------------//

/*本set底层数据结构使用 AVL Tree实现,现在处处于开发阶段,首先使用普通代码实现,而后才会使用真正的膨胀代码;*/
typedef unsigned int typeClass;

typedef struct __SET_typeClass_node
{
    typeClass data;
    struct __SET_typeClass_node *left;
    struct __SET_typeClass_node *right;
    u8 heigh;
} SET_typeClass_node_t;

typedef struct __SET_typeClass_t
{
    SET_typeClass_node_t *root;
    u32 size;
} SET_typeClass_t;

SET_typeClass_t *SET_newtypeClass_t(void);
void SET_deletetypeClass_t(SET_typeClass_t *set);
void SET_inserttypeClass_t(SET_typeClass_t *set, const typeClass *ele);
void SET_removetypeClass_t(SET_typeClass_t *set, const typeClass *ele);
u32 SET_getSizetypeClass_t(SET_typeClass_t *set);
const typeClass *SET_toDatatypeClass_t(SET_typeClass_t *set, u32 *lengh);
const SET_typeClass_node_t *SET_nexttypeClass_t(const SET_typeClass_node_t *item);

void SET_deletetypeClass_node_t(void (*freesub)(const typeClass *d), SET_typeClass_node_t *node);
u32 SET_toDatatypeClass_node_t(SET_typeClass_node_t *node, typeClass *array);

#endif // _cset.h
