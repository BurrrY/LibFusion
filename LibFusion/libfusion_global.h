#ifndef LIBFUSION_GLOBAL_H
#define LIBFUSION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBFUSION_LIBRARY)
#  define LIBFUSIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBFUSIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#define UPDATER_VERSION_STBL_FILE "http://update.fusion.florian-bury.de/stable/FVersion.txt"
#define UPDATER_VERSION_NIGHTLY_FILE "http://update.fusion.florian-bury.de/nightly/FVersion.txt"
#define UPDATER_LOCAL_VERSIONFILE_NAME "FVersion.txt"

#ifdef _WIN32
    #define UPDATER_LATES_STABLE  "http://update.fusion.florian-bury.de/stable/latest/FusionLauncher_Windows.exe"
    #define UPDATER_LATES_NIGHTLY "http://update.fusion.florian-bury.de/nightly/latest/FusionLauncher_Nightly.exe"
#elif __linux
    #define UPDATER_LATES_STABLE "http://projfusion.com/files/Releases/latest/FusionClient_Linux.tar"
    #define UPDATER_LATES_STABLE_ALT "http://fsnupdt.florian-bury.de/latest/latest/FusionClient_Linux.tar"

    #define UPDATER_LATES_NIGHTLY
    #define UPDATER_LATES_NIGHTLY_ALT
#endif


#endif // LIBFUSION_GLOBAL_H
