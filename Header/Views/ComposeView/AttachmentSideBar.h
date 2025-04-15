//
// Created by phatt on 4/8/25.
//

#ifndef ATTACHMENTSIDEBAR_H
#define ATTACHMENTSIDEBAR_H


#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"


class AttachmentSideBar final : public QComponent {
public:
    explicit AttachmentSideBar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~AttachmentSideBar() override;

    void BindEvents() override;

    QList<QString> GetAttachments() const;
private:
    Ref<DIContainer> m_DiContainer;

    QAbstractItemView* m_AttachmentsView;
    QStandardItemModel* m_Model;
};



#endif //ATTACHMENTSIDEBAR_H
