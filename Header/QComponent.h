//
// Created by phatt on 4/8/25.
//

#ifndef Q_COMPONENT_H
#define Q_COMPONENT_H


#include <QGroupBox>


class QComponent : public QFrame
{
    Q_OBJECT
public:
    explicit QComponent(const QString& name, QWidget* parent = nullptr);

protected:
    virtual void BindEvents();
};


#endif //Q_COMPONENT_H
