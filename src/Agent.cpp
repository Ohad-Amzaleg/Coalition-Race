#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Coalition.h"
#include <vector>

using std::vector;

Agent::Agent():mAgentId(), mPartyId(),mCoalId(-1),outOfOffers(false),mSelectionPolicy(),mNieghbors(){}

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),mCoalId(-1),outOfOffers(false),mSelectionPolicy(selectionPolicy),mNieghbors()
{
}


Agent::~Agent(){
    if(mSelectionPolicy){
        delete mSelectionPolicy;
    }
}

Agent::Agent(const Agent &other):Agent(){
    mAgentId=other.mAgentId;
    mPartyId=other.mPartyId;
    outOfOffers=other.outOfOffers;
    mCoalId=other.mCoalId;
    mNieghbors=other.mNieghbors;

mSelectionPolicy=other.mSelectionPolicy->copyMyPolicy();


}

Agent::Agent(Agent &&other):Agent(){
    mNieghbors=other.mNieghbors;
    mAgentId=other.mAgentId;
    mPartyId=other.mPartyId;
    mSelectionPolicy=other.mSelectionPolicy;
    mCoalId=other.mCoalId;
    outOfOffers=other.outOfOffers;

    other.mSelectionPolicy=nullptr;

}


Agent& Agent::operator=(const Agent &other){
    if(this==&other)
    return *this;

    delete mSelectionPolicy;
    mAgentId=other.mAgentId;
    mPartyId=other.mPartyId;
    mCoalId=other.mCoalId;
    outOfOffers=other.outOfOffers;
    mNieghbors=other.mNieghbors;

    
mSelectionPolicy=other.mSelectionPolicy->copyMyPolicy();


    return *this;
}


Agent& Agent:: operator=(Agent &&other){
if(this==&other)
return *this;

delete mSelectionPolicy;

mAgentId=other.mAgentId;
mPartyId=other.mPartyId;
mSelectionPolicy=other.mSelectionPolicy;
mCoalId=other.mCoalId;
mNieghbors=other.mNieghbors;
outOfOffers=other.outOfOffers;

other.mSelectionPolicy=nullptr;

return *this;

}



SelectionPolicy *Agent::getMSelectionPolicy() const {
    return mSelectionPolicy;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalition(){
    return mCoalId;
}

void Agent::copyCoaliton(int coalId){
 mCoalId=coalId;
}


bool Agent::noOffers()
{
    return outOfOffers;
}



vector<vector<int>> Agent ::calculNighbors(Graph Graph){
    vector<vector<int>> Nighbors;
    vector<int> partyId;
    vector<int> edgeWeight;
    for (int i = 0; i < Graph.getNumVertices(); i++){
        int EdgeWeight = Graph.getEdgeWeight((*this).getPartyId(), i);
        if (EdgeWeight != 0){
            edgeWeight.push_back(EdgeWeight);
            partyId.push_back(i);
        }
    }

    Nighbors.push_back(partyId);
    Nighbors.push_back(edgeWeight);

    return Nighbors;
}






void Agent::step(Simulation &sim) {
    //Get neighbors
    if (mNieghbors.empty()) {
        mNieghbors = calculNighbors(sim.getGraph());
    }

    //Select party to offer
    int partyId=mSelectionPolicy->select(mNieghbors,sim,sim.getCoalitionsVector()[mCoalId].getOffered());
    
    if(partyId ==-1)
        outOfOffers=true;

    if(!outOfOffers){
    Party *nextToOffer=&sim.getParty(partyId);

    //Update the offer in the party offers
    nextToOffer->partyAddOffer(this,sim);
    
    if(nextToOffer->getState()==Waiting)
    //Change State
    nextToOffer->setState(CollectingOffers);

    //Update that we offered to this party already
    sim.getCoalitionsVector()[mCoalId].addOldOffer(*nextToOffer);


    }
}

