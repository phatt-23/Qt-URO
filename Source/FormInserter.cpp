#include "FormInserter.h"

FormInserter::FormInserter(Ref<DbContext> const& context, Ref<EventBus> const& eventBus)
    : m_EventBus(eventBus)
    , m_DbContext(context)
{

}

FormInserter::~FormInserter()
{
}


bool FormInserter::InsertEmailWithAttachments(Email const& email, QStringList const& attachments, EmailStatus status) const
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    qInfo() << "-------------------------------------";
    QSqlQuery insertEmailQuery(m_DbContext->GetDatabase());
    qInfo() << "-------------------------------------";

    // insert email
    insertEmailQuery.prepare(R"(
        INSERT INTO email(sender_id, subject, body, status)
        VALUES (:sender_id, :subject, :body, :status)
        RETURNING email_id
    )");
    qInfo() << "-------------------------------------";

    insertEmailQuery.bindValue(":sender_id", email.SenderId);
    insertEmailQuery.bindValue(":subject", email.Subject);
    insertEmailQuery.bindValue(":body", email.Body);
    insertEmailQuery.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));

    qInfo() << "Getting the returning email_id";
    if (!insertEmailQuery.exec())
    {
        throw std::runtime_error("Query failed to execute.");
    }

    insertEmailQuery.next();
    auto const emailId = insertEmailQuery.value("email_id").toInt();

    qInfo() << "INSERTED EMAIL, GOT EMAIL_ID:" << emailId;


    // insert attachments
    // associate attachments with the email
    std::for_each(attachments.constBegin(), attachments.constEnd(), 
    [this, emailId](QString const& attachment)
    {
        QString filepath;
        const QString filename = filepath = attachment;

        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly)) 
            return;

        QByteArray blob = file.readAll();

        QSqlQuery insertAttachment(m_DbContext->GetDatabase());
        insertAttachment.prepare(R"(
            INSERT INTO attachment(filename, filepath, data)
            VALUES (:filename, :filepath, :data)
            RETURNING attachment_id
        )");

        insertAttachment.bindValue(":filename", filename);
        insertAttachment.bindValue(":filepath", filepath);
        insertAttachment.bindValue(":data", blob);

        if (!insertAttachment.exec())
        {
            throw std::runtime_error("Query failed to execute!" + insertAttachment.lastError().text().toStdString());
        }

        insertAttachment.next();
        auto const attachmentId = insertAttachment.value("attachment_id").toInt();

        qInfo() << "INSERTED ATTACHMENT" << filename << "RETURNED ID:" << attachmentId;

        QSqlQuery linkAttachment(m_DbContext->GetDatabase());
        linkAttachment.prepare(R"(
            INSERT INTO email_attachment(email_id, attachment_id)
            VALUES (:email_id, :attachment_id)
        )");

        linkAttachment.bindValue(":email_id", emailId);
        linkAttachment.bindValue(":attachment_id", attachmentId);
        if (!linkAttachment.exec())
        {
            throw std::runtime_error("Query failed to execute!" + linkAttachment.lastError().text().toStdString());
        }
    });

    m_EventBus->ForwardEmit<EmailWithAttachmentsInsertedEvent>();

    return true;
}
