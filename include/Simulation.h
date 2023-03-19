#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

class Coalition;
using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    vector<Coalition> & getCoalitionsVector();
    vector<Agent> &getAgents();
    Party & getParty(int partyId);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    Coalition defaultCoal;
     vector<Coalition> mCoalVec;
    int numOfCoalition;
};
