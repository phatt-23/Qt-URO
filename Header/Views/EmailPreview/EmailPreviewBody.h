#ifndef INCLUDE_EMAILPREVIEW_EMAILPREVIEWBODY_H_
#define INCLUDE_EMAILPREVIEW_EMAILPREVIEWBODY_H_




#include "DataModels.h"
#include "QComponent.h"
#include "QtWidgets.h"



class EmailPreviewBody final : public QComponent 
{
public:
    EmailPreviewBody(QWidget* parent);
    ~EmailPreviewBody() override;

    void ProjectEmail(Email const& email);

private:
    QTextEdit m_TextEdit;
};




#endif  // INCLUDE_EMAILPREVIEW_EMAILPREVIEWBODY_H_

