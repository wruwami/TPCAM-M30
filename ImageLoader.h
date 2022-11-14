#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QPixmap>

class ImageLoader
{
private:
    ImageLoader() {}
    ImageLoader(const ImageLoader& other);
    ~ImageLoader() {}
    static ImageLoader* instance;
public:
    static ImageLoader* GetInstance()
    {
        if(instance == nullptr) instance = new ImageLoader();
        return instance;
    }

//    void Initialize(std::string path_name, std::string file_name, std::string language);

//    std::map<std::string, QString> LoadString();
    QPixmap LoadImage(std::string path_name, std::string file_name);
//private:
//    void AddInvalidString(std::string str);
//private:
//    std::string m_file_name;
//    std::map <std::string, QString> m_StringResource;
};

static QPixmap LoadImage(std::string path_name, std::string file_name)
{
    return ImageLoader::GetInstance()->LoadImage(path_name, file_name);
}

#endif // IMAGELOADER_H
