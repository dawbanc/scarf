# @author : dawbanc
all:

clean:
	@rm -f scarf scarf-config-creator
	@rm -f null
	@rm -f scarf_log scarf_debug
	@rm -f scc_log

build: build_scarf build_scarf_config_creator

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

run:
	./scarf -dummy_run -int_log internal_log
