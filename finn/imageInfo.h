#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QString>

class ImageInfo {
public:
    QString imagePath; // 图片路径
    QString description; // 对应的描述

    ImageInfo(const QString &imagePath, const QString &description): imagePath(imagePath), description(description) {}
};

#endif // IMAGEINFO_H
