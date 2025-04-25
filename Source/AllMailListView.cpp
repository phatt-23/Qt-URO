//
// Created by phatt on 4/25/25.
//

#include "../Header/Views/EmailView/EmailListViews/AllMailListView.h"

#include "Config.h"
#include "EmailRepo.h"
#include "UserRepo.h"

AllMailListView::AllMailListView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : EmailListView(diContainer, "AllMailListView", parent)
{
    // layout
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_EmailCardList);
}

void AllMailListView::ShowEmails(QString const& searchString)
{
    const auto emailRepo = m_DiContainer->GetService<EmailRepo>();
    const auto userRepo = m_DiContainer->GetService<UserRepo>();

    const auto user = userRepo->GetUser(DEFAULT_EMAIL_ADDRESS);

    const auto emails =
        emailRepo->GetEmailsFrom(user.UserId, searchString)
        + emailRepo->GetEmailsTo(user.UserId, searchString);

    m_EmailCardList.ProjectEmails(emails);
}
