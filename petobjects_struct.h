#ifndef PETOBJECTS_STRUCT_H
#define PETOBJECTS_STRUCT_H

#include <QPixmap>

struct PetAppearance
{
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
struct Food
{
    int food_id;
    int food_price;
    int m_hunger;
    int m_number;
    QPixmap food_picture;
    QString food_name;
    Food()
    {}
    Food(int food_id,QString food_pic_path,QString food_name="",int food_price=0,int m_number=0,int m_hunger=0)
        :food_id(food_id)
        ,food_price(food_price)
        ,m_hunger(m_hunger)
        ,m_number(m_number)
        ,food_picture(food_pic_path)
        ,food_name(food_name)
    {}
};


#endif // PETOBJECTS_STRUCT_H
