//
// Created by phatt on 4/12/25.
//

#include "EmailRepo.h"

static QString getLastExecutedQuery(const QSqlQuery& query)
{
    QString sql = query.executedQuery();
    auto values = query.boundValues();

    qInfo() << "------------------------";

    for (auto v : values)
    {
           qInfo() << v.toString();
    }

    return sql;
}



EmailRepo::EmailRepo(const Ref<DbContext>& dbService, const Ref<EventBus>& eventBus)
    : m_DbService(dbService)
    , m_EventBus(eventBus)
{
}

EmailRepo::~EmailRepo()
{
}

QList<Email> EmailRepo::GetAllEmails() const
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    const auto db = m_DbService->GetDatabase();
    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return {};
    }

    QSqlQuery query(m_DbService->GetDatabase());

    query.prepare("SELECT * FROM email");
    if (!query.exec()) {
        qCritical() << "Query failed:" << query.lastError().text();
        return {};
    }

    QList<Email> emails;
    while (query.next())
    {
        emails.append(MapToEmail(query));
    }

    return emails;
}

Email EmailRepo::GetEmail(int const emailId) const
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    auto const db = m_DbService->GetDatabase();

    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return {};
    }

    QSqlQuery query(db);

    query.prepare(R"(
        SELECT *
        FROM email
        WHERE email_id = :email_id
    )");
    query.bindValue(":email_id", emailId);

    if (!query.exec())
    {
        qCritical() << "Query failed:" << query.lastError().text();
        throw std::runtime_error("Query failed to execute");
    }

    if (!query.next())
        throw std::runtime_error(std::format("No email with id '{}' exists in the DB.", emailId));

    return MapToEmail(query);
}

QList<Email> EmailRepo::GetEmailsFrom(int const userId, QString const& searchString) const
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";

    const auto db = m_DbService->GetDatabase();
    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return {};
    }

    QSqlQuery query(m_DbService->GetDatabase());

    if (searchString.isEmpty())
    {
        query.prepare(R"(
            SELECT * FROM email
             WHERE sender_id = :sender_id
        )");

        query.bindValue(":sender_id", userId);
        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }
    }
    else
    {
        qInfo() << "HEEEEEEEEEEEREEEEEEEEEEEEEEEEEEE";

        query.prepare(R"(
            SELECT *
            FROM email e
            LEFT JOIN email_recipient er ON e.email_id = er.email_id
            LEFT JOIN user u ON er.recipient_id = u.user_id
            WHERE e.sender_id = :sender_id
            AND (
                LOWER(e.subject) LIKE :search OR
                LOWER(e.body) LIKE :search OR
                LOWER(u.email) LIKE :search OR
                LOWER(u.first_name) LIKE :search OR
                LOWER(u.last_name) LIKE :search
            )
        )");

        qInfo() << "HEEEEEEEEEEEREEEEEEEEEEEEEEEEEEE 2";

        query.bindValue(":sender_id", userId);
        query.bindValue(":search", '%' + searchString.trimmed().toLower() + '%');

        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }

        qInfo() << "Last executed:" << getLastExecutedQuery(query);
    }

    QList<Email> emails;
    while (query.next())
    {
        emails.append(MapToEmail(query));
    }

    return emails;
}

QList<Email> EmailRepo::GetEmailsFrom(int const userId, EmailStatus const status, QString const& searchString) const
{
    const auto db = m_DbService->GetDatabase();
    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return {};
    }

    QSqlQuery query(m_DbService->GetDatabase());


    if (searchString.isEmpty())
    {
        query.prepare(R"(
            SELECT * FROM email
            WHERE sender_id = :sender_id
            AND status = :status
        )");

        query.bindValue(":sender_id", userId);
        query.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));

        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }
    }
    else
    {
        qInfo() << "STATUS HEEEEEEEEEEEERE 1";

        query.prepare(R"(
            SELECT *
            FROM email e
            LEFT JOIN email_recipient er ON e.email_id = er.email_id
            LEFT JOIN user u ON er.recipient_id = u.user_id
            WHERE e.sender_id = :sender_id
              AND status = :status
              AND (
                LOWER(e.subject) LIKE :search OR
                LOWER(e.body) LIKE :search OR
                LOWER(u.email) LIKE :search OR
                LOWER(u.first_name) LIKE :search OR
                LOWER(u.last_name) LIKE :search
            )
        )");


        query.bindValue(":sender_id", userId);
        query.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));
        query.bindValue(":search", '%' + searchString.trimmed().toLower() + '%');


        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }

        qInfo() << "STATUS HEEEEEEEEEEEERE 2";

        qInfo() << "Last executed:" << getLastExecutedQuery(query);
    }

    QList<Email> emails;
    while (query.next())
    {
        emails.append(MapToEmail(query));
    }

    return emails;
}

