//
// Created by phatt on 4/8/25.
//

#ifndef EMAIL_LIST_FILTERFRAME_H
#define EMAIL_LIST_FILTERFRAME_H


#include <QCheckBox>
#include <QDateEdit>

#include "DIContainer.h"
#include "QComponent.h"


class EmailListFilterFrame final : public QComponent {
    Q_OBJECT
public:
    explicit EmailListFilterFrame(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);

private:
    Ref<DIContainer> m_DiContainer;

    QHBoxLayout *m_ReadStatusLayout, *m_DateRangeLayout, *m_ApplyFiltersButtonLayout;
    QPushButton *m_ApplyFiltersButton;
    QCheckBox *m_HasAttachmentCheckBox, *m_ReadCheckBox, *m_UnreadCheckBox;
    QLabel *m_RecipientLabel;
    QLineEdit *m_RecipientLineEdit;
    QLabel *m_DateRangeLabel;
    QDateEdit *m_StartDateEdit, *m_EndDateEdit;
};



#endif //EMAIL_LIST_FILTERFRAME_H
