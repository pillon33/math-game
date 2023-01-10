#include <gtk/gtk.h>
void tworz_okno(){
GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(win),800,600);
gtk_window_set_title(GTK_WINDOW(win),"Hello world");
g_signal_connect(G_OBJECT(win), "destroy", gtk_main_quit, NULL);
gtk_widget_show(win);
}
int main(int argc, char **argv){
gtk_init(&argc,&argv);// inicjujemy gtk
tworz_okno();
gtk_main();// uruchamia p˛etl˛e główn ˛a programu, która trwa
// do momentu wywołania w procesie funkcji gtk_main_quit
}
