#Specify installation rules
install(TARGETS ${LIB_NAME} DESTINATION lib)

install(FILES ${INC} DESTINATION include/cache)
install(FILES ${INC_CACHE} DESTINATION include)

# Set up CPack
set(CPACK_PACKAGE_NAME "lib_${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY " CACHE library")
set(CPACK_PACKAGE_CONTACT "Salomon Lee")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

# Generate an installer
set(CPACK_GENERATOR "ZIP")  # You can choose other generators like "DEB", "RPM", "NSIS", etc.

include(CPack)