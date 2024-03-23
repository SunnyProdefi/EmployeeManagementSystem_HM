# 添加当前目录中的所有源文件到变量SRC_FILES
file(GLOB SRC_FILES "*.cpp")

# 创建可执行文件
add_executable(MyExecutable ${SRC_FILES})

# 如果有需要链接的库，例如动态链接库或静态链接库
# target_link_libraries(MyExecutable PRIVATE library_name)