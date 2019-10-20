/**
  * @file cvector.h
  * @breif 此头文件使用C语言实现了类似于C++ 中 Vector 中的功能 实现了 以下函数
  * resize,size,at,clear,append,insert,removelast,removeat,new,delete
  * 文件实现需要实现以下函数:
  * malloc,free,memcpy,memset
  * 使用事项:Vector 最大容量: 2^32-1;
  * @date 2019-10-05
  * @author kim_alittlestar@qq.com
  * @note all copyright by author
  *
  */
#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#define PRINTF_ENABLE 1

#if PRINTF_ENABLE == 1
#define VPRINTF(ftm,...) printf(ftm,##__VA_ARGS__)
#else
#define VPRINTF(ftm,...)
#endif

//---------------自定义类型区------------------//
#if 1

typedef unsigned int u32;
typedef unsigned short  u16;
typedef unsigned char   u8;
typedef unsigned long long u64;

#endif      //当#if 0 时自定义类型区关闭

#ifndef FALSE
#define FALSE 0u
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif




#ifndef _INC_STDLIB

extern void* memcpy(void* des ,void* src,u64 size);
extern void* malloc(u64 size);
extern void free(void* p);

#endif      //如果没有include stdlib.h 文件 那么需要实现以上几个函数

#ifndef _INC_STRING

void* memset(void* des,int v,u64 size);

#endif      //如果没有include string.h 文件 那么需要实现以上几个函数


