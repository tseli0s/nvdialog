CC?=gcc
CFLAGS?=-Wall -Wextra -pedantic -std=c11 -O3 -g0 -s
LINK:=-lnvdialog
SRC:=nvd_flatpak_test.c
OUTFILE:=nvd-flatpak-test
MANIFEST:=io.tseli0s.NvdFlatpakTest.json

flatpak-test: $(SRC)
	$(CC) $(SRC) -o $(OUTFILE) $(CFLAGS) $(LINK)
	@echo "Done."

flatpak:
	flatpak-builder build-dir/ $(MANIFEST) --force-clean --install --user

clean: .flatpak-builder/ build-dir/
	@rm -rfv .flatpak-builder/ build-dir/