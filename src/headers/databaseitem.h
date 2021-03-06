#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include "databasemanager.h"

class DatabaseItem
{
    protected:
        DatabaseManager         *_pDB;

        int                     _iID;

    public:
                                DatabaseItem( DatabaseManager *pDB, int iID ) : _pDB( pDB ), _iID( iID ) { }

        virtual bool            Insert( void ) = 0;
        virtual bool            Update( void ) = 0;
        virtual bool            Select( void ) = 0;

        virtual bool            BuildQueries( void ) = 0;
        static bool             Create( DatabaseManager *pDB );
        static bool             Delete( DatabaseManager *pDB, int iID );
};

#endif // DATABASEITEM_H
