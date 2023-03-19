#include "Party.h"
#include "Agent.h"
#include "JoinPolicy.h"

Party::Party(): mId(), mName(), mMandates(), mJoinPolicy(), mState(Waiting),mTimer(1),mCoalId(-1){}

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),mTimer(1),mCoalId(-1)
{

}




Party::~Party(){
    if( mJoinPolicy){
        delete  mJoinPolicy;
    }
}

Party::Party(const Party &other):Party(){
mMandates=other.mMandates;    
mId=other.mId;
mName=other.mName;
mCoalId=other.mCoalId;
mState=other.mState;
mTimer=other.mTimer;

mJoinPolicy=other.mJoinPolicy->copyMyPolicy();


}

Party::Party(Party &&other):Party(){
mMandates=other.mMandates;    
mId=other.mId;
mName=other.mName;
mJoinPolicy=other.mJoinPolicy;
mCoalId=other.mCoalId;
mState=other.mState;
mTimer=other.mTimer;


other.mJoinPolicy=nullptr;
}


Party& Party::operator=(const Party &other){
if(this!=&other){
delete mJoinPolicy;

mMandates=other.mMandates;    
mId=other.mId;
mName=other.mName;
mCoalId=other.mCoalId;
mState=other.mState;
mTimer=other.mTimer;

mJoinPolicy=other.mJoinPolicy->copyMyPolicy();


}

return *this;
}


Party& Party:: operator=(Party &&other){
if(this!=&other){
delete mJoinPolicy;

mMandates=other.mMandates;    
mId=other.mId;
mName=other.mName;
mJoinPolicy=other.mJoinPolicy;
mCoalId=other.mCoalId;
mState=other.mState;
mTimer=other.mTimer;

other.mJoinPolicy=nullptr;
}

return *this;

}

State Party::getState() const
{
    return mState;
}


void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::setMCoal(int CoalId) {
    mCoalId = CoalId;
}


int Party::getCoalition() const{
    return mCoalId;
}



//ADD new offers to the party 
void Party :: partyAddOffer(Agent *agent,Simulation &sim) {
    mJoinPolicy->policyAddOffer(agent,sim);
     
}

int Party::getMId() const {
    return mId;
}


void Party::step(Simulation &s)
{
    if(mState==CollectingOffers){
        if(mTimer==3){
        //Join to selected coalition
        mJoinPolicy->join(*this,s);
        }
        else{
            mTimer++;
        }
    }
}

