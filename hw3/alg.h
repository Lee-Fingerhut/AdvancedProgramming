//
//  alg.h
//  Ex3_Template
//
//  Created by Lee Fingerhut on 15/12/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//

#pragma once
#include <iostream>
#include <string>
#include <iterator>
using namespace std;

template <class Iter>
bool Fib(Iter begin, Iter end){
    int count=0;
    Iter it = begin;
    while(begin<=end){
        for (int i=2; i<=*begin; i++){
            if (((i-1)+(i-2))== *begin){
                  count++;
                break;
            }
        }
         begin=begin+1;
    }
    
    if((count+1)==(int)distance(it, end)){
        return 0;
    }
    return 1;
}

template <class Iter>
Iter Transpose(Iter begin, Iter end){
    Iter it = begin;
    if(begin == end || distance(begin, end) % 2 == 1){
        return it;
    }
    else{
        while (it < end) {
            if (it + 1 == end)
                break;
            iter_swap(begin, begin + 1);
            begin+=2;
            it = begin;
        }
    }
    return it;
}

template <class Iter, class Iter_other, class Function>
Iter_other Transform2(Iter begin, Iter end, Iter_other otherBegin, Function f){
    if (begin == end || distance(begin, end) % 2 == 1){
        Iter it = end-1;
        while (begin < it) {
            *otherBegin = f(*begin, *(begin + 1));
            otherBegin++;
            begin += 2;
        }
    }
    else{
        while (begin < end) {
            *otherBegin = f(*begin, *(begin + 1));
            otherBegin++;
            begin += 2;
        }
    }
    return otherBegin;
}

