#ifndef __DIGRAPH_H
#define __DIGRAPH_H
#include<iostream>
#include <string>
#include <vector>
using namespace std;

class DigraphMatrix
{
  private:
  string filenameo;
public:
  DigraphMatrix(const string& filename)
  {
    filenameo=filename;
  }
  vector<int> topologicalSort();
  void topologicalSort2(int x);
  void assignfilename();
  void assignneighbors();
  bool isexplored(int lookin);
  bool isdiscovered(int lookin);
  void helpme(int lookin);
  bool iscrazy(int lookin);
  int numvertices;
  int numedges;
  bool offshoot;
  int neighborlist[90][90];
  int numneighbors[90];
  int crazyarray[90];
  std::vector<int> discoveredlist;
  std::vector<int> exploredlistoutput;
  std::vector<int> crazylist;
};
#endif