QList<Email> EmailRepo::GetEmailsTo(const int userId, QString const& searchString) const
{
    const auto db = m_DbService->GetDatabase();
    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return {};
    }

    QSqlQuery query(m_DbService->GetDatabase());

    if (searchString.isEmpty())
    {
        query.prepare(R"(
            SELECT * FROM email e
            JOIN email_recipient er ON e.email_id = er.email_id
            WHERE er.recipient_id = :recipient_id
        )");

        query.bindValue(":recipient_id", userId);

        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }
    }
    else
    {
        query.prepare(R"(
            SELECT *
            FROM email e
            LEFT JOIN email_recipient er ON e.email_id = er.email_id
            LEFT JOIN user u ON er.recipient_id = u.user_id
            WHERE er.recipient_id = :recipient_id
              AND (
                LOWER(e.subject) LIKE :search OR
                LOWER(e.body) LIKE :search OR
                LOWER(u.email) LIKE :search OR
                LOWER(u.first_name) LIKE :search OR
                LOWER(u.last_name) LIKE :search
            )
        )");

        query.bindValue(":recipient_id", userId);
        query.bindValue(":search", '%' + searchString.trimmed().toLower() + '%');

        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }


        qInfo() << "Last executed:" << getLastExecutedQuery(query);
    }

    QList<Email> emails;
    while (query.next())
    {
        emails.append(MapToEmail(query));
    }

    return emails;
}

QList<Email> EmailRepo::GetEmailsTo(const int userId, EmailStatus const status, QString const& searchString) const
{
    const auto db = m_DbService->GetDatabase();
    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return {};
    }

    QSqlQuery query(m_DbService->GetDatabase());

    if (searchString.isEmpty())
    {
        query.prepare(R"(
            SELECT * FROM email e
            JOIN email_recipient er ON e.email_id = er.email_id
            WHERE er.recipient_id = :recipient_id AND status = :status
        )");

        query.bindValue(":recipient_id", userId);
        query.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));

        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }
    }
    else
    {
        query.prepare(R"(
            SELECT *
            FROM email e
            LEFT JOIN email_recipient er ON e.email_id = er.email_id
            LEFT JOIN user u ON er.recipient_id = u.user_id
            WHERE er.recipient_id = :recipient_id AND status = :status
              AND (
                LOWER(e.subject) LIKE :search OR
                LOWER(e.body) LIKE :search OR
                LOWER(u.email) LIKE :search OR
                LOWER(u.first_name) LIKE :search OR
                LOWER(u.last_name) LIKE :search
            )
        )");

        query.bindValue(":recipient_id", userId);
        query.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));
        query.bindValue(":search", '%' + searchString.trimmed().toLower() + '%');

        if (!query.exec()) {
            qCritical() << "Query failed:" << query.lastError().text();
            return {};
        }


        qInfo() << "Last executed:" << getLastExecutedQuery(query);
    }

    QList<Email> emails;
    while (query.next())
    {
        emails.append(MapToEmail(query));
    }

    return emails;
}

void EmailRepo::SetEmailStatus(int const emailId, EmailStatus const status) const
{
    const auto db = m_DbService->GetDatabase();
    if (!db.isValid() || !db.isOpen()) {
        qCritical() << "Database is not valid or not open!";
        return;
    }

    QSqlQuery query(m_DbService->GetDatabase());

    query.prepare(R"(
        UPDATE email
        SET status = :status
        WHERE email_id = :email_id
    )");

    query.bindValue(":email_id", emailId);
    query.bindValue(":status", QString::fromStdString(GetEmailStatusString(status)));

    if (!query.exec()) {
        qCritical() << "Query failed:" << query.lastError().text();
        return;
    }

    m_EventBus->ForwardEmit<EmailStatusChangedEvent>(emailId, status);
}


