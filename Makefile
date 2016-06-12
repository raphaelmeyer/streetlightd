################################################################

all: check

################################################################

check:         #/ Run all tests
host:          #/ Build streetlightd for amd64
target:        #/ Build streetlightd for raspbian
rootfs:        #/ Create container with updated raspbian rootfs
doc:           #/ Create documentation

clean:         #/ Clean

################################################################

ci: check doc

################################################################

check: host
	./run-amd64 /home/root/source/ci/test.sh

host: host-workspace artifacts
	./run-amd64 make -j `nproc` streetlightd azure-sas-token session-test unit-test
	./copy-amd64 /workspace/azure-sas-token artifacts/amd64
	./copy-amd64 /workspace/streetlightd artifacts/amd64

host-workspace:
	./run-amd64 cmake /home/root/source

################################################################

target: target-workspace artifacts
	./run-raspbian make -j `nproc` streetlightd azure-sas-token session-test unit-test
	./copy-raspbian /workspace/azure-sas-token artifacts/raspbian
	./copy-raspbian /workspace/streetlightd artifacts/raspbian

target-workspace:
	./run-raspbian cmake -DCMAKE_TOOLCHAIN_FILE=/opt/cmake/raspbian.cmake /home/user/source

################################################################

artifacts:
	mkdir -p artifacts/amd64
	mkdir -p artifacts/raspbian

################################################################

.PHONY: rootfs
rootfs:
	./rootfs.sh

################################################################

doc:
	./run-amd64 /home/root/source/ci/documentation.sh

################################################################

.PHONY: clean
clean:
	rm -rf artifacts
	./run-amd64 make clean

################################################################

help:
	@echo
	@grep -E "^(\S+)\s*:\s*#/\s*(.*)$$" $(lastword $(MAKEFILE_LIST))
	@echo

