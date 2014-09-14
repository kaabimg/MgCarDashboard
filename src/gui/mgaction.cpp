#include "mgaction.h"

MgAction::MgAction(QObject *parent) :
    QObject(parent)
{
}

QByteArray MgAction::name() const
{
    return m_name;
}

QByteArray MgAction::iconSource() const
{
    return m_iconSource;
}

bool MgAction::enabled() const
{
    return m_enabled;
}

void MgAction::setIconSource(const QByteArray & arg)
{
    if (m_iconSource != arg) {
        m_iconSource = arg;
        emit iconSourceChanged(arg);
    }
}

void MgAction::setEnabled(bool arg)
{
    if (m_enabled != arg) {
        m_enabled = arg;
        emit enabledChanged(arg);
    }
}


void MgAction::setName(const QByteArray & arg)
{
    if (m_name != arg) {
        m_name = arg;
        emit nameChanged(arg);
    }
}
