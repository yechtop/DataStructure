# cmake_minimum_required(VERSION <specify CMake version here>)
project(Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(link linearTable/link.cpp)
add_executable(stack stack/stack.cpp)
add_executable(queue queue/queue.cpp)
add_executable(queue_apply queue/queue_apply.cpp)
add_executable(kmp string/kmp.cpp)
add_executable(binaryTree binaryTree/binaryTree.cpp)
add_executable(binarySearchTree binaryTree/BinarySearchTree.cpp)