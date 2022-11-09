//
//  nsga2.hpp
//  NSGA-II
//
//  Created by Andreas on 2022/11/8.
//

#ifndef nsga2_hpp
#define nsga2_hpp

#include <vector>
#include <math.h>
#include "FNDSable.hpp"
using namespace std;
class NSGA2
{
private:
    bool isDominance(vector<double>, vector<double>);
    vector<vector<int>> pareto(vector<FNDSable> &individuals);
    void crowding_distance(vector<FNDSable> &individuals, vector<vector<int>> pareto_sets);
    vector<int> sort_indexs(const vector<double> &cost);
public:
    void sort_solution(vector<FNDSable> &individuals);
};
#endif /* nsga2_hpp */
