#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "cpu_power_adaptor.h"

class CPUPower : public QObject
{
    Q_OBJECT

public:
    explicit CPUPower( QObject* parent ) :
        QObject( parent )
    {}

public Q_SLOTS:
    void set_bias( int bias )
    {
        using namespace Qt::StringLiterals;

        auto cpuDir = QDir {
            u"/sys/devices/system/cpu/"_s,
            u"cpu*"_s,
            QDir::SortFlag::Unsorted,
            QDir::Filter::Dirs,
        };

        for ( QFileInfo info : cpuDir.entryInfoList() ) {
            if ( info.fileName().endsWith( u"cpuidle"_s ) )
                continue;
            if ( info.fileName().endsWith( u"cpufreq"_s ) )
                continue;

            auto path = info.filesystemAbsoluteFilePath() / "power" / "energy_perf_bias";

            std::ofstream of = path;
            fmt::print( of, "{}\n", bias );
            if ( !of.good() )
                qWarning() << "write failed" << path.string() << bias;
        }
    }

    void set_governor( QString governor )
    {
        using namespace Qt::StringLiterals;

        auto cpuDir = QDir {
            u"/sys/devices/system/cpu/cpufreq"_s,
            u"policy*"_s,
            QDir::SortFlag::Unsorted,
            QDir::Filter::Dirs,
        };

        for ( QFileInfo info : cpuDir.entryInfoList() ) {
            auto path = info.filesystemAbsoluteFilePath() / "scaling_governor";

            std::ofstream of = path;
            fmt::print( of, "{}\n", governor.toStdString() );
            if ( !of.good() )
                qWarning() << "write failed" << path << governor;
        }
    }
};

int main( int argc, char** argv )
{
    QCoreApplication app( argc, argv );

    auto cpupower = new CPUPower( &app );

    new NovaCPUPowerInterfaceAdaptor( cpupower );
    auto connection = QDBusConnection::sessionBus();
    connection.registerObject( "/CpuPower", cpupower );
    connection.registerService( "org.klingt.tim.NovaCPUPower" );

    return app.exec();
}


#include "main.moc"
