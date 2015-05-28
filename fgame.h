#ifndef QTCORE
#include <QtCore>
#endif

#ifndef FGAME_H
#define FGAME_H

enum FGameType {unknown, Executable, Steam, Origin, Uplay};

class FGame
{
public:
    FGame (QString gName, FGameType gType, QString gDir, QString exePath, QStringList args);
    FGame();
    QString getName();
    QString getExe();
    QString getPath();
    QStringList getArgs();
    FGameType getType();


    void setName(QString val);
    void setExe(QString val);
    void setPath(QString val);
    void setArgs(QStringList val);
    void setType(FGameType val);
    bool execute();
    int dbId;


    friend bool operator==(const  FGame &g1, const  FGame &g2)
    {
         return (g1.getName()==g2.getName() && g1.getExe()==g2.getExe());
    }


private:
    QString gameName;
    FGameType gameType;
    QString gamePath;
    QString gameExe;
    QStringList gameArgs;
};

#endif // FGAME_H
