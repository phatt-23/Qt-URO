//
// Created by phatt on 4/12/25.
//

#ifndef EMAILREPO_H
#define EMAILREPO_H
#include "DbContext.h"


#include "DataModels.h"
#include "EventBus.h"
#include "StdLib.h"


class EmailRepo final : public IService {
public:
    explicit EmailRepo(const Ref<DbContext>& dbService, const Ref<EventBus>& eventBus);
    ~EmailRepo() override;

    [[nodiscard]] Email GetEmail(int emailId) const;
    [[nodiscard]] QList<Email> GetAllEmails() const;
    [[nodiscard]] QList<Email> GetEmailsFrom(const int userId, QString const& searchString = "") const;
    [[nodiscard]] QList<Email> GetEmailsFrom(const int userId, EmailStatus const status, QString const& searchString = "") const;

    [[nodiscard]] QList<Email> GetEmailsTo(const int userId, QString const& searchString) const;
    [[nodiscard]] QList<Email> GetEmailsTo(const int userId, EmailStatus const status, QString const& searchString) const;

    void SetEmailStatus(int emailId, EmailStatus const status) const;

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
    Ref<EventBus> m_EventBus;
};

struct EmailStatusChangedEvent final : EventBase
{
    EmailStatusChangedEvent(int const emailId, EmailStatus const status)
        : EmailId(emailId), Status(status) {}

    int EmailId;
    EmailStatus Status;
};

#endif //EMAILREPO_H
