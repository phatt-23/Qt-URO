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
    QSqlQuery query(R"(
        SELECT *
        FROM attachment a
        JOIN email_attachment ea ON a.attachment_id = ea.attachment_id
        WHERE ea.email_id = :email_id
    )", m_DbService->GetDatabase());

    query.bindValue(":email_id", emailId);

    query.exec();

    QList<Attachment> attachments;

    while (query.next())
        attachments.append(MapToAttachment(query));

    return attachments;
}

Attachment AttachmentRepo::MapToAttachment(const QSqlQuery& query)
{
    return {
        .AttachmentId = query.value("attachment_id").toInt(),
        .FileName = query.value("attachment_name").toString(),
        .FilePath = query.value("attachment_path").toString(),
        .Data = query.value("attachment_data").toByteArray(),
        .CreatedAt = query.value("created_at").toString()
    };
}

