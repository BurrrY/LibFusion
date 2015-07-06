#include "fcrawler.h"
#include "fgame.h"

#include <QVariantMap>

FCrawler::FCrawler()
{

}

FCrawler::~FCrawler()
{

}

void FCrawler::scanAllFolders()
{
    db.beginTransaction();

    QList<QDir> folder =db.getWatchedFoldersList();
    for(int i=0;i<folder.length();++i) {

        FGameType folderType = getType(folder.at(i));
        if(folderType==FGameType::Steam) {
            getSteamGames(folder.at(i));
        } else if (folderType==FGameType::Galaxy) {
            getGalaxyGames(folder.at(i));
        }
    }

    //Origin only on Windows
    #if OS == Windows
        getOriginGames();
    #endif

    db.endTransaction();
}


FGameType FCrawler::getType(QDir folder) {

    //TODO: Proper Type-Check
    folder.setNameFilters(QStringList()<<"*.acf");
    QStringList steamFiles = folder.entryList();

    if(steamFiles.length()>0)
        return FGameType::Steam;
/*
    folder = folder.absolutePath() + QDir::separator() + "!Downloads";
    if(folder.exists())
        return FGameType::Galaxy;
*/
    return FGameType::unknown;
}

void FCrawler::getGalaxyGames(QDir folder) {
    QStringList subfolders = folder.entryList();

    for(int i=0;i<subfolders.length();++i) {
        if(subfolders[i]=="!Downloads")
            continue;

        //Get Info-File
        QStringList filters;
        filters << "goggame-*.info";

        QDir dir(folder.absolutePath()  + QDir::separator() + subfolders[i]);
        QStringList InfoFile = dir.entryList(filters);
        if(InfoFile.length()==1) {

        }
        else
            continue;
    }
}


void FCrawler::getOriginGames() {

    QString file = "C:\\ProgramData\\Origin\\Logs\\Client_Log.txt";
    QList<QString> doneIDs;

    QFile oLogFile;
    oLogFile.setFileName(file);

    if(!oLogFile.exists())
        return;

    oLogFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QString fileContent = oLogFile.readAll();
    QStringList fileLines = fileContent.split("\n");
    oLogFile.close();

    //Example-String:
    // 457    May 26 17:59:46.363 Event     Origin::Downloader::ContentProtocolPackage::InitializeVerified              7460      [Game Title: Mass Effect 2 Digital Art Books][ProductID:OXX-MASS:57404]CRC Calculation Complete.
    for(int i=0;i<fileLines.length();++i){
        QString line = fileLines[i];
        if(line.contains("Finished: ")) {

            int gamenameLength = line.indexOf(", ctid:", 135)-135;
            QString gameName = line.mid(135, gamenameLength);

            QString gameID = line.right(7);

            if(!doneIDs.contains(gameID)) {
                FGame g;
                g.setPath("-");
                g.setName(gameName);
                g.setType(FGameType::Origin);
                g.setExe(gameID);

                doneIDs.append(gameID);

                if(!db.gameExists(g)){
                   if(!db.addGame(g))
                       qDebug() << "Error on insert Game!";
                }
                else
                    qDebug() << "Game exists: " << g.getName();
            }
        }

    }
}



void FCrawler::getSteamGames(QDir folder) {
    folder.setNameFilters(QStringList()<<"*.acf");
    QStringList steamFiles = folder.entryList();
    for(QString file : steamFiles) {

        //Get File-Content
        QFile f;
        f.setFileName(folder.absoluteFilePath(file));
        f.open(QIODevice::ReadOnly|QIODevice::Text);
        QString fileContent = f.readAll();
        f.close();

        QStringList fileLines = fileContent.replace("\"", "").split("\n");

        //Create Game
        FGame g;
        g.setName(fileLines[4].split("\t")[3]);
        g.setType(FGameType::Steam);
        g.setExe(fileLines[2].split("\t")[3]);
        g.setPath("-");

        if(!db.gameExists(g)){
           if(!db.addGame(g))
               qDebug() << "Error on insert Game!";
        }
        else
            qDebug() << "Game exists: " << g.getName();
    }
}