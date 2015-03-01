/* 
 * File:   newsimpletest.cpp
 * Author: max
 *
 * Created on 18.04.2014, 22:47:43
 */

#include <stdlib.h>
#include <iostream>
#include "../ContainerIO.h"
#include "../Vertraege.h"

/*
 * Simple C++ Test Suite
 */

void testContainerIO( ) {
    ContainerIO containerIO( );
    if( true /*check result*/ ) {
        std::cout << "%TEST_FAILED% time=0 testname=testContainerIO (newsimpletest) message=error message sample" << std::endl;
    }
}

void testConnect( ) {
    ContainerIO containerIO;
    containerIO.connect( );
    if( true /*check result*/ ) {
        std::cout << "%TEST_FAILED% time=0 testname=testConnect (newsimpletest) message=error message sample" << std::endl;
    }
}

void testGetVertraege( ) {
    Vertraege v;
    ContainerIO containerIO;
    containerIO.getVertraege( v);
    if( true /*check result*/ ) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetVertraege (newsimpletest) message=error message sample" << std::endl;
    }
}

int main( int argc, char** argv ) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testContainerIO (newsimpletest)" << std::endl;
    testContainerIO( );
    std::cout << "%TEST_FINISHED% time=0 testContainerIO (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testConnect (newsimpletest)" << std::endl;
    testConnect( );
    std::cout << "%TEST_FINISHED% time=0 testConnect (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testGetVertraege (newsimpletest)" << std::endl;
    testGetVertraege( );
    std::cout << "%TEST_FINISHED% time=0 testGetVertraege (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS );
}

