/**
 **********************************************************************
 * @file cset.c
 * @brief 此文件属于 cset 项目中 SET.h文件的测试 demo文件，所有在set 方法中可能用到的
 * 函数都会在这里有映射，因此如果出现BUG可以使用此文件进行调试，当然更新相应功能也需要使用此文件更新；
 * @verbatim
 * >Introduce: 利用宏定义膨胀代码可以将set 这一C++中的标准容器使用到C语言中；
 * >Depend On: set 需要用到 以下几个库函数 malloc free rand memset memcpy
 * 如果需要正常使用 set 至少需要实现 compare 函数，否则set将不能使用；
 * >Include: 默认include stdio stdlib
 * @endverbatim
 * @author  kimalittlestar@gmail.com
 * @date 2019-10-24
 * @version V0.0
 * @note CopyRight By XXXX Co. Ltd All right reserve
 **********************************************************************
*/
#include "cset.h"
/* 不影响cset.h 中的所有函数， 其中cset.h 中的所有函数够可以在下列函数中 得到映射*/

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
    void (*deleteSub)(const typeClass *ele);
    /*! @brief 作为元素的比较函数 */
    u8 (*compare)(const typeClass *a, const typeClass *b);
    void (*toString)(const typeClass *a);
    u8 (*insert)(struct __SET_typeClass_t *set, const typeClass ele);
    u8 (*remove)(struct __SET_typeClass_t *set, const typeClass ele);
    u32 (*getSize)(struct __SET_typeClass_t *set);
    typeClass *(*toData)(struct __SET_typeClass_t *set, u32 *lengh);
    typeClass **(*itemData)(struct __SET_typeClass_t *set, u32 *lengh);
    void (*show)(struct __SET_typeClass_t *set);
    typeClass *(*find)(struct __SET_typeClass_t *set, const typeClass *v);
    typeClass *(*findMax)(struct __SET_typeClass_t *set);
    typeClass *(*findMin)(struct __SET_typeClass_t *set);
    typeClass (*removeMax)(struct __SET_typeClass_t *set);
    typeClass (*removeMin)(struct __SET_typeClass_t *set);

} SET_typeClass_t;

SET_typeClass_t *SET_newtypeClass_t(void);
void SET_deletetypeClass_t(SET_typeClass_t *set);
u8 SET_inserttypeClass_t(SET_typeClass_t *set, const typeClass ele);
u8 SET_removetypeClass_t(SET_typeClass_t *set, const typeClass ele);
u32 SET_getSizetypeClass_t(SET_typeClass_t *set);
typeClass *SET_toDatatypeClass_t(SET_typeClass_t *set, u32 *lengh);
typeClass **SET_itemDatatypeClass_t(SET_typeClass_t *set, u32 *lengh);
void SET_showtypeClass_t(SET_typeClass_t *set);
typeClass *SET_findtypeClass_t(SET_typeClass_t *set, const typeClass *v);
typeClass *SET_findMaxtypeClass_t(SET_typeClass_t *set);
typeClass *SET_findMintypeClass_t(SET_typeClass_t *set);
typeClass SET_removeMaxtypeClass_t(SET_typeClass_t *set);
typeClass SET_removeMintypeClass_t(SET_typeClass_t *set);

void SET_deletetypeClass_node_t(void (*freesub)(const typeClass *d), SET_typeClass_node_t *node);
u32 SET_toDatatypeClass_node_t(SET_typeClass_node_t *node, typeClass *array);
void SET_itemDatatypeClass_node_t(SET_typeClass_node_t *root, typeClass **array, u32 *lengh);
SET_typeClass_node_t *SET_doubleRotateLefttypeClass(SET_typeClass_node_t *s);
SET_typeClass_node_t *SET_doubleRotateRighttypeClass(SET_typeClass_node_t *s);
SET_typeClass_node_t *SET_singleRotateLefttypeClass(SET_typeClass_node_t *s);
SET_typeClass_node_t *SET_singleRotateRighttypeClass(SET_typeClass_node_t *s);
SET_typeClass_node_t *SET_inserttypeClass_node_t(SET_typeClass_node_t *root,
                                                 u8 (*compare)(const typeClass *a, const typeClass *b),
                                                 const typeClass *value, u32 *size);
