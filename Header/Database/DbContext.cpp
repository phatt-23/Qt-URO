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
    if (QSqlDatabase::contains(m_ConnectionName))
    {
        qInfo() << "Database already exists.";
        m_Database = QSqlDatabase::database(m_ConnectionName);
    }
    else
    {
        // supporting only SQLite for now
        qInfo() << "Adding database.";
        m_Database = QSqlDatabase::addDatabase("QSQLITE", m_ConnectionName);
    }
}

DbContext::~DbContext()
{
    qInfo() << "DatabaseService::~DatabaseService";
    if (m_Database.isOpen())
    {
        qInfo() << "Closing database";
        m_Database.close();
    }

    qInfo() << "Removing database";
    QSqlDatabase::removeDatabase(m_ConnectionName);
}

bool DbContext::Connect(const QString& dbPath)
{
    qInfo() << "DatabaseService::connect called";
    const auto currentPath = std::filesystem::current_path();

    m_Database.setDatabaseName(dbPath);  // only supporting SQLite
    if (!m_Database.open())
    {
        qCritical() << "Failed to open database " << m_ConnectionName << ":" << m_Database.lastError().text();
        return false;
    }
    return true;
}

bool DbContext::IsConnected() const
{
    return m_Database.isOpen();
}

const QSqlDatabase& DbContext::GetDatabase() const
{
    return m_Database;
}
