#include "StringLoader.h"

#include <fstream>
#include <iostream>
#include <list>

#include <QString>
#include <QList>
#include <Qdir>


StringLoader* StringLoader::instance = nullptr;

void StringLoader::Initialize(std::string path_name, std::string file_name, std::string language)
{    
    QDir qdir;
    QString dir = qdir.absolutePath();

    std::ifstream inFile(m_file_name.c_str());
    if (!inFile.is_open()) {
        std::cout << "no file has been opened" << std::endl;
        inFile.close();
        QString dir_qstr;
#ifdef Q_OS_WIN
dir_qstr = dir + "\\" + QString::fromStdString(path_name);
m_file_name = dir_qstr.toStdString() + "\\" + file_name;
#else   /*Q_OS_LINUX*/
    dir_qstr = dir + "/" + QString::fromStdString(path_name);
    m_file_name = dir_qstr.toStdString() + "/" + file_name;
#endif
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
    }

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

    QString input_language = QString::fromStdString(language);
    std::string strLanguage;
    getline( inFile, strLanguage);
    QString qstrLanguage = QString::fromStdString(strLanguage);
    QStringList m_LanguageList = qstrLanguage.split(",");
    int i = m_LanguageList.indexOf(input_language);

    while (!inFile.eof()) {
        std::string strLine;
        getline ( inFile, strLine);
        if (strLine.empty())
            continue;
        QString qstrTmp = QString::fromStdString(strLine);
        QStringList list2 = qstrTmp.split(",");
        m_StringResource[list2[0].toStdString()] = list2[i];
    }
    inFile.close();
}

std::map<std::string, QString> StringLoader::LoadString()
{
    return m_StringResource;
}

QString StringLoader::LoadString(std::string index)
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