SET_typeClass_node_t *SET_removetypeClass_node_t(SET_typeClass_node_t *root,
                                                 u8 (*compare)(const typeClass *a, const typeClass *b),
                                                 void (*deleteSub)(const typeClass *ele),
                                                 const typeClass *value, u32 *size);

u8 SET_heighttypeClass(SET_typeClass_node_t *s);
void SET_showtypeClass_node_t(SET_typeClass_node_t *root, void (*toString)(const typeClass *a));

/*----------------------------------函数声明结束---------------------------------------------*/

u8 compare_temp(const typeClass *a, const typeClass *b)
{
    return *a < *b;
}
void toString_temp(const typeClass *a)
{
    VPRINTF("%d \n", *a);
}
SET_Define(u32, u16_t);
/**/
SET_Declare_Set(u32, u16_t, compare_temp, NULL, toString_temp);

/**
 ***********************************************************************
 * @brief 此函数是一个实力demo函数，这个函数是笔者作为测试函数的一个入口函数
 * @param param1                 Explanation_theParam
 * @param param1                 Explanation_theParam
 * @return Return_Value_Type    Explanation_theReturn
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-24
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
void cset_test_demo(void)
{
    SET_typeClass_t *test = SET_newtypeClass_t();
    test->compare = compare_temp;
    test->deleteSub = NULL;
    test->toString = toString_temp;
    for (u32 i = 0; i < 15; i++)
        SET_inserttypeClass_t(test, rand() & 0xFFFFFF);
    u32 len = 0;
    typeClass *data = SET_toDatatypeClass_t(test, &len);
    for (u32 i = 0; i < len; i++)
    {
        printf("%d\n", data[i]);
    }
    free(data);

    SET_removetypeClass_t(test, 6334);
    printf("\nremove 6334\n");
    SET_showtypeClass_t(test);
    // data = SET_toDatatypeClass_t(test, &len);
    // for (u32 i = 0; i < len; i++)
    // {
    //     printf("%d\n", data[i]);
    // }
    // free(data);

    SET_removetypeClass_t(test, 41);
    printf("\nremove 41\n");
    SET_showtypeClass_t(test);
    // data = SET_toDatatypeClass_t(test, &len);
    // for (u32 i = 0; i < len; i++)
    // {
    //     printf("%d\n", data[i]);
    // }
    // free(data);

    SET_removeMaxtypeClass_t(test);
    printf("\nremove Max\n");
    SET_showtypeClass_t(test);

    SET_removeMintypeClass_t(test);
    printf("\nremove Min\n");
    SET_showtypeClass_t(test);
    while (SET_getSizetypeClass_t(test) != 0)
    {
        printf("remove and size = %d\n", test->size);
        SET_removeMaxtypeClass_t(test);
        SET_removeMintypeClass_t(test);
        SET_showtypeClass_t(test);
    }
#if 1
    SET_u16_t *set = SET_newSET_u16_t();
    for (u32 i = 0; i < 5000; i++)
    {
        set->insert(set, rand() & 0xFFFFF);
    }

    while (set->size != 0)
    {
        printf("this set size = %d\n", set->size);
        printf("remove max = %d\n", set->removeMax(set));
        printf("remove max = %d\n", set->removeMin(set));
    }
    SET_deleteSET_u16_t(set);
    printf("over that \n");
#endif
}

SET_typeClass_t *SET_newtypeClass_t(void)
{
    SET_typeClass_t *ret = (SET_typeClass_t *)malloc(sizeof(SET_typeClass_t));
    if (ret != NULL)
    {
        ret->size = 0;
        ret->root = NULL;
        ret->deleteSub = NULL;
        ret->compare = NULL;
        ret->toString = NULL;
        ret->insert = SET_inserttypeClass_t;
        ret->remove = SET_removetypeClass_t;
        ret->getSize = SET_getSizetypeClass_t;
        ret->toData = SET_toDatatypeClass_t;
        ret->itemData = SET_itemDatatypeClass_t;
        ret->show = SET_showtypeClass_t;
        ret->find = SET_findtypeClass_t;
        ret->findMax = SET_findMaxtypeClass_t;
        ret->findMin = SET_findMintypeClass_t;
        ret->removeMax = SET_removeMaxtypeClass_t;
        ret->removeMin = SET_removeMintypeClass_t;
    }
    return ret;
}

/**
 ***********************************************************************
 * @brief deleteFunction
 * @param void (*)(const typeClass *d)                 
 *                      这是一个函数指针,用于释放data中可能引用的地址;
 * @param SET_typeClass_node_t*                        
 *                      传入一个节点,将会递归的将此节点中的所有元素释放
 * @return void    
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-23
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
void SET_deletetypeClass_node_t(void (*freesub)(const typeClass *d), SET_typeClass_node_t *node)
{
    if (node == NULL)
        return;
    SET_deletetypeClass_node_t(freesub, node->left);
    if (freesub != NULL)
        freesub(&(node->data));
    SET_deletetypeClass_node_t(freesub, node->right);
    free(node);
}
void SET_deletetypeClass_t(SET_typeClass_t *set)
{
    if (set != NULL)
        return;
    SET_deletetypeClass_node_t(NULL, set->root);
    free(set);
}

inline u8 SET_heighttypeClass(SET_typeClass_node_t *s)
{
    return (s == NULL) ? (0) : (s->heigh);
}

SET_typeClass_node_t *SET_doubleRotateLefttypeClass(SET_typeClass_node_t *s)
{
    s->left = SET_singleRotateRighttypeClass(s->left);
    return SET_singleRotateLefttypeClass(s);
}
SET_typeClass_node_t *SET_doubleRotateRighttypeClass(SET_typeClass_node_t *s)
{
    s->right = SET_singleRotateLefttypeClass(s->right);
    return SET_singleRotateRighttypeClass(s);
}

SET_typeClass_node_t *SET_singleRotateLefttypeClass(SET_typeClass_node_t *s)
{
    SET_typeClass_node_t *s1;
    s1 = s->left;
    s->left = s1->right;
    s1->right = s;

    s->heigh = SET_Max(
                   SET_heighttypeClass(s->left),
                   SET_heighttypeClass(s->right)) +
               1;
    s1->heigh = SET_Max(
                    SET_heighttypeClass(s1->left),
                    s->heigh) +
                1;
    return s1;
}

SET_typeClass_node_t *SET_singleRotateRighttypeClass(SET_typeClass_node_t *s)
{
    SET_typeClass_node_t *s1;
    s1 = s->right;
    s->right = s1->left;
    s1->left = s;

    s->heigh = SET_Max(
                   SET_heighttypeClass(s->left),
                   SET_heighttypeClass(s->right)) +
               1;
    s1->heigh = SET_Max(
                    SET_heighttypeClass(s1->right),
                    s->heigh) +
                1;
    return s1;
}
SET_typeClass_node_t *SET_inserttypeClass_node_t(SET_typeClass_node_t *root,
                                                 u8 (*compare)(const typeClass *a, const typeClass *b),
                                                 const typeClass *value, u32 *size)
{
    if (root == NULL)
    {
        root = (SET_typeClass_node_t *)malloc(sizeof(SET_typeClass_node_t));
        if (root == NULL)
        {
            // Out of space!!!
        }
        else
        {
            root->data = (*value);
            root->left = root->right = NULL;
            root->heigh = 1;
            (*size)++;
        }
        return root;
    }
    else if (compare(value, &root->data))
    {
        root->left = SET_inserttypeClass_node_t(root->left, compare, value, size);
        if (SET_heighttypeClass(root->left) - SET_heighttypeClass(root->right) == 2)
        {
            if (compare(value, &root->left->data))
                root = SET_singleRotateLefttypeClass(root);
            else
                root = SET_doubleRotateLefttypeClass(root);
        }
    }
    else if (compare(&root->data, value))
    {
        root->right = SET_inserttypeClass_node_t(root->right, compare, value, size);
        if (SET_heighttypeClass(root->right) - SET_heighttypeClass(root->left) == 2)
        {
            if (compare(&root->right->data, value))
                root = SET_singleRotateRighttypeClass(root);
            else
                root = SET_doubleRotateRighttypeClass(root);
        }
    }
    root->heigh = SET_Max(SET_heighttypeClass(root->left),
                          SET_heighttypeClass(root->right)) +
                  1;
    return root;
}
u8 SET_inserttypeClass_t(SET_typeClass_t *set, const typeClass ele)
{
    if (set == NULL || set->compare == NULL)
        return 0;
    u32 cursize = set->size;
    set->root = SET_inserttypeClass_node_t(set->root, set->compare, &ele, &set->size);
    return (cursize < set->size);
}

SET_typeClass_node_t *SET_removetypeClass_node_t(SET_typeClass_node_t *root,
                                                 u8 (*compare)(const typeClass *a, const typeClass *b),
                                                 void (*deleteSub)(const typeClass *ele),
                                                 const typeClass *value, u32 *size)
{
    if (root == NULL)
    {
        // no has this value
    }
    else if (compare(value, &root->data))
    {
        root->left = SET_removetypeClass_node_t(root->left, compare, deleteSub, value, size);
        if (SET_heighttypeClass(root->right) - SET_heighttypeClass(root->left) == 2)
        {
            if (SET_heighttypeClass(root->right->right) > SET_heighttypeClass(root->right->left))
                root = SET_singleRotateRighttypeClass(root);
            else
                root = SET_doubleRotateRighttypeClass(root);
        }
    }
    else if (compare(&root->data, value))
    {
        root->right = SET_removetypeClass_node_t(root->right, compare, deleteSub, value, size);
        if (SET_heighttypeClass(root->left) - SET_heighttypeClass(root->right) == 2)
        {
            if (SET_heighttypeClass(root->left->left) > SET_heighttypeClass(root->left->right))
                root = SET_singleRotateLefttypeClass(root);
            else
                root = SET_doubleRotateLefttypeClass(root);
        }
    }
    else
    {
        /*real delete option*/
        if (root->right != NULL && root->left != NULL)
        {
            /* has two child */
            SET_typeClass_node_t *temp = root;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            if (deleteSub != NULL)
                deleteSub(&root->data);
            root->data = temp->data;

            /* deleteSub == NULL because this min not to free ,just become root->data; */
            root->left = SET_removetypeClass_node_t(root->left, compare, NULL, &root->data, size);
            if (SET_heighttypeClass(root->right) - SET_heighttypeClass(root->left) == 2)
            {
                if (SET_heighttypeClass(root->right->right) > SET_heighttypeClass(root->right->left))
                    root = SET_singleRotateRighttypeClass(root);
                else
                    root = SET_doubleRotateRighttypeClass(root);
            }
        }
        else
        {
            /* has only child or no child */
            SET_typeClass_node_t *t = (root->right == NULL) ? (root->left) : (root->right);
            if (deleteSub != NULL)
                deleteSub(&root->data);
            free(root);
            (*size)--;
            root = t;
        }
    }
    if (root != NULL)
        root->heigh = SET_Max(SET_heighttypeClass(root->left),
                              SET_heighttypeClass(root->right)) +
                      1;
    return root;
}

