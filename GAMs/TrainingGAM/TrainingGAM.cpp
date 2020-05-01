/**
 * TrainingGAM.cpp
 * Source code for the TrainingGAM class
 */

#include "TrainingGAM.h"
#include "DDBInputInterface.h"
#include "DDBOutputInterface.h"
#include "TrainingGAMInputStructure.h"
#include "TrainingGAMOutputStructure.h"

bool TrainingGAM::Initialise(ConfigurationDataBase& cdbData) {
    ////////////////////////////////////////////////////
    //                Add interfaces to DDB           //
    ////////////////////////////////////////////////////
    if (!AddInputInterface(input, "InputInterface")) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: failed to add input interface", Name());
        return False;
    }
    if (!AddOutputInterface(output, "OutputInterface")) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: failed to add output interface", Name());
        return False;
    }

    CDBExtended cdb(cdbData);

    ////////////////////////////////////////////////////
    //                Add input signals               //
    ////////////////////////////////////////////////////
    if (!cdb->Move("InputSignals")) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: did not specify InputSignals entry",Name());
        return False;
    }
    if (!input->ObjectLoadSetup(cdb,NULL)) {
        AssertErrorCondition(InitialisationError,"TrainingGAM %s::Initialise: ObjectLoadSetup Failed DDBInterface %s ",Name(),input->InterfaceName());
        return False;
    }
    uint32 nOfSignals = cdb->NumberOfChildren();
    if(nOfSignals != 1){
        AssertErrorCondition(Warning,"TrainingGAM %s::Initialise: ObjectLoadSetup. Exactly 1 TrainingGAMInputStructure is expected to be given as input of this GAM ",Name());
    }
    cdb->MoveToFather();

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
    nOfSignals = cdb->NumberOfChildren();
    if(nOfSignals != 1){
        AssertErrorCondition(Warning,"TrainingGAM %s::Initialise: ObjectLoadSetup. Only a TrainingGAMOutputStructure is going to be given as output of this GAM ",Name());
    }
    cdb->MoveToFather();

    return True;
}

bool TrainingGAM::Execute(GAM_FunctionNumbers functionNumber) {
    // At the beginning of each function we collect input data
    input->Read();

    switch (functionNumber) {
        case GAMPrepulse:
            // At the start of a pulse, reset the sums to zero
            intSum = 0;
            floatSum = 0.0f;
            break;
        case GAMOnline:
            // Each cycle we will add to our sums from the input
            // First get the buffer from the DDBInputInterface
            TrainingGAMInputStructure *inputBuffer = reinterpret_cast<TrainingGAMInputStructure *>(input->Buffer());
            
            // Now use these in the sums
            intSum += inputBuffer->intToAdd;
            floatSum += inputBuffer->floatToAdd;
            
            // Then we will calculate the product of the new sums
            float productOfSums = (float)intSum * floatSum;
            
            // Finally we will output this to our OutputInterface
            TrainingGAMOutputStructure *outputBuffer = reinterpret_cast<TrainingGAMOutputStructure *>(output->Buffer());
            outputBuffer->productOfSums = productOfSums;
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
