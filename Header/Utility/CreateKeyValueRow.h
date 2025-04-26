//
// Created by phatt on 4/25/25.
//

#ifndef CREATEKEYVALUEROW_H
#define CREATEKEYVALUEROW_H

#include "QtWidgets.h"

inline QHBoxLayout* CreateKeyValueRow(const QString& key, const QString& value, QWidget* parent)
{
    auto* rowLayout = new QHBoxLayout();
    rowLayout->setContentsMargins(0, 0, 0, 0);
    rowLayout->setSpacing(0);

    auto* keyLabel = new QLabel(key, parent);
    keyLabel->setMinimumWidth(100);
    keyLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    auto* valueLabel = new QLabel(value, parent);
    valueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // Allow the value to expand
    valueLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    rowLayout->addWidget(keyLabel);
    rowLayout->addWidget(valueLabel);

    return rowLayout;
}

inline QHBoxLayout* CreateKeyValueRow(const QString& key, QWidget* value, QWidget* parent)
{
    auto* rowLayout = new QHBoxLayout();
    rowLayout->setContentsMargins(0, 0, 0, 0);
    rowLayout->setSpacing(0);

    auto* keyLabel = new QLabel(key);
    keyLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    value->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // Allow the value to expand

    rowLayout->addWidget(keyLabel);
    rowLayout->addSpacing(4);
    rowLayout->addWidget(value);

    return rowLayout;
}

#endif //CREATEKEYVALUEROW_H
