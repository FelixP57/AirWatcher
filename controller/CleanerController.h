#include <string>
#include "../service/CleanerService.h"

class CleanerController
{
public:
    ImpactReport handleEvaluateImpact(string cleanerId);
    CleanerController();
    ~CleanerController();
private:

};
