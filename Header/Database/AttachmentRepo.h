//
// Created by phatt on 4/13/25.
//

#ifndef ATTACHMENTREPO_H
#define ATTACHMENTREPO_H


#include "DbContext.h"
#include "IService.h"
#include "StdLib.h"
#include "DataModels.h"



class AttachmentRepo final : public IService {
public:
    explicit AttachmentRepo(const Ref<DbContext>& db);
    ~AttachmentRepo() override;

    QList<Attachment> GetAttachments(int emailId) const;

private:
    static Attachment MapToAttachment(const QSqlQuery& query);

private:
    Ref<DbContext> m_DbService;
};



#endif //ATTACHMENTREPO_H
