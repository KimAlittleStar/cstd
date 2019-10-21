#include "../cvector.h"
#include <stdio.h>
#include <sys/time.h>
typedef char template_t;

V_Define(template_t, DOU_t)
//
V_Declare_Vector(template_t, DOU_t)



V_Define(template_t, uint_t)
//
V_Declare_Vector(template_t, uint_t)

void heapSort(VCT_uint_t *v);
void heapSortInt(VCT_DOU_t *v);
void replace_demo(VCT_uint_t* v,template_t* des,u32 len_d,template_t* src,u32 len_s);
int main_testForSort(void);
int main_testForReplace(void);

int main(void)
{
    main_testForReplace();
    return 0;
}


u8 compaleuint(const template_t *a, const template_t *b)
{
    return *a > *b;
}
u8 compare(const template_t* a,const template_t* b)
{
    return *a<*b;
}
void toStr(const template_t *a)
{
    printf("\t%5d", *a);
}

//bubble sort
void bubol(VCT_uint_t *v)
{
    template_t temp;
    u32 i, j;
    for (i = 0; i < (v->size - 1); i++) /* 外循环为排序趟数，len个数进行len-1趟 */
        for (j = 0; j < (v->size - 1 - i); j++)
        { /* 内循环为每趟比较的次数，第i趟比较len-i次 */
            if (v->data[j] > v->data[j + 1])
            { /* 相邻元素比较，若逆序则交换（升序为左大于右，降序反之） */
                temp = v->data[j];
                v->data[j] = v->data[j + 1];
                v->data[j + 1] = temp;
            }
        }
}

void quicksort(template_t *a, unsigned int n)
{
    unsigned int i, j;
    u32 index = (u32)rand() % n;
    template_t pivot = a[0]; //设置基准值
    a[0] = a[index];
    a[index] = pivot;
    pivot = a[0];
    i = 0;
    j = n - 1;
    while (i < j)
    {
        //大于基准值者保持在原位置
        while (i < j && a[j] > pivot)
        {
            j--;
        }
        if (i < j)
        {
            a[i] = a[j];
            i++;
        }
        //不大于基准值者保持在原位置
        while (i < j && a[i] <= pivot)
        {
            i++;
        }
        if (i < j)
        {
            a[j] = a[i];
            j--;
        }
    }
    a[i] = pivot; //基准元素归位
    if (i > 1)
    {
        //递归地对左子序列 进行快速排序
        quicksort(a, i);
    }
    if (n - i - 1 > 1)
    {
        quicksort(a + i + 1, n - i - 1);
    }
}

void quickSort(VCT_uint_t *v)
{
    quicksort(v->data, v->size);
}

int main_testForSort(void)
{

    VCT_uint_t *test = VCT_newVCT_uint_t();
    test->compare = compaleuint;
    test->toString = toStr;
    struct timeval start, end;

    int number = 100;

    for (int i = 0; i < number; i++)
    {
        test->append(test, (template_t)rand());
    }
    printf("start heap :\n");
    gettimeofday(&start, NULL);
    heapSort(test);
    gettimeofday(&end, NULL);
    int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    printf("over:time: %d us\n", timeuse);
    test->clear(test);

    for (int i = 0; i < number; i++)
    {
        test->append(test, (template_t)rand());
    }
    test->show(test);
    printf("start heap int :\n");
    gettimeofday(&start, NULL);
    test->sort(test);
    gettimeofday(&end, NULL);

    timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    test->show(test);
    printf("over:time: %d us\n", timeuse);
    //--------------------------------------------
    //    test->clear(test);

    //    for(int i = 0;i<number;i++)
    //    {
    //        test->append(test,rand()&0xFFFFFFFFF);
    //    }
    //    printf("start bubel :\n");
    //    gettimeofday( &start, NULL );
    //    bubol(test);
    //    gettimeofday( &end, NULL );

    //    timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;

    //    printf("over:time: %d us\n", timeuse);
    //-----------------------------------------------
    test->clear(test);
    for (int i = 0; i < number; i++)
    {
        //        test->append(test,rand()&0xFFFFFFFFF);
        test->append(test, (template_t)i);
    }
    printf("start quick :\n");
    gettimeofday(&start, NULL);
    quickSort(test);
    //    quickSubSort(d,0,19,0);
    gettimeofday(&end, NULL);

    timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    printf("over:time: %d us\n", timeuse);
    //    test->show(test);

    //    printf("Hello World!\n");
    //    VCT_DOU_t *v = VCT_newVCT_DOU_t();
    //    v->toString = douToStr;
    //    for(int i = 0;i<35;i++)
    //    {
    //        template_t temp;
    //        temp.data = rand()/(rand()+0.1);
    //        v->append(v, temp);
    //    }
    //    v->show(v);

    //    v->compare = compare;

    //    heapSortInt(v);

    //    //    heapSort(v);

    return 0;
}

