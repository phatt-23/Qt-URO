//
// Created by phatt on 4/8/25.
//

#ifndef EMAILPREVIEW_H
#define EMAILPREVIEW_H


#include "QComponent.h"
#include "Core.h"


class EmailPreview final : public QComponent {
public:
    explicit EmailPreview(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;
};



#endif //EMAILPREVIEW_H
