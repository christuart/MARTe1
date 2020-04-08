/*
 * Copyright 2011 EFDA | European Fusion Development Agreement
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they 
   will be approved by the European Commission - subsequent  
   versions of the EUPL (the "Licence"); 
 * You may not use this work except in compliance with the 
   Licence. 
 * You may obtain a copy of the Licence at: 
 *  
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in 
   writing, software distributed under the Licence is 
   distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
   express or implied. 
 * See the Licence for the specific language governing 
   permissions and limitations under the Licence. 
 *
 * $Id$
 *
**/

/**
 * Training Object created by Chris Stuart <chris.stuart@ukaea.uk>
 * 07/04/2020
**/

#ifndef TRAINING_OBJECT_H_
#define TRAINING_OBJECT_H_

#include "GCNamedObject.h"
#include "HttpInterface.h"
#include "MessageHandler.h"

/**
 * An enumeration for HelloWorld to understand day vs night
 */
enum TrainingObjectEarthRotationStatus {
    UNKNOWN_EARTH_ROTATION_STATUS,
    DAYTIME,
    NIGHTTIME
};

/**
 * A HelloWorld object
 */
OBJECT_DLL(TrainingObject)
class TrainingObject : public GCNamedObject, public HttpInterface, public MessageHandler {
OBJECT_DLL_STUFF(TrainingObject)

private:
    /** States */
    TrainingObjectEarthRotationStatus dayOrNight;

public:
    /** Constructor */
    TrainingObject(){
        dayOrNight = UNKNOWN_EARTH_ROTATION_STATUS;
    }

    /** Destructor */
    ~TrainingObject(){
    }

    /** Loads object parameters from a CDB */
    virtual bool ObjectLoadSetup(ConfigurationDataBase &cdbData, StreamInterface *err);

    /** The MARTe message handling routine */
    virtual bool ProcessMessage(GCRTemplate<MessageEnvelope> envelope);

    /** Responds to HTTP requests */
    bool ProcessHttpMessage(HttpStream &hStream);
};

#endif /* TRAINING_OBJECT_H_ */
