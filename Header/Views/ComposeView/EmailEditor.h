//
// Created by phatt on 4/8/25.
//

#ifndef EMAILEDITOR_H
#define EMAILEDITOR_H


#include <qcombobox.h>

#include "DIContainer.h"
#include "EventBus.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailEditor final : public QComponent {
public:
    struct DataContext {
        explicit DataContext(QWidget* parent)
            : SenderLineEdit(parent)
            , RecipientsLideEdit(parent)
            , SubjectLineEdit(parent)
            , TextBody(parent) {}

        QLineEdit SenderLineEdit;
        QLineEdit RecipientsLideEdit;
        QLineEdit SubjectLineEdit;
        QTextEdit TextBody;
    };

    enum ToolbarButtons { SEND, SAVE, ATTACH };

public:
    explicit EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailEditor() override;

    const DataContext& GetDataContext() const { return *m_Data.get(); }


    inline void SetReadonly(const bool value) const
    {
        m_Data->RecipientsLideEdit.setReadOnly(value);
        m_Data->SubjectLineEdit.setReadOnly(value);
        m_Data->TextBody.setReadOnly(value);
    }

    inline void SetEntries(QString const& recipients, QString const& subject, QString const& body) const
    {
        m_Data->RecipientsLideEdit.setText(recipients);
        m_Data->SubjectLineEdit.setText(subject);
        m_Data->TextBody.setText(body);
    }

    inline void ClearEntries() const
    {
        m_Data->RecipientsLideEdit.clear();
        m_Data->SubjectLineEdit.clear();
        m_Data->TextBody.clear();
    }

    void RenewContacts();

private:
    void BindEvents() override;
    void ShowContactMenu();

private:
    Ref<DIContainer> m_DiContainer;

    QComponent m_ToolbarFrame;
    QMap<ToolbarButtons, QPushButton*> m_ToolbarButtons;

    QComponent m_HeaderFrame;
    QComponent m_BodyFrame;

    Scope<DataContext> m_Data;

    QPushButton* m_ContactChooser;
};

/////////////////////////////////////////
// Events emitted by this component
/////////////////////////////////////////

struct SendEmailClickedEvent final : public EventBase 
{
    SendEmailClickedEvent(const EmailEditor::DataContext& data) : EventBase(), Data(data) {}
    const EmailEditor::DataContext& Data;
};

struct SaveEmailClickedEvent final : public EventBase 
{
    SaveEmailClickedEvent(const EmailEditor::DataContext& data) : EventBase(), Data(data) {}
    const EmailEditor::DataContext& Data;
};

/// Attachment(s) is/are chosen from the file dialog.
struct AttachToEmailEvent final : public EventBase 
{
    AttachToEmailEvent(const QStringList& attachments) : Attachments(attachments) {}
    QList<QString> Attachments;
};

////////////////////////////////////////
/// DEBUG //////////////////////////////
////////////////////////////////////////

inline QDebug operator<<(QDebug dbg, const EmailEditor::DataContext& d)
{
    dbg.nospace()
    << "sender: " << d.SenderLineEdit.text()
    << ", recipients: " << d.RecipientsLideEdit.text()
    << ", subject: " << d.SubjectLineEdit.text()
    << ", text: " << d.TextBody.toPlainText();
    return dbg;
}

inline QDebug operator<<(QDebug dbg, const SendEmailClickedEvent& e)
{
    dbg.nospace() << "SendEmailClickedEvent(" << e.Data << ")";
    return dbg;
}

inline QDebug operator<<(QDebug dbg, const SaveEmailClickedEvent& e)
{
    dbg.nospace() << "SaveEmailClickedEvent(" << e.Data << ")";
    return dbg;
}

inline QDebug operator<<(QDebug dbg, const AttachToEmailEvent& e)
{
    dbg.nospace() << "AttachToEmailEvent(attachments: " << e.Attachments << ")";
    return dbg;
}



#endif //EMAILEDITOR_H
