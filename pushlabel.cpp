#include "pushlabel.h"

PushLabel::PushLabel(int lable_index,QWidget* parent)
    :QLabel(parent)
    ,label_index_(lable_index)
    {}

void PushLabel::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton) {
            emit clicked(label_index_);
        }
        QLabel::mousePressEvent(event);
    }
