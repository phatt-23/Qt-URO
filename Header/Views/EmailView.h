//
// Created by phatt on 4/7/25.
//

#ifndef MAILVIEW_H
#define MAILVIEW_H


#include "QComponent.h"
#include "EmailView/BaseView.h"
#include "EmailView/CategoryList.h"
#include "EmailView/EmailList.h"
#include "EmailView/EmailPreview.h"


class EmailView final : public BaseView {
    Q_OBJECT
public:
    explicit EmailView(const Ref<DIContainer>& diContainer, QWidget* parent);
    ~EmailView() override;

    void OnEnter() override {};
private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QSplitter m_Splitter;

    CategoryList m_CategoryList;
    EmailList m_EmailList;
    EmailPreview m_EmailPreview;

    QVBoxLayout* m_Layout;
};



#endif //MAILVIEW_H
