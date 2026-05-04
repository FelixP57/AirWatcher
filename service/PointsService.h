
#if !defined ( POINTSSERVICE_H )
#define POINTSSERVICE_H

#include "../data/UserDAO.h"
#include <vector>
#include <string>
using namespace std;

class PointsService
{
public:
    PointsService ( UserDAO& userDAO );

    void awardPoints ( const vector<string>& sensorIds );
    int  getPoints   ( const string& userId );

private:
    UserDAO& userDAO;
};

#endif // POINTSSERVICE_H
