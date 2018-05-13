file (GLOB main_SRC "*.c" "*.cpp")

add_executable (
  # Executable
  main

  # Sources
  ${main_SRC}
)