int main_testForReplace(void)
{
    VCT_uint_t * test = VCT_newVCT_uint_t();
    template_t des[] = "123";
    template_t src[] = "";
    test->compare = compaleuint;
    test->toString = toStr;
    for(int i = 0;i<10;i++)
    {
        test->append(test,'0'+(template_t)i%4);
    }
    test->show(test);
    printf("\n%s\n",test->data);
//    replace_demo(test,des,sizeof (des)/sizeof (des[0])-1,src,0);
    test->replace(test,des,3,src,0);
    test->show(test);
    printf("\n%s\n",test->data);

    return 0;


}

/*
 *
 * 此函数为堆排序的改进版本，使用了一个数组作为数据的映射，使用此数组记住当前位置正确的数据下标是多少；
 * 例如 数组a[0] = 12;即表示 在真正有序的数据中第 [0] 位应该是现在的第12位数据；但是在这里为了节约空间，
 * 将数据的顺序颠倒；也就是说 a[maxsize] 中存放的数字下标就是有序数据的第[0]位；
 *
 * insert delete后，生成的数组就是我们的映射表，这个是依照迭代的思想，从第0位开始，找出第0位应该存放的数据是第n位，
 * 迭代，需要应该在第n位的数据现在在第y位。依次寻找迭代；
 * 由此一定会迭代出一个循环，此时将之前缓存起来的第0位数据放入它应该去的位置，同时，自增，查看第1位，如果第1位已经就绪则继续自增
 * 性能分析；
 * 此方法相对于堆排序，将空间缩减为每个元素只占用5个字节，如果元素类型大小小于5，则使用此方法将浪费空间和时间，
*/
void heapSortInt(VCT_DOU_t *v)
{
    u32 *mapTab = (u32 *)malloc(sizeof(u32) * (v->size + 1));
    //    u32 temp[50] = {0};
    u32 index = 0;
    // insert min
    for (u32 i = 1; i <= v->size; i++)
    {
        index = i;
        for (; index > 1 && v->compare(&v->data[i - 1], &v->data[mapTab[(index >> 1)]]); index >>= 1)
            mapTab[index] = mapTab[index >> 1];
        mapTab[index] = i - 1;
    }
    // delete min
    u32 child = 0;
    u32 minindex;
    for (u32 i = 0; i < v->size; i++)
    {
        minindex = mapTab[1];
        mapTab[1] = mapTab[v->size - i];
        index = 1;
        for (; (index << 1) <= (v->size - i - 1); index = child)
        {
            child = (index << 1);
            if (child != (v->size - i - 1) && compare(&v->data[mapTab[child + 1]], &v->data[mapTab[child]]))
            {
                child++;
            }
            if (compare(&v->data[mapTab[child]], &v->data[mapTab[v->size - i]]))
                mapTab[index] = mapTab[child];
            else
                break;
        }
        mapTab[index] = mapTab[v->size - i];
        mapTab[v->size - i] = minindex;
    }

    //    double t;
    u8 *sta = (u8 *)malloc(sizeof(u8) * v->size);
    //    u8 sta[50] = {0};
    template_t t = {0};
    memset(sta, 0, sizeof(u8) * v->size);
    for (u32 i = v->size; i > 0; i--)
    {
        printf("\n[%d]  %d", i, mapTab[i]);
        if (sta[v->size - i] == 1)
            continue;
        t = v->data[v->size - i];
        u32 start = v->size - i;
        u32 next = mapTab[i];
        while (next != (v->size - i))
        {
            v->data[start] = v->data[next];
            sta[start] = 1;
            start = next;
            next = mapTab[v->size - next];
        }
        v->data[start] = t;
        sta[start] = 1;
    }
    v->show(v);
}
/*  
 * 本函数主要分为3个阶段进行
 * 1. （insert）堆序性质中 a[x] 一定 小于等于 a[2x] 和 a[2x+1],因此将新元素放置到数组末尾，然后使用
 * 上浮，上浮到合适的位置；
 * 2. （delete）堆序性质决定了处于a[1]位置的元素一定是最小的；因此我们将最小的数据取出后，维护这个堆结构
 * 即：将最小的数据取出后将队尾的数据放置到队首，使用下浮，下浮到合适位置；
 * 3. 由于每次delete队首的数据都是最小的，因此我们只需要循环delete即可；
 * Ps* compare(a<b)函数默认 比较的是 return a<b ,如果将其换成a>b 那么所有情况相反，即为降序排列；
*/
void heapSort(VCT_uint_t *v)
{
    //申请合适的空间为其存储 结构类型
    template_t *temp = (template_t *)malloc(sizeof(v->data[0]) * (v->size + 1));
    u32 index = 0;

    // insert min
    for (u32 i = 1; i <= v->size; i++)
    {
        // index 的初始值即为当前数组的队尾；
        index = i;
        // 我们需要插入的数据 data[i-1] 与队列中他的母亲比较大小，如果小则进行迭代
        for (; index > 1 && compare(&v->data[i - 1], temp + (index >> 1)); index >>= 1)
            temp[index] = temp[index >> 1];

        //最后将需要插入的数据放入指定位置
        temp[index] = v->data[i - 1];
    }
    // delete min
    u32 child = 0;
    for (u32 i = 0; i < v->size; i++)
    {                                //循环delete 所有数据
        v->data[i] = temp[1];        //取出队首数据
        temp[1] = temp[v->size - i]; //将队尾数据放入队首
        index = 1;
        for (; (index << 1) <= (v->size - i - 1); index = child) //由于队尾的数据一开始已经放到了队首，因此长度需要-1
        {
            child = (index << 1);
            if (child != (v->size - i - 1) && compare(&temp[child + 1], &temp[child])) //选择教小的子节点作为迭代点
            {
                child++;
            }
            if (compare(&temp[child], &temp[v->size - i]))
                temp[index] = temp[child];
            else
                break;
        }
        temp[index] = temp[v->size - i];
    }
    free(temp);
    //    v->show(v);
}


