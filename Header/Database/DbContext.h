//
// Created by phatt on 4/12/25.
//

#pragma once


#include "IService.h"
#include <QtSql/QtSql>



class DbContext final : public IService 
{
public:
    explicit DbContext(QString connectionName = "default");
    ~DbContext() override;

    bool Connect(const QString& dbPath);
    bool IsConnected() const;
    QSqlDatabase GetDatabase() const;

private:
    QString m_ConnectionName;
};


