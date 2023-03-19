#pragma once
#include <string>

using std::string;

class JoinPolicy;
class Simulation;
class Coalition;
class Agent;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party();
    Party(int id, string name, int mandates, JoinPolicy *); 
    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    void partyAddOffer(Agent *agent,Simulation &sim);
    int getCoalition() const;
    int getMId() const;
    //JoinPolicy set coalition
    void setMCoal(int CoalId);



    //Rule of 5
    virtual ~Party();
    Party(const Party &other);
    Party(Party &&other);
    Party& operator=(const Party &other);
    Party& operator=(Party &&other);



private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTimer;
    int mCoalId;

};
