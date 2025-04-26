//
// Created by phatt on 4/8/25.
//

#ifndef EMAILEDITOR_H
#define EMAILEDITOR_H


#include <qcombobox.h>

#include "DIContainer.h"
#include "EmailEditorBody.h"
#include "EmailEditorHeader.h"
#include "EmailEditorToolbar.h"
#include "EventBus.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailEditorBody;

class EmailEditor final : public QComponent {
    Q_OBJECT
public:
    struct DataContext {
        explicit DataContext(
            QString const& sender,
            QStringList const& recipients,
            QString const& subject,
            QString const& body
        )
            : Sender(sender)
            , Recipients(recipients)
            , Subject(subject)
            , Body(body) {}

        QString Sender;
        QStringList Recipients;
        QString Subject;
        QString Body;
    };


public:
    explicit EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailEditor() override;

    [[nodiscard]] DataContext GetDataContext() const
    {
        QStringList recipients = m_Header->m_RecipientsLineEdit->text().split(',', Qt::SkipEmptyParts);
        QStringList recipientsTrimmed;
        for (auto r : recipients)
        {
            recipientsTrimmed.append(r.trimmed());
        }

        return DataContext(
            m_Header->m_SenderLineEdit->text(),
            recipientsTrimmed,
            m_Header->m_SubjectLineEdit->text(),
            m_Body->GetText());
    }

    void SetReadonly(const bool value) const
    {
        m_Header->m_SubjectLineEdit->setReadOnly(value);
        m_Header->m_RecipientsLineEdit->setReadOnly(value);
        m_Body->m_TextBody->setReadOnly(value);
    }

    void SetEntries(QString const& recipients, QString const& subject, QString const& body) const
    {
        m_Header->m_RecipientsLineEdit->setText(recipients);
        m_Header->m_SubjectLineEdit->setText(subject);
        m_Body->m_TextBody->setText(body);
    }

    void ClearEntries() const
    {
        m_Header->m_RecipientsLineEdit->clear();
        m_Header->m_SubjectLineEdit->clear();
        m_Body->m_TextBody->clear();
    }

private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    EmailEditorToolbar* m_Toolbar;
    EmailEditorHeader* m_Header;
    EmailEditorBody* m_Body;
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
    << "sender: " << d.Sender
    << ", recipients: " << d.Recipients
    << ", subject: " << d.Subject
    << ", text: " << d.Body;
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
