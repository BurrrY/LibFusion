#ifndef LIBFUSION_H
#define LIBFUSION_H

#include "libfusion_global.h"

#ifndef QTCORE
#include <QtCore>
#endif

#include <QDir>

#define VersionNumber QString("0.9.1")
#define VersionName QString("Pluto")
#define VersionString VersionNumber + "\n" + VersionName


class LIBFUSIONSHARED_EXPORT LibFusion
{

public:
    LibFusion();
    static QDir getWorkingDir();
    static bool makeSureWorkingDirExists();
};

#endif // LIBFUSION_H
