//���Ա�ArrayList.cpp : �������̨Ӧ�ó������ڵ㡣
//�ŵ㣺�����������Ԫ�أ�
//ȱ�㣺����ͺ�ɾ����ʱ����Ҫ�ƶ�������Ԫ�ء�
//

#include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

/*�궨��*/
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1  
#define OVERFLOW -2  

#define LT(a,b)   ((a)<(b))  
#define N = 100  

#define LIST_INIT_SIZE 100 //���Գ�ʼ�ռ������
#define LISTINCREMENT 10 //���Ա�ռ���������

/*��������*/
typedef int Status;
typedef int ElemType;


typedef struct SqList{
  ElemType *elem;    //�洢�ռ�Ļ���ַ
  int length;        //��ǰ�ĳ���
  int listsize;      //��ǰ����Ĵ洢����
}SqList;             //���Ա�

/*��ʼ������*/
Status initList(SqList &L,int length){
  if (length == 0)length = LIST_INIT_SIZE;
  L.elem=(ElemType *)malloc(length* sizeof(ElemType));
  if (!L.elem)exit(OVERFLOW);//����洢�ռ�ʧ��
  L.length = 0;              //��ʼ�ձ���Ϊ0
  L.listsize=length;         //��ǰ�洢����Ϊ100  
  return OK;
}


//����Ԫ�أ�����+1
Status insertList(SqList &L, ElemType e,int i){
  ElemType *p,*q;
  if (i<0 || i>L.length)return ERROR;

  if (L.length>=L.listsize)
  {
    ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
    if (!newbase) return OVERFLOW;   //�洢����ʧ��    
    L.elem = newbase;               //�»�ֵ  
    L.listsize += LISTINCREMENT;    //���Ӵ洢����  
  }
  q = &L.elem[i];                     //qΪ�����λ��  
  for (p = &L.elem[L.length]; p >= q; --p) {
    *p = *(p - 1);                    //iԪ��֮���Ԫ�������ƶ�  
  }
  *q = e;                             //����e  
  L.length += 1;
  return OK;
}

/************************************************************************/
/* ��������
*/
/************************************************************************/
void sortList(SqList &L){


}

/************************************************************************/
/* ɾ����iλ��Ԫ�أ�����e������ֵ                                                                     */
/************************************************************************/
Status deleteListElem(SqList &L, int i, ElemType &e){
  int *p, *q;
  if (i<0 || i > L.length) return ERROR;  //iֵ���Ϸ�  
  q = &L.elem[i];                       //��ɾ��Ԫ�ص�λ��Ϊi��L.elem����������,  
  e = *q;                               //��ɾ��Ԫ�ص�ֵ��ֵ��e  
  for (p = q; p< (L.elem + L.length); p++){ //Ԫ������  
    *p = *(p + 1);
  }
  --L.length;
  return OK;
}

int partition(SqList &L, ElemType low, ElemType high){
  ElemType pivotkey = L.elem[low];               //�����¼�ؼ���  
  while (low < high) {                  //�ӱ���������м�ɨ��  
    while (low < high &&  L.elem[high] >= pivotkey) --high;//�߶�λ��ɨ��  
    L.elem[low] = L.elem[high];     //�������ݣ�С��pivotkey�Ƶ��Ͷ�  
    L.elem[high] = pivotkey;

    while (low < high && L.elem[low] <= pivotkey) ++low;     //�Ͷ�ɨ��  
    L.elem[high] = L.elem[low];               //�������� ����pivotkey�Ƶ��߶�  
    L.elem[low] = pivotkey;
  }
  return low;
}

void quickSort(SqList &L, ElemType low, ElemType high){
  int pivot;
  if (low < high) {
    pivot = partition(L, low, high);
    quickSort(L, low, pivot - 1);          //�Ͷ��ӱ�����  
    quickSort(L, pivot + 1, high);          //�߶��ӱ�����  
  }

}

/************************************************************************/
/*
�ϲ��������Ա�
*/
/************************************************************************/

void mergeList(SqList La, SqList Lb, SqList &Lc){
  ElemType *pa, *pb, *pc;
  Lc.listsize = La.length + Lb.length;
  initList(Lc, Lc.listsize);          //��ʼ��LC\pc = Lc.elem;  
  Lc.length = Lc.listsize;
  pc = Lc.elem;
  pa = La.elem;
  pb = Lb.elem;
  while (pa <= &La.elem[La.length - 1] && pb <= &Lb.elem[Lb.length - 1]){
    if (*pa <= *pb) *pc++ = *pa++;
    else *pc++ = *pb++;
  }
  while (pa <= &La.elem[La.length - 1]) *pc++ = *pa++; //����La��ʣ��Ԫ��  
  while (pb <= &Lb.elem[Lb.length - 1]) *pc++ = *pb++; //����Lb��ʣ��Ԫ��  

}

/************************************************************************/
/* ��ӡlist
*/
/************************************************************************/
void printList(SqList L){
  printf("��ǰֵ:");
  for (int i = 0; i<L.length; i++) {
    printf("%d ", *(L.elem + i)); // L.elemΪ�׵�ַ  
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

  //����  
  quickSort(La, 0, La.length - 1);
  printList(La);

  printf("LB:\r\n");
  initList(Lb, LIST_INIT_SIZE);
  int Bdata[5] = { 1, 3, 2, 4, 6 };
  for (i = 0; i<5; i++) {
    insertList(Lb, Bdata[i], i);
  }
  //����  
  quickSort(Lb, 0, Lb.length - 1);
  printList(Lb);

  mergeList(La, Lb, Lc);
  printList(Lc);

}
