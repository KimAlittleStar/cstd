#include "cset.h"

u8 compare_temp(const typeClass *a, const typeClass *b)
{
    return *a < *b;
}
void cset_test_demo(void)
{
    SET_typeClass_t *test = SET_newtypeClass_t();
    test->compare = compare_temp;
    test->deleteSub = NULL;
    for (u32 i = 0; i < 10; i++)
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
    data = SET_toDatatypeClass_t(test, &len);
    for (u32 i = 0; i < len; i++)
    {
        printf("%d\n", data[i]);
    }
    free(data);

    SET_removetypeClass_t(test, 41);
    printf("\nremove 41\n");
    data = SET_toDatatypeClass_t(test, &len);
    for (u32 i = 0; i < len; i++)
    {
        printf("%d\n", data[i]);
    }
    free(data);
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

inline u8 SET_heighttypeClass(SET_typeClass_node_t *s)
{
    return (s == NULL) ? (0) : (s->heigh);
}

_Static SET_typeClass_node_t *SET_doubleRotateLefttypeClass(SET_typeClass_node_t *s)
{
    s->left = SET_singleRotateRighttypeClass(s->left);
    return SET_singleRotateLefttypeClass(s);
}
_Static SET_typeClass_node_t *SET_doubleRotateRighttypeClass(SET_typeClass_node_t *s)
{
    s->right = SET_singleRotateLefttypeClass(s->right);
    return SET_singleRotateRighttypeClass(s);
}

_Static SET_typeClass_node_t *SET_singleRotateLefttypeClass(SET_typeClass_node_t *s)
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

_Static SET_typeClass_node_t *SET_singleRotateRighttypeClass(SET_typeClass_node_t *s)
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
_Static SET_typeClass_node_t *SET_inserttypeClass_node_t(SET_typeClass_node_t *root,
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
void SET_inserttypeClass_t(SET_typeClass_t *set, const typeClass ele)
{
    if (set == NULL || set->compare == NULL)
        return;
    set->root = SET_inserttypeClass_node_t(set->root, set->compare, &ele, &set->size);
}

typeClass SET_removeMintypeClass_t(SET_typeClass_node_t *s)
{
    typeClass ret = {0};
    if (s == NULL)
        return ret;
    while (s->left != NULL && s->left->left != NULL)
        s = s->left;
    SET_typeClass_node_t *min = s->left;
    s->left = min->right;
    ret = min->data;
    free(min);
    return ret;
}

_Static SET_typeClass_node_t *SET_removetypeClass_node_t(SET_typeClass_node_t *root,
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
            if (compare(&root->right->data, value))
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
            if (compare(value, &root->left->data))
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
                if (compare(&root->right->data, value))
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

void SET_removetypeClass_t(SET_typeClass_t *set, const typeClass ele)
{
    SET_removetypeClass_node_t(set->root, set->compare, set->deleteSub, &ele, &set->size);
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

const SET_typeClass_node_t *SET_nexttypeClass_t(const SET_typeClass_node_t *item)
{
}
