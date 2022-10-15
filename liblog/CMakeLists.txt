cmake_minimum_required (VERSION 3.8)

project ("liblog")

set( SOURCES 
		"src/console-log.cpp"
		"src/filelog.cpp"
		"src/log.cpp"
		"src/logtype.cpp"
	)

add_library("liblog" STATIC  ${SOURCES})

