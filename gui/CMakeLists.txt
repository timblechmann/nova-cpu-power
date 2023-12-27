set(InterfaceSources)
qt_add_dbus_interface(InterfaceSources
    ../common/cpu-power-interface.xml
    cpu_power_interface
)


qt_add_executable(nova-cpu-power
    main.cpp
    CPUPowerController.h
    ${InterfaceSources}
)

qt_add_qml_module(nova-cpu-power
    URI NovaCPUPowerModule
    VERSION 1.0
    QML_FILES Main.qml

    RESOURCE_PREFIX /org.klingt.tim/rc
    RESOURCES icon.svg
)

target_link_libraries(nova-cpu-power
    PRIVATE Qt6::Quick Qt6::DBus
)
target_include_directories(nova-cpu-power PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

include(GNUInstallDirs)
install(TARGETS nova-cpu-power
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
