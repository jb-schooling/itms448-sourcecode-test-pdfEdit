/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech AS. All rights reserved.
**
** This file is part of the QSA of the Qt Toolkit.
**
** For QSA Commercial License Holders (non-open source):
** 
** Licensees holding a valid Qt Script for Applications (QSA) License Agreement
** may use this file in accordance with the rights, responsibilities and
** obligations contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of the Licensing Agreement are
** not clear to you.
** 
** Further information about QSA licensing is available at:
** http://www.trolltech.com/products/qsa/licensing.html or by contacting
** info@trolltech.com.
** 
** 
** For Open Source Edition:  
** 
** This file may be used under the terms of the GNU General Public License
** version 2 as published by the Free Software Foundation and appearing in the
** file LICENSE.GPL included in the packaging of this file.  Please review the
** following information to ensure GNU General Public Licensing requirements
** will be met:  http://www.trolltech.com/products/qt/opensource.html 
** 
** If you are unsure which license is appropriate for your use, please review
** the following information:
** http://www.trolltech.com/products/qsa/licensing.html or contact the 
** sales department at sales@trolltech.com.

**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qsobject_object.h"
#include "qsclass.h"
#include "qsenv.h"
#include "qsoperations.h"
#include "qstypes.h"
#include "qsfunction.h"

QSObjectClass::QSObjectClass( QSEnv *e )
    : QSClass( e )
{
}

void QSObjectClass::init()
{
    addMember( QString::fromLatin1("toString"), QSMember( &QSObjectClass::toStringScript ) );
    addMember( QString::fromLatin1("valueOf"), QSMember( &QSObjectClass::valueOf ) );
}

QString QSObjectClass::toString( const QSObject *obj ) const
{
    return QString::fromLatin1("[object ") + obj->typeName() + QString::fromLatin1("]");
}

QSObject QSObjectClass::construct() const
{
    QSList dummy;
    return construct( dummy );
}

QSObject QSObjectClass::construct( const QSList &args ) const
{
    if ( args.isEmpty() ) {
	return env()->dynamicClass()->createWritable();
    } else {
	// ### warn about superfluous arguments ?
	return args[0];
    }
}

/*! \reimp */
QSObject QSObjectClass::cast( const QSList &args ) const
{
    // same as 'new'
    return construct( args );
}

// Object.toString()
QSObject QSObjectClass::toStringScript( QSEnv *env )
{
    QString str = QString::fromLatin1("[object ") + env->thisValue().typeName() + QString::fromLatin1("]");
    return env->createString( str );
}

// Object.valueOf()
QSObject QSObjectClass::valueOf( QSEnv *env )
{
    return env->thisValue();
}