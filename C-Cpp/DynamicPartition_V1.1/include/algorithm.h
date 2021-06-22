/*
 * @Author: Ken Kaneki
 * @Date: 2020-06-01 23:40:02
 * @LastEditTime: 2020-06-12 11:17:40
 * @Description: README
 * @FilePath: \DynamicPartition_V1.0\include\algorithm.h
 */
#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "Linkedlist.h"
#include <time.h>
#include <vector>

bool first(LinkedList *S, vector<vector<int>> &cache);

bool loopfirst(LinkedList *S, vector<vector<int>> &cache);

bool best(LinkedList *S, vector<vector<int>> &cache, int mode);

bool worst(LinkedList *S, vector<vector<int>> &cache);

void recovery(LinkedList *L, vector<vector<int>> &cache);
#endif
