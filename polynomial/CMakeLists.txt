cmake_minimum_required(VERSION 3.10)
project(PolynomialCalculator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(polynomial_calculator
    main.c
    polynomial.c
) 