#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GtkWidget *window;
GtkWidget *fixed;

void init_menu();

void back()
{
    gtk_widget_destroy(fixed);
    init_menu();
}

// function called when learning game type is chosen
void nauka()
{
    // code here //
}

// function called when test game type is chosen
void test()
{
    // code here //
}

// function called when arcade game type is chosen
void arcade()
{
    // code here //
}

void init_play()
{
    GtkWidget *button;

    //initialize fixed
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    //create first button
    button = gtk_button_new_with_label("Nauka");
    g_signal_connect (button, "clicked", G_CALLBACK (nauka), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach first button
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 150);

    //create second button
    button = gtk_button_new_with_label("Test");
    g_signal_connect (button, "clicked", G_CALLBACK (test), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach second button
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 200);

    //create third button
    button = gtk_button_new_with_label("Arcade");
    g_signal_connect (button, "clicked", G_CALLBACK (arcade), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach third button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 250);

    //create fourth button
    button = gtk_button_new_with_label("Wyjscie");
    g_signal_connect (button, "clicked", G_CALLBACK (back), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach fourth button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 300);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

void init_settings()
{
    GtkWidget *slider;
    GtkWidget *label;

    //initialize fixed
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    label = gtk_label_new("Poziom trudnosci");
    gtk_fixed_put(GTK_FIXED(fixed), label, 320, 130);

    //initialize first slider
    slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 3, 1);

    //set size
    gtk_widget_set_size_request(slider, 160, 32);

    gtk_fixed_put(GTK_FIXED(fixed), slider, 310, 150);

    label = gtk_label_new("Dlugosc gry");
    gtk_fixed_put(GTK_FIXED(fixed), label, 320, 230);

    //initialize second slider
    slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 3, 1);

    //set size
    gtk_widget_set_size_request(slider, 160, 32);

    gtk_fixed_put(GTK_FIXED(fixed), slider, 310, 250);

    gtk_widget_show_all(window);
}

//menu button 1 (Play)
void menu_b1(GtkWidget *button)
{
    gtk_widget_destroy(fixed);
    init_play();
}

//menu button 2 (Leaderboard)
void menu_b2(GtkWidget *button, GtkWidget *fixed)
{
    // code //
}

//menu button 3 (Settings)
void menu_b3(GtkWidget *button, GtkApplication *app)
{
    gtk_widget_destroy(fixed);
    init_settings();
}

//menu button 4 ()
void menu_b4(GtkWidget *button, GtkApplication *app)
{
    // code here //
}

void init_window()
{
    //setup window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Math Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
}

//function intializing menu window
void init_menu()
{
    GtkWidget *button;

    //initialize fixed
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    //create first button
    button = gtk_button_new_with_label("Graj");
    g_signal_connect (button, "clicked", G_CALLBACK (menu_b1), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach first button
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 150);

    //create second button
    button = gtk_button_new_with_label("Wyniki");
    g_signal_connect (button, "clicked", G_CALLBACK (menu_b2), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach second button
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 200);

    //create third button
    button = gtk_button_new_with_label("Ustawienia");
    g_signal_connect (button, "clicked", G_CALLBACK (menu_b3), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach third button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 250);

    //create fourth button
    button = gtk_button_new_with_label("Wyjscie");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach fourth button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 300);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}


int main(int argc, char *argv[]) 
{
    srand(time(NULL));

    gtk_init(&argc, &argv);

    // GtkApplication *app;
    // int status;

    // app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    // g_signal_connect (app, "activate", G_CALLBACK (init_menu), NULL);
    // status = g_application_run (G_APPLICATION (app), argc, argv);
    // g_object_unref (app);

    init_window();

    init_menu();

    gtk_main();

    return 0;
}