import  Qt.labs.platform

import NovaCPUPowerModule

SystemTrayIcon {
    property CPUPowerController cpupower

    visible: true

    tooltip: "Nova Power"

    icon {
        source: "qrc:///org.klingt.tim/rc/NovaCPUPowerModule/icon.svg"
    }

    menu: Menu {
        MenuItem {
            text: qsTr("Performance")
            onTriggered: cpupower.setPerformance()
        }
        MenuItem {
            text: qsTr("Powersave")
            onTriggered: cpupower.setPowersave()
        }
        MenuItem {
            text: qsTr("Balanced")
            onTriggered: cpupower.setBalanced()
        }
        MenuItem {
            text: qsTr("Quit")
            onTriggered: Qt.quit()
        }
    }

    onActivated: menu.open()
}
