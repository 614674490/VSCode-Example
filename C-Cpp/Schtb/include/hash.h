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
//开放定址哈希表的存储结构
extern int *hashsize;  //素数索引表
typedef struct
{
    NodeType *elem;     //数据元素存储基址
    int count;          //当前数据元素个数
    int mod;            //模值
    int sizeindex;      //hasesize[sizeindex]为当前容量 0除外
    int length;         //表长
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
