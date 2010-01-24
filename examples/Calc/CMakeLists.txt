project(Calc)

include_directories(${CUKE_INCLUDE_DIR} Calc)

add_library(Calc Calc/Calculator)

add_executable(CalcFeatures CalcFeatures/CalculatorSteps)
target_link_libraries(CalcFeatures Calc cuke)

