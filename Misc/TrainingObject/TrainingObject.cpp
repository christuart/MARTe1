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

bool TrainingObject::ProcessMessage(GCRTemplate<MessageEnvelope> envelope) {
    AssertErrorCondition(Information, "ProcessMessage %s: Received Message from %s: ", Name(), envelope->Sender());
    GCRTemplate<Message> message = envelope->GetMessage();
    if (message.IsValid()){
        FString messageContent = message->Content();
        if (messageContent == "SUN_IS_SETTING") {
            dayOrNight = NIGHTTIME;
        } else if (messageContent == "SUN_IS_RISING") {
            dayOrNight = DAYTIME;
        } else {
            dayOrNight = UNKNOWN_EARTH_ROTATION_STATUS;
        }
    }
    return True;
}

bool TrainingObject::ProcessHttpMessage(HttpStream &hStream) {
    hStream.SSPrintf("OutputHttpOtions.Content-Type","text/html");
    hStream.Printf("<html><head><title>TrainingObject</title><head><body>\n");
    switch (dayOrNight) {
        case DAYTIME:
            hStream.Printf("<p>Hello World, what a wonderful day!</p>\n");
            break;
        case NIGHTTIME:
            hStream.Printf("<p>Hello World, what a wonderful night!</p>\n");
            break;
        case UNKNOWN_EARTH_ROTATION_STATUS:
            hStream.Printf("<p>Hello World, wherever you may be!</p>\n");
    }
    hStream.Printf("</body></html>");        
    hStream.WriteReplyHeader(True);
    return True;
}

OBJECTLOADREGISTER(TrainingObject, "$Id$")
