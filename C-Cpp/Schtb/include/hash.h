/*
 * @Author: liguiyin
 * @Date: 2019-11-26 22:18:02
 * @LastEditTime: 2019-11-29 20:51:53
 * @Description: README
 * @FilePath: \Schtb\include\hash.h
 */
#ifndef _hash_h
#define _hash_h
#include "config.h"
#include "schtb.h"

#define NULLKEY Random_Range
#define Duplivate_Threshold 10
//���Ŷ�ַ��ϣ��Ĵ洢�ṹ
extern int *hashsize;  //����������
typedef struct
{
    NodeType *elem;     //����Ԫ�ش洢��ַ
    int count;          //��ǰ����Ԫ�ظ���
    int mod;            //ģֵ
    int sizeindex;      //hasesize[sizeindex]Ϊ��ǰ���� 0����
    int length;         //��
}HashTable;

#define SUCCESS     1
#define UNSUCCESS   0
#define DUPLICATE   -1

Status isPrime(int key);
int *prime(int n);
Status Init_HashTable(HashTable *H, int sizeindex);
int Hash(HashTable H, KeyType key);
int collision(HashTable H, KeyType Key, int dupcount);
Status _Search_Hash(HashTable H, KeyType Key, int *pos, int *c);
Status Insert_HashTable(HashTable *H, NodeType e);
Status Creat_HashTable(HashTable *H);
int Search_Hash(HashTable H, KeyType Key);
Status Del_HashTable(HashTable H, KeyType Key);
void print_HashTable(HashTable H);
#endif
