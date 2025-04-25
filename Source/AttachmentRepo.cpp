//
// Created by phatt on 4/13/25.
//


#include "AttachmentRepo.h"


AttachmentRepo::AttachmentRepo(const Ref<DbContext>& dbService)
    : m_DbService(dbService)
{
}

AttachmentRepo::~AttachmentRepo()
{
}

QList<Attachment> AttachmentRepo::GetAttachments(const int emailId) const
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    QSqlQuery query(m_DbService->GetDatabase());
    query.prepare(R"(
        SELECT a.*
        FROM attachment a
        JOIN email_attachment ea ON a.attachment_id = ea.attachment_id
        WHERE ea.email_id = :email_id
    )");

    query.bindValue(":email_id", emailId);

    if (!query.exec())
    {
        throw std::runtime_error("Query execution failed: " + query.lastError().text().toStdString());
    }

    QList<Attachment> attachments;

    while (query.next())
        attachments.append(MapToAttachment(query));

    return attachments;
}

Attachment AttachmentRepo::MapToAttachment(const QSqlQuery& query)
{
    return {
        .AttachmentId = query.value("attachment_id").toInt(),
        .FileName = query.value("filename").toString(),
        .FilePath = query.value("filepath").toString(),
        .Data = query.value("data").toByteArray(),
        .CreatedAt = query.value("create_at").toString()
    };
}

