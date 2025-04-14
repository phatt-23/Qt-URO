//
// Created by phatt on 4/12/25.
//
#include <filesystem>
#include <utility>

#include "DbContext.h"

DbContext::DbContext(QString connectionName)
    : m_ConnectionName(std::move(connectionName))
{
    qInfo() << __PRETTY_FUNCTION__ << "called!";
    // if (QSqlDatabase::contains(m_ConnectionName))
    // {
    //     qInfo() << "Database already exists.";
    //     m_Database = CreateRef<QSqlDatabase>(QSqlDatabase::database(m_ConnectionName));
    // }
    // else
    // {
    //     // supporting only SQLite for now
    //     qInfo() << "Adding database.";
    //     m_Database = CreateRef<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE", m_ConnectionName));
    // }
}

DbContext::~DbContext()
{
}

bool DbContext::Connect(const QString& dbPath)
{
    qInfo() << "DatabaseService::connect called";
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
