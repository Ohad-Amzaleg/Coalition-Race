#pragma once
#include <map>
#include <vector>
#include "Simulation.h"

using std::map;
using std::vector;

class SelectionPolicy {
    public:
    virtual int select(vector<vector<int>> &ng,Simulation &sim,vector<bool> *mOffered)=0;
    virtual ~SelectionPolicy();
    virtual SelectionPolicy* copyMyPolicy()=0;

 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
    public:
        virtual int select(vector<vector<int>> &ng,Simulation &sim,vector<bool> *mOffered);
         ~MandatesSelectionPolicy();
         virtual SelectionPolicy* copyMyPolicy();


};


class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
        virtual int select(vector<vector<int>> &ng,Simulation &sim,vector<bool> *mOffered);
        ~EdgeWeightSelectionPolicy();
        virtual SelectionPolicy* copyMyPolicy();


 };