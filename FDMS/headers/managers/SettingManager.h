/*
    Fire Department Management System
    Copyright (C) 2010  Joseph W. Dougherty

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QSettings>
#include <QString>

class SettingManager
{
    private:
                                    SettingManager( void );
                                    ~SettingManager( void );

        QSettings                   *_pSettings;

        QMap<QString, QVariant>     _Entries;

    public:
        friend SettingManager*      GetSettingManager( void );

        void                        set( QString sKey, QVariant vValue );
        bool                        exists( void );
        bool                        remove( void );
        void                        save( void );
        void                        load( void );
};

SettingManager* GetSettingManager();

#endif // SETTINGMANAGER_H
