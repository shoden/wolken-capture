#ifndef COMMON_H
#define COMMON_H

// C
#include <stdio.h>
#include <stdlib.h>

// C++
#include <iostream>

// Qt
#include <QDateTime>
#include <QList>
#include <QHash>
#include <QHashIterator>
#include <QString>
#include <QStringList>
#include <QVariant>

using namespace std;

typedef QHash<QString,QString> Params;
typedef QList<Params> Takes;

#endif // COMMON_H
