//
// Created by phatt on 4/8/25.
//

#ifndef Q_COMPONENT_H
#define Q_COMPONENT_H


#include "QtWidgets.h"


class QComponent : public QGroupBox {
public:
    explicit QComponent(const QString& name, QWidget* parent = nullptr);

private:
};


#endif //Q_COMPONENT_H
