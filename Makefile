file := game

# OS specific
ifeq ($(OS),Windows_NT)
	BUILD_ARG = -G "MinGW Makefiles"
	B_RELEASE = --config Release
	MOVE_CMD  = move
	FILE_EXT  = .exe
	PATH_MV	  = build\application$(FILE_EXT) $(file)$(FILE_EXT)
else
	BUILD_ARG = -DCMAKE_BUILD_TYPE=Release
	MOVE_CMD  = mv
	PATH_MV	  = build/application $(file)
endif

.phony: run, install

install:
	cmake -S . -B build $(BUILD_ARG)
	cmake --build build $(B_RELEASE)
	@$(MOVE_CMD) $(PATH_MV)

run: install
	./$(file)
