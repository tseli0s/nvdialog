#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (gtk_init_check(&argc, &argv) != true)
	{
		puts("Not initialized.");
		return -12;
	}
	gtk_main();
	gtk_main_quit();
}
