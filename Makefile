# @author : dawbanc
all:

CURRENT_DATE_TIME := $(shell date +"%y%m%d_%H%M")
GIT_BRANCH := $(shell git branch --show-current)

clean:
	@echo "Cleaning directory..."
	@rm -f scarf scarf-config-creator
	@rm -f null
	@rm -f scarf_log scarf_debug
	@rm -f scc_log
	@rm -f *.csv
	@rm -f src/common/version.h
	@touch src/common/version.h

build: update_version build_scarf build_scarf_config_creator

build_debug: update_version_debug build_scarf_debug build_scc_debug

build_scarf:
	g++ -Wall -fPIC \
	-I${PWD}/src/scarf \
	-I${PWD}/src/common \
	-o scarf src/scarf/scarf.cpp

build_scarf_config_creator build_scc:
	g++ -Wall -fPIC \
	-I${PWD}/src/scarf_config_creator \
	-I${PWD}/src/common \
	-o scarf-config-creator src/scarf_config_creator/scarf_config_creator.cpp

update_version:
	@sed "s/000000_0000/$(CURRENT_DATE_TIME)_$(GIT_BRANCH)/g" src/common/version_string_file.cfg > src/common/version.h

build_scarf_debug:
	g++ -g -Wall -fPIC \
	-I${PWD}/src/scarf \
	-I${PWD}/src/common \
	-o scarf src/scarf/scarf.cpp

build_scc_debug:
	g++ -Wall -fPIC \
	-I${PWD}/src/scarf_config_creator \
	-I${PWD}/src/common \
	-o scarf-config-creator src/scarf_config_creator/scarf_config_creator.cpp

update_version_debug:
	@sed "s/000000_0000/$(CURRENT_DATE_TIME)_$(GIT_BRANCH) DEBUG/g" src/common/version_string_file.cfg > src/common/version.h

run:
	./scarf -dummy_run

debug:
	gdb scarf
