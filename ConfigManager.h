/**
 * @file ConfigManager.h
 * @author wruwami (wruwami@naver.com)
 * @brief json 설정파일을 읽고 쓰는 기능
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <map>
#include <vector>

using namespace std;

class ConfigManager
{
public:
    ConfigManager(QString file_name);
    QJsonObject GetConfig();
    void SetConfig(QJsonObject);
    QString GetText();
    void SaveFile();
private:
    QJsonDocument m_jsonDocument;
    QString m_file_full_path;
    QString m_text;
};

static bool cmp(std::pair<std::string, int>& a,
         std::pair<std::string, int>& b)
{
    return a.second > b.second;
}

static void sort(std::map<std::string, int>& map, std::vector<std::pair<std::string, int>>& vec)
{
//    std::vector<std::pair<std::string, int> > vec;

    for (auto& it : map) {
        vec.emplace_back(it);
    }

    // 우리가 위에서 정의한 cmp
    sort(vec.begin(), vec.end(), cmp);

//    return vec;
//    for (auto& it : vec)
//		cout << it.first << " " << it.second << endl;

}


#endif // CONFIGMANAGER_H
