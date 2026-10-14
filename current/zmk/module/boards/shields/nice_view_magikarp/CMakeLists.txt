# Solo para la mitad periférica: la central usa el shield nice_view de serie.
if(CONFIG_ZMK_SPLIT_ROLE_CENTRAL OR NOT CONFIG_ZMK_SPLIT)
  message(FATAL_ERROR "nice_view_magikarp solo soporta la mitad periférica de un split")
endif()

if(CONFIG_ZMK_DISPLAY AND CONFIG_NICE_VIEW_WIDGET_STATUS)
  zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)
  zephyr_library_sources(custom_status_screen.c)
  zephyr_library_sources(widgets/bolt.c)
  zephyr_library_sources(widgets/util.c)
  zephyr_library_sources(widgets/art.c)
  zephyr_library_sources(widgets/peripheral_status.c)
endif()
