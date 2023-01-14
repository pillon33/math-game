#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <json-c/json.h>

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *slider1;     //Game difficulty slider
GtkWidget *slider2;     //Game length slider

double difficulty = 1;  //value of game difficulty
double length = 1;      //value of game length

json_object *ldboard;

void init_menu();
void init_play();
void init_settings();
void settings_back();
void save_settings();
void read_settings();
void init_leaderboard();
void save_leaderboard();
void read_leaderboard();

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
    gtk_widget_destroy(fixed);

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
    button = gtk_button_new_with_label("Powrot");
    g_signal_connect (button, "clicked", G_CALLBACK (init_menu), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach fourth button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 300);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

//function saves settings and opens previous panel
void settings_back()
{
    double dif_value = gtk_range_get_value(GTK_RANGE(slider1));
    double len_value = gtk_range_get_value(GTK_RANGE(slider2));

    if ((dif_value != difficulty) || (len_value != length))
    {
        difficulty = dif_value;
        length = len_value;

        save_settings();
    }

    init_menu();
}

//function saves settings to .json file
void save_settings()
{
    json_object *dif;
    json_object *len;
    json_object *settings;
    
    settings = json_object_new_object();

    dif = json_object_new_double(difficulty);
    json_object_object_add(settings, "difficulty", dif);

    len = json_object_new_double(length);
    json_object_object_add(settings, "length", len);

    json_object_to_file("settings.json", settings);
}

//function updates difficulty and length with values from settings file
//if file doesn't exist default values are inserted
void read_settings()
{
    json_object *dif;
    json_object *len;
    json_object *settings;

    settings = json_object_from_file("settings.json");

    if (settings)
    {
        dif = json_object_object_get(settings, "difficulty");
        len = json_object_object_get(settings, "length");
        difficulty = json_object_get_double(dif);
        length = json_object_get_double(len);
    }
    else
    {
        //sets default values if file doesn't exist
        difficulty = 1;
        length = 1;
    }
    
}

//function initializing settings window
void init_settings()
{
    read_settings();

    gtk_widget_destroy(fixed);

    GtkWidget *label;
    GtkWidget *button;

    //initialize fixed
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    label = gtk_label_new("Poziom trudnosci");
    gtk_fixed_put(GTK_FIXED(fixed), label, 320, 130);

    //initialize first slider
    slider1 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 3, 1);

    gtk_scale_set_digits(GTK_SCALE(slider1), 0);

    gtk_range_set_value(GTK_RANGE(slider1), difficulty);

    //set size
    gtk_widget_set_size_request(slider1, 160, 32);

    gtk_fixed_put(GTK_FIXED(fixed), slider1, 310, 150);

    label = gtk_label_new("Dlugosc gry");
    gtk_fixed_put(GTK_FIXED(fixed), label, 320, 230);

    //initialize second slider
    slider2 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 3, 1);

    gtk_scale_set_digits(GTK_SCALE(slider2), 0);

    gtk_range_set_value(GTK_RANGE(slider2), length);

    //set size
    gtk_widget_set_size_request(slider2, 160, 32);

    gtk_fixed_put(GTK_FIXED(fixed), slider2, 310, 250);

    //create "back button"
    button = gtk_button_new_with_label("Powrot");
    g_signal_connect (button, "clicked", G_CALLBACK (settings_back), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach fourth button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 300);

    gtk_widget_show_all(window);
}

//menu button 2 (Leaderboard)
void menu_b2(GtkWidget *button, GtkWidget *fixed)
{
    // code //
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
    //destroy previous grid if it already exists
    if (GTK_IS_WIDGET (fixed))
    {
        gtk_widget_destroy(fixed);
    }

    GtkWidget *button;

    //initialize fixed
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    //create first button
    button = gtk_button_new_with_label("Graj");
    g_signal_connect (button, "clicked", G_CALLBACK (init_play), NULL);

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
    g_signal_connect (button, "clicked", G_CALLBACK (init_settings), NULL);

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

    init_window();

    init_menu();

    gtk_main();

    return 0;
}