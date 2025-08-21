# Maintainer: Aggelos Tselios <aggelostselios777@gmail.com>

pkgname=nvdialog
_pkgname=nvdialog
pkgver=0.10.0
pkgrel=1
epoch=
pkgdesc="Cross-platform dialog box library written in C, using the host's standard backend."
arch=(x86_64 i686 aarch64)
url="https://tseli0s.github.io/nv.dialog/"
_repo="https://github.com/tseli0s/nvdialog.git"
license=('MIT')
groups=()
depends=(gtk3 glibc)		
makedepends=(git ninja gcc cmake)
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
	cmake . -B build -DNVD_USE_GTK4=OFF -DNVD_BUILD_STATIC=ON -DNVDIALOG_MAXBUF=4096 -G "Ninja" -DCROSS_COMPILE_FOR_WIN32=OFF -DCMAKE_BUILD_TYPE=Release
	cd build/ && ninja
}

package() {
	cd ..
	mkdir -p ${pkgdir}/usr/include/nvdialog/ ${pkgdir}/usr/lib/ && cd build
	cp -rf ../include/* ${pkgdir}/usr/include/nvdialog/ && cp -rf ./libnvdialog.so* ${pkgdir}/usr/lib/
}
