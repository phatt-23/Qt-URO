
#include "DIContainer.h"
#include "Event/EventBus.h"
#include "FormInserter.h"
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


    QFile file("Assets/Styles/styles.css"); 
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet); 
    } else {
        qWarning() << "Failed to load stylesheet:" << file.errorString();
    }
    

    // Event bus service.
    const auto eventBus = CreateRef<EventBus>();


    // Database context.
    const auto dbService = CreateRef<DbContext>();
    if (!dbService->Connect("Assets/Sql/emails.db")) {
        qFatal("Failed to connect to DB.");
    }


    // Database repos.
    const auto emailRepo = CreateRef<EmailRepo>(dbService, eventBus);
    const auto userRepo = CreateRef<UserRepo>(dbService);
    const auto attachmentRepo = CreateRef<AttachmentRepo>(dbService);
    const auto formInserter = CreateRef<FormInserter>(dbService, eventBus);


    // Set up DI Container and add services.
    const auto diContainer = CreateRef<DIContainer>();
    diContainer->AddSingleton<Ref<EventBus>>(eventBus);
    diContainer->AddSingleton<Ref<DbContext>>(dbService);
    diContainer->AddSingleton<Ref<EmailRepo>>(emailRepo);
    diContainer->AddSingleton<Ref<UserRepo>>(userRepo);
    diContainer->AddSingleton<Ref<AttachmentRepo>>(attachmentRepo);
    diContainer->AddSingleton<Ref<FormInserter>>(formInserter);


    // Inject DI container.
    MainWindow window(diContainer);
    window.setWindowTitle("Qt Email Client");
    window.resize(1200, 800);
    window.show();


    // Run.
    return QApplication::exec();
}

