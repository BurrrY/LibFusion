#ifndef FGAME_H
#define FGAME_H


#include <QDateTime>

#include "libfusion_global.h"
#include "flauncher.h"
#include "ffilesync.h"

enum FGameType {unknown, Executable, Steam, Origin, Uplay, Galaxy, ROM};
enum FGameSizeConstrain {FHeight, FWidth};
enum FGameArt { FArtBox, FArtClearart, FArtBanner, FArtFanart};



class LIBFUSIONSHARED_EXPORT FGame
{
public:
    FGame (QString gName, FGameType gType, QString gDir, QString exePath, QStringList args);
    FGame();

    /**
    * @brief get name of the game
    *
    * @return the name of the game 
    */
    QString getName();

    /**
    * @brief get the name of the executable file
    *
    * @return  the filename of the executable
    */
    QString getExe();

    /**
    * @brief get the absolute path of the executalbe
    *
    * @return the absolute path, where the executable lies
    */
    QString getPath();

    /**
    * @brief get the Path, where the Artwork for this game is stored. 
    * This is a folder named like the ID of the game.
    *
    * @return the path to the folder, where the artwork is saved
    */
    QString getArtworkDir();

    /**
    * @brief get the Arguments, passed when launching the game. 
    *
    * @return QStringList of passed Arguments for executable
    */
    QStringList getArgs();
    
    /**
    * @brief Get the Type of Executable/Game 
    *
    * @return type of Executable as FGameType
    */
    FGameType getType();

    
    /**
    * @brief The gamecommand is can be used to Launch a game. 
    * This command is more flexible. If no command is provided, './gamePath/gameExecutable' will be
    * executed
    * @todo Rename this to something like "Custom Exeute-Command"
    *
    * @return Command-String with placeholders, which will be executed 
    */
    QString getCommand();
    
    /**
    * @brief return the Launcher for this Executable, if one is used
    * @todo Check if Launcher is really used, or launcher is nulll
    *
    * @return Object of FLauncher for the selected launcher 
    */
    FLauncher getLauncher();
    
    /**
    * @brief get QDateTime of the last moment, the game was executed in Fusion
    *
    * @return QDateTime, of the moment, the game was executed last
    */
    QDateTime getGameLastPlayed() const;

    /**
    * @brief Set the name of the game/executabe
    * Length needs to be > 0
    *
    * @param val Name of the game
    */
    void setName(QString val);

    /**
    * @brief Set the name of the Executable, which will be executed
    *
    * @param val Name of the Executable
    */
    void setExe(QString val);

    /**
    * @brief Set the absolute path to the directory, which contains the executabe stated in
    * setName()
    *
    * @param val Absolute path, wihich contains the executable
    */
    void setPath(QString val);

    /**
    * @brief Set a List of Arguments, which will be appended to the command of execution. Existing
    * commands will be overwritten.
    *
    * @param val List of Arguments
    */
    void setArgs(QStringList val);

    /**
    * @brief Set the Type of Game.
    * This is mandoratory, as it will determine how the executable is started.
    *
    * @param val Type of the Executable
    */
    void setType(FGameType val);
    void setCommand(QString val);
    void setLauncher(FLauncher launcher);
    void setGameLastPlayed(const QDateTime &value);
    void disableLauncher();
    bool doesUseLauncher();
    bool execute();

    int dbId;

    //Artwork-Stuff
    QString getBoxart(bool fromCache = false, int size=0, FGameSizeConstrain fsc = FWidth);
    QString getClearart(bool fromCache = false, int size=0, FGameSizeConstrain fsc = FWidth);
    QString getFanart(bool fromCache = false, int size=0, FGameSizeConstrain fsc = FWidth);
    QString getBanner(bool fromCache = false, int size=0, FGameSizeConstrain fsc = FWidth);

    QString getArt(FGameArt imgType, bool fromCache = false, int size = 0, FGameSizeConstrain fsc = FWidth);
    static QString FGameArtToStr(FGameArt imgType);
    static QString FGameTypeToStr(FGameType type);
    static QString getCacheDir();

    QDir getSavegameDir() const;
    void setSavegameDir(const QDir &value);
    void setSavegameDir(const QString &value);
    bool savegameSyncEndabled();

    bool syncData();


protected:
    QString gameName;
    FGameType gameType;
    QString gamePath;
    QString gameExe;
    QStringList gameArgs;
    QString gameCommand;
    QDateTime gameLastPlayed;
    QDir savegameDir;
    FLauncher launcher;
    bool launcherEnabled;
    bool syncEnabled;
private:
    QString cachedImage(int size, FGameSizeConstrain fsc, FGameArt imgType);
    QStringList createStringListFromArguments(QString args);
};

#endif // FGAME_H