u8 SET_removetypeClass_t(SET_typeClass_t *set, const typeClass ele)
{
    if (set == NULL || set->compare == NULL)
        return 0;
    u32 cursize = set->size;
    set->root = SET_removetypeClass_node_t(set->root, set->compare, set->deleteSub, &ele, &set->size);
    return (cursize > set->size);
}
u32 SET_getSizetypeClass_t(SET_typeClass_t *set)
{
    return (set == NULL) ? (-1u) : (set->size);
}

/**
 ***********************************************************************
 * @brief SET_toDatatypeClass_node_t
 * 此函数用来中序遍历指针生成一个数组;属于递归调用中的一个子函数;
 * @param SET_typeClass_node_t *                 需要迭代放入数组的节点指针
 * @param typeClass *                            存储数据的数组指针
 * @return u32                                   返回在当前node节点下总共有多少数据;
 * @author kimalittlestar@gmail.com
 * @date Create at 2019-10-23
 * @note AllCopyRight by XXX CO ,. LTD
 **********************************************************************
 */
u32 SET_toDatatypeClass_node_t(SET_typeClass_node_t *node, typeClass *array)
{
    u32 ret = 0;
    if (node != NULL && array != NULL)
    {
        ret += SET_toDatatypeClass_node_t(node->left, array);
        *(array + ret) = node->data;
        ret++;
        ret += SET_toDatatypeClass_node_t(node->right, array + ret);
    }
    return ret;
}
typeClass *SET_toDatatypeClass_t(SET_typeClass_t *set, u32 *lengh)
{
    if (set == NULL || lengh == NULL)
        return NULL;
    typeClass *ret = (typeClass *)malloc(sizeof(typeClass) * set->size);
    *(lengh) = SET_toDatatypeClass_node_t(set->root, ret);
    return ret;
}
void SET_itemDatatypeClass_node_t(SET_typeClass_node_t *root, typeClass **array, u32 *lengh)
{
    if (root == NULL || array == NULL)
        return;
    SET_itemDatatypeClass_node_t(root->left, array + (*lengh), lengh);
    *(array + (*lengh)) = &root->data;
    (*lengh)++;
    SET_itemDatatypeClass_node_t(root->right, array + (*lengh), lengh);
}

