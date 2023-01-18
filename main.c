#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <json-c/json.h>
#include <stdbool.h>

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *slider1;     //Game difficulty slider
GtkWidget *slider2;     //Game length slider
GtkWidget *entry;

int difficulty = 1;  //value of game difficulty
int length = 1;      //value of game length
int correct_answers;

int ranges[3][4][2] = {
    // add       sub        mult         div
    { {1, 25},   {1, 50},   {1, 10},    {1, 5} },      //easy
    { {15, 50},  {30, 100}, {7, 20},    {2, 10} },     //medium
    { {25, 75},  {50, 150}, {10, 100},  {5, 20} }      //hard
};

char operations[4] = {'+', '-', '*', '/'};

json_object *ldboard;   //json object storing leaderboard data


//structure representing question 
//for example if operation='+' number1 + number2 = expected_answer
//if entered_answer == expected_answer answered_correctly = true (otherwise it is set to false)
typedef struct Question
{
    struct Question *prev;
    int number1;
    int number2;
    int expected_result;
    char operation;
    bool answered_correctly;
    struct Question *next;
}Question;

Question *head = NULL;     //head of linked list
Question *iter = NULL;     //current question
Question *buf = NULL;
typedef struct Question *node;        //linked list node

char *game;         //string determinig game type
char operation;    //string determinig which operation user wants to focus on

void init_menu();
void init_play();
void init_settings();
void init_operation_choice();
void settings_back();
void save_settings();
void read_settings();
void plus();
void minus();
void mult();
void division();
void mixed();
void init_question();
void answer();
void get_question();
void generate_questions();
void init_evaluate_learn();
void init_evaluate_test();
void init_evaluate_arcade();
void test();
void learn();
void clear_questions();
void arcade();
void evaluate_arcade();
void init_leaderboard();
void save_leaderboard();
void read_leaderboard();

void init_question()
{
    GtkWidget *label;

    //go to next question that user didn't answer
    while ((iter != NULL) && (iter->answered_correctly))
    {
        iter = iter->next;
    }

    //if there are no more questions
    if (iter == NULL)
    {
        if (strcmp(game, "learn") == 0)
        {
            if (correct_answers == length*5)
            {
                init_evaluate_learn();
                return;
            }
            else
            {
                iter = head;
            }
        }
        else
        {
            init_evaluate_test();
            return;
        }
    }

    //go to next question that user didn't answer
    while ((iter->answered_correctly))
    {
        iter = iter->next;
    }
    
    
    gtk_widget_destroy(fixed);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    char *text;
    text = g_strdup_printf ("%d %c %d = ?", iter->number1, iter->operation, iter->number2);
    label = gtk_label_new(text);
    gtk_fixed_put(GTK_FIXED(fixed), label, 350, 200);

    entry = gtk_entry_new();
    gtk_widget_set_size_request(entry, 160, 32);
    g_signal_connect (entry, "activate", G_CALLBACK (answer), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), entry, 310, 220);

    gtk_window_set_focus(GTK_WINDOW(window), entry);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

void init_evaluate_learn()
{
    GtkWidget *label;
    GtkWidget *image;
    GtkWidget *button;
    GdkPixbuf *pixbuf;

    char *path;
    char *text;

    clear_questions();

    path = "./resources/learning_finished.jpg";

    gtk_widget_destroy(fixed);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    pixbuf = gdk_pixbuf_scale_simple(pixbuf, 423, 283, GDK_INTERP_BILINEAR);

    image = gtk_image_new_from_pixbuf(pixbuf);

    gtk_fixed_put(GTK_FIXED(fixed), image, 200, 40);

    text = g_strdup_printf("Nauka zakończona, kontynuuj lub przejdź do testu", correct_answers, length*5);
    label = gtk_label_new(text);
    gtk_fixed_put(GTK_FIXED(fixed), label, 200, 350);

    button = gtk_button_new_with_label("Kontynuuj");
    gtk_widget_set_size_request(button, 160, 32);
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 400);
    g_signal_connect (button, "clicked", G_CALLBACK (init_menu), NULL);

    button = gtk_button_new_with_label("Przejdź do testu");
    gtk_widget_set_size_request(button, 160, 32);
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 450);
    g_signal_connect (button, "clicked", G_CALLBACK (test), NULL);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

