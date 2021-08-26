BUILD_DIR=build 

install: compile

detect:	
ifeq ($(OS), Windows_NT)
	@cmake . -B build -G "Unix Makefiles" 
else 
	@cmake . -B build 
endif

compile: detect
	@$(MAKE) -C $(BUILD_DIR) install

clean:
	@rm -rf build 