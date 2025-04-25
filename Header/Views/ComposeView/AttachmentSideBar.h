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

    QList<QString> GetAttachments() const;
    
    inline void SetReadonly(bool value) { m_Readonly = value; }
    inline void Clear() const
    {
        m_Model->clear();
    }

    inline void SetList(QStringList const& attachments) const
    {
        Clear();
        for (const QString& a : attachments)
        {
            m_Model->appendRow(QList<QStandardItem*>() << new QStandardItem(a));
        }
    }

private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QAbstractItemView* m_AttachmentsView;
    QStandardItemModel* m_Model;

    bool m_Readonly = false;
};



#endif //ATTACHMENTSIDEBAR_H
