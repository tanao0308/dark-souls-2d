# 从新构建
cmake -S . -B build
# 增量编译
cmake --build build
# 运行
./build/mb
# 格式化
find src \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -not -path "*/build/*" -type f | xargs clang-format -i