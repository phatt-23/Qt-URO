//
// Created by phatt on 4/25/25.
//

#ifndef BASEVIEW_H
#define BASEVIEW_H
#include "QComponent.h"


class BaseView : public QComponent {
public:
    BaseView(QString const& widgetName, QWidget* parent);
    ~BaseView() override = default;

    virtual void OnEnter() {}
};



#endif //BASEVIEW_H
