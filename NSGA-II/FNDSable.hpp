//
//  FNDSable.hpp
//  NSGA-II
//
//  Created by Andreas on 2022/11/9.
//

#ifndef FNDSable_hpp
#define FNDSable_hpp

#include <stdio.h>
#include <vector>
using namespace std;
// Fast Nondominated sorting -able.
// The individual must have the following properties.
class FNDSable
{
public:
    vector<double> costs;
    int dominated_count;
    int rank;
    double crowding_distance;
    vector<int> domination_set;
};
#endif /* FNDSable_hpp */