void replace_demo(VCT_uint_t* v,template_t* des,u32 len_d,template_t* src,u32 len_s)
{
    if(v== NULL || v->compare == NULL || len_d>v->size)  return;
    u8 match_status = 1;
    for(u32 i = 0;i<(v->size-len_d );i++)
    {
        match_status = 1;                   //置位默认为匹配成功
        for(u32 j = 0;j < len_d;j++)
        {
            if(v->compare(v->data+j+i,des+j) != v->compare(des+j,v->data+j+i))
            {
                match_status = 0;
                break;
            }
        }//如果匹配字符成功 那么match_status == 1;
        if(match_status == 1)
        {//匹配字符成功开始替换
            if(len_s > len_d && v->realsize - v->size < (len_s - len_d))
            {
                v->reSize(v,v->realsize*3/2+len_s);
            }
            if(len_s > len_d)   //插入大于原生；向后移动
            {
                for(u32 j = v->size-1;j>=i+len_d;j--)
                    v->data[j+len_s-len_d] = v->data[j];
            }else if(len_d > len_s)
            {//向前移动
                for(u32 j = i+len_s;(j-len_s+len_d)<v->size;j++)
                    v->data[j] = v->data[j-len_s+len_d];
                memset(v->data+v->size-len_d+len_s,0,sizeof(v->data[0]) * (len_d- len_s));
            }
            for(u32 j = 0;j<len_s;j++)
                v->data[i+j] = src[j];
            v->size = v->size + len_s-len_d;
            i+=len_s;
//            else
//            {//相等不需要移动

//            }
        }
    }




}
