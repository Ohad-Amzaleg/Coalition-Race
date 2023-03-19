#pragma once

#include <vector>
#include "Graph.h"
#include "Coalition.h"

class SelectionPolicy;

class Agent
{
public:
    Agent();
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    bool noOffers();
    int getCoalition() ;
    SelectionPolicy *getMSelectionPolicy() const;

    //Rule of 5
    virtual~Agent();
    Agent(const Agent &other);
    Agent(Agent &&other);
    Agent& operator=(const Agent &other);
    Agent& operator=(Agent &&other);


    //Nighbors in the graph
    vector<vector<int>> calculNighbors(Graph graph);

    //Copy Coalition for the new clone agent 
    void copyCoaliton(int coalId);

private:
    int mAgentId;
    int mPartyId;
    int mCoalId;
    bool outOfOffers;
    SelectionPolicy *mSelectionPolicy;
    vector<vector<int>> mNieghbors;
};
