/**
 **********************************************************************
 * @file cset.h
 * @brief include 本头文件后，将可以使用 S_Define S_Declare_Set 实现代码
 * 膨胀，实现标准容器set
 * @verbatim
 * >Introduce: 本文件的SET 数据容器底层实现使用 AVL 二叉树实现，平均时间复杂度为
 * O(nLogn);
 * >Depend On: 本文件的测试 依靠于 cset.c 所有宏定义的函数都可在cset.c中拥有映射函数
 * 如果你想正常使用此数据容器,那么你至少需要实现 compare 库函数;
 * >Include: 默认include stdlib.h string.h stdio.h 
 * @endverbatim
 * @author  kimalittlestar@gmail.com
 * @date 2019-10-24
 * @version V0.0
 * @note CopyRight By XXXX Co. Ltd All right reserve
 **********************************************************************
*/
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

#define SET_Max(a, b) (u8)((a > b) ? (a) : (b))

//代码膨胀代码实现区
/**
 ***********************************************************************
 * @brief 定义 类型的模板类,T真正的类型,TName为你自定义的类型名字;而后Set的类型
 * 为SET_TName;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_TYPEDEF(T, TName)                                          \
    /*! @brief define the tree node*/                                \
    typedef struct __SET_##TName##_node                              \
    {                                                                \
        struct __SET_##TName##_node *left;                           \
        struct __SET_##TName##_node *right;                          \
        T data;                                                      \
        u8 heigh;                                                    \
    } SET_##TName##_node_t;                                          \
    /*! @brief define the Set struct*/                               \
    typedef struct __SET_##TName##_t                                 \
    {                                                                \
        SET_##TName##_node_t *root;                                  \
        void (*deleteSub)(const T *ele);                             \
        u8 (*compare)(const T *a, const T *b);                       \
        void (*toString)(const T *a);                                \
        u8 (*insert)(struct __SET_##TName##_t * set, const T ele);   \
        u8 (*remove)(struct __SET_##TName##_t * set, const T ele);   \
        u32 (*getSize)(struct __SET_##TName##_t * set);              \
        T *(*toData)(struct __SET_##TName##_t * set, u32 *lengh);    \
        T **(*itemData)(struct __SET_##TName##_t * set, u32 *lengh); \
        void (*show)(struct __SET_##TName##_t * set);                \
        T *(*find)(struct __SET_##TName##_t * set, const T *v);      \
        T *(*findMax)(struct __SET_##TName##_t * set);               \
        T *(*findMin)(struct __SET_##TName##_t * set);               \
        void (*clear)(struct __SET_##TName##_t * set);               \
        T(*removeMax)                                                \
        (struct __SET_##TName##_t * set);                            \
        T(*removeMin)                                                \
        (struct __SET_##TName##_t * set);                            \
        u32 size;                                                    \
    } SET_##TName;

/**
 ***********************************************************************
 * @brief 定义实现一个 new函数,其中 将会给结构体中的指针附上初始值,
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_NEW(T, TName, Compare, ToString, DeleteSub)                  \
    /*! @brief new a SET_##TName and get the*/                         \
    /*! @brief defaule function pointc*/                               \
    SET_##TName *SET_newSET_##TName(void)                              \
    {                                                                  \
        SET_##TName *ret = (SET_##TName *)malloc(sizeof(SET_##TName)); \
        if (ret != NULL)                                               \
        {                                                              \
            ret->size = 0;                                             \
            ret->root = NULL;                                          \
            ret->deleteSub = DeleteSub;                                \
            ret->compare = Compare;                                    \
            ret->toString = ToString;                                  \
            ret->insert = __SET_insertSET_##TName;                     \
            ret->remove = __SET_removeSET_##TName;                     \
            ret->getSize = __SET_getSizeSET_##TName;                   \
            ret->toData = __SET_toDataSET_##TName;                     \
            ret->itemData = __SET_itemDataSET_##TName;                 \
            ret->show = __SET_showSET_##TName;                         \
            ret->find = __SET_findSET_##TName;                         \
            ret->findMax = __SET_findMaxSET_##TName;                   \
            ret->findMin = __SET_findMinSET_##TName;                   \
            ret->removeMax = __SET_removeMaxSET_##TName;               \
            ret->removeMin = __SET_removeMinSET_##TName;               \
            ret->clear = __SET_clearSET_##TName;                       \
        }                                                              \
        return ret;                                                    \
    }

/**
 ***********************************************************************
 * @brief 删除,定义实现一个删除函数,遍历释放空间之前,会首先尝试删除自身子元素
 * 所指向的空间元素
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_DELETE(T, TName)                                                                                                \
    /*! @brief  这是一个递归调用的函数 将  SET_##TName##_node_t 下所有的 node;*/                          \
    /*! @brief 先释放data而后释放自己的内存空间;*/                                                          \
    void __SET_deleteSET_##TName##_node_t(void (*freesub)(const T *d), SET_##TName##_node_t *node)                        \
    {                                                                                                                     \
        if (node == NULL)                                                                                                 \
            return;                                                                                                       \
        __SET_deleteSET_##TName##_node_t(freesub, node->left);                                                            \
        if (freesub != NULL)                                                                                              \
            freesub(&(node->data));                                                                                       \
        __SET_deleteSET_##TName##_node_t(freesub, node->right);                                                           \
        free(node);                                                                                                       \
    }                                                                                                                     \
                                                                                                                          \
    /*! @brief 此函数是会声明在外部的delete函数,调用上述  @see __SET_deleteSET_##TName##_node_t 函数*/ \
    void SET_deleteSET_##TName(SET_##TName *set)                                                                          \
    {                                                                                                                     \
        if (set != NULL)                                                                                                  \
            return;                                                                                                       \
        __SET_deleteSET_##TName##_node_t(set->deleteSub, set->root);                                                      \
        free(set);                                                                                                        \
    }

/**
 ***********************************************************************
 * @brief 实现插入函数 由于平衡二叉树的性质,所以我们需要在insert/remove中
 * 维护树的平衡,因此在inser 宏中定义 单旋转 双旋转等;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_INSERT(T, TName)                                                                                                                   \
    /*! @brief 此函数是判断返回当前节点的高度(heigh) */                                                                       \
    inline u8 __SET_heightSET_##TName(SET_##TName##_node_t *s)                                                                               \
    {                                                                                                                                        \
        return (s == NULL) ? (0) : (s->heigh);                                                                                               \
    }                                                                                                                                        \
    /*! @brief 单旋转,将s->left作为新的根返回 只有在左节点高度大于有节点时使用 */                                 \
    SET_##TName##_node_t *__SET_singleRotateLeftSET_##TName(SET_##TName##_node_t *s)                                                         \
    {                                                                                                                                        \
        SET_##TName##_node_t *s1;                                                                                                            \
        s1 = s->left;                                                                                                                        \
        s->left = s1->right;                                                                                                                 \
        s1->right = s;                                                                                                                       \
                                                                                                                                             \
        s->heigh = SET_Max(                                                                                                                  \
                       __SET_heightSET_##TName(s->left),                                                                                     \
                       __SET_heightSET_##TName(s->right)) +                                                                                  \
                   1;                                                                                                                        \
        s1->heigh = SET_Max(                                                                                                                 \
                        __SET_heightSET_##TName(s1->left),                                                                                   \
                        s->heigh) +                                                                                                          \
                    1;                                                                                                                       \
        return s1;                                                                                                                           \
    }                                                                                                                                        \
    /*! @brief 单旋转,将s->right作为新的根返回 @see  __SET_singleRotateLeftSET_##TName*/                                          \
    SET_##TName##_node_t *__SET_singleRotateRightSET_##TName(SET_##TName##_node_t *s)                                                        \
    {                                                                                                                                        \
        SET_##TName##_node_t *s1;                                                                                                            \
        s1 = s->right;                                                                                                                       \
        s->right = s1->left;                                                                                                                 \
        s1->left = s;                                                                                                                        \
                                                                                                                                             \
        s->heigh = SET_Max(                                                                                                                  \
                       __SET_heightSET_##TName(s->left),                                                                                     \
                       __SET_heightSET_##TName(s->right)) +                                                                                  \
                   1;                                                                                                                        \
        s1->heigh = SET_Max(                                                                                                                 \
                        __SET_heightSET_##TName(s1->right),                                                                                  \
                        s->heigh) +                                                                                                          \
                    1;                                                                                                                       \
        return s1;                                                                                                                           \
    }                                                                                                                                        \
    /*! @brief 双旋转,由两侧单旋转组成;将s->left做为新的根 */                                                               \
    SET_##TName##_node_t *__SET_doubleRotateLeftSET_##TName(SET_##TName##_node_t *s)                                                         \
    {                                                                                                                                        \
        s->left = __SET_singleRotateRightSET_##TName(s->left);                                                                               \
        return __SET_singleRotateLeftSET_##TName(s);                                                                                         \
    }                                                                                                                                        \
    /*! @brief 双旋转,参考 @see __SET_doubleRotateLeftSET_##TName */                                                                    \
    SET_##TName##_node_t *__SET_doubleRotateRightSET_##TName(SET_##TName##_node_t *s)                                                        \
    {                                                                                                                                        \
        s->right = __SET_singleRotateLeftSET_##TName(s->right);                                                                              \
        return __SET_singleRotateRightSET_##TName(s);                                                                                        \
    }                                                                                                                                        \
    /*! @brief 以上函数都是为了insert函数能够正常的运行;在insert/remove时需要维护树的平衡                */       \
    /*! @brief 此函数是一个递归调用函数,基础情况为 当前root为空,那么将再此节点插入新的node                */ \
    /*! @param SET_##TName##_node_t *root 期望将 value 的值插入此树中                                 */                           \
    /*! @param u8 (*)(const T *a, const T *b) 函数指针,提供一个比较两个 T 元素的方法;                  */                   \
    /*! @param const T *value 需要插入的值,如果这个值已经存在于该 root中,那么将不会操作                 */          \
    /*! @param u32 *size 用于传递 管理 整个set 的大小,当 发生真实插入时将会自加;                        */            \
    /*! @return  SET_##TName##_node_t 将会返回一个此树的root,请使用原来的传参的参数进行迭代             */           \
    /*! @author kimalittlestar@ gmail.com                                                           */                                       \
    /*! @date __DATE__ */                                                                                                                    \
    SET_##TName##_node_t *__SET_insertSET_##TName##_node_t(SET_##TName##_node_t *root,                                                       \
                                                           u8 (*compare)(const T *a, const T *b),                                            \
                                                           const T *value, u32 *size)                                                        \
    {                                                                                                                                        \
        if (root == NULL)                                                                                                                    \
        {                                                                                                                                    \
            root = (SET_##TName##_node_t *)malloc(sizeof(SET_##TName##_node_t));                                                             \
            if (root == NULL)                                                                                                                \
            { /* out of space */                                                                                                             \
            }                                                                                                                                \
            else                                                                                                                             \
            {                                                                                                                                \
                root->data = (*value);                                                                                                       \
                root->left = root->right = NULL;                                                                                             \
                root->heigh = 1;                                                                                                             \
                (*size)++;                                                                                                                   \
            }                                                                                                                                \
            return root;                                                                                                                     \
        }                                                                                                                                    \
        else if (compare(value, &root->data))                                                                                                \
        {                                                                                                                                    \
            root->left = __SET_insertSET_##TName##_node_t(root->left, compare, value, size);                                                 \
            if (__SET_heightSET_##TName(root->left) - __SET_heightSET_##TName(root->right) == 2)                                             \
            {                                                                                                                                \
                if (compare(value, &root->left->data))                                                                                       \
                    root = __SET_singleRotateLeftSET_##TName(root);                                                                          \
                else                                                                                                                         \
                    root = __SET_doubleRotateLeftSET_##TName(root);                                                                          \
            }                                                                                                                                \
        }                                                                                                                                    \
        else if (compare(&root->data, value))                                                                                                \
        {                                                                                                                                    \
            root->right = __SET_insertSET_##TName##_node_t(root->right, compare, value, size);                                               \
            if (__SET_heightSET_##TName(root->right) - __SET_heightSET_##TName(root->left) == 2)                                             \
            {                                                                                                                                \
                if (compare(&root->right->data, value))                                                                                      \
                    root = __SET_singleRotateRightSET_##TName(root);                                                                         \
                else                                                                                                                         \
                    root = __SET_doubleRotateRightSET_##TName(root);                                                                         \
            }                                                                                                                                \
        }                                                                                                                                    \
        root->heigh = SET_Max(__SET_heightSET_##TName(root->left),                                                                           \
                              __SET_heightSET_##TName(root->right)) +                                                                        \
                      1;                                                                                                                     \
        return root;                                                                                                                         \
    }                                                                                                                                        \
    u8 __SET_insertSET_##TName(SET_##TName *set, const T ele)                                                                                \
    {                                                                                                                                        \
        if (set == NULL || set->compare == NULL)                                                                                             \
            return 0;                                                                                                                        \
        u32 cursize = set->size;                                                                                                             \
        set->root = __SET_insertSET_##TName##_node_t(set->root, set->compare, &ele, &set->size);                                             \
        return (cursize < set->size);                                                                                                        \
    }
/**
 ***********************************************************************
 * @brief 实现声明remove 相关功能的宏定义,需要注意的是在删除有两个孩子的节点时
 * 并不是释放该节点空间,而是将此节点下最小的元素赋值进入此节点,然后删除那个最
 * 小节点;同时维护树的平衡与插入刚好相反;删除了左边的,那么左边就要比右边要小,
 * 因此需要右旋;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_REMOVE(T, TName)                                                                                                                               \
    /*! @brief 主要功能的remove函数,将会递归调用,其中一定要求 compare 函数指针可用,在函数中 */                              \
    /*! @param SET_##TName##_node_t *root 功能与 insert 相同 @see __SET_insertSET_##TName##_node_t */                                               \
    /*! @param u8 (*compare)(const T *a, const T *b) 比较函数指针 @see __SET_insertSET_##TName##_node_t*/                                          \
    /*! @param void (*deleteSub)(const T *ele)  与insert函数不同,这里需要提供一个deletesub 函数释放子元素中可能引用的指针 */ \
    /*! @param const T *value 需要remove的值,如果这个值不存在于该 root中,那么将不会操作                 */                         \
    /*! @param u32 *size 用于传递 管理 整个set 的大小,当 发生真实删除时将会自减;                        */                        \
    /*! @return  SET_##TName##_node_t 将会返回一个此树的root,请使用原来的传参的参数进行迭代             */                       \
    /*! @author kimalittlestar@ gmail.com                                                           */                                                   \
    SET_##TName##_node_t *__SET_removeSET_##TName##_node_t(SET_##TName##_node_t *root,                                                                   \
                                                           u8 (*compare)(const T *a, const T *b),                                                        \
                                                           void (*deleteSub)(const T *ele),                                                              \
                                                           const T *value, u32 *size)                                                                    \
    {                                                                                                                                                    \
        if (root == NULL)                                                                                                                                \
        { /*! no this value; */                                                                                                                          \
        }                                                                                                                                                \
        else if (compare(value, &root->data))                                                                                                            \
        {                                                                                                                                                \
            root->left = __SET_removeSET_##TName##_node_t(root->left, compare, deleteSub, value, size);                                                  \
            if (__SET_heightSET_##TName(root->right) - __SET_heightSET_##TName(root->left) == 2)                                                         \
            {                                                                                                                                            \
                if (__SET_heightSET_##TName(root->right->right) > __SET_heightSET_##TName(root->right->left))                                            \
                    root = __SET_singleRotateRightSET_##TName(root);                                                                                     \
                else                                                                                                                                     \
                    root = __SET_doubleRotateRightSET_##TName(root);                                                                                     \
            }                                                                                                                                            \
        }                                                                                                                                                \
        else if (compare(&root->data, value))                                                                                                            \
        {                                                                                                                                                \
            root->right = __SET_removeSET_##TName##_node_t(root->right, compare, deleteSub, value, size);                                                \
            if (__SET_heightSET_##TName(root->left) - __SET_heightSET_##TName(root->right) == 2)                                                         \
            {                                                                                                                                            \
                if (__SET_heightSET_##TName(root->left->left) > __SET_heightSET_##TName(root->left->right))                                              \
                    root = __SET_singleRotateLeftSET_##TName(root);                                                                                      \
                else                                                                                                                                     \
                    root = __SET_doubleRotateLeftSET_##TName(root);                                                                                      \
            }                                                                                                                                            \
        }                                                                                                                                                \
        else                                                                                                                                             \
        {                                                                                                                                                \
            /*real delete option*/                                                                                                                       \
            if (root->right != NULL && root->left != NULL)                                                                                               \
            {                                                                                                                                            \
                /* has two child */                                                                                                                      \
                SET_##TName##_node_t *temp = root;                                                                                                       \
                while (temp->left != NULL)                                                                                                               \
                {                                                                                                                                        \
                    temp = temp->left;                                                                                                                   \
                }                                                                                                                                        \
                if (deleteSub != NULL)                                                                                                                   \
                    deleteSub(&root->data);                                                                                                              \
                root->data = temp->data;                                                                                                                 \
                /* deleteSub == NULL because this min not to free ,just become root->data; */                                                            \
                root->left = __SET_removeSET_##TName##_node_t(root->left, compare, NULL, &root->data, size);                                             \
                if (__SET_heightSET_##TName(root->right) - __SET_heightSET_##TName(root->left) == 2)                                                     \
                {                                                                                                                                        \
                    if (__SET_heightSET_##TName(root->right->right) > __SET_heightSET_##TName(root->right->left))                                        \
                        root = __SET_singleRotateRightSET_##TName(root);                                                                                 \
                    else                                                                                                                                 \
                        root = __SET_doubleRotateRightSET_##TName(root);                                                                                 \
                }                                                                                                                                        \
            }                                                                                                                                            \
            else                                                                                                                                         \
            {                                                                                                                                            \
                /* has only child or no child */                                                                                                         \
                SET_##TName##_node_t *t = (root->right == NULL) ? (root->left) : (root->right);                                                          \
                if (deleteSub != NULL)                                                                                                                   \
                    deleteSub(&root->data);                                                                                                              \
                free(root);                                                                                                                              \
                (*size)--;                                                                                                                               \
                root = t;                                                                                                                                \
            }                                                                                                                                            \
        }                                                                                                                                                \
        if (root != NULL)                                                                                                                                \
            root->heigh = SET_Max(__SET_heightSET_##TName(root->left),                                                                                   \
                                  __SET_heightSET_##TName(root->right)) +                                                                                \
                          1;                                                                                                                             \
        return root;                                                                                                                                     \
    }                                                                                                                                                    \
    /*! @brief 真正被结构体调用的函数 ,此函数将会调用  __SET_removeSET_##TName##_node_t 递归查询删除,然后维护平衡 */       \
    u8 __SET_removeSET_##TName(SET_##TName *set, const T ele)                                                                                            \
    {                                                                                                                                                    \
        if (set == NULL || set->compare == NULL)                                                                                                         \
            return 0;                                                                                                                                    \
        u32 cursize = set->size;                                                                                                                         \
        set->root = __SET_removeSET_##TName##_node_t(set->root, set->compare, set->deleteSub, &ele, &set->size);                                         \
        return (cursize < set->size);                                                                                                                    \
    }
/**
 ***********************************************************************
 * @brief 实现获取返回当前set的大小的函数 简单,不做赘述
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_GETSIZE(T, TName)                         \
    u32 __SET_getSizeSET_##TName(SET_##TName *set)  \
    {                                               \
        return (set == NULL) ? (-1u) : (set->size); \
    }

/**
 ***********************************************************************
 * @brief 实现将set中的元素复制转换成数组的功能
 * 但是请注意:生成出来的数组,如果元素中有指针,那么此数组中的元素将会与SET中指向
 * 同一块地址,因此请使用者思考后在进行操作;同时,释放空间也需要释放次数组空间即可;
 * @param param1                 Explanation_theParam
 * @param param1                 Explanation_theParam
 * @return Return_Value_Type    Explanation_theReturn
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_TODATA(T, TName)                                                                                                \
    /*! @brief todata 实现的主要函数,使用此函数递归遍历树中的元素 */                                 \
    u32 __SET_toDataSET_##TName##_node_t(SET_##TName##_node_t *node, T *array)                                            \
    {                                                                                                                     \
        u32 ret = 0;                                                                                                      \
        if (node != NULL && array != NULL)                                                                                \
        {                                                                                                                 \
            ret += __SET_toDataSET_##TName##_node_t(node->left, array);                                                   \
            *(array + ret) = node->data;                                                                                  \
            ret++;                                                                                                        \
            ret += __SET_toDataSET_##TName##_node_t(node->right, array + ret);                                            \
        }                                                                                                                 \
        return ret;                                                                                                       \
    }                                                                                                                     \
    /*! @brief 将set中的数据复制出来成为一个数组,再次数组中改变并不会改变set中元素的值 */ \
    /*! @note 注意如果返回的 T 数组释放,只需要释放单纯的T数组空间*/                                \
    /*! @note 如果 T 中存在指针,那么此情况需要仔细思考*/                                                \
    /*! @note 此函数返回出来的值可以认为与Set 中指向了同一个空间 */                                \
    T *__SET_toDataSET_##TName(SET_##TName *set, u32 *lengh)                                                              \
    {                                                                                                                     \
        if (set == NULL || lengh == NULL)                                                                                 \
            return NULL;                                                                                                  \
        T *ret = (T *)malloc(sizeof(T) * set->size);                                                                      \
        *(lengh) = __SET_toDataSET_##TName##_node_t(set->root, ret);                                                      \
        return ret;                                                                                                       \
    }
/**
 ***********************************************************************
 * @brief 实现将set中的元素引用成数组的返回
 * 使用后请一定要 释放此数组指针的空间;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_TOITEM(T, TName)                                                                                            \
    /*! @brief 与 @see __SET_toDataSET_##TName##_node_t相似 只是此次操作的是set中元素的地址 */       \
    void __SET_itemDataSET_##TName##_node_t(SET_##TName##_node_t *root, T **array, u32 *lengh)                        \
    {                                                                                                                 \
        if (root == NULL || array == NULL)                                                                            \
            return;                                                                                                   \
        __SET_itemDataSET_##TName##_node_t(root->left, array + (*lengh), lengh);                                      \
        *(array + (*lengh)) = &root->data;                                                                            \
        (*lengh)++;                                                                                                   \
        __SET_itemDataSET_##TName##_node_t(root->right, array + (*lengh), lengh);                                     \
    }                                                                                                                 \
    /*! @brief 与 @see SET_toDataSET_##TName ,但此次返回的是元素指针数组 即全部都是真实引用 */ \
    /*! @brief 所有对此数组元素的操作都会真实的反映到SET中的元素中 */                         \
    T **__SET_itemDataSET_##TName(SET_##TName *set, u32 *lengh)                                                       \
    {                                                                                                                 \
        if (set == NULL || lengh == NULL)                                                                             \
            return NULL;                                                                                              \
        *lengh = 0;                                                                                                   \
        T **ret = (T **)malloc(sizeof(T *) * set->size);                                                              \
        if (ret == NULL)                                                                                              \
            return ret;                                                                                               \
        __SET_itemDataSET_##TName##_node_t(set->root, ret, lengh);                                                    \
        return ret;                                                                                                   \
    }
/**
 ***********************************************************************
 * @brief 实现find函数功能,如果没有找到,返回NULL 指针,如果找到了返回指向该元素的
 * 指针;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_FIND(T, TName)                                   \
    T *__SET_findSET_##TName(SET_##TName *set, const T *v) \
    {                                                      \
        SET_##TName##_node_t *item = NULL;                 \
        T *ret = NULL;                                     \
        if (set == NULL || set->compare == NULL)           \
            return NULL;                                   \
        item = set->root;                                  \
        while (item != NULL)                               \
        {                                                  \
            if (set->compare(v, &item->data))              \
            {                                              \
                item = item->left;                         \
            }                                              \
            else if (set->compare(&item->data, v))         \
            {                                              \
                item = item->right;                        \
            }                                              \
            else                                           \
            { /* find the item; */                         \
                ret = &(item->data);                       \
            }                                              \
        }                                                  \
        return ret;                                        \
    }

/**
 ***********************************************************************
 * @brief 实现显示函数,递归遍历 中序递归遍历;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_SHOW(T, TName)                                                                          \
    void __SET_showSET_##TName##_node_t(SET_##TName##_node_t *root, void (*toString)(const T *a)) \
    {                                                                                             \
        if (root == NULL)                                                                         \
        {                                                                                         \
            /* du nothing */                                                                      \
            return;                                                                               \
        }                                                                                         \
        __SET_showSET_##TName##_node_t(root->left, toString);                                     \
        toString(&root->data);                                                                    \
        __SET_showSET_##TName##_node_t(root->right, toString);                                    \
    }                                                                                             \
    /*! @brief 递归中序遍历 显示所有元素 */                                           \
    void __SET_showSET_##TName(SET_##TName *set)                                                  \
    {                                                                                             \
        if (set == NULL || set->toString == NULL)                                                 \
            return;                                                                               \
        VPRINTF("\nTHIS SET SIZE = %u;\n", set->size);                                            \
        __SET_showSET_##TName##_node_t(set->root, set->toString);                                 \
    }
/**
 ***********************************************************************
 * @brief 寻找到当前set中最大的元素,并返回此元素的指针
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_FINDMAX(T, TName)                       \
    T *__SET_findMaxSET_##TName(SET_##TName *set) \
    {                                             \
        if (set == NULL || set->root == NULL)     \
            return NULL;                          \
        SET_##TName##_node_t *item = set->root;   \
        while (item->right != NULL)               \
            item = item->right;                   \
        return &item->data;                       \
    }

/**
 ***********************************************************************
 * @brief 寻找到当前set中最小的元素,并返回此元素的指针
 * @see S_FINDMAX
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_FINDMIN(T, TName)                       \
    T *__SET_findMinSET_##TName(SET_##TName *set) \
    {                                             \
        if (set == NULL || set->root == NULL)     \
            return NULL;                          \
        SET_##TName##_node_t *item = set->root;   \
        while (item->left != NULL)                \
            item = item->left;                    \
        return &item->data;                       \
    }

/**
 ***********************************************************************
 * @brief 实现删除最大的元素的函数,如果删除成功,将返回最大的元素值,如果删除失败,
 * 那么将返回 -1的填充
 * @note 如果元素中有指针,且deleteSub函数不为NULL 那么此返回值不可靠;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_REMOVEMAX(T, TName)                                                 \
    T __SET_removeMaxSET_##TName(SET_##TName *set)                            \
    {                                                                         \
        T ret;                                                                \
        memset(&ret, 0xFF, sizeof(T));                                        \
        if (set == NULL || set->compare == NULL || set->root == NULL)         \
            return ret;                                                       \
        ret = (*__SET_findMaxSET_##TName(set));                               \
        set->root = __SET_removeSET_##TName##_node_t(set->root, set->compare, \
                                                     set->deleteSub,          \
                                                     &ret,                    \
                                                     &set->size);             \
        return ret;                                                           \
    }

/**
 ***********************************************************************
 * @brief 实现删除最小的元素的函数,如果删除成功,将返回最大的元素值,如果删除失败,
 * 那么将返回 -1的填充 @see S_REMOVEMAX
 * @note 如果元素中有指针,且deleteSub函数不为NULL 那么此返回值不可靠;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */

#define S_REMOVEMIN(T, TName)                                                 \
    T __SET_removeMinSET_##TName(SET_##TName *set)                            \
    {                                                                         \
        T ret;                                                                \
        memset(&ret, 0xFF, sizeof(T));                                        \
        if (set == NULL || set->compare == NULL || set->root == NULL)         \
            return ret;                                                       \
        ret = (*__SET_findMinSET_##TName(set));                               \
        set->root = __SET_removeSET_##TName##_node_t(set->root, set->compare, \
                                                     set->deleteSub,          \
                                                     &ret,                    \
                                                     &set->size);             \
        return ret;                                                           \
    }

/**
 ***********************************************************************
 * @brief 实现clear函数，与delete函数类似，只是最后并不free  自身
 * @param SET_##TName *set                 指向需要操作的set指针
 * @return void    
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define S_CLEAR(T, TName)                                            \
    void __SET_clearSET_##TName(SET_##TName *set)                    \
    {                                                                \
        if (set != NULL)                                             \
            return;                                                  \
        __SET_deleteSET_##TName##_node_t(set->deleteSub, set->root); \
        set->size = 0;                                               \
        set->root = NULL;                                            \
    }

/**
 ***********************************************************************
 * @brief 声明 某一个数据结构的SET 结构 此宏应该使用在 .h文件中
 * @param T                     SET中数据元素的类型
 * @param TName                 你给此数据元素类型起的别名
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define SET_Define(T, TName)                      \
    S_TYPEDEF(T, TName)                           \
    extern SET_##TName *SET_newSET_##TName(void); \
    extern void SET_deleteSET_##TName(SET_##TName *set);

/**
 ***********************************************************************
 * @brief 实现定义某个结构体;前两项与Define相同,后三项分别是函数指针,分别实现不同的
 * 功能,此宏定义应该在.c文件中使用
 * @param Compare                 比较函数的函数指针,此函数为必须实现如果Compare(a,b) a<b 则返回 !0 ;
 * @param DeleteSub                 删除子元素,如果类型 T中有指针,且会指向malloc的内存,那么此函数为必要
 * @param ToString                 此函数为show函数的基础函数,如果此函数为NULL 则show函数无反应;
 * @return Return_Value_Type    Explanation_theReturn
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
#define SET_Declare_Set(T, TName, Compare, DeleteSub, ToString)                                           \
    extern u8 __SET_heightSET_##TName(SET_##TName##_node_t *s);                                           \
    extern SET_##TName##_node_t *__SET_singleRotateLeftSET_##TName(SET_##TName##_node_t *s);              \
    extern SET_##TName##_node_t *__SET_singleRotateRightSET_##TName(SET_##TName##_node_t *s);             \
    extern SET_##TName##_node_t *__SET_doubleRotateLeftSET_##TName(SET_##TName##_node_t *s);              \
    extern SET_##TName##_node_t *__SET_doubleRotateRightSET_##TName(SET_##TName##_node_t *s);             \
    extern SET_##TName##_node_t *__SET_insertSET_##TName##_node_t(SET_##TName##_node_t *root,             \
                                                                  u8 (*compare)(const T *a, const T *b),  \
                                                                  const T *value, u32 *size);             \
    extern u8 __SET_insertSET_##TName(SET_##TName *set, const T ele);                                     \
    extern SET_##TName##_node_t *__SET_removeSET_##TName##_node_t(SET_##TName##_node_t *root,             \
                                                                  u8 (*compare)(const T *a, const T *b),  \
                                                                  void (*deleteSub)(const T *ele),        \
                                                                  const T *value, u32 *size);             \
    extern u8 __SET_removeSET_##TName(SET_##TName *set, const T ele);                                     \
    extern u32 __SET_getSizeSET_##TName(SET_##TName *set);                                                \
    extern u32 __SET_toDataSET_##TName##_node_t(SET_##TName##_node_t *node, T *array);                    \
    extern T *__SET_toDataSET_##TName(SET_##TName *set, u32 *lengh);                                      \
    extern void __SET_itemDataSET_##TName##_node_t(SET_##TName##_node_t *root, T **array, u32 *lengh);    \
    extern T **__SET_itemDataSET_##TName(SET_##TName *set, u32 *lengh);                                   \
    extern T *__SET_findSET_##TName(SET_##TName *set, const T *v);                                        \
    extern void __SET_showSET_##TName##_node_t(SET_##TName##_node_t *root, void (*toString)(const T *a)); \
    extern void __SET_showSET_##TName(SET_##TName *set);                                                  \
    extern T *__SET_findMaxSET_##TName(SET_##TName *set);                                                 \
    extern T *__SET_findMinSET_##TName(SET_##TName *set);                                                 \
    extern T __SET_removeMaxSET_##TName(SET_##TName *set);                                                \
    extern T __SET_removeMinSET_##TName(SET_##TName *set);                                                \
    void __SET_clearSET_##TName(SET_##TName *set);                                                        \
    S_NEW(T, TName, Compare, ToString, DeleteSub)                                                         \
    S_DELETE(T, TName)                                                                                    \
    S_INSERT(T, TName)                                                                                    \
    S_REMOVE(T, TName)                                                                                    \
    S_GETSIZE(T, TName)                                                                                   \
    S_TODATA(T, TName)                                                                                    \
    S_TOITEM(T, TName)                                                                                    \
    S_FIND(T, TName)                                                                                      \
    S_SHOW(T, TName)                                                                                      \
    S_FINDMAX(T, TName)                                                                                   \
    S_FINDMIN(T, TName)                                                                                   \
    S_REMOVEMAX(T, TName)                                                                                 \
    S_REMOVEMIN(T, TName)                                                                                 \
    S_CLEAR(T, TName)

//-----------------------------------------------//

#endif // _cset.h
