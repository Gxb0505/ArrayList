//线性表ArrayList.cpp : 定义控制台应用程序的入口点。
//优点：在于随机访问元素，
//缺点：插入和和删除的时候，需要移动大量的元素。
//

#include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

/*宏定义*/
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1  
#define OVERFLOW -2  

#define LT(a,b)   ((a)<(b))  
#define N = 100  

#define LIST_INIT_SIZE 100 //线性初始空间分配量
#define LISTINCREMENT 10 //线性表空间分配的增量

/*别名定义*/
typedef int Status;
typedef int ElemType;


typedef struct SqList{
  ElemType *elem;    //存储空间的基地址
  int length;        //当前的长度
  int listsize;      //当前分配的存储容量
}SqList;             //线性表

/*初始化链表*/
Status initList(SqList &L,int length){
  if (length == 0)length = LIST_INIT_SIZE;
  L.elem=(ElemType *)malloc(length* sizeof(ElemType));
  if (!L.elem)exit(OVERFLOW);//分配存储空间失败
  L.length = 0;              //初始空表长度为0
  L.listsize=length;         //当前存储容量为100  
  return OK;
}


//插入元素，长度+1
Status insertList(SqList &L, ElemType e,int i){
  ElemType *p,*q;
  if (i<0 || i>L.length)return ERROR;

  if (L.length>=L.listsize)
  {
    ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
    if (!newbase) return OVERFLOW;   //存储分配失败    
    L.elem = newbase;               //新基值  
    L.listsize += LISTINCREMENT;    //增加存储容量  
  }
  q = &L.elem[i];                     //q为插入的位置  
  for (p = &L.elem[L.length]; p >= q; --p) {
    *p = *(p - 1);                    //i元素之后的元素往后移动  
  }
  *q = e;                             //插入e  
  L.length += 1;
  return OK;
}

/************************************************************************/
/* 快速排序
*/
/************************************************************************/
void sortList(SqList &L){


}

/************************************************************************/
/* 删除第i位置元素，并用e返回其值                                                                     */
/************************************************************************/
Status deleteListElem(SqList &L, int i, ElemType &e){
  int *p, *q;
  if (i<0 || i > L.length) return ERROR;  //i值不合法  
  q = &L.elem[i];                       //被删除元素的位置为i，L.elem就是数组名,  
  e = *q;                               //被删除元素的值赋值给e  
  for (p = q; p< (L.elem + L.length); p++){ //元素左移  
    *p = *(p + 1);
  }
  --L.length;
  return OK;
}

int partition(SqList &L, ElemType low, ElemType high){
  ElemType pivotkey = L.elem[low];               //枢轴记录关键字  
  while (low < high) {                  //从表的两端向中间扫描  
    while (low < high &&  L.elem[high] >= pivotkey) --high;//高端位置扫描  
    L.elem[low] = L.elem[high];     //交换数据，小于pivotkey移到低端  
    L.elem[high] = pivotkey;

    while (low < high && L.elem[low] <= pivotkey) ++low;     //低端扫描  
    L.elem[high] = L.elem[low];               //交换数据 大于pivotkey移到高端  
    L.elem[low] = pivotkey;
  }
  return low;
}

void quickSort(SqList &L, ElemType low, ElemType high){
  int pivot;
  if (low < high) {
    pivot = partition(L, low, high);
    quickSort(L, low, pivot - 1);          //低端子表排序  
    quickSort(L, pivot + 1, high);          //高端子表排序  
  }

}

/************************************************************************/
/*
合并两个线性表
*/
/************************************************************************/

void mergeList(SqList La, SqList Lb, SqList &Lc){
  ElemType *pa, *pb, *pc;
  Lc.listsize = La.length + Lb.length;
  initList(Lc, Lc.listsize);          //初始化LC\pc = Lc.elem;  
  Lc.length = Lc.listsize;
  pc = Lc.elem;
  pa = La.elem;
  pb = Lb.elem;
  while (pa <= &La.elem[La.length - 1] && pb <= &Lb.elem[Lb.length - 1]){
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= &La.elem[La.length - 1]) *pc++ = *pa++; //插入La的剩余元素  
  while (pb <= &Lb.elem[Lb.length - 1]) *pc++ = *pb++; //插入Lb的剩余元素  

}

/************************************************************************/
/* 打印list
*/
/************************************************************************/
void printList(SqList L){
  printf("当前值:");
  for (int i = 0; i<L.length; i++) {
    printf("%d ", *(L.elem + i)); // L.elem为首地址  
  }
  printf("\r\n");
}

void main()
{
  SqList La, Lb, Lc;
  ElemType e;
  int init, i;
  init = initList(La, LIST_INIT_SIZE);
  int data[6] = { 5, 3, 6, 2, 7, 4 };
  for (i = 0; i<6; i++) {
    insertList(La, data[i], i);
  }
  printf("LA:\r\n");
  printList(La);
  deleteListElem(La, 3, e);
  printList(La);
  insertList(La, e, 3);
  printList(La);

  //排序  
  quickSort(La, 0, La.length - 1);
  printList(La);

  printf("LB:\r\n");
  initList(Lb, LIST_INIT_SIZE);
  int Bdata[5] = { 1, 3, 2, 4, 6 };
  for (i = 0; i<5; i++) {
    insertList(Lb, Bdata[i], i);
  }
  //排序  
  quickSort(Lb, 0, Lb.length - 1);
  printList(Lb);

  mergeList(La, Lb, Lc);
  printList(Lc);

}
