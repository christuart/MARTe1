/**
 * TrainingGAM.h
 * Header for the TrainingGAM class
 */

#include "GAM.h"

/**
 * A GAM that sums numbers into its memory
 */
OBJECT_DLL(TrainingGAM)
class TrainingGAM : public GAM, public HttpInterface {
OBJECT_DLL_STUFF(TrainingGAM)
private:
    /** DDB Interfaces **/
    /* Input interface */
    DDBInputInterface *input;
    /* Output interface */
    DDBOutputInterface *output;

    /** Parameters **/

    /** State **/
    /* The stored sum of integers */
    int32 intSum;
    /* The stored sum of floats */
    float floatSum;

public:
    /* Constructor */
    TrainingGAM() {
        input = NULL;
        output = NULL;

        intSum = 0;
        floatSum = 0.0f;
    }

    /* Destructor */
    ~TrainingGAM() {
    }

    /* Set up the GAM based on the configuration data cbdData */
    bool Initialise(ConfigurationDataBase& cdbData);

    /* Execute the GAM function requested */
    bool Execute(GAM_FunctionNumbers functionNumber);

    /* Respond to HTTP requests */
    bool ProcessHttpMessage(HttpStream &hStream);
};
