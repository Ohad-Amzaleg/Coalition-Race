#include "Simulation.h"
#include"Coalition.h"
#include"Party.h"
#include<vector>

using std::vector;

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents),defaultCoal(),mCoalVec(),numOfCoalition(agents.size()) 
{

    mCoalVec=vector<Coalition>(mAgents.size());

    int numOfAgents=mAgents.size();
    //Intzialize coalition 
    for(int i=0;i<numOfAgents;i++){
        Agent *agent=&mAgents[i];
        Party *party=&mGraph.getParty(agent->getPartyId());

        //Create new coalition
        mCoalVec[i]=Coalition(party->getMandates(),agent->getId(),mGraph.getNumVertices());

        //Set agent and party coalition pointer to the coaliton object
        party->setMCoal(i);
        agent->copyCoaliton(i);

        }

}

void Simulation::step()
{

    //Go over parties
   for(int i=0;i<mGraph.getNumVertices();i++){
       mGraph.getParty(i).step(*this);
   }


        //Go over Agents
   for(Agent &agent :mAgents){
    if(!agent.noOffers())
       agent.step(*this);
   }
  
}

bool Simulation::shouldTerminate() const
{
    bool joined=true;
    for(int i=0;i<mGraph.getNumVertices();i++){
        Party const *party=&mGraph.getParty(i);

        //If there is a coalition with 61 mandates
        //Terminate

        if(party->getState()==Joined && mCoalVec[party->getCoalition()].getSize()>60){
            return true;
        }

        //If all party joined terminate
        if(party->getState()!=State::Joined){
            joined= false;
        }
    }

    return joined;
    }

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

vector<Agent> &Simulation::getAgents()
{
    return mAgents;
}


const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}


Party &Simulation::getParty(int partyId) 
{
    return mGraph.getParty(partyId);
}


vector<Coalition> & Simulation::getCoalitionsVector(){
    return mCoalVec;
}



/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{   

     vector<vector<int>> vec(numOfCoalition);
    //Go over all parties
      for(Agent agent:mAgents){
      int id=agent.getCoalition();
      Party currParty=mGraph.getParty(agent.getPartyId());

        //Push to the coalition vector the party id
        if(currParty.getState()==Joined){
            int partyId=agent.getPartyId();
            vec[id].push_back(partyId);
        }
      }
       
    return vec;
}
