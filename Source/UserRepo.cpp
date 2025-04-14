//
// Created by phatt on 4/13/25.
//

#include "UserRepo.h"


UserRepo::UserRepo(const Ref<DbContext>& dbService)
    : m_DbService(dbService)
{
}

UserRepo::~UserRepo()
{
}

QList<User> UserRepo::GetAllUsers() const
{
    QSqlQuery query(R"(SELECT * FROM user)", m_DbService->GetDatabase());
    query.exec();

    QList<User> users;
    while (query.next())
        users.append(MapToUser(query));

    return users;
}

User UserRepo::GetUser(const QString& email) const
{
    QSqlQuery query(m_DbService->GetDatabase());
    query.prepare("SELECT * FROM user WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec())
        throw std::runtime_error(std::format("No user with email '{}'", email.toStdString()));


    if (query.next())
        return MapToUser(query);

    throw std::runtime_error(std::format("User with email '{}' doesn't exist", email.toStdString()));
}

User UserRepo::GetUser(const int userId) const
{
    qInfo() << "UserRepo::GetUser() called!";

    QSqlQuery query(m_DbService->GetDatabase());
    query.prepare("SELECT * FROM user WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec())
        throw std::runtime_error("Failed to execute query: " + query.lastError().text().toStdString());

    if (query.next())
        return MapToUser(query);

    throw std::runtime_error(std::format("User with id '{}' doesn't exist", userId));
}

bool UserRepo::AddUser(const User& user) const
{
    QSqlQuery query(R"(
        INSERT INTO user(email, first_name, last_name)
        VALUES (:email, :first_name, :last_name)
    )", m_DbService->GetDatabase());

    query.bindValue(":email", user.Email);
    query.bindValue(":first_name", user.FirstName);
    query.bindValue(":last_name", user.LastName);

    if (query.exec())
        return true;

    qCritical() << "AddUser failed:" << query.lastError().text();
    return false;
}

QList<User> UserRepo::GetRecipients(const int emailId) const
{
    QSqlQuery query(m_DbService->GetDatabase());
    query.prepare(R"(
        SELECT *
        FROM user u
        JOIN email_recipient er ON u.user_id = er.recipient_id
        WHERE er.email_id = :email_id)");

    query.bindValue(":email_id", emailId);

    if (!query.exec())
        throw std::runtime_error(std::format("Failed to execute query {}", __PRETTY_FUNCTION__));

    QList<User> recipients;
    while (query.next())
        recipients.append(MapToUser(query));

    return recipients;
}


User UserRepo::MapToUser(const QSqlQuery& query)
{
    return {
        .UserId = query.value("user_id").toInt(),
        .Email = query.value("email").toString(),
        .FirstName = query.value("first_name").toString(),
        .LastName = query.value("last_name").toString(),
        .CreatedAt = query.value("created_at").toString(),
    };
}
