#pragma once
#include "Agent.h"
class Simulation;
class Party;

class JoinPolicy {
    public:
    virtual void join(Party &party,Simulation &sim)=0;
    virtual void policyAddOffer(Agent *agent,Simulation &sim)=0;
    virtual int  getMOffer()=0;
    virtual~JoinPolicy();
    virtual JoinPolicy* copyMyPolicy()=0;

};

class MandatesJoinPolicy : public JoinPolicy {
    public:
    MandatesJoinPolicy();
    virtual void join(Party &party,Simulation &sim);
    virtual void policyAddOffer(Agent *agent,Simulation &sim);
    virtual int  getMOffer(){return mOffer;};
    ~MandatesJoinPolicy();
    virtual JoinPolicy* copyMyPolicy();


    private:
    int mOffer;

};



class LastOfferJoinPolicy : public JoinPolicy {
    public:
    LastOfferJoinPolicy ();
    virtual void join(Party &party,Simulation &sim);
    virtual void policyAddOffer(Agent *agent,Simulation &sim);
    virtual int getMOffer(){return mOffer;};
    ~LastOfferJoinPolicy();
    virtual JoinPolicy* copyMyPolicy();



    private:
    int mOffer;
   



};