void init_evaluate_test()
{
    GtkWidget *label;
    GtkWidget *image;
    GtkWidget *button;
    GdkPixbuf *pixbuf;

    clear_questions();

    double score = ((double)correct_answers/(length*5))*100;
    bool passed = score >= 80.0;
    char *path;
    char *text;

    path = "./resources/failed.jpg";

    if (passed)
    {
        path = "./resources/passed.jpg";
    }
    
    gtk_widget_destroy(fixed);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    pixbuf = gdk_pixbuf_scale_simple(pixbuf, 200, 200, GDK_INTERP_BILINEAR);

    image = gtk_image_new_from_pixbuf(pixbuf);

    gtk_fixed_put(GTK_FIXED(fixed), image, 300, 80);

    text = g_strdup_printf("Odpowiedziałeś poprawnie na %d/%d pytań", correct_answers, length*5);
    label = gtk_label_new(text);
    gtk_fixed_put(GTK_FIXED(fixed), label, 270, 350);

    button = gtk_button_new_with_label("Kontynuuj");
    gtk_widget_set_size_request(button, 160, 32);
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 400);
    g_signal_connect (button, "clicked", G_CALLBACK (init_menu), NULL);

    button = gtk_button_new_with_label("Spróbuj ponownie");
    gtk_widget_set_size_request(button, 160, 32);
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 450);
    g_signal_connect (button, "clicked", G_CALLBACK (test), NULL);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

void answer()
{
    GtkWidget *image;
    GtkWidget *button;
    GdkPixbuf *pixbuf;
    gchar *ans;
    gchar *expected;
    char *path;

    expected = g_strdup_printf ("%d", iter->expected_result);
    ans = gtk_editable_get_chars(GTK_EDITABLE(entry), 0, -1);

    if (strcmp(ans, expected) == 0)
    {
        iter->answered_correctly = true;
        correct_answers++;
    }

    gtk_widget_destroy(fixed);

    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    if (iter->answered_correctly)
    {
        path = "./resources/correct.jpg";
    }
    else
    {
        path = "./resources/incorrect.jpg";
    }
    
    
    pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    pixbuf = gdk_pixbuf_scale_simple(pixbuf, 300, 300, GDK_INTERP_BILINEAR);

    image = gtk_image_new_from_pixbuf(pixbuf);

    gtk_fixed_put(GTK_FIXED(fixed), image, 220, 80);

    button = gtk_button_new_with_label("Kontynuuj");
    gtk_widget_set_size_request(button, 160, 32);
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 400);
    g_signal_connect (button, "clicked", G_CALLBACK (init_question), NULL);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);


    iter = iter->next;
}

void clear_questions()
{
    node tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }

    iter = NULL;
}

// function called when learning game type is chosen
void learn()
{
    read_settings();        //update all game parameters
    game = "learn";         //set game type
    correct_answers = 0;    //reset after previous game
    init_operation_choice();
}

// function called when test game type is chosen
void test()
{
    read_settings();        //update all game parameters
    game = "test";          //set game type
    correct_answers = 0;    //reset after previous game
    init_operation_choice();
}

void init_operation_choice()
{
    gtk_widget_destroy(fixed);

    GtkWidget *button;

    //initialize fixed
    fixed = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), fixed);

    //first button
    button = gtk_button_new_with_label("+");
    g_signal_connect (button, "clicked", G_CALLBACK (plus), NULL);

    gtk_widget_set_size_request(button, 50, 50);

    gtk_fixed_put(GTK_FIXED(fixed), button, 330, 150);


    //second button
    button = gtk_button_new_with_label("-");
    g_signal_connect (button, "clicked", G_CALLBACK (minus), NULL);

    gtk_widget_set_size_request(button, 50, 50);

    gtk_fixed_put(GTK_FIXED(fixed), button, 410, 150);


    //third button
    button = gtk_button_new_with_label("*");
    g_signal_connect (button, "clicked", G_CALLBACK (mult), NULL);

    gtk_widget_set_size_request(button, 50, 50);

    gtk_fixed_put(GTK_FIXED(fixed), button, 330, 210);


    //fourth button
    button = gtk_button_new_with_label("/");
    g_signal_connect (button, "clicked", G_CALLBACK (division), NULL);

    gtk_widget_set_size_request(button, 50, 50);

    gtk_fixed_put(GTK_FIXED(fixed), button, 410, 210);


    //fifth button
    button = gtk_button_new_with_label("Mieszane");
    g_signal_connect (button, "clicked", G_CALLBACK (mixed), NULL);

    gtk_widget_set_size_request(button, 130, 50);

    gtk_fixed_put(GTK_FIXED(fixed), button, 330, 270);


    //sixth button
    button = gtk_button_new_with_label("Powrót");
    g_signal_connect (button, "clicked", G_CALLBACK (init_play), NULL);

    gtk_widget_set_size_request(button, 130, 50);

    gtk_fixed_put(GTK_FIXED(fixed), button, 330, 330);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
}

