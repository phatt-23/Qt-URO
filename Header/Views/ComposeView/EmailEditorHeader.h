//
// Created by phatt on 4/26/25.
//

#ifndef EMAILEDITORHEADER_H
#define EMAILEDITORHEADER_H
#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailEditorHeader final : public QComponent {
    Q_OBJECT

signals:
    void ContactChosen(QString const& contact);
public:
    friend class EmailEditor;

public:
    explicit EmailEditorHeader(Ref<DIContainer> const& diContainer, QWidget* parent);
    void BindEvents() override;

private:
    void ShowContactMenu();

private:
    Ref<DIContainer> m_DiContainer;

    QLineEdit *m_SenderLineEdit, *m_RecipientsLineEdit, *m_SubjectLineEdit;
    QPushButton *m_ContactChooser;
};



#endif //EMAILEDITORHEADER_H
