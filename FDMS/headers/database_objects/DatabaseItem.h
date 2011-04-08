#ifndef DATABASEITEM_H
#define DATABASEITEM_H

class DatabaseItem
{
    protected:
        int                         _iID;

    public:
                                    DatabaseItem( void ) : _iID( -1 ) { }
                                    DatabaseItem( int iID ) : _iID( iID ) { }
        virtual                     ~DatabaseItem( void ) {}

        int                         ID( void ) { return _iID; }

        virtual bool                createTable( void );

        virtual bool                save( void ) = 0;
        virtual bool                load( void ) = 0;
};

#endif // DATABASEITEM_H
