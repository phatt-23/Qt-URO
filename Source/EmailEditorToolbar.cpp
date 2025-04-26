//
// Created by phatt on 4/26/25.
//

#include "../Header/Views/ComposeView/EmailEditorToolbar.h"

EmailEditorToolbar::EmailEditorToolbar(Ref<DIContainer> const& diContainer, QWidget* parent): QComponent("EmailEditorToolbar", parent)
    , m_DiContainer(diContainer)
{
    // toolbar frame
    m_ToolbarButtons[SEND] = new QPushButton("Send", this);
    m_ToolbarButtons[SAVE] = new QPushButton("Save", this);
    m_ToolbarButtons[ATTACH] = new QPushButton("Attach", this);

    const auto toolbarLayout = new QHBoxLayout(this);
    toolbarLayout->setContentsMargins(0, 0, 0, 0);
    toolbarLayout->setSpacing(0);
    toolbarLayout->addWidget(m_ToolbarButtons[SEND]);
    toolbarLayout->addWidget(m_ToolbarButtons[SAVE]);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(m_ToolbarButtons[ATTACH]);

    BindEvents();
}

void EmailEditorToolbar::BindEvents()
{
    connect(m_ToolbarButtons[SEND], &QPushButton::clicked, [this] {
        emit SendButtonClicked();
    });

    connect(m_ToolbarButtons[SAVE], &QPushButton::clicked, [this] {
        emit SaveButtonClicked();
    });

    connect(m_ToolbarButtons[ATTACH], &QPushButton::clicked, [this] {
        emit AttachButtonClicked();
    });
}
