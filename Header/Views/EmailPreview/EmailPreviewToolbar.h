#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWTOOLBAR_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWTOOLBAR_H_


#include "DIContainer.h"
#include "QComponent.h"
#include "QtWidgets.h"



class EmailPreviewToolbar final : public QComponent
{
    Q_OBJECT
public:
    friend class EmailPreview;

    enum PreviewToolbarButton 
    {
        REPLY,
        FORWARD,
        REMOVE,
        DELETE_FOREVER,
        EDIT,
        CLOSE,
    };

public:
    explicit EmailPreviewToolbar(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailPreviewToolbar() override;

    void HideButtons() const;

private:
    Ref<DIContainer> m_DiContainer;

    QMap<PreviewToolbarButton, QPushButton*> m_Buttons;
};



#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWTOOLBAR_H_
