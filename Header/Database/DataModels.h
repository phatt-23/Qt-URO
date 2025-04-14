//
// Created by phatt on 4/12/25.
//

#ifndef DATAMODELS_H
#define DATAMODELS_H


#include <QString>
#include <qdebug.h>
#include <string>

/////////////////////////////////////////
// EMAILS ///////////////////////////////
/////////////////////////////////////////

enum class EmailStatus
{
    SENT,
    DRAFT,
    DELETED,
    SENT_DRAFT,
};

static EmailStatus GetEmailStatusFromString(const std::string& status)
{
    if (status == "sent") return EmailStatus::SENT;
    if (status == "draft") return EmailStatus::DRAFT;
    if (status == "deleted") return EmailStatus::DELETED;
    if (status == "sent_draft") return EmailStatus::SENT_DRAFT;

    throw std::runtime_error("Unknown email status type: " + status);
}

static std::string GetEmailStatusString(EmailStatus status)
{
    switch (status)
    {
        case EmailStatus::SENT: return "sent";
        case EmailStatus::DRAFT: return "draft";
        case EmailStatus::DELETED: return "deleted";
        case EmailStatus::SENT_DRAFT: return "draft";
    }

    throw std::runtime_error(std::format("Unknown email status type: {}", static_cast<int>(status)));
}


struct Email
{
    int EmailId;
    int SenderId;
    QString Subject;
    QString Body;
    EmailStatus Status;
    QString SentAt;
};

/////////////////////////////////////////
/// ATTACHMENT //////////////////////////
/////////////////////////////////////////

struct Attachment
{
    int AttachmentId;
    QString FileName;
    QString FilePath;
    QByteArray Data;
    QString CreatedAt;
};

/////////////////////////////////////////
/// USER ////////////////////////////////
/////////////////////////////////////////

struct User
{
    int UserId;
    QString Email;
    QString FirstName;
    QString LastName;
    QString CreatedAt;
};

/////////////////////////////////////////
/// DEBUG ASPECT ////////////////////////
/////////////////////////////////////////

inline QDebug operator<<(QDebug dbg, const Email& email)
{
    dbg.nospace()
    << "Email("
    << "email_id: " << email.EmailId
    << ", sender_id: " << email.SenderId
    << ", subject: " << email.Subject
    << ", body: " << email.Body
    << ", status: " << GetEmailStatusString(email.Status)
    << ", sent_at: " << email.SentAt
    << ")";
    return dbg;
}

inline QDebug operator<<(QDebug dbg, const Attachment& attachment)
{
    dbg.nospace()
    << "Attachment("
    << "attachment_id: " << attachment.AttachmentId
    << ", file_name: " << attachment.FileName
    << ", file_path: " << attachment.FilePath
    << ", created_at: " << attachment.CreatedAt
    << ")";
    return dbg;
}

inline QDebug operator<<(QDebug dbg, const User& user)
{
    dbg.nospace()
    << "User("
    << "user_id: " << user.UserId
    << ", email: " << user.Email
    << ", first_name: " << user.FirstName
    << ", last_name: " << user.LastName
    << ", created_at: " << user.CreatedAt
    << ")";
    return dbg;
}


#endif //DATAMODELS_H
