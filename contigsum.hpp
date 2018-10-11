#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

#include <iterator>
#include <iostream>

using std::distance;
using std::advance;

struct gcsSums
{
    int GCS=0; 
    int lGCS=0;
    int rGCS=0;
    int sum=0;
};

template<typename RAIter>
gcsSums recurseSum(RAIter first, RAIter last){
    size_t size = distance(first, last);
    gcsSums sums;
    if (size == 1)
    {
        sums.GCS = *first > 0 ? *first : 0;
        sums.lGCS = *first > 0 ? *first : 0;
        sums.rGCS = *first > 0 ? *first : 0;
        sums.sum = *first;
    }
    else if (size > 1)
    {
        auto middle = first;
        advance(middle, size/2);
        auto lSums = recurseSum(first, middle);
        auto rSums = recurseSum(middle, last);

        sums.sum = lSums.sum + rSums.sum;
        sums.lGCS = lSums.sum + rSums.lGCS > lSums.lGCS 
            ? lSums.sum + rSums.lGCS : lSums.lGCS;
        sums.rGCS = rSums.sum + lSums.rGCS > rSums.rGCS 
            ? rSums.sum + lSums.rGCS : rSums.rGCS;
        sums.GCS = lSums.GCS > rSums.GCS ? 
            (lSums.GCS > lSums.rGCS + rSums.lGCS ? lSums.GCS : lSums.rGCS + rSums.lGCS):
            (rSums.GCS > lSums.rGCS + rSums.lGCS ? rSums.GCS : lSums.rGCS + rSums.lGCS);
    }
    return sums;
}

template<typename RAIter>
int contigSum(RAIter first, RAIter last){
    gcsSums returnSums = recurseSum(first, last);
    return returnSums.GCS;
}

#endif /* CONTIGSUM_HPP */