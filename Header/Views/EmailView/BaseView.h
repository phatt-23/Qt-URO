//
// Created by phatt on 4/25/25.
//

#ifndef BASEVIEW_H
#define BASEVIEW_H
#include "QComponent.h"


class BaseView : public QComponent {
    Q_OBJECT
public:
    BaseView(QString const& widgetName, QWidget* parent);
    virtual ~BaseView() override = default;

    virtual void OnEnter() {}
};



#endif //BASEVIEW_H
