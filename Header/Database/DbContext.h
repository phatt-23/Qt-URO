//
// Created by phatt on 4/12/25.
//

#ifndef DBCONTEXT_H
#define DBCONTEXT_H

#include <QtSql/QtSql>
#include "IService.h"


class DbContext final : public IService {
public:
    explicit DbContext(QString connectionName = "default");
    ~DbContext() override;

    bool Connect(const QString& dbPath);
    bool IsConnected() const;
    const QSqlDatabase& GetDatabase() const;

private:
    QString m_ConnectionName;
    QSqlDatabase m_Database;
};



#endif //DBCONTEXT_H
