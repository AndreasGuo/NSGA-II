//
//  main.cpp
//  NSGA-II
//
//  Created by Andreas on 2022/11/8.
//

#include <iostream>
#include <vector>
#include "nsga2.hpp"

int main(int argc, const char * argv[]) {
    auto a = std::vector<FNDSable>();
    NSGA2 nsga = NSGA2();
    for(int i=0; i<20; i++){
        auto f = FNDSable();
        f.costs = {double(i%7), double(i%2)};
        a.push_back(f);
    }
    nsga.sort_solution(a);
    
    std::vector<FNDSable>::iterator f;
    for(f=a.begin(); f!=a.end(); f++){
        std::cout<<"cost: "<<(*f).costs[0]<<" "<<(*f).costs[1] << " rank: "<<(*f).rank<< std::endl;
    }
    return 0;
}
