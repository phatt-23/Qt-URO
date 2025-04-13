//
// Created by phatt on 4/8/25.
//

#ifndef EMAILEDITOR_H
#define EMAILEDITOR_H


#include "DIContainer.h"
#include "EventBus.h"
#include "QComponent.h"
#include "QtWidgets.h"


class EmailEditor final : public QComponent {
public:
    explicit EmailEditor(const Ref<DIContainer>& diContainer, QWidget* parent = nullptr);
    ~EmailEditor() override;

    struct DataContext {
        explicit DataContext(QWidget* parent)
            : SenderLideEdit(parent)
            , RecipientsLideEdit(parent)
            , SubjectLideEdit(parent)
            , TextBody(parent) {}

        QLineEdit SenderLideEdit;
        QLineEdit RecipientsLideEdit;
        QLineEdit SubjectLideEdit;
        QTextEdit TextBody;
    };

private:
    Ref<DIContainer> m_DiContainer;

    QComponent m_ToolbarFrame;
    QComponent m_HeaderFrame;
    QComponent m_BodyFrame;

    Scope<DataContext> m_Data;
};


// TODO: Remove, only for now
struct EmailWrittenEvent final : public EventBase {
    explicit EmailWrittenEvent(const EmailEditor::DataContext* data)
        : m_Data(data) {}
    const EmailEditor::DataContext* m_Data;
};



#endif //EMAILEDITOR_H
