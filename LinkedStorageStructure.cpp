/* 链式存储结构 */
#include <iostream>
using namespace std;

/*存储空间分配初始分配量*/
#define MAXSIZE 20
/* ElemType类型根据实际情况而定，这里假设为int */
typedef int ElemType;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* Status是函数的类型，其值是函数结果状态代码，如OK等 */
typedef int Status;

/* 线性表的单链表存储结构 */

/*定义Node*/
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

/* 定义LinkedList */
typedef struct Node *LinkList;

/*单链表的读取*/
/*
获得第i个数据GetElem()
算法思路：
1.声明一个指针p指向链表第1个结点，初始化j从1开始；
2.当j<i,就遍历链表，让p指针向后移动，不断指向下一结点，j累加1；
3.若到链表末尾p为空，则说明第i个结点不存在；
4.否则查找成功，返回结点p的数据。
*/
/*
初始条件：顺序线性表L已存在，1 <= i <= ListLength(L);
操作结果：用e返回L中第i个元素的值。
*/
Status GetElem(LinkList L, int i, ElemType *e)
{
    /* j为计数器 */
    int j = 1;
    /*声明一个指针p*/
    LinkList p;
    /* 让p指向链表L的第一个结点 */
    p = L->next;
    while (p && j < i)
    {
        /*让p指向下一个结点*/
        p = p->next;
        ++j;
    }
    if (!p || j > i)
    {
        /*第i个结点不存在*/
        return ERROR;
    }
    /*取第i个结点的数据*/
    *e = p->data;
    return OK;
}

/*
单链表的插入操作ListInsert()
算法思路：
1.声明一指针p指向链表头结点，初始化j从1开始；
2.当j<i时，就遍历链表，让p的指针向后移动，不断指向下一结点，j累加1；
3.若到链表末尾p为空，则说明第i个结点不存在；
4.否则查找成功，在系统中生成一个空结点s；
5.将数据元素e赋值给s->data;
6.单链表的插入标准语句
s->next = p->next;
p->next = s;
7.返回成功。
*/
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j = 1;
    LinkList p, s;
    p = *L;
    //寻找第i-1个结点
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    //第i个结点不存在
    if (!p || j > i)
    {
        return ERROR;
    }
    //生成新结点（C标准函数）
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    //将p的后继结点赋值给s的后继
    s->next = p->next;
    //将s赋值给p的后继
    p->next = s;
    return OK;
}

/*
单链表的删除操作ListDelete()
算法思路：
1.声明一指针p指向链表头指针，初始化j从1开始；
2.当j<i时遍历链表，让p指针向后移动，不断指向下一个结点，j累加1；
3.若到链表末尾p为空，说明第i个结点不存在；
4.否则查找成功，将欲删除的结点p->next赋值给q；
5.单链表的标准删除语句
p->next = q->next;
6.将q结点中数据赋值给e，作为返回；
7.释放q结点；
8.返回成功；
*/
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j = 1;
    LinkList q, p;
    p = *L;
    //遍历寻找第i-1个结点
    while (p->next && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p->next || j > i)
    {
        //第i个结点不存在
        return ERROR;
    }
    q = p->next;
    //将q的后继赋值给p的后继
    p->next = q->next;
    //将q结点中的数据给e
    *e = q->data;
    //让系统回收此结点，释放内存
    free(q);
    return OK;
}

int main()
{
    LinkList l;
    int *p = (int *)malloc(sizeof(int));
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4;
    ListInsert(&l, 1, x1);
    ListInsert(&l, 2, x2);
    ListInsert(&l, 3, x3);
    GetElem(l, 2, p);
    cout << "链表中第2个元素为" << *p << endl;
    cout << "------删除后------" << endl;
    ListDelete(&l, 2, p);
    GetElem(l, 2, p);
    cout << "链表中第2个元素为" << *p << endl;
    free(p);
    return 0;
}