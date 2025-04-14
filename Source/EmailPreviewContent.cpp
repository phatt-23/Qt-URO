#include "EmailPreviewContent.h"

EmailPreviewContent::EmailPreviewContent(const Ref<DIContainer>& diContainer, QWidget* parent)
    : QComponent("EmailPreviewContent", parent), m_DiContainer(diContainer)
{
}

EmailPreviewContent::~EmailPreviewContent()
{
}
