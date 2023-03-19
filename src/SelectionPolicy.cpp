#include <vector>
#include <map>
#include "SelectionPolicy.h"
#include "Party.h"
#include "Simulation.h"
using std::map;
using std::vector;

SelectionPolicy::~SelectionPolicy(){}

MandatesSelectionPolicy::~MandatesSelectionPolicy(){}

//copy policy
SelectionPolicy* MandatesSelectionPolicy::copyMyPolicy(){
return new MandatesSelectionPolicy();
}


int  MandatesSelectionPolicy::select(vector<vector<int>> &ng,Simulation &sim,vector<bool> *mOffered) {
    
    int maxPartyId=-1;
    int maxMandate=-1;
    int numOfnieghbors=ng[0].size();

    for(int i =0;i<numOfnieghbors;i++){
        Party currParty=sim.getParty(ng[0][i]);
        int tmpMandate=currParty.getMandates();

        //Check if our coalition didnt offer to this party yet
        //Check if the party not in Joined state
        //Check if the party is the party with the biggest mandate

        if(tmpMandate>maxMandate && !(*mOffered)[ng[0][i]] && (currParty.getState()!=Joined) ){
            maxPartyId=ng[0][i];
            maxMandate=tmpMandate;
        }
    }
    return maxPartyId;
}


EdgeWeightSelectionPolicy::~EdgeWeightSelectionPolicy(){}


//copy policy
SelectionPolicy* EdgeWeightSelectionPolicy::copyMyPolicy(){
return new EdgeWeightSelectionPolicy();

}



int EdgeWeightSelectionPolicy::select(vector<vector<int>> &ng, Simulation &sim,vector<bool> *mOffered) {
    int maxPartyId=-1;
    int maxWeight=-1;
    int numOfnieghbors=ng[0].size();

    for(int i =0;i<numOfnieghbors;i++){
        int currPartyId=ng[0][i];
        int currWeight=ng[1][i];
        Party *pParty=&sim.getParty(currPartyId);

        if(currWeight>maxWeight && !(*mOffered)[currPartyId] & (pParty->getState()!=Joined) ){
            maxPartyId=ng[0][i];
            maxWeight=ng[1][i];
        }
    }
    return maxPartyId;
}

