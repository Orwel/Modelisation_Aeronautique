#ifndef LOADERXML_H
#define LOADERXML_H

#include <string>

class Scene;

class LoaderXML
{
public:
    LoaderXML();
    ~LoaderXML();

    static void LoadModel(Scene &scene,const std::string &patch);

private:
    const std::string directory;
};

#endif // LOADERXML_H
