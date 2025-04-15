#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWATTACHMENTS_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWATTACHMENTS_H_




#include "DIContainer.h"
#include "DataModels.h"
#include "QComponent.h"




class EmailPreviewAttachments final : public QComponent
{
public:
    EmailPreviewAttachments(Ref<DIContainer> const& diContainer, QWidget* parent);
    ~EmailPreviewAttachments() override;

    void ProjectEmail(Email const& email);

private:
    Ref<DIContainer> m_DiContainer;
    
    QScrollArea m_ScrollArea;
    QWidget m_Container;
    QVBoxLayout m_ContainerLayout;
};




#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWATTACHMENTS_H_
