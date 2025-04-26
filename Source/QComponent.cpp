//
// Created by phatt on 4/8/25.
//

#include "../Header/QComponent.h"

QComponent::QComponent(const QString& name, QWidget* parent)
    // : QGroupBox(name, parent)
    : QFrame(parent)
{
    // Set a frame style similar to QGroupBox
    // setFrameStyle(QFrame::Panel | QFrame::Raised);
    // setLineWidth(1);
}


void QComponent::BindEvents()
{
}
