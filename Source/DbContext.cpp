//
// Created by phatt on 4/12/25.
//
#include <utility>

#include "DbContext.h"

DbContext::DbContext(QString connectionName)
    : m_ConnectionName(std::move(connectionName))
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";
}

DbContext::~DbContext()
{
}

bool DbContext::Connect(const QString& dbPath)
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";
    auto db = QSqlDatabase::addDatabase("QSQLITE", m_ConnectionName);  // only supporting SQLite
    
    db.setDatabaseName(dbPath);  
    if (!db.open())
    {
        qCritical() << "Failed to open database " << m_ConnectionName << ":" << db.lastError().text();
        return false;
    }
    return true;
}

QSqlDatabase DbContext::GetDatabase() const
{
    auto db = QSqlDatabase::database(m_ConnectionName);

    if (!db.isValid())
        throw std::runtime_error("Database is not valid");

    if (!db.isOpen())
        throw std::runtime_error("Database is not open");

    if (db.isOpenError())
        throw std::runtime_error("Is Open Error: " + db.lastError().text().toStdString());

    return db;
}


