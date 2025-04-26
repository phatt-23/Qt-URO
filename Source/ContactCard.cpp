//
// Created by phatt on 4/25/25.
//

#include "ContactCard.h"

#include <QVBoxLayout>

#include "Utility/CreateKeyValueRow.h"

ContactCard::ContactCard(const QString& email, const QString& firstName, const QString& lastName, QWidget* parent)
    : QComponent("ContactCard", parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Create a row for each key-value pair
    layout->addLayout(CreateKeyValueRow("Email:", email, this));
    layout->addLayout(CreateKeyValueRow("First Name:", firstName, this));
    layout->addLayout(CreateKeyValueRow("Last Name:", lastName, this));
}
