cmake_minimum_required(VERSION 3.16)
project(abi2bot_arduino LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
)

# find dependencies
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()


## COMPILE
add_library(
  abi2bot_arduino
  SHARED
  hardware/tricycle_system.cpp
)
target_compile_features(abi2bot_arduino PUBLIC cxx_std_17)
target_include_directories(abi2bot_arduino PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
$<INSTALL_INTERFACE:include/abi2bot_arduino>
)
ament_target_dependencies(
  abi2bot_arduino PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

target_link_libraries(abi2bot_arduino PUBLIC serial)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${PROJECT_NAME} PRIVATE "abi2bot_arduino_BUILDING_DLL")

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface abi2bot_arduino.xml)

# INSTALL
install(
  DIRECTORY hardware/include/
  DESTINATION include/abi2bot_arduino
)

install(TARGETS abi2bot_arduino
  EXPORT export_abi2bot_arduino
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
endif()

## EXPORTS
ament_export_targets(export_abi2bot_arduino HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
