#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number = 0;

//function updating label with new number value
void update_label(GtkWidget *label)
{
    char *text;
    text = g_strdup_printf ("Value : %d",number);

    gtk_label_set_label(GTK_LABEL(label), text);

    g_free(text);
}

//increases global number
void b1(GtkWidget *button, GtkWidget *label)
{
    number++;

    update_label(label);
}

//decreases global number
void b2(GtkWidget *button, GtkWidget *label)
{
    number--;

    update_label(label);
}

//resets global number
void b3(GtkWidget *button, GtkWidget *label)
{
    number = 0;

    update_label(label);
}

//sets global number to random in range (1, 100)
void b4(GtkWidget *button, GtkWidget *label)
{
    number = rand()%100 + 1;

    update_label(label);
}

//function intializing menu window
void init_menu()
{
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *button;
    GtkWidget *label;

    //setup window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Math Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    //initialize grid
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    //create label
    char *text;
    text = g_strdup_printf ("Value : %d",number);
    label = gtk_label_new(text);
    g_free(text);

    gtk_fixed_put(GTK_FIXED(fixed), label, 340, 100);

    //create first button
    button = gtk_button_new_with_label("Button 1");
    g_signal_connect (button, "clicked", G_CALLBACK (b1), label);

    //attach first button
    gtk_fixed_put(GTK_FIXED(fixed), button, 340, 150);

    //create second button
    button = gtk_button_new_with_label("Button 2");
    g_signal_connect (button, "clicked", G_CALLBACK (b2), label);

    //attach second button
    gtk_fixed_put(GTK_FIXED(fixed), button, 340, 200);

    //create third button
    button = gtk_button_new_with_label("Button 3");
    g_signal_connect (button, "clicked", G_CALLBACK (b3), label);

    //attach third button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 340, 250);

    //create fourth button
    button = gtk_button_new_with_label("Button 4");
    g_signal_connect (button, "clicked", G_CALLBACK (b4), label);

    //attach fourth button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 340, 300);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

int main(int argc, char *argv[]) 
{
    srand(time(NULL));

    gtk_init(&argc, &argv);

    init_menu();

    gtk_main();

    return 0;
}