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

#include "TrainingObject.h"
#include "ErrorManagement.h"

bool TrainingObject::ObjectLoadSetup(ConfigurationDataBase &cdbData, StreamInterface *err){

    // load name of object
    bool ret = this->GCNamedObject::ObjectLoadSetup(cdbData, err);
    this->AssertErrorCondition(Information, "Hello World! Greetings from %s", this->Name());
    return ret;

}

bool TrainingObject::ProcessHttpMessage(HttpStream &hStream) {
    hStream.SSPrintf("OutputHttpOtions.Content-Type","text/html");
    hStream.Printf("<html><head><title>TrainingObject</title><head><body>\n");
    hStream.Printf("<p>Hello World!</p>\n");
    hStream.Printf("</body></html>");        
    hStream.WriteReplyHeader(True);
    return True;
}

OBJECTLOADREGISTER(TrainingObject, "$Id$")