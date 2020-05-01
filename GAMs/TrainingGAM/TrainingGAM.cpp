/**
 * TrainingGAM.cpp
 * Source code for the TrainingGAM class
 */

#include "TrainingGAM.h"

bool TrainingGAM::Initialise(ConfigurationDataBase& cdbData) {
    // Read in our integer to add
    intToAdd = 3;

    // Read in our float to add
    floatToAdd = 2.721828;

    return True;
}

bool TrainingGAM::Execute(GAM_FunctionNumbers functionNumber) {
    switch (functionNumber) {
        case GAMPrepulse:
            intSum = 0;
            floatSum = 0.0f;
            break;
        case GAMOnline:
            intSum += intToAdd;
            floatSum += floatToAdd;
            break;
    }
    return True;
}

bool TrainingGAM::ProcessHttpMessage(HttpStream &hStream) {
    hStream.SSPrintf("OutputHttpOtions.Content-Type","text/html");
    hStream.Printf("<html><head><title>TrainingGAM</title><head><body>\n");
    hStream.Printf("<p>Hello World!</p>\n");
    hStream.Printf("<p>I have summed integers: %d</p>\n", intSum);
    hStream.Printf("<p>I have summed floats: %f</p>\n", floatSum);
    hStream.Printf("</body></html>");        
    hStream.WriteReplyHeader(True);
    return True;
}

OBJECTLOADREGISTER(TrainingGAM, "$Id$")
