#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWCONTENT_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWCONTENT_H_




#include "DIContainer.h"
#include "QComponent.h"



class EmailPreviewContent : public QComponent
{
public:
    explicit EmailPreviewContent(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailPreviewContent() override;

private:
    Ref<DIContainer> m_DiContainer;

    
};




#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWCONTENT_H_