void generate_questions()
{
    //reset state after previous game
    head = NULL;
    iter = NULL;

    //generating questions
    get_question();
    head = iter;        //first element

    for (int i = 0; i < length*5 - 1; i++)
    {
        get_question();
    }
    //finished generating questions

    iter = head;        //reset iterator before the game
}

void plus()
{
    operation = '+';

    generate_questions();

    init_question();
}

void minus()
{
    operation = '-';

    generate_questions();

    init_question();
}

void mult()
{
    operation = '*';

    generate_questions();

    init_question();
}

void division()
{
    operation = '/';

    generate_questions();

    init_question();
}

void mixed()
{
    //reset state after previous game
    head = NULL;
    iter = NULL;

    //generating questions
    operation = operations[rand()%4];
    get_question();    
    head = iter;

    for (int i = 0; i < length*5 - 1; i++)
    {
        operation = operations[rand()%4];
        get_question();
    }
    //finished generating questions

    iter = head;        //reset iterator before the game

    init_question();
}

//generates data for one question
void get_question()
{
    int idx;

    //get value range from table
    switch (operation)
    {
    case '+':
        idx = 0;
        break;
    case '-':
        idx = 1;
        break;
    case '*':
        idx = 2;
        break;
    case '/':
        idx = 3;
    default:
        break;
    }

    int left_range = ranges[difficulty-1][idx][0];
    int right_range = ranges[difficulty-1][idx][1];

    node q;
    q = (node)malloc(sizeof(struct Question)); // allocate memory using malloc()

    q->next = NULL;

    //make linked list connection
    if (iter)
    {
        iter->next = q;
    }
    
    iter = q;

    switch (operation)
    {
    case '+':
        q->number1 = rand()%right_range + left_range;   //generates two random numbers in given range
        q->number2 = rand()%right_range + left_range;
        q->expected_result = q->number1 + q->number2;
        break;
    case '-':
        q->expected_result = rand()%right_range + left_range;   //generates random number in given range
        q->number2 = rand()%100 + 1;
        q->number1 = q->number2 + q->expected_result;
        break;
    case '*':
        q->number1 = rand()%right_range + left_range;   //generates two random numbers in given range
        q->number2 = rand()%right_range + left_range;
        q->expected_result = q->number1 * q->number2;
        break;
    case '/':
        q->expected_result = rand()%right_range + left_range;   //generates random number in given range
        q->number2 = rand()%right_range + left_range;
        q->number1 = q->number2 * q->expected_result;
    default:
        break;
    }
    
    q->answered_correctly = false;
    q->operation = operation;
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
    g_signal_connect (button, "clicked", G_CALLBACK (learn), NULL);

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
    button = gtk_button_new_with_label("Powrót");
    g_signal_connect (button, "clicked", G_CALLBACK (init_menu), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach third button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 250);

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

    dif = json_object_new_int(difficulty);
    json_object_object_add(settings, "difficulty", dif);

    len = json_object_new_int(length);
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
        difficulty = json_object_get_int(dif);
        length = json_object_get_int(len);
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
    button = gtk_button_new_with_label("Ustawienia");
    g_signal_connect (button, "clicked", G_CALLBACK (init_settings), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach second button
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 200);

    //create third button
    button = gtk_button_new_with_label("Wyjscie");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_widget_set_size_request(button, 160, 32);

    //attach third button 
    gtk_fixed_put(GTK_FIXED(fixed), button, 310, 250);

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