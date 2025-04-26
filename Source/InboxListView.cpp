//
// Created by phatt on 4/8/25.
//

#include "InboxListView.h"

#include "Config.h"
#include "EmailCardList.h"
#include "EmailEditor.h"
#include "Database/EmailRepo.h"
#include "Utility.h"
#include "Database/UserRepo.h"
#include "QtWidgets.h"
#include "EmailCard.h"



InboxListView::InboxListView(const Ref<DIContainer>& diContainer, QWidget* parent)
    : EmailListView(diContainer, "InboxListView", parent)
{
    // layout
    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);



    layout->addWidget(&m_EmailCardList);
}

void InboxListView::ShowEmails(QString const& searchString)
{
    const auto emailRepo = m_DiContainer->GetService<EmailRepo>();
    const auto userRepo = m_DiContainer->GetService<UserRepo>();

    const auto user = userRepo->GetUser(DEFAULT_EMAIL_ADDRESS);
    const auto emails = emailRepo->GetEmailsTo(user.UserId, searchString);
    m_EmailCardList.ProjectEmails(emails);
}


