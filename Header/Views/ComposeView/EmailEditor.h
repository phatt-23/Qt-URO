//
// Created by phatt on 4/8/25.
//

#ifndef EMAILEDITOR_H
#define EMAILEDITOR_H


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
            , SubjectLideEdit(parent)
            , TextBody(parent) {}

        QLineEdit SenderLineEdit;
        QLineEdit RecipientsLideEdit;
        QLineEdit SubjectLideEdit;
        QTextEdit TextBody;
    };

    enum ToolbarButtons { SEND, SAVE, ATTACH };

public:
    explicit EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailEditor() override;

    const DataContext& GetDataContext() const { return *m_Data.get(); }

private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QComponent m_ToolbarFrame;
    QMap<ToolbarButtons, QPushButton*> m_ToolbarButtons;

    QComponent m_HeaderFrame;
    QComponent m_BodyFrame;

    Scope<DataContext> m_Data;
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
    << ", subject: " << d.SubjectLideEdit.text()
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
