#ifndef PUSHLABLE_H
#define PUSHLABLE_H

#include <QLabel>
#include <QMouseEvent>

class PushLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PushLabel(int label_index,QWidget* parent=nullptr);
    int GetLableIndex(){return label_index_;}
signals:
    void clicked(int label_index);
protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    int label_index_;
};


#endif // PUSHLABLE_H
