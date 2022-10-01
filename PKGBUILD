# Maintainer: Aggelos Tselios <aggelostselios777@gmail.com>

pkgname=libnvdialog-git
_pkgname=nvdialog
pkgver=0.2.0
pkgrel=1
epoch=
pkgdesc="A cross-platform library to show dialog boxes, written in C. (Git Version)"
arch=(x86_64 i686)
url="https://androgr.github.io/libnvdialog/"
_repo="https://github.com/AndroGR/nvdialog.git"
license=('MIT')
groups=()
depends=(gtk3 glibc gcc)
makedepends=(cmake git make)
checkdepends=()
optdepends=(
	'gtk4: To use the Gtk4 backend.'
	'libadwaita: Required by the Gtk4 backend to work.'
	'clang: Alternative compiler to GCC, if you wish to use it.'
)
provides=(libnvdialog)
conflicts=(libnvdialog)
replaces=(libnvdialog)
backup=()
options=()
install=
changelog=
source=("git+$_repo")
noextract=()
md5sums=('SKIP')
validpgpkeys=()

pkgver() {
	cd "${_pkgname}"
	printf "0.2.0.r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
	cd "${_pkgname}"
	cmake . -B build -DNVD_USE_GTK4=OFF -DNVD_BUILD_STATIC=OFF -DNVDIALOG_MAXBUF=4096 -G "Unix Makefiles" -DWIN32_TARGET=OFF -DCMAKE_BUILD_TYPE=Release
	cd build/ && make -j1
}

package() {
	cd "${_pkgname}"
	mkdir -p ${pkgdir}/usr/include/nvdialog/ ${pkgdir}/usr/lib/ && cd build
	cp -rf ../include/* ${pkgdir}/usr/include/nvdialog/ && cp -rf ./libnvdialog.so* ${pkgdir}/usr/lib/
}
