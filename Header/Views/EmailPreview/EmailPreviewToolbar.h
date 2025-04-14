#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWTOOLBAR_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWTOOLBAR_H_




#include "QComponent.h"
#include "QtWidgets.h"



class EmailPreviewToolbar : public QComponent 
{
public:
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
    explicit EmailPreviewToolbar(QWidget* parent = nullptr);
    ~EmailPreviewToolbar() override;

private:

    QMap<PreviewToolbarButton, QPushButton*> m_Buttons;
};



#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWTOOLBAR_H_
