#include "cset.h"

void cset_test_demo(void)
{
}

SET_typeClass_t *SET_newtypeClass_t(void)
{
    SET_typeClass_t *ret = (SET_typeClass_t *)malloc(sizeof(SET_typeClass_t));
    if (ret != NULL)
    {
        ret->size = 0;
        ret->root = NULL;
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

void SET_inserttypeClass_t(SET_typeClass_t *set, const typeClass *ele)
{
}
void SET_removetypeClass_t(SET_typeClass_t *set, const typeClass *ele)
{
}
u32 SET_getSizetypeClass_t(SET_typeClass_t *set)
{
    if (set != NULL)
        return set->size;
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
const typeClass *SET_toDatatypeClass_t(SET_typeClass_t *set, u32 *lengh)
{
    if (set == NULL || lengh == NULL)
        return NULL;
    typeClass *ret = (typeClass *)malloc(sizeof(typeClass) * set->size);
    *(lengh) = SET_toDatatypeClass_node_t(set->root, ret);
    return ret;
}

const SET_typeClass_node_t *SET_nexttypeClass_t(const SET_typeClass_node_t *item)
{
}
