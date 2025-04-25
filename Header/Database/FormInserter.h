#ifndef INCLUDE_DATABASE_FORMINSERTER_H_
#define INCLUDE_DATABASE_FORMINSERTER_H_




#include "DIContainer.h"
#include "DataModels.h"
#include "DbContext.h"
#include "EventBus.h"
#include "IService.h"
#include "StdLib.h"




/// handles non-trivial insertion to the database
class FormInserter : public IService
{
public:
    FormInserter(Ref<DbContext> const& context, Ref<EventBus> const& eventBus);
    ~FormInserter() override;

    /// should be async
    bool InsertEmailWithAttachments(Email const& email, QStringList const& attachments, EmailStatus status = EmailStatus::SENT) const;

private:
    Ref<EventBus> m_EventBus;
    Ref<DbContext> m_DbContext;
};


struct EmailWithAttachmentsInsertedEvent : public EventBase
{
    EmailWithAttachmentsInsertedEvent() : EventBase() {}
};

inline QDebug operator<<(QDebug dbg, EmailWithAttachmentsInsertedEvent const& e)
{
    dbg.nospace() << "EmailWithAttachmentsInsertedEvent()";
    return dbg;
}



#endif  // INCLUDE_DATABASE_FORMINSERTER_H_



