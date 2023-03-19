#include "JoinPolicy.h"
#include "Party.h"
#include "Simulation.h"
#include "Agent.h"
#include "SelectionPolicy.h"


JoinPolicy:: ~JoinPolicy(){}


//Lastoffer class


//contructor
LastOfferJoinPolicy::LastOfferJoinPolicy():mOffer(-1){}

//destructor
LastOfferJoinPolicy::~LastOfferJoinPolicy(){}


//copy policy
JoinPolicy* LastOfferJoinPolicy::copyMyPolicy(){
return new LastOfferJoinPolicy();
}






void LastOfferJoinPolicy::join(Party &party,Simulation &sim) {
    Agent *offer=&sim.getAgents()[mOffer];

    
   Coalition *coal=&sim.getCoalitionsVector()[offer->getCoalition()];

   int oldSize=party.getMandates();
   int newSize=coal->getSize();

   //Set new coalition
   party.setMCoal(coal->getId());

   //Set new size after union
    coal->setSize(oldSize+newSize);

   //Change state of the party
   party.setState(Joined);
   

    //clone agent
    Agent agent( sim.getAgents().size(),party.getMId(),offer->getMSelectionPolicy()->copyMyPolicy());

    
   
    //Take referens of this coalition
    agent.copyCoaliton(coal->getId());

   sim.getAgents().push_back(agent);
}



void LastOfferJoinPolicy:: policyAddOffer(Agent *agent,Simulation &sim){
    mOffer=agent->getId();;
}






//Mandate class


MandatesJoinPolicy::~MandatesJoinPolicy(){}

MandatesJoinPolicy:: MandatesJoinPolicy():mOffer(-1){}


//copy policy
JoinPolicy* MandatesJoinPolicy::copyMyPolicy(){
return new MandatesJoinPolicy();
}





void MandatesJoinPolicy::join(Party &party,Simulation &sim) {
 Agent *offer=&sim.getAgents()[mOffer];

    
   Coalition *coal=&sim.getCoalitionsVector()[offer->getCoalition()];

   int oldSize=party.getMandates();
   int newSize=coal->getSize();

   //Set new coalition
   party.setMCoal(coal->getId());

   //Set new size after union
    coal->setSize(oldSize+newSize);

   //Change state of the party
   party.setState(Joined);
   
   

    Agent agent( sim.getAgents().size(),party.getMId(),offer->getMSelectionPolicy()->copyMyPolicy());

    
    //Take referens of this coalition
    agent.copyCoaliton(coal->getId());

   sim.getAgents().push_back(agent);

}


void MandatesJoinPolicy::policyAddOffer(Agent *agent,Simulation &sim) {
//First offer
        if (mOffer == -1) {
            mOffer =agent->getId();;
        }

//Take bigger mandates offer
        else {
            Agent *offer=&sim.getAgents()[mOffer];
            int lastOffer = sim.getCoalitionsVector()[offer->getCoalition()].getSize();
            int newOffer =  sim.getCoalitionsVector()[agent->getCoalition()].getSize();
            if (newOffer > lastOffer) {
                mOffer = agent->getId();
            }
        }
    }

