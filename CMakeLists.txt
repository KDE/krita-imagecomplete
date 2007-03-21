add_subdirectory(Poisson)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

set(kritaImageComplete_PART_SRCS ImageComplete.cc )

kde3_automoc(${kritaImageComplete_PART_SRCS})

kde3_add_kpart(kritaImageComplete ${kritaImageComplete_PART_SRCS})

target_link_libraries(kritaImageComplete ${KRITAUI_LIBRARY} Poisson)

install(TARGETS kritaImageComplete  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES  kritaImageComplete.desktop  DESTINATION ${SERVICES_INSTALL_DIR})