typeClass **SET_itemDatatypeClass_t(SET_typeClass_t *set, u32 *lengh)
{
    if (set == NULL || lengh == NULL)
        return NULL;
    *lengh = 0;
    typeClass **ret = (typeClass **)malloc(sizeof(typeClass *) * set->size);
    if (ret == NULL)
        return ret;
    SET_itemDatatypeClass_node_t(set->root, ret, lengh);
    return ret;
}

typeClass *SET_findtypeClass_t(SET_typeClass_t *set, const typeClass *v)
{
    SET_typeClass_node_t *item = NULL;
    typeClass *ret = NULL;
    if (set == NULL || set->compare == NULL)
        return NULL;
    item = set->root;
    while (item != NULL)
    {
        if (set->compare(v, &item->data))
        {
            item = item->left;
        }
        else if (set->compare(&item->data, v))
        {
            item = item->right;
        }
        else
        { /* find the item; */
            ret = &(item->data);
        }
    }
    return ret;
}

void SET_showtypeClass_node_t(SET_typeClass_node_t *root, void (*toString)(const typeClass *a))
{
    if (root == NULL)
    {
        /* du nothing */
        return;
    }
    SET_showtypeClass_node_t(root->left, toString);
    toString(&root->data);
    SET_showtypeClass_node_t(root->right, toString);
}
void SET_showtypeClass_t(SET_typeClass_t *set)
{
    if (set == NULL || set->toString == NULL)
        return;
    VPRINTF("\nTHIS SET SIZE = %u;\n", set->size);
    SET_showtypeClass_node_t(set->root, set->toString);
}

