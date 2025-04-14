//
// Created by phatt on 4/12/25.
//

#include "EmailRepo.h"

EmailRepo::EmailRepo(const Ref<DbContext>& dbService)
    : m_DbService(dbService)
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
    int i = 0;
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


