
#include "PointsService.h"
#include "../model/PrivateUser.h"

PointsService::PointsService ( UserDAO& userDAO )
    : userDAO(userDAO) {}

void PointsService::awardPoints ( const vector<string>& sensorIds )
{
    for ( const string& sensorId : sensorIds )
    {
        PrivateUser* user = userDAO.getBySensorId( sensorId );
        if ( user != nullptr && !user->getIsBlocked() )
        {
            user->addPoints( 1 );
        }
    }
}

int PointsService::getPoints ( const string& userId )
{
    return userDAO.getPoints( userId );
}
