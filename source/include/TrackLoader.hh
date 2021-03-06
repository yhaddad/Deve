  /// \file TrackLoader.hh
/*
 *
 * TrackLoader.hh header template generated by fclass
 * Creation date : mar. sept. 24 2013
 *
 * This file is part of XXX libraries.
 * 
 * XXX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * XXX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with XXX.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author : Et� R�mi
 * @version
 * @copyright
 *
 *
 */


#ifndef TRACKLOADER_HH
#define TRACKLOADER_HH

#include "ObjectLoader.hh"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

// lcio includes
#include "EVENT/LCIO.h"


namespace deve {

	/*!
	*
	* @brief  TrackLoader class
	* Inherits from base class ObjectLoader
	*
	*/
	class TrackLoader : public ObjectLoader {

		public:

			/*!
			*
			* @brief Constructor
			*
			*/
			TrackLoader()
			: ObjectLoader( EVENT::LCIO::TRACK ) {}

			/*!
			*
			* @brief Default destructor
			*
			*/
			virtual ~TrackLoader();

			/*!
			*
			* @brief Load the specific objects from a lcio LCCollection pointer and a collection name
			*
			*/
			virtual void loadObjectsFromLCCollection( EVENT::LCCollection * , const std::string & );

			/*!
			*
			* @brief Load objects from an other framework.
			*
			*/
			virtual void loadObjects( void * );

		protected:


	};  // class

}  // namespace 

#endif  //  TRACKLOADER_HH
