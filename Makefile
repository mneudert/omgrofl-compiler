OBJ_DIR := _obj

SRCS := $(shell find src \( -name "*.cpp" ! -iname "omgrofl.cpp" \))
OBJS := $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET := omgrofl


$(OBJ_DIR)/%.o: src/%.cpp
	@echo "  CXX  src/$*.cpp"
	@mkdir -p $(dir $@)
	@$(CXX) -c -o $@ src/$*.cpp

$(TARGET): clean $(OBJS)
	@echo ""
	@echo "  >>   ./$@"
	@rm -f $@
	@$(CXX) -o $@ src/omgrofl.cpp $(OBJS)
	@echo "> OK <"


clean:
	@rm -rf $(OBJ_DIR)

default: $(TARGET)

lint:
	@cpplint \
		--root="src" \
		--filter="-legal/copyright" \
		src/*.h src/*.cpp


.PHONY: clean default
.DEFAULT_GOAL := default
