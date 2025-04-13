//
// Created by phatt on 4/8/25.
//

#ifndef EMAIL_LIST_FILTERFRAME_H
#define EMAIL_LIST_FILTERFRAME_H


#include "DIContainer.h"
#include "QComponent.h"


class EmailListFilterFrame final : public QComponent {
public:
    explicit EmailListFilterFrame(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;
};



#endif //EMAIL_LIST_FILTERFRAME_H
