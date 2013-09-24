#include "EventLoader.h"
#include "lcio.h"
#include "IO/LCReader.h"
#include "IMPL/LCTOOLS.h"                                                             
#include "EVENT/LCRunHeader.h"                                                        
#include "UTIL/Operators.h"
#include "UTIL/LCIterator.h"
#include "EVENT/ReconstructedParticle.h"

#include "TEveManager.h"
#include "TEveElement.h"
#include "TEveTrack.h"
#include "TEveArrow.h"
#include "TEveTrackPropagator.h"
#include "TEveBrowser.h"
#include "TDatabasePDG.h"
#include "TEveBox.h"
#include "TEveVSDStructs.h"

#include "TEveText.h"
#include "TEveTrans.h"
#include "TEveTextGL.h"
#include <TEveViewer.h>
#include <TGLViewer.h>
#include <TEveScene.h>
#include <TEveElement.h>
#include <TEveTrack.h>
#include "TEveTrackPropagator.h"
#include <TEveProjectionManager.h>
#include <TEveProjectionAxes.h>
#include <TEveBrowser.h>
#include <TEveWindow.h>
#include <TEveGeoShape.h>
#include <TGeoTube.h>

using namespace std;
using namespace lcio;

bool              EventLoader::m_instance_flag     = false;
bool              EventLoader::m_eve_initialize    = false;
EventLoader*      EventLoader::m_pEventLoader      = NULL;
// --
TEveElementList*  EventLoader::gJetList     = 0 ;
TEveTrackList*    EventLoader::gTrackList   = 0 ;
DeveDisplay*      EventLoader::gDeveDisplay = 0 ;
// -- geom init generic :: to be fixed for the future
Double_t          EventLoader::gRadius     = 1.29;
Double_t          EventLoader::gHalfLength = 3.0;
Double_t          EventLoader::gBz         = 3.8;


EventLoader::EventLoader() : m_event_id(-2)
{
  TEveManager::Create();

  //root_interface = new TRint("Deve via ROOT",0,0);
  //root_interface->SetReturnFromRun(kTRUE);
}

EventLoader::~EventLoader()
{
  if(m_eve_initialize){
    //TEveManager::Terminate();
    //gSystem->ProcessEvent();
  }
  root_interface->Terminate(0);
}
void EventLoader::delete_instance()
{
  delete get_instance();
}
  
EventLoader *EventLoader::get_instance()
{
  if(!m_instance_flag){
    m_pEventLoader  = new EventLoader();
    m_instance_flag = true;
  }
  return m_pEventLoader;
}

void EventLoader::next(){
  if (m_event_id < 1000000){
    ++m_event_id;
    //load_event(m_event_id);
  }else{
    std::cout<< "WARNING:: Already at last event.\n"<< std::endl;
  }
}
void EventLoader::back(){
  if (m_event_id > 0) {
    --m_event_id;
    //load_event(event_id);
  }else{
    std::cout<< "WARNING:: Already at first event.\n"<< std::endl;
  }
}

void EventLoader::load_event(LCEvent* evt)
{
  const std::vector< std::string >* col_names = evt->getCollectionNames() ;
  
  // --- loop on collections
  std::vector<std::string>::const_iterator name;
  for(  name = col_names->begin() ; name != col_names->end() ; name++){
    LCCollection* col = evt->getCollection( *name ) ;
    if( col->getTypeName() == LCIO::RECONSTRUCTEDPARTICLE )
    	gEve->AddElement(this->build_PFO(col));
  }
  
}

TEveElementList* EventLoader::build_PFO(LCCollection* col) {

  TEveTrackList *gTrackList = new TEveTrackList();
  TEveTrackPropagator *trkProp = gTrackList->GetPropagator();
  trkProp->SetMagField(0.0, 0.0, -gBz);
  trkProp->SetMaxR(gRadius*100.0);
  trkProp->SetMaxZ(gHalfLength*100.0);
  
  std::string col_type = col->getTypeName();
  //if(col->getNumberOfElements() == 0)     continue; // fixme
  //if(col_type != "ReconstructedParticle") continue;
  
  for(int i=0; i<col->getNumberOfElements(); i++){ // loop over part


    ReconstructedParticle* part=dynamic_cast<ReconstructedParticle*>(col->getElementAt(i));
    cout << "part : " << part << endl;
    TEveRecTrack* deveTrack = new TEveRecTrack();
    deveTrack->fV.Set( part->getStartVertex()->getPosition() );
    deveTrack->fP.Set(part->getMomentum());
    deveTrack->fSign = part->getCharge();
    
    TEveTrack* track = new TEveTrack(deveTrack, trkProp);
    track->SetName(Form("Track %d", i));
    //track->SetLineWidth(PFOParams[TrType].Width);
    //track->SetLineColor(PFOParams[TrType].Color);
    //track->SetLineStyle(PFOParams[TrType].Style);
    track->SetSmooth(kTRUE);
    gTrackList->AddElement(track);
    
  }
  gTrackList->MakeTracks();
  //TEveElement*  = gEve->GetCurrentEvent();
  return gTrackList;
}


void EventLoader::init_deve(){
  // -- generic geometry 
  TEveElementList *geometry = new TEveElementList("Geometry");
  TEveGeoShape *barell = new TEveGeoShape("Barell");
  barell->SetShape(new TGeoTube(gRadius*100.0 - 1, gRadius*100.0, gHalfLength*100.0));
  barell->SetMainColor(kCyan);
  barell->SetMainTransparency(80);
  geometry->AddElement(barell);
  
  gDeveDisplay = new DeveDisplay;
  gEve->AddGlobalElement(geometry);
  gDeveDisplay->ImportGeomRPhi(geometry);
  gDeveDisplay->ImportGeomRhoZ(geometry);


//  gEve->Redraw3D(kTRUE);

}
