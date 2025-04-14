#include "EmailCardList.h"
#include "EmailCard.h"
#include "EmailRepo.h"
#include "UserRepo.h"


EmailCardList::EmailCardList(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailCardList", parent)
    , m_DiContainer(diContainer)
    , m_ScrollArea(this)
    , m_Container()
    , m_ContainterLayout(&m_Container)
{
    m_ScrollArea.setWidgetResizable(true);

    m_ScrollArea.setWidget(&m_Container);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_ScrollArea);
}

EmailCardList::~EmailCardList() 
{
}

void EmailCardList::ProjectEmails(const QList<Email>& emails)
{
    // kill all children
    auto children = m_Container.children();
    for (auto* ch : children)
    {
        auto child = qobject_cast<QWidget*>(ch);
        m_ContainterLayout.removeWidget(child);
    }
   
    const auto userRepo = m_DiContainer->GetService<UserRepo>();

    // populate containter
    for (const auto& email : emails) 
    {
        const auto sender = userRepo->GetUser(email.SenderId);
        m_ContainterLayout.addWidget(new EmailCard(m_DiContainer, email, sender.Email, this));
    }
}


