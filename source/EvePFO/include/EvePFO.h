/* @(#)EvePFO.h
 */

#ifndef _EVEPFO_H
#define _EVEPFO_H 1

#include <lcio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class EvePFO {
 public:
  virtual ~EvePFO(){;}
  
  virtual void pretty(){std::cout << "la classe mec !!! 8-) "<< std::endl;}
 private:
  EvePFO();
  int test;
};

//class EveRecoParticle : public EvePFO {
// public:
//  EveRecoParticle(){;}
//  virtual ~EveRecoParticle(){;}
//  virtual TEveElementList *visualizePFO(const reconstructedparticle *pat);
// private:
//  
//};




#endif /* _EVEPFO_H */

