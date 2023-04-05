#ifndef PETOBJECTS_STRUCT_H
#define PETOBJECTS_STRUCT_H

#include <QPixmap>

struct PetAppearance{
    int app_id;
    int app_price;
    QPixmap app_picture;
    QString app_name;
    PetAppearance()
    {}
    PetAppearance(int app_id,QString app_pic_path,QString app_name="",int app_price=0)
        :app_id(app_id)
        ,app_price(app_price)
        ,app_picture(app_pic_path)
        ,app_name(app_name)
    {}
};


#endif // PETOBJECTS_STRUCT_H
