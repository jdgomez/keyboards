# Solo para la mitad central: recibe las pulsaciones de ambas mitades y el WPM.
if(NOT CONFIG_ZMK_SPLIT_ROLE_CENTRAL AND CONFIG_ZMK_SPLIT)
  message(FATAL_ERROR "nice_view_bongo solo soporta la mitad central de un split")
endif()

if(CONFIG_ZMK_DISPLAY AND CONFIG_NICE_VIEW_BONGO_WIDGET)
  zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)
  zephyr_library_sources(custom_status_screen.c)
  zephyr_library_sources(bongo_status.c)
  zephyr_library_sources(bongo_frames.c)
  zephyr_library_sources(bolt.c)
endif()
