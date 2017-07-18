all: install

depot_tools:
	@if [ ! -d depot_tools ]; then \
	    git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git; \
	fi

skia-checkout: depot_tools
	@if [ ! -d skia ]; then                      \
	    git clone git@github.com:google/skia.git; \
	fi
	@cd skia && python tools/git-sync-deps

skia-configure: skia-checkout
	@mkdir -p skia/out/Static/
	@cp skia-args.gn skia/out/Static/args.gn
	@cd skia && bin/gn gen out/Static

skia: skia-configure
	@PATH=`pwd`/depot_tools:$$PATH ninja -C skia/out/Static libskia.a

build: skia
	@npm build

install: build
	@npm install

clean:
	@rm -rf build depot_tools node_modules skia

.PHONY: depot_tools skia-checkout skia-configure skia prepare build
