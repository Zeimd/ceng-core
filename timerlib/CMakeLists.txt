cmake_minimum_required (VERSION 3.8)

project ("timerlib")

set( SOURCES 
		"timerlib.CPP"
	)

add_library("timerlib" STATIC  ${SOURCES})

