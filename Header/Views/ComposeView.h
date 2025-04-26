//
// Created by phatt on 4/7/25.
//

#ifndef COMPOSEVIEW_H
#define COMPOSEVIEW_H


#include "AttachmentSideBar.h"
#include "EmailEditor.h"
#include "QComponent.h"
#include "StdLib.h"
#include "EmailView/BaseView.h"


class ComposeView final : public BaseView {
    Q_OBJECT
public:
    explicit ComposeView(const Ref<DIContainer>& diContainer, QWidget* parent, const bool isDialog = false);

    void SetIsDialog(const bool value) { m_IsDialog = value; }
    void OnEnter() override;

private:
    void BindEvents() override;
    void OpenInNewButtonClicked();

    void ClearContent() const;
    void SetContent(
        QString const& recipients,
        QString const& subject,
        QString const& body,
        QStringList const& attachments) const;

private:
    Ref<DIContainer> m_DiContainer;

    QSplitter* m_Splitter;
    QComponent* m_LeftSplit;
    QComponent* m_RightSplit;

    EmailEditor* m_EmailEditor;
    AttachmentSideBar* m_AttachmentSideBar;
    QPushButton* m_OpenInNewButton;

    bool m_IsDialog;
};



#endif //COMPOSEVIEW_H
