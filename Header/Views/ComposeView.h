//
// Created by phatt on 4/7/25.
//

#ifndef COMPOSEVIEW_H
#define COMPOSEVIEW_H


#include "AttachmentSideBar.h"
#include "Core.h"
#include "EmailEditor.h"
#include "QComponent.h"
#include "StdLib.h"


class ComposeView final : public QComponent {
public:
    explicit ComposeView(const Ref<DIContainer>& diContainer, QWidget* parent, const bool isDialog = false);

    void SetIsDialog(const bool value) { m_IsDialog = value; }

private:
    void OpenInNewButtonClicked();

private:
    Ref<DIContainer> m_DiContainer;

    QSplitter m_Splitter;
    QComponent m_LeftSplit;
    QComponent m_RightSplit;

    EmailEditor m_EmailEditor;
    AttachmentSideBar m_AttachmentSideBar;
    Scope<QPushButton> m_OpenInNewButton;

    bool m_IsDialog;
};



#endif //COMPOSEVIEW_H
