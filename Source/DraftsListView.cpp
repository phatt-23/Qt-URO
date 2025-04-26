//
// Created by phatt on 4/25/25.
//

#include "../Header/Views/EmailView/EmailListViews/DraftsListView.h"

#include "Config.h"
#include "EmailRepo.h"
#include "UserRepo.h"

DraftsListView::DraftsListView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : EmailListView(diContainer, "DraftsListView", parent)
{
    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    layout->addWidget(&m_EmailCardList);
}

void DraftsListView::ShowEmails(QString const& searchString)
{
    const auto emailRepo = m_DiContainer->GetService<EmailRepo>();
    const auto userRepo = m_DiContainer->GetService<UserRepo>();

    const auto user = userRepo->GetUser(DEFAULT_EMAIL_ADDRESS);

    const auto emails = emailRepo->GetEmailsFrom(user.UserId, EmailStatus::DRAFT, searchString);
    m_EmailCardList.ProjectEmails(emails);
}

