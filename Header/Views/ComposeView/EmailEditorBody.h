//
// Created by phatt on 4/26/25.
//

#ifndef EMAILEDITORBODY_H
#define EMAILEDITORBODY_H
#include "QComponent.h"
#include "QtWidgets.h"

class EmailEditorBody final : public QComponent {
    Q_OBJECT
public:
    friend class EmailEditor;

public:
    explicit EmailEditorBody(QWidget* parent);

    ~EmailEditorBody() override = default;

    QString GetText() const
    {
        return m_TextBody->toPlainText();
    }

private:
    QTextEdit* m_TextBody;
};



#endif //EMAILEDITORBODY_H
