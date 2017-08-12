all: install

DEPOT_TOOLS_URL ?= https://chromium.googlesource.com/chromium/tools/depot_tools.git
DEPOT_TOOLS_REV ?= ""

SKIA_URL ?= git@github.com:google/skia.git
SKIA_REV ?= ""

EGL_PLATFORM ?= x11

depot_tools:
	@if [ ! -d depot_tools ]; then           \
	    git clone $(DEPOT_TOOLS_URL);        \
	    if [ -n "$(DEPOT_TOOLS_REV)" ]; then \
	        pushd depot_tools;               \
	        git checkout $(DEPOT_TOOLS_REV); \
	        popd;                            \
	    fi;                                  \
	fi

skia-checkout: depot_tools
	@if [ ! -d skia ]; then           \
	    git clone $(SKIA_URL);        \
	    if [ -n "$(SKIA_REV)" ]; then \
	        pushd skia;               \
	        git checkout $(SKIA_REV); \
	        popd;                     \
	    fi;                           \
	fi
	@cd skia && python tools/git-sync-deps

skia-configure: skia-checkout
	@mkdir -p skia/out/Static/
	@cp skia-args.gn skia/out/Static/args.gn
	@cd skia && bin/gn gen out/Static

skia: skia-configure
	@PATH=`pwd`/depot_tools:$$PATH ninja -C skia/out/Static libskia.a

build: skia
	@./tools/generate_config.sh $(EGL_PLATFORM)
	@npm build

install: build
	@npm install

clean:
	@rm -rf build depot_tools node_modules skia config.gypi

.PHONY: depot_tools skia-checkout skia-configure skia prepare build
