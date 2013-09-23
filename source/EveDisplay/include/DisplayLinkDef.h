
/** DisplayLinkdef
 *
 *  Lists classes to be included in cint dicitonary
 *
 *  \author Haddad Yacine/ LLR- Ecole polytechnique
 *  All rights reserved
 *
 */

#include "LCDisplay.h"
//#include "display/DelphesCaloData.h"

#ifdef __CINT__
  
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

/*
  #pragma link C++ class TEveProjectionManager+;
  #pragma link C++ class TEveElement+;
  #pragma link C++ class TEveCalo3D+;
  #pragma link C++ class TEveCaloLego+;
  #pragma link C++ class TEveViewer+;
  #pragma link C++ class TEveScene+;
*/

#pragma link C++ class LCDisplay+;

  //#pragma link C++ class DelphesCaloData+;

#endif
