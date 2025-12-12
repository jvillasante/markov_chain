.PHONY: clean
clean:
	if test -d "build/debug"; then cmake --build "build/debug" --target clean; fi
	if test -d "build/release"; then cmake --build "build/release" --target clean; fi

.PHONY: debug
debug:
	cmake -E make_directory "build/debug" && \
    cmake -S . -B "build/debug" -G Ninja \
          -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && \
    cmake --build build/debug --config Debug

.PHONY: release
release:
	cmake -E make_directory "build/release" && \
    cmake -S . -B "build/release" -G Ninja \
        -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build/release --config Release

.PHONY: install
install:
	cmake --build build/release --config Release --target install

.DEFAULT_GOAL := debug
