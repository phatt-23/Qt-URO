//
// Created by phatt on 4/12/25.
//

#ifndef EMAILREPO_H
#define EMAILREPO_H
#include "DbContext.h"


#include "DataModels.h"
#include "StdLib.h"


class EmailRepo final : public IService {
public:
    explicit EmailRepo(const Ref<DbContext>& dbService);
    ~EmailRepo() override;

    [[nodiscard]] QList<Email> GetAllEmails() const;
    [[nodiscard]] Email GetEmail(int emailId) const;

private:
    static Email MapToEmail(const QSqlQuery& query)
    {
        const auto value = query.value("status").toString().toStdString();
        const auto status = GetEmailStatusFromString(value);

        return {
            .EmailId = query.value("email_id").toInt(),
            .SenderId = query.value("sender_id").toInt(),
            .Subject = query.value("subject").toString(),
            .Body = query.value("body").toString(),
            .Status = status,
            .SentAt = query.value("sent_at").toString(),
        };
    }

    Ref<DbContext> m_DbService;
};



#endif //EMAILREPO_H
