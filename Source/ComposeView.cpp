//
// Created by phatt on 4/7/25.
//

#include "../Header/Views/ComposeView.h"

#include "EmailEditor.h"


ComposeView::ComposeView(const Ref<DIContainer>& diContainer, QWidget* parent, const bool isDialog)
    : QComponent("ComposeView", parent), m_DiContainer(diContainer)
    // init children
    , m_Splitter(Qt::Horizontal, this)
    , m_LeftSplit("LeftSplit", this)
    , m_RightSplit("RightSplit", this)
    , m_EmailEditor(m_DiContainer, &m_LeftSplit)
    , m_AttachmentSideBar(m_DiContainer, &m_RightSplit)
    , m_IsDialog(isDialog)
{
    // split widgets
    m_Splitter.addWidget(&m_LeftSplit);
    m_Splitter.addWidget(&m_RightSplit);

    m_Splitter.setSizes({400, 200});
    m_Splitter.setStretchFactor(0, 4);
    m_Splitter.setStretchFactor(1, 3);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_Splitter);

    // left split
    const auto leftSplitLayout = new QVBoxLayout(&m_LeftSplit);
    leftSplitLayout->addWidget(&m_EmailEditor);

    if (m_IsDialog == false)
    {
        m_OpenInNewButton = CreateScope<QPushButton>("Open in New", &m_LeftSplit);
        const auto buttonLayout = new QHBoxLayout();
        leftSplitLayout->addLayout(buttonLayout);
        buttonLayout->addStretch();
        buttonLayout->addWidget(m_OpenInNewButton.get());
    }

    leftSplitLayout->setStretch(0, 4);
    leftSplitLayout->setStretch(1, 0);

    // right split
    const auto rightSplitLayout = new QVBoxLayout(&m_RightSplit);
    rightSplitLayout->addWidget(&m_AttachmentSideBar);

    // events
    connect(m_OpenInNewButton.get(), &QPushButton::clicked, this, &ComposeView::OpenInNewButtonClicked);
}

void ComposeView::OpenInNewButtonClicked()
{
    const auto bus = m_DiContainer->GetService<EventBus>();

    const auto dialog = new QDialog();
    dialog->setWindowTitle("Compose Email");
    dialog->resize(800, 600);

    const auto composeView = new ComposeView(m_DiContainer, this, true);

    const auto dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->addWidget(composeView);

    dialog->show();
}

