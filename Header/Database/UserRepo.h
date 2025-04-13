//
// Created by phatt on 4/13/25.
//

#ifndef USERREPO_H
#define USERREPO_H


#include "DbContext.h"
#include "IService.h"
#include "StdLib.h"
#include "DataModels.h"


class UserRepo final : public IService {
public:
    explicit UserRepo(const Ref<DbContext>& dbService);
    ~UserRepo() override;

    QList<User> GetAllUsers() const;
    User GetUser(const QString& email) const;
    User GetUser(int userId) const;
    bool AddUser(const User& user) const;
    QList<User> GetRecipients(int emailId) const;

private:
    static User MapToUser(const QSqlQuery& query);

private:
    Ref<DbContext> m_DbService;
};



#endif //USERREPO_H
