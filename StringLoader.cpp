#include "StringLoader.h"

#include <fstream>
#include <iostream>
#include <list>

#include <QString>
#include <QList>
#include "qdir.h"

#include "rapidcsv.h"
#include "FileManager.h"

using namespace ResourceLoader;
StringLoader* StringLoader::instance = nullptr;

void StringLoader::Initialize(std::string path_name, std::string file_name, std::string language)
{    
    QDir qdir;
    QString dir = GeteMMCPath();

    QString dir_qstr;
#ifdef Q_OS_WIN
dir_qstr = dir + "\\" + QString::fromStdString(path_name);
m_file_name = dir_qstr.toStdString() + "\\" + file_name;
#else   /*Q_OS_LINUX*/
    dir_qstr = dir + "/" + QString::fromStdString(path_name);
    m_file_name = dir_qstr.toStdString() + "/" + file_name;
#endif

    std::ifstream inFile(m_file_name.c_str());
    if (!inFile.is_open()) {
        std::cout << "no file has been opened" << std::endl;
        inFile.close();

        qdir.mkdir(dir_qstr);

#ifdef Q_OS_WIN
        std::ofstream outFile((dir_qstr.toStdString() + "\\" +file_name).c_str());
#else   /*Q_OS_LINUX*/
        std::ofstream outFile((dir_qstr.toStdString() + "/" + file_name).c_str());
#endif


        std::cout << "new file has been created" << std::endl;
        outFile << "Index,English" << std::endl;
        //        outFile
        outFile.close();

#ifdef Q_OS_WIN
        inFile.open((dir.toStdString() + "\\" + path_name + "\\" + file_name).c_str());
#else   /*Q_OS_LINUX*/
        inFile.open((dir.toStdString() + "/" + path_name + "/" + file_name).c_str());
#endif

        if (!inFile.is_open()) {
            std::cout << "no file has been opened" << std::endl;
            inFile.close();
            return;
        }
    }
    inFile.close();

    rapidcsv::Document doc(m_file_name, rapidcsv::LabelParams(0, 0));

    std::vector<std::string> row = doc.GetRow<std::string>(-1);
    foreach (std::string language, row) {
        m_LanguageList.append(QString::fromStdString(language));
    }
//    m_LanguageList.removeOne("Index");

    std::vector<std::string> col = doc.GetColumn<std::string>(-1);
    foreach (std::string index, col) {
        try {
            m_StringResource[index] = QString::fromStdString(doc.GetCell<std::string>(language, index));
        }  catch (...) {
            m_StringResource[index] = QString::fromStdString(index);
        }

    }

    m_Language = QString::fromStdString(language);

//    QString input_language = QString::fromStdString(language);
//    std::string strLanguage;
//    getline( inFile, strLanguage);
//    QString qstrLanguage = QString::fromStdString(strLanguage);
//    m_LanguageList = qstrLanguage.split(",");
//    m_LanguageList.removeFirst();
//    int i = m_LanguageList.indexOf(input_language) + 1;

//    while (!inFile.eof()) {
//        std::string strLine;
//        getline ( inFile, strLine);
//        if (strLine.empty())
//            continue;
//        QString qstrTmp = QString::fromStdString(strLine);
//#if 1
//        QStringList list2 = Split(qstrTmp);
//#else
//        QStringList list2 = qstrTmp.split(",");
//        if (list2[i][0] == '\"')
//            list2[i] = list2[i].remove("\"") + "," + list2[i+1].remove("\"");
//#endif
//        m_StringResource[list2[0].toStdString()] = list2[i];

//    }
}

std::map<std::string, QString> StringLoader::GetString()
{
    return m_StringResource;
}

QString StringLoader::GetString(std::string index)
{
    if (m_StringResource.find(index) != m_StringResource.end())
    {

        return m_StringResource[index];
    }

    m_StringResource[index] = QString::fromStdString(index);
    AddInvalidString(index);
    return QString::fromStdString(index);
}

void StringLoader::AddInvalidString(std::string str)
{
    std::ofstream inFile(m_file_name.c_str(), std::ios::app);
    if (!inFile.is_open()) {
        std::cout << "no file has been opened" << std::endl;

        return;
    }

    if (str.find(",") != std::string::npos)
    {
        str.insert(0, "\"");
        str.append("\"");
    }
    inFile << str + "," + str + "\n";
    inFile.close();
}

QStringList StringLoader::LoadLanuageList()
{
    return m_LanguageList;
}

QString StringLoader::GetLanguage()
{
    return m_Language;
}
