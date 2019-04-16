cmake_minimum_required (VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(scripts)
set(CMAKE_CXX_STANDARD 11)
set(REPORT_FOLDER "Reports")# Set to "" if you wish to report to stderr




# Enable coverage for project, since 'target_compile_options' doesn't work well, set the global flag
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
endif()




#[[ 
    "-O0"                      [optional]       Disables optimizations, allowing better stacktraces. Alternative: -01
    "-g"                       [required]       Compile with debug information (filenames, line numbers etc)
    "-rdynamic"                [optional]       Needed for shared libraries, so the function can be backtraced
    "-fno-omit-frame-pointer"  [optional]       Nicer stacktraces
    "-funwind-tables"          [required:ARM]   "Allows walking back in the stack frame from given a given point",
                                                toggling this flag avoids stacktraces with only one entry
    "-mapcs-frame"             [required:ARM]   "Generate a stack frame that is compliant 
                                                with the ARM Procedure Call Standard"
]]
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

	# Set global options
	set(GLOBAL_COMPILER_FLAGS -O0 -g -pthread)
	set(GLOBAL_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -fno-omit-frame-pointer -rdynamic")
	set(GLOBAL_LINK_LIBRARIES "")
	include_directories(${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/src")

	# AddressSanitizer
	# https://clang.llvm.org/docs/AddressSanitizer.html
	add_executable(asan "${PROJECT_SOURCE_DIR}/asan.cpp")
	target_compile_options(asan PRIVATE -fsanitize=address ${GLOBAL_COMPILER_FLAGS})
	set_target_properties(asan PROPERTIES LINK_FLAGS "-fsanitize=address ${GLOBAL_LINKER_FLAGS}")
	target_link_libraries(asan ${GLOBAL_LINK_LIBRARIES})
	create_script_asan(asan "${REPORT_FOLDER}")

	# ThreadSanitizer
	# https://clang.llvm.org/docs/ThreadSanitizer.html
	add_executable(tsan "${PROJECT_SOURCE_DIR}/tsan.cpp")
	target_compile_options(tsan PRIVATE -fsanitize=thread ${GLOBAL_COMPILER_FLAGS})
	set_target_properties(tsan PROPERTIES LINK_FLAGS "-fsanitize=thread ${GLOBAL_LINKER_FLAGS}")
	target_link_libraries(tsan ${GLOBAL_LINK_LIBRARIES})
	create_script_tsan(tsan "${REPORT_FOLDER}")

	# UndefinedBehaviorSanitizer
	# https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
	add_executable(ubsan "${PROJECT_SOURCE_DIR}/ubsan.cpp")
	target_compile_options(ubsan PRIVATE -fsanitize=undefined ${GLOBAL_COMPILER_FLAGS})
	set_target_properties(ubsan PROPERTIES LINK_FLAGS "-fsanitize=undefined -fno-sanitize-recover=all ${GLOBAL_LINKER_FLAGS}")
	target_link_libraries(ubsan ${GLOBAL_LINK_LIBRARIES})
	create_script_ubsan(ubsan "${REPORT_FOLDER}")

	# Valgrind
	# http://valgrind.org/docs/manual/mc-manual.html
	add_executable(valg "${PROJECT_SOURCE_DIR}/valg.cpp")
	target_compile_options(valg PRIVATE ${GLOBAL_COMPILER_FLAGS})
	set_target_properties(valg PROPERTIES LINK_FLAGS "${GLOBAL_LINKER_FLAGS}")
	target_link_libraries(valg ${GLOBAL_LINK_LIBRARIES})
	create_script_valgrind(valg "${REPORT_FOLDER}")

	# Package scripts into "_run_sanitizers" with abort on error "ON"
	package_scripts("_run_sanitizers" ON "s_asan.sh" "s_tsan.sh" "s_ubsan.sh")

	# Coverage
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		# Coverage data will be generate in execution directory
		add_executable(cov "${PROJECT_SOURCE_DIR}/cov.cpp")
		target_compile_options(cov PRIVATE ${GLOBAL_COMPILER_FLAGS})
		set_target_properties(cov PROPERTIES LINK_FLAGS "${GLOBAL_LINKER_FLAGS}")
		target_link_libraries(cov ${GLOBAL_LINK_LIBRARIES})
		create_script_llvm_coverage(cov "${PROJECT_SOURCE_DIR}/cov.cpp")
		#create_script_llvm_coverage(cov "")#all
		#create_script_llvm_coverage(cov "${PROJECT_SOURCE_DIR}/src")#specific folder
		#create_script_llvm_coverage(cov "${PROJECT_SOURCE_DIR}/src/cov1.h")#specific file
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		# Let's install gcovr: sudo apt-get install gcovr 
		# because it is easier to handle this stuff
		add_executable(cov "${PROJECT_SOURCE_DIR}/cov.cpp")
		target_compile_options(cov PRIVATE ${GLOBAL_COMPILER_FLAGS})
		set_target_properties(cov PROPERTIES LINK_FLAGS "${GLOBAL_LINKER_FLAGS}")
		target_link_libraries(cov ${GLOBAL_LINK_LIBRARIES})
		create_script_gcc_coverage(cov "${PROJECT_SOURCE_DIR}/cov.cpp")
		#create_script_gcc_coverage(cov "")#all
		#create_script_gcc_coverage(cov "${PROJECT_SOURCE_DIR}/src")#specific folder
		#create_script_gcc_coverage(cov "${PROJECT_SOURCE_DIR}/src/cov1.h")#specific file
	endif()

	#[[ Generate core dump

        Linux:
            Permanently enable core dumps:
                File:   /etc/security/limits.conf
                Lines:  *       soft    core    8000000
                        root    hard    core    10000000
                Note:   For type 'core' the value is in KB
			
            Permanently set core dump path:
                Disable pattern overwrite by apport:
                    File:       /etc/default/apport
                    Change to:  enabled=0
                Set new pattern:
                    File folder:    /etc/sysctl.d/
                    Create file:    60-core-pattern.conf
                    Lines:          kernel.core_pattern = mycoredump%e_%t_%p

	]]
	add_executable(cored "${PROJECT_SOURCE_DIR}/cored.cpp")
	target_compile_options(cored PRIVATE ${GLOBAL_COMPILER_FLAGS})
	set_target_properties(cored PROPERTIES LINK_FLAGS "${GLOBAL_LINKER_FLAGS}")
	target_link_libraries(cored ${GLOBAL_LINK_LIBRARIES})

endif()