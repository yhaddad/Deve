/** 
 *  @file  EventLoader
 *  @brief event loader 
 */

#ifndef _EVENTLOADER_H
#define _EVENTLOADER_H 1

#include "lcio.h"
#include "IO/LCReader.h"
#include "EVENT/LCEvent.h"
#include "EVENT/LCCollection.h"

#include "DeveDisplay.h"
#include "TEveElement.h"
#include "TEveManager.h"
#include "TEveTrack.h"

//--- ROOT Deps
#include "TSystem.h"
#include "TRint.h"
#include "TROOT.h"

class TEveElement;
class DeveDisplay;
class TEveManager;

//class TGeoShape;
//class TGeoVolume;
//class TGeoMedium;

extern TEveManager *gEve;

using namespace lcio;
using namespace std;


class EventLoader{
 public:
  /**
   *  @brief  Event Loader navigator
   */
  static EventLoader *get_instance();
  
  void load_event(LCEvent* evt);
  void init_deve();
  void load_collection(std::string col);
  
  void next();
  void back();
  
  //void pause() const;
  
  ~EventLoader();
  void delete_instance();
  
  //-- Deve Part for drawing
  TEveElementList* build_PFO(LCCollection* col);
  
  //TEveElement*     draw_recPart(ReconstructedParticle* rec);
 private:
  EventLoader();
  // --- sub rootins for Deve 
  //Color GetColorForPdgCode(int particleId);
  
  // ---flags
  static bool         m_instance_flag;
  static EventLoader *m_pEventLoader ;
  static bool         m_eve_initialize;
  static TEveElementList    *gJetList     ;
  static TEveTrackList      *gTrackList   ;
  static DeveDisplay        *gDeveDisplay ;
    
  // generic detector
  static Double_t gRadius     ;
  static Double_t gHalfLength ;
  static Double_t gBz         ;
  
  TRint *root_interface ;
  
  std::map <string, TEveElementList*> collectionClasses;
  //-- internal vairable
  int m_event_id;
};

#endif /* _EVENTLOADER_H */

