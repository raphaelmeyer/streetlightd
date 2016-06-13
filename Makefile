################################################################

all: check

################################################################

check:         #/ Run all tests
host:          #/ Build streetlightd for amd64
target:        #/ Build streetlightd for raspbian
doc:           #/ Create documentation

clean:         #/ Clean

################################################################

ci: check doc

################################################################

check: host
	./run-amd64 /home/root/source/ci/test.sh

host: host-workspace artifacts
	./run-amd64 make -j `nproc` streetlightd azure-sas-token session-test unit-test
	./copy-amd64 /workspace/azure-sas-token _artifacts/amd64
	./copy-amd64 /workspace/streetlightd _artifacts/amd64

host-workspace:
	./run-amd64 cmake /home/root/source

################################################################

target: target-daemon target-sas-token

target-daemon: target-buildfolder
	cmake --build _build --target streetlightd
	cp _build/streetlightd _artifacts/

target-sas-token: target-buildfolder
	cmake --build _build --target azure-sas-token
	cp _build/azure-sas-token _artifacts/

target-buildfolder:
	mkdir -p _build
	cd _build && cmake ../source

################################################################

.PHONY: artifacts
artifacts:
	mkdir -p _artifacts/amd64

################################################################

doc:
	./run-amd64 /home/root/source/ci/documentation.sh

################################################################

.PHONY: clean
clean:
	rm -rf _artifacts
	rm -rf _build
	./run-amd64 make clean

################################################################

help:
	@echo
	@grep -E "^(\S+)\s*:\s*#/\s*(.*)$$" $(lastword $(MAKEFILE_LIST))
	@echo
