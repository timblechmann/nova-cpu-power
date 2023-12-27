#pragma once

#include <QtQml/QQmlEngine>

#include "cpu_power_interface.h"

struct CPUPowerController : public QObject
{
    Q_OBJECT;
    QML_ELEMENT;

public:
    explicit CPUPowerController( QObject* parent = nullptr ) :
        QObject( parent )
    {
        using namespace Qt::StringLiterals;

        m_interface = new org::klingt::tim::NovaCPUPowerInterface( "org.klingt.tim.NovaCPUPower",
                                                                   "/CpuPower",
                                                                   QDBusConnection::sessionBus(),
                                                                   this );
        QObject::connect( this, &CPUPowerController::setPowersave, m_interface, [ this ] {
            m_interface->set_bias( 15 );
            m_interface->set_governor( u"powersave"_s );
        } );
        QObject::connect( this, &CPUPowerController::setPerformance, m_interface, [ this ] {
            m_interface->set_bias( 0 );
            m_interface->set_governor( u"performance"_s );
        } );
        QObject::connect( this, &CPUPowerController::setBalanced, m_interface, [ this ] {
            m_interface->set_bias( 6 );
            m_interface->set_governor( u"powersave"_s );
        } );
    }

Q_SIGNALS:
    void setPowersave();
    void setPerformance();
    void setBalanced();

public:
    org::klingt::tim::NovaCPUPowerInterface* m_interface;
};
