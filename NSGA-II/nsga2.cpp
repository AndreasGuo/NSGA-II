//
//  nsga2.cpp
//  NSGA-II
//
//  Created by Andreas on 2022/11/8.
//

#include "nsga2.hpp"
#include <algorithm>
bool NSGA2::isDominance(vector<double> a, vector<double> b){
    // according to the concept
    // each cost in a not greater than b
    // and at lest one cost in a less than b
    // But in the real world, it dose not render disparage,
    // <= will produce more rank that (almost) do not effect sort order.
    return (a<=b)&&!(a==b);
}

vector<vector<int>> NSGA2::pareto(vector<FNDSable> &individuals){
    // A rank Set in each vector<FNDSable>.
    vector<vector<int>> pareto_sets = vector<vector<int>>();
    // clear Domininantion information.
    vector<FNDSable>::iterator individual;
    for(individual=individuals.begin(); individual!=individuals.end(); individual++){
        (*individual).domination_set = vector<int>();
        (*individual).dominated_count = 0;
    }
    
    // Rank0
    vector<int> rank1 = vector<int>();
    for(int i=0; i<individuals.size(); i++){
        for(int j=i+1; j<individuals.size(); j++){
            if(isDominance(individuals[i].costs, individuals[j].costs)){
                individuals[i].domination_set.push_back(j);
                individuals[j].dominated_count += 1;
            }
            else if(isDominance(individuals[j].costs, individuals[i].costs)){
                individuals[j].domination_set.push_back(i);
                individuals[i].dominated_count += 1;
            }
        }
        if(individuals[i].dominated_count == 0){
            rank1.push_back(i);
            individuals[i].rank = 0;
        }
    }
    pareto_sets.push_back(rank1);
    
    // Rank 1,2,3,4...
    int k=0;
    while(true){
        vector<int> rank_set = vector<int>();
        vector<int>::iterator i,j;
        for(i=pareto_sets[k].begin(); i!=pareto_sets[k].end(); i++){
            for(j=individuals[*i].domination_set.begin(); j!=individuals[*i].domination_set.end(); j++){
                if((--individuals[*j].dominated_count)==0){
                    rank_set.push_back(*j);
                    individuals[*j].rank=k+1;
                }
            }
        }
        if(rank_set.empty()) break;
        pareto_sets.push_back(rank_set);
        ++k;
    }
    
    return pareto_sets;
}

vector<int> NSGA2::sort_indexs(const vector<double> &cost){
    vector<int> idx(cost.size());
    for(int i=0; i<idx.size(); i++) idx[i]=i;
    sort(idx.begin(), idx.end(),
         [&cost](int i1, int i2){return cost[i1]<cost[i2];});
    return idx;
}

void NSGA2::crowding_distance(vector<FNDSable> &individuals, vector<vector<int>> pareto_sets){
    unsigned long object_size = individuals[0].costs.size();
    vector<vector<int>>::iterator rank_set;
    vector<int>::iterator i;
    for(rank_set=pareto_sets.begin(); rank_set!=pareto_sets.end(); rank_set++){
            for(unsigned long j=0; j<object_size; j++){
                // j is the object index: cost1, cost2...
                vector<double> cost = vector<double>(); //same object in a rank.
                for(i=(*rank_set).begin(); i!=(*rank_set).end(); i++){
                    // i is individuals' index;
                    cost.push_back(individuals[*i].costs[j]);
                }
                vector<int> arg_idx = sort_indexs(cost);
                // crowding distance of first and last is INF
                // rank_set[arg_idx] is the index of individuals
                individuals[(*rank_set)[arg_idx[0]]].crowding_distance = INFINITY;
                for(int k=1; k<cost.size()-1; k++){
                    individuals[(*rank_set)[arg_idx[k]]].crowding_distance
                    += (cost[arg_idx[k+1]] - cost[arg_idx[k-1]])
                        / (cost[cost.size()-1] - cost[0]);
                }
                individuals[(*rank_set)[arg_idx[arg_idx.size()-1]]].crowding_distance = INFINITY;
        }
    }
}

void NSGA2::sort_solution(vector<FNDSable> &individuals){
    auto pareto_sets = pareto(individuals);
    crowding_distance(individuals, pareto_sets);
    sort(individuals.begin(), individuals.end(),
         [&individuals](FNDSable i1, FNDSable i2){return
            (i1.rank<i2.rank)|| 
            (i1.rank==i2.rank && i1.crowding_distance > i2.crowding_distance);});
}
