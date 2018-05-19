cmake_minimum_required(VERSION 2.8)
project(SmartScript)

if(UNIX)
		set(RUNTIME_INSTALL_DIR /usr/bin)
endif()
aux_source_directory(./src SRCDIR)
aux_source_directory(./src/runtime RUNTIMEDIR)
add_executable(sscript ${SRCDIR} ${RUNTIMEDIR})
install(TARGETS sscript
		RUNTIME
		DESTINATION ${RUNTIME_INSTALL_DIR}/bin)
