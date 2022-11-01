#include "StringLoader.h"

#include <QString>
#include <QList>
#include <fstream>
#include <iostream>

#include <list>

StringLoader* StringLoader::instance = nullptr;

void StringLoader::Initialize(std::string file_name, std::string language)
{
    m_file_name = file_name;
    std::ifstream inFile(m_file_name.c_str());
    if (!inFile.is_open()) {
        std::cout << "no file has been opened" << std::endl;

        return;
    }

    QString input_language = QString::fromStdString(language);
    std::string strLanguage;
    getline( inFile, strLanguage);
    QString qstrLanguage = QString::fromStdString(strLanguage);
    QStringList list = qstrLanguage.split(",");
    int i = list.indexOf(input_language);

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
    inFile << str + ",," + str + "\n";
    inFile.close();
}
