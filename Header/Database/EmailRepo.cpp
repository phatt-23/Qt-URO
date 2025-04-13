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
    qInfo() << "GetAllEmails called";

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
        qInfo() << "Next" << i++;
        emails.append(MapToEmail(query));
    }

    return emails;
}

