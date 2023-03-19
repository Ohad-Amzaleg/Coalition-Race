#include "Coalition.h"
#include "Party.h"

Coalition:: Coalition():mSize(),mId(),mOffered(){}

Coalition:: Coalition(int size,int id, int mofferdSize):mSize(size),mId(id),mOffered(mofferdSize){
}


const int Coalition::getSize()const 
{
    return mSize;
}


void Coalition::setSize(int size)
{
    mSize=size;
}


int Coalition::getId() 
{
    return mId;
}

void Coalition::setId(int id) 
{
    mId=id;
}

vector<bool>* Coalition::getOffered() {
    vector<bool> *pmOffered=&mOffered;
    return pmOffered;
}

void Coalition::addOldOffer(const Party & party) {
    mOffered[party.getMId()]=true;
}
