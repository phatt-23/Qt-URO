//
// Created by phatt on 4/26/25.
//

#ifndef EMAILEDITORTOOLBAR_H
#define EMAILEDITORTOOLBAR_H
#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailEditorToolbar final : public QComponent {
    Q_OBJECT
public:
    friend class EmailEditor;

    enum ToolbarButtons
    {
        SEND,
        SAVE,
        ATTACH
    };

signals:
    void SendButtonClicked();
    void SaveButtonClicked();
    void AttachButtonClicked();

public:
    EmailEditorToolbar(Ref<DIContainer> const& diContainer, QWidget* parent);

private:
    void BindEvents() override;

private:
    QMap<ToolbarButtons, QPushButton*> m_ToolbarButtons;
    Ref<DIContainer> m_DiContainer;
};



#endif //EMAILEDITORTOOLBAR_H
