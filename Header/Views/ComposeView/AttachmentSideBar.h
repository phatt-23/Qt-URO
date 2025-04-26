//
// Created by phatt on 4/8/25.
//

#ifndef ATTACHMENTSIDEBAR_H
#define ATTACHMENTSIDEBAR_H

#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"

class AttachmentSideBar final : public QComponent {
    Q_OBJECT
public:
    explicit AttachmentSideBar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~AttachmentSideBar() override;

    [[nodiscard]] QList<QString> GetAttachments() const;
    void AddAttachment(const QString& filepath);
    inline void SetReadonly(const bool value) { m_Readonly = value; }
    void Clear() const;

    inline void SetList(const QList<QString>& filepaths)
    {
        Clear(); 
        for (const QString& filepath : filepaths) {
            AddAttachment(filepath); 
        }
    }
    
private:
    void BindEvents() override;

private:
    Ref<DIContainer> m_DiContainer;

    QWidget* m_ContainerWidget;     
    QVBoxLayout* m_ContainerLayout; 

    bool m_Readonly = false;
};

#endif // ATTACHMENTSIDEBAR_H