//
// Created by phatt on 4/8/25.
//

#ifndef EMAILLISTSORTFRAME_H
#define EMAILLISTSORTFRAME_H


#include "DIContainer.h"
#include "QComponent.h"


class EmailListSortFrame final : public QComponent {
public:
    explicit EmailListSortFrame(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;

};



#endif //EMAILLISTSORTFRAME_H
