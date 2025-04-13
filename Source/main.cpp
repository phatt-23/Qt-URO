
#include "DIContainer.h"
#include "Event/EventBus.h"
#include "MainWindow.h"
#include "StdLib.h"
#include "Database/DbContext.h"
#include "Database/EmailRepo.h"
#include <QApplication>

#include "Database/AttachmentRepo.h"
#include "Database/UserRepo.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);


    // Event bus service.
    const auto eventBusService = CreateRef<EventBus>();


    // Database context.
    const auto dbService = CreateRef<DbContext>();
    if (!dbService->Connect("Assets/Sql/emails.db")) {
        qFatal("Failed to connect to DB.");
    }


    // Database repos.
    const auto emailRepo = CreateRef<EmailRepo>(dbService);
    const auto userRepo = CreateRef<UserRepo>(dbService);
    const auto attachmentRepo = CreateRef<AttachmentRepo>(dbService);


    // Set up DI Container and add services.
    const auto diContainer = CreateRef<DIContainer>();
    diContainer->AddSingleton<Ref<EventBus>>(eventBusService);
    diContainer->AddSingleton<Ref<DbContext>>(dbService);
    diContainer->AddSingleton<Ref<EmailRepo>>(emailRepo);
    diContainer->AddSingleton<Ref<UserRepo>>(userRepo);
    diContainer->AddSingleton<Ref<AttachmentRepo>>(attachmentRepo);


    // Inject DI container.
    MainWindow window(diContainer);
    window.setWindowTitle("Qt Email Client");
    window.resize(1200, 800);
    window.show();


    // Run.
    return QApplication::exec();
}


#if 0

int main(int argc, char* argv[])
{
    const std::string DB_PATH = "./Assets/Sql/emails.db";

    QApplication app(argc, argv);

    qInfo() << "CURRENT DIRECTORY:" << std::filesystem::current_path().c_str();

    QFile file("./Assets/Sql/create.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qInfo() << "Could not open file";
        return -1;
    }

    QTextStream stream(&file);
    const QString content = stream.readAll();
    qInfo() << "Content:" << content;

    QStringList sqlStatements = content.split(";", Qt::SplitBehavior(QString::SectionSkipEmpty));
    qInfo() << "Split:\n" << sqlStatements;

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_PATH.c_str());
    if (!db.open())
    {
        qInfo() << "Error: connection with database failed";
    }
    else
    {
        qInfo() << "Database: connection ok";
    }

    int successCount = 0;

    foreach(const auto& statement, sqlStatements)
    {
        if (statement.trimmed() == "")
            continue;

        qInfo() << "Executing statement:" << statement;

        QSqlQuery query(db);
        if (query.exec(statement))
        {
            qInfo() << "Done executing statement: " << statement;
            successCount++;
        }
        else
        {
            qInfo()
                << "Failed to execute statement:" << statement
                << "\nReason:" << query.lastError().text();
        }
    }


    return app.exec();
}


#endif
