#include "digraph.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;



vector<int> DigraphMatrix::topologicalSort() 
{
    vector<int> whatsgood;
    offshoot=false;
    this->assignfilename();
    //cout << "we did one thing" << endl;
    this->assignneighbors();
    topologicalSort2(0);
    exploredlistoutput.pop_back();
    for(int zeb=0; zeb<numvertices; zeb++)
    {
        if(!isdiscovered(zeb))
        {
            topologicalSort2(zeb);
            //cout << "Looks like we missed " << zeb << endl;
        }
    }
    while(exploredlistoutput.size()!=0)
    {
        whatsgood.push_back(exploredlistoutput.back());
        exploredlistoutput.pop_back();
    }
    //cout << "Final thing: ";
    return whatsgood;
}

//TODO READ INSTRUCTIONS AND FIGURE OUT HOW TO BREAK INFINITE LOOP LOL
void DigraphMatrix::topologicalSort2(int x)
{
    helpme(x);
    if(isexplored(x))
        return;
    if(x==0&&!isexplored(0))
    {
        crazylist.push_back(x);
        discoveredlist.push_back(x);
    }
    int ultimatetemp=0;
    //cout << "Now checking neighbors of " << x << endl;
    int minneighbor;
    for(int xd=0;xd<20;xd++)
    {
        int temperoos;
        int temperoos2;
        temperoos=neighborlist[x][xd];
        if(temperoos!=420 && !isdiscovered(temperoos))
        {
            //cout << temperoos << " Just got added to discovered list from being a neighbor of " << x << endl;
            if(temperoos < minneighbor) minneighbor=temperoos;
            ultimatetemp++;
        }
    }
    if(ultimatetemp==0)
    {
        exploredlistoutput.push_back(x);
        int normaltemp;
        if(crazylist.size()!=0)
        {
            normaltemp= crazylist.back();
            crazylist.pop_back();
        }
        if(x!=normaltemp && !isexplored(normaltemp))
        {
                //cout << "Goin back since " << x << "has no undiscovered neighbors and has been explored. Going to " << normaltemp << endl;
                topologicalSort2(normaltemp);
        }
        else
        {
            //cout << "yoo dawg!" << endl;
            if(isexplored(1)&&!offshoot)
            {
                exploredlistoutput.push_back(0);
                offshoot=true;
            }
        }
    }
    else
    {
        //cout << "Now about to check " << minneighbor << endl;
        if(!isdiscovered(minneighbor))
            discoveredlist.push_back(minneighbor);
        crazylist.push_back(x);
        topologicalSort2(minneighbor);
    }
    //cout << "done? i just put " << x << "somewhere lol" << endl;
}

void DigraphMatrix::assignfilename()
{
    ifstream in(filenameo);
    vector<int> ins (99);
    string line;
    int temp;
    int temp2=0;
    istringstream iss;
    getline(in,line);
    iss.str(line);
    while (iss >> temp)
    {
        ins[temp2]=(temp);
        temp2++;
    }
    iss.clear();
    numvertices=ins[0];
    numedges=ins[1];
}
bool DigraphMatrix::isexplored(int lookin)
{
    std::vector<int> liltempy=exploredlistoutput;
    int bigtempy;
    while (liltempy.size()!=0)
    {
        bigtempy=liltempy.back();
        if(bigtempy==lookin) 
            return true;
        liltempy.pop_back();
    }
    return false;
}

bool DigraphMatrix::iscrazy(int lookin)
{
    std::vector<int> liltempy=crazylist;
    int bigtempy;
    int crazycount;
    while (liltempy.size()!=0)
    {
        bigtempy=liltempy.back();
        if(bigtempy==lookin) 
            crazycount++;
        liltempy.pop_back();
    }
    if(crazycount>1) return true;
    return false;
}

void DigraphMatrix::helpme(int lookin)
{
    int factor=0;
    int factor2=0;
    for (int swag=0; swag < 12; swag++)
    {
        if(isexplored(neighborlist[lookin][swag]))
            factor++;
        if(isdiscovered(neighborlist[lookin][swag]))
            factor2++;
    }
    if (factor==0&&isdiscovered(lookin)&&factor2>0)
    {
        throw std::invalid_argument("cycle");
    }
}

bool DigraphMatrix::isdiscovered(int lookin)
{
    std::vector<int> liltempy=discoveredlist;
    int bigtempy;
    if(isexplored(lookin)) return true;
    while (liltempy.size()!=0)
    {
        bigtempy=liltempy.back();
        if(bigtempy==lookin) 
            return true;
        liltempy.pop_back();
    }
    return false;
}

void DigraphMatrix::assignneighbors()
{
    for(int xd=0;xd<89;xd++)
    {
        numneighbors[xd]=0;
    }
    for(int xd=0;xd<89;xd++)
    {
        for (int xc=0; xc<89; xc++)
        {
            neighborlist[xd][xc]=420;
        }
    }
    ifstream in(filenameo);
    vector<int> ins (99);
    string line;
    int temp;
    int temp2=0;
    istringstream iss;
    if(in.good())
    {
        while(getline(in,line))
        {
            iss.str(line);
            while (iss >> temp)
            {
                ins[temp2]=(temp);
                temp2++;
            }
            iss.clear();
            int tempyboy=ins[0];
            int tempyboy2=ins[1];
            int numtempyboy=numneighbors[tempyboy];
            neighborlist[tempyboy][numtempyboy]=tempyboy2;
            //cout << tempyboy << "Just attained an outward neighbor of " << tempyboy2 << endl;
            numneighbors[tempyboy]++;
            temp2=0;
        }
    }
}