typeClass *SET_findMaxtypeClass_t(SET_typeClass_t *set)
{
    if (set == NULL || set->root == NULL)
        return NULL;
    SET_typeClass_node_t *item = set->root;
    while (item->right != NULL)
        item = item->right;
    return &item->data;
}

typeClass *SET_findMintypeClass_t(SET_typeClass_t *set)
{
    if (set == NULL || set->root == NULL)
        return NULL;
    SET_typeClass_node_t *item = set->root;
    while (item->left != NULL)
        item = item->left;
    return &item->data;
}

typeClass SET_removeMaxtypeClass_t(SET_typeClass_t *set)
{
    typeClass ret = {0};
    if (set == NULL || set->compare == NULL || set->root == NULL)
        return ret;
    ret = (*SET_findMaxtypeClass_t(set));
    set->root = SET_removetypeClass_node_t(set->root, set->compare,
                                           set->deleteSub,
                                           &ret,
                                           &set->size);
    return ret;
}

typeClass SET_removeMintypeClass_t(SET_typeClass_t *set)
{
    typeClass ret = {0};
    if (set == NULL || set->compare == NULL || set->root == NULL)
        return ret;
    ret = (*SET_findMintypeClass_t(set));
    set->root = SET_removetypeClass_node_t(set->root, set->compare,
                                           set->deleteSub,
                                           &ret,
                                           &set->size);
    return ret;
}
