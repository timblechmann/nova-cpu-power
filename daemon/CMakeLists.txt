set(AdapterSources)
qt_add_dbus_adaptor(AdapterSources
    ../common/cpu-power-interface.xml
    qobject.h
    ""
    cpu_power_adaptor
)

qt_add_executable(nova-cpu-powerd
    main.cpp
    ../common/cpu-power-interface.xml
    ${AdapterSources}
)

target_include_directories(nova-cpu-powerd PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(nova-cpu-powerd
    PRIVATE Qt6::Core Qt6::DBus fmt::fmt
)

include(GNUInstallDirs)
install(TARGETS nova-cpu-powerd
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