//----------------vector 自定义结构体实现----------------//
#define V_TYPEDEF(XX,TypeName) typedef struct __##TypeName##_t \
{\
    XX* data;\
    u32 size;\
    u32 realsize;\
    u8   (* reSize)(struct __##TypeName##_t * v,u32 newsize);\
    u32  (* getSize)(struct __##TypeName##_t * v);\
    XX*  (* at) (struct __##TypeName##_t * v,u32 index);\
    u8   (* append)(struct __##TypeName##_t * v,const XX d);\
    void (* clear)(struct __##TypeName##_t * v);\
    void (* removeLast)(struct __##TypeName##_t * v);\
    void (* remove)(struct __##TypeName##_t * v,u32 starX,u32 lengh);\
    void (* insert)(struct __##TypeName##_t * v,u32 index,const XX value);\
    void (* sort)(struct __##TypeName##_t * v);\
    void (* show)(struct __##TypeName##_t * v);\
    u8   (* compare)(const XX * v1,const XX * v2);\
    void (* toString)(const XX * value);\
    void (* deleteSub)(const XX value);\
} VCT_##TypeName;

//V_TYPEDEF(int,Vint)

//--------------vector 自定义函数 实现区域------------//

/*
 *  new函数 返回相对应的vector 指针
*/
#define V_NEW(TypeName,COMPARE,TOSTR,DELSUB) \
 VCT_##TypeName* VCT_newVCT_##TypeName()\
{\
    VCT_##TypeName* ret = malloc(sizeof(VCT_##TypeName));\
    if(ret == NULL) return NULL;\
    ret->size = 0;\
    ret->realsize = 0;\
    ret->data = NULL;\
    ret->reSize = __VCT_resizeVCT_##TypeName;\
    ret->getSize = __VCT_sizeVCT_##TypeName;\
    ret->at = __VCT_atVCT_##TypeName;\
    ret->append = __VCT_appendVCT_##TypeName;\
    ret->clear = __VCT_clearVCT_##TypeName;\
    ret->removeLast = __VCT_removelastVCT_##TypeName;\
    ret->remove = __VCT_removeVCT_##TypeName;\
    ret->insert = __VCT_insertVCT_##TypeName;\
    ret->sort = __VCT_sortVCT_##TypeName;\
    ret->show = __VCT_showVCT_##TypeName;\
    ret->compare = COMPARE;\
    ret->toString = TOSTR;\
    ret->deleteSub = DELSUB;\
    return ret;\
}


/*
 *  delete函数,清理相关结构体使用的堆内存空间
*/
#define V_DELETE(TypeName)\
 void VCT_deleteVCT_##TypeName(VCT_##TypeName* v)\
{\
    if(v == NULL) return ;\
    if(v->data == NULL)    return ;\
    for(u32 i = 0;i< v->size && v->deleteSub != NULL;i++)\
        v->deleteSub(v->data[i]);\
    free(v->data);\
    free(v);\
}

/*
 *  vector 实现resize函数,当新的size大于原来的size时,此函数生效,否则则不生效.
*/
#define V_RESIZE(XX,TypeName) \
    u8 __VCT_resizeVCT_##TypeName(VCT_##TypeName* v,u32 newsize)\
 {\
    if(v->realsize < newsize && v->size < newsize )\
    {\
        XX* temp = malloc(sizeof(*v->data)*newsize);\
        if(temp == NULL) return FALSE;\
        memcpy(temp,v->data,sizeof(*v->data)*v->size);\
        memset(temp+v->size,0,sizeof(*v->data)*(newsize-v->size));\
        free(v->data);\
        v->data = temp;\
        v->realsize = newsize;\
        return TRUE;\
    }\
    return FALSE;\
 }

/**
 *  vector 实现 size 函数,获取当前有实际意义的大小为多少
 *
 */

#define V_SIZE(TypeName) \
    inline u32 __VCT_sizeVCT_##TypeName(VCT_##TypeName* v)\
    {\
        if(v!=NULL) return v->size;\
        else return -1u;\
    }

/*
 *  vector 实现 at 函数,需要 传参V不为空且 index 小于size  从0开始计数
*/
#define V_AT(XX,TypeName) \
    inline XX* __VCT_atVCT_##TypeName(VCT_##TypeName* v,u32 index)\
    {\
        if(v!=NULL && index < v->size)  return v->data+index;\
        else return NULL;\
    }

/*
 *  vector 实现 append 函数,需要 传参V不为空,自动追加在vector数组的末尾
*/
#define V_APPEND(XX,TypeName) \
    inline u8 __VCT_appendVCT_##TypeName(VCT_##TypeName* v,const XX d)\
    {\
        if(v!= NULL)\
        {\
            if(v->size >= v->realsize)\
                if(v->reSize(v,v->realsize*2+1) == FALSE)\
                    return FALSE;\
            v->data[v->size] = d;\
            v->size++;\
            return TRUE;\
        }\
        return FALSE;\
    }

/*
 *  vector 实现 clear 函数,需要 传参V不为空,清空vector中所有有效的数据,都初始化为 0,并将size重置,
 * 但是其真正占用的内存并没有被释放.
*/
#define V_CLEAR(TypeName) \
    inline void __VCT_clearVCT_##TypeName(VCT_##TypeName* v)\
 {\
    if(v != NULL) \
    {\
        for(u32 i = 0;i<v->size && v->deleteSub!= NULL;i++)\
            v->deleteSub(v->data[i]);\
        memset(v->data,0,sizeof(*v->data)*v->realsize);\
        v->size = 0;\
    }\
 }

/*
 *  vector 实现 removelast 函数,需要 传参V不为空,将vector 中最后一个数据删除 实质为size--
 * 但是其真正占用的内存并没有被释放.
*/
#define V_REMOVELAST(TypeName) \
    inline void __VCT_removelastVCT_##TypeName(VCT_##TypeName* v)\
 {\
    if(v!= NULL && v->size > 0)\
    {\
        v->size--;\
        if(v->deleteSub!= NULL)\
            v->deleteSub(v->data[v->size]);\
    }\
 }

/*
 *  vector 实现 remove 函数,需要 传参V不为空,将vector 中从指定位置开始删除 指定长度的数据,如果长度过大则自动判断删除后面所有,
 * 真正的删除,其末尾一定会追加 一个全为 0 的数据字节
 * .
*/
#define V_REMOVE(TypeName) \
    inline void __VCT_removeVCT_##TypeName(VCT_##TypeName* v,u32 starX,u32 lengh) \
{\
    if(v!= NULL) \
    {\
        if(lengh == 0)  return ;\
        else if(v->size > starX) \
        {\
            lengh = (v->size >(starX+lengh))?(lengh):(v->size - starX); \
            for(u32 i = starX;i<v->size;i++) \
            {\
                if(i+lengh < v->size)\
                {\
                    if(v->deleteSub!= NULL)\
                        v->deleteSub(v->data[i]);\
                    memcpy(v->data+i,v->data+i+lengh,sizeof(*v->data)); \
                }\
                else \
                    {memset(v->data+i,0,sizeof(*v->data));  break;}\
            }\
            v->size-=lengh;\
        }\
    }\
}

/*
 *  vector 实现 insert 函数,需要 传参V不为空,将vector 中从指定位置开始插入 指定数据,如果指定位置溢出则自动添加到最后,
 * .
*/
#define V_INSERT(T,TypeName) \
    inline void __VCT_insertVCT_##TypeName(VCT_##TypeName* v,u32 index,const T value) \
{\
    if(v!= NULL) \
    {\
        if(index > v->size)\
            index = v->size;\
        if(v->size >= v->realsize)\
            v->reSize(v,v->realsize*2+1);\
        for(u32 i = v->size;i>index;i--)\
            memcpy(v->data+i,v->data+i-1,sizeof(*v->data));\
        memcpy(v->data+index,&value,sizeof(*v->data));    \
        v->size++;\
    }\
}

/*
 *  vector 实现 sort 函数,需要 传参V不为空,将vector 进行升序排序,但是需要人为实现函数 compare
 * .
*/
#define V_SORT(T,TypeName) \
    void __VCT_sortVCT_##TypeName(VCT_##TypeName *v)\
    {\
        if(v == NULL || v->compare == NULL)    return ;\
        u32 *mapTab = (u32 *)malloc(sizeof(u32) * (v->size + 1));\
        u32 index = 0;\
        for (u32 i = 1; i <= v->size; i++)\
        {\
            index = i;\
            for (; index > 1 && v->compare(&v->data[i - 1], &v->data[mapTab[(index >> 1)]]); index >>= 1)\
                mapTab[index] = mapTab[index >> 1];\
            mapTab[index] = i - 1;\
        }\
        u32 child = 0;\
        u32 minindex;\
        for (u32 i = 0; i < v->size; i++)\
        {\
            minindex = mapTab[1];\
            mapTab[1] = mapTab[v->size - i];\
            index = 1;\
            for (; (index << 1) <= (v->size - i - 1); index = child)\
            {\
                child = (index << 1);\
                if (child != (v->size - i - 1) && v->compare(&v->data[mapTab[child + 1]], &v->data[mapTab[child]]))\
                {\
                    child++;\
                }\
                if (v->compare(&v->data[mapTab[child]], &v->data[mapTab[v->size - i]]))\
                    mapTab[index] = mapTab[child];\
                else\
                    break;\
            }\
            mapTab[index] = mapTab[v->size - i];\
            mapTab[v->size - i] = minindex;\
        }\
        u8 *sta = (u8 *)malloc(sizeof(u8) * v->size);\
        u32 cnt = 0;\
        T t = {0};\
        u32 start = 0;\
        u32 next = 0;\
        memset(sta, 0, sizeof(u8) * v->size);\
        for (u32 i = v->size; i > 0 && cnt != v->size; i--)\
        {\
            if (sta[v->size - i] == 1)\
                continue;\
            t = v->data[v->size - i];\
            start = v->size - i;\
            next = mapTab[i];\
            while (next != (v->size - i))\
            {\
                v->data[start] = v->data[next];\
                sta[start] = 1;cnt++;\
                start = next;\
                next = mapTab[v->size - next];\
            }\
            v->data[start] = t;\
            sta[start] = 1;cnt++;\
        }\
    free(mapTab);\
    free(sta);\
    }



#define V_SHOW(TypeName) \
    inline void __VCT_showVCT_##TypeName(VCT_##TypeName* v) \
{\
    if(v == NULL || v->toString == NULL)    return ;\
    VPRINTF("this VCT_%s size = %d realsize = %d \n",#TypeName,v->size,v->realsize);\
    for(u32 i = 0;i<v->size;i++) \
    {\
        VPRINTF("\ndata[%d] = ",i);\
        v->toString(v->data+i);\
    }\
}\



//-----------------vector 外部调用 宏定义区域------------//

///< 此宏定义使用在头文件,一定要和 V_Declare_Vector 成对使用,一个在头文件一个在.c文件
///< 且传值要一模一样


#define V_Define(T,TypeName) \
    V_TYPEDEF(T,TypeName) \
    extern VCT_##TypeName* VCT_newVCT_##TypeName(void);\
    extern void VCT_deleteVCT_##TypeName(VCT_##TypeName* v);\
    //


#define V_Declare_Vector(T,TypeName) \
    u8 __VCT_resizeVCT_##TypeName(VCT_##TypeName* v,u32 newsize);\
    u32 __VCT_sizeVCT_##TypeName(VCT_##TypeName* v);\
    T* __VCT_atVCT_##TypeName(VCT_##TypeName* v,u32 index);\
    u8 __VCT_appendVCT_##TypeName(VCT_##TypeName* v,const T d);\
    void __VCT_clearVCT_##TypeName(VCT_##TypeName* v);\
    void __VCT_removelastVCT_##TypeName(VCT_##TypeName* v);\
    void __VCT_removeVCT_##TypeName(VCT_##TypeName* v,u32 starX,u32 lengh);\
    void __VCT_insertVCT_##TypeName(VCT_##TypeName* v,u32 index,const T value);\
    void __VCT_sortVCT_##TypeName(VCT_##TypeName* v);\
    void __VCT_showVCT_##TypeName(VCT_##TypeName* v);\
    V_NEW(TypeName,NULL,NULL,NULL) \
    V_DELETE(TypeName) \
    V_RESIZE(T,TypeName) \
    V_SIZE(TypeName) \
    V_AT(T,TypeName) \
    V_APPEND(T,TypeName) \
    V_CLEAR(TypeName) \
    V_REMOVELAST(TypeName) \
    V_REMOVE(TypeName) \
    V_INSERT(T,TypeName) \
    V_SORT(T,TypeName) \
    V_SHOW(TypeName)\
    //

V_Define(int,int_t)

#endif // CVECTOR_H