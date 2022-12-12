# Maintainer: Aggelos Tselios <aggelostselios777@gmail.com>

pkgname=nvdialog
_pkgname=nvdialog
pkgver=0.5.0
pkgrel=1
epoch=
pkgdesc="Cross-platform dialog box library written in C, using the host's standard backend."
arch=(x86_64 i686 aarch64)
url="https://androgr.github.io/libnvdialog/"
_repo="https://github.com/AndroGR/nvdialog.git"
license=('MIT')
groups=()
depends=(gtk4 libadwaita glibc gcc cmake) # Arch Linux is modern enough to safely say that
					  # libadwaita won't cause any problems as the default
					  # backend.
makedepends=(cmake git ninja)
checkdepends=()
optdepends=()
provides=(libnvdialog)
conflicts=(libnvdialog)
replaces=(libnvdialog)
backup=()
options=()
install=
changelog=
source=()
noextract=()
md5sums=()
validpgpkeys=()

build() {
	cd .. # Arch wants to go to src/ for some reason :(
	[[ -d build/ ]] && rm -rfv build/ # Needed step
	cmake . -B build -DNVD_USE_GTK4=ON -DNVD_BUILD_STATIC=OFF -DNVDIALOG_MAXBUF=4096 -G "Ninja" -DWIN32_TARGET=OFF -DCMAKE_BUILD_TYPE=Release
	cd build/ && ninja
}

package() {
	cd ..
	mkdir -p ${pkgdir}/usr/include/nvdialog/ ${pkgdir}/usr/lib/ && cd build
	cp -rf ../include/* ${pkgdir}/usr/include/nvdialog/ && cp -rf ./libnvdialog.so* ${pkgdir}/usr/lib/
}
