#pragma once
#include <map>
#include <vector>


using std::vector;
using std::map;
class Party;

class Coalition{
    public:
    Coalition();
    Coalition(int size,int id,int mofferdSize);
    const int getSize() const;
    void setSize(int size);
    int getId();
    void setId(int id);
    vector<bool> *getOffered();
    void addOldOffer(const Party &party);
    

private:
    int mSize;
    int mId;
    vector <bool> mOffered;
};