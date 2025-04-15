//
// Created by phatt on 4/7/25.
//

#ifndef MAILVIEW_H
#define MAILVIEW_H


#include "QComponent.h"
#include "EmailView/CategoryList.h"
#include "EmailView/EmailList.h"
#include "EmailView/EmailPreview.h"


class EmailView final : public QComponent {
public:
    explicit EmailView(const Ref<DIContainer>& diContainer, QWidget* parent);
    ~EmailView() override;

private:
    Ref<DIContainer> m_DiContainer;

    QSplitter m_Splitter;

    CategoryList m_CategoryList;
    EmailList m_EmailList;
    EmailPreview m_EmailPreview;
};



#endif //MAILVIEW_H
