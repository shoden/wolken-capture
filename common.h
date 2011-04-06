#ifndef COMMON_H
#define COMMON_H

// C
#include <stdio.h>
#include <stdlib.h>

// C++
#include <iostream>

// Qt
#include <QList>
#include <QMap>
#include <QMapIterator>
#include <QString>
#include <QVariant>

using namespace std;

typedef QMap<QString,QString> Params;
typedef QList<Params> Takes;

#endif // COMMON_H
