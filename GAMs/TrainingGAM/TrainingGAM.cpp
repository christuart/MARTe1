/**
 * TrainingGAM.cpp
 * Source code for the TrainingGAM class
 */

#include "TrainingGAM.h"
#include "DDBOutputInterface.h"

bool TrainingGAM::Initialise(ConfigurationDataBase& cdbData) {
    // Read in our integer to add
    intToAdd = 3;

    // Read in our float to add
    floatToAdd = 2.721828;

    ////////////////////////////////////////////////////
    //                Add interfaces to DDB           //
    ////////////////////////////////////////////////////
    if (!AddOutputInterface(output, "OutputInterface")) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: failed to add output interface", Name());
        return False;
    }

    CDBExtended cdb(cdbData);

    ////////////////////////////////////////////////////
    //                Add output signals              //
    ////////////////////////////////////////////////////
    if (!cdb->Move("OutputSignals")) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: did not specify OutputSignals entry",Name());
        return False;
    }
    if (!output->ObjectLoadSetup(cdb,NULL)) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: ObjectLoadSetup Failed DDBInterface %s ",Name(),output->InterfaceName());
        return False;
    }
    uint32 nOfSignals = cdb->NumberOfChildren();
    if(nOfSignals != 1){
        AssertErrorCondition(Warning,"TrainingGAM %s::Initialise: ObjectLoadSetup. Only the product of the two sums is going to be given as output of this GAM ",Name());
    }
    cdb->MoveToFather();

    return True;
}

bool TrainingGAM::Execute(GAM_FunctionNumbers functionNumber) {
    switch (functionNumber) {
        case GAMPrepulse:
            // At the start of a pulse, reset the sums to zero
            intSum = 0;
            floatSum = 0.0f;
            break;
        case GAMOnline:
            // Each cycle we will add to our sums
            intSum += intToAdd;
            floatSum += floatToAdd;
            
            // Then we will calculate the product of the new sums
            float productOfSums = (float)intSum * floatSum;
            
            // Finally we will output this to our OutputInterface
            float *outputBuffer = reinterpret_cast<float*>(output->Buffer());
            outputBuffer[0] = productOfSums;
            break;
    }

    // At the end of each function we send the output buffer out
    output->Write();

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
