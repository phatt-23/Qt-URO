//
// Created by phatt on 4/25/25.
//

#include "../Header/Views/EmailView/EmailListViews/SentMailListView.h"

#include "Config.h"
#include "EmailRepo.h"
#include "UserRepo.h"

SentMailListView::SentMailListView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : EmailListView(diContainer, "SentMailListView", parent)
{
    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);



    layout->addWidget(&m_EmailCardList);
}

void SentMailListView::ShowEmails(QString const& searchString)
{
    const auto emailRepo = m_DiContainer->GetService<EmailRepo>();
    const auto userRepo = m_DiContainer->GetService<UserRepo>();

    const auto user = userRepo->GetUser(DEFAULT_EMAIL_ADDRESS);

    const auto emails = emailRepo->GetEmailsFrom(user.UserId, EmailStatus::SENT, searchString);
    m_EmailCardList.ProjectEmails(emails);
}
