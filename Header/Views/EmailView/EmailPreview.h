//
// Created by phatt on 4/8/25.
//

#ifndef EMAILPREVIEW_H
#define EMAILPREVIEW_H


#include "EmailPreviewContent.h"
#include "EmailPreviewToolbar.h"
#include "QComponent.h"
#include "Core.h"


class EmailPreview final : public QComponent {
public:
    explicit EmailPreview(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailPreview() override;

private:
    void BindEvents() override;

    void PreviewEmail(int emailId);

private:
    Ref<DIContainer> m_DiContainer;

    EmailPreviewToolbar m_EmailPreviewToolbar;
    EmailPreviewContent m_EmailPreviewContent;
};



#endif //EMAILPREVIEW_H
