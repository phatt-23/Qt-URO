#include "EmailCardList.h"
#include "EmailCard.h"
#include "EmailRepo.h"
#include "FormInserter.h"
#include "UserRepo.h"


EmailCardList::EmailCardList(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailCardList", parent)
    , m_DiContainer(diContainer)
    , m_ScrollArea(this)
    , m_ContainerLayout(&m_Container)
{
    m_ScrollArea.setWidgetResizable(true);
    m_ScrollArea.setWidget(&m_Container);

    m_ContainerLayout.setAlignment(Qt::AlignTop);

    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_ScrollArea);

    BindEvents();
}

EmailCardList::~EmailCardList() 
{
}

void EmailCardList::BindEvents()
{
}

void EmailCardList::ProjectEmails(const QList<Email>& emails)
{
    // kill all children
    auto children = m_Container.children();
    for (auto* ch : children)
    {
        if (const auto child = qobject_cast<QWidget*>(ch))
        {
            m_ContainerLayout.removeWidget(child);
            child->deleteLater();
        }
    }
   
    const auto userRepo = m_DiContainer->GetService<UserRepo>();

    // populate container
    for (const auto& email : emails) 
    {
        const auto sender = userRepo->GetUser(email.SenderId);

        auto* emailCard = new EmailCard(m_DiContainer, email, sender.Email, this);

        // Set size policy to prevent expansion
        emailCard->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

        m_ContainerLayout.addWidget(emailCard);
    }
}


