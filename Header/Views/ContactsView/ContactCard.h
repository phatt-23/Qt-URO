//
// Created by phatt on 4/25/25.
//

#ifndef CONTACTCARD_H
#define CONTACTCARD_H
#include "QComponent.h"


class ContactCard final : public QComponent {
    Q_OBJECT
public:
    explicit ContactCard(const QString& email, const QString& firstName, const QString& lastName, QWidget* parent);
    ~ContactCard() override = default;
};



#endif //CONTACTCARD_H
