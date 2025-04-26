#include "FormInserter.h"

#include "UserRepo.h"

FormInserter::FormInserter(Ref<DbContext> const& context, Ref<EventBus> const& eventBus)
    : m_EventBus(eventBus)
    , m_DbContext(context)
{

}

FormInserter::~FormInserter()
{
}


bool FormInserter::InsertEmailWithAttachments(Email const& email, QStringList const& recipients, QStringList const& attachments, EmailStatus status) const
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    QSqlQuery insertEmailQuery(m_DbContext->GetDatabase());

    // Insert email
    insertEmailQuery.prepare(R"(
        INSERT INTO email(sender_id, subject, body, status)
        VALUES (:sender_id, :subject, :body, :status)
        RETURNING email_id
    )");

    insertEmailQuery.bindValue(":sender_id", email.SenderId);
    insertEmailQuery.bindValue(":subject", email.Subject);
    insertEmailQuery.bindValue(":body", email.Body);
    insertEmailQuery.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));

    if (!insertEmailQuery.exec())
    {
        throw std::runtime_error("Failed to insert email: " + insertEmailQuery.lastError().text().toStdString());
    }

    insertEmailQuery.next();
    auto const emailId = insertEmailQuery.value("email_id").toInt();

    qInfo() << "Inserted email, got email_id:" << emailId;

    // Insert recipients
    std::for_each(recipients.constBegin(), recipients.constEnd(), [this, emailId](auto const& recipient)
    {
        QSqlQuery query(m_DbContext->GetDatabase());
        query.prepare("SELECT * FROM user WHERE email = :email");
        query.bindValue(":email", recipient);

        if (!query.exec())
        {
            throw std::runtime_error("Failed to query user: " + query.lastError().text().toStdString());
        }

        int userId = 0;

        if (!query.next())
        {
            QSqlQuery insertUser(m_DbContext->GetDatabase());
            insertUser.prepare(R"(
                INSERT INTO user(email, first_name, last_name)
                VALUES (:email, '', '')
                RETURNING user_id
            )");

            insertUser.bindValue(":email", recipient);

            if (!insertUser.exec())
            {
                throw std::runtime_error("Failed to insert user: " + insertUser.lastError().text().toStdString());
            }

            insertUser.next();
            userId = insertUser.value("user_id").toInt();
        }
        else
        {
            userId = query.value("user_id").toInt();
        }

        QSqlQuery insertRecipient(m_DbContext->GetDatabase());
        insertRecipient.prepare(R"(
            INSERT INTO email_recipient(email_id, recipient_id)
            VALUES (:email_id, :recipient_id)
        )");

        insertRecipient.bindValue(":email_id", emailId);
        insertRecipient.bindValue(":recipient_id", userId);

        if (!insertRecipient.exec())
        {
            throw std::runtime_error("Failed to insert email recipient: " + insertRecipient.lastError().text().toStdString());
        }
    });

    // Insert attachments
    std::for_each(attachments.constBegin(), attachments.constEnd(), [this, emailId](QString const& attachment)
    {
        QFile file(attachment);
        if (!file.open(QIODevice::ReadOnly))
        {
            qWarning() << "Failed to open file:" << attachment;
            return;
        }

        QByteArray blob = file.readAll();
        file.close();

        QSqlQuery insertAttachment(m_DbContext->GetDatabase());
        insertAttachment.prepare(R"(
            INSERT INTO attachment(filename, filepath, data)
            VALUES (:filename, :filepath, :data)
            RETURNING attachment_id
        )");

        insertAttachment.bindValue(":filename", QFileInfo(attachment).fileName());
        insertAttachment.bindValue(":filepath", attachment);
        insertAttachment.bindValue(":data", blob);

        if (!insertAttachment.exec())
        {
            throw std::runtime_error("Failed to insert attachment: " + insertAttachment.lastError().text().toStdString());
        }

        insertAttachment.next();
        auto const attachmentId = insertAttachment.value("attachment_id").toInt();

        QSqlQuery linkAttachment(m_DbContext->GetDatabase());
        linkAttachment.prepare(R"(
            INSERT INTO email_attachment(email_id, attachment_id)
            VALUES (:email_id, :attachment_id)
        )");

        linkAttachment.bindValue(":email_id", emailId);
        linkAttachment.bindValue(":attachment_id", attachmentId);

        if (!linkAttachment.exec())
        {
            throw std::runtime_error("Failed to link attachment to email: " + linkAttachment.lastError().text().toStdString());
        }
    });

    m_EventBus->ForwardEmit<EmailWithAttachmentsInsertedEvent>();

    return true;
}
