#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "CPUPowerController.h"

int main( int argc, char* argv[] )
{
    using namespace Qt::StringLiterals;

    QGuiApplication app( argc, argv );

    auto ctrl = new CPUPowerController( &app );

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
        QCoreApplication::exit( -1 );
    },
        Qt::QueuedConnection );

    QVariantMap props; //{ u"cpupower"_s, QVariant::fromValue( ctrl ) }
    props.insert( u"cpupower"_s, QVariant::fromValue( ctrl ) );

    engine.setInitialProperties( props );

    engine.loadFromModule( "NovaCPUPowerModule", "Main" );

    return app.exec();